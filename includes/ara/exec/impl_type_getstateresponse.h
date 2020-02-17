#ifndef ARA_EXEC_IMPL_TYPE_GETSTATERESPONSE_H
#define ARA_EXEC_IMPL_TYPE_GETSTATERESPONSE_H

#include <ara/exec/impl_type_string.h>
#include <ara/exec/impl_type_getstateresponsestatus.h>

namespace ara
{
namespace exec
{

struct GetStateResponse
{
	::ara::exec::GetStateResponseStatus status;
    ::ara::exec::String currentState;
    
    using IsEnumerableTag = void;
    
    template <typename T>
	void Serialize(T* serializer) const
	{
		serializer->Serialize(status);
		serializer->Serialize(currentState);
	}

	template <typename T>
	bool Deserialize(T* deserializer)
	{
		if (!deserializer->Deserialize(status))
		{
			return false;
		}
		
		if (!deserializer->Deserialize(currentState))
		{
			return false;
		}

		return true;
	}
};

} // namespace exec
} // namespace ara

#endif // ARA_EXEC_IMPL_TYPE_GETSTATERESPONSE_H

