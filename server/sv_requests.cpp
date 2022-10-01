#include "values.h"
#include "global.h"
#include "database.h"
#include "server/server.h"
#include "server/sv_threads.h"
#include "server/sv_requests.h"
#include "serialization/serializer.h"
#include "serialization/deserializer.h"

void SocketThread::onReadyRead()
{
    Deserializer *read = new Deserializer(m_socket);
    int action_id; read->stream() >> action_id;
    switch (action_id)
    {
    case Chat::Request::RestoreConnection: {Requests::RestoreConnection(read, this); break;}
    case Chat::Request::TrySignUp:         {Requests::TrySignUp(read); break;}
    case Chat::Request::TryLogIn:          {Requests::TryLogIn(read, this); break;}
    case Chat::Request::GetChatList:       {Requests::GetChatList(read); break;}
    case Chat::Request::GetMessageHistory: {Requests::GetMessageHistory(read); break;}
    case Chat::Request::LogOut:            {Requests::LogOut(read, this); break;}
    case Chat::Request::SendTextMessage:   {Requests::SendTextMessage(read, this); break;}
    case Chat::Request::GetUserInfo:       {Requests::GetUserInfo(read); break;}
    case Chat::Request::GetOnlineList:     {Requests::GetOnlineList(read); break;}
    default: {qDebug() << "server socket thread -> unknown action triggered:" << action_id; break;}
    }
    delete read;
}

void Requests::TrySignUp(Deserializer *read, SocketThread *thread)
{
    QString login, password, nick;
    read->stream() >> login >> password >> nick;
    Database *db = new Database(NULL, qint64(QThread::currentThreadId()), Server::Object->database_path + "/chats.db");
    QString request = DB_Requests::select("users", {"rowid"}, {"login = " + login});
    if(db->checkData(request))
    {
        Serializer(read->device()).stream() << Chat::Response::SignUpResult << QString("-1");
    }
    else
    {
        QString key = Generators::key();
        db->writeData(DB_Requests::insert("users", {"key = " + key,
                                                    "login = " + login,
                                                    "password = " + password,
                                                    "nickname = " + nick}));
        db->writeData(DB_Requests::insert("chats", {"key = " + key,
                                                    "name = " + nick}));
        Serializer(read->device()).stream() << Chat::Response::SignUpResult << key;
    }
    delete db;
}

void Requests::TryLogIn(Deserializer *read, SocketThread *thread)
{
    QString login, password;
    read->stream() >> login >> password;
    Database *db = new Database(NULL, qint64(QThread::currentThreadId()), Server::Object->database_path + "/chats.db");
    QString request = DB_Requests::select("users", {"key", "nickname"}, {"login = " + login, "password = " + password});
    DBData acquired_data;
    db->readData(request, acquired_data);
    if(acquired_data.isEmpty())
    {
        Serializer(read->device()).stream() << Chat::Response::LogInResult << QString("-1");
    }
    else
    {
        QString key = acquired_data[0][0];
        QString nick = acquired_data[0][1];
        thread->key() = key;
        if(Server::Object->getOnlineList().contains(key))
        {
            Serializer(read->device()).stream() << Chat::Response::LogInResult << QString("-2");
            return;
        }
        Server::Object->insertOnlineUser(thread->descriptor(), key);
        Serializer(read->device()).stream() << Chat::Response::LogInResult << key << nick;
    }
    delete db;
}

void Requests::GetChatList(Deserializer *read, SocketThread *thread)
{
    QString user_key;
    read->stream() >> user_key;
    Database *db = new Database(NULL, qint64(QThread::currentThreadId()), Server::Object->database_path + "/chats.db");
    QString request = DB_Requests::select("chats", {"key", "name"}, {"key != " + user_key});
    DBData acquired_data;
    db->readData(request, acquired_data);
    Serializer(read->device()).stream() << Chat::Response::AcquireChatList << acquired_data;
    delete db;
}

void Requests::GetMessageHistory(Deserializer *read, SocketThread *thread)
{
    QString user_key, chat_key;
    read->stream() >> user_key >> chat_key;
    Database *db = new Database(NULL, qint64(QThread::currentThreadId()), Server::Object->database_path + "/messages.db");
    QString request = DB_Requests::select("messages", {}, {"*WHERE sender_key = '" + user_key +
                                                           "' AND recipient_key = '" + chat_key +
                                                           "' OR recipient_key = '" + user_key +
                                                           "' AND sender_key = '" + chat_key + "'"});
    DBData acquired_data;
    db->readData(request, acquired_data);
    delete db;
    Serializer(read->device()).stream() << Chat::Response::AcquireMessageHistory << acquired_data;
}

void Requests::LogOut(Deserializer *read, SocketThread *thread)
{
    QString user_key;
    read->stream() >> user_key;
    Server::Object->removeOnlineUser(user_key);
}

void Requests::SendTextMessage(Deserializer *read, SocketThread *thread)
{
    QString sender_key, receiver_key, message;
    read->stream() >> sender_key >> receiver_key >> message;
    Database *db = new Database(NULL, qint64(QThread::currentThreadId()), Server::Object->database_path + "/messages.db");
    QString key = Generators::key();
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    db->writeData(DB_Requests::insert("messages", {"key = " + key,
                                                   "sender_key = " + sender_key,
                                                   "recipient_key = " + receiver_key,
                                                   "message_text = " + message,
                                                   "date = " + date}));
    DBData message_data;
    QString request = DB_Requests::select("messages", {}, {"key = " + key});
    db->readData(request, message_data);
    if(Server::Object->getOnlineList().contains(receiver_key))
    {
        qintptr descriptor = Server::Object->getOnlineList().value(receiver_key);
        emit Server::Object->getDevice(descriptor)->sendMessage(message_data.first());
    }
    delete db;
}

void Requests::GetUserInfo(Deserializer *read, SocketThread *thread)
{

}

void Requests::GetOnlineList(Deserializer *read, SocketThread *thread)
{
    QStringList online_list = Server::Object->getOnlineList().keys();
    Serializer(read->device()).stream() << Chat::Response::AcquireOnlineList << online_list;
}

void Requests::RestoreConnection(Deserializer *read, SocketThread *thread)
{
    QString key;
    read->stream() >> key;
    if(key.isEmpty()) return;
    Server::Object->insertOnlineUser(thread->descriptor(), key);
}
