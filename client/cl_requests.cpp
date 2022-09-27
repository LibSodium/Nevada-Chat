#pragma once

#include "client.h"
#include "serialization/serializer.h"

void Client::trySignUp(QString login, QString password, QString nick)
{
    Serializer(m_socket).stream();
}

void Client::connectToServer(QString ip, int port)
{
    Serializer(m_socket).stream();
}


void Client::tryLogIn(QString login, QString password)
{
    Serializer(m_socket).stream();
}


void Client::getUserList(QString my_key)
{
    Serializer(m_socket).stream();
}


void Client::getMessageHistory(QString my_key, QString chat_key)
{
    Serializer(m_socket).stream();
}


void Client::logOut(QString my_key)
{
    Serializer(m_socket).stream();
}


void Client::sendTextMessage(QString my_key, QString chat_key, QString message)
{
    Serializer(m_socket).stream();
}


void Client::getUserInfo(QString user_key)
{
    Serializer(m_socket).stream();
}
