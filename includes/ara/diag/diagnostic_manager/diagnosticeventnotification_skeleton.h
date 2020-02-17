#ifndef ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICEVENTNOTIFICATION_SKELETON_H_
#define ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICEVENTNOTIFICATION_SKELETON_H_

#include "diagnosticeventnotification_common.h"

#include <ara/com/internal/skeleton/types.h>

namespace ara
{
namespace diag
{
namespace diagnostic_manager
{

namespace skeleton
{

namespace events
{
    using EventStatusChanged = ara::com::internal::skeleton::Event<::ara::diag::UdsDTCStatusByteChangedType>;
    using InitMonitor = ara::com::internal::skeleton::Event<::ara::diag::InitMonitorReasonType>;

} // namespace events


namespace fields
{
    using CurrentEventStatus = ara::com::internal::skeleton::FieldType<::ara::diag::UdsDTCStatusByteType,true,true,false>::type;

} // namespace fields


class DiagnosticEventNotificationSkeleton : public ara::com::internal::skeleton::ServiceSkeleton
{
public:
    DiagnosticEventNotificationSkeleton(
        ara::com::InstanceIdentifier instance,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	)
        : ara::com::internal::skeleton::ServiceSkeleton("DiagnosticEventNotification", instance, mode)
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

    virtual ~DiagnosticEventNotificationSkeleton(){}

    // Events
    events::EventStatusChanged EventStatusChanged;
    events::InitMonitor InitMonitor;
	
    // Fields
    fields::CurrentEventStatus CurrentEventStatus;
	
    // Methods
	
    ara::core::Future<::ara::diag::UdsDTCStatusByteType> CurrentEventStatus_Get()
    {
        if (CurrentEventStatus.GetHandler)
        {
            return CurrentEventStatus.GetHandler();
        }
        else
        {
            return NoHandler<::ara::diag::UdsDTCStatusByteType>();
        }
    }

    virtual void DispatchMethodCall(const std::shared_ptr<ara::com::internal::Message> msg, std::shared_ptr<binding_base_type> binding)
    {

        if (msg->methodName == "CurrentEventStatus_Get")
        {
            HandleCall(*this, &DiagnosticEventNotificationSkeleton::CurrentEventStatus_Get, msg, binding);
        }
    
    }
};
} // namespace skeleton
}
}
}

#endif //ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICEVENTNOTIFICATION_SKELETON_H_
