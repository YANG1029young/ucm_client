#ifndef ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICMONITOR_COMMON_H
#define ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICMONITOR_COMMON_H

#include <ara/com/types.h>
#include <impl_type_uint8.h>
#include <ara/diag/impl_type_initmonitorreasontype.h>
#include <ara/diag/impl_type_monitoractiontype.h>

namespace ara
{
namespace diag
{
namespace diagnostic_manager
{

class DiagnosticMonitor
{
public:
		struct InitMonitorOutput
	{
		InitMonitorOutput(){}
		
		
		
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



static void registerDiagnosticMonitorErrors()
{
	
}

}
}
}

#endif //ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICMONITOR_COMMON_H
