#ifndef ARA_PER_READ_WRITE_ACCESSOR_H_
#define ARA_PER_READ_WRITE_ACCESSOR_H_

#include <cstddef>
#include <cstdint>
#include <string>

#include "read_accessor.h"
#include "write_accessor.h"

namespace ara
{
namespace per
{

/// ReadWriteAccessor is used to read and write file data.
///
/// For unformatted reading it provides the read() method and for formatted
/// reading it provides the operator>>
///
/// For unformatted writing it provides the write() method and for formatted
/// writing it provides the operator<<. It also provides the ability to force an
/// fsync to flush the buffer of the operating system to the storage.
///
class ReadWriteAccessor : public ReadAccessor, public WriteAccessor
{
public:
    virtual ~ReadWriteAccessor()
    {
    }
};

}  // namespace per
}  // namaspace ara

#endif  // ARA_PER_READ_WRITE_ACCESSOR_H_
