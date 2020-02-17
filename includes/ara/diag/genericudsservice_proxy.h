#ifndef ARA_DIAG_GENERICUDSSERVICE_PROXY_H_
#define ARA_DIAG_GENERICUDSSERVICE_PROXY_H_

#include "genericudsservice_common.h"
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

} // namespace fields


namespace methods
{
    using HandleMessage = ara::com::internal::proxy::Method<ara::diag::GenericUDSService::HandleMessageOutput(const ara::diag::SIDType&,const ara::diag::ByteVectorType&,const ara::diag::MetaInfoType&)>;
    using Cancel = ara::com::internal::proxy::Method<void(const ::ara::diag::MetaInfoType&)>;

} // namespace methods


class GenericUDSServiceProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
    using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit GenericUDSServiceProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("GenericUDSService", handle)
    	
    	
        , HandleMessage(this, "HandleMessage")
        , Cancel(this, "Cancel")

    {
        //Events
	
        //Fields
	
        //Methods
        addMethod("HandleMessage");
        addMethod("Cancel");
	
        //registerErrors
        registerGenericUDSServiceErrors();
		
        // init
        init();
    }
	
    virtual ~GenericUDSServiceProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("GenericUDSService", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("GenericUDSService", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("GenericUDSService", handler, instance);
    }
	
    // Events
	
    // Fields
	
    // Methods
    methods::HandleMessage HandleMessage;
    methods::Cancel Cancel;

};

} // namespace proxy
}
}

#endif //ARA_DIAG_GENERICUDSSERVICE_PROXY_H_
