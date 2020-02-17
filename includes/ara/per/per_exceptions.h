/// @file
/// @brief Persistency exceptions declaration

#ifndef ARA_PER_PER_EXCEPTIONS_H_
#define ARA_PER_PER_EXCEPTIONS_H_

#include <exception>
#include <string>

namespace ara
{
namespace per
{

/// @brief LogicErrorException exception for any logical, typically usage errors thrown
/// by the key-value-storage.
/// For example, requesting an int when the stored value is string, will
/// throw this exception.
///
class LogicErrorException : public std::exception
{
public:
    LogicErrorException(const std::string& message)
        : message_(message)
    {
    }

    virtual ~LogicErrorException()
    {
    }
    ///
    const char* what() const noexcept
    {
        return message_.c_str();
    }

private:
    std::string message_;
};

/// @brief StorageLocationNotFoundException exception, this exception will
/// be thrown if the requested storage, typically a file, but depending
/// on the implementation, could also be a service, is not found.
///
/// PSE51 requires no new files are created or deleted.
///
class StorageLocationNotFoundException : public std::exception
{
public:
    StorageLocationNotFoundException(const std::string& location)
        : message_(location)
    {
    }

    virtual ~StorageLocationNotFoundException()
    {
    }

    const char* what() const noexcept
    {
        return message_.c_str();
    }

private:
    std::string message_;
};

/// @brief PhysicalStorageErrorException exception, this exception signals any
/// severe error which might happen during the operation, such as
/// - out of memory
/// - writing/reading to the storage return an error
///
class PhysicalStorageErrorException : public std::exception
{
public:
    PhysicalStorageErrorException(const std::string& message)
        : message_(message)
    {
    }

    virtual ~PhysicalStorageErrorException()
    {
    }

    const char* what() const noexcept
    {
        return message_.c_str();
    }

private:
    std::string message_;
};

}  // namespace exception
}  // namespace per

#endif  // ARA_PER_PER_EXCEPTIONS_H_
