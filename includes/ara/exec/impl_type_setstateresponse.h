#ifndef ARA_EXEC_IMPL_TYPE_SETSTATERESPONSE_H
#define ARA_EXEC_IMPL_TYPE_SETSTATERESPONSE_H

#include <ara/exec/impl_type_vector.h>
#include <ara/exec/impl_type_setstateresponsestatus.h>
#include <ara/exec/impl_type_statechangestatus.h>

namespace ara
{
namespace exec
{

struct SetStateResponse
{
	::ara::exec::SetStateResponseStatus status;
    ::ara::exec::Vector<StateChangeStatus> requestResults;
    
    using IsEnumerableTag = void;
    
    template <typename T>
	void Serialize(T* serializer) const
	{
		serializer->Serialize(status);
		serializer->Serialize(requestResults);
	}

	template <typename T>
	bool Deserialize(T* deserializer)
	{
		if (!deserializer->Deserialize(status))
		{
			return false;
		}
		
		if (!deserializer->Deserialize(requestResults))
		{
			return false;
		}

		return true;
	}
};

} // namespace exec
} // namespace ara

#endif // ARA_EXEC_IMPL_TYPE_SETSTATERESPONSE_H

