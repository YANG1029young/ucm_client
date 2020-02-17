#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_SWPACKAGEINFOTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_SWPACKAGEINFOTYPE_H

#include "impl_type_swinfoname.h"
#include "impl_type_string.h"
#include "impl_type_string.h"
#include "impl_type_transferidtype.h"
#include "impl_type_requesttype.h"
#include "impl_type_packagetype.h"
#include "impl_type_swpackageinfostatetype.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

struct SwPackageInfoType
{	
    ::ara::ucm::pkgmgr::SwInfoName Name;
::String Version;
::String Description;
::ara::ucm::pkgmgr::TransferIdType TransferID;
::ara::ucm::pkgmgr::RequestType requestType;
::ara::ucm::pkgmgr::PackageType packageType;
::ara::ucm::pkgmgr::SwPackageInfoStateType State;

    using IsEnumerableTag = void;
  
    template <typename T>
    void Serialize(T* serializer) const
    {
        serializer->Serialize(Name);
        serializer->Serialize(Version);
        serializer->Serialize(Description);
        serializer->Serialize(TransferID);
        serializer->Serialize(requestType);
        serializer->Serialize(packageType);
        serializer->Serialize(State);

    }

    template <typename T>
    bool Deserialize(T* deserializer)
    {
        if (!deserializer->Deserialize(Name))
        {
            return false;
        }
        if (!deserializer->Deserialize(Version))
        {
            return false;
        }
        if (!deserializer->Deserialize(Description))
        {
            return false;
        }
        if (!deserializer->Deserialize(TransferID))
        {
            return false;
        }
        if (!deserializer->Deserialize(requestType))
        {
            return false;
        }
        if (!deserializer->Deserialize(packageType))
        {
            return false;
        }
        if (!deserializer->Deserialize(State))
        {
            return false;
        }

        return true;
	}
};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_SWPACKAGEINFOTYPE_H

