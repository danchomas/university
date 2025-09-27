; Файл: zadanie1.asm
; Компиляция: nasm -f elf32 zadanie1.asm -o zadanie1.o
; Сборка: gcc -m32 -no-pie zadanie1.o -o zadanie1
; Запуск: ./zadanie1

extern printf
extern exit

section .data
    str1 db "some string 1", 0
    a dd 1000

    ; Формат: длина, конец, начало, имя
    str_format db "%d\t0x%08x\t0x%08x\t%s", 10, 0  ; \t — табуляция, \n — перевод строки

    str1_name db "str1", 0
    a_name db "a", 0

section .text
    global main

main:
    ; Вывод для str1: длина=14, конец=str1+14, начало=str1, имя="str1"
    push dword str1_name        ; %s — имя
    push dword str1             ; %08x — начало
    push dword str1 + 14        ; %08x — конец
    push dword 14               ; %d — длина
    push dword str_format       ; форматная строка
    call printf
    add esp, 20                 ; 5 аргументов * 4 = 20 байт

    ; Вывод для a: размер=4, конец=a+4, начало=a, имя="a"
    push dword a_name           ; %s
    push dword a                ; начало
    push dword a + 4            ; конец
    push dword 4                ; размер
    push dword str_format       ; формат
    call printf
    add esp, 20

    ; Завершение программы
    push dword 0
    call exit
