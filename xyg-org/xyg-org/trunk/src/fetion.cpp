#include "include/fetion.h"
#include "include/xyg.h"
#include "include/send.h"
#include "include/libxyg.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using namespace xyg;

extern ServiceConnector* SRVCONN;

void fx_register(Transaction &trans) {
    static string username("");
    static string password("");
    static string nonce("");
    int cur_state = trans.GetStatus();
    if(cur_state == 1) {
        string args = trans.GetArgs();
        int p1 = args.find(";", 0);
        int p2 = args.find(";", p1+1);
        string cmd = args.substr(0, p1);
        username = args.substr(p1+1, p2-p1-1);
        password = args.substr(p2+1, string::npos);
        
        string body1("\
<args>\
<device type=\"PC\" version=\"5\" client-version=\"2.3.0210\" />\
<caps value=\"simple-im;im-session;temp-group\" />\
<events value=\"contact;permission;system-message\" />\
<user-info attributes=\"all\" />\
<presence>\
<basic value=\"0\" desc=\"\" />\
</presence>\
</args>");
        
        msg_reg_1 msg(username, trans.GetID(), trans.GetSeq(), body1);
        
        if(Send(msg.content().c_str(), msg.content().size()) == PR_SUCCESS) {
            trans.SetStatus(cur_state+1);
        }
    }
    else if(cur_state == 2) {
        /*string body1("\
<args>\
<device type=\"PC\" version=\"5\" client-version=\"2.3.0210\" />\
<caps value=\"simple-im;im-session;temp-group\" />\
<events value=\"contact;permission;system-message\" />\
<user-info attributes=\"all\" />\
<presence>\
<basic value=\"0\" desc=\"\" />\
</presence>\
</args>");*/
        
        cout <<trans.GetStatus() <<endl;
        cout <<trans.GetArgs() <<endl;
    }
    else if(cur_state == 3) {
            
    }
    else if(cur_state == 4) {
            
    }
    else if(cur_state == 5) {
        
    }
    else if(cur_state == 0xff) {
        
    }
    else {
        
    }
}

void fx_getcontactlist(Transaction &trans) {
    
}
