#ifndef ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICEVENT_SKELETON_H_
#define ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICEVENT_SKELETON_H_

#include "diagnosticevent_common.h"

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

} // namespace events


namespace fields
{
    using EventStatus = ara::com::internal::skeleton::FieldType<::ara::diag::EventStatusByteType,true,true,false>::type;

} // namespace fields


class DiagnosticEventSkeleton : public ara::com::internal::skeleton::ServiceSkeleton
{
public:
    DiagnosticEventSkeleton(
        ara::com::InstanceIdentifier instance,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	)
        : ara::com::internal::skeleton::ServiceSkeleton("DiagnosticEvent", instance, mode)

        , EventStatus(this, "EventStatus")

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

    virtual ~DiagnosticEventSkeleton(){}

    // Events
	
    // Fields
    fields::EventStatus EventStatus;
	
    // Methods
    virtual ara::core::Future<ara::diag::diagnostic_manager::DiagnosticEvent::FaultDetectionCounterOutput> FaultDetectionCounter() = 0;
    virtual ara::core::Future<ara::diag::diagnostic_manager::DiagnosticEvent::GetDebouncingOfEventOutput> GetDebouncingOfEvent() = 0;
    virtual ara::core::Future<ara::diag::diagnostic_manager::DiagnosticEvent::GetDTCOfEventOutput> GetDTCOfEvent(const ara::diag::DTCFormatType& DTCFormatType) = 0;
    virtual ara::core::Future<void> SetClearAllowed(const ::Boolean& IsClearAllowed) = 0;
	
    ara::core::Future<::ara::diag::EventStatusByteType> EventStatus_Get()
    {
        if (EventStatus.GetHandler)
        {
            return EventStatus.GetHandler();
        }
        else
        {
            return NoHandler<::ara::diag::EventStatusByteType>();
        }
    }

    virtual void DispatchMethodCall(const std::shared_ptr<ara::com::internal::Message> msg, std::shared_ptr<binding_base_type> binding)
    {
        if (msg->methodName == "FaultDetectionCounter")
        {
            HandleCall(*this, &DiagnosticEventSkeleton::FaultDetectionCounter, msg, binding);
        }
        if (msg->methodName == "GetDebouncingOfEvent")
        {
            HandleCall(*this, &DiagnosticEventSkeleton::GetDebouncingOfEvent, msg, binding);
        }
        if (msg->methodName == "GetDTCOfEvent")
        {
            HandleCall(*this, &DiagnosticEventSkeleton::GetDTCOfEvent, msg, binding);
        }
        if (msg->methodName == "SetClearAllowed")
        {
            HandleCall(*this, &DiagnosticEventSkeleton::SetClearAllowed, msg, binding);
        }

        if (msg->methodName == "EventStatus_Get")
        {
            HandleCall(*this, &DiagnosticEventSkeleton::EventStatus_Get, msg, binding);
        }
    
    }
};
} // namespace skeleton
}
}
}

#endif //ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICEVENT_SKELETON_H_
