#pragma once

#include <QObject>
#include <QTcpServer>

class SocketThread;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server() {};
    static Server *Object;
    Q_INVOKABLE bool start(int port = 2222);
    Q_INVOKABLE void stop();
    QMap<qintptr, SocketThread*> device_list;
    
public slots:
    void sendData(int descr, QString data);
    void disconnect(int descr);
    void disconnectAll();
    
private:
    void incomingConnection(qintptr descriptor);

private:
    ~Server() {};
};
