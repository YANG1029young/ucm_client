#ifndef ARA_EXEC_PLATFORMCLIENT_SKELETON_H_
#define ARA_EXEC_PLATFORMCLIENT_SKELETON_H_

#include "platformclient_common.h"

#include <ara/com/internal/skeleton/types.h>

namespace ara
{
namespace exec
{
namespace skeleton
{

namespace events
{
} // namespace events

namespace fields
{
} // namespace fields

class PlatformClientSkeleton : public ara::com::internal::skeleton::ServiceSkeleton
{
public:
	PlatformClientSkeleton(
		ara::com::InstanceIdentifier instance,
		ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	)
		: ara::com::internal::skeleton::ServiceSkeleton("PlatformClient", instance, mode)
	{
		// Events
		
		// Fields
		
		// Methods
		addMethod("RequestRestartAction");
		addMethod("SetProcessState");
		addMethod("GetProcessState");
		addMethod("ImmediateStateTransition");
		addMethod("EnterSafeState");
		
		addMethod("GetProcessName");
		addMethod("ActivateApplication");
		
		//registerErrors
		registerPlatformClientErrors();
		
		// init
		init();
	}
	
	virtual ~PlatformClientSkeleton(){}
	
	// Events
	
	// Fields
	
	// Methods
	virtual ara::core::Future<ara::exec::PlatformClient::RequestRestartActionOutput> RequestRestartAction(const ::ara::exec::String& applicationname) = 0;
	virtual ara::core::Future<ara::exec::PlatformClient::SetProcessStateOutput> SetProcessState(const ::ara::exec::String& applicationname, const ::ara::exec::ProcessState& state) = 0;
	virtual ara::core::Future<ara::exec::PlatformClient::GetProcessStateOutput> GetProcessState(const ::ara::exec::String& applicationname) = 0;
	virtual ara::core::Future<ara::exec::PlatformClient::ImmediateStateTransitionOutput> ImmediateStateTransition(const ::ara::exec::MachineState& state) = 0;
	virtual ara::core::Future<ara::exec::PlatformClient::EnterSafeStateOutput> EnterSafeState() = 0;
	
	virtual ara::core::Future<ara::exec::PlatformClient::GetProcessNameOutput> GetProcessName(const int& pid) = 0;
	virtual ara::core::Future<ara::exec::PlatformClient::ActivateApplicationOutput> ActivateApplication(const ::ara::exec::ApplicationInfo& applicationinfo) = 0;
	
	virtual void DispatchMethodCall(const std::shared_ptr<ara::com::internal::Message> msg, std::shared_ptr<binding_base_type> binding)
	{
		if (msg->methodName == "RequestRestartAction")
		{
			HandleCall(*this, &PlatformClientSkeleton::RequestRestartAction, msg, binding);
		}
		else if (msg->methodName == "SetProcessState")
		{
			HandleCall(*this, &PlatformClientSkeleton::SetProcessState, msg, binding);
		}
		else if (msg->methodName == "GetProcessState")
		{
			HandleCall(*this, &PlatformClientSkeleton::GetProcessState, msg, binding);
		}
		else if (msg->methodName == "ImmediateStateTransition")
		{
			HandleCall(*this, &PlatformClientSkeleton::ImmediateStateTransition, msg, binding);
		}
		else if (msg->methodName == "EnterSafeState")
		{
			HandleCall(*this, &PlatformClientSkeleton::EnterSafeState, msg, binding);
		}
		
		else if (msg->methodName == "GetProcessName")
		{
			HandleCall (*this, &PlatformClientSkeleton::GetProcessName, msg, binding);
		}
		else if (msg->methodName == "ActivateApplication")
		{
			HandleCall (*this, &PlatformClientSkeleton::ActivateApplication, msg, binding);
		}
	}
};

} // namespace skeleton
} // namespace exec
} // namespace ara

#endif //ARA_EXEC_PLATFORMCLIENT_SKELETON_H_
