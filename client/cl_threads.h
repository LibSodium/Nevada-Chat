#pragma once

#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QTcpSocket>

class ConnectionTracker : public QTimer
{
    Q_OBJECT
public:
    ConnectionTracker(int periodicity = 2000);
    bool connected = false;
    
public slots:
    void onResponse();
    void onNoResponse();
    
signals:
    void connectionLost();
};

class ConnectionRestorer : public QTimer
{
    Q_OBJECT
public:
    ConnectionRestorer(QTcpSocket *socket, int periodicity = 2000);
        
    void setServer(QString ip, int port) {m_ip = ip; m_port = port;}
    
signals:
    void connectionRestored();
    
public slots:
    void tryToRestoreConnection();
    
private:
    QTcpSocket *m_socket;
    QString m_ip;
    int m_port;
};
