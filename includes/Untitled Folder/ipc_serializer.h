/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_BINDING_IPC_IPC_SERIALIZER_H_
#define ARA_COM_INTERNAL_BINDING_IPC_IPC_SERIALIZER_H_

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <cmath>

#include <ara/com/internal/common.h>
#include <ara/com/internal/binding/common.h>
#include <ara/com/internal/binding/serializer.h>

#include <ara/core/optional.h>

namespace ara
{
namespace com
{
namespace internal
{
namespace binding
{
namespace ipc
{

class IpcSerializer : public ara::com::internal::binding::Serializer
{
public:
    IpcSerializer();
    virtual ~IpcSerializer();
    
    void Serialize(const bool& value) override;
    void Serialize(const uint8_t& value) override;
    void Serialize(const uint16_t& value) override;
    void Serialize(const uint32_t& value) override;
    void Serialize(const uint64_t& value) override;
    void Serialize(const int8_t& value) override;
    void Serialize(const int16_t& value) override;
    void Serialize(const int32_t& value) override;
    void Serialize(const int64_t& value) override;
    void Serialize(const float& value) override;
    void Serialize(const double& value) override;
    void Serialize(const std::string& value) override;
    
    void Serialize(uint16_t dataId, const ara::core::Optional<bool>& value) override;
    void Serialize(uint16_t dataId, const ara::core::Optional<uint8_t>& value) override;
    void Serialize(uint16_t dataId, const ara::core::Optional<uint16_t>& value) override;
    void Serialize(uint16_t dataId, const ara::core::Optional<uint32_t>& value) override;
    void Serialize(uint16_t dataId, const ara::core::Optional<uint64_t>& value) override;
    void Serialize(uint16_t dataId, const ara::core::Optional<int8_t>& value) override;
    void Serialize(uint16_t dataId, const ara::core::Optional<int16_t>& value) override;
    void Serialize(uint16_t dataId, const ara::core::Optional<int32_t>& value) override;
    void Serialize(uint16_t dataId, const ara::core::Optional<int64_t>& value) override;
    void Serialize(uint16_t dataId, const ara::core::Optional<float>& value) override;
    void Serialize(uint16_t dataId, const ara::core::Optional<double>& value) override;
    void Serialize(uint16_t dataId, const ara::core::Optional<std::string>& value) override;

private:
    void SerializeStructSize(const uint32_t& beginSize) override;
    void SerializeVectorSize(const uint32_t& beginSize) override;
    void SerializeArraySize(const uint32_t& beginSize) override;
    void SerializeMapSize(const uint32_t& beginSize) override;
    void SerializeStructTag(const uint16_t& dataId) override;
    void SerializeVectorTag(const uint16_t& dataId) override;
    void SerializeArrayTag(const uint16_t& dataId) override;
    void SerializeMapTag(const uint16_t& dataId) override;
    void SerializeTag(const uint16_t& tag) override;
};

} // ipc
} // binding
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_BINDING_IPC_IPC_SERIALIZER_H_
