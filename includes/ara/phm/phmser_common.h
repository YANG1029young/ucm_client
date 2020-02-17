#ifndef ARA_PHM_PHMSER_COMMON_H
#define ARA_PHM_PHMSER_COMMON_H

#include <ara/com/types.h>
#include <impl_type_boolean.h>
#include <impl_type_double.h>
#include <impl_type_int16.h>
#include <impl_type_int32.h>
#include <impl_type_int8.h>
#include <impl_type_string.h>
#include <impl_type_uint16.h>
#include <impl_type_uint32.h>
#include <impl_type_uint8.h>
#include <ara/phm/impl_type_statusinfo.h>
#include <ara/phm/impl_type_eventinfo.h>

namespace ara
{
namespace phm
{

class PhmSer
{
public:
		struct ReportCheckpointOutput
	{
		ReportCheckpointOutput(){}
		
		::Boolean result;

		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(result);

		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(result))
{
	return false;
}

			
			return true;
		}
};
struct ReportHealthStatusOutput
	{
		ReportHealthStatusOutput(){}
		
		::Boolean result;

		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(result);

		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(result))
{
	return false;
}

			
			return true;
		}
};
struct GetLocalStatusOutput
	{
		GetLocalStatusOutput(){}
		
		::UInt8 status;

		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(status);

		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(status))
{
	return false;
}

			
			return true;
		}
};
struct GetGlobalStatusOutput
	{
		GetGlobalStatusOutput(){}
		
		::UInt8 status;

		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(status);

		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(status))
{
	return false;
}

			
			return true;
		}
};

};



static void registerErrors()
{
	
}

}
}

#endif //ARA_PHM_PHMSER_COMMON_H
