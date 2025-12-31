#include "efi.h"
#include "common.h"

EFI_SYSTEM_TABLE *ST;
struct _EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
struct _EFI_SIMPLE_POINTER_PROTOCOL *SPP;

void efi_init(EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	EFI_GUID spp_guid = EFI_SIMPLE_POINTER_PROTOCOL_GUID;
	EFI_GUID app_guid = EFI_ABSOLUTE_POINTER_PROTOCOL_GUID;

	ST = SystemTable;
	ST->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
	{
		unsigned long long st;
		st = ST->BootServices->LocateProtocol(&gop_guid, NULL,
						      (void **)&GOP);
		if (st) {
			puts(L"GOP LocateProtocol failed ");
			puth(st, 16);
			puts(L"\r\n");
		}

		st = ST->BootServices->LocateProtocol(&spp_guid, NULL,
						      (void **)&SPP);
		if (st) {
			puts(L"SPP LocateProtocol failed ");
			puth(st, 16);
			puts(L"\r\n");
		}

		puts(L"H ");
		puth(GOP->Mode->Info->HorizontalResolution, 16);
		puts(L": ");
		puts(L"V ");
		puth(GOP->Mode->Info->VerticalResolution, 16);
		puts(L"\r\n");
	}
}
