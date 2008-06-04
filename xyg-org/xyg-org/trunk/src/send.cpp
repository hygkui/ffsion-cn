#include "include/send.h"
#include "include/global.h"
#include <cstdlib>

extern TCPConnection TCPCONN;

PRStatus Send(const void *buffer, int length) {
    return TCPCONN.Send(buffer, length);
}
