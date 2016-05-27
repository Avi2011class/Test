global main
extern printf
extern scanf
section .text
main:
	sub esp, 8
	mov eax, esp
	push eax
	add eax, 4
	push eax
	push scan
	call scanf
	add esp, 12
	pop ebx; больше говнокода
	pop eax
	sub eax, ebx
	push eax
	push print
	call printf
	add esp, 8
	xor eax, eax
	ret
section .data
	scan db "%d %d", 0x00
	print db "%d", 0x0A, 0x00