#ifndef ARA_EXEC_STATECLIENT_SKELETON_H_
#define ARA_EXEC_STATECLIENT_SKELETON_H_

#include "stateclient_common.h"

#include <ara/com/internal/skeleton/types.h>

namespace ara
{
namespace exec
{
namespace skeleton
{

namespace events
{
	using StateChangeEvent = ara::com::internal::skeleton::Event<::ara::exec::StateChange>;
} // namespace events

namespace fields
{
} // namespace fields

class StateClientSkeleton : public ara::com::internal::skeleton::ServiceSkeleton
{
public:
	StateClientSkeleton(
		ara::com::InstanceIdentifier instance,
		ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	)
		: ara::com::internal::skeleton::ServiceSkeleton("StateClient", instance, mode)
		, StateChangeEvent(this, "StateChangeEvent")
	{
		// Events
		addEvent("StateChangeEvent");
		// Fields
		
		// Methods
		addMethod("GetState");
		addMethod("SetState");
		
		//registerErrors
		registerStateClientErrors();
		
		// init
		init();
	}
	
	virtual ~StateClientSkeleton(){}
	
	// Events
	events::StateChangeEvent StateChangeEvent;
	// Fields
	
	// Methods
	virtual ara::core::Future<ara::exec::StateClient::GetStateOutput> GetState(const ::ara::exec::GetStateRequest& request) = 0;
	virtual ara::core::Future<ara::exec::StateClient::SetStateOutput> SetState(const ::ara::exec::SetStateRequest& request) = 0;
	
	virtual void DispatchMethodCall(const std::shared_ptr<ara::com::internal::Message> msg, std::shared_ptr<binding_base_type> binding)
	{
		if (msg->methodName == "GetState")
		{
			HandleCall(*this, &StateClientSkeleton::GetState, msg, binding);
		}
		else if (msg->methodName == "SetState")
		{
			HandleCall(*this, &StateClientSkeleton::SetState, msg, binding);
		}
	}
};

} // namespace skeleton
} // namespace exec
} // namespace ara

#endif //ARA_EXEC_STATECLIENT_SKELETON_H_
