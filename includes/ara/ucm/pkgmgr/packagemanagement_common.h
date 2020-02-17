#ifndef ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_COMMON_H
#define ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_COMMON_H

#include <ara/com/types.h>
#include <impl_type_uint8.h>
#include <impl_type_uint32.h>
#include <impl_type_string.h>
#include <ara/ucm/pkgmgr/impl_type_transferidtype.h>
#include <ara/ucm/pkgmgr/impl_type_activateoptiontype.h>
#include <ara/ucm/pkgmgr/impl_type_activatereturntype.h>
#include <ara/ucm/pkgmgr/impl_type_cancelreturntype.h>
#include <ara/ucm/pkgmgr/impl_type_finishreturntype.h>
#include <ara/ucm/pkgmgr/impl_type_generalresponsetype.h>
#include <ara/ucm/pkgmgr/impl_type_logleveltype.h>
#include <impl_type_bytearray.h>
#include <ara/ucm/pkgmgr/impl_type_bytevectortype.h>
#include <ara/ucm/pkgmgr/impl_type_logentrytype.h>
#include <ara/ucm/pkgmgr/impl_type_logtype.h>
#include <ara/ucm/pkgmgr/impl_type_logvectortype.h>
#include <ara/ucm/pkgmgr/impl_type_packagemanagerstatustype.h>
#include <ara/ucm/pkgmgr/impl_type_processresulttype.h>
#include <ara/ucm/pkgmgr/impl_type_processswpackagereturntype.h>
#include <ara/ucm/pkgmgr/impl_type_revertprocessedswpackagesreturntype.h>
#include <ara/ucm/pkgmgr/impl_type_rollbackreturntype.h>
#include <ara/ucm/pkgmgr/impl_type_swclusterinfostatetype.h>
#include <ara/ucm/pkgmgr/impl_type_swinfoname.h>
#include <ara/ucm/pkgmgr/impl_type_swclusterinfotype.h>
#include <ara/ucm/pkgmgr/impl_type_swclusterinfovectortype.h>
#include <ara/ucm/pkgmgr/impl_type_packagetype.h>
#include <ara/ucm/pkgmgr/impl_type_requesttype.h>
#include <ara/ucm/pkgmgr/impl_type_swpackageinfostatetype.h>
#include <ara/ucm/pkgmgr/impl_type_swpackageinfotype.h>
#include <ara/ucm/pkgmgr/impl_type_swpackageinfovectortype.h>
#include <ara/ucm/pkgmgr/impl_type_transferdatareturntype.h>
#include <ara/ucm/pkgmgr/impl_type_transferexitreturntype.h>
#include <ara/ucm/pkgmgr/impl_type_transferstartsuccesstype.h>
#include <ara/ucm/pkgmgr/impl_type_transferstartreturntype.h>

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

class PackageManagement
{
public:
		struct TransferStartOutput
	{
		TransferStartOutput(){}
		
		::ara::ucm::pkgmgr::TransferStartReturnType result;

		
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
struct TransferDataOutput
	{
		TransferDataOutput(){}
		
		::ara::ucm::pkgmgr::TransferDataReturnType result;

		
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
struct TransferExitOutput
	{
		TransferExitOutput(){}
		
		::ara::ucm::pkgmgr::TransferExitReturnType result;

		
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
struct DeleteTransferOutput
	{
		DeleteTransferOutput(){}
		
		::ara::ucm::pkgmgr::GeneralResponseType result;

		
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
struct ProcessSwPackageOutput
	{
		ProcessSwPackageOutput(){}
		
		::ara::ucm::pkgmgr::ProcessSwPackageReturnType result;

		
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
struct GetSwProcessProgressOutput
	{
		GetSwProcessProgressOutput(){}
		
		::UInt8 progress;

		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(progress);

		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(progress))
{
	return false;
}

			
			return true;
		}
};
struct CancelOutput
	{
		CancelOutput(){}
		
		::ara::ucm::pkgmgr::CancelReturnType result;

		
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
struct RevertProcessedSwPackagesOutput
	{
		RevertProcessedSwPackagesOutput(){}
		
		::ara::ucm::pkgmgr::RevertProcessedSwPackagesReturnType result;

		
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
struct SetLogLevelOutput
	{
		SetLogLevelOutput(){}
		
		::ara::ucm::pkgmgr::LogLevelType result;

		
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
struct GetLogOutput
	{
		GetLogOutput(){}
		
		::ara::ucm::pkgmgr::LogType log;

		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(log);

		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(log))
{
	return false;
}

			
			return true;
		}
};
struct GetSwClusterChangeInfoOutput
	{
		GetSwClusterChangeInfoOutput(){}
		
		::ara::ucm::pkgmgr::SwClusterInfoVectorType SwInfo;

		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(SwInfo);

		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(SwInfo))
{
	return false;
}

			
			return true;
		}
};
struct GetSwClusterInfoOutput
	{
		GetSwClusterInfoOutput(){}
		
		::ara::ucm::pkgmgr::SwClusterInfoVectorType SwInfo;

		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(SwInfo);

		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(SwInfo))
{
	return false;
}

			
			return true;
		}
};
struct GetSwPackagesOutput
	{
		GetSwPackagesOutput(){}
		
		::ara::ucm::pkgmgr::SwPackageInfoVectorType Packages;

		
		using IsEnumerableTag = void;
		
		template <typename T>
		void Serialize(T* serializer) const
		{
			serializer->Serialize(Packages);

		}
		
		template <typename T>
		bool Deserialize(T* deserializer)
		{
			if (!deserializer->Deserialize(Packages))
{
	return false;
}

			
			return true;
		}
};
struct ActivateOutput
	{
		ActivateOutput(){}
		
		::ara::ucm::pkgmgr::ActivateReturnType result;

		
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
struct RollbackOutput
	{
		RollbackOutput(){}
		
		::ara::ucm::pkgmgr::RollbackReturnType result;

		
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
struct FinishOutput
	{
		FinishOutput(){}
		
		::ara::ucm::pkgmgr::FinishReturnType result;

		
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

};



static void registerPackageManagementErrors()
{
	
}

}
}
}

#endif //ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_COMMON_H
