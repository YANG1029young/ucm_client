#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_PROCESSSWPACKAGERETURNTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_PROCESSSWPACKAGERETURNTYPE_H

#include "impl_type_processresulttype.h"
#include "impl_type_transferidtype.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

struct ProcessSwPackageReturnType
{	
    ::ara::ucm::pkgmgr::ProcessResultType result;
::ara::ucm::pkgmgr::TransferIdType transferId;

    using IsEnumerableTag = void;
  
    template <typename T>
    void Serialize(T* serializer) const
    {
        serializer->Serialize(result);
        serializer->Serialize(transferId);

    }

    template <typename T>
    bool Deserialize(T* deserializer)
    {
        if (!deserializer->Deserialize(result))
        {
            return false;
        }
        if (!deserializer->Deserialize(transferId))
        {
            return false;
        }

        return true;
	}
};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_PROCESSSWPACKAGERETURNTYPE_H

