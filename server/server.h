#pragma once

#include <QDir>
#include <QMutex>
#include <QObject>
#include <QDateTime>
#include <QTcpServer>
#include <QStandardPaths>

class Database;
class SocketThread;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server() {};
    static Server *Object;
    Q_INVOKABLE bool start(int port = 2222);
    Q_INVOKABLE void stop();
    
    QString database_path;
    bool reading_data_from_database = false;
    bool writing_data_to_database = false;
    
    void insertDevice(int descriptor, SocketThread *device);
    void removeDevice(int descriptor);
    SocketThread *getDevice(int descriptor);
    
    void insertOnlineUser(int descriptor, QString key);
    void removeOnlineUser(QString key);
    QMap<QString, qintptr> getOnlineList();
    
public slots:
    void disconnect(int descr);
    void disconnectAll();

private:
    void incomingConnection(qintptr descriptor);

private:
    ~Server() {};
    QMutex m_online_list_mutex;
    QMap<QString, qintptr> m_online_users;
    QMutex m_device_list_mutex;
    QMap<qintptr, SocketThread*> m_device_list;
};
