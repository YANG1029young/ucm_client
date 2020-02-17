#ifndef ARA_EXEC_IMPL_TYPE_STATECHANGE_H
#define ARA_EXEC_IMPL_TYPE_STATECHANGE_H

#include <ara/exec/impl_type_string.h>

namespace ara
{
namespace exec
{

struct StateChange
{
    ::ara::exec::String functionGroupName;
    ::ara::exec::String newStateName;
    
    using IsEnumerableTag = void;
    
    template <typename T>
	void Serialize(T* serializer) const
	{
		serializer->Serialize(functionGroupName);
		serializer->Serialize(newStateName);
	}

	template <typename T>
	bool Deserialize(T* deserializer)
	{
		if (!deserializer->Deserialize(functionGroupName))
		{
			return false;
		}
		
		if (!deserializer->Deserialize(newStateName))
		{
			return false;
		}

		return true;
	}
};

} // namespace exec
} // namespace ara

#endif // ARA_EXEC_IMPL_TYPE_STATECHANGE_H

