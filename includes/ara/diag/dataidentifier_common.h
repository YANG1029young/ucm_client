#ifndef ARA_DIAG_DATAIDENTIFIER_COMMON_H
#define ARA_DIAG_DATAIDENTIFIER_COMMON_H

#include <ara/com/types.h>
#include <ara/diag/impl_type_metainfotype.h>
#include <impl_type_bytearray.h>
#include <impl_type_uint8.h>
#include <impl_type_string.h>

namespace ara
{
namespace diag
{

namespace DataIdentifier
{
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
struct ReadOutput
	{
		ReadOutput(){}
		
		::ByteArray dataRecord;

		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(dataRecord);

		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(dataRecord))
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

    static constexpr const char* m_errorMessage = "INCORRECT_MESSAGELENGTH_OR_INVALIDFORMAT in DataIdentifier with ErrorCode: 19";

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

    static constexpr const char* m_errorMessage = "CONDITIONS_NOT_CORRECT in DataIdentifier with ErrorCode: 34";

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

    static constexpr const char* m_errorMessage = "Security_ACCESS_DENIED in DataIdentifier with ErrorCode: 51";

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

    static constexpr const char* m_errorMessage = "REQUEST_OUT_OF_RANGE in DataIdentifier with ErrorCode: 49";

};

} //namespace DataIdentifier
static void registerDataIdentifierErrors()
{
	static const ara::com::internal::ErrorEntry<ara::diag::DataIdentifier::INCORRECT_MESSAGELENGTH_OR_INVALIDFORMAT> s_INCORRECT_MESSAGELENGTH_OR_INVALIDFORMAT(19, "DataIdentifier");
static const ara::com::internal::ErrorEntry<ara::diag::DataIdentifier::CONDITIONS_NOT_CORRECT> s_CONDITIONS_NOT_CORRECT(34, "DataIdentifier");
static const ara::com::internal::ErrorEntry<ara::diag::DataIdentifier::Security_ACCESS_DENIED> s_Security_ACCESS_DENIED(51, "DataIdentifier");
static const ara::com::internal::ErrorEntry<ara::diag::DataIdentifier::REQUEST_OUT_OF_RANGE> s_REQUEST_OUT_OF_RANGE(49, "DataIdentifier");

}

}
}

#endif //ARA_DIAG_DATAIDENTIFIER_COMMON_H
