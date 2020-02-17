#ifndef ARA_EXEC_IMPL_TYPE_GETSTATEREQUEST_H
#define ARA_EXEC_IMPL_TYPE_GETSTATEREQUEST_H

#include <ara/exec/impl_type_string.h>

namespace ara
{
namespace exec
{

struct GetStateRequest
{
    ::ara::exec::String groupName;
    
    using IsEnumerableTag = void;
    
    template <typename T>
	void Serialize(T* serializer) const
	{
		serializer->Serialize(groupName);
	}

	template <typename T>
	bool Deserialize(T* deserializer)
	{
		if (!deserializer->Deserialize(groupName))
		{
			return false;
		}

		return true;
	}
};

} // namespace exec
} // namespace ara

#endif // ARA_EXEC_IMPL_TYPE_GETSTATEREQUEST_H

