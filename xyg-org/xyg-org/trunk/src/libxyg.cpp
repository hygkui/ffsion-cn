#include "include/libxyg.h"
#include "include/global.h"
#include "include/xygreg.h"
#include "include/network.h"
#include "include/utils.h"
#include "include/fetion.h"
#include <prinit.h>
#include <prio.h>
#include <string>
#include <cstdlib>
using namespace std;
using namespace xyg;

ServiceConnector *SRVCONN;
TCPConnection TCPCONN;



ServiceConnector::ServiceConnector() {
    TransactionAgent agent;
    
    agent.Add(TransactionHandler(FX_REGISTER, fx_register));
    _trans.SetTransactionAgent(agent);
}

int ServiceConnector::SendCommand(Command &cmd) {
    _trans.Lock();
    int ticketid =  _trans.AddTicket(cmd);
    _trans.Unlock();

    return ticketid;
}

int ServiceConnector::GetReturncode() {
    return _returncode;
}

string ServiceConnector::GetReturnstring() {
    return _returnstring;
}

TransactionQueue& ServiceConnector::GetTransQ() {
    return _trans;
}

PRStatus ServiceConnector::SetReturncode(int retcode) {
    _returncode = retcode;
    return PR_SUCCESS;
}

PRStatus ServiceConnector::SetReturnstring(string retstr) {
    _returnstring = retstr;
    return PR_SUCCESS;
}


Service::Service() {
    SRVCONN = NULL;
}

Service::~Service() {
    cleanup();
}

PRStatus Service::init(ServiceConnector *connector) {
    PR_STDIO_INIT();
    /* init the nspr threads environment */
    PR_Init(PR_USER_THREAD, PR_PRIORITY_HIGH, 0);
    
    /* init the service connector */
    SRVCONN = connector;
    
    /* init the network connection */
    TCPCONN.init(SERVER_HOST, SERVER_PORT);
    TCPCONN.Connect();
    
    /* spawn the recv thread */
    _recvthread.run();
    
    return PR_SUCCESS;
}

PRStatus Service::cleanup() {
    PR_Cleanup();
    return PR_SUCCESS;
}

