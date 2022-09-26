#pragma once

#include <QObject>

class Deserializer;

struct Responses
{
public:
    static void SignUpResult         (Deserializer *read);
    static void LogInResult          (Deserializer *read);
    static void Connected            (Deserializer *read);
    static void AcquireUserList      (Deserializer *read);
    static void AcquireMessageHistory(Deserializer *read);
    static void AcquireTextMessage   (Deserializer *read);
    static void AcquireUserInfo      (Deserializer *read);
};
