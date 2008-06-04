#ifndef TRANS_H_
#define TRANS_H_

#include "global.h"
#include <vector>
#include <prlock.h>
#include <prio.h>
#include <string>
using namespace std;


namespace xyg {

class Command {
    private:
    int _type;
    string _args;
    string _targetsid;

    public:
    Command();
    Command(int transtype, string targetsid, string args);
    PRStatus SetType(int transtype);
    PRStatus SetArgs(string args);
    PRStatus SetTargetsid(string targetsid);
    int GetType();
    string GetArgs();
    string GetTargetsid();
};

class Transaction {
    public:
    Transaction();
    Transaction(Command& cmd);
    
    PRStatus SetID(int id);
    PRStatus SetCommand(Command &cmd);
    PRStatus SetTicketid(int ticket);
    PRStatus SetStatus(int status);

    int GetType();
    int GetStatus();
    int GetID();
    int GetSeq();
    int GetTicketid();
    string GetTargetsid();
    string GetArgs();
    
    private:
    PRStatus IncreaseSeq();
    
    string _targetsid;
    Command _cmd;
    int _id;
    int _seq;
    int _status;
    int _ticketid;

};

class TransactionHandler {
    public:
    TransactionHandler();
    TransactionHandler(int type, void(*handler)(Transaction&));
    
    int GetType();
    void Run(Transaction &trans);
    
    private:
    int _type;
    void (*_handler)(Transaction &);
    
};

class TransactionAgent {
    public:
    TransactionAgent();
    
    PRStatus Add(TransactionHandler handler);
    void Run(Transaction &trans);
    
    private:
    vector<TransactionHandler> _agent;
};

class TransactionQueue {
    public:
    TransactionQueue();
    TransactionQueue(TransactionAgent &agent);
    PRStatus init();
    PRStatus init(TransactionAgent &agent);
    PRStatus SetTransactionAgent(TransactionAgent &agent);
    int AddTicket(Command &cmd);
    Transaction GetTransaction(int transid);
    PRStatus SetCommand(int transid, Command cmd);
    PRStatus DoTransaction(int transid);
    void Lock();
    void Unlock();
    

    private:
    int Add(Transaction trans);    
    PRStatus Remove(int transid);
    int GetNextID();
    int GetNextTicketID();
    vector<Transaction> _transq;
    

    
    PRLock *_lock;
    int _nextid;
    int _nextticket;
    TransactionAgent _agent;
    
};

}


#endif /*TRANS_H_*/
