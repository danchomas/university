section .data
    output_msg db "Результат: 0x%08X", 10, 0
    format db "%x", 0
    number dd 0
    result dd 0
    flag db 0          ; Флаг: начали ли мы обрабатывать значащие цифры

section .text
    global main
    extern scanf
    extern printf

main:
    ; Ввод числа
    push number
    push format
    call scanf
    add esp, 8

    ; Загружаем число в регистр
    mov eax, [number]
    mov ebx, 0          ; Результат
    mov byte [flag], 0  ; Сбрасываем флаг

    ; Проверяем на ноль
    test eax, eax
    jz print_result

    mov edx, eax        ; Рабочая копия

extract_loop:
    ; Циклический сдвиг влево на 4 бита
    rol edx, 4

    ; Получаем текущую цифру (младшие 4 бита после сдвига)
    mov esi, edx
    and esi, 0x0000000F

    ; Если флаг = 0 и цифра = 0, пропускаем
    cmp byte [flag], 0
    jne process_digit
    test esi, esi
    jnz process_digit
    jmp continue

process_digit:
    ; Устанавливаем флаг, что начали обработку
    mov byte [flag], 1

    ; Сравниваем с A (10 в десятичной)
    cmp esi, 0x0A
    jl skip_digit       ; Если меньше A - пропускаем

    ; Если цифра >= A, добавляем ее в результат
    shl ebx, 4          ; Сдвигаем результат на 4 бита влево
    or ebx, esi         ; Добавляем текущую цифру

skip_digit:
    ; Продолжаем цикл
    jmp continue

continue:
    ; Проверяем, не вернулись ли к исходному числу
    cmp edx, eax
    jne extract_loop    ; Продолжаем, пока не вернемся к исходному

print_result:
    ; Сохраняем результат
    mov [result], ebx

    ; Вывод результата
    push ebx
    push output_msg
    call printf
    add esp, 8

    ; Выход из программы
    mov eax, 0
    ret
