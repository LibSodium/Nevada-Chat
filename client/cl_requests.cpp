#pragma once

#include "values.h"
#include "client.h"
#include "serialization/serializer.h"

void Client::onConnectionRestored()
{
    Serializer(m_socket).stream() << Chat::Request::RestoreConnection << m_key;
}

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
    Serializer(m_socket).stream() << Chat::Request::GetChatList << my_key;
}


void Client::getMessageHistory(QString my_key, QString chat_key)
{
    Serializer(m_socket).stream() << Chat::Request::GetMessageHistory << my_key << chat_key;
}


void Client::logOut(QString my_key)
{
    Serializer(m_socket).stream() << Chat::Request::LogOut << my_key;
}


void Client::sendTextMessage(QString my_key, QString chat_key, QString message)
{
    Serializer(m_socket).stream() << Chat::Request::SendTextMessage << my_key << chat_key << message;
}


void Client::getUserInfo(QString user_key)
{
    Serializer(m_socket).stream() << Chat::Request::GetUserInfo;
}

void Client::getOnlineList()
{
    Serializer(m_socket).stream() << Chat::Request::GetOnlineList;
}
