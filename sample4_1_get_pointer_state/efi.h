#ifndef _EFI_H_
#define _EFI_H_

#include <Uefi/UefiBaseType.h>
#include <Uefi/UefiSpec.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/SimplePointer.h>
#include <Protocol/AbsolutePointer.h>

extern EFI_SYSTEM_TABLE *ST;
extern struct _EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
extern struct _EFI_SIMPLE_POINTER_PROTOCOL *SPP;
extern struct _EFI_ABSOLUTE_POINTER_PROTOCOL *APP;

void efi_init(EFI_SYSTEM_TABLE *SystemTable);

#endif
