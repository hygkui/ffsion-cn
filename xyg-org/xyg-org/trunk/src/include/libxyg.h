#ifndef LIBXYG_H_
#define LIBXYG_H_

#include <prio.h>
#include <string>
#include "trans.h"
#include "recv.h"
#include "network.h"
using namespace std;
using namespace xyg;

/* The header file for external use 
 */

namespace xyg {

class ServiceConnector {
    public:
    ServiceConnector();
    
    virtual PRStatus GetResult() = 0;
    int SendCommand(Command &cmd);
    int GetReturncode();
    string GetReturnstring();
    
    PRStatus SetReturncode(int retcode);
    PRStatus SetReturnstring(string retstr);
    
    TransactionQueue& GetTransQ();
    
    private:
    int _ticketid;
    int _returncode;
    string _returnstring;
    TransactionQueue _trans;
};

class Service {
    public:
    Service();
    ~Service();
    
    PRStatus init(ServiceConnector *srvconn);
    PRStatus cleanup();

    private:
    RecvThread _recvthread;
};


}

#endif /*LIBXYG_H_*/
