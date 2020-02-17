#ifndef ARA_DIAG_DATAIDENTIFIER_PROXY_H_
#define ARA_DIAG_DATAIDENTIFIER_PROXY_H_

#include "dataidentifier_common.h"
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
    using Read = ara::com::internal::proxy::Method<ara::diag::DataIdentifier::ReadOutput(const ara::diag::MetaInfoType&)>;
    using Write = ara::com::internal::proxy::Method<void(const ::ByteArray&,const ::ara::diag::MetaInfoType&)>;
    using Cancel = ara::com::internal::proxy::Method<void(const ::ara::diag::MetaInfoType&)>;

} // namespace methods


class DataIdentifierProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
    using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit DataIdentifierProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("DataIdentifier", handle)
    	
    	
        , Write(this, "Write")
        , Read(this, "Read")
        , Cancel(this, "Cancel")

    {
        //Events
	
        //Fields
	
        //Methods
        addMethod("Write");
        addMethod("Read");
        addMethod("Cancel");
	
        //registerErrors
        registerDataIdentifierErrors();
		
        // init
        init();
    }
	
    virtual ~DataIdentifierProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("DataIdentifier", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("DataIdentifier", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("DataIdentifier", handler, instance);
    }
	
    // Events
	
    // Fields
	
    // Methods
    methods::Write Write;
    methods::Read Read;
    methods::Cancel Cancel;

};

} // namespace proxy
}
}

#endif //ARA_DIAG_DATAIDENTIFIER_PROXY_H_
