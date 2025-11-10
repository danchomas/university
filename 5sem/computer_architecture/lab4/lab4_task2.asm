section .data
    x dd 10, -5       ; массив 4-байтовых знаковых чисел
    y dw 2, 10        ; массив 2-байтовых беззнаковых чисел
    n dw 1                  ; количество элементов (от 0 до n, т.е. n+1 элементов)

    format db "r = %d", 10, 0

section .bss
    sum1 resd 1             ; Первая сумма
    sum2 resd 1             ; Вторая сумма

section .text
    global main
    extern printf
    extern exit

; Функция f(x, y)
; Аргументы: [ebp+8] = x (4 байта), [ebp+12] = y (4 байта)
; Возвращает результат в EAX
f:
    push ebp
    mov ebp, esp
    push ebx

    mov eax, [ebp+8]     ; EAX = x
    mov ebx, [ebp+12]    ; EBX = y

    ; Проверяем x > 7
    cmp eax, 7
    jg f_case1           ; Если x > 7

    ; Иначе x <= 7: f(x,y) = (x - y)^3
    sub eax, ebx         ; EAX = x - y
    mov ebx, eax         ; EBX = x - y
    imul eax, ebx        ; EAX = (x-y)^2
    imul eax, ebx        ; EAX = (x-y)^3
    jmp f_end

f_case1:
    ; f(x,y) = |x + y| / 200
    add eax, ebx         ; EAX = x + y

    ; Вычисляем |x + y|
    cmp eax, 0
    jge f_abs_done
    neg eax              ; Если отрицательное, делаем положительным
f_abs_done:

    ; Делим на 200
    cdq                  ; Расширяем EAX до EDX:EAX
    mov ebx, 200
    idiv ebx             ; EAX = |x + y| / 200

f_end:
    pop ebx
    pop ebp
    ret 8                ; Очищаем стек от 8 байт

main:
    push ebp
    mov ebp, esp

    ; Обнуляем суммы
    mov dword [sum1], 0
    mov dword [sum2], 0

    xor esi, esi         ; ESI = индекс i
    xor ecx, ecx
    mov cx, [n]          ; ECX = n
    inc ecx              ; ECX = n + 1 (количество итераций)

loop_start:
    ; Первая сумма: накапливаем x[i]
    mov eax, [x + esi*4] ; EAX = x[i]
    add [sum1], eax      ; sum1 += x[i]

    ; Проверяем четность i
    test esi, 1          ; Проверяем младший бит
    jnz odd_case         ; Если i нечётное

even_case:
    ; i чётное: x_i / y_i + f(x_i, y_i)
    mov eax, [x + esi*4] ; EAX = x[i]
    xor edx, edx
    movzx edx, word [y + esi*2] ; EDX = y[i]

    ; Сохраняем для вызова функции
    push edx             ; Сохраняем y[i]
    push eax             ; Сохраняем x[i]

    ; Деление x[i] / y[i]
    cdq                  ; Расширяем EAX до EDX:EAX
    idiv dword [esp+4]   ; Делим на y[i]
    push eax             ; Сохраняем результат деления

    ; Вызов функции f(x[i], y[i])
    ; Аргументы уже в стеке (после push eax)
    push dword [esp+8]   ; y[i]
    push dword [esp+8]   ; x[i]
    call f               ; Результат в EAX

    pop ebx              ; EBX = результат деления (x[i]/y[i])
    add esp, 8           ; Очищаем x[i] и y[i]

    add eax, ebx         ; EAX = x[i]/y[i] + f(x[i], y[i])
    add [sum2], eax      ; sum2 += результат

    jmp loop_continue

odd_case:
    ; i нечётное: x_i + y_i^2 + f(x_i^2, y_i^2)
    mov eax, [x + esi*4] ; EAX = x[i]
    add [sum2], eax      ; sum2 += x[i]

    xor edx, edx
    movzx edx, word [y + esi*2] ; EDX = y[i]
    mov eax, edx         ; EAX = y[i]
    imul eax, edx        ; EAX = y[i]^2
    add [sum2], eax      ; sum2 += y[i]^2
    push eax             ; Сохраняем y[i]^2

    ; Вычисляем x[i]^2
    mov eax, [x + esi*4] ; EAX = x[i]
    imul eax             ; EDX:EAX = x[i]^2

    ; Вызов f(x[i]^2, y[i]^2)
    push dword [esp]     ; y[i]^2
    push eax             ; x[i]^2
    call f               ; Результат в EAX

    add esp, 4           ; Убираем y[i]^2
    add [sum2], eax      ; sum2 += f(x[i]^2, y[i]^2)

loop_continue:
    inc esi              ; i++
    dec ecx              ; ECX--
    jnz loop_start       ; Переход если ECX != 0

    ; r = sum1 + sum2
    mov eax, [sum1]
    add eax, [sum2]

    ; Вывод результата
    push eax
    push format
    call printf
    add esp, 8

    ; Выход из программы
    push 0
    call exit
