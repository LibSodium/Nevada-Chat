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
    QString &key() {return m_key;}
    qintptr &descriptor() {return m_descriptor;}
    
public slots:
    void onReadyRead();
    void onDisconnected();
    void onSendMessage(QStringList message_data);
    void onlineBroadcast();
    
signals:
    void sendMessage(QStringList message_data);
    void disconnectFromServer();
    
private:
    qintptr m_descriptor;
    QString m_ip;
    QTcpSocket *m_socket;
    QTimer *m_timer;
    Database *m_database;
    QString m_key;
};
