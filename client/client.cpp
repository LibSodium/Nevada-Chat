#include "values.h"
#include "client/client.h"
#include "client/cl_threads.h"
#include "serialization/serializer.h"
#include "serialization/deserializer.h"

Client *Client::Object = nullptr;

Client::Client()
{
    m_socket = new QTcpSocket();
    
    m_tracker = new ConnectionTracker(4000);
    QObject::connect(m_tracker, SIGNAL(connectionLost()), this, SIGNAL(connectionLost()));
    QObject::connect(m_tracker, SIGNAL(connectionLost()), m_tracker, SLOT(stop()));
    QObject::connect(this, SIGNAL(response()), m_tracker, SLOT(onResponse()));
    
    m_restorer = new ConnectionRestorer(m_socket, 2000);
    QObject::connect(m_restorer, SIGNAL(connectionRestored()), m_restorer, SLOT(stop()));
    QObject::connect(m_restorer, SIGNAL(connectionRestored()), this, SIGNAL(connectionRestored()));
    QObject::connect(m_restorer, SIGNAL(timeout()), m_restorer, SLOT(tryToRestoreConnection()));
    QObject::connect(m_tracker, SIGNAL(connectionLost()), m_restorer, SLOT(start()));
    QObject::connect(m_restorer, SIGNAL(timeout()), m_tracker, SLOT(start()));
}

bool Client::connect(QString ip, int port)
{
    m_socket->connectToHost(ip, port);
    if(m_socket->waitForConnected(500))
    {
        QObject::connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        QObject::connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
        
        m_tracker->start();
        m_restorer->setServer(ip, port);
        
        server_ip = ip;
        server_port = port;
        return true;
    }
    else
    {
        m_socket->disconnectFromHost();
        return false;
    }
}

void Client::disconnect()
{
    
}

void Client::onDisconnected()
{
    
}

QString Client::currentTime(QString format)
{return QDateTime::currentDateTime().toString(format);}
