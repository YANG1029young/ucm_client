#ifndef ARA_DIAG_IMPL_TYPE_UDSDTCSTATUSBYTECHANGEDTYPE_H
#define ARA_DIAG_IMPL_TYPE_UDSDTCSTATUSBYTECHANGEDTYPE_H

#include "impl_type_uint8.h"
#include "impl_type_uint8.h"

namespace ara
{
namespace diag
{

struct UdsDTCStatusByteChangedType
{	
    ::UInt8 uds_dtc_status_old;
::UInt8 uds_dtc_status_new;

    using IsEnumerableTag = void;
  
    template <typename T>
    void Serialize(T* serializer) const
    {
        serializer->Serialize(uds_dtc_status_old);
        serializer->Serialize(uds_dtc_status_new);

    }

    template <typename T>
    bool Deserialize(T* deserializer)
    {
        if (!deserializer->Deserialize(uds_dtc_status_old))
        {
            return false;
        }
        if (!deserializer->Deserialize(uds_dtc_status_new))
        {
            return false;
        }

        return true;
	}
};

}
}

#endif // ARA_DIAG_IMPL_TYPE_UDSDTCSTATUSBYTECHANGEDTYPE_H

