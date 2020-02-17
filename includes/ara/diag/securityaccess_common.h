#ifndef ARA_DIAG_SECURITYACCESS_COMMON_H
#define ARA_DIAG_SECURITYACCESS_COMMON_H

#include <ara/com/types.h>
#include <ara/diag/impl_type_bytevectortype.h>
#include <ara/diag/impl_type_metainfotype.h>
#include <ara/diag/impl_type_keycompareresulttype.h>
#include <impl_type_uint8.h>
#include <impl_type_uint16.h>
#include <impl_type_string.h>

namespace ara
{
namespace diag
{

namespace SecurityAccess
{
	struct GetSeedOutput
	{
		GetSeedOutput(){}
		
		::ara::diag::ByteVectorType seed;

		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(seed);

		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(seed))
{
	return false;
}

			
			return true;
		}
};
struct CompareKeyOutput
	{
		CompareKeyOutput(){}
		
		::ara::diag::KeyCompareResultType result;

		
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

    static constexpr const char* m_errorMessage = "SUBFUNCTION_NOT_SUPPORTED in SecurityAccess with ErrorCode: 18";

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

    static constexpr const char* m_errorMessage = "INCORRECT_MESSAGELENGTH_OR_INVALIDFORMAT in SecurityAccess with ErrorCode: 19";

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

    static constexpr const char* m_errorMessage = "CONDITIONS_NOT_CORRECT in SecurityAccess with ErrorCode: 34";

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

    static constexpr const char* m_errorMessage = "REQUEST_SEQUENCE_ERROR in SecurityAccess with ErrorCode: 36";

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

    static constexpr const char* m_errorMessage = "REQUEST_OUT_OF_RANGE in SecurityAccess with ErrorCode: 49";

};
class INVALID_KEY : public ara::com::ApplicationErrorException
{
public:
    INVALID_KEY()
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
    std::uint8_t m_errorCode = 53;

    static constexpr const char* m_errorMessage = "INVALID_KEY in SecurityAccess with ErrorCode: 53";

};
class Exceed_NUMBEROFATTEMPTS : public ara::com::ApplicationErrorException
{
public:
    Exceed_NUMBEROFATTEMPTS()
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
    std::uint8_t m_errorCode = 54;

    static constexpr const char* m_errorMessage = "Exceed_NUMBEROFATTEMPTS in SecurityAccess with ErrorCode: 54";

};
class SERVICE_ONTSUPPORT_INACTIVESESSION : public ara::com::ApplicationErrorException
{
public:
    SERVICE_ONTSUPPORT_INACTIVESESSION()
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
    std::uint8_t m_errorCode = 127;

    static constexpr const char* m_errorMessage = "SERVICE_ONTSUPPORT_INACTIVESESSION in SecurityAccess with ErrorCode: 127";

};

} //namespace SecurityAccess
static void registerSecurityAccessErrors()
{
	static const ara::com::internal::ErrorEntry<ara::diag::SecurityAccess::SUBFUNCTION_NOT_SUPPORTED> s_SUBFUNCTION_NOT_SUPPORTED(18, "SecurityAccess");
static const ara::com::internal::ErrorEntry<ara::diag::SecurityAccess::INCORRECT_MESSAGELENGTH_OR_INVALIDFORMAT> s_INCORRECT_MESSAGELENGTH_OR_INVALIDFORMAT(19, "SecurityAccess");
static const ara::com::internal::ErrorEntry<ara::diag::SecurityAccess::CONDITIONS_NOT_CORRECT> s_CONDITIONS_NOT_CORRECT(34, "SecurityAccess");
static const ara::com::internal::ErrorEntry<ara::diag::SecurityAccess::REQUEST_SEQUENCE_ERROR> s_REQUEST_SEQUENCE_ERROR(36, "SecurityAccess");
static const ara::com::internal::ErrorEntry<ara::diag::SecurityAccess::REQUEST_OUT_OF_RANGE> s_REQUEST_OUT_OF_RANGE(49, "SecurityAccess");
static const ara::com::internal::ErrorEntry<ara::diag::SecurityAccess::INVALID_KEY> s_INVALID_KEY(53, "SecurityAccess");
static const ara::com::internal::ErrorEntry<ara::diag::SecurityAccess::Exceed_NUMBEROFATTEMPTS> s_Exceed_NUMBEROFATTEMPTS(54, "SecurityAccess");
static const ara::com::internal::ErrorEntry<ara::diag::SecurityAccess::SERVICE_ONTSUPPORT_INACTIVESESSION> s_SERVICE_ONTSUPPORT_INACTIVESESSION(127, "SecurityAccess");

}

}
}

#endif //ARA_DIAG_SECURITYACCESS_COMMON_H
