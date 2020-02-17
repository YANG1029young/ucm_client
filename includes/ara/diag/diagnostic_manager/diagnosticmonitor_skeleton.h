#ifndef ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICMONITOR_SKELETON_H_
#define ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICMONITOR_SKELETON_H_

#include "diagnosticmonitor_common.h"

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
    using MonitorAction = ara::com::internal::skeleton::Event<::ara::diag::MonitorActionType>;

} // namespace events


namespace fields
{

} // namespace fields


class DiagnosticMonitorSkeleton : public ara::com::internal::skeleton::ServiceSkeleton
{
public:
    DiagnosticMonitorSkeleton(
        ara::com::InstanceIdentifier instance,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	)
        : ara::com::internal::skeleton::ServiceSkeleton("DiagnosticMonitor", instance, mode)
        , MonitorAction(this, "MonitorAction")


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

    virtual ~DiagnosticMonitorSkeleton(){}

    // Events
    events::MonitorAction MonitorAction;
	
    // Fields
	
    // Methods
    virtual ara::core::Future<void> InitMonitor(const ::ara::diag::InitMonitorReasonType& reason) = 0;
	

    virtual void DispatchMethodCall(const std::shared_ptr<ara::com::internal::Message> msg, std::shared_ptr<binding_base_type> binding)
    {
        if (msg->methodName == "InitMonitor")
        {
            HandleCall(*this, &DiagnosticMonitorSkeleton::InitMonitor, msg, binding);
        }

    
    }
};
} // namespace skeleton
}
}
}

#endif //ARA_DIAG_DIAGNOSTIC_MANAGER_DIAGNOSTICMONITOR_SKELETON_H_
