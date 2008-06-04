#ifndef RECV_H_
#define RECV_H_

#include "network.h"
#include <prthread.h>
#include <prio.h>

class RecvThread {
    public:
    RecvThread();
    
    void run();
    
    private:
    PRThread* _thread;
};

#endif /*RECV_H_*/
