#pragma once
#include <ntifs.h>

//���ؾ���ص�����
PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING FullImageName,HANDLE ProcessId,PIMAGE_INFO ImageInfo);
