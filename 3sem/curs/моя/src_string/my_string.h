#ifndef SRC_MY_STRING_H_
#define SRC_MY_STRING_H_

#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>

#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__)
typedef uint64_t size_t;  // 64-битная система
#else
typedef uint32_t size_t;  // 32-битная система
#endif

#define ASCII_SHIFT 32

// Находит первое вхождение символа в блоке памяти указанной длины
extern void *find_byte(const void *str, int symbol, size_t n);

// Сравнивает два блока памяти указанной длины
extern int compare_memory(const void *str1, const void *str2, size_t n);

// Заполняет блок памяти указанным символом на заданную длину
extern void *fill_memory(void *str, int symbol, size_t n);

// Копирует блок памяти из одного места в другое
extern void *copy_memory(void *dest, const void *src, size_t n);

// Конкатенирует (объединяет) строки с ограничением максимальной длины
extern char *concat_strings_limited(char *dest, const char *src, size_t n);

// Вычисляет длину строки
extern size_t get_string_length(const char *str);

// Находит первое вхождение указанного символа в строке
extern char *find_first_char(const char *str, int symbol);

// Копирует строку с ограничением максимальной длины
extern char *copy_string_limited(char *dest, const char *src, size_t n);

// Подсчитывает количество несовпадающих символов между двумя строками
extern size_t count_not_matching_chars(const char *str1, const char *str2);

// Сравнивает строки с ограничением максимальной длины
extern int compare_strings_limited(const char *str1, const char *str2, size_t n);

// Находит первый совпадающий символ между двумя строками
extern char *find_first_matching_char(const char *str1, const char *str2);

// Находит последнее вхождение символа в строке
extern char *find_last_char(const char *str, int symbol);

// Разделяет строку на части по указанному разделителю
extern char *split_string(char *str, const char *delim);

// Преобразует строку в верхний регистр
extern void *convert_to_uppercase(const char *str);

// Преобразует строку в нижний регистр
extern void *convert_to_lowercase(const char *str);

// Вставляет одну строку в другую по указанному индексу
extern void *insert_string(const char *src, const char *str, size_t start_index);

// Удаляет символы по краям строки, указанные в trim_chars
extern void *trim_string_edges(const char *src, const char *trim_chars);

// Конкатенирует (объединяет) строки без ограничения длины
extern char *concat_strings(char *dest, const char *src);

// Копирует строку без ограничения длины
extern char *copy_string(char *dest, const char *src);

// Подсчитывает количество совпадающих символов между двумя строками
extern size_t count_matching_chars(const char *str1, const char *str2);

#endif