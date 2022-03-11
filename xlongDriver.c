#pragma once
#pragma warning (disable : 4100 4047 4024)
#include "include.h"


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
	pDriverObject->DriverUnload = UnLoadDriver;
	DebugMessage("xlongDriver loaded!\n");
	//注册loadImage回调，每当加载（或映射到内存）映像时，该回调都会随后收到通知。
	PsSetLoadImageNotifyRoutine(ImageLoadCallback);
	//设备名称变量
	RtlInitUnicodeString(&sdev, L"\\Device\\xlongDriver");
	//设备链接符号名称变量
	RtlInitUnicodeString(&sdos, L"\\DosDevices\\xlongDriver");
	
	//创建io设备
	IoCreateDevice(pDriverObject, 0, &sdev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	//给创建的设备名称绑定链接符
	IoCreateSymbolicLink(&sdos, &sdev);

	//指定IRP派遣函数
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
	IoDeleteSymbolicLink(&sdos);
	IoDeleteDevice(pDriverObject->DeviceObject);
	return STATUS_SUCCESS;
}
