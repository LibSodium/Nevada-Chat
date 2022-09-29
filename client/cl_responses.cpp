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
    case Chat::Response::AcquireUserList:       {Responses::AcquireUserList(read); break;}
    case Chat::Response::AcquireMessageHistory: {Responses::AcquireMessageHistory(read); break;}
    case Chat::Response::AcquireTextMessage:    {Responses::AcquireTextMessage(read); break;}
    case Chat::Response::AcquireUserInfo:       {Responses::AcquireUserInfo(read); break;}
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
    emit Client::Object->logInResult(key, nick);
}

void Responses::AcquireUserList(Deserializer *read)
{

}

void Responses::AcquireMessageHistory(Deserializer *read)
{

}

void Responses::AcquireTextMessage(Deserializer *read)
{

}

void Responses::AcquireUserInfo(Deserializer *read)
{

}
