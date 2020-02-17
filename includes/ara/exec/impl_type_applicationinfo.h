#ifndef ARA_EXEC_IMPL_TYPE_APPLICATIONINFO_H
#define ARA_EXEC_IMPL_TYPE_APPLICATIONINFO_H

#include <ara/exec/impl_type_string.h>

namespace ara
{
namespace exec
{

struct ApplicationInfo
{
    ::ara::exec::String applicationPath;
    ::ara::exec::String applicationName;
    ::ara::exec::String manifestPath;
    
    using IsEnumerableTag = void;
    
    template <typename T>
	void Serialize(T* serializer) const
	{
		serializer->Serialize(applicationPath);
		serializer->Serialize(applicationName);
		serializer->Serialize(manifestPath);
	}

	template <typename T>
	bool Deserialize(T* deserializer)
	{
		if (!deserializer->Deserialize(applicationPath))
		{
			return false;
		}
		if (!deserializer->Deserialize(applicationName))
		{
			return false;
		}
		if (!deserializer->Deserialize(manifestPath))
		{
			return false;
		}
		return true;
	}
};

} // namespace exec
} // namespace ara

#endif // ARA_EXEC_IMPL_TYPE_APPLICATIONINFO_H



