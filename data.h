#pragma once
#include <ntdef.h>

//io设备对象
PDEVICE_OBJECT pDeviceObject;
UNICODE_STRING sdev, sdos;
//Client.dll的虚拟地址
ULONG64 ClientDLLAddress;