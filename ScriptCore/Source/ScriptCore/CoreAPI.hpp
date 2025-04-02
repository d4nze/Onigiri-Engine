#ifdef SCRIPT_CORE_EXPORTS
#define SCRIPT_CORE_API __declspec(dllexport)
#else
#define SCRIPT_CORE_API __declspec(dllimport)
#endif
