#pragma warning (disable :  4047 )
#pragma once
#include "include.h"

//���ؾ���ص�����
PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{
    
    if (wcsstr(FullImageName->Buffer, L"\\client.dll") || wcsstr(FullImageName->Buffer, L"\\Raft.exe")) {
        DebugMessage("ImageLoaded:%ls ,Address:%llx \n", FullImageName->Buffer, ImageInfo->ImageBase);
        DebugMessage("DLL found!  \n");
        ClientDLLAddress = ImageInfo->ImageBase;
        DebugMessage("ProcessId: %d  \n",ProcessId);
    }
    return STATUS_SUCCESS;
}
