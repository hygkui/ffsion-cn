#include "include/network.h"
#include <prio.h>
#include <prnetdb.h>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

#include <cstdio>

TCPConnection::TCPConnection() {
    _hostname = "";
    _port = 0;
    _available = PR_FALSE;
}

TCPConnection::TCPConnection(string hostname, int port) {
    init(hostname, port);
}

PRStatus TCPConnection::init(string hostname, int port) {
    _hostname = hostname;
    _port = port;

    
    char buf[PR_NETDB_BUF_SIZE];
    PRIntn index = 0;

    _available = PR_FALSE;

    /* resolve */
    if (PR_GetHostByName(_hostname.c_str(), buf, sizeof(buf), &_he) == PR_FAILURE) {
        #ifdef DEBUG
        cerr <<"PR_GetHostByName failed" <<endl;
        #endif
        return PR_FAILURE;
    }
    /* get netaddr */
    index = PR_EnumerateHostEnt(index, &_he,0, &_addr);
    if (index == -1) {
        #ifdef DEBUG
        cerr <<"PR_EnumerateHostEnt failed" <<endl;
        #endif
        return PR_FAILURE;
    }
    
    /* assign the port */
    PR_InitializeNetAddr(PR_IpAddrNull, _port, &_addr);

    /* init TCP socket */
    _sockfd = PR_NewTCPSocket();
    if (_sockfd == NULL) {
        #ifdef DEBUG
        cerr <<"Unable to create a new TCP socket." <<endl;
        #endif
        return PR_FAILURE;
    }

    _available = PR_TRUE;
    
    return PR_SUCCESS;
}

TCPConnection::~TCPConnection() {
    Disconnect();
}

PRStatus TCPConnection::Connect() {

    if (_available == PR_FALSE) {
        return PR_FAILURE;
    }

    if (PR_Connect(_sockfd, &_addr, PR_INTERVAL_NO_TIMEOUT) == PR_FAILURE) {
        cerr <<"Unable to connect." <<endl;
        return PR_FAILURE;
    }

    return PR_SUCCESS;
}

PRStatus TCPConnection::Send(const void* buf, PRInt32 amount) {
    PRInt32 ret;
    ret = PR_Send(_sockfd, buf, amount, 0, PR_INTERVAL_NO_TIMEOUT);
    if (ret == -1) {
        return PR_FAILURE;
    }
    /* must be (ret == amount) since this is a blocking socket */
    return PR_SUCCESS;
}

PRInt32 TCPConnection::Receive(void *buf) {
    return PR_Recv(_sockfd, buf, 1024, 0, PR_INTERVAL_NO_TIMEOUT);
}

PRStatus TCPConnection::Disconnect() {
    _available = PR_FALSE;
    return PR_Shutdown(_sockfd, PR_SHUTDOWN_BOTH);
}
