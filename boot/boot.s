; First we declare the "kernel_main" as being external to this file
; It is the name of the main C function in the kernel.c file

.extern kernel_main

; Now to declare the "start" label as global so we can access from outside this file

.global start

; Using the GRUB bootloader, it needs basic information about our kernel before it can boot
; We pass this to GRUB with a standard known as Multiboot
; Define valid Multiboot header which can be recognised by GRUB
; Hardcode constants into the excecutable. The following code calculates the constants

.set MB_MAGIC 0x1BADB002    ; This is a magic constant which GRUB uses to detect kernel location

.set MB_FLAGS, (1 << 0) | (1 << 1)  ; This tells GRUB to load modules on page boundaries first and then provide a memory map

.set MB_CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS))   ; Calculate checksum that includes all previous values

; The following section contains the Multiboot header

.section .multiboot
.align 4                    ; Aligns following data on a multiple of 4 bytes
.long MB_MAGIC
.long MB_FLAGS
.long MB_CHECKSUM

