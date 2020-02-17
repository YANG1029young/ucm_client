#ifndef ARA_DIAG_REQUESTRESTART_PROXY_H_
#define ARA_DIAG_REQUESTRESTART_PROXY_H_

#include "requestrestart_common.h"
#include <ara/com/internal/proxy/types.h>

namespace ara
{
namespace diag
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
    using RequestRestart = ara::com::internal::proxy::Method<void(const ::ara::diag::RestartType&,const ::ara::diag::ExecutionType&)>;

} // namespace methods


class RequestRestartProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
    using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit RequestRestartProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("RequestRestart", handle)
    	
    	
        , RequestRestart(this, "RequestRestart")

    {
        //Events
	
        //Fields
	
        //Methods
        addMethod("RequestRestart");
	
        //registerErrors
        registerRequestRestartErrors();
		
        // init
        init();
    }
	
    virtual ~RequestRestartProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("RequestRestart", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("RequestRestart", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("RequestRestart", handler, instance);
    }
	
    // Events
	
    // Fields
	
    // Methods
    methods::RequestRestart RequestRestart;

};

} // namespace proxy
}
}

#endif //ARA_DIAG_REQUESTRESTART_PROXY_H_
