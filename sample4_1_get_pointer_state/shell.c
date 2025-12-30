#include "efi.h"
#include "common.h"
#include "graphics.h"
#include "shell.h"
#include "gui.h"

#define MAX_COMMAND_LEN	100

void pstat(void)
{
	unsigned long long status;
	struct EFI_SIMPLE_POINTER_STATE s;
	//struct EFI_ABSOLUTE_POINTER_STATE a;
	unsigned long long waitidx;

	if (SPP) {
		SPP->Reset(SPP, FALSE);
		while (1) {
			status = ST->BootServices->WaitForEvent(
				1, &(SPP->WaitForInput), &waitidx);
			if (status) {
				puts(L"SPP WaitForEvent failed\r\n");
				puth(status, 8);
				puts(L"\r\n");
				return;
			}
			status = SPP->GetState(SPP, &s);
			if (!status) {
				puth(s.RelativeMovementX, 8);
				puts(L" ");
				puth(s.RelativeMovementY, 8);
				puts(L" ");
				puth(s.RelativeMovementZ, 8);
				puts(L" ");
				puth(s.LeftButton, 1);
				puts(L" ");
				puth(s.RightButton, 1);
				puts(L"\r\n");
			}
		}
	}

	#if 0
	if (APP) {
		APP->Reset(APP, FALSE);
		while (1) {
			status = ST->BootServices->WaitForEvent(
				1, &(APP->WaitForInput), &waitidx);
			if (status) {
				puts(L"APP WaitForEvent failed\r\n");
				puth(status, 8);
				puts(L"\r\n");
				return;
			}
			status = APP->GetState(APP, &a);
			if (!status) {
				puth(a.CurrentX, 8);
				puts(L" ");
				puth(a.CurrentY, 8);
				puts(L" ");
				puth(a.CurrentZ, 8);
				puts(L" ");
				puth(a.ActiveButtons, 2);
				puts(L"\r\n");
			}
		}
	}
	#endif

	puts(L"No pointer protocol found\r\n");
}

void debug(void)
{
	#if 0
	unsigned long long Count;
	struct EFI_HANDLE *Handles;
	struct EFI_BOOT_SERVICES *gBS;

	gBS->LocateHandleBuffer(
    	ByProtocol,
    	&gEfiSimplePointerProtocolGuid,
    	NULL,
    	&Count,
    	&Handles
	);
	puth(Count, 8);
	puts(L" ");
	#endif
}

void shell(void)
{
	unsigned short com[MAX_COMMAND_LEN];
	struct RECT r = {10, 10, 100, 200};

	while (TRUE) {
		puts(L"poiOS> ");
		if (gets(com, MAX_COMMAND_LEN) <= 0)
			continue;

		if (!strcmp(L"hello", com))
			puts(L"Hello UEFI!\r\n");
		else if (!strcmp(L"rect", com))
			draw_rect(r, white);
		else if (!strcmp(L"gui", com))
			gui();
		else if (!strcmp(L"pstat", com))
			pstat();
		else if (!strcmp(L"debug", com))
			debug();
		else
			puts(L"Command not found.\r\n");
	}
}
