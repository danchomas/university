; lab5_v14.asm
; Вариант 14
; S = sum( (1 - cos(1/n)) * q^n ), где q = 1/2

extern printf

section .data
    fmt_iter db "n = %d; S = %.10f", 10, 0 ; Формат вывода

    val_q       dq 0.5      ; q = 1/2
    val_1       dq 1.0      ; Константа 1.0

    ; Переменная для сохранения текущего S
    total_sum   dq 0.0

section .bss
    temp_n      resq 1      ; Для загрузки n в FPU

section .text
    global main

; Функция my_pow (x^y)
; Вход:
;   ST(0) = y (показатель степени)
;   ST(1) = x (основание)
; Выход:
;   ST(0) = result
;   Основание x удаляется из стека.
; Формула: x^y = 2^(y * log2(x))
my_pow:
    fyl2x               ; ST(0) = y * log2(x), pop y

    ; Вычисляем 2^ST(0). Нужно разбить на целую и дробную части.
    fld     st0         ; Дублируем значение
    frndint             ; Округляем до целого (Int)
    fsub    st1, st0    ; ST(1) = Total - Int = Frac (дробная часть)
    fxch    st1         ; ST(0) = Frac, ST(1) = Int

    f2xm1               ; ST(0) = (2^Frac) - 1
    fld1                ; Загружаем 1.0
    faddp               ; ST(0) = 2^Frac

    fscale              ; ST(0) = ST(0) * 2^Int
    fstp    st1         ; Удаляем Int
    ret

; Основная программа
main:
    push    rbp
    mov     rbp, rsp

    finit               ; Инициализация сопроцессора
    fldz                ; Загружаем 0.0
    fstp    qword [total_sum] ; S = 0

    ; --- Цикл по n от 1 до 50 ---
    mov     rbx, 1      ; rbx - счетчик n

loop_start:
    cmp     rbx, 50
    jg      loop_end

    ; Шаг 1: Вычисляем (1 - cos(1/n))
    fld1                ; ST(0) = 1.0

    mov     [temp_n], rbx
    fild    qword [temp_n] ; ST(0) = n, ST(1) = 1.0

    fdivp   st1, st0    ; ST(0) = 1.0 / n

    fcos                ; ST(0) = cos(1/n)

    fld1                ; ST(0) = 1.0, ST(1) = cos(1/n)
    fsubrp  st1, st0    ; ST(0) = 1.0 - cos(1/n)

    ; Теперь в ST(0) лежит первая часть формулы.

    ; Шаг 2: Вычисляем q^n = (0.5)^n
    fld     qword [val_q] ; ST(0)=0.5, ST(1)=(1-cos)

    mov     [temp_n], rbx
    fild    qword [temp_n] ; ST(0)=n, ST(1)=0.5, ST(2)=(1-cos)

    ; Вызываем my_pow(0.5, n) -> результат будет в ST(0)
    ; my_pow ожидает: ST(0)=y, ST(1)=x. У нас так и есть: y=n, x=0.5
    call    my_pow        ; ST(0) = 0.5^n

    ; Шаг 3: Перемножаем и суммируем
    ; Сейчас стек: ST(0) = q^n, ST(1) = (1-cos)
    fmulp   st1, st0      ; ST(0) = (1-cos) * q^n

    ; Добавляем к общей сумме
    fld     qword [total_sum] ; ST(0)=S, ST(1)=Term
    faddp   st1, st0          ; ST(0)=S+Term
    fstp    qword [total_sum] ; Сохраняем обратно в память

    ; Вывод на экран
    mov     rdi, fmt_iter
    mov     rsi, rbx           ; n
    movsd   xmm0, [total_sum]  ; S (для printf)
    mov     rax, 1             ; Кол-во векторных регистров
    call    printf WRT ..plt

    ; Следующая итерация
    inc     rbx
    jmp     loop_start

loop_end:
    ; Завершение
    mov     rsp, rbp
    pop     rbp
    xor     rax, rax
    ret
