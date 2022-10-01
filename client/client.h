#pragma once

#include <QTimer>
#include <QScreen>
#include <QDateTime>
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
    QString &key() {return m_key;}
    Q_INVOKABLE bool connect(QString ip, int port);
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE QString currentTime(QString format = "dd.MM.yyyy hh:mm:ss");

private:
    QTcpSocket *m_socket;
    ConnectionTracker *m_tracker;
    ConnectionRestorer *m_restorer;
    QString server_ip;
    int server_port;
    QString m_key;
    
public slots: // not from qml
    void onReadyRead();
    void onDisconnected();
    void onConnectionRestored();
    
public slots: // from qml
    void trySignUp(QString login, QString password, QString nick);
    void tryLogIn(QString login, QString password);
    void getChatList(QString my_key);
    void getMessageHistory(QString my_key, QString chat_key);
    void logOut(QString my_key);
    void sendTextMessage(QString my_key, QString chat_key, QString message);
    void getUserInfo(QString user_key);
    void getOnlineList();
    //void changeAccountData(QString photo_path, QString login, QString password, QString nickname);

signals: // connected to qml
    void signUpResult(QString key);
    void logInResult(QString key, QString nick);
    void connected();
    void acquireChatList(QList<QStringList> data);
    void acquireMessageHistory(QList<QStringList> data);
    void acquireTextMessage(QStringList message_data);
    void acquireUserInfo(QStringList data);
    void connectionLost();
    void connectionRestored();
    void acquireOnlineList(QStringList keys);
    
signals: // not connected to qml
    void response();
    
private:
    ~Client() {};
};
