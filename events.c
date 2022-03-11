#pragma warning (disable :  4047 )

#include "events.h"
#include "msg.h"
#include "data.h"

//加载镜像回调函数
PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{
    
    if (wcsstr(FullImageName->Buffer, L"\\client.dll")) {
        DebugMessage("ImageLoaded:%ls ,Address:%llx \n", FullImageName->Buffer, ImageInfo->ImageBase);
        DebugMessage("DLL found!  \n");
        ClientDLLAddress = ImageInfo->ImageBase;
        DebugMessage("ProcessId: %d  \n",ProcessId);
    }
    return STATUS_SUCCESS;
}
