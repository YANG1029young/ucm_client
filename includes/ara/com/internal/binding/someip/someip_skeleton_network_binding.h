/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_BINDING_SOMEIP_SOMEIP_SKELETON_NETWORK_BINDING_H_
#define ARA_COM_INTERNAL_BINDING_SOMEIP_SOMEIP_SKELETON_NETWORK_BINDING_H_

#include <ara/com/internal/binding/skeleton_network_binding_base.h>
#include <ara/com/internal/binding/marshal.h>
#include "someip_network_binding_base.h"

namespace ara
{
namespace com
{
namespace internal
{
namespace binding
{
namespace someip
{

class SomeipSkeletonNetworkBinding : public ara::com::internal::binding::SkeletonNetworkBindingBase, public SomeipNetworkBindingBase
{
public:
    SomeipSkeletonNetworkBinding(std::string serviceName, uint16_t instanceId, MessageReceiveHandler handler);
    virtual ~SomeipSkeletonNetworkBinding();
    
    virtual void offerService();
    virtual void stopOfferService();
    virtual void init(std::shared_ptr<ServiceInterface> si);

private:
    bool sendResponse(const std::shared_ptr<Message> msg, const std::shared_ptr<std::vector<uint8_t>> payload);
    bool sendResponse(const std::shared_ptr<Message> msg);
    bool sendError(const std::shared_ptr<Message> msg, ReturnCode code = ReturnCode::E_NOT_OK);
    bool sendError(const std::shared_ptr<Message> msg, const std::shared_ptr<std::vector<uint8_t>> payload);
    bool sendEvent(std::string eventName, const std::shared_ptr<std::vector<uint8_t>> payload, bool is_field);
    
    std::shared_ptr<Serializer> getSerializer() override;
    std::shared_ptr<Deserializer> getDeserializer(const uint8_t *data, uint32_t size) override;
    
    std::shared_ptr<ApSomeipTransformationProps> m_transformationProps;
};

} // someip
} // binding
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_BINDING_SOMEIP_SOMEIP_SKELETON_NETWORK_BINDING_H_
