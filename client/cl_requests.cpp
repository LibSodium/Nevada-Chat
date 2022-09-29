#pragma once

#include "values.h"
#include "client.h"
#include "serialization/serializer.h"

void Client::trySignUp(QString login, QString password, QString nick)
{
    Serializer(m_socket).stream() << Chat::Request::TrySignUp << login << password << nick;
}

void Client::tryLogIn(QString login, QString password)
{
    Serializer(m_socket).stream() << Chat::Request::TryLogIn << login << password;
}

void Client::getChatList(QString my_key)
{
    Serializer(m_socket).stream() << Chat::Request::GetChatList;
}


void Client::getMessageHistory(QString my_key, QString chat_key)
{
    Serializer(m_socket).stream() << Chat::Request::GetMessageHistory;
}


void Client::logOut(QString my_key)
{
    Serializer(m_socket).stream() << Chat::Request::LogOut;
}


void Client::sendTextMessage(QString my_key, QString chat_key, QString message)
{
    Serializer(m_socket).stream() << Chat::Request::SendTextMessage;
}


void Client::getUserInfo(QString user_key)
{
    Serializer(m_socket).stream() << Chat::Request::GetUserInfo;
}
