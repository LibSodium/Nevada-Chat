#include "values.h"
#include "client/client.h"
#include "serialization/serializer.h"
#include "serialization/deserializer.h"

Client *Client::Object = nullptr;

Client::Client()
{
    m_socket = new QTcpSocket();
}

bool Client::connect()
{
    m_socket->connectToHost("192.168.0.101", 2222);
    m_socket->waitForConnected(3000);
    qDebug() << "lol";
}

bool Client::reconnect()
{
    
}

void Client::disconnect()
{

}

void Client::onReadyRead()
{
    
}

void Client::onDisconnected()
{

}

