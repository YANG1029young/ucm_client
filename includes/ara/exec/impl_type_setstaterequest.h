#ifndef ARA_EXEC_IMPL_TYPE_SETSTATEREQUEST_H
#define ARA_EXEC_IMPL_TYPE_SETSTATEREQUEST_H

#include <ara/exec/impl_type_vector.h>
#include <ara/exec/impl_type_statechange.h>

namespace ara
{
namespace exec
{

struct SetStateRequest
{
    ::ara::exec::Vector<::ara::exec::StateChange> changes;
    
    using IsEnumerableTag = void;
    
    template <typename T>
	void Serialize(T* serializer) const
	{
		serializer->Serialize(changes);
	}

	template <typename T>
	bool Deserialize(T* deserializer)
	{
		if (!deserializer->Deserialize(changes))
		{
			return false;
		}

		return true;
	}
};

} // namespace exec
} // namespace ara

#endif // ARA_EXEC_IMPL_TYPE_SETSTATEREQUEST_H

