#include "include/xygsvc.h"
#include "include/global.h"
using namespace xyg;

msg_svc_getpersonalinfo::msg_svc_getpersonalinfo() {

}
msg_svc_getpersonalinfo::msg_svc_getpersonalinfo(string sid, string id, string cseq, string body) {
    init(sid,id,cseq,body);
}

PRStatus msg_svc_getpersonalinfo::init(string sid, string id, string cseq, string body) {
    _startline.SetMethod("S");
    _startline.SetUri(STARTLINE_DOMAIN);
    _startline.SetVersion(STARTLINE_VERSION);
    _header.append(SIPHeaderLine("F",sid));
    _header.append(SIPHeaderLine("N","GetPersonalInfo"));
    _header.append(SIPHeaderLine("I", id));
    _header.append(SIPHeaderLine("Q", cseq));
    SetBody(body);
    return PR_SUCCESS;
}
PRStatus msg_svc_getpersonalinfo::SetSid(string sid) {
    return _header.modify("F",sid);
}
PRStatus msg_svc_getpersonalinfo::SetID(string id) {
    return _header.modify("I",id);
}
PRStatus msg_svc_getpersonalinfo::SetCSeq(string cseq) {
    return _header.modify("Q",cseq);
}

