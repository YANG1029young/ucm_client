#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_TRANSFERSTARTRETURNTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_TRANSFERSTARTRETURNTYPE_H

#include "impl_type_transferidtype.h"
#include "impl_type_transferstartsuccesstype.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

struct TransferStartReturnType
{	
    ::ara::ucm::pkgmgr::TransferIdType TransferId;
::ara::ucm::pkgmgr::TransferStartSuccessType TransferStartSuccess;

    using IsEnumerableTag = void;
  
    template <typename T>
    void Serialize(T* serializer) const
    {
        serializer->Serialize(TransferId);
        serializer->Serialize(TransferStartSuccess);

    }

    template <typename T>
    bool Deserialize(T* deserializer)
    {
        if (!deserializer->Deserialize(TransferId))
        {
            return false;
        }
        if (!deserializer->Deserialize(TransferStartSuccess))
        {
            return false;
        }

        return true;
	}
};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_TRANSFERSTARTRETURNTYPE_H

