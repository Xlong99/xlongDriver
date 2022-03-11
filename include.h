#pragma once
#include <ntdef.h>
#include <ntifs.h>
#include <ntddk.h>
#include <ntstrsafe.h>
#include <minwindef.h>
#include <ifdef.h>
#include <ntddndis.h>
#include <wdm.h>
#include <intrin.h>
#include <ntimage.h>

#include "xlongDriver.h"
#include "communication.h"
#include "data.h"
#include "events.h"
#include "memory.h"
#include "msg.h"


#define bool int
#define false 0
#define true 1
