/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_BINDING_IPC_IPC_DESERIALIZER_H_
#define ARA_COM_INTERNAL_BINDING_IPC_IPC_DESERIALIZER_H_

#include <cstdint>
#include <string>
#include <vector>
#include <string.h>
#include <map>
#include <cmath>

#include <ara/com/internal/common.h>
#include <ara/com/internal/binding/common.h>
#include <ara/com/internal/binding/deserializer.h>

#include <ara/core/optional.h>
#include <ara/core/variant.h>

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

class IpcDeserializer : public ara::com::internal::binding::Deserializer
{
public:
    IpcDeserializer(const uint8_t *data, uint32_t size);
    virtual ~IpcDeserializer();
    
    bool Deserialize(bool& value) override;
    bool Deserialize(uint8_t& value) override;
    bool Deserialize(uint16_t& value) override;
    bool Deserialize(uint32_t& value) override;
    bool Deserialize(uint64_t& value) override;
    bool Deserialize(int8_t& value) override;
    bool Deserialize(int16_t& value) override;
    bool Deserialize(int32_t& value) override;
    bool Deserialize(int64_t& value) override;
    bool Deserialize(float& value) override;
    bool Deserialize(double& value) override;
    bool Deserialize(std::string& value) override;
    
    int Deserialize(bool& value, const uint8_t *data, uint32_t size) override;
    int Deserialize(uint8_t& value, const uint8_t *data, uint32_t size) override;
    int Deserialize(uint16_t& value, const uint8_t *data, uint32_t size) override;
    int Deserialize(uint32_t& value, const uint8_t *data, uint32_t size) override;
    int Deserialize(uint64_t& value, const uint8_t *data, uint32_t size) override;
    int Deserialize(int8_t& value, const uint8_t *data, uint32_t size) override;
    int Deserialize(int16_t& value, const uint8_t *data, uint32_t size) override;
    int Deserialize(int32_t& value, const uint8_t *data, uint32_t size) override;
    int Deserialize(int64_t& value, const uint8_t *data, uint32_t size) override;
    int Deserialize(float& value, const uint8_t *data, uint32_t size) override;
    int Deserialize(double& value, const uint8_t *data, uint32_t size) override;
    int Deserialize(std::string& value, const uint8_t *data, uint32_t size) override;
    
    bool Deserialize(uint16_t dataId, ara::core::Optional<bool>& value) override;
    bool Deserialize(uint16_t dataId, ara::core::Optional<uint8_t>& value) override;
    bool Deserialize(uint16_t dataId, ara::core::Optional<uint16_t>& value) override;
    bool Deserialize(uint16_t dataId, ara::core::Optional<uint32_t>& value) override;
    bool Deserialize(uint16_t dataId, ara::core::Optional<uint64_t>& value) override;
    bool Deserialize(uint16_t dataId, ara::core::Optional<int8_t>& value) override;
    bool Deserialize(uint16_t dataId, ara::core::Optional<int16_t>& value) override;
    bool Deserialize(uint16_t dataId, ara::core::Optional<int32_t>& value) override;
    bool Deserialize(uint16_t dataId, ara::core::Optional<int64_t>& value) override;
    bool Deserialize(uint16_t dataId, ara::core::Optional<float>& value) override;
    bool Deserialize(uint16_t dataId, ara::core::Optional<double>& value) override;
    bool Deserialize(uint16_t dataId, ara::core::Optional<std::string>& value) override;

private:    
    bool DeserializeStructSize(uint32_t& size) override;
    bool DeserializeVectorSize(uint32_t& size) override;
    bool DeserializeArraySize(uint32_t& size) override;
    bool DeserializeMapSize(uint32_t& size) override;
    bool DeserializeTagStructSize(const uint16_t& tag, uint32_t& size) override;
    bool DeserializeTagVectorSize(const uint16_t& tag, uint32_t& size) override;
    bool DeserializeTagArraySize(const uint16_t& tag, uint32_t& size) override;
    bool DeserializeTagMapSize(const uint16_t& tag, uint32_t& size) override;
    bool CheckTag(const uint16_t& tag, const uint16_t& tagData) override;
};

} // ipc
} // binding
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_BINDING_IPC_IPC_DESERIALIZER_H_
