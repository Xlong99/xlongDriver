#pragma once
#pragma warning (disable : 4100 4022 4024)
#include "include.h"



NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	DebugMessage("createCall was called,connection enstablished!\n");
	return STATUS_SUCCESS;
}

NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	DebugMessage("CloseCall was called,connection Terminated!\n");
	return STATUS_SUCCESS;
}

NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	//DebugMessage("IoControl was called,connection Terminated!\n");
	UNREFERENCED_PARAMETER(DeviceObject);
	NTSTATUS Status = STATUS_UNSUCCESSFUL;
	ULONG ByteIO = 0;

	//返回指向指定 IRP 中调用方的 I/O 堆栈位置的指针。
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	//获取调用方参数中的IoControlCode
	ULONG ControlCode = stack->Parameters.DeviceIoControl.IoControlCode;
	if (ControlCode == IO_GET_CLIENTADDRESS) {
		//systemBuffer可以转为任意内容
		ULONG64* OutPut = (ULONG64*)Irp->AssociatedIrp.SystemBuffer;
		*OutPut = ClientDLLAddress;
		DebugMessage("address requested!\n");
		Status = STATUS_SUCCESS;
		ByteIO = sizeof(*OutPut);
	}
	else if (ControlCode == IO_READ_REQUEST) {
		
		PKERNEL_READ_WRITE_REQUEST ReadInput = (PKERNEL_READ_WRITE_REQUEST)Irp->AssociatedIrp.SystemBuffer;
		PEPROCESS Process;
		DebugMessage("Read memory:called :0x%p \n",ReadInput->Address);
		if (NT_SUCCESS(PsLookupProcessByProcessId(ReadInput->ProcessId, &Process))) {
			
			NTSTATUS res = KernelReadVirtualMemory(Process, ReadInput->Address, ReadInput->pBuff, ReadInput->size);
			if (res == STATUS_SUCCESS) {
				DebugMessage("Read memory succeed  \n");
			}
			else {
				DebugMessage("Read memory failed  \n");
			}
			
			Status = STATUS_SUCCESS;
			ByteIO = sizeof(*ReadInput);
		}
	}
	else if (ControlCode == IO_WRITE_REQUEST) {
		PKERNEL_READ_WRITE_REQUEST WriteInput = (PKERNEL_READ_WRITE_REQUEST)Irp->AssociatedIrp.SystemBuffer;
		PEPROCESS Process;
		if (NT_SUCCESS(PsLookupProcessByProcessId(WriteInput->ProcessId, &Process))) {
			KernelWriteVirtualMemory(Process, WriteInput->pBuff, WriteInput->Address, WriteInput->size);
			
			
			Status = STATUS_SUCCESS;
			ByteIO = sizeof(*WriteInput);
		}
	}
	else {
		ByteIO = 0;
	}
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = ByteIO;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return Status;
}


