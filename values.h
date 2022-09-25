#pragma once

namespace Chat
{
enum Request
{
    TrySignUp = 0x000010,
    ConnectToServer,
    TryLogIn,
    GetUserList,
    GetMessageHistory,
    LogOut,
    SendTextMessage,
    GetUserInfo
};
enum Response
{
    SignUpResult = 0x001000,
    LogInResult,
    Connected,
    AcquireUserList,
    AcquireMessageHistory,
    AcquireTextMessage,
    AcquireUserInfo
};
}
