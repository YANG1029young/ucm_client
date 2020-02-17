#ifndef ARA_DIAG_SECURITYACCESS_PROXY_H_
#define ARA_DIAG_SECURITYACCESS_PROXY_H_

#include "securityaccess_common.h"
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
    using GetSeed = ara::com::internal::proxy::Method<ara::diag::SecurityAccess::GetSeedOutput(const ara::diag::ByteVectorType&,const ara::diag::MetaInfoType&)>;
    using CompareKey = ara::com::internal::proxy::Method<ara::diag::SecurityAccess::CompareKeyOutput(const ara::diag::ByteVectorType&,const ara::diag::MetaInfoType&)>;
    using Cancel = ara::com::internal::proxy::Method<void(const ::ara::diag::MetaInfoType&)>;

} // namespace methods


class SecurityAccessProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
    using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit SecurityAccessProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("SecurityAccess", handle)
    	
    	
        , GetSeed(this, "GetSeed")
        , CompareKey(this, "CompareKey")
        , Cancel(this, "Cancel")

    {
        //Events
	
        //Fields
	
        //Methods
        addMethod("GetSeed");
        addMethod("CompareKey");
        addMethod("Cancel");
	
        //registerErrors
        registerSecurityAccessErrors();
		
        // init
        init();
    }
	
    virtual ~SecurityAccessProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("SecurityAccess", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("SecurityAccess", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("SecurityAccess", handler, instance);
    }
	
    // Events
	
    // Fields
	
    // Methods
    methods::GetSeed GetSeed;
    methods::CompareKey CompareKey;
    methods::Cancel Cancel;

};

} // namespace proxy
}
}

#endif //ARA_DIAG_SECURITYACCESS_PROXY_H_
