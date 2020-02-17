#ifndef ARA_PER_FILE_PROXY_ACCESSOR_FACTORY_H_
#define ARA_PER_FILE_PROXY_ACCESSOR_FACTORY_H_

#include <memory>
#include <string>
#include <vector>

#include "basic_operations.h"
#include "read_write_accessor.h"
#include "per_version.h"
namespace ara
{
namespace per
{
/// The FileProxyAccessorFactory creates objects to read or write memory blocks. Which
/// block is going to be read or written is specified by a key.
///
class FileProxyAccessorFactory
{
public:
    virtual ~FileProxyAccessorFactory()
    {
    }
    /// Returns a vector of available (file) identifiers within this proxy
    /// \return a vector of identifiers
    ///
    virtual std::vector<std::string> GetAllKeys() const noexcept(true) = 0;

    /// Deletes a file with the given identifier from this accessor.
    /// \param[in] key identifier of the file
    /// \return void
    ///
    virtual void DeleteKey(const std::string& key) noexcept(true) = 0;

    /// Query if a file with the given identifier is available in the proxy
    /// \param[in] key identifier of the file
    /// \return bool true if the file exists, false otherwise.
    ///
    virtual bool HasKey(const std::string& key) noexcept(true) = 0;

    /// Create accessor for reading and writing.
    /// \param[in] key identifier of the file
    /// \param[in] mode with which the file shall be opened
    /// \return Read_write_accessor associated to the file
    ///
    virtual std::unique_ptr<ReadWriteAccessor> CreateRWAccess(std::string const& key,
        BasicOperations::OpenMode const mode
        = BasicOperations::OpenMode::kOut | BasicOperations::OpenMode::kIn) noexcept(true)
        = 0;

    /// Create accessor for reading.
    /// \param[in] key identifier of the file
    /// \param[in] mode with which the file shall be opened
    /// \return Read_accessor associated to the file
    ///
    virtual std::unique_ptr<ReadAccessor> CreateReadAccess(std::string const& key,
        BasicOperations::OpenMode const mode = BasicOperations::OpenMode::kIn) noexcept(true)
        = 0;

    /// Create accessor for writing.
    /// \param[in] key identifier of the file
    /// \param[in] mode with which the file shall be opened
    /// \return Write_accessor associated to the file
    ///
    virtual std::unique_ptr<WriteAccessor> CreateWriteAccess(std::string const& key,
        BasicOperations::OpenMode const mode = BasicOperations::OpenMode::kOut) noexcept(true)
        = 0;
	
};

std::unique_ptr<FileProxyAccessorFactory> CreateFileAccessorFactory(std::string proxy) noexcept(false);
int RecoverFileProxy(std::string filePath) noexcept;
int ResetFileProxy(std::string filePath) noexcept;
}  // namespace per
}  // namespace ara
#endif  // ARA_PER_FILE_PROXY_ACCESSOR_FACTORY_H_
