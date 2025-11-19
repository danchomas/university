section .data
    arr     dd  5, -9, 7, 3, 77, 7, 1, -2
    n       dd  ($ - arr) / 4
    fmtNum  db  "%d ", 0                    ; формат печати числа

section .text
    global main
    extern printf
    extern exit

main:
    mov  ecx, [n]           ; ECX = n
    dec  ecx                ; ECX = n-1

outer:
    mov  edi, ecx           ; счётчик оставшихся сравнений
    mov  esi, 0             ; ESI = индекс j = 0

inner:
    mov  eax, [arr + esi*4]     ; EAX = arr[j]
    mov  ebx, [arr + esi*4 + 4] ; EBX = arr[j+1]
    cmp  eax, ebx
    jle  noswap                  ; если arr[j] <= arr[j+1], пропустить обмен

    ; обмен элементов
    mov  [arr + esi*4], ebx
    mov  [arr + esi*4 + 4], eax

noswap:
    inc  esi
    dec  edi
    jnz  inner

    dec  ecx
    jnz  outer

    mov  esi, 0              ; ESI = 0 (индекс)

print_loop:
    mov  eax, [arr + esi*4]  ; EAX = arr[ESI]

    ; вызов printf (cdecl)
    push eax
    push fmtNum
    call printf
    add  esp, 8              ; очистка стека после printf

    inc  esi
    cmp  esi, [n]
    jl   print_loop

    push 0
    call exit
