use32
global main
extern puts
section text
main:
	push ans
	call puts
	add esp, 4
	xor eax, eax
	ret
section data
	ans db "77", 0x0A, 0x00