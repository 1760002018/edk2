#include "Datahub.h"
EFI_GUID gApplePlatformProducerNameGuid = {0x64517CC8, 0x6561, 0x4051, {0xB0, 0x3C, 0x59, 0x64, 0xB6, 0x0F, 0x4C, 0x7A}};
EFI_GUID gAppleFsbFrequencyPlatformInfoGuid = {0xD1A04D55, 0x75B9, 0x41A3, {0x90, 0x36, 0x8F, 0x4A, 0x26, 0x1C, 0xBB, 0xA2}};
typedef struct { UINT32 DataNameSize; UINT32 DataSize; } EFI_PROPERTY_SUBCLASS_RECORD;
typedef struct { EFI_SUBCLASS_TYPE1_HEADER Header; EFI_PROPERTY_SUBCLASS_RECORD Record; } EFI_PROPERTY_SUBCLASS_DATA;
EFI_STATUS
SetEfiPlatformProperty (IN EFI_DATA_HUB_PROTOCOL *DataHub, IN CONST EFI_STRING Name, EFI_GUID EfiPropertyGuid, VOID *Data, UINT32 DataSize) {
 EFI_STATUS Status;
 UINT32 DataNameSize;
 EFI_PROPERTY_SUBCLASS_DATA *DataRecord;
 DataNameSize = (UINT32)StrSize(Name);
 DataRecord = AllocateZeroPool (sizeof (EFI_PROPERTY_SUBCLASS_DATA) + DataNameSize + DataSize);
 DataRecord->Header.Version = EFI_DATA_RECORD_HEADER_VERSION;
 DataRecord->Header.HeaderSize = sizeof(EFI_SUBCLASS_TYPE1_HEADER);
 DataRecord->Header.Instance = 0xFFFF;
 DataRecord->Header.SubInstance = 0xFFFF;
 DataRecord->Header.RecordType = 0xFFFFFFFF;
 DataRecord->Record.DataNameSize = DataNameSize;
 DataRecord->Record.DataSize = DataSize;
 CopyMem((UINT8 *)DataRecord + sizeof(EFI_PROPERTY_SUBCLASS_DATA), Name, DataNameSize);
 CopyMem((UINT8 *)DataRecord + sizeof(EFI_PROPERTY_SUBCLASS_DATA) + DataNameSize, Data, DataSize);
 Status = DataHub->LogData(DataHub, &EfiPropertyGuid, &gApplePlatformProducerNameGuid,
 EFI_DATA_RECORD_CLASS_DATA,
 DataRecord,
 sizeof(EFI_PROPERTY_SUBCLASS_DATA) + DataNameSize + DataSize);
 if (DataRecord) {
   gBS->FreePool(DataRecord);
 }
 return Status;
}
EFI_STATUS EFIAPI InitializeDatahub (IN EFI_HANDLE ImageHandle) {
 EFI_STATUS Status;
 EFI_DATA_HUB_PROTOCOL *DataHub;
 Status = gBS->LocateProtocol(&gEfiDataHubProtocolGuid, NULL, (VOID **)&DataHub);
 UINT64 FsbFrequency = 725000000;
 SetEfiPlatformProperty(DataHub, L"FSBFrequency", gAppleFsbFrequencyPlatformInfoGuid, &FsbFrequency, sizeof(UINT64));
 return Status;
}
