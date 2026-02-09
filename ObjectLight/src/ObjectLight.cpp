// ObjectLight.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "ObjectLight/ObjectLight.h"

#if defined(_WIN32) || defined(_WIN64)

#define NOWINRES // Exclude Windows Resource values 
#define WIN32_LEAN_AND_MEAN 1 // Exclude rarely-used stuff from Windows headers
#define NOGDI // Exclude GDI (Graphics Device Interface) definitions and routines

#include <windows.h>

BOOL APIENTRY DllMain(
    HANDLE hModule,// Handle to DLL module
    DWORD ul_reason_for_call,// Reason for calling function
    LPVOID lpReserved) // Reserved
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: // A process is loading the DLL.
        break;
    case DLL_THREAD_ATTACH: // A process is creating a new thread.
        break;
    case DLL_THREAD_DETACH: // A thread exits normally.
        break;
    case DLL_PROCESS_DETACH: // A process unloads the DLL.
        break;
    }
    return TRUE;
}

#endif
