#include "global.h"
#include "server/server.h"
#include "server/sv_threads.h"

Server *Server::Object = nullptr;

bool Server::start(int port)
{
    if(this->listen(QHostAddress::Any, port))
    {
        database_path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        if(!QDir().exists(database_path)) QDir().mkdir(database_path);
        database_path += "/databases";
        if(!QDir().exists(database_path))
        {
            QDir().mkdir(database_path);
            Files::copy(":/db_files", database_path);
        }
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
    for(auto &desc : device_list.keys())
    {
        emit device_list.value(desc)->disconnectFromServer();
    }
}
