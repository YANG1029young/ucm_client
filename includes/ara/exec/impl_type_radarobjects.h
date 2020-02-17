#ifndef COM_HINGE_RADAR_IMPL_TYPE_RADAROBJECTS_H
#define COM_HINGE_RADAR_IMPL_TYPE_RADAROBJECTS_H

#include "impl_type_boolean.h"
#include "impl_type_bytearray.h"

namespace com
{
namespace hinge
{
namespace radar
{

struct RadarObjects
{	
	::Boolean active;
	::ByteArray objectVector;

	using IsEnumerableTag = void;
  
	template <typename T>
	void Serialize(T* serializer) const
	{
		serializer->Serialize(active);
		serializer->Serialize(objectVector);
	}

	template <typename T>
	bool Deserialize(T* deserializer)
	{
		if (!deserializer->Deserialize(active))
		{
			return false;
		}
	
		if (!deserializer->Deserialize(objectVector))
		{
			return false;
		}
	
		return true;
	}
};

} // namespace radar
} // namespace hinge
} // namespace com

#endif // COM_HINGE_RADAR_IMPL_TYPE_RADAROBJECTS_H

