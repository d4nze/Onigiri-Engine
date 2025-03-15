#ifdef APPLICATION_CORE_EXPORTS
#define APPLICATION_CORE_API __declspec(dllexport)
#else
#define APPLICATION_CORE_API __declspec(dllimport)
#endif
