#pragma once
#include "include.h"

NTSTATUS KernelReadVirtualMemory(PEPROCESS Process, PVOID SourceAddress, PVOID Targetaddress, SIZE_T Size) {
	SIZE_T Bytes;
	return MmCopyVirtualMemory(Process, SourceAddress, PsGetCurrentProcess(), Targetaddress, Size, KernelMode, &Bytes);
}
NTSTATUS KernelWriteVirtualMemory(PEPROCESS Process, PVOID SourceAddress, PVOID Targetaddress, SIZE_T Size) {
	SIZE_T Bytes;
	return MmCopyVirtualMemory(PsGetCurrentProcess(), SourceAddress, Process, Targetaddress, Size, KernelMode, &Bytes);
}