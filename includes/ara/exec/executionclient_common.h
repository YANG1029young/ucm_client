#ifndef ARA_EXEC_EXECUTIONCLIENT_COMMON_H
#define ARA_EXEC_EXECUTIONCLIENT_COMMON_H

#include <ara/com/types.h>

#include <ara/exec/impl_type_executionstate.h>
#include <ara/exec/impl_type_executionreturntype.h>

namespace ara
{
namespace exec
{

class ExecutionClient
{
public:
	struct ReportExecutionStateOutput
	{
		ReportExecutionStateOutput(){};
		
		::ara::exec::ExecutionReturnType executionReturn;

		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(executionReturn);
		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(executionReturn))
			{
				return false;
			}
			
			return true;
		}
    };
};

static void registerExecutionClientErrors()
{
}

} // namespace exec
} // namespace ara

#endif //ARA_EXEC_EXECUTIONCLIENT_COMMON_H


