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
    case Chat::Request::TrySignUp:         {Requests::TrySignUp(read); break;}
    case Chat::Request::TryLogIn:          {Requests::TryLogIn(read); break;}
    case Chat::Request::GetChatList:       {Requests::GetChatList(read); break;}
    case Chat::Request::GetMessageHistory: {Requests::GetMessageHistory(read); break;}
    case Chat::Request::LogOut:            {Requests::LogOut(read); break;}
    case Chat::Request::SendTextMessage:   {Requests::SendTextMessage(read); break;}
    case Chat::Request::GetUserInfo:       {Requests::GetUserInfo(read); break;}
    default: {qDebug() << "server socket thread -> unknown action triggered:" << action_id; break;}
    }
    delete read;
}

void Requests::TrySignUp(Deserializer *read)
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
        Serializer(read->device()).stream() << Chat::Response::SignUpResult << key;
    }
    delete db;
}

void Requests::TryLogIn(Deserializer *read)
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
        Serializer(read->device()).stream() << Chat::Response::LogInResult << key << nick;
    }
    delete db;
}

void Requests::GetChatList(Deserializer *read)
{
    
}

void Requests::GetMessageHistory(Deserializer *read)
{
    
}

void Requests::LogOut(Deserializer *read)
{
    
}

void Requests::SendTextMessage(Deserializer *read)
{
    
}

void Requests::GetUserInfo(Deserializer *read)
{
    
}
