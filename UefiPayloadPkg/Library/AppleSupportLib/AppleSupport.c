#include "Console.h"
#include "Datahub.h"
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <FrameworkDxe.h>
#include <Guid/DataHubRecords.h>
#include <Protocol/DataHub.h>
#include <Library/UefiRuntimeServicesTableLib.h>

EFI_GUID gAppleBootVariableGuid = { 0x7c436110, 0xab2a, 0x4bbb, { 0xa8, 0x80, 0xfe, 0x41, 0x99, 0x5c, 0x9f, 0x82 } };
EFI_GUID gAppleVendorVariableGuid = { 0x4d1ede05, 0x38c7, 0x4a6a, { 0x9c, 0xc6, 0x4b, 0xcc, 0xa8, 0xb3, 0x8c, 0x14 } };

EFI_STATUS InitializeFirmware () {
  EFI_STATUS Status;
  UINTN DataSize;
  CHAR8 bootArgs[] = "-no_compat_check";
  CHAR8 csrActiveConfig[] = { 0x01 };
  CHAR8 ExtendedFirmwareFeatures[] = { 0x66, 0xF0, 0xB3, 0xFF, 0x08, 0x00, 0x00, 0x00 };
  CHAR8 ExtendedFirmwareFeaturesMask[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x00, 0x00, 0x00 };
  CHAR8 FirmwareFeatures[] = { 0x66, 0xF0, 0xB3, 0xFF };
  CHAR8 FirmwareFeaturesMask[] = { 0xFF, 0xFF, 0xFF, 0xFF };
  CHAR8 HW_BID[] = { 0x4D, 0x61, 0x63, 0x2D, 0x43, 0x46, 0x46, 0x37, 0x44, 0x39, 0x31, 0x30, 0x41, 0x37, 0x34, 0x33, 0x43, 0x41, 0x41, 0x46 };
  CHAR8 HW_MLB[] = { 0x43, 0x30, 0x32, 0x32, 0x31, 0x34, 0x37, 0x30, 0x31, 0x47, 0x55, 0x50, 0x48, 0x43, 0x31, 0x4A, 0x43 };
  CHAR8 HW_ROM[] = { 0x73, 0x47, 0x1C, 0x7F, 0xCD, 0x5B };
  CHAR8 HW_SSN[] = { 0x43, 0x30, 0x32, 0x48, 0x4A, 0x32, 0x59, 0x4B, 0x50, 0x4E, 0x35, 0x54 };
  CHAR8 MLB[] = { 0x43, 0x30, 0x32, 0x32, 0x31, 0x34, 0x37, 0x30, 0x31, 0x47, 0x55, 0x50, 0x48, 0x43, 0x31, 0x4A, 0x43 };
  CHAR8 ROM[] = { 0x73, 0x47, 0x1C, 0x7F, 0xCD, 0x5B };
  CHAR8 SSN[] = { 0x43, 0x30, 0x32, 0x48, 0x4A, 0x32, 0x59, 0x4B, 0x50, 0x4E, 0x35, 0x54 };

  DataSize = 0;
  Status = gRT->GetVariable(L"boot-args", &gAppleBootVariableGuid, NULL, &DataSize, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
	Status = gRT->SetVariable(L"boot-args", &gAppleBootVariableGuid, 0x07, sizeof(bootArgs), &bootArgs);
  }

  DataSize = 0;
  Status = gRT->GetVariable(L"csr-active-config", &gAppleBootVariableGuid, NULL, &DataSize, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
	Status = gRT->SetVariable(L"csr-active-config", &gAppleBootVariableGuid, 0x07, sizeof(csrActiveConfig), &csrActiveConfig);
  }

  DataSize = 0;
  Status = gRT->GetVariable(L"ExtendedFirmwareFeatures", &gAppleVendorVariableGuid, NULL, &DataSize, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
	Status = gRT->SetVariable(L"ExtendedFirmwareFeatures", &gAppleVendorVariableGuid, 0x06, sizeof(ExtendedFirmwareFeatures), &ExtendedFirmwareFeatures);
  }

  DataSize = 0;
  Status = gRT->GetVariable(L"ExtendedFirmwareFeaturesMask", &gAppleVendorVariableGuid, NULL, &DataSize, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
	Status = gRT->SetVariable(L"ExtendedFirmwareFeaturesMask", &gAppleVendorVariableGuid, 0x06, sizeof(ExtendedFirmwareFeaturesMask), &ExtendedFirmwareFeaturesMask);
  }

  DataSize = 0;
  Status = gRT->GetVariable(L"FirmwareFeatures", &gAppleVendorVariableGuid, NULL, &DataSize, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
	Status = gRT->SetVariable(L"FirmwareFeatures", &gAppleVendorVariableGuid, 0x06, sizeof(FirmwareFeatures), &FirmwareFeatures);
  }

  DataSize = 0;
  Status = gRT->GetVariable(L"FirmwareFeaturesMask", &gAppleVendorVariableGuid, NULL, &DataSize, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
	Status = gRT->SetVariable(L"FirmwareFeaturesMask", &gAppleVendorVariableGuid, 0x06, sizeof(FirmwareFeaturesMask), &FirmwareFeaturesMask);
  }

  DataSize = 0;
  Status = gRT->GetVariable(L"HW_BID", &gAppleVendorVariableGuid, NULL, &DataSize, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
	Status = gRT->SetVariable(L"HW_BID", &gAppleVendorVariableGuid, 0x06, sizeof(HW_BID), &HW_BID);
  }

  DataSize = 0;
  Status = gRT->GetVariable(L"HW_MLB", &gAppleVendorVariableGuid, NULL, &DataSize, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
	Status = gRT->SetVariable(L"HW_MLB", &gAppleVendorVariableGuid, 0x06, sizeof(HW_MLB), &HW_MLB);
  }

  DataSize = 0;
  Status = gRT->GetVariable(L"HW_ROM", &gAppleVendorVariableGuid, NULL, &DataSize, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
	Status = gRT->SetVariable(L"HW_ROM", &gAppleVendorVariableGuid, 0x06, sizeof(HW_ROM), &HW_ROM);
  }

  DataSize = 0;
  Status = gRT->GetVariable(L"HW_SSN", &gAppleVendorVariableGuid, NULL, &DataSize, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
	Status = gRT->SetVariable(L"HW_SSN", &gAppleVendorVariableGuid, 0x06, sizeof(HW_SSN), &HW_SSN);
  }

  DataSize = 0;
  Status = gRT->GetVariable(L"MLB", &gAppleVendorVariableGuid, NULL, &DataSize, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
	Status = gRT->SetVariable(L"MLB", &gAppleVendorVariableGuid, 0x06, sizeof(MLB), &MLB);
  }

  DataSize = 0;
  Status = gRT->GetVariable(L"ROM", &gAppleVendorVariableGuid, NULL, &DataSize, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
	Status = gRT->SetVariable(L"ROM", &gAppleVendorVariableGuid, 0x06, sizeof(ROM), &ROM);
  }

  DataSize = 0;
  Status = gRT->GetVariable(L"SSN", &gAppleVendorVariableGuid, NULL, &DataSize, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
	Status = gRT->SetVariable(L"SSN", &gAppleVendorVariableGuid, 0x06, sizeof(SSN), &SSN);
  }

  return Status;
}

EFI_STATUS EFIAPI InitializeAppleSupport ( IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable ) {
  EFI_STATUS Status;
  Status = InitializeConsoleControl(ImageHandle);
  Status = InitializeDatahub(ImageHandle);
  Status = InitializeFirmware();
  return Status;
}
