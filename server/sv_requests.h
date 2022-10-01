#pragma once

class SocketThread;
class Deserializer;

struct Requests
{
public:
    static void TrySignUp         (Deserializer *read, SocketThread *thread = nullptr);
    static void TryLogIn          (Deserializer *read, SocketThread *thread = nullptr);
    static void GetChatList       (Deserializer *read, SocketThread *thread = nullptr);
    static void GetMessageHistory (Deserializer *read, SocketThread *thread = nullptr);
    static void LogOut            (Deserializer *read, SocketThread *thread = nullptr);
    static void SendTextMessage   (Deserializer *read, SocketThread *thread = nullptr);
    static void GetUserInfo       (Deserializer *read, SocketThread *thread = nullptr);
    static void GetOnlineList     (Deserializer *read, SocketThread *thread = nullptr);
    static void RestoreConnection (Deserializer *read, SocketThread *thread = nullptr);
};
