#ifndef ARA_PHM_PROXY_H_
#define ARA_PHM_PROXY_H_

#include <ara/phm/phmser_common.h>
#include <ara/com/internal/proxy/types.h>

namespace ara
{
namespace phm
{

namespace proxy
{

namespace events
{
    using statusChangeEvent = ara::com::internal::proxy::Event<::ara::phm::EventInfo>;

} // namespace events


namespace fields
{

} // namespace fields


namespace methods
{
    using ReportCheckpoint = ara::com::internal::proxy::Method<ara::phm::PhmSer::ReportCheckpointOutput(const ::UInt16&,const ::UInt8&,const ::Int32&,const ::UInt8&)>;
    using ReportHealthStatus = ara::com::internal::proxy::Method<ara::phm::PhmSer::ReportHealthStatusOutput(const ::UInt16&,const ::UInt8&,const ::Int32&,const ::ara::phm::StatusInfo&)>;
    using GetLocalStatus = ara::com::internal::proxy::Method<ara::phm::PhmSer::GetLocalStatusOutput(const ::Int32&,const ::UInt16&,const ::UInt8&)>;
    using GetGlobalStatus = ara::com::internal::proxy::Method<ara::phm::PhmSer::GetGlobalStatusOutput(const ::Int32&)>;

} // namespace methods


class PhmSerProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
    using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit PhmSerProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("PhmSer", handle)
        , statusChangeEvent(this, "statusChangeEvent")
    	
    	
        , ReportCheckpoint(this, "ReportCheckpoint")
        , ReportHealthStatus(this, "ReportHealthStatus")
        , GetLocalStatus(this, "GetLocalStatus")
        , GetGlobalStatus(this, "GetGlobalStatus")

    {
        //Events
        addEvent("statusChangeEvent");
	
        //Fields
	
        //Methods
        addMethod("ReportCheckpoint");
        addMethod("ReportHealthStatus");
        addMethod("GetLocalStatus");
        addMethod("GetGlobalStatus");
	
        //registerErrors
        registerErrors();
		
        // init
        init();
    }
	
    virtual ~PhmSerProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("PhmSer", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("PhmSer", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("PhmSer", handler, instance);
    }
	
    // Events
    events::statusChangeEvent statusChangeEvent;
	
    // Fields
	
    // Methods
    methods::ReportCheckpoint ReportCheckpoint;
    methods::ReportHealthStatus ReportHealthStatus;
    methods::GetLocalStatus GetLocalStatus;
    methods::GetGlobalStatus GetGlobalStatus;

};

} // namespace proxy
}
}

#endif //ARA_PHM_PROXY_H_
