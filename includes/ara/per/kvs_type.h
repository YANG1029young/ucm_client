#ifndef ARA_PER_KVSTYPE_KVS_TYPE_H_
#define ARA_PER_KVSTYPE_KVS_TYPE_H_

#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace ara
{
namespace per
{

/// @brief A container class for storing any of the POD types, plus some additional complex types.


class KvsType
{
public:
    /// @brief Status of the KVS access.
    enum class Status : uint8_t
    {
        kSuccess = 0,  ///< kSuccess, indicates that the value was successfully restored from the KVS-storage.
        kNotFound,  ///< kNotfound, requested key was not found
        kCheckSumError,  ///< kIntegrityError, the key-value pair was found, but the checksum of it is incorrect.
        kGeneralError,  ///< kGeneralError, any other failure.
        kDefault
    };

    /// @brief Supported types.
    enum class Type : uint8_t
    {
        kNotSupported = 0,
        kFloat,
        kDouble,
        kSInt8,
        kSInt16,
        kSInt32,
        kSInt64,
        kUInt8,
        kUInt16,
        kUInt32,
        kUInt64,
        kString,
        kBinary,
        kBoolean,
        kObject,
        kNotSet
    };

    /// @brief Copy constructor.
    ///
    /// @param src the source KvsType object that shall be copied
    KvsType(const KvsType& src) noexcept(false);

    /// @brief Copy assignment operator.
    ///
    /// @param src the source KvsType object that shall be copied
    /// @returns a copy of given KvsType object
    KvsType& operator=(const KvsType& src) noexcept(false);

    /// @brief Move constructor.
    KvsType(KvsType&&) noexcept;

    /// @brief Move assignment operator.
    ///
    /// @returns the moved-to object
    KvsType& operator=(KvsType&&) noexcept;

    /// @brief Destructor.
    virtual ~KvsType() noexcept;

    /// @brief Basic constructor which creates a "not found"-state object.
    KvsType() noexcept(false);

    // ####################################
    // # Constructors for supported types #
    // ####################################

    /// @brief Constructor for bool.
    ///
    /// @param value the initial bool value
    KvsType(bool value) noexcept(false);

    /// @brief Constructor for 8-bit signed integer.
    ///
    /// @param value the initial int8_t value
    KvsType(int8_t value) noexcept(false);

    /// @brief Constructor for 16-bit signed integer.
    ///
    /// @param value the initial int16_t value
    KvsType(int16_t value) noexcept(false);

    /// @brief Constructor for 32-bit signed integer.
    ///
    /// @param value the initial int32_t value
    KvsType(int32_t value) noexcept(false);

    /// @brief Constructor for 64-bit signed integer.
    ///
    /// @param value the initial int64_t value
    KvsType(int64_t value) noexcept(false);

    /// @brief Constructor for 8-bit unsigned integer.
    ///
    /// @param value the initial uint8_t value
    KvsType(uint8_t value) noexcept(false);

    /// @brief Constructor for 16-bit unsigned integer.
    ///
    /// @param value the initial uint16_t value
    KvsType(uint16_t value) noexcept(false);

    /// @brief Constructor for 32-bit unsigned integer.
    ///
    /// @param value the initial uint32_t value
    KvsType(uint32_t value) noexcept(false);

    /// @brief Constructor for 64-bit unsigned integer.
    ///
    /// @param value the initial uint64_t value
    KvsType(uint64_t value) noexcept(false);

    /// @brief Constructor for float.
    ///
    /// @param value the initial float value
    KvsType(float value) noexcept(false);

    /// @brief Constructor for double.
    ///
    /// @param value the initial double value
    KvsType(double value) noexcept(false);

    /// @brief Constructor for std::string.
    ///
    /// @param value the initial string value
    KvsType(const std::string& value) noexcept(false);

    /// @brief Constructor for const char*.
    ///
    /// @param value the initial char value
    KvsType(const char* value) noexcept(false);

    /// @brief Generic constructor for any POD-type.
    ///
    /// @param data the address of the the data to be stored
    /// @param len the lenght of the data to be stored
    ///
    /// @deprecated Usage of this is not safe an not recommended!
    /// As there are some users for this type, this is still here.
    KvsType(void* data, std::size_t len) noexcept(false);

    /// @brief Accesses the internal presentation as a boolean
    ///
    /// @throws std::logic_error is thrown if the requested conversion is not supported
    /// @returns the internal presentation as a boolean
    bool GetBool() const noexcept(false);

    /// @brief Accesses the internal presentation as integer.
    ///
    /// @throws std::logic_error is thrown if the requested conversion is not supported
    /// @returns the internal presentation as integer
    int32_t GetSInt() const noexcept(false);

    /// @brief Accesses the internal presentation as 64-bit integer.
    ///
    /// @throws std::logic_error is thrown if the requested conversion is not supported
    /// @returns the internal presentation as 64-bit integer
    int64_t GetSInt64() const noexcept(false);

    /// @brief Accesses the internal presentation as unsigned integer.
    ///
    /// @throws std::logic_error is thrown if the requested conversion is not supported
    /// @returns the internal presentation as unsigned integer
    uint32_t GetUInt() const noexcept(false);

    /// @brief Accesses the internal presentation as 64-bit unsigned integer.
    ///
    /// @throws std::logic_error is thrown if the requested conversion is not supported
    /// @returns the internal presentation as 64-bit unsigned integer
    uint64_t GetUInt64() const noexcept(false);

    /// @brief Accesses the internal presentation as float.
    ///
    /// @throws std::logic_error is thrown if the requested conversion is not supported
    /// @returns the internal presentation as float
    float GetFloat() const noexcept(false);

    /// @brief Accesses the internal presentation as double.
    ///
    /// @throws std::logic_error is thrown if the requested conversion is not supported
    /// @returns the internal presentation as double
    double GetDouble() const noexcept(false);

    /// @brief Accesses the internal presentation as string.
    ///
    /// @throws std::logic_error is thrown if the requested conversion is not supported
    /// @returns the internal presentation as string
    std::string GetString() const noexcept(false);

    /// @brief Restores the stored value to the given memory address.
    ///
    /// Usage example:
    ///
    /// @code
    /// struct MyStructureWithPodData { .... };
    /// KeyValueStorage db("databasename.json");
    ///
    /// MyStructureWithPodData mystruct;
    ///
    /// KvsType binary = db.getValue("my-binary-key");
    /// binary.GetBinary(&mystruct, sizeof(mystruct));
    /// // Error handling missing from the example.
    /// @endcode
    ///
    /// @param data Pointer to the memory, where the data is to be restored to.
    /// @param len number of bytes to be restored.
    /// @throws std::logic_error is thrown if the requested conversion is not supported.
    void GetBinary(void* data, std::size_t len) noexcept(false);

    /// @brief Returns a vector of requested type.
    ///
    /// Supported types are [integral, floating point, std::string and KVSType].
    /// Restores the items in same order as they were saved with StoreArray
    /// This is specialized for integer types and booleans.
    ///
    /// @tparam T the expected underlying type of the array to be returned
    /// @returns a vector of the requested type
    /// @throws std::logic_error is thrown if the requested conversion is not supported.
    /// @throws ara::per::physical_storage_error is thrown if internal memory allocation fails.
    template <class T, typename std::enable_if<std::is_integral<T>::value, T>::type* = nullptr>
    std::vector<T> GetArray() noexcept(false)
    {
        std::vector<T> return_vector;
		bool bSinType = false;
		bool bBoolType = false;
        ResetArrayItemGetter();
        if (std::is_signed<T>::value)
		{
			bSinType = true;
        }
		else if (std::is_same<T, bool>::value)
		{
			bBoolType = true;
        } 
		
        for (std::size_t i = 0; i < this->GetNumberOfArrayItems(); i++)
		{
			try 
			{
            	KvsType tmp = this->GetNextArrayItem();
				if (true == bSinType)
				{
					return_vector.push_back(static_cast<T>(tmp.GetSInt64()));
				}
				else if (true == bBoolType)
				{
					return_vector.push_back(static_cast<T>(tmp.GetBool()));
				}
				else
				{
            		return_vector.push_back(static_cast<T>(tmp.GetUInt64()));
				}
			}
			catch (const std::logic_error & e)
			{
				std::cout<<e.what()<<std::endl;
			}
        }
        return return_vector;
    }

    /// @brief GetArray() specialized for floating point types.
    template <class T, typename std::enable_if<std::is_floating_point<T>::value, T>::type* = nullptr>
    std::vector<T> GetArray() noexcept(false)
    {
        std::vector<T> return_vector;
        ResetArrayItemGetter();
        for (std::size_t i = 0; i < this->GetNumberOfArrayItems(); i++)
		{
			try
			{
            	KvsType tmp = this->GetNextArrayItem();
            	return_vector.push_back(static_cast<T>(tmp.GetDouble()));
			}
			catch (const std::logic_error & e)
			{
				std::cout<<e.what()<<std::endl;
			}
        }
        return return_vector;
    }

    /// @brief GetArray() specialized for KvsType.
    template <class T, typename std::enable_if<std::is_same<T, KvsType>::value, T>::type* = nullptr>
    std::vector<T> GetArray() noexcept(false)
    {
        std::vector<T> return_vector;
        ResetArrayItemGetter();

        for (std::size_t i = 0; i < this->GetNumberOfArrayItems(); i++)
		{
			try
			{
            	KvsType tmp = this->GetNextArrayItem();
            	return_vector.push_back(std::move(tmp));
			}
			catch (const std::logic_error & e)
			{
				std::cout<<e.what()<<std::endl;
			}
        }
        return return_vector;
    }

    /// @brief GetArray() specialized for std::string.
    template <class T, typename std::enable_if<std::is_same<T, std::string>::value, T>::type* = nullptr>
    std::vector<T> GetArray() noexcept(false)
    {
        std::vector<T> return_vector;
        ResetArrayItemGetter();
        for (std::size_t i = 0; i < this->GetNumberOfArrayItems(); i++) {
			try
			{
	            KvsType tmp = this->GetNextArrayItem();
	            return_vector.push_back(tmp.GetString());
			}
			catch (const std::logic_error & e)
			{
				std::cout<<e.what()<<std::endl;
			}
        }
        return return_vector;
    }

    /// @brief Adds an element to the internal array container.
    ///
    /// @param kvs the element to be added
    void AddArrayItem(const KvsType& kvs) noexcept(false);

    /// @brief Accesses the key of the KVS-pair object.
    ///
    /// @returns the key of the KVS-pair object
    std::string GetKey() const noexcept;

    /// @brief Accesses the status of the KVS-pair object.
    ///
    /// @returns the status of the KVS-pair object
    /// @note The status should be checked before trying to use the stored KVS-pair.
    Status GetStatus() const noexcept;
	void SetStatus(const KvsType::Status& status) noexcept;

    /// @brief Accesses the type of the value stored to the internal presentation.
    ///
    /// @returns the type of the value stored to the internal presentation
    Type GetType() const noexcept;

    /// @brief Convenience function for checking if the internal type is any of
    /// the signed integer types.
    ///
    /// @returns whether the internal type is a signed integer
    /// @note Types might be 8,16,32, or 64bit.
    bool IsSignedInteger() const noexcept;

    /// @brief Convenience function for checking if the internal type is any of
    /// the unsigned integer types.
    ///
    /// @returns whether the internal type is an unsigned integer
    /// @note Types might be 8,16,32, or 64bit.
    bool IsUnsignedInteger() const noexcept;

    /// @brief Logs the internal variables of the object.
    ///
    /// This is useful only for debugging the KVSType.
    ///
    /// @note The ara::log log level must be set to kDebug for this to be visible in the logs.
    void LogState() const noexcept;

    /// @brief Sets the key of the KVS-pair object.
    ///
    /// @param name the key to be used for the KVS-pair object
    void SetKey(const std::string& name) noexcept;

    /// @brief Stores an array of [integer, floating point, or KvsType].
    ///
    /// The elements are stored in the iteration order to the KVS internal data structure.
    ///
    /// @tparam Array the underlying type of the array to be stored
    /// @param array the actual Array that is to be stored
    /// @throws std::logic_error is thrown if the requested conversion is not supported.
    /// @throws ara::per::physical_storage_error is thrown if internal memory allocation fails.
    /// @note The container must be iterable!
    template <class Array>
    void StoreArray(const Array& array) noexcept(false)
    {
        static_assert((std::is_integral<typename Array::value_type>::value)
                || (std::is_floating_point<typename Array::value_type>::value)
                || (std::is_same<typename Array::value_type, std::string>::value)
                || (std::is_same<typename Array::value_type, KvsType>::value),
            "Storing of array template supports only iterable containers, which contain  "
            "one of fundamental types (int,float, etc.) or std::strings or KvsType-objects");

        auto current = array.cbegin();
        auto end = array.cend();

        std::size_t counter = 0;
        while (current != end) {
            // If already have an iterable container of KvsType objects, just
            // pass them.
            if (std::is_same<typename Array::value_type, KvsType>::value) {
                this->AddArrayItem(*current);
            } else {
                // Otherwise, construct KVSType-object from the value
                KvsType temp(*current);
                // unfortunately this is necessary for successful validation against schema
                temp.SetKey(std::to_string(counter++));
                // Add it to the internal presentation
                this->AddArrayItem(temp);
            }
            current++;
        }
    }

    /// @brief Constructs a KVSObject from a string.
    ///
    /// This is implementation specific.
    /// For the demonstrator, the  example chosen is JSON.
    ///
    /// @param kvsStrObj the string representation of a KvsType
    /// @returns the deserialized KvsType
    /// @throws std::logic_error is thrown if the KVSType cannot be constructed from the input.
    static KvsType DeSerializeKvsData(const std::string& kvsStrObj, bool isUpdate) noexcept(false);

    /// @brief Serializes a KVSObject to a string.
    ///
    /// This is implementation specific.
    /// For the demonstrator, the  example chosen is JSON.
    ///
    /// @returns the string representation of this object.
    std::string SerializeKvsData() noexcept;
public:
	
	/// @brief Application specific implementation.
	class Impl;

	/// @brief Pointer to the actual implementation.
	std::unique_ptr<Impl> impl_ptr_;

private:
    /// @brief Implementation specific serialization helper class.
    ///
    /// The actual serialization support depends on the internal implementation
    /// of Impl-class.
    friend class InternalAccess;

    /// @brief Accesses the next item in the array.
    ///
    /// @returns the next item in the array
    KvsType GetNextArrayItem() noexcept(false);

    /// @brief Accesses the number of items currently stored.
    ///
    /// @returns the number of items currently stored
    std::size_t GetNumberOfArrayItems() noexcept(false);

    /// @brief Resets the kvs array getter.
    ///
    /// The next value will be the first in the internal data structure
    void ResetArrayItemGetter() noexcept(false);
};

template <typename... Args>
KvsType CreateKvsType(std::string const& key, Args&&... args)
{
    KvsType result(std::forward<Args>(args)...);
    result.SetKey(key);
    return result;
}

}  // namespace per
}  // namespace ara

#endif  // ARA_PER_KVSTYPE_KVS_TYPE_H_
