#ifndef ARA_DIAG_DIAGNOSTICCONVERSATION_COMMON_H
#define ARA_DIAG_DIAGNOSTICCONVERSATION_COMMON_H

#include <ara/com/types.h>
#include <impl_type_uint8.h>
#include <impl_type_uint16.h>
#include <impl_type_string.h>
#include <ara/diag/impl_type_activitystatustype.h>
#include <ara/diag/impl_type_diagnosticsessiontype.h>
#include <ara/diag/impl_type_diagnosticsecurityleveltype.h>
#include <ara/diag/impl_type_diagnosticconversationidentifiertype.h>
#include <ara/diag/impl_type_udsaddresstype.h>

namespace ara
{
namespace diag
{

class DiagnosticConversation
{
public:
		struct ResetToDefaultSessionOutput
	{
		ResetToDefaultSessionOutput(){}
		
		
		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			
		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			
			
			return true;
		}
};
struct CancelOutput
	{
		CancelOutput(){}
		
		
		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			
		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			
			
			return true;
		}
};

};



static void registerDiagnosticConversationErrors()
{
	
}

}
}

#endif //ARA_DIAG_DIAGNOSTICCONVERSATION_COMMON_H
