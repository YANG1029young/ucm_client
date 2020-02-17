#ifndef ARA_PER_KEY_VALUE_STORAGE_H_
#define ARA_PER_KEY_VALUE_STORAGE_H_

#include <memory>
#include <string>
#include <vector>
#include <ara/per/macro_define.h>
#include "per_version.h"

namespace ara
{
namespace per
{

/// @brief Interface to the common key-value store functions.
///
class KeyValueStorage
{
public:
    /// @brief The status of a given operation
    ///
    enum class Status : uint8_t
    {
        kSuccess = 0,  ///< kSuccess, indicates that the value was successfully
        /// restored from the KVS-storage.
        kNotFound,  ///< kNotfound, requested key was not found
        kCheckSumError,  ///< kCheckSumError, the key-value pair was found, but the
        /// checksum of it is incorrect.
        kGeneralError,  ///< kGeneralError, any other failure.
        /// the default operation
        kDefault
    };
	

    explicit KeyValueStorage(const std::string& database) noexcept(false);

    /// \brief Returns a list of all keys explicitly set in the dataset.
    /// \return The list of available keys.
    /// @throws ara::per::physical_storage_error if out of memory while creating the return vector.
    /// @throws ara::per::logic_error if used in invalid state. (Eg. after std::move)
    ///
    std::vector<std::string> GetAllKeys() const noexcept(false);

    /// \brief Determines whether the \a key is explicitly set in the dataset.
    /// \param key The \p key to lookup.
    /// \return \a true if the \p key is part of the dataset, \a false otherwise.
    ///
    bool HasKey(const std::string& key) const noexcept;

    /// @brief Get the @p value assigned to given @p key.
    ///
    /// @param[in] key The @p key to look up.
    /// @param[out] value The @p value to be retrieved.
    ///
    /// @returns the status of the get request. See #Status for possible return values.
    ///
    template <class T>
    Status GetValue(const std::string& key, T& value) const noexcept(false);

    /// @brief Assign the @p value to the @p key.
    /// @param key The @p key to assign the @p value to.
    /// @param value The @p value to store.
    ///
    /// @throws ara::per::physical_storage_error is thrown if internal memory allocation fails.
    /// @throws ara::per::logic_error if used in invalid state. (Eg. after std::move)
    ///
    /// @returns the status of the set request. See #Status for possible return values.
    ///
    template <class T>
    Status SetValue(const std::string& key, const T& value) noexcept(false);

    /// \brief Removes the \p key and associated value.
    /// \param key The \p key to be removed.
    ///
    /// non-existing key has no effect.
    ///
    void RemoveKey(const std::string& key) noexcept;

    void RemoveAllKeys() noexcept;

    ///
    template <class T>
    Status GetKvsTypeStatus(const std::string& key, T value) const noexcept(false);

    /// \brief Synchronizes key-value pairs to the storage.
    /// Explicitly request the current state of the key-value-storage
    /// be saved to the non-volatile storage.
    /// The actual point of time, when the data is stored to the medium
    /// is implementation specific.
    ///
    ///  @throws ara::per::physical_storage_error
    ///  Any error during writing to the storage. The content of the storage cannot be trusted.
    ///  @throws ara::per::logic_error if used in invalid state. (Eg. after std::move)
    ///
    void SyncToStorage() const noexcept(false);

    virtual ~KeyValueStorage() noexcept;
	void  setLogLevel(int eVal);
	friend std::unique_ptr<KeyValueStorage> CreateKeyValueStorage(const std::string& database) noexcept;
private:
    class Impl;
    KeyValueStorage(const KeyValueStorage&) = delete;
    KeyValueStorage& operator=(const KeyValueStorage&) = delete;
    KeyValueStorage(KeyValueStorage&& src) noexcept;
    KeyValueStorage& operator=(KeyValueStorage&& src) noexcept;
    std::unique_ptr<Impl> m_pimpl;
	//LogExtend * m_KVSLog;
};  // class KeyValueStorage
std::unique_ptr<KeyValueStorage> CreateKeyValueStorage(const std::string& database) noexcept;
void RecoverKeyValueStorage(const std::string & database) noexcept;
void ResetKeyValueStorage(const std::string &database) noexcept;
}  // namespace per
}  // namespace ara
#endif  // ARA_PER_KEY_VALUE_STORAGE_H_
