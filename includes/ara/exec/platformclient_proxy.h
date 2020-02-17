#ifndef ARA_EXEC_PLATFORMCLIENT_PROXY_H_
#define ARA_EXEC_PLATFORMCLIENT_PROXY_H_

#include "platformclient_common.h"

#include <ara/com/internal/proxy/types.h>

namespace ara
{
namespace exec
{
namespace proxy
{

namespace events
{
} // namespace events

namespace fields
{
} // namespace fields

namespace methods
{
	using RequestRestartAction = ara::com::internal::proxy::Method<::ara::exec::PlatformClient::RequestRestartActionOutput(const ::ara::exec::String&)>;
	using SetProcessState = ara::com::internal::proxy::Method<::ara::exec::PlatformClient::SetProcessStateOutput(const ::ara::exec::String&, const ::ara::exec::ProcessState&)>;
	using GetProcessState = ara::com::internal::proxy::Method<::ara::exec::PlatformClient::GetProcessStateOutput(const ::ara::exec::String&)>;
	using ImmediateStateTransition = ara::com::internal::proxy::Method<::ara::exec::PlatformClient::ImmediateStateTransitionOutput(const ::ara::exec::MachineState&)>;
	using EnterSafeState = ara::com::internal::proxy::Method<::ara::exec::PlatformClient::EnterSafeStateOutput()>;
	
	using GetProcessName = ara::com::internal::proxy::Method<::ara::exec::PlatformClient::GetProcessNameOutput(const int&)>;
	using ActivateApplication = ara::com::internal::proxy::Method<::ara::exec::PlatformClient::ActivateApplicationOutput(const ::ara::exec::ApplicationInfo&)>;	
	
} // namespace methods

class PlatformClientProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
	using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit PlatformClientProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("PlatformClient", handle)
    	, RequestRestartAction(this, "RequestRestartAction")
    	, SetProcessState(this, "SetProcessState")
    	, GetProcessState(this, "GetProcessState")
    	, ImmediateStateTransition(this, "ImmediateStateTransition")
    	, EnterSafeState(this, "EnterSafeState")
		
		, GetProcessName(this, "GetProcessName")
		, ActivateApplication(this, "ActivateApplication")
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
	
    virtual ~PlatformClientProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("PlatformClient", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("PlatformClient", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("PlatformClient", handler, instance);
    }
	
	// Events
	
	// Fields
	
	// Methods
	methods::RequestRestartAction RequestRestartAction;
	methods::SetProcessState SetProcessState;
	methods::GetProcessState GetProcessState;
	methods::ImmediateStateTransition ImmediateStateTransition;
	methods::EnterSafeState EnterSafeState;
	
	methods::GetProcessName GetProcessName;
	methods::ActivateApplication ActivateApplication;
	
};

} // namespace proxy
} // namespace exec
} // namespace ara


#endif //ARA_EXEC_PLATFORMCLIENT_PROXY_H_
