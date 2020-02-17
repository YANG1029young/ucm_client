#ifndef ARA_DIAG_DIAGNOSTICSERVER_SKELETON_H_
#define ARA_DIAG_DIAGNOSTICSERVER_SKELETON_H_

#include "diagnosticserver_common.h"

#include <ara/com/internal/skeleton/types.h>

namespace ara
{
namespace diag
{

namespace skeleton
{

namespace events
{

} // namespace events


namespace fields
{
    using ControlDTCStatus = ara::com::internal::skeleton::FieldType<::ara::diag::ControlDTCStatusType,true,true,false>::type;

} // namespace fields


class DiagnosticServerSkeleton : public ara::com::internal::skeleton::ServiceSkeleton
{
public:
    DiagnosticServerSkeleton(
        ara::com::InstanceIdentifier instance,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	)
        : ara::com::internal::skeleton::ServiceSkeleton("DiagnosticServer", instance, mode)

        , ControlDTCStatus(this, "ControlDTCStatus")

    {
        //Events
	
        //Fields
        addField("ControlDTCStatus",true,true,false);
	
        //Methods
	
        //registerErrors
        registerDiagnosticServerErrors();
		
        // init
        init();
    }

    virtual ~DiagnosticServerSkeleton(){}

    // Events
	
    // Fields
    fields::ControlDTCStatus ControlDTCStatus;
	
    // Methods
	
    ara::core::Future<::ara::diag::ControlDTCStatusType> ControlDTCStatus_Get()
    {
        if (ControlDTCStatus.GetHandler)
        {
            return ControlDTCStatus.GetHandler();
        }
        else
        {
            return NoHandler<::ara::diag::ControlDTCStatusType>();
        }
    }

    virtual void DispatchMethodCall(const std::shared_ptr<ara::com::internal::Message> msg, std::shared_ptr<binding_base_type> binding)
    {

        if (msg->methodName == "ControlDTCStatus_Get")
        {
            HandleCall(*this, &DiagnosticServerSkeleton::ControlDTCStatus_Get, msg, binding);
        }
    
    }
};
} // namespace skeleton
}
}

#endif //ARA_DIAG_DIAGNOSTICSERVER_SKELETON_H_
