#ifndef ARA_EXEC_EXECUTIONCLIENT_PROXY_H_
#define ARA_EXEC_EXECUTIONCLIENT_PROXY_H_

#include "executionclient_common.h"
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
	using ReportExecutionState = ara::com::internal::proxy::Method<::ara::exec::ExecutionClient::ReportExecutionStateOutput(const ::ara::exec::ExecutionState&, const int&)>;
} // namespace methods


class ExecutionClientProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
	using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit ExecutionClientProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("ExecutionClient", handle)
    	, ReportExecutionState(this, "ReportExecutionState")
	{
		// Events
		
		// Fields
		
		// Methods
		addMethod("ReportExecutionState");
		
		//registerErrors
		registerExecutionClientErrors();
		
		// init
		init();
	}
	
    virtual ~ExecutionClientProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("ExecutionClient", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("ExecutionClient", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("ExecutionClient", handler, instance);
    }
	
	// Events
	
	// Fields
	
	// Methods
	methods::ReportExecutionState ReportExecutionState;
};

} // namespace proxy
} // namespace exec
} // namespace ara


#endif //ARA_EXEC_EXECUTIONCLIENT_PROXY_H_
