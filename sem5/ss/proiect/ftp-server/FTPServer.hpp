#ifndef _FTP_SERVER_HPP_
#define _FTP_SERVER_HPP_

typedef _Return_type_success_(return >= 0) LONG NTSTATUS;

#define STATUS_SUCCESS                          ((NTSTATUS)0x00000000L)
#define STATUS_UNSUCCESSFUL                     ((NTSTATUS)0xC0000001L)

#define USERNAME_MAX_LENGTH         25
#define PASSWORD_MAX_LENGTH         32
#define MESSAGE_MAX_LENGTH          256
#define HARDCODED_USER              "test"
#define HARDCODED_PASSWORD          "test123"

typedef enum class _CLIENT_ACCESS : BYTE
{
    Unknown             = 0,
    NotLoggedIn         = 1,
    ReadOnly            = 2,
    CreateNew           = 3,
    Full                = 4,

    MaxClientAccess
} CLIENT_ACCESS, * PCLIENT_ACCESS;

typedef struct _CLIENT_CONTEXT
{
    SOCKET        Socket = { 0 };
    CHAR          UserName[USERNAME_MAX_LENGTH] = { 0 };
    CHAR          CurrentDir[MAX_PATH] = { 0 };
    CLIENT_ACCESS Access = CLIENT_ACCESS::Unknown;
    IN_ADDR       IPv4;
    IN_ADDR       DataIPv4;
    USHORT        DataPort;
    SOCKET        DataSocket = { 0 };
} CLIENT_CONTEXT, * PCLIENT_CONTEXT;

class FTPServer
{
    std::unique_ptr<BS::thread_pool_light> threadPool;
    SOCKET listenSocket = { 0 };

public:
    FTPServer();
    ~FTPServer();

    FTPServer(_In_ const FTPServer& Other) = delete;
    FTPServer& operator=(_In_ const FTPServer& Other) = delete;

    FTPServer(_Inout_ FTPServer&& Other) = delete;
    FTPServer& operator=(_In_ FTPServer&& Other) = delete;

    NTSTATUS
    Start();

private:
    VOID
    HandleConnections();

    VOID
    HandleConnection(_Inout_ CLIENT_CONTEXT& ClientContext);

    VOID
    ProcessCommand(_In_ const std::string& Command, _Inout_ CLIENT_CONTEXT& ClientContext);

    _Success_(return)
    bool
    SendString(_In_ const CLIENT_CONTEXT& ClientContext, _In_ const std::string& Message);

    _Success_(return)
    bool
    SendString(_In_ const SOCKET& ClientContext, _In_ const std::string& Message);

    _Success_(return)
    bool
    HandleUSER(_Inout_ CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument);

    _Success_(return)
    bool
    HandlePASS(_Inout_ CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument);

    _Success_(return)
    bool
    HandleSYST(_In_ const CLIENT_CONTEXT& ClientContext);

    _Success_(return)
    bool
    HandleFEAT(_In_ const CLIENT_CONTEXT& ClientContext);

    _Success_(return)
    bool
    HandlePWD(_In_ const CLIENT_CONTEXT& ClientContext);

    _Success_(return)
    bool
    HandleCWD(_Inout_ CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument);

    _Success_(return)
    bool
    HandleTYPE(_In_ const CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument);

    _Success_(return)
    bool
    HandleLIST(_Inout_ CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument);

    _Success_(return)
    bool
    HandlePORT(_Inout_ CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument);

    _Success_(return)
    bool
    HandleREST(_In_ const CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument);

    _Success_(return)
    bool
    HandleQUIT(_In_ const CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument);

    _Success_(return)
    bool
    HandleRETR(_Inout_ CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument);

    _Success_(return)
    bool
    HandleSTOR(_Inout_ CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument);

    _Success_(return)
    bool
    HandleDELE(_In_ const CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument);

    _Success_(return)
    bool
    HandleABOR(_In_ const CLIENT_CONTEXT& ClientContext);

    _Success_(return)
    bool
    HandlePASV(_Inout_ CLIENT_CONTEXT& ClientContext);
};

#endif//_FTP_SERVER_HPP_