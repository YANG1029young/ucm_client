#ifndef ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICEVENTNOTIFICATION_PROXY_H_
#define ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICEVENTNOTIFICATION_PROXY_H_

#include "diagnosticeventnotification_common.h"
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
    using EventStatusChanged = ara::com::internal::proxy::Event<::ara::diag::UdsDTCStatusByteChangedType>;
    using InitMonitor = ara::com::internal::proxy::Event<::ara::diag::InitMonitorReasonType>;

} // namespace events


namespace fields
{
    using CurrentEventStatus = ara::com::internal::proxy::FieldType<::ara::diag::UdsDTCStatusByteType,true,true,false>::type;

} // namespace fields


namespace methods
{

} // namespace methods


class DiagnosticEventNotificationProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
    using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit DiagnosticEventNotificationProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("DiagnosticEventNotification", handle)
        , EventStatusChanged(this, "EventStatusChanged")
        , InitMonitor(this, "InitMonitor")
    	
        , CurrentEventStatus(this, "CurrentEventStatus")
    	

    {
        //Events
        addEvent("EventStatusChanged");
        addEvent("InitMonitor");
	
        //Fields
        addField("CurrentEventStatus",true,true,false);
	
        //Methods
	
        //registerErrors
        registerDiagnosticEventNotificationErrors();
		
        // init
        init();
    }
	
    virtual ~DiagnosticEventNotificationProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("DiagnosticEventNotification", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("DiagnosticEventNotification", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("DiagnosticEventNotification", handler, instance);
    }
	
    // Events
    events::EventStatusChanged EventStatusChanged;
    events::InitMonitor InitMonitor;
	
    // Fields
    fields::CurrentEventStatus CurrentEventStatus;
	
    // Methods

};

} // namespace proxy
}
}
}

#endif //ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICEVENTNOTIFICATION_PROXY_H_
