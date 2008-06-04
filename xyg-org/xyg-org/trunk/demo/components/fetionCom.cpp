#include <iostream>
#include "fetionCom.h"
#include "libxyg.h" //use jinpu's lib xyg.
using namespace std;
using namespace xyg;

// inherit form the virtual base ServiceConnector.
class myServiceConnector : public ServiceConnector,
                        public fetionCom
{
    public:
    PRStatus GetResult(){
        PRBool ret=true;
        this->callback->Call(GetReturnstring().c_str(),&ret);
        cout<<GetReturnstring();
        return PR_SUCCESS;
    }

};

/* Implementation file */
NS_IMPL_ISUPPORTS1(fetionCom, IFetionCom)

fetionCom::fetionCom()
{
    this->callback = NULL;
  /* member initializers and constructor code */
}

fetionCom::~fetionCom()
{
  /* destructor code */
}

/* long Add (in long a, in long b); */
NS_IMETHODIMP fetionCom::Add(PRInt32 a, PRInt32 b, PRInt32 *rtn)
{
    *rtn = a + b;
    return NS_OK;
}


NS_IMETHODIMP fetionCom::SetCallback(IJSCallback *aCallback ) {
    this->callback = aCallback; // need check.
    return NS_OK;
}

NS_IMETHODIMP fetionCom::TestCallback(IJSCallback *aCallback)
{
	PRBool ret =true ;
    this->callback = aCallback ;
    this->callback->Call("hello", &ret);

    return NS_OK;
}

/* long CloseSocket (in long c); */
NS_IMETHODIMP fetionCom::CreateSocket(PRInt32 *rtn)
{
	//*rtn= createSocket();
    *rtn=0;
    return NS_OK;
}

/* void login (in string FetionNo, in string FetionPswd); */
NS_IMETHODIMP fetionCom::Login(const char *FetionNo, const char *FetionPswd , PRInt32 *rtn )
{
    
    char cmd_args[256];
    memset(cmd_args,0,256);
    strcat(cmd_args,FetionNo);
    strcat(cmd_args,":");
    strcat(cmd_args,FetionPswd);

    Service si;
    Command c(1,cmd_args);
    myServiceConnector sc;
    sc.SetCallback(this->callback);
    si.init(sc);
    sc.SendCommand(c); //send cmd ,then wait for the login process. ???? need another thread ?
    si.cleanup();
    
    *rtn = 0;

    return NS_OK;
}

/* long SendAMsg (in long c, in string from, in string to, in string msg); */
NS_IMETHODIMP fetionCom::SendAMsg(PRInt32 c, const char *from, const char *to, const char *msg, PRInt32 *rtn)
{
	//*rtn = sendAMsg((int)c, (char *)from, (char *)to, (char *)msg );
    *rtn=0;
    return NS_OK;
}
NS_IMETHODIMP fetionCom::GetMsg( PRInt32 c , char **rtn)
{
	//*rtn = getMsg(c);
    *rtn="";
    return NS_OK;
}
/* long CloseSocket (in long c); */
NS_IMETHODIMP fetionCom::CloseSocket(PRInt32 c, PRInt32 *rtn)
{
	//*rtn= closeSocket(c);
    * rtn = 0;
    return NS_OK;
}
NS_IMETHODIMP fetionCom::GetUserInfo(PRInt32 c , const char *FetionNo, char **info)
{
		//*info = getUserInfo((int)c ,(char *)FetionNo);
        *info="";
	    return NS_OK;
}
NS_IMETHODIMP fetionCom::TestProxyThread(PRInt32 *rtn) /*not implement yet .*/
{
	*rtn= 0;
    return NS_OK;
}

