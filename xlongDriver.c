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
	//ע��loadImage�ص���ÿ�����أ���ӳ�䵽�ڴ棩ӳ��ʱ���ûص���������յ�֪ͨ��
	PsSetLoadImageNotifyRoutine(ImageLoadCallback);
	RtlInitUnicodeString(&dev, L"\\Device\\xlongDriver");
	RtlInitUnicodeString(&dos, L"\\DosDevices\\xlongDriver");

	//����io�豸
	IoCreateDevice(pDriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	//������������
	IoCreateSymbolicLink(&dos, &dev);

	pDriverObject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;

	pDeviceObject->Flags |= DO_DIRECT_IO;

	//������DO_DEVICE_INITIALIZING��־ʱ��I/O���������ܾ����д򿪸��豸����������Լ�����豸�����ϸ��������豸����
	//����ñ�־
	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	return STATUS_SUCCESS;
}

NTSTATUS UnLoadDriver(PDRIVER_OBJECT pDriverObject)
{	
	DebugMessage("goodbye xlong!\n");

	//�Ƴ��ص�
	PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);
	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(pDriverObject->DeviceObject);
	return STATUS_SUCCESS;
}
