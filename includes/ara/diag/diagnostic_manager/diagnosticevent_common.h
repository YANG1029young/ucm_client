#ifndef ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICEVENT_COMMON_H
#define ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICEVENT_COMMON_H

#include <ara/com/types.h>
#include <impl_type_boolean.h>
#include <impl_type_uint32.h>
#include <impl_type_uint8.h>
#include <ara/diag/impl_type_eventstatusbytetype.h>
#include <ara/diag/impl_type_faultdetectioncountertype.h>
#include <ara/diag/impl_type_debouncingstatetype.h>
#include <ara/diag/impl_type_dtcformattype.h>
#include <ara/diag/impl_type_dtctype.h>

namespace ara
{
namespace diag
{
namespace diagnostic_manager
{

class DiagnosticEvent
{
public:
		struct FaultDetectionCounterOutput
	{
		FaultDetectionCounterOutput(){}
		
		::ara::diag::FaultDetectionCounterType faultDetectionCounter;

		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(faultDetectionCounter);

		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(faultDetectionCounter))
{
	return false;
}

			
			return true;
		}
};
struct GetDebouncingOfEventOutput
	{
		GetDebouncingOfEventOutput(){}
		
		::ara::diag::DebouncingStateType debouncingState;

		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(debouncingState);

		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(debouncingState))
{
	return false;
}

			
			return true;
		}
};
struct GetDTCOfEventOutput
	{
		GetDTCOfEventOutput(){}
		
		::ara::diag::DTCType DTCOfEvent;

		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(DTCOfEvent);

		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(DTCOfEvent))
{
	return false;
}

			
			return true;
		}
};
struct SetClearAllowedOutput
	{
		SetClearAllowedOutput(){}
		
		
		
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



static void registerDiagnosticEventErrors()
{
	
}

}
}
}

#endif //ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICEVENT_COMMON_H
