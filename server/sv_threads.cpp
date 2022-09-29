#include "values.h"
#include "server.h"
#include "database.h"
#include "sv_threads.h"
#include "serialization/serializer.h"

SocketThread::~SocketThread()
{
    m_socket->deleteLater();
    m_socket = nullptr;
    m_timer->deleteLater();
    m_timer = nullptr;
}

SocketThread::SocketThread(qintptr descriptor)
{
    m_descriptor = descriptor;
    m_socket = new QTcpSocket();
    m_socket->setSocketDescriptor(descriptor);
    m_timer = new QTimer();
    m_timer->setInterval(2000);
    QObject::connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    QObject::connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(onlineBroadcast()));
    QObject::connect(m_timer, SIGNAL(timeout()), m_timer, SLOT(start()));
    QObject::connect(this, SIGNAL(sendData(QString)), SLOT(onSendData(QString)));
    QObject::connect(this, SIGNAL(disconnectFromServer()), SLOT(onDisconnected()));
    QObject::connect(this, SIGNAL(finished()), SLOT(deleteLater()));
    m_timer->start();
}

void SocketThread::run() {exec();}

void SocketThread::onDisconnected()
{
    m_socket->disconnect();
    m_socket->disconnectFromHost();
    m_timer->stop();
    Server::Object->device_list.remove(m_descriptor);
    exit();
}

void SocketThread::onSendData(QString data)
{
    m_socket->write(data.toUtf8());
}

void SocketThread::onlineBroadcast()
{
    m_socket->write("$online$");
}
