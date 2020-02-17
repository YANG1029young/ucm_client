#ifndef ARA_EXEC_EXECUTIONCLIENT_SKELETON_H_
#define ARA_EXEC_EXECUTIONCLIENT_SKELETON_H_

#include "executionclient_common.h"

#include <ara/com/internal/skeleton/types.h>

namespace ara
{
namespace exec
{
namespace skeleton
{

namespace events
{
} // namespace events

namespace fields
{
} // namespace fields

class ExecutionClientSkeleton : public ara::com::internal::skeleton::ServiceSkeleton
{
public:
	ExecutionClientSkeleton(
		ara::com::InstanceIdentifier instance,
		ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	)
		: ara::com::internal::skeleton::ServiceSkeleton("ExecutionClient", instance, mode)
	{
		// Events
		
		// Fields
		
		// Methods
		addMethod("ReportExecutionState");
		
		//registerErrors
		registerExecutionClientErrors();
		
		// init
		init();
	}
	
	virtual ~ExecutionClientSkeleton(){}
	
	// Events
	
	// Fields
	
	// Methods
	virtual ara::core::Future<ara::exec::ExecutionClient::ReportExecutionStateOutput> ReportExecutionState(const ::ara::exec::ExecutionState& state, const int& pid) = 0;
	
	virtual void DispatchMethodCall(const std::shared_ptr<ara::com::internal::Message> msg, std::shared_ptr<binding_base_type> binding)
	{
		if (msg->methodName == "ReportExecutionState")
		{
			HandleCall(*this, &ExecutionClientSkeleton::ReportExecutionState, msg, binding);
		}
	}
};

} // namespace skeleton
} // namespace exec
} // namespace ara

#endif //ARA_EXEC_EXECUTIONCLIENT_SKELETON_H_
