section .data
    x db -3              ; знаковое однобайтовое
    y dw -5             ; знаковое 2-байтовое
    z dw 10               ; беззнаковое 2-байтовое

    format db "p = %d", 10, 0

section .text
    global _start
    extern printf
    extern exit

_start:
    ; Проверка условия |x| > 3
    XOR EAX, EAX         ; Обнулить EAX
    MOV AL, [x]          ; AL = x
    CBW                  ; Расширить до 2 байт (AX)
    CWDE                 ; Расширить до 4 байт (EAX)

    ; Вычисляем |x|
    MOV EBX, EAX         ; Сохраняем x в EBX
    CMP EAX, 0
    JGE abs_done         ; Если x >= 0, то |x| = x
    NEG EAX              ; Иначе |x| = -x
abs_done:

    ; Проверяем |x| > 3
    CMP EAX, 3
    JG case1             ; Если |x| > 3, переход к case1

    ; Иначе x ∈ [-3, 3]
    ; Нужно проверить z
    XOR ECX, ECX
    MOV CX, [z]          ; ECX = z (беззнаковое, просто загружаем)

    ; Проверяем z ∈ [-2, 2] для беззнакового z это z ∈ [0, 2]
    CMP ECX, 2
    JBE case3            ; Если z <= 2, то z ∈ [0, 2] -> case3

    ; Иначе z > 2, т.е. z ∉ [-2, 2] -> case2
    JMP case2

case1:
    ; p = x^2 + 1 + z
    MOV EAX, EBX         ; EAX = x
    IMUL EAX             ; EDX:EAX = x^2
    ADD EAX, 1           ; EAX = x^2 + 1
    XOR ECX, ECX
    MOV CX, [z]          ; ECX = z
    ADD EAX, ECX         ; EAX = x^2 + 1 + z
    JMP output

case2:
    ; p = x / (4 - z^2)
    XOR ECX, ECX
    MOV CX, [z]          ; ECX = z
    MOV EAX, ECX         ; EAX = z
    IMUL EAX             ; EDX:EAX = z^2
    MOV ECX, EAX         ; ECX = z^2
    MOV EAX, 4           ; EAX = 4
    SUB EAX, ECX         ; EAX = 4 - z^2
    MOV ECX, EAX         ; ECX = делитель (4 - z^2)

    MOV EAX, EBX         ; EAX = x
    CDQ                  ; Расширить EAX до EDX:EAX для деления
    IDIV ECX             ; EAX = x / (4 - z^2)
    JMP output

case3:
    ; p = x - y - 2z
    MOV EAX, EBX         ; EAX = x
    XOR ECX, ECX
    MOV CX, [y]          ; ECX = y
    CWDE                 ; Расширить CX до ECX со знаком
    MOVSX ECX, word [y]  ; ECX = y (знаковое расширение)
    SUB EAX, ECX         ; EAX = x - y

    XOR ECX, ECX
    MOV CX, [z]          ; ECX = z
    SHL ECX, 1           ; ECX = 2*z
    SUB EAX, ECX         ; EAX = x - y - 2z

output:
    ; Вывод результата
    push eax
    push format
    call printf
    add esp, 8

    ; Выход из программы
    push 0
    call exit
