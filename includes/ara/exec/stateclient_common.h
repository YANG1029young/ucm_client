#ifndef ARA_EXEC_STATECLIENT_COMMON_H
#define ARA_EXEC_STATECLIENT_COMMON_H

#include <ara/com/types.h>

#include <ara/exec/impl_type_getstateresponse.h>
#include <ara/exec/impl_type_setstateresponse.h>
#include <ara/exec/impl_type_getstaterequest.h>
#include <ara/exec/impl_type_setstaterequest.h>

namespace ara
{
namespace exec
{

class StateClient
{
public:
	struct GetStateOutput
	{
		GetStateOutput(){};
		
		::ara::exec::GetStateResponse response;

		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(response);
		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(response))
			{
				return false;
			}
			
			return true;
		}
    };
    
    struct SetStateOutput
	{
		SetStateOutput(){};
		
		::ara::exec::SetStateResponse response;

		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(response);
		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(response))
			{
				return false;
			}
			
			return true;
		}
    };
};

static void registerStateClientErrors()
{
}

} // namespace exec
} // namespace ara

#endif //ARA_EXEC_STATECLIENT_COMMON_H


