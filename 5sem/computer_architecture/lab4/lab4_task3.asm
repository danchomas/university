; Лабораторная работа №4 - Задание 3 (Вариант 14, задача 6)
; Подсчёт целых точек на отрезке через НОД
; NASM для Arch Linux

section .data
    ; Координаты точек (целые числа)
    x1 dd 0              ; x координата первой точки
    y1 dd 0              ; y координата первой точки
    x2 dd 5              ; x координата второй точки
    y2 dd 7              ; y координата второй точки

    format db "Количество целых точек между (%d, %d) и (%d, %d): %d", 10, 0

section .text
    global main
    extern printf

; Функция вычисления НОД (алгоритм Евклида)
; Аргументы: [ebp+8] = a, [ebp+12] = b
; Возвращает НОД в EAX
gcd:
    push ebp
    mov ebp, esp
    push ebx

    mov eax, [ebp+8]     ; EAX = a
    mov ebx, [ebp+12]    ; EBX = b

    ; Проверяем, что оба числа положительные (берём модули)
    cmp eax, 0
    jge gcd_a_positive
    neg eax
gcd_a_positive:

    cmp ebx, 0
    jge gcd_b_positive
    neg ebx
gcd_b_positive:

gcd_loop:
    ; Проверяем, если b == 0, то НОД = a
    cmp ebx, 0
    je gcd_end

    ; Иначе: temp = a % b, a = b, b = temp
    xor edx, edx         ; Обнуляем EDX для деления
    push ebx             ; Сохраняем b
    idiv ebx             ; EAX = a / b, EDX = a % b
    pop eax              ; EAX = b
    mov ebx, edx         ; EBX = a % b

    jmp gcd_loop

gcd_end:
    ; EAX содержит НОД
    pop ebx
    pop ebp
    ret 8

main:
    push ebp
    mov ebp, esp

    ; Вычисляем |x2 - x1|
    mov eax, [x2]
    sub eax, [x1]        ; EAX = x2 - x1

    ; Берём модуль (на случай, если вдруг x2 < x1, хотя по условию x1 < x2)
    cmp eax, 0
    jge dx_positive
    neg eax
dx_positive:
    push eax             ; Сохраняем |x2 - x1|

    ; Вычисляем |y2 - y1|
    mov eax, [y2]
    sub eax, [y1]        ; EAX = y2 - y1

    ; Берём модуль
    cmp eax, 0
    jge dy_positive
    neg eax
dy_positive:
    push eax             ; Сохраняем |y2 - y1|

    ; Вызываем функцию gcd(|x2-x1|, |y2-y1|)
    call gcd             ; Результат в EAX

    ; Вычисляем результат = НОД - 1
    dec eax              ; EAX = gcd - 1

    ; Вывод результата
    push eax             ; Количество точек
    push dword [y2]
    push dword [x2]
    push dword [y1]
    push dword [x1]
    push format
    call printf
    add esp, 24

    ; Выход
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
