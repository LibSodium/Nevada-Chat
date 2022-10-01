#include "values.h"
#include "client/client.h"
#include "client/cl_responses.h"
#include "serialization/deserializer.h"

void Client::onReadyRead()
{
    if(m_socket->peek(8) == "$online$")
    {
        m_socket->readAll(); 
        emit response();
        return;
    }
    Deserializer *read = new Deserializer(m_socket);
    int action_id; read->stream() >> action_id;
    switch (action_id)
    {
    case Chat::Response::SignUpResult:          {Responses::SignUpResult(read); break;}
    case Chat::Response::LogInResult:           {Responses::LogInResult(read); break;}
    case Chat::Response::AcquireChatList:       {Responses::AcquireChatList(read); break;}
    case Chat::Response::AcquireMessageHistory: {Responses::AcquireMessageHistory(read); break;}
    case Chat::Response::AcquireTextMessage:    {Responses::AcquireTextMessage(read); break;}
    case Chat::Response::AcquireUserInfo:       {Responses::AcquireUserInfo(read); break;}
    case Chat::Response::AcquireOnlineList:     {Responses::AcquireOnlineList(read); break;} 
    default: {qDebug() << "client socket thread -> unknown action triggered:" << action_id; break;}
    }
    delete read;
    emit response();
}

void Responses::SignUpResult(Deserializer *read)
{
    QString result;
    read->stream() >> result;
    emit Client::Object->signUpResult(result);
}

void Responses::LogInResult(Deserializer *read)
{
    QString key, nick;
    read->stream() >> key >> nick;
    if(key.size() != 2) Client::Object->key() = key;
    emit Client::Object->logInResult(key, nick);
}

void Responses::AcquireChatList(Deserializer *read)
{
    QList<QStringList> acquired_data;
    read->stream() >> acquired_data;
    emit Client::Object->acquireChatList(acquired_data);
}

void Responses::AcquireMessageHistory(Deserializer *read)
{
    QList<QStringList> history;
    read->stream() >> history;
    emit Client::Object->acquireMessageHistory(history);
}

void Responses::AcquireTextMessage(Deserializer *read)
{
    QStringList message_data;
    read->stream() >> message_data;
    emit Client::Object->acquireTextMessage(message_data);
}

void Responses::AcquireUserInfo(Deserializer *read)
{

}

void Responses::AcquireOnlineList(Deserializer *read)
{
    QStringList online_list;
    read->stream() >> online_list;
    emit Client::Object->acquireOnlineList(online_list);
}
