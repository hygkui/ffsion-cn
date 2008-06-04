#ifndef SEND_H_
#define SEND_H_
#include "network.h"
#include <prthread.h>
#include <prio.h>

PRStatus Send(const void *buffer, int length);
#endif /*SEND_H_*/
