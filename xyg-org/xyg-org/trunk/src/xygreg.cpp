#include <string>
#include <iostream>
#include <prio.h>
#include "include/xygreg.h"
#include "include/global.h"
#include "include/utils.h"

using namespace std;
using namespace sip;
using namespace xyg;


/* Implements for Fetion Message: REG-1
 * (1) Message Primitive

R Domain SIP-C/2.0
F: SID
I: call-id-value
Q: cseq-value R
L: content-length-value

<args>
    <device type =“client-type-value” version=“config-version-value” client-version=“client-version-value” />
    <caps value=“client-capablity-list” />
    <events value=“accept-event-list” />
    <oem-tag value=”oem-tag-value” />
    <user-info attributes=“require-list“/>
    <presence>
      <basic value=“basic-presence-value“ desc=“basic-presence-desc“/>
    </presence>
</args>

 * (2) Purpose
 *     The clients initate a login request. 
 *     The server will return the login method as response(REG-RSP-1). 
 */

msg_reg_1::msg_reg_1() {
}

msg_reg_1::msg_reg_1(const string sid, const int id, const int cseq, const string body) {
    init(sid, id, cseq, body);
}

PRStatus msg_reg_1::init(const string sid, const int id, const int cseq, const string body){
    _startline.SetMethod("R");
    _startline.SetUri(STARTLINE_DOMAIN);
    _startline.SetVersion(STARTLINE_VERSION);
    _header.append(SIPHeaderLine("F",sid));
    _header.append(SIPHeaderLine("I",toString(id)));
    _header.append(SIPHeaderLine("Q",toString(cseq)+" R"));
    SetBody(body);
    return PR_SUCCESS;
}



PRStatus msg_reg_1::SetSID(string sid) {
	return _header.modify("F",sid);
}
PRStatus msg_reg_1::SetID(int id) {
    return _header.modify("I", toString(id));
}
PRStatus msg_reg_1::SetCSeq(int cseq) {
    return _header.modify("Q",toString(cseq)+" R");
}


/* Implements for Fetion Message: REG-RSP-1
 * (Response of REG-1)
 * 
 * (1) Message Primitive

SIP-C/2.0 401 Unauthorized
W: Digest algorithm="MD5-sess", nonce = "12345678901234567890123456789012"
I: 1
Q: 1 R


 * (2) Purpose
 *     This message is the response of REG-1.
 *     Contains the digest algorithm specification and an important value
 * "nonce" which will be used in authentication progress.
 */
msg_reg_rsp_1::msg_reg_rsp_1() {
}

msg_reg_rsp_1::msg_reg_rsp_1(const void* buffer) {
    init(buffer);
}



string msg_reg_rsp_1::GetNonce() {
    int i = 0, j = 0, k = 0;
    string str = _header.GetValue("W");
    i = str.find("nonce", 0);
    j = str.find("\"", i+1);
    k = str.find("\"", j+1);
    return str.substr(j+1, k-j-1);
}

int msg_reg_rsp_1::GetID() {
    return toInteger(_header.GetValue("I"));
}

int msg_reg_rsp_1::GetCSeq() {
	return toInteger(_header.GetValue("Q"));
}



/* Implements for Fetion Message: REG-2
 * (1) Message Primitive

R Domain SIP-C/2.0
F: SID
A: Digest response="rsp-value", cnonce="cn-value"
I: call-id-value
Q: cseq-value R
L: body-length

<args>
    <device type =“PC” version=“config-version-value” client-version=“client-version-value” />
    <caps value=“simple-im;im-session;temp-group” />
    <events value=“contact;permission;system-message />
    <oem-tag value=”oem-tag-value” />
    <user-info attributes=“require-list“/>
    <presence>
      <basic value=“basic-presence-value“ desc=“basic-presence-desc“/>
    </presence>
</args>

 * (2) Purpose
 *     The client send this mesage as authentication information. 
 */ 
msg_reg_2::msg_reg_2() {
}

msg_reg_2::msg_reg_2(const string sid,\
                     const int id,    \
                     const int cseq,  \
                     const string response, \
                     const string cnonce,   \
                     const string body) {
    init(sid,id,cseq,response,cnonce,body);
}

PRStatus msg_reg_2::init( const string sid, \
		       const int id, \
		       const int cseq, \
		       const string response,\
		       const string cnonce ,\
		       const string body) {
    _startline.SetMethod("R");
    _startline.SetUri(STARTLINE_DOMAIN);
    _startline.SetVersion(STARTLINE_VERSION);
    _header.append(SIPHeaderLine("F", sid));
    _header.append(SIPHeaderLine("I", toString(id)));
    _header.append(SIPHeaderLine("Q", toString(cseq)+" R"));
    _header.append(SIPHeaderLine("A", "\
Digest response=\"" + response + "\", \
cnonce=\""+ cnonce + "\"" ));

    _header.append(SIPHeaderLine("L", body.size()));
    SetBody(body);
    return PR_SUCCESS;
}

PRStatus msg_reg_2::SetSID(string sid) {
    return _header.modify("F", sid);
}

PRStatus msg_reg_2::SetID(int id) {
    return _header.modify("I", id);
}

PRStatus msg_reg_2::SetCSeq(int cseq) {
    return _header.modify("Q", toString(cseq)+" R"); 
}

PRStatus msg_reg_2::SetResponse(string response) {
    string str = _header.GetValue("A");
    string ret("Digest response=\"");
    string tmp;
    ret += response + "\" ,";
    
    unsigned int i = 0;
    while( ( i = str.find(",", 0) ) != string::npos ) {
    	tmp = str.substr(0,i);
    	cerr <<tmp <<endl;
        if(tmp.find("Digest",0) == string::npos) {
            ret += tmp;
            ret += ",";
        }
        str.erase(0, i+1);
    }
    if(str.find("Digest",0) == string::npos) {
        ret += str;
    }

    return _header.modify("A", ret); 
}

PRStatus msg_reg_2::SetCnonce(string cnonce) {
    string str = _header.GetValue("A");
    string ret;
    string tmp;
        
    unsigned int i = 0;
    while( ( i = str.find(",", 0) ) != string::npos ) {
    	tmp = str.substr(0,i);
    	cerr <<tmp <<endl;
        if(tmp.find("cnonce",0) == string::npos) {
            ret += tmp;
            ret += ", ";
        }
        str.erase(0, i+1);
    }
    if(str.find("cnonce",0) == string::npos) {
        ret += str;
        ret += ", ";
    }
    
    ret += "cnonce = \"" + cnonce + "\""; 

    return _header.modify("A", ret);
}


/* Implements of Fetion Message: REG-RSP-2
 * (Response of REG-2)
 * 
 * (1) Message Primitive
SIP-C/2.0 200 Ok
X: expires-time
I: call-id-value
Q: cseq-value R
L: content-length-value

<results>
    <client public-ip=”public-ip-address” >
         <custom-config version=”version-value”>terminal-relavant-configuration</custom-config>
    </client>
    <user-info personal-info-version=”personal-info-version-value”
          contact-version=”contact-version-value”
          permission-version=”permission-version-value”
    />
    <presence result=”result-code”/>
</results>

 *
 * (2) Purpose:
 *     This is the response of REG-2, "expire-time" is useful.
 */

msg_reg_rsp_2::msg_reg_rsp_2() {

}
msg_reg_rsp_2::msg_reg_rsp_2(const void* buffer) {
    init(buffer);
}


string msg_reg_rsp_2::GetExpiresTime() {
    return _header.GetValue("X");
}
int msg_reg_rsp_2::GetID() {
    return toInteger(_header.GetValue("I"));
}
int msg_reg_rsp_2::GetCSeq() {
	return toInteger(_header.GetValue("Q"));
}

/* Implements of Fetion Message: REG-3
 * 
 * (1) Message Primitive

R Domain SIP-C/2.0
F: SID
I: call-id-value
Q: cseq-value R

 * (2) Purpose
 *     This message is for keeping the online status.
 */
msg_reg_3::msg_reg_3() {

}
msg_reg_3::msg_reg_3(const string sid, const int id, const int cseq) {
    init(sid,id,cseq);
}

PRStatus msg_reg_3::init(const string sid, const int id, const int cseq) {
    _startline.SetMethod("R");
    _startline.SetUri(STARTLINE_DOMAIN);
    _startline.SetVersion(STARTLINE_VERSION);
    _header.append(SIPHeaderLine("F",sid));
    _header.append(SIPHeaderLine("I",toString(id)));
    _header.append(SIPHeaderLine("Q", toString(cseq)+" R" ));
    return PR_SUCCESS;
}

PRStatus msg_reg_3::SetSID(string sid) {
    return _header.modify("F", sid);
}
PRStatus msg_reg_3::SetID(int id) {
    return _header.modify("I", id);
}
PRStatus msg_reg_3::SetCSeq(int cseq) {
    return _header.modify("Q", cseq);
}

/* Implements of Fetion Message: REG-RSP-3
 * (Response of REG-3)
 * 
 * (1) Message Primitive
SIP-C/2.0 200 Ok
X: expires-time
I: call-id-value
Q: cseq-value R

 * (2) Purpose
 *     This is the response message of REG-3, contains expire-time.
 */

msg_reg_rsp_3::msg_reg_rsp_3() {
	
}

msg_reg_rsp_3::msg_reg_rsp_3(const void* buffer) {
    init(buffer);
}


string msg_reg_rsp_3::GetExpiresTime() {
    return _header.GetValue("X");
}
int msg_reg_rsp_3::GetID() {
    return toInteger(_header.GetValue("I"));
}
int msg_reg_rsp_3::GetCSeq() {
    return toInteger(_header.GetValue("Q"));
}


/* Implements of Fetion Message: UNREG-1
 * 
 * (1) Message Primitive
R Domain SIP-C/2.0
F: SID
X: 0
I: call-id-value
Q: cseq-value R

    msg_unreg_1();
    msg_unreg_1(string id, string cseq);
    
    PRStatus SetID(string id);
    PRStatus SetCSeq(string cseq);

 * (2) Purpose
 *     This message is for logout.
 */

msg_unreg_1::msg_unreg_1() {

}

msg_unreg_1::msg_unreg_1(string sid, int id, int cseq) {
    init(sid, id, cseq);
}

PRStatus msg_unreg_1::init(string sid, int id, int cseq) {
    _startline.SetMethod("R");
    _startline.SetUri(STARTLINE_DOMAIN);
    _startline.SetVersion(STARTLINE_VERSION);
    _header.append(SIPHeaderLine("X", "0"));
    _header.append(SIPHeaderLine("F", sid));
    _header.append(SIPHeaderLine("I", toString(id)));
    _header.append(SIPHeaderLine("Q", toString(cseq)+" R"));
    return PR_SUCCESS;
}

PRStatus msg_unreg_1::SetSID(string sid) {
    return _header.modify("F", sid);
}
PRStatus msg_unreg_1::SetID(int id) {
    return _header.modify("I", toString(id));
}
PRStatus msg_unreg_1::SetCSeq(int cseq) {
    return _header.modify("Q", toString(cseq)+" R");
}

/* Implements of Fetion Message: UNREG-RSP-1
 * (Response of UNREG-1)
 * 
 * (1) Message Primitive
SIP-C/2.0 200 Ok
X: 0
I: call-id-value
Q: cseq-value R

 * (2) Purpose
 *     This is the response of UNREG-1. 
 */
 
msg_unreg_rsp_1::msg_unreg_rsp_1() {
}
msg_unreg_rsp_1::msg_unreg_rsp_1(void *buffer) {
    init(buffer);
}

int msg_unreg_rsp_1::GetID() {
    return toInteger(_header.GetValue("I"));
}
int msg_unreg_rsp_1::GetCSeq() {
    return toInteger(_header.GetValue("Q"));
}

