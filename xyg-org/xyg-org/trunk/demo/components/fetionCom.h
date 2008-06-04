#include "nsISupports.h"
#include "IFetionCom.h"
#include "nsCOMPtr.h"
/* starting interface:    IFetionCom */

#define IFETIONCOM_CID  {0x4fdf2881, 0xf1a5, 0x4832, { 0xa2, 0xad, 0xff, 0x82, 0xdb, 0x3e, 0x31, 0x41 }}
#define IFETIONCOM_CLASSNAME "Fetion Protocol Manager"
#define IFETIONCOM_CONTRACTID "@mozilla.org/fetion/fetionCom;1"


/* Header file */
class fetionCom : public IFetionCom
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFETIONCOM

  nsCOMPtr < IJSCallback > callback ; 
  fetionCom();
  ~fetionCom();
private:

protected:
  /* additional members */
};

