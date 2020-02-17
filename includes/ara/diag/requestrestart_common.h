#ifndef ARA_DIAG_REQUESTRESTART_COMMON_H
#define ARA_DIAG_REQUESTRESTART_COMMON_H

#include <ara/com/types.h>
#include <ara/diag/impl_type_restarttype.h>
#include <ara/diag/impl_type_executiontype.h>
#include <impl_type_uint8.h>
#include <impl_type_uint16.h>
#include <impl_type_string.h>

namespace ara
{
namespace diag
{

namespace RequestRestart
{
	struct RequestRestartOutput
	{
		RequestRestartOutput(){}
		
		
		
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

		

class kRejected : public ara::com::ApplicationErrorException
{
public:
    kRejected()
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
    std::uint8_t m_errorCode = 0;

    static constexpr const char* m_errorMessage = "kRejected in RequestRestart with ErrorCode: 0";

};

} //namespace RequestRestart
static void registerRequestRestartErrors()
{
	static const ara::com::internal::ErrorEntry<ara::diag::RequestRestart::kRejected> s_kRejected(0, "RequestRestart");

}

}
}

#endif //ARA_DIAG_REQUESTRESTART_COMMON_H
