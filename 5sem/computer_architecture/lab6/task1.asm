section .data
    newline db 10

section .text
    global _start

_start:
    ; Внешний цикл: длина последовательности единиц (len) от 2 до 7
    mov r8, 2           ; r8 = длина (len)

loop_len:
    cmp r8, 7
    jg exit_prog        ; Если len > 7, выход

    ; Создаем базовую маску из r8 единиц.
    ; Формула: (1 << r8) - 1
    mov rcx, r8         ; Подготовка для сдвига
    mov rax, 1
    shl rax, cl         ; 1 << len
    dec rax             ; (1 << len) - 1
    mov r9, rax         ; r9 хранит базовый блок единиц (например, 11, 111...)

    ; Внутренний цикл: сдвиг (shift) от 0 до (34 - len)
    mov r10, 0          ; r10 = текущий сдвиг (shift)

loop_shift:
    mov r11, 34
    sub r11, r8         ; r11 = 34 - len (максимальный сдвиг)
    cmp r10, r11
    jg next_len         ; Если сдвиг больше допустимого, переходим к следующей длине

    ; Формируем число: base_mask << shift
    mov rax, r9         ; Восстанавливаем базовую маску
    mov rcx, r10
    shl rax, cl         ; Сдвигаем на позицию r10

    ; Выводим число в RAX на экран в двоичном виде (34 бита)
    push rax            ; Сохраняем регистры перед вызовом
    push r8
    push r9
    push r10
    push r11

    call print_binary_34

    pop r11
    pop r10
    pop r9
    pop r8
    pop rax

    inc r10             ; shift++
    jmp loop_shift

next_len:
    inc r8              ; len++
    jmp loop_len

exit_prog:
    mov rax, 60         ; sys_exit
    xor rdi, rdi        ; status 0
    syscall

; --- Подпрограмма вывода 34 бит числа из RAX ---
print_binary_34:
    mov rbx, rax        ; Сохраняем число в RBX для работы
    mov r12, 33         ; Начинаем с 33-го бита (всего 0..33 = 34 бита)

print_bit_loop:
    mov rax, rbx        ; Копируем число
    mov rcx, r12        ; Текущий номер бита для сдвига
    shr rax, cl         ; Сдвигаем бит в младшую позицию
    and rax, 1          ; Изолируем бит (0 или 1)

    add rax, '0'        ; Преобразуем в ASCII ('0' или '1')

    ; Вывод символа (прямой сисколл для простоты)
    push rax            ; Кладем символ в стек
    mov rax, 1          ; sys_write
    mov rdi, 1          ; stdout
    mov rsi, rsp        ; адрес буфера (стек)
    mov rdx, 1          ; длина 1 байт
    syscall
    pop rax             ; Восстанавливаем стек

    dec r12
    cmp r12, 0
    jge print_bit_loop  ; Если r12 >= 0, продолжаем

    ; Вывод перевода строки
    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    syscall

    ret
