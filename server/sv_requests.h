#pragma once

class Deserializer;

struct Requests
{
public:
    static void TrySignUp         (Deserializer *read);
    static void TryLogIn          (Deserializer *read);
    static void GetChatList       (Deserializer *read);
    static void GetMessageHistory (Deserializer *read);
    static void LogOut            (Deserializer *read);
    static void SendTextMessage   (Deserializer *read);
    static void GetUserInfo       (Deserializer *read);
};
