#ifndef ARA_DIAG_VININFORMATION_PROXY_H_
#define ARA_DIAG_VININFORMATION_PROXY_H_

#include "vininformation_common.h"
#include <ara/com/internal/proxy/types.h>

namespace ara
{
namespace diag
{
namespace VINInformation
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
    using Read = ara::com::internal::proxy::Method<ara::diag::VINInformation::ReadOutput(const ara::diag::MetaInfoType&)>;
    using Write = ara::com::internal::proxy::Method<void(const ::ara::diag::VINType&,const ::ara::diag::MetaInfoType&)>;
    using Cancel = ara::com::internal::proxy::Method<void(const ::ara::diag::MetaInfoType&)>;

} // namespace methods


class VINInformationProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
    using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit VINInformationProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("VINInformation", handle)
    	
    	
        , Read(this, "Read")
        , Write(this, "Write")
        , Cancel(this, "Cancel")

    {
        //Events
	
        //Fields
	
        //Methods
        addMethod("Read");
        addMethod("Write");
        addMethod("Cancel");
	
        //registerErrors
        registerVINInformationErrors();
		
        // init
        init();
    }
	
    virtual ~VINInformationProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("VINInformation", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("VINInformation", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("VINInformation", handler, instance);
    }
	
    // Events
	
    // Fields
	
    // Methods
    methods::Read Read;
    methods::Write Write;
    methods::Cancel Cancel;

};

} // namespace proxy
}
}
}
#endif //ARA_DIAG_VININFORMATION_PROXY_H_
