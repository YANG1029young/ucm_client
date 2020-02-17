#ifndef ARA_PHM_IMPL_TYPE_STATUSINFO_H
#define ARA_PHM_IMPL_TYPE_STATUSINFO_H

#include "impl_type_uint8.h"
#include "impl_type_string.h"

namespace ara
{
namespace phm
{

struct StatusInfo
{	
    ::UInt8 status;
::String name;

    using IsEnumerableTag = void;
  
    template <typename T>
    void Serialize(T* serializer) const
    {
        serializer->Serialize(status);
        serializer->Serialize(name);

    }

    template <typename T>
    bool Deserialize(T* deserializer)
    {
        if (!deserializer->Deserialize(status))
        {
            return false;
        }
        if (!deserializer->Deserialize(name))
        {
            return false;
        }

        return true;
	}
};

}
}

#endif // ARA_PHM_IMPL_TYPE_STATUSINFO_H

