#pragma once

#include <QObject>

class Requests
{
public:
    static void TrySignUp        (QString login, QString password, QString nick);
    static void ConnectToServer  (QString ip, int port);
    static void TryLogIn         (QString login, QString password);
    static void GetUserList      (QString my_key);
    static void GetMessageHistory(QString my_key, QString chat_key);
    static void LogOut           (QString my_key);
    static void SendTextMessage  (QString my_key, QString chat_key, QString message);
    static void GetUserInfo      (QString user_key);
};
