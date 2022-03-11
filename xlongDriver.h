#pragma once

#include <ntifs.h>

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath);
NTSTATUS UnLoadDriver(PDRIVER_OBJECT pDriverObject);
