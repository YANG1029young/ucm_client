
#ifndef ARA_CORE_SYSTEM_ERROR_H_
#define ARA_CORE_SYSTEM_ERROR_H_

#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "ara/core/exception.h"

#include <cerrno>

namespace ara
{
namespace core
{

enum class posix_errc : ErrorDomain::CodeType
{
    address_family_not_supported = EAFNOSUPPORT,
    address_in_use = EADDRINUSE,
    address_not_available = EADDRNOTAVAIL,
    already_connected = EISCONN,
    argument_list_too_long = E2BIG,
    argument_out_of_domain = EDOM,
    bad_address = EFAULT,
    bad_file_descriptor = EBADF,
    bad_message = EBADMSG,
    broken_pipe = EPIPE,
    connection_aborted = ECONNABORTED,
    connection_already_in_progress = EALREADY,
    connection_refused = ECONNREFUSED,
    connection_reset = ECONNRESET,
    cross_device_link = EXDEV,
    destination_address_required = EDESTADDRREQ,
    device_or_resource_busy = EBUSY,
    directory_not_empty = ENOTEMPTY,
    executable_format_error = ENOEXEC,
    file_exists = EEXIST,
    file_too_large = EFBIG,
    filename_too_long = ENAMETOOLONG,
    function_not_supported = ENOSYS,
    host_unreachable = EHOSTUNREACH,
    identifier_removed = EIDRM,
    illegal_byte_sequence = EILSEQ,
    inappropriate_io_control_operation = ENOTTY,
    interrupted = EINTR,
    invalid_argument = EINVAL,
    invalid_seek = ESPIPE,
    io_error = EIO,
    is_a_directory = EISDIR,
    message_size = EMSGSIZE,
    network_down = ENETDOWN,
    network_reset = ENETRESET,
    network_unreachable = ENETUNREACH,
    no_buffer_space = ENOBUFS,
    no_child_process = ECHILD,
    no_link = ENOLINK,
    no_lock_available = ENOLCK,
    no_message_available = ENODATA,
    no_message = ENOMSG,
    no_protocol_option = ENOPROTOOPT,
    no_space_on_device = ENOSPC,
    no_stream_resources = ENOSR,
    no_such_device_or_address = ENXIO,
    no_such_device = ENODEV,
    no_such_file_or_directory = ENOENT,
    no_such_process = ESRCH,
    not_a_directory = ENOTDIR,
    not_a_socket = ENOTSOCK,
    not_a_stream = ENOSTR,
    not_connected = ENOTCONN,
    not_enough_memory = ENOMEM,
    not_supported = ENOTSUP,
    operation_canceled = ECANCELED,
    operation_in_progress = EINPROGRESS,
    operation_not_permitted = EPERM,
    operation_not_supported = EOPNOTSUPP,
    operation_would_block = EWOULDBLOCK,
    owner_dead = EOWNERDEAD,
    permission_denied = EACCES,
    protocol_error = EPROTO,
    protocol_not_supported = EPROTONOSUPPORT,
    read_only_file_system = EROFS,
    resource_deadlock_would_occur = EDEADLK,
    resource_unavailable_try_again = EAGAIN,
    result_out_of_range = ERANGE,
    state_not_recoverable = ENOTRECOVERABLE,
    stream_timeout = ETIME,
    text_file_busy = ETXTBSY,
    timed_out = ETIMEDOUT,
    too_many_files_open_in_system = ENFILE,
    too_many_files_open = EMFILE,
    too_many_links = EMLINK,
    too_many_symbolic_link_levels = ELOOP,
    value_too_large = EOVERFLOW,
    wrong_protocol_type = EPROTOTYPE,
};

class PosixException : public ara::core::Exception
{
public:
    PosixException(ErrorCode&& err)
        : ara::core::Exception(std::move(err))
    {
    }
};

inline std::ostream& operator<<(std::ostream& out, PosixException const& ex)
{
    return (out << "PosixException: " << ex.Error() << " (" << ex.what() << ")");
}

class PosixErrorDomain : public ErrorDomain
{
    constexpr static ErrorDomain::IdType kId = 0x123456;

public:
    using Errc = posix_errc;
    using Exception = PosixException;

    constexpr PosixErrorDomain() noexcept
        : ErrorDomain(kId)
    {
    }

    char const* Name() const noexcept override
    {
        return "System";
    }

    char const* Message(ErrorDomain::CodeType errorCode) const noexcept override
    {
        Errc const code = static_cast<Errc>(errorCode);
        switch (code) {
        case Errc::address_family_not_supported:
            return "Address family not supported";
        case Errc::address_in_use:
            return "Address in use";
        case Errc::address_not_available:
            return "Address not available";
        case Errc::already_connected:
            return "Transport endpoint is already connected";
        case Errc::argument_list_too_long:
            return "Argument list too long";
        case Errc::argument_out_of_domain:
            return "Argument out of domain";
        case Errc::bad_address:
            return "Bad address";
        case Errc::bad_file_descriptor:
            return "Bad file descriptor";
        case Errc::bad_message:
            return "Bad message";
        case Errc::broken_pipe:
            return "Broken pipe";
        case Errc::connection_aborted:
            return "Connection aborted";
        case Errc::connection_already_in_progress:
            return "Connection already in progress";
        case Errc::connection_refused:
            return "Connection refused";
        case Errc::connection_reset:
            return "Connection reset";
        case Errc::cross_device_link:
            return "Cross-device link";
        case Errc::destination_address_required:
            return "Destination address required";
        case Errc::device_or_resource_busy:
            return "Device or resource busy";
        case Errc::directory_not_empty:
            return "Directory not empty";
        case Errc::executable_format_error:
            return "Executable format error";
        case Errc::file_exists:
            return "File exists";
        case Errc::file_too_large:
            return "File too large";
        case Errc::filename_too_long:
            return "File name too long";
        case Errc::function_not_supported:
            return "Function not supported";
        case Errc::host_unreachable:
            return "Host unreachable";
        case Errc::identifier_removed:
            return "Identifier removed";
        case Errc::illegal_byte_sequence:
            return "Illegal byte sequence";
        case Errc::inappropriate_io_control_operation:
            return "Inappropriate I/O control operation";
        case Errc::interrupted:
            return "Interrupted system call";
        case Errc::invalid_argument:
            return "Remote I/O error";
        case Errc::invalid_seek:
            return "Invalid seek";
        case Errc::io_error:
            return "Remote I/O error";
        case Errc::is_a_directory:
            return "Is a directory";
        case Errc::message_size:
            return "Message too long";
        case Errc::network_down:
            return "Network is down";
        case Errc::network_reset:
            return "Network dropped connection because of reset";
        case Errc::network_unreachable:
            return "Network is unreachable";
        case Errc::no_buffer_space:
            return "No buffer space available";
        case Errc::no_child_process:
            return "No child process";
        case Errc::no_link:
            return "Link has been severed";
        case Errc::no_lock_available:
            return "No record locks available";
        case Errc::no_message_available:
            return "No data available";
        case Errc::no_message:
            return "No message of desired type";
        case Errc::no_protocol_option:
            return "Protocol not available";
        case Errc::no_space_on_device:
            return "No space left on device";
        case Errc::no_stream_resources:
            return "Device not a stream";
        case Errc::no_such_device_or_address:
            return "No such device or address";
        case Errc::no_such_device:
            return "No such device";
        case Errc::no_such_file_or_directory:
            return "No such file or directory";
        case Errc::no_such_process:
            return "No such process";
        case Errc::not_a_directory:
            return "Not a directory";
        case Errc::not_a_socket:
            return "Socket operation on non-socket";
        case Errc::not_a_stream:
            return "Device not a stream";
        case Errc::not_connected:
            return "Transport endpoint is not connected";
        case Errc::not_enough_memory:
            return "Out of memory";
        // case Errc::not_supported:
        //    return "Not supported";
        case Errc::operation_canceled:
            return "Operation canceled";
        case Errc::operation_in_progress:
            return "Operation in progress";
        case Errc::operation_not_permitted:
            return "Operation not permitted";
        case Errc::operation_not_supported:
            return "Operation not supported";
        case Errc::operation_would_block:
            return "Operation would block";
        case Errc::owner_dead:
            return "Owner dead";
        case Errc::permission_denied:
            return "Permission denied";
        case Errc::protocol_error:
            return "Protocol error";
        case Errc::protocol_not_supported:
            return "Protocol not supported";
        case Errc::read_only_file_system:
            return "Read-only file system";
        case Errc::resource_deadlock_would_occur:
            return "Resource deadlock would occur";
        // case Errc::resource_unavailable_try_again:
        //    return "Resource unavailable, try again";
        case Errc::result_out_of_range:
            return "Result out of range";
        case Errc::state_not_recoverable:
            return "State not recoverable";
        case Errc::stream_timeout:
            return "Stream timeout";
        case Errc::text_file_busy:
            return "Text file busy";
        case Errc::timed_out:
            return "Time out";
        case Errc::too_many_files_open_in_system:
            return "Too many files open in system";
        case Errc::too_many_files_open:
            return "Too many open files";
        case Errc::too_many_links:
            return "Too many links";
        case Errc::too_many_symbolic_link_levels:
            return "Too many symbolic links encountered";
        case Errc::value_too_large:
            return " Value too large";
        case Errc::wrong_protocol_type:
            return "Wrong protocol type";
        default:
            return "Unknown error";
        }
    }

    void ThrowAsException(ErrorCode const& errorCode) const noexcept(false) override
    {
        ThrowOrTerminate<Exception>(errorCode);
    }
};

namespace internal
{
constexpr PosixErrorDomain g_posixErrorDomain;
}

inline constexpr ErrorDomain const& GetPosixDomain()
{
    return internal::g_posixErrorDomain;
}

inline constexpr ErrorCode MakeErrorCode(PosixErrorDomain::Errc code,
    ErrorDomain::SupportDataType data,
    char const* message)
{
    return ErrorCode(static_cast<ErrorDomain::CodeType>(code), GetPosixDomain(), data, message);
}

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_SYSTEM_ERROR_H_
