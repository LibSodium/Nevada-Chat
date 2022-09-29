#pragma once

#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QTcpSocket>

class Database;

class SocketThread : public QThread
{
    Q_OBJECT
public:
    ~SocketThread();
    SocketThread(qintptr descriptor);
    void run() override;

public slots:
    void onReadyRead();
    void onDisconnected();
    void onSendData(QString data);
    void onlineBroadcast();
    
signals:
    void sendData(QString data);
    void disconnectFromServer();
    
private:
    qintptr m_descriptor;
    QString m_ip;
    QTcpSocket *m_socket;
    QTimer *m_timer;
    Database *m_database;
};
