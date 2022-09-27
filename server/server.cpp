#include "server/server.h"
#include "server/sv_threads.h"

Server *Server::Object = nullptr;

bool Server::start(int port)
{
    if(this->listen(QHostAddress::Any, 2222))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Server::stop()
{
    this->close();
}

void Server::incomingConnection(qintptr descriptor)
{
    SocketThread *thread = new SocketThread(descriptor);
    thread->start();
    device_list.insert(descriptor, thread);
    qDebug() << "connected";
}

void Server::sendData(int desc, QString data)
{
    if(!device_list.contains(desc)) return;
    emit device_list.value(desc)->sendData(data);
}

void Server::disconnect(int desc)
{
    if(!device_list.contains(desc)) return;
    emit device_list.value(desc)->disconnectFromServer();
}

void Server::disconnectAll()
{
    
}
