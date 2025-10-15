section .text
    global _start

_start:
    ; Часть 1: Символьные команды → машинный код 
    add ax, 8080                    ; ADD AX, 8080
    and bl, al                      ; AND BL, AL
    test byte [ebx + 0xE2], 9       ; TEST BYTE PTR [EBX + 0E2h], 9
    mov dx, [ecx*4 + 0x34]          ; MOV DX, [ECX*4 + 34h]
    or [eax], dx                    ; OR [EAX], DX

    ; Часть 2: Машинные коды → символьные команды (вставлены как байты)
    db 0x8B, 0x44, 0x1F, 0x11
    db 0x8B, 0x5D, 0x02 

    ; === Завершение программы ===
    mov eax, 1
    xor ebx, ebx 
    int 0x80