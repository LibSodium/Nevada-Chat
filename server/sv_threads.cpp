#include "server.h"
#include "sv_threads.h"


SocketThread::~SocketThread()
{
    m_socket->deleteLater();
    m_socket = nullptr;
}

SocketThread::SocketThread(qintptr descriptor)
{
    m_descriptor = descriptor;
    m_socket = new QTcpSocket();
    m_socket->setSocketDescriptor(descriptor);
    QObject::connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    QObject::connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    QObject::connect(this, SIGNAL(sendData(QString)), SLOT(onSendData(QString)));
    QObject::connect(this, SIGNAL(disconnectFromServer()), SLOT(onDisconnected()));
    QObject::connect(this, SIGNAL(finished()), SLOT(deleteLater()));
}

void SocketThread::run()
{
    exec();
}

void SocketThread::onReadyRead()
{
    qDebug() << "read";
}

void SocketThread::onDisconnected()
{
    m_socket->disconnect();
    m_socket->disconnectFromHost();
    Server::Object->device_list.remove(m_descriptor);
    exit();
}

void SocketThread::onSendData(QString data)
{
    m_socket->write(data.toUtf8());
}
