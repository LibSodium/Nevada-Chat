#pragma once

namespace Chat
{
enum Request
{
    TrySignUp = 0x000010,
    TryLogIn,
    GetChatList,
    GetMessageHistory,
    LogOut,
    SendTextMessage,
    GetUserInfo,
    GetOnlineList,
    RestoreConnection
};
enum Response
{
    Online = 0x001000,
    SignUpResult,
    LogInResult,
    AcquireChatList,
    AcquireMessageHistory,
    AcquireTextMessage,
    AcquireUserInfo,
    AcquireOnlineList
};
}
