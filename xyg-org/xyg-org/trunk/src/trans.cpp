#include "include/trans.h"
using namespace xyg;

Command::Command() {
}

Command::Command(int transtype, string targetsid, string args) {
    SetType(transtype);
    SetArgs(args);
    SetTargetsid(targetsid);
}


PRStatus Command::SetType(int type) {
    _type = type;
    return PR_SUCCESS;
}
PRStatus Command::SetArgs(string args) {
    _args = args;
    return PR_SUCCESS;
}

PRStatus Command::SetTargetsid(string targetsid) {
    _targetsid = targetsid;
    return PR_SUCCESS;
}

int Command::GetType() {
    return _type;
}
string Command::GetArgs() {
    return _args;
}

string Command::GetTargetsid() {
    return _targetsid;
}



TransactionHandler::TransactionHandler() {
    
}

TransactionHandler::TransactionHandler(int type, void(*handler)(Transaction&)) {
    _type = type;
    _handler = handler;
}

int TransactionHandler::GetType() {
    return _type;
}

void TransactionHandler::Run(Transaction &trans) {
    _handler(trans);
}

TransactionAgent::TransactionAgent() {

}
    
PRStatus TransactionAgent::Add(TransactionHandler handler) {
    _agent.push_back(handler);
    return PR_SUCCESS;
}

void TransactionAgent::Run(Transaction &trans) {
    int type = trans.GetType();
    vector<TransactionHandler>::iterator it;
    for( it =_agent.begin(); it < _agent.end(); it++) {
        if((*it).GetType() == type) {
            (*it).Run(trans);
            return;
        }
    }
    return;
}

Transaction::Transaction() {
    _id = 0;
    _seq = 0;
    _status = 0;
    
}
Transaction::Transaction(Command& cmd) {
    _id = 0;
    _seq = 1;
    _status = 1;
    _cmd = cmd;
}

PRStatus Transaction::IncreaseSeq() {
    _seq++;
    return PR_SUCCESS;
}


PRStatus Transaction::SetID(int id) {
    _id = id;
    return PR_SUCCESS;
}

PRStatus Transaction::SetCommand(Command &cmd) {
    _cmd = cmd;
    return PR_SUCCESS;
}

PRStatus Transaction::SetTicketid(int ticketid) {
    _ticketid = ticketid;
    return PR_SUCCESS;
}

PRStatus Transaction::SetStatus(int status) {
    _status = status;
    return PR_SUCCESS;
}

int Transaction::GetType() {
    return _cmd.GetType();
}

int Transaction::GetStatus() {
    return _status;
}


int Transaction::GetID() {
    return _id;
}

int Transaction::GetSeq() {
    return _seq;
}

int Transaction::GetTicketid() {
    return _ticketid;
}

string Transaction::GetTargetsid() {
    return _cmd.GetTargetsid();
}

string Transaction::GetArgs() {
    return _cmd.GetArgs();
}

TransactionQueue::TransactionQueue() {
    init();
}

TransactionQueue::TransactionQueue(TransactionAgent &agent) {
    init(agent);
}
    
PRStatus TransactionQueue::init() {
    /* clear the transaction queue */
    _transq.clear();

    /* reset the _nextid */
    _nextid = 0;
    
    /* reset the _nextticket */
    _nextticket = 0;

    /* init the lock */
    _lock = PR_NewLock();
    
    return PR_SUCCESS;
}

PRStatus TransactionQueue::init(TransactionAgent &agent) {
    /* clear the transaction queue */
    _transq.clear();

    /* reset the _nextid */
    _nextid = 0;
    
    /* reset the _nextticket */
    _nextticket = 0;

    /* init the lock */
    _lock = PR_NewLock();
    
    /* init the transaction agent */
    SetTransactionAgent(agent);
    
    return PR_SUCCESS;
}

PRStatus TransactionQueue::SetTransactionAgent(TransactionAgent &agent) {
    _agent = agent;
    return PR_SUCCESS;
}

int TransactionQueue::Add(Transaction trans) {
    trans.SetID(GetNextID());
    _transq.push_back(trans);
    return trans.GetID();
}

int TransactionQueue::GetNextID() {
    _nextid++;
    return _nextid;
}
int TransactionQueue::GetNextTicketID() {
    _nextticket++;
    return _nextticket;
}

int TransactionQueue::AddTicket(Command &cmd) {
    string target = cmd.GetTargetsid();
    int type = cmd.GetType();
    int ticket = GetNextTicketID();
    string targetsid = cmd.GetTargetsid();
    
    vector<Transaction>::iterator it;
    
    /* if the command object is register command */
    if(type == FX_REGISTER) {
        /* first find the register transaction */
        for( it = _transq.begin(); it < _transq.end(); it++) {
            if((*it).GetType() == 0 ) {
            /* We have found the register transaction
             * Update the command object and do the transaction
             */
                (*it).SetCommand(cmd);
                (*it).SetTicketid(ticket);
                DoTransaction((*it).GetID());
                return ticket;
            }
        }
        
        /* not existing a register transaction 
         * add a new transaction and do it
         */
        Transaction tmp(cmd);
        tmp.SetTicketid(ticket);
        DoTransaction(Add(Transaction(cmd)));
        return ticket;
        
    } else {
    /* not a register command */
    /* find if there exists a transaction 
     * whose targetid and type is the same 
     * as the command. 
     */
        for( it = _transq.begin(); it < _transq.end(); it++) {
            if( ((*it).GetTargetsid().compare(targetsid) == 0) && \
                ((*it).GetType() == cmd.GetType())                ) {
            /* We have found the specific transaction
             * Update the command object and do the transaction
             */
                (*it).SetCommand(cmd);
                (*it).SetTicketid(ticket);
                DoTransaction((*it).GetID());
                return ticket;
            }
        }
        Transaction tmp(cmd);
        tmp.SetTicketid(ticket);
        DoTransaction(Add(Transaction(cmd)));
        return ticket;
    }

}

Transaction TransactionQueue::GetTransaction(int transid) {
    int it;
    for( it = 0; it < _transq.size(); it++) {
        if(_transq[it].GetID() == transid ) {
            return _transq[it];
        }
    }
    
    Transaction t;
    t.SetID(-1);
    return t;

}

PRStatus TransactionQueue::Remove(int transid) {
    vector<Transaction>::iterator it;
    for( it = _transq.begin(); it < _transq.end(); it++) {
        if( (*it).GetID() == transid ) {
            _transq.erase(it);
            return PR_SUCCESS;
        }
    }
    return PR_FAILURE;
}


void TransactionQueue::Lock() {
    PR_Lock(_lock);
}
void TransactionQueue::Unlock() {
    PR_Unlock(_lock);
}

PRStatus TransactionQueue::SetCommand(int transid, Command cmd) {
    vector<Transaction>::iterator it;
    for( it = _transq.begin(); it < _transq.end(); it++) {
        if( (*it).GetID() == transid ) {
            (*it).SetCommand(cmd);
            return PR_SUCCESS;
        }
    }
    return PR_FAILURE;
}

PRStatus TransactionQueue::DoTransaction(int transid) {
    vector<Transaction>::iterator it;
    for( it = _transq.begin(); it < _transq.end(); it++) {
        if( (*it).GetID() == transid ) {
            _agent.Run((*it));
            return PR_SUCCESS;
        }
    }
    return PR_FAILURE;
}
