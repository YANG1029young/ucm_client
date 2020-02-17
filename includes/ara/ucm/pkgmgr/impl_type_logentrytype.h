#ifndef ARA_UCM_PKGMGR_IMPL_TYPE_LOGENTRYTYPE_H
#define ARA_UCM_PKGMGR_IMPL_TYPE_LOGENTRYTYPE_H

#include "impl_type_uint8.h"
#include "impl_type_string.h"

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

struct LogEntryType
{	
    ::UInt8 LogLevel;
::String Message;

    using IsEnumerableTag = void;
  
    template <typename T>
    void Serialize(T* serializer) const
    {
        serializer->Serialize(LogLevel);
        serializer->Serialize(Message);

    }

    template <typename T>
    bool Deserialize(T* deserializer)
    {
        if (!deserializer->Deserialize(LogLevel))
        {
            return false;
        }
        if (!deserializer->Deserialize(Message))
        {
            return false;
        }

        return true;
	}
};

}
}
}

#endif // ARA_UCM_PKGMGR_IMPL_TYPE_LOGENTRYTYPE_H

