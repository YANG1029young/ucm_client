#ifndef ARA_PER_BASIC_OPERATIONS_H_
#define ARA_PER_BASIC_OPERATIONS_H_

#include <cstddef>
#include <cstdint>
#include <exception>
#include <string>

#include "char_traits_wrapper.h"

namespace ara
{
namespace per
{

/// The basic operations have to be supported by all accessor interfaces. It
/// contains seeking and error checking.
///
class BasicOperations
{
public:
    /// specification of seek direction
    ///
    enum class SeekDirection : uint8_t
    {
        /// seek from the beginning
        kBeg,
        /// seek from the end
        kEnd,
        /// seek from the current position
        kCur,
        /// the invalid argument 
        kDefault
    };

    /// how the file shall be opened
    ///
    enum class OpenMode : uint8_t
    {
        /// append to the end
        kApp = 1 << 0,
        /// open as binary, will be opened as text if missing
        kBinary = 1 << 1,
        /// open for reading
        kIn = 1 << 2,
        /// open for writing
        kOut = 1 << 3,
        /// delete existing data at open
        kTrunc = 1 << 4,
        /// put seek pointer at the end
        kAte = 1 << 5,
	/// the invalid argument 
	kDefault =  1 << 6 
    };

    virtual ~BasicOperations()
    {
    }

    /// Get the current position in byte in the file from start
    ///
    virtual pos_type tell() noexcept(true) = 0;
    /// Set the position in byte in the file from start
    ///
    virtual void seek(pos_type const pos) noexcept(true) = 0;
    /// Set the position in byte in the file in relation to the current position
    ///
    virtual void seek(off_type const off, SeekDirection const dir) noexcept(true) = 0;

    /// no error happened
    ///
    virtual bool good() const noexcept(true) = 0;
    /// end of file reached
    ///
    virtual bool eof() const noexcept(true) = 0;
    /// error during operation
    ///
    virtual bool fail() const noexcept(true) = 0;
    /// read/writing error in i/o operation
    ///
    virtual bool bad() const noexcept(true) = 0;
    /// synonym of fail()
    ///
    virtual bool operator!() const noexcept(true) = 0;
    /// synonym of !fail()
    ///
    explicit virtual operator bool() const noexcept(true) = 0;
    /// clear error flags
    ///
    virtual void clear() noexcept(true) = 0;
};

/// Merge all Open_mode modifiers into on Open_mode object
///
BasicOperations::OpenMode operator|(BasicOperations::OpenMode const& left, BasicOperations::OpenMode const& right);

/// Create the intersection of both Open_mode objects
///
BasicOperations::OpenMode operator&(BasicOperations::OpenMode const& left, BasicOperations::OpenMode const& right);

}  // namespace per
}  // namaspace ara

#endif  // ARA_PER_BASIC_OPERATIONS_H_
