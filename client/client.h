#pragma once

#include <QTimer>
#include <QScreen>
#include <QTcpSocket>
#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

class ConnectionTracker;
class ConnectionRestorer;

class Client : public QObject
{
    Q_OBJECT
public:
    Client();
    static Client *Object;
    Q_INVOKABLE bool connect(QString ip, int port);
    Q_INVOKABLE void disconnect();

private:
    QTcpSocket *m_socket;
    ConnectionTracker *m_tracker;
    ConnectionRestorer *m_restorer;
    QString server_ip;
    int server_port;

public slots: // not from qml
    void onReadyRead();
    void onDisconnected();
    
public slots: // from qml
    void trySignUp(QString login, QString password, QString nick);
    void connectToServer(QString ip, int port);
    void tryLogIn(QString login, QString password);
    void getUserList(QString my_key);
    void getMessageHistory(QString my_key, QString chat_key);
    void logOut(QString my_key);
    void sendTextMessage(QString my_key, QString chat_key, QString message);
    void getUserInfo(QString user_key);

signals: // connected to qml
    void signUpResult(QString key);
    void logInResult(QString key);
    void connected();
    void acquireUserList(QList<QStringList> data);
    void acquireMessageHistory(QList<QStringList> data);
    void acquireTextMessage(QString text, QString time, QString owner_key);
    void acquireUserInfo(QStringList data);
    void connectionLost();
    void connectionRestored();
    
signals: // not connected to qml
    void response();
    
private:
    ~Client() {};
};
