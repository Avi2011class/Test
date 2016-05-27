use32
global main
extern getchar
extern printf
section .text
main:
  pusha
  call getchar
      cmp al, 'n'
      mov edx, timenop
      je .endin
      cmp al, 'f'
      mov edx, timefdiv
      je .endin
      cmp al, 'i'
      mov edx, timeidiv
      je .endin
      mov eax, 1
      ret
  .endin:
  call edx
  shr eax, 16
  push eax
  push print_fmt
  call printf
  add esp, 8
  popa
  xor eax, eax
ret
;---------------------------------------------------
timenop:
  lfence
  rdtsc
  mov esi, eax  
  %rep 65536
  nop
  %endrep
  lfence
  rdtsc
  mov edi, eax
  lfence
  rdtsc
  sub eax, edi
  sub edi, esi
  add eax, edi
  ret
;--------------------------------------------------
timeidiv:
  lfence
  rdtsc
  mov esi, eax  
  %rep 65536
  mov eax, 100500
  cdq
  mov ebx, 1
  idiv ebx
  %endrep
  lfence
  rdtsc
  mov edi, eax
  lfence
  rdtsc
  sub eax, edi
  sub edi, esi
  add eax, edi
  ret
;------------------------------------------
timefdiv:
  lfence
  rdtsc
  mov esi, eax    
  %rep 65536
  fld dword [dd1]
  fdiv dword [dd2]
  %endrep
  lfence
  rdtsc
  mov edi, eax
  lfence
  rdtsc
  nop
  sub eax, edi
  sub edi, esi
  add eax, edi
  ret
;------------------------------------------
section .data
  dd1 dd 100.5
  dd2 dd 4.2
  alltime dd 0
  timeptr dd 0
  print_fmt db "%u", 0x0A, 0x00