#include "values.h"
#include "client/client.h"
#include "serialization/serializer.h"
#include "serialization/deserializer.h"

Client *Client::Object = nullptr;

Client::Client()
{
    m_socket = new QTcpSocket();
}

bool Client::connect(QString ip, int port)
{
    m_socket->connectToHost(ip, port);
    if(m_socket->waitForConnected(500))
    {
        QObject::connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        QObject::connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
        return true;
    }
    else
    {
        return false;
    }
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
    qDebug() << "disconnected";
}

