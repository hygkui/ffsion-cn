#ifndef NETWORK_H_
#define NETWORK_H_

#include <string>
using namespace std;
#include <prio.h>
#include <prnetdb.h>


#include <prtypes.h>

class TCPConnection {
    private:
    string _hostname;
    int _port;

    PRNetAddr _addr;
    PRHostEnt _he;
    PRFileDesc* _sockfd;
    
    PRBool _available;
    
    public:
    TCPConnection();
    TCPConnection(string hostname, int port);
    PRStatus init(string hostname, int port);
    ~TCPConnection();
    PRStatus Connect();
    PRStatus Send(const void* buf, PRInt32 amount);
    PRInt32 Receive(void* buf);
    PRStatus Disconnect();
};


#endif /*NETWORK_H_*/
