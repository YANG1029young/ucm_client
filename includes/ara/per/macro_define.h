#ifndef _MACRO_DEFINE_H_
#define _MACRO_DEFINE_H_
#include "jsconfig/jsconfig.h"
#include <unistd.h>
#include <stdlib.h>

//define the type desc macro
#define STR_SINT8              (char *)"sint8"
#define STR_SINT16             (char *)"sint16"
#define STR_SINT32             (char *)"sint32"
#define STR_SINT64             (char *)"sint64"
#define STR_UINT8              (char *)"uint8"
#define STR_UINT16             (char *)"uint16"
#define STR_UINT32             (char *)"uint32"
#define STR_UINT64             (char *)"uint64"
#define STR_BOOL               (char *)"bool" 
#define STR_DOUBLE             (char *)"double"
#define STR_FLOAT              (char *)"float"
#define STR_STRING             (char *)"string"
#define STR_BINARY             (char *)"binary"
#define STR_OBJECT             (char *)"object"

//define app update strategy
#define STR_APP_UP_STRATEGY_INSTALL    (char *)"installation"
#define STR_APP_UP_STRATEGY_UPDATE     (char *)"update"
#define STR_APP_UP_STRATEGY_UNINSTALL  (char *)"unInstallation"

//define DeploymentConfig
#define STR_DEPLOYMENT_CONFIG  (char *)"DeploymentConfig"
#define STR_UPDATE_TYPE        (char *)"UpdateType"
#define STR_KVS_DATABASE       (char *)"KeyValukDatabase"
#define STR_FILE_PROXY         (char *)"FileProxy"
#define STR_DATA_CONFIG        (char *)"DataConfig"

//define UpdateStrategy marco
#define DELETE_STRATEGY        (char *)"delete"
#define KEEP_EXISTING_STRATEGY (char *)"keepExisting"
#define OVER_WRITE             (char *)"overWrite"

//define jsonParse str marco
#define STR_URI                (char *)"uri"
#define STR_UPDATE_STRATEGY    (char *)"updateStrategy"
#define STR_KEYVALUE_PAIRS     (char *)"keyValuePairs"

//define KeyValuePairs str
#define STR_KVS_NAME           (char *)"name"
#define STR_KVS_INIT_VALUE     (char *)"initValue"
#define STR_KVS_DATA_TYPE      (char *)"valueDataType"
#define STR_KVS_UPDATE_STRATEGY STR_UPDATE_STRATEGY

#define STR_KVS_TYPE           (char *)"type"
#define STR_KVS_KEY            (char *)"key"
#define STR_KVS_VALUE          (char *)"value"
#define STR_KVS_CHECKSUM       (char *)"checksum"

//define FileProxy
#define STR_FILE_PROXY_CONTENT_URI       (char *)"contentUri"
#define STR_FILE_PROXY_URI               STR_URI
#define STR_FILE_PROXY_UPDATE_STRATEGY   STR_UPDATE_STRATEGY

//define DataConfig
#define STR_DATA_CONFIG_MAXSIZE          (char *)"maxSize"
#define STR_DATA_CONFIG_CHECKSUM         (char *)"checksum"
#define STR_DATA_CONFIG_UPDATE_TIME      (char *)"updateTime"
#define STR_DATA_CONFIG_IS_REDUNDANCY    (char *)"isRedundancy"

//json string split flag marco
#define COMMA_FLAG ","
#define COLON_FLAG ":"

//define the App name
#define APP_NAME "PersistencyService"

//define function marco
#define CHECK_JSON_TYPE_VALID(obj) \
		{ \
			auto eType = (obj).getType(); \
			 if((jsconfig::kInvalid == eType) || (jsconfig::kNull == eType)) \
	 		 { \
	 		 		std::cout<<"the json type is invalid"<<std::endl; \
	 				return false; \
	 		 } \
		}

#define CHECK_WHETHER_FILE_EXISTS(filename, bResult) \
		{ \
			if (0 != access(filename, F_OK)) \
			{ \
				bResult = false; \
			} \
			else \
			{ \
				bResult = true; \
			} \
		}

#define CHECK_PARSE_STATE() \
    {                       \
        if (!new_item_)     \
            return false;   \
    }

#define CREATE_FILE(fileName) \
	{                         \
		char systemCmd[1024] = {0}; \
		if (access(fileName, F_OK)) \
		{ \
			snprintf(systemCmd, sizeof(systemCmd) - 1, "touch %s &", fileName); \
			system(systemCmd); \
		} \
	}

#define REMOVE_FILE(fileName) \
	{                         \
		char systemCmd[1024] = {0}; \
		snprintf(systemCmd, sizeof(systemCmd) - 1, "rm -rf %s &", fileName); \
		system(systemCmd); \
	}

#endif
