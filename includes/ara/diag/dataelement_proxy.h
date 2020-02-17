#ifndef ARA_DIAG_DATAELEMENT_PROXY_H_
#define ARA_DIAG_DATAELEMENT_PROXY_H_

#include "dataelement_common.h"
#include <ara/com/internal/proxy/types.h>

namespace ara
{
namespace diag
{
namespace DataElement
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
    using Read = ara::com::internal::proxy::Method<ara::diag::DataElement::ReadOutput(const ara::diag::MetaInfoType&)>;
    using Cancel = ara::com::internal::proxy::Method<void(const ::ara::diag::MetaInfoType&)>;

} // namespace methods


class DataElementProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
    using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit DataElementProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("DataElement", handle)
    	
    	
        , Read(this, "Read")
        , Cancel(this, "Cancel")

    {
        //Events
	
        //Fields
	
        //Methods
        addMethod("Read");
        addMethod("Cancel");
	
        //registerErrors
        registerDataElementErrors();
		
        // init
        init();
    }
	
    virtual ~DataElementProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("DataElement", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("DataElement", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("DataElement", handler, instance);
    }
	
    // Events
	
    // Fields
	
    // Methods
    methods::Read Read;
    methods::Cancel Cancel;

};

} // namespace proxy
}
}
}
#endif //ARA_DIAG_DATAELEMENT_PROXY_H_
