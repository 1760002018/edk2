#ifndef _APPLESUPPORT_DATAHUB_H_INCLUDED_
#define _APPLESUPPORT_DATAHUB_H_INCLUDED_
#include "Common.h"
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <FrameworkDxe.h>
#include <Guid/DataHubRecords.h>
#include <Protocol/DataHub.h>
EFI_STATUS EFIAPI InitializeDatahub ( IN EFI_HANDLE ImageHandle );
#endif
