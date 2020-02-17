#ifndef ARA_PER_PER_UPDATE_H_
#define ARA_PER_PER_UPDATE_H_
#include <memory>
#include <string>

namespace ara
{
namespace per
{
enum UpdateResult
{
    kSuccess = 0, //update success
    kNotFound,  //not found the cofig file
    kfailed //update failed
};
/// @brief private a interface to ucm update the user data.
/// 
/// For example, when app need to update, ucm can update the user data from persistency deployment config file by this class.
/// throw this exception.
///
class PersistencyUpdate
{
public:
    virtual ~PersistencyUpdate() = default;
    virtual UpdateResult updatePersistency(const std::string& path) noexcept(true) = 0;
	static std::unique_ptr<PersistencyUpdate> CreatePersistencyUpdate() noexcept(false);
};

}  // namespace per
}  // namespace ara

#endif  // ARA_PER_PER_UPDATE_H_
