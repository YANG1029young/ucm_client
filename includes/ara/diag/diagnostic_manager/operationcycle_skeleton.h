#ifndef ARA_DIAG_DIAGNOSTIC_MANAGER_OPERATIONCYCLE_SKELETON_H_
#define ARA_DIAG_DIAGNOSTIC_MANAGER_OPERATIONCYCLE_SKELETON_H_

#include "operationcycle_common.h"

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
    using State = ara::com::internal::skeleton::FieldType<::ara::diag::OperationCycleStateType,true,true,true>::type;

} // namespace fields


class OperationCycleSkeleton : public ara::com::internal::skeleton::ServiceSkeleton
{
public:
    OperationCycleSkeleton(
        ara::com::InstanceIdentifier instance,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	)
        : ara::com::internal::skeleton::ServiceSkeleton("OperationCycle", instance, mode)

        , State(this, "State")

    {
        //Events
	
        //Fields
        addField("State",true,true,true);
	
        //Methods
	
        //registerErrors
        registerOperationCycleErrors();
		
        // init
        init();
    }

    virtual ~OperationCycleSkeleton(){}

    // Events
	
    // Fields
    fields::State State;
	
    // Methods
	
    ara::core::Future<::ara::diag::OperationCycleStateType> State_Get()
    {
        if (State.GetHandler)
        {
            return State.GetHandler();
        }
        else
        {
            return NoHandler<::ara::diag::OperationCycleStateType>();
        }
    }
    ara::core::Future<::ara::diag::OperationCycleStateType> State_Set(const ::ara::diag::OperationCycleStateType& value)
    {
        if (State.SetHandler)
        {
            return State.SetHandler(value);
        }
        else
        {
            return NoHandler<::ara::diag::OperationCycleStateType>();
        }
    }

    virtual void DispatchMethodCall(const std::shared_ptr<ara::com::internal::Message> msg, std::shared_ptr<binding_base_type> binding)
    {

        if (msg->methodName == "State_Get")
        {
            HandleCall(*this, &OperationCycleSkeleton::State_Get, msg, binding);
        }
        else if (msg->methodName == "State_Set")
        {
            HandleCall(*this, &OperationCycleSkeleton::State_Set, msg, binding);
        }
    
    }
};
} // namespace skeleton
}
}
}

#endif //ARA_DIAG_DIAGNOSTIC_MANAGER_OPERATIONCYCLE_SKELETON_H_
