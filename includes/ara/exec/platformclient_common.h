#ifndef ARA_EXEC_PLATFORMCLIENT_COMMON_H
#define ARA_EXEC_PLATFORMCLIENT_COMMON_H

#include <ara/com/types.h>

#include <ara/exec/impl_type_machinestate.h>
#include <ara/exec/impl_type_statereturntype.h>
#include <ara/exec/impl_type_processstate.h>
#include <ara/exec/impl_type_applicationinfo.h>
#include <ara/exec/impl_type_string.h>

namespace ara
{
namespace exec
{

class PlatformClient
{
public:
	struct RequestRestartActionOutput
	{
		RequestRestartActionOutput(){};
		
		::ara::exec::StateReturnType stateReturn;

		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(stateReturn);
		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(stateReturn))
			{
				return false;
			}
			
			return true;
		}
    };
    
    struct SetProcessStateOutput
	{
		SetProcessStateOutput(){};
		
		::ara::exec::StateReturnType stateReturn;

		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(stateReturn);
		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(stateReturn))
			{
				return false;
			}
			
			return true;
		}
    };
    
    struct GetProcessStateOutput
	{
		GetProcessStateOutput(){};
		
		::ara::exec::ProcessState state;
		::ara::exec::StateReturnType stateReturn;

		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(state);
			serializer->Serialize(stateReturn);
		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(state))
			{
				return false;
			}
			
			if (!deserializer->Deserialize(stateReturn))
			{
				return false;
			}
			
			return true;
		}
    };
    
    struct ImmediateStateTransitionOutput
	{
		ImmediateStateTransitionOutput(){};
		
		::ara::exec::StateReturnType stateReturn;

		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(stateReturn);
		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(stateReturn))
			{
				return false;
			}
			
			return true;
		}
    };
    
    struct EnterSafeStateOutput
	{
		EnterSafeStateOutput(){};
		
		::ara::exec::StateReturnType stateReturn;

		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(stateReturn);
		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(stateReturn))
			{
				return false;
			}
			
			return true;
		}
    };


	struct GetProcessNameOutput
	{
		GetProcessNameOutput(){};
		
		::ara::exec::String applicationname;
		::ara::exec::StateReturnType stateReturn;

		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(applicationname);
			serializer->Serialize(stateReturn);
		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(applicationname))
			{
				return false;
			}
			if (!deserializer->Deserialize(stateReturn))
			{
				return false;
			}
			
			return true;
		}
    };
	
		struct ActivateApplicationOutput
	{
		ActivateApplicationOutput(){};
		
		::ara::exec::ApplicationInfo applicationinfo;
		::ara::exec::StateReturnType stateReturn;

		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(applicationinfo);
			serializer->Serialize(stateReturn);
		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(applicationinfo))
			{
				return false;
			}
			if (!deserializer->Deserialize(stateReturn))
			{
				return false;
			}
			
			return true;
		}
    };
};

static void registerPlatformClientErrors()
{
}

} // namespace exec
} // namespace ara

#endif //ARA_EXEC_PLATFORMCLIENT_COMMON_H


