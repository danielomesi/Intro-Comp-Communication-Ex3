#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <codecvt>


using namespace std;

#pragma comment(lib, "Ws2_32.lib")

#define TIME_PORT 8080
#define MAX_SOCKETS 60
#define MAX_PHRASES 100
#define EMPTY 0
#define LISTEN 1
#define CLIENT_CHANNEL 2
#define GET 1
#define POST 2
#define HTML_FILE_NAME "index.html"
#define DEFAULT_LANGUAGE "en"
#define EMPTY_STRING ""
#define BUFFER_SIZE 8192

typedef struct SocketState
{
    SOCKET sock;            // Socket handle
    int socket_type;
    bool isWaitingForClientMsg;             // Receiving?
    bool isSendNeeded;             // Sending?
    int sendSubType;      // Sending sub-type
    char buffer[BUFFER_SIZE];    // Increase buffer size for HTTP requests
    int len;
} SocketState;

typedef struct Phrase
{
    int id;
    string str;
} Phrase;

extern SocketState sockets[MAX_SOCKETS];
extern vector<Phrase> phrases;
extern int socketsCount;

void StartServer();
bool AddSocket(SOCKET id, int what);
void RemoveSocket(int index);
void AcceptConnection(int index);
void ReceiveMessage(int index);
void SendMessage(int index);
void HandleHttpRequest(int index);
void HandleGetRequest(int index, const char* path);
void HandlePostRequest(int index, const char* path);
void HandleDeleteRequest(int socketIndex, const char* path);
void HandlePutRequest(int socketIndex, const char* path);
void HandleHeadRequest(int socketIndex, const char* path);
void HandleTraceRequest(int socketIndex, const char* path);
void ConstructHttpResponse(int index, int statusCode, const char* statusMessage,const char* responseBody, bool isDynamicallyAllocated, bool isHeadersOnly, const char* lang = DEFAULT_LANGUAGE);
const char* GetLangQueryParam(const char* path);
int GetIdQueryParam(const char* path);
void LoadDLL();
void PerformExit();
SOCKET GetListenSocket();
void BindServerAddressToListenSocket(SOCKET& listenSocket, sockaddr_in& serverService);
void ListenForClients(SOCKET& listenSocket);
char* GenerateOptionsMenu();


