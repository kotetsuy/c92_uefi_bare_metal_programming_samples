# ===== toolchain =====
CC      = clang
LD      = lld-link

# EDK2 headers (git cloneした場所に合わせて変更)
EDK2_DIR ?= ../edk2
EDK2_INC  = -I$(EDK2_DIR)/MdePkg/Include -I$(EDK2_DIR)/MdePkg/Include/X64

CFLAGS = \
	-target x86_64-unknown-windows \
	-ffreestanding -fno-stack-protector -fno-pic \
	-mno-red-zone \
	$(EDK2_INC)

LDFLAGS = \
	/subsystem:efi_application \
	/entry:efi_main \
	/nodefaultlib

# ===== build =====
all: disk.img

OBJS = main.o common.o efi.o shell.o graphics.o gui.o

BOOTX64.EFI: $(OBJS)
	$(LD) $(LDFLAGS) $^ /out:$@

# modern rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ===== run =====
run: BOOTX64.EFI OVMF_CODE.fd OVMF_VARS.fd disk.img
	qemu-system-x86_64 \
	-machine q35 \
	-m 512M \
	-drive if=pflash,format=raw,readonly=on,file=OVMF_CODE.fd \
	-drive if=pflash,format=raw,file=OVMF_VARS.fd \
	-drive file=disk.img,format=raw \
	-device usb-ehci \
	-device usb-mouse \
	-serial stdio

# ===== OVMF =====
OVMF_CODE.fd:
	cp /opt/homebrew/share/qemu/edk2-x86_64-code.fd ./OVMF_CODE.fd

OVMF_VARS.fd:
	cp /opt/homebrew/share/qemu/edk2-i386-vars.fd ./OVMF_VARS.fd

disk.img: BOOTX64.EFI
	dd if=/dev/zero of=disk.img bs=1m count=64
	mkfs.fat -F 32 disk.img
	mmd   -i disk.img ::/EFI
	mmd   -i disk.img ::/EFI/BOOT
	mcopy -i disk.img BOOTX64.EFI ::/EFI/BOOT/BOOTX64.EFI

clean:
	rm -f BOOTX64.EFI disk.img *.o *.fd

.PHONY: clean
