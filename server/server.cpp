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
    insertDevice(descriptor, thread);
}

void Server::disconnect(int desc)
{
    if(!m_device_list.contains(desc)) return;
    emit m_device_list.value(desc)->disconnectFromServer();
}

void Server::disconnectAll()
{
    for(auto &desc : m_device_list.keys())
    {
        emit m_device_list.value(desc)->disconnectFromServer();
    }
}

void Server::insertDevice(int descriptor, SocketThread *device)
{
    m_device_list_mutex.lock();
    m_device_list.insert(descriptor, device);
    m_device_list_mutex.unlock();
}

void Server::removeDevice(int descriptor)
{
    m_device_list_mutex.lock();
    if(m_device_list.contains(descriptor))
        m_device_list.remove(descriptor);
    m_device_list_mutex.unlock();
}

SocketThread *Server::getDevice(int descriptor)
{
    if(m_device_list.contains(descriptor))
    {
        return m_device_list.value(descriptor);
    }
    else
    {
        return nullptr;
    }
}

void Server::insertOnlineUser(int descriptor, QString key)
{
    m_online_list_mutex.lock();
    m_online_users.insert(key, descriptor);
    m_online_list_mutex.unlock();
}

void Server::removeOnlineUser(QString key)
{
    m_online_list_mutex.lock();
    if(m_online_users.contains(key))
        m_online_users.remove(key);
    m_online_list_mutex.unlock();
}

QMap<QString, qintptr> Server::getOnlineList()
{
    return m_online_users;
}
