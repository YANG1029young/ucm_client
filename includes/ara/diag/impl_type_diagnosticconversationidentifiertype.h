#ifndef ARA_DIAG_IMPL_TYPE_DIAGNOSTICCONVERSATIONIDENTIFIERTYPE_H
#define ARA_DIAG_IMPL_TYPE_DIAGNOSTICCONVERSATIONIDENTIFIERTYPE_H

#include "impl_type_string.h"
#include "impl_type_udsaddresstype.h"
#include "impl_type_udsaddresstype.h"

namespace ara
{
namespace diag
{

struct DiagnosticConversationIdentifierType
{	
    ::String diagnosticProtocolKind;
	::ara::diag::UdsAddressType diagnoticServerAddress;
	::ara::diag::UdsAddressType testerAddress;

    using IsEnumerableTag = void;
  
    template <typename T>
    void Serialize(T* serializer) const
    {
        serializer->Serialize(diagnosticProtocolKind);
        serializer->Serialize(diagnoticServerAddress);
        serializer->Serialize(testerAddress);

    }

    template <typename T>
    bool Deserialize(T* deserializer)
    {
        if (!deserializer->Deserialize(diagnosticProtocolKind))
        {
            return false;
        }
        if (!deserializer->Deserialize(diagnoticServerAddress))
        {
            return false;
        }
        if (!deserializer->Deserialize(testerAddress))
        {
            return false;
        }

        return true;
	}
};

}
}

#endif // ARA_DIAG_IMPL_TYPE_DIAGNOSTICCONVERSATIONIDENTIFIERTYPE_H

