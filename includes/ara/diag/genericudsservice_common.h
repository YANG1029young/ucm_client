#ifndef ARA_DIAG_GENERICUDSSERVICE_COMMON_H
#define ARA_DIAG_GENERICUDSSERVICE_COMMON_H

#include <ara/com/types.h>
#include <ara/diag/impl_type_sidtype.h>
#include <ara/diag/impl_type_bytevectortype.h>
#include <ara/diag/impl_type_metainfotype.h>
#include <impl_type_uint8.h>
#include <impl_type_uint16.h>
#include <impl_type_string.h>

namespace ara
{
namespace diag
{

namespace GenericUDSService
{
	struct HandleMessageOutput
	{
		HandleMessageOutput(){}
		
		::ara::diag::ByteVectorType responseData;

		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(responseData);

		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(responseData))
{
	return false;
}

			
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

		

class SUBFUNCTION_NOT_SUPPORTED : public ara::com::ApplicationErrorException
{
public:
    SUBFUNCTION_NOT_SUPPORTED()
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
    std::uint8_t m_errorCode = 18;

    static constexpr const char* m_errorMessage = "SUBFUNCTION_NOT_SUPPORTED in GenericUDSService with ErrorCode: 18";

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

    static constexpr const char* m_errorMessage = "INCORRECT_MESSAGELENGTH_OR_INVALIDFORMAT in GenericUDSService with ErrorCode: 19";

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

    static constexpr const char* m_errorMessage = "CONDITIONS_NOT_CORRECT in GenericUDSService with ErrorCode: 34";

};
class REQUEST_SEQUENCE_ERROR : public ara::com::ApplicationErrorException
{
public:
    REQUEST_SEQUENCE_ERROR()
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
    std::uint8_t m_errorCode = 36;

    static constexpr const char* m_errorMessage = "REQUEST_SEQUENCE_ERROR in GenericUDSService with ErrorCode: 36";

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

    static constexpr const char* m_errorMessage = "REQUEST_OUT_OF_RANGE in GenericUDSService with ErrorCode: 49";

};
class SECURITY_ACCESS_DENIED : public ara::com::ApplicationErrorException
{
public:
    SECURITY_ACCESS_DENIED()
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

    static constexpr const char* m_errorMessage = "SECURITY_ACCESS_DENIED in GenericUDSService with ErrorCode: 51";

};
class GENERAL_PROGRAMMING_FAILURE : public ara::com::ApplicationErrorException
{
public:
    GENERAL_PROGRAMMING_FAILURE()
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
    std::uint8_t m_errorCode = 114;

    static constexpr const char* m_errorMessage = "GENERAL_PROGRAMMING_FAILURE in GenericUDSService with ErrorCode: 114";

};

} //namespace GenericUDSService
static void registerGenericUDSServiceErrors()
{
	static const ara::com::internal::ErrorEntry<ara::diag::GenericUDSService::SUBFUNCTION_NOT_SUPPORTED> s_SUBFUNCTION_NOT_SUPPORTED(18, "GenericUDSService");
static const ara::com::internal::ErrorEntry<ara::diag::GenericUDSService::INCORRECT_MESSAGELENGTH_OR_INVALIDFORMAT> s_INCORRECT_MESSAGELENGTH_OR_INVALIDFORMAT(19, "GenericUDSService");
static const ara::com::internal::ErrorEntry<ara::diag::GenericUDSService::CONDITIONS_NOT_CORRECT> s_CONDITIONS_NOT_CORRECT(34, "GenericUDSService");
static const ara::com::internal::ErrorEntry<ara::diag::GenericUDSService::REQUEST_SEQUENCE_ERROR> s_REQUEST_SEQUENCE_ERROR(36, "GenericUDSService");
static const ara::com::internal::ErrorEntry<ara::diag::GenericUDSService::REQUEST_OUT_OF_RANGE> s_REQUEST_OUT_OF_RANGE(49, "GenericUDSService");
static const ara::com::internal::ErrorEntry<ara::diag::GenericUDSService::SECURITY_ACCESS_DENIED> s_SECURITY_ACCESS_DENIED(51, "GenericUDSService");
static const ara::com::internal::ErrorEntry<ara::diag::GenericUDSService::GENERAL_PROGRAMMING_FAILURE> s_GENERAL_PROGRAMMING_FAILURE(114, "GenericUDSService");

}

}
}

#endif //ARA_DIAG_GENERICUDSSERVICE_COMMON_H
