#include "nsIGenericFactory.h"
#include "fetionCom.h"


NS_GENERIC_FACTORY_CONSTRUCTOR(fetionCom)

    static nsModuleComponentInfo components[]=
{
    {
        IFETIONCOM_CLASSNAME,
        IFETIONCOM_CID,
        IFETIONCOM_CONTRACTID,
        fetionComConstructor,
    }
};

NS_IMPL_NSGETMODULE("fetionComModule",components)
