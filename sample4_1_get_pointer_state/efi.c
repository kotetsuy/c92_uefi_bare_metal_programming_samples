#include <Uefi/UefiBaseType.h>
#include <Uefi/UefiSpec.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/SimplePointer.h>
#include <Protocol/AbsolutePointer.h>
#include "common.h"

EFI_SYSTEM_TABLE *ST;
struct _EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
struct _EFI_SIMPLE_POINTER_PROTOCOL *SPP;
//struct _EFI_ABSOLUTE_POINTER_PROTOCOL *APP;

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

		ST->BootServices->Stall(10*1000*1000);

		st = ST->BootServices->LocateProtocol(&spp_guid, NULL,
						      (void **)&SPP);
		if (st) {
			puts(L"SPP LocateProtocol failed ");
			puth(st, 16);
			puts(L"\r\n");
		}

		#if 0
		st = ST->BootServices->LocateProtocol(&app_guid, NULL,
						      (void **)&APP);
		if (st) {
			puts(L"APP LocateProtocol failed ");
			puth(st, 16);
			puts(L"\r\n");
		}
		#endif
	}
}
