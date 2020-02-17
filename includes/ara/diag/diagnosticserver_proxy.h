#ifndef ARA_DIAG_DIAGNOSTICSERVER_PROXY_H_
#define ARA_DIAG_DIAGNOSTICSERVER_PROXY_H_

#include "diagnosticserver_common.h"
#include <ara/com/internal/proxy/types.h>

namespace ara
{
namespace diag
{

namespace proxy
{

namespace events
{

} // namespace events


namespace fields
{
    using ControlDTCStatus = ara::com::internal::proxy::FieldType<::ara::diag::ControlDTCStatusType,true,true,false>::type;

} // namespace fields


namespace methods
{

} // namespace methods


class DiagnosticServerProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
    using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit DiagnosticServerProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("DiagnosticServer", handle)
    	
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
	
    virtual ~DiagnosticServerProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("DiagnosticServer", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("DiagnosticServer", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("DiagnosticServer", handler, instance);
    }
	
    // Events
	
    // Fields
    fields::ControlDTCStatus ControlDTCStatus;
	
    // Methods

};

} // namespace proxy
}
}

#endif //ARA_DIAG_DIAGNOSTICSERVER_PROXY_H_
