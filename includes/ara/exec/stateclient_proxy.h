#ifndef ARA_EXEC_STATECLIENT_PROXY_H_
#define ARA_EXEC_STATECLIENT_PROXY_H_

#include "stateclient_common.h"
#include <ara/com/internal/proxy/types.h>

namespace ara
{
namespace exec
{
namespace proxy
{

namespace events
{
	using StateChangeEvent = ara::com::internal::proxy::Event<::ara::exec::StateChange>;
	
} // namespace events

namespace fields
{
} // namespace fields

namespace methods
{
	using GetState = ara::com::internal::proxy::Method<::ara::exec::StateClient::GetStateOutput(const ::ara::exec::GetStateRequest&)>;
	using SetState = ara::com::internal::proxy::Method<::ara::exec::StateClient::SetStateOutput(const ::ara::exec::SetStateRequest&)>;
} // namespace methods


class StateClientProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
	using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit StateClientProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("StateClient", handle)
		, StateChangeEvent(this, "StateChangeEvent")
    	, GetState(this, "GetState")
    	, SetState(this, "SetState")
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
	
    virtual ~StateClientProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("StateClient", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("StateClient", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("StateClient", handler, instance);
    }
	
	// Events
	events::StateChangeEvent StateChangeEvent;
	// Fields
	
	// Methods
	methods::GetState GetState;
	methods::SetState SetState;
};

} // namespace proxy
} // namespace exec
} // namespace ara


#endif //ARA_EXEC_STATECLIENT_PROXY_H_
