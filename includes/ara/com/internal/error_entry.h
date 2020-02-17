/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */
 
#ifndef ARA_COM_INTERNAL_ERROR_ENTRY_H_
#define ARA_COM_INTERNAL_ERROR_ENTRY_H_

#include <cstdint>
#include <memory>
#include <vector>
#include <functional>

#include <ara/com/exception.h>
#include <ara/com/internal/manifest.h>
#include <ara/com/internal/binding/serializer.h>
#include <ara/com/internal/binding/deserializer.h>

namespace ara
{
namespace com
{
namespace internal
{
const std::string COMMON_SERVICE_NAME_FOR_ERROR = "COMMON_SERVICE_NAME_FOR_ERROR";

using ErrorSerializeFunction = std::function<std::shared_ptr<std::vector<uint8_t>>(const ara::com::ApplicationErrorException& error,
    std::shared_ptr<ara::com::internal::binding::Serializer> serializer)>;

using ErrorDeserializeFunction = std::function<std::exception_ptr(std::shared_ptr<ara::com::internal::binding::Deserializer> deserializer)>;

class Factory
{
public:
    static void RegisterErrorSerialization(std::string serviceName, const std::string& errorTypeName, ErrorSerializeFunction serialize);
    static void RegisterErrorDeserialization(std::string serviceName, std::uint8_t errorCode, ErrorDeserializeFunction deserialize);
    static std::shared_ptr<std::vector<uint8_t>> ErrorSerialize(std::string serviceName, const ara::com::ApplicationErrorException& error,
        std::shared_ptr<ara::com::internal::binding::Serializer> serializer);
    static std::exception_ptr ErrorDeserialize(std::string serviceName, std::uint8_t errorCode,
        std::shared_ptr<ara::com::internal::binding::Deserializer> deserializer);
};

template <typename T>
class ErrorEntry
{
public:
    ErrorEntry(std::uint8_t errorCode, std::string serviceName = COMMON_SERVICE_NAME_FOR_ERROR)
    {
        std::string errorTypeName = typeid(T).name();
        
        Factory::RegisterErrorSerialization(serviceName, errorTypeName, [](const ara::com::ApplicationErrorException& error,
            std::shared_ptr<ara::com::internal::binding::Serializer> serializer){
            const T& t = static_cast<const T&>(error);
            t.Serialize(serializer.get());
            return serializer->GetPayload();
        });
        
        Factory::RegisterErrorDeserialization(serviceName, errorCode, [](
            std::shared_ptr<ara::com::internal::binding::Deserializer> deserializer){
            T error;
            error.Deserialize(deserializer.get());
            return std::make_exception_ptr(error);
        });
    }
};

}  // namespace internal
}  // namespace com
}  // namespace ara

#endif // ARA_COM_INTERNAL_DEFINITIONS_H_
