#ifndef ARA_DIAG_DIAGNOSTIC_MANAGER_OPERATIONCYCLE_PROXY_H_
#define ARA_DIAG_DIAGNOSTIC_MANAGER_OPERATIONCYCLE_PROXY_H_

#include "operationcycle_common.h"
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
    using State = ara::com::internal::proxy::FieldType<::ara::diag::OperationCycleStateType,true,true,true>::type;

} // namespace fields


namespace methods
{

} // namespace methods


class OperationCycleProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
    using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit OperationCycleProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("OperationCycle", handle)
    	
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
	
    virtual ~OperationCycleProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("OperationCycle", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("OperationCycle", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("OperationCycle", handler, instance);
    }
	
    // Events
	
    // Fields
    fields::State State;
	
    // Methods

};

} // namespace proxy
}
}
}

#endif //ARA_DIAG_DIAGNOSTIC_MANAGER_OPERATIONCYCLE_PROXY_H_
