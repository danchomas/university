default rel             ; исправляет warning

section .data
    hex_format db "%02X", 0
    newline    db 0xA, 0

    number_a:
        times 44 db 0xAA    ; Младшие 44 байта
        db 0xF0             ; Старший байт (45-й)

    pow_n dd 4              ; Степень сдвига

section .bss
    result_res resb 45

section .text
    global main
    extern printf

main:
    push rbp
    mov rbp, rsp

    ; Подготовка аргументов: RDI=a, ESI=n, RDX=res
    mov rdi, number_a
    mov esi, [pow_n]
    lea rdx, [result_res]   ; Используем LEA для корректной адресации

    call division

    mov rbx, 44             ; Индекс старшего байта

print_loop:
    xor rax, rax
    mov al, [result_res + rbx]

    push rbx
    push rdx                ; Сохраним rdx, так как printf может его затереть

    mov rdi, hex_format
    mov rsi, rax
    xor rax, rax
    call printf

    pop rdx
    pop rbx

    dec rbx
    jns print_loop          ; Пока rbx >= 0

    ; Перевод строки
    mov rdi, newline
    xor rax, rax
    call printf

    pop rbp
    mov rax, 60             ; sys_exit
    xor rdi, rdi
    syscall

; division(char* a, int n, char* res)
division:
    push rbx
    push r12

    ; 1. Копирование памяти (a -> res)
    mov rcx, 45
    xor rbx, rbx
copy_loop:
    mov al, [rdi + rbx]
    mov [rdx + rbx], al
    inc rbx
    loop copy_loop

    ; 2. Проверка n=0
    test esi, esi
    jz div_end

    ; 3. Внешний цикл (счетчик сдвигов)
    mov r12d, esi

shift_outer_loop:
    ; --- Обработка старшего байта (индекс 44) ---
    mov rbx, 44
    sar byte [rdx + rbx], 1 ; Знаковый сдвиг. CF устанавливается здесь.

    dec rbx                 ; Переход к индексу 43. DEC не меняет CF.

    ; --- Внутренний цикл (индексы 43 -> 0) ---
shift_inner_loop:
    ; [FIX] Убрали CMP. Используем JNS после DEC в конце.

    rcr byte [rdx + rbx], 1 ; Сдвиг через перенос. Берет CF от предыдущего байта.

    dec rbx                 ; Уменьшаем индекс. CF не меняется.
    jns shift_inner_loop    ; Если индекс >= 0 (Not Sign), продолжаем.

    ; Конец прохода по числу
    dec r12d                ; Уменьшаем счетчик n
    jnz shift_outer_loop    ; Если n > 0, повторяем

div_end:
    pop r12
    pop rbx
    ret
