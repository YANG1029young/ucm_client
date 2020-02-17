#ifndef ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICEVENT_PROXY_H_
#define ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICEVENT_PROXY_H_

#include "diagnosticevent_common.h"
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

} // namespace events


namespace fields
{
    using EventStatus = ara::com::internal::proxy::FieldType<::ara::diag::EventStatusByteType,true,true,false>::type;

} // namespace fields


namespace methods
{
    using FaultDetectionCounter = ara::com::internal::proxy::Method<ara::diag::diagnostic_manager::DiagnosticEvent::FaultDetectionCounterOutput()>;
    using GetDebouncingOfEvent = ara::com::internal::proxy::Method<ara::diag::diagnostic_manager::DiagnosticEvent::GetDebouncingOfEventOutput()>;
    using GetDTCOfEvent = ara::com::internal::proxy::Method<ara::diag::diagnostic_manager::DiagnosticEvent::GetDTCOfEventOutput(const ara::diag::DTCFormatType&)>;
    using SetClearAllowed = ara::com::internal::proxy::Method<void(const ::Boolean&)>;

} // namespace methods


class DiagnosticEventProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
    using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit DiagnosticEventProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("DiagnosticEvent", handle)
    	
        , EventStatus(this, "EventStatus")
    	
        , FaultDetectionCounter(this, "FaultDetectionCounter")
        , GetDebouncingOfEvent(this, "GetDebouncingOfEvent")
        , GetDTCOfEvent(this, "GetDTCOfEvent")
        , SetClearAllowed(this, "SetClearAllowed")

    {
        //Events
	
        //Fields
        addField("EventStatus",true,true,false);
	
        //Methods
        addMethod("FaultDetectionCounter");
        addMethod("GetDebouncingOfEvent");
        addMethod("GetDTCOfEvent");
        addMethod("SetClearAllowed");
	
        //registerErrors
        registerDiagnosticEventErrors();
		
        // init
        init();
    }
	
    virtual ~DiagnosticEventProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("DiagnosticEvent", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("DiagnosticEvent", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("DiagnosticEvent", handler, instance);
    }
	
    // Events
	
    // Fields
    fields::EventStatus EventStatus;
	
    // Methods
    methods::FaultDetectionCounter FaultDetectionCounter;
    methods::GetDebouncingOfEvent GetDebouncingOfEvent;
    methods::GetDTCOfEvent GetDTCOfEvent;
    methods::SetClearAllowed SetClearAllowed;

};

} // namespace proxy
}
}
}

#endif //ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICEVENT_PROXY_H_
