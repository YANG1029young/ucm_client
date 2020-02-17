#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_SWCLUSTERINFOTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_SWCLUSTERINFOTYPE_H

#include "impl_type_swinfoname.h"
#include "impl_type_string.h"
#include "impl_type_swclusterinfostatetype.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

struct SwClusterInfoType
{	
    ::ara::ucm::pkgmgr::SwInfoName Name;
::String Version;
::ara::ucm::pkgmgr::SwClusterInfoStateType State;

    using IsEnumerableTag = void;
  
    template <typename T>
    void Serialize(T* serializer) const
    {
        serializer->Serialize(Name);
        serializer->Serialize(Version);
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

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_SWCLUSTERINFOTYPE_H

