#pragma onece

#ifdef _WIN32
    #ifdef OBL_API_EXPORTS
        #define OBL_API __declspec(dllexport)
    #else
        #define OBL_API __declspec(dllimport)
    #endif
#elif defined(__GNUC__) && __GNUC__ >= 4
    #define OBL_API __attribute__((visibility("default")))
#else
	#define OBL_API 
#endif

#define OBL_EXTERN extern "C"