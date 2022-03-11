#pragma warning (disable : 4100 4047 4024)

#include "xlongDriver.h"
#include "data.h"
#include "msg.h"
#include "events.h"
#include "communication.h"

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
	pDriverObject->DriverUnload = UnLoadDriver;
	DebugMessage("xlongDriver loaded!\n");
	//注册loadImage回调，每当加载（或映射到内存）映像时，该回调都会随后收到通知。
	PsSetLoadImageNotifyRoutine(ImageLoadCallback);
	RtlInitUnicodeString(&dev, L"\\Device\\xlongDriver");
	RtlInitUnicodeString(&dos, L"\\DosDevices\\xlongDriver");

	//创建io设备
	IoCreateDevice(pDriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	//创建符号链接
	IoCreateSymbolicLink(&dos, &dev);

	pDriverObject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;

	pDeviceObject->Flags |= DO_DIRECT_IO;

	//当设置DO_DEVICE_INITIALIZING标志时，I/O管理器将拒绝所有打开该设备句柄的请求以及向该设备对象上附着其他设备对象。
	//清除该标志
	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	return STATUS_SUCCESS;
}

NTSTATUS UnLoadDriver(PDRIVER_OBJECT pDriverObject)
{	
	DebugMessage("goodbye xlong!\n");

	//移除回调
	PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);
	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(pDriverObject->DeviceObject);
	return STATUS_SUCCESS;
}
