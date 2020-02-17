#ifndef ARA_PER_WRITE_ACCESSOR_H_
#define ARA_PER_WRITE_ACCESSOR_H_

#include <cstddef>
#include <cstdint>
#include <string>

#include "basic_operations.h"

namespace ara
{
namespace per
{

/// WriteAccessor is used to write file data.
///
/// For unformatted writing it provides the write() method and for formatted
/// writing it provides the operator<<. It also provides the ability to force an
/// fsync to flush the buffer of the operating system to the storage.
///
class WriteAccessor : public virtual BasicOperations
{
public:
    virtual ~WriteAccessor()
    {
    }

    /// flush() and force the OS to write its data to persistent storage
    ///
    virtual void fsync() noexcept(true) = 0;

    /// Write n bytes from s.
    /// \return actual number of written bytes
    ///
    virtual pos_type write(char const* const s, std::size_t const n) noexcept(true) = 0;

    /// Write string
    ///
    virtual WriteAccessor& operator<<(std::string const& string) noexcept(true) = 0;

    /// Apply modifier like endl or flush (e.g. wacc << endl; )
    ///
    virtual WriteAccessor& operator<<(WriteAccessor& (*op)(WriteAccessor&)) noexcept(true) = 0;

    /// Pass write buffer to OS
    ///
    virtual void flush() noexcept(true) = 0;
};

/// Write newline to the file and call flush()
///
WriteAccessor& endl(WriteAccessor&);

/// Call flush()
///
WriteAccessor& flush(WriteAccessor&);

}  // namespace per
}  // namaspace ara

#endif  // ARA_PER_WRITE_ACCESSOR_H_
