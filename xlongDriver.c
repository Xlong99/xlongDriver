#pragma once
#pragma warning (disable : 4100 4047 4024)
#include "include.h"


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
	pDriverObject->DriverUnload = UnLoadDriver;
	DebugMessage("xlongDriver loaded!\n");
	//ע��loadImage�ص���ÿ�����أ���ӳ�䵽�ڴ棩ӳ��ʱ���ûص���������յ�֪ͨ��
	PsSetLoadImageNotifyRoutine(ImageLoadCallback);
	//�豸���Ʊ���
	RtlInitUnicodeString(&sdev, L"\\Device\\xlongDriver");
	//�豸���ӷ������Ʊ���
	RtlInitUnicodeString(&sdos, L"\\DosDevices\\xlongDriver");
	
	//����io�豸
	IoCreateDevice(pDriverObject, 0, &sdev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	//���������豸���ư����ӷ�
	IoCreateSymbolicLink(&sdos, &sdev);

	//ָ��IRP��ǲ����
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
	IoDeleteSymbolicLink(&sdos);
	IoDeleteDevice(pDriverObject->DeviceObject);
	return STATUS_SUCCESS;
}
