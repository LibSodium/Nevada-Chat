#include "cl_threads.h"

ConnectionTracker::ConnectionTracker(int periodicity)
{
    this->setInterval(periodicity);
    QObject::connect(this, SIGNAL(timeout()), SLOT(onNoResponse()));
    connected = true;
}

void ConnectionTracker::onResponse()
{
    this->start();
}

void ConnectionTracker::onNoResponse()
{
    connected = false;
    qDebug() << "connection lost.";
    emit connectionLost();
}

ConnectionRestorer::ConnectionRestorer(QTcpSocket *socket, int periodicity)
    : m_socket(socket)
{
    this->setInterval(periodicity);
}

void ConnectionRestorer::tryToRestoreConnection()
{
    m_socket->connectToHost(m_ip, m_port);
    if(m_socket->waitForConnected(500))
    {
        emit connectionRestored();
    }
    else
    {
        this->start();
        qDebug() << "restoring connection...";
    }
}
