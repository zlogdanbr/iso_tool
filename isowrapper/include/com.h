#ifndef MYCOMM_SOCKETS
#define MYCOMM_SOCKETS

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "isowrapper.h"


class Comm final{
public:
    explicit Comm( const std::string& IPHost, const int& port );
    int send( const DL_UINT8* outmsg, DL_UINT16& no, DL_UINT8* inmsg , DL_UINT16& ni );
private:
    Comm( const Comm& ) = delete;
    Comm operator=( const Comm& ) = delete;  
    struct sockaddr_in serv_addr;
    struct hostent *server{nullptr};
    std::string IPHost;
    int port;

};

#endif
