#include "values.h"
#include "client/client.h"
#include "serialization/serializer.h"
#include "serialization/deserializer.h"

Client *Client::Object = nullptr;

Client::Client()
{

}

bool Client::connect()
{

}

bool Client::reconnect()
{

}

void Client::disconnect()
{

}

void Client::onReadyRead()
{
    Deserializer *read = new Deserializer(m_socket);
    int action; read->stream() >> action;
    switch (action)
    {
    case Chat::Response::Online: {qDebug() << "online"; break;}
    }
    delete read;
}

void Client::onDisconnected()
{

}





// === CLIENT REQUESTS ===

void Client::trySignUp(QString login, QString password, QString nick)
{
    Serializer(m_socket).stream();
}

void Client::connectToServer(QString ip, int port)
{
    Serializer(m_socket).stream();
}


void Client::tryLogIn(QString login, QString password)
{
    Serializer(m_socket).stream();
}


void Client::getUserList(QString my_key)
{
    Serializer(m_socket).stream();
}


void Client::getMessageHistory(QString my_key, QString chat_key)
{
    Serializer(m_socket).stream();
}


void Client::logOut(QString my_key)
{
    Serializer(m_socket).stream();
}


void Client::sendTextMessage(QString my_key, QString chat_key, QString message)
{
    Serializer(m_socket).stream();
}


void Client::getUserInfo(QString user_key)
{
    Serializer(m_socket).stream();
}

