#pragma once

#include <QScreen>
#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "requests.h"

class Client : public QObject
{
    Q_OBJECT
public:
    Client();
    static Client *Object;
    Q_INVOKABLE bool connect();
    Q_INVOKABLE bool reconnect();
    Q_INVOKABLE void disconnect();

signals:
    void signUpResult(QString key);
    void logInResult(QString key);
    void connected();
    void acquireUserList(QList<QStringList> data);
    void acquireMessageHistory(QList<QStringList> data);
    void acquireTextMessage(QString text, QString time, QString owner_key);
    void acquireUserInfo(QStringList data);

private:
    ~Client();
};
