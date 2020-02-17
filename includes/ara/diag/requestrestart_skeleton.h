#ifndef ARA_DIAG_REQUESTRESTART_SKELETON_H_
#define ARA_DIAG_REQUESTRESTART_SKELETON_H_

#include "requestrestart_common.h"

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

} // namespace fields


class RequestRestartSkeleton : public ara::com::internal::skeleton::ServiceSkeleton
{
public:
    RequestRestartSkeleton(
        ara::com::InstanceIdentifier instance,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	)
        : ara::com::internal::skeleton::ServiceSkeleton("RequestRestart", instance, mode)


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

    virtual ~RequestRestartSkeleton(){}

    // Events
	
    // Fields
	
    // Methods
    virtual ara::core::Future<void> RequestRestart(const ::ara::diag::RestartType& RestartType,const ::ara::diag::ExecutionType& ExecutionType) = 0;
	

    virtual void DispatchMethodCall(const std::shared_ptr<ara::com::internal::Message> msg, std::shared_ptr<binding_base_type> binding)
    {
        if (msg->methodName == "RequestRestart")
        {
            HandleCall(*this, &RequestRestartSkeleton::RequestRestart, msg, binding);
        }

    
    }
};
} // namespace skeleton
}
}

#endif //ARA_DIAG_REQUESTRESTART_SKELETON_H_
