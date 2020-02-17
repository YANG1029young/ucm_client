#ifndef ARA_PER_READ_ACCESSOR_H_
#define ARA_PER_READ_ACCESSOR_H_

#include <cstddef>
#include <cstdint>
#include <string>

#include "basic_operations.h"

namespace ara
{
namespace per
{

/// ReadAccessor is used to read file data.
///
/// For unformatted reading it provides the read() method and for formatted
/// reading it provides the operator>>
///
class ReadAccessor : public virtual BasicOperations
{
public:
    virtual ~ReadAccessor()
    {
    }

    /// @brief Peek the first char in the file buffer
    /// @return the char
    ///
    virtual int_type peek() noexcept(true) = 0;

    /// @brief Get the first char in the file buffer
    /// @return the char
    ///
    virtual int_type get() noexcept(true) = 0;

    /// Read n bytes into s.
    /// \return actual number of read bytes
    ///
    virtual pos_type read(char* const s, std::size_t const n) noexcept(true) = 0;

    /// Read the next string and store it in string
    ///
    virtual ReadAccessor& getline(std::string& string, char const delim) noexcept(true) = 0;

    /// Read the next string and store it in string
    ///
    virtual ReadAccessor& operator>>(std::string& string) noexcept(true) = 0;
	
	virtual int fileSize() noexcept(true) = 0;
};

/// Read the next string and store it in string
///
ReadAccessor& getline(ReadAccessor& ifstream, std::string& string, char const delim);

}  // namespace per
}  // namaspace ara

#endif  // ARA_PER_READ_ACCESSOR_H_
