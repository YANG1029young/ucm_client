#ifndef ARA_PER_TRAITS_WRAPPER_H_
#define ARA_PER_TRAITS_WRAPPER_H_

#include <fstream>

namespace ara
{
namespace per
{
using pos_type = std::fstream::pos_type;
using off_type = std::fstream::off_type;
using int_type = std::fstream::int_type;
}  // namespace per
}  // namaspace ara

#endif  // ARA_PER_TRAITS_WRAPPER_H_
