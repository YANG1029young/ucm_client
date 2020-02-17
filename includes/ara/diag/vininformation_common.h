#ifndef ARA_DIAG_VININFORMATION_COMMON_H
#define ARA_DIAG_VININFORMATION_COMMON_H

#include <ara/com/types.h>
#include <ara/diag/impl_type_metainfotype.h>
#include <ara/diag/impl_type_vintype.h>
#include <impl_type_bytearray.h>
#include <impl_type_uint8.h>
#include <impl_type_string.h>

namespace ara
{
namespace diag
{

namespace VINInformation
{
	struct ReadOutput
	{
		ReadOutput(){}
		
		::ara::diag::VINType vin;

		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(vin);

		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(vin))
{
	return false;
}

			
			return true;
		}
};
struct WriteOutput
	{
		WriteOutput(){}
		
		
		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			
		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			
			
			return true;
		}
};
struct CancelOutput
	{
		CancelOutput(){}
		
		
		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			
		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			
			
			return true;
		}
};

		

class INCORRECT_MESSAGELENGTH_OR_INVALIDFORMAT : public ara::com::ApplicationErrorException
{
public:
    INCORRECT_MESSAGELENGTH_OR_INVALIDFORMAT()
    	:ara::com::ApplicationErrorException()
    {
    }

    const char *what() const noexcept final override { return m_errorMessage; }

    using IsEnumerableTag = void;
    
    template<typename F>
    void enumerate(F& fun)
    {
        fun(m_errorCode);
    }
    template<typename F>
    void enumerate(F& fun) const
    {
        fun(m_errorCode);
    }
    
    template <typename T>
	void Serialize(T* serializer) const
	{
		serializer->Serialize(m_errorCode);
	}
	
	template <typename T>
	bool Deserialize(T* deserializer)
	{
		if (!deserializer->Deserialize(m_errorCode))
		{
			return false;
		}
		
		return true;
	}

private:
    std::uint8_t m_errorCode = 19;

    static constexpr const char* m_errorMessage = "INCORRECT_MESSAGELENGTH_OR_INVALIDFORMAT in VINInformation with ErrorCode: 19";

};
class CONDITIONS_NOT_CORRECT : public ara::com::ApplicationErrorException
{
public:
    CONDITIONS_NOT_CORRECT()
    	:ara::com::ApplicationErrorException()
    {
    }

    const char *what() const noexcept final override { return m_errorMessage; }

    using IsEnumerableTag = void;
    
    template<typename F>
    void enumerate(F& fun)
    {
        fun(m_errorCode);
    }
    template<typename F>
    void enumerate(F& fun) const
    {
        fun(m_errorCode);
    }
    
    template <typename T>
	void Serialize(T* serializer) const
	{
		serializer->Serialize(m_errorCode);
	}
	
	template <typename T>
	bool Deserialize(T* deserializer)
	{
		if (!deserializer->Deserialize(m_errorCode))
		{
			return false;
		}
		
		return true;
	}

private:
    std::uint8_t m_errorCode = 34;

    static constexpr const char* m_errorMessage = "CONDITIONS_NOT_CORRECT in VINInformation with ErrorCode: 34";

};
class Security_ACCESS_DENIED : public ara::com::ApplicationErrorException
{
public:
    Security_ACCESS_DENIED()
    	:ara::com::ApplicationErrorException()
    {
    }

    const char *what() const noexcept final override { return m_errorMessage; }

    using IsEnumerableTag = void;
    
    template<typename F>
    void enumerate(F& fun)
    {
        fun(m_errorCode);
    }
    template<typename F>
    void enumerate(F& fun) const
    {
        fun(m_errorCode);
    }
    
    template <typename T>
	void Serialize(T* serializer) const
	{
		serializer->Serialize(m_errorCode);
	}
	
	template <typename T>
	bool Deserialize(T* deserializer)
	{
		if (!deserializer->Deserialize(m_errorCode))
		{
			return false;
		}
		
		return true;
	}

private:
    std::uint8_t m_errorCode = 51;

    static constexpr const char* m_errorMessage = "Security_ACCESS_DENIED in VINInformation with ErrorCode: 51";

};
class REQUEST_OUT_OF_RANGE : public ara::com::ApplicationErrorException
{
public:
    REQUEST_OUT_OF_RANGE()
    	:ara::com::ApplicationErrorException()
    {
    }

    const char *what() const noexcept final override { return m_errorMessage; }

    using IsEnumerableTag = void;
    
    template<typename F>
    void enumerate(F& fun)
    {
        fun(m_errorCode);
    }
    template<typename F>
    void enumerate(F& fun) const
    {
        fun(m_errorCode);
    }
    
    template <typename T>
	void Serialize(T* serializer) const
	{
		serializer->Serialize(m_errorCode);
	}
	
	template <typename T>
	bool Deserialize(T* deserializer)
	{
		if (!deserializer->Deserialize(m_errorCode))
		{
			return false;
		}
		
		return true;
	}

private:
    std::uint8_t m_errorCode = 49;

    static constexpr const char* m_errorMessage = "REQUEST_OUT_OF_RANGE in VINInformation with ErrorCode: 49";

};

} //namespace VINInformation
static void registerVINInformationErrors()
{
	static const ara::com::internal::ErrorEntry<ara::diag::VINInformation::INCORRECT_MESSAGELENGTH_OR_INVALIDFORMAT> s_INCORRECT_MESSAGELENGTH_OR_INVALIDFORMAT(19, "VINInformation");
static const ara::com::internal::ErrorEntry<ara::diag::VINInformation::CONDITIONS_NOT_CORRECT> s_CONDITIONS_NOT_CORRECT(34, "VINInformation");
static const ara::com::internal::ErrorEntry<ara::diag::VINInformation::Security_ACCESS_DENIED> s_Security_ACCESS_DENIED(51, "VINInformation");
static const ara::com::internal::ErrorEntry<ara::diag::VINInformation::REQUEST_OUT_OF_RANGE> s_REQUEST_OUT_OF_RANGE(49, "VINInformation");

}

}
}

#endif //ARA_DIAG_VININFORMATION_COMMON_H
