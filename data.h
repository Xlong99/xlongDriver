#pragma once
#include <ntdef.h>

//io设备对象
PDEVICE_OBJECT pDeviceObject;
UNICODE_STRING dev, dos;
//Client.dll的虚拟地址
ULONG ClientDLLAddress;