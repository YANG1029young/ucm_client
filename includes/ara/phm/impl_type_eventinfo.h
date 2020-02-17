#ifndef ARA_PHM_IMPL_TYPE_EVENTINFO_H
#define ARA_PHM_IMPL_TYPE_EVENTINFO_H

#include "impl_type_uint8.h"
#include "impl_type_uint8.h"
#include "impl_type_uint8.h"

namespace ara
{
namespace phm
{

struct EventInfo
{	
 ::UInt8 status;
::UInt8 type;
::UInt8 instance;

    using IsEnumerableTag = void;
  
    template <typename T>
    void Serialize(T* serializer) const
    {
        serializer->Serialize(status);
        serializer->Serialize(type);
        serializer->Serialize(instance);

    }

    template <typename T>
    bool Deserialize(T* deserializer)
    {
        if (!deserializer->Deserialize(status))
        {
            return false;
        }
        if (!deserializer->Deserialize(type))
        {
            return false;
        }
        if (!deserializer->Deserialize(instance))
        {
            return false;
        }

        return true;
	}
};

}
}

#endif // ARA_PHM_IMPL_TYPE_EVENTINFO_H

