section .bss
    str1 resb 256
    str2 resb 256

section .text
    global _start

_start:

    mov eax, 3
    mov ebx, 0
    mov ecx, str1
    mov edx, 256
    int 0x80
    mov byte [str1 + eax - 1], 0

    mov eax, 3
    mov ebx, 0
    mov ecx, str2
    mov edx, 256
    int 0x80
    mov byte [str2 + eax - 1], 0


    mov esi, str1
find_end:
    cmp byte [esi], 0
    je concat_strings
    inc esi
    jmp find_end

concat_strings:
    mov edi, str2
concat_loop:
    mov al, [edi]
    mov [esi], al
    inc esi
    inc edi
    cmp byte [edi], 0
    jne concat_loop


    mov byte [esi], 0


    mov eax, 4
    mov ebx, 1
    mov ecx, str1
    mov edx, esi
    sub edx, str1
    int 0x80


    mov eax, 1
    xor ebx, ebx
    int 0x80
