#ifndef ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICMONITOR_PROXY_H_
#define ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICMONITOR_PROXY_H_

#include "diagnosticmonitor_common.h"
#include <ara/com/internal/proxy/types.h>

namespace ara
{
namespace diag
{
namespace diagnostic_manager
{

namespace proxy
{

namespace events
{
    using MonitorAction = ara::com::internal::proxy::Event<::ara::diag::MonitorActionType>;

} // namespace events


namespace fields
{

} // namespace fields


namespace methods
{
    using InitMonitor = ara::com::internal::proxy::Method<void(const ::ara::diag::InitMonitorReasonType&)>;

} // namespace methods


class DiagnosticMonitorProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
    using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit DiagnosticMonitorProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("DiagnosticMonitor", handle)
        , MonitorAction(this, "MonitorAction")
    	
    	
        , InitMonitor(this, "InitMonitor")

    {
        //Events
        addEvent("MonitorAction");
	
        //Fields
	
        //Methods
        addMethod("InitMonitor");
	
        //registerErrors
        registerDiagnosticMonitorErrors();
		
        // init
        init();
    }
	
    virtual ~DiagnosticMonitorProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("DiagnosticMonitor", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("DiagnosticMonitor", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("DiagnosticMonitor", handler, instance);
    }
	
    // Events
    events::MonitorAction MonitorAction;
	
    // Fields
	
    // Methods
    methods::InitMonitor InitMonitor;

};

} // namespace proxy
}
}
}

#endif //ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICMONITOR_PROXY_H_
