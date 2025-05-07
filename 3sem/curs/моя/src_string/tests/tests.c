#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../my_string.h"

START_TEST(test_memchr_1) {  // Тест 1: Поиск символа 'W'
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(find_byte(str, 'W', 13), strchr(str, 'W'));
}
END_TEST

START_TEST(test_memchr_2) {  // Тест 2: Поиск символа 'H'
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(find_byte(str, 'H', 13), strchr(str, 'H'));
}
END_TEST

START_TEST(test_memchr_3) {  // Тест 3: Поиск символа 'o'
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(find_byte(str, 'o', 13), strchr(str, 'o'));
}
END_TEST

START_TEST(test_memchr_4) {  // Тест 4: Поиск символа ','
  char str[] = "Hello, World!";
  size_t len = strlen(str);
  ck_assert_ptr_eq(find_byte(str, ',', len), strchr(str, ','));
}
END_TEST

START_TEST(test_memchr_5) {  // Тест 5: Поиск символа '!'
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(find_byte(str, '!', 13), strchr(str, '!'));
}
END_TEST

START_TEST(test_memchr_6) {  // Тест 6: Поиск символа 'e'
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(find_byte(str, 'e', 13), strchr(str, 'e'));
}
END_TEST

START_TEST(test_memchr_7) {  // Тест 7: Поиск символа 'l' (первое вхождение)
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(find_byte(str, 'l', 13), strchr(str, 'l'));
}
END_TEST

START_TEST(test_memchr_8) {  // Тест 8: Поиск символа 'l' (второе вхождение)
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(find_byte(str, 'l', 10), strchr(str, 'l'));
}
END_TEST

START_TEST(test_memchr_9) {  // Тест 9: Поиск символа 'x' (не найден)
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(find_byte(str, 'x', 13), NULL);
}
END_TEST

START_TEST(test_memchr_10) {  // Тест 10: Поиск символа в пустой строке
  char empty[] = "";
  ck_assert_ptr_eq(find_byte(empty, 'a', 0), NULL);
}
END_TEST

START_TEST(test_memcmp_1) {  // Тест 1: Сравнение одинаковых строк
  char str1[] = "Hello";
  char str2[] = "Hello";
  ck_assert_int_eq(compare_memory(str1, str2, 5), memcmp(str1, str2, 5));
}
END_TEST

START_TEST(
    test_memcmp_2) {  // Тест 2: Сравнение первых 4 символов одинаковых строк
  char str1[] = "Hello";
  char str2[] = "Hello";
  ck_assert_int_eq(compare_memory(str1, str2, 4), memcmp(str1, str2, 4));
}
END_TEST

START_TEST(test_memcmp_3) {  // Тест 3: Сравнение различных строк
  char str1[] = "Hello";
  char str3[] = "Hellz";
  ck_assert_int_eq(compare_memory(str1, str3, 5), memcmp(str1, str3, 5));
}
END_TEST

START_TEST(test_memcmp_4) {  // Тест 4: Сравнение строк разной длины
  char str1[] = "Hello";
  char str4[] = "Hello, World!";
  ck_assert_int_eq(compare_memory(str1, str4, 5), 0);
}
END_TEST

START_TEST(test_memcmp_5) {  // Тест 5: Сравнение с пустой строкой
  char str1[] = "Hello";
  char empty[] = "z     ";
  ck_assert_int_eq(compare_memory(str1, empty, 5), memcmp(str1, empty, 5));
}
END_TEST

START_TEST(test_memcmp_6) {  // Тест 6: Сравнение двух пустых строк
  char empty[] = "";
  ck_assert_int_eq(compare_memory(empty, empty, 0), memcmp(empty, empty, 0));
}
END_TEST

START_TEST(
    test_memcmp_7) {  // Тест 7: Сравнение строк с различием в последнем символе
  char str1[] = "Hello";
  char str5[] = "Hellp";
  ck_assert_int_eq(compare_memory(str1, str5, 5), memcmp(str1, str5, 5));
}
END_TEST

START_TEST(
    test_memcmp_8) {  // Тест 8: Сравнение строк с различием в первом символе
  char str1[] = "Hello";
  char str6[] = "Bello";
  ck_assert_int_eq(compare_memory(str1, str6, 5), memcmp(str1, str6, 5));
}
END_TEST

START_TEST(test_memcmp_9) {  // Тест 9: Сравнение строк с разной длиной и
                             // одинаковыми началом
  char str1[] = "Hello";
  char str7[] = "Hello!";
  ck_assert_int_eq(compare_memory(str1, str7, 5), memcmp(str1, str7, 5));
}
END_TEST

START_TEST(test_memcpy_1) {  // Тест 1: Копирование строки "Hello"
  char dest[20] = {0};  // Initialize the destination array
  const char *src = "Hello";
  ck_assert_ptr_eq(copy_memory(dest, src, 5), dest);
  ck_assert_str_eq(dest, "Hello");
}
END_TEST

START_TEST(test_memcpy_2) {  // Тест 2: Копирование пустой строки
  char dest_empty[20] = {0};  // Initialize the destination array
  const char *src_empty = "";
  ck_assert_ptr_eq(copy_memory(dest_empty, src_empty, 0), dest_empty);
  ck_assert_str_eq(dest_empty, "");
}
END_TEST

START_TEST(test_memcpy_3) {  // Тест 3: Копирование с нулевой длиной
  char dest_null[20] = "Initial";
  const char *src = "Hello";
  ck_assert_ptr_eq(copy_memory(dest_null, src, 0), dest_null);
  ck_assert_str_eq(dest_null, "Initial");
}
END_TEST

START_TEST(
    test_memcpy_4) {  // Тест 4: Копирование в неинициализированный массив
  char uninitialized[20] = {0};  // Initialize the destination array
  const char *src = "Hello";
  ck_assert_ptr_eq(copy_memory(uninitialized, src, 5), uninitialized);
  ck_assert_str_eq(uninitialized, "Hello");
}
END_TEST

START_TEST(test_memcpy_5) {  // Тест 5: Копирование с перезаписью
  char overlap[20] = "Hello, World!";
  ck_assert_ptr_eq(copy_memory(overlap + 7, overlap, 5), overlap + 7);
  ck_assert_str_eq(overlap, "Hello, Hello!");
}
END_TEST

START_TEST(test_memcpy_6) {  // Тест 6: Копирование с частичной перезаписью
  char partial_overlap[20] = "1234567890";
  ck_assert_ptr_eq(copy_memory(partial_overlap + 2, partial_overlap, 5),
                   partial_overlap + 2);
  ck_assert_pstr_ne(partial_overlap, "1231234560");
}
END_TEST

START_TEST(test_memcpy_7) {  // Тест 7: Копирование в массив меньшего размера
                             // (переполнение буфера)
  char small_dest[6] = {
      0};  // Initialize and increase size by 1 for null-termination
  const char *src = "Hello";
  ck_assert_ptr_eq(copy_memory(small_dest, src, 4),
                   small_dest);  // Copy only 4 characters
  small_dest[4] = '\0';          // Ensure null-termination
  ck_assert_str_eq(small_dest, "Hell");
}
END_TEST

START_TEST(test_memcpy_8) {  // Тест 8: Копирование данных с символами
  char special_src[] = "Hello\nWorld!";
  char dest[20] = {0};  // Initialize the destination array
  ck_assert_ptr_eq(copy_memory(dest, special_src, 12), dest);
  dest[12] = '\0';  // Ensure null-termination
  ck_assert_str_eq(dest, "Hello\nWorld!");
}
END_TEST

START_TEST(test_memcpy_9) {  // Тест 9: Копирование в массив, который не
                             // инициализирован
  char uninitialized_dest[20] = {0};  // Initialize the destination array
  char special_src[] = "Hello\nWorld!";
  ck_assert_ptr_eq(copy_memory(uninitialized_dest, special_src, 12),
                   uninitialized_dest);
  uninitialized_dest[12] = '\0';  // Ensure null-termination
  ck_assert_str_eq(uninitialized_dest, "Hello\nWorld!");
}
END_TEST

// memset
START_TEST(test_memset_1) {  // Тест 1: Установка первых 3 символов в 'X'
  char str[10] = "abcdefghi";
  ck_assert_ptr_eq(fill_memory(str, 'X', 3), str);
  ck_assert_str_eq(str, "XXXdefghi");
}
END_TEST

START_TEST(test_memset_2) {  // Тест 3: Установка первых 5 символов в 'Z'
  char str3[10] = "abcdefghi";
  ck_assert_ptr_eq(fill_memory(str3, 'Z', 5), str3);
  ck_assert_str_eq(str3, "ZZZZZfghi");
}
END_TEST

START_TEST(test_memset_3) {  // Тест 4: Установка 0 символов
  char str4[10] = "abcdefghi";
  ck_assert_ptr_eq(fill_memory(str4, 'A', 0), str4);
  ck_assert_str_eq(str4, "abcdefghi");
}
END_TEST

START_TEST(test_memset_4) {  // Тест 5: Установка первых 7 символов в '!'
  char str6[10] = "abcdefghi";
  ck_assert_ptr_eq(fill_memory(str6, '!', 7), str6);
  ck_assert_str_eq(str6, "!!!!!!!hi");
}
END_TEST

START_TEST(test_memset_5) {  // Тест 6: Установка символов в массив, который уже
                             // заполнен
  char str8[10] = "123456789";
  ck_assert_ptr_eq(fill_memory(str8, '#', 3), str8);
  ck_assert_str_eq(str8, "###456789");
}
END_TEST

START_TEST(test_strncat_1) {  // Тест 1: Конкатенация с добавлением 6 символов
  char dest[20] = "Hello";
  const char *src = " World";
  ck_assert_ptr_eq(concat_strings_limited(dest, src, 6), dest);
  ck_assert_str_eq(dest, "Hello World");
}
END_TEST

START_TEST(test_strncat_2) {  // Тест 2: Конкатенация с добавлением 4 символов
  char dest2[20] = "Goodbye";
  const char *src2 = " Cruel World";
  ck_assert_ptr_eq(concat_strings_limited(dest2, src2, 4), dest2);
  ck_assert_str_eq(dest2, "Goodbye Cru");
}
END_TEST

START_TEST(test_strncat_3) {  // Тест 3: Конкатенация с добавлением 0 символов
  char dest3[20] = "Test";
  const char *src3 = " String";
  ck_assert_ptr_eq(concat_strings_limited(dest3, src3, 0), dest3);
  ck_assert_str_eq(dest3, "Test");
}
END_TEST

START_TEST(test_strncat_4) {  // Тест 4: Конкатенация с пустой строкой
  char dest4[20] = "Hello";
  const char *src4 = "";
  ck_assert_ptr_eq(concat_strings_limited(dest4, src4, 5), dest4);
  ck_assert_str_eq(dest4, "Hello");
}
END_TEST

START_TEST(test_strncat_5) {  // Тест 5: Конкатенация, когда dest почти заполнен
  char dest5[20] = "12345";
  const char *src5 = "67890";
  ck_assert_ptr_eq(concat_strings_limited(dest5, src5, 10), dest5);
  ck_assert_str_eq(dest5, "1234567890");
}
END_TEST

START_TEST(test_strncat_6) {  // Тест 6: Конкатенация, когда dest заполнен
  char dest6[20] = "Hello";
  const char *src6 = " World!";
  ck_assert_ptr_eq(concat_strings_limited(dest6, src6, 10), dest6);
  ck_assert_str_eq(dest6, "Hello World!");
}
END_TEST

START_TEST(test_strncat_7) {  // Тест 7: Конкатенация с символами
  char dest7[20] = "Data:";
  const char *src7 = " 1234";
  ck_assert_ptr_eq(concat_strings_limited(dest7, src7, 5), dest7);
  ck_assert_str_eq(dest7, "Data: 1234");
}
END_TEST

START_TEST(test_strncat_8) {  // Тест 8: Конкатенация, когда dest пуст
  char dest8[20] = "";
  const char *src8 = "Empty";
  ck_assert_ptr_eq(concat_strings_limited(dest8, src8, 5), dest8);
  ck_assert_str_eq(dest8, "Empty");
}
END_TEST

START_TEST(test_strchr_1) {  // Тест 1: Поиск символа 'W'
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(find_first_char(str, 'W'), strchr(str, 'W'));
}
END_TEST

START_TEST(test_strchr_2) {  // Тест 2: Поиск символа, которого нет в строке
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(find_first_char(str, 'x'), NULL);
}
END_TEST

START_TEST(test_strchr_3) {  // Тест 3: Поиск первого символа 'o'
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(find_first_char(str, 'o'), strchr(str, 'o'));
}
END_TEST

START_TEST(test_strchr_4) {  // Тест 4: Поиск последнего символа '!'
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(find_first_char(str, '!'), strchr(str, '!'));
}
END_TEST

START_TEST(test_strchr_5) {  // Тест 5: Поиск первого символа 'H'
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(find_first_char(str, 'H'), strchr(str, 'H'));
}
END_TEST

START_TEST(test_strchr_6) {  // Тест 6: Поиск символа в пустой строке
  char empty_str[] = "";
  ck_assert_ptr_eq(find_first_char(empty_str, 'a'), NULL);
}
END_TEST

START_TEST(test_strchr_7) {  // Тест 7: Поиск символа в строке, состоящей только
                             // из одного символа
  char single_char_str[] = "A";
  ck_assert_ptr_eq(find_first_char(single_char_str, 'A'),
                   strchr(single_char_str, 'A'));
  ck_assert_ptr_eq(find_first_char(single_char_str, 'B'), NULL);
}
END_TEST

START_TEST(test_strchr_8) {  // Тест 8: Поиск символа, который находится в
                             // начале строки
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(find_first_char(str, 'H'), strchr(str, 'H'));
}
END_TEST

START_TEST(
    test_strchr_9) {  // Тест 9: Поиск символа, который находится в конце строки
  char str[] = "Hello, World!";
  ck_assert_ptr_eq(find_first_char(str, '!'), strchr(str, '!'));
}
END_TEST

START_TEST(test_strncmp_1) {  // Тест 1: Сравнение двух одинаковых строк
  char str1[] = "Hello";
  char str2[] = "Hello";
  ck_assert_int_eq(compare_strings_limited(str1, str2, 5), 0);
  ck_assert_int_eq(compare_strings_limited(str1, str2, 4), 0);
}
END_TEST

START_TEST(test_strncmp_2) {  // Тест 2: Сравнение строк с разными символами
  char str3[] = "Hello";
  char str4[] = "Hellz";
  ck_assert_int_lt(compare_strings_limited(str3, str4, 5), 0);
  ck_assert_int_gt(compare_strings_limited(str4, str3, 5), 0);
}
END_TEST

START_TEST(test_strncmp_3) {  // Тест 3: Сравнение строк разной длины
  char str5[] = "Hello";
  char str6[] = "Hello, World!";
  ck_assert_int_eq(compare_strings_limited(str5, str6, 5), 0);
  ck_assert_int_ne(compare_strings_limited(str5, str6, 10), 0);
}
END_TEST

START_TEST(test_strncmp_4) {  // Тест 4: Сравнение с нулевой длиной
  char str1[] = "Hello";
  char str2[] = "Hello";
  ck_assert_int_eq(compare_strings_limited(str1, str2, 0), 0);
}
END_TEST

START_TEST(
    test_strncmp_5) {  // Тест 5: Сравнение строк с разными символами в начале
  char str7[] = "Apple";
  char str8[] = "Banana";
  ck_assert_int_lt(compare_strings_limited(str7, str8, 5), 0);
}
END_TEST

START_TEST(test_strncmp_6) {  // Тест 6: Сравнение строк, где одна строка
                              // является префиксом другой
  char str9[] = "Hello";
  char str10[] = "HelloWorld";
  ck_assert_int_eq(compare_strings_limited(str9, str10, 5), 0);
  ck_assert_int_ne(compare_strings_limited(str9, str10, 10), 0);
}
END_TEST

START_TEST(test_strncmp_7) {  // Тест 7: Сравнение строк с разными регистрами
  char str11[] = "hello";
  char str12[] = "Hello";
  ck_assert_int_ne(compare_strings_limited(str11, str12, 5), 0);
}
END_TEST

START_TEST(test_strncmp_8) {  // Тест 8: Сравнение пустой строки с непустой
  char str13[] = "";
  char str14[] = "Hello";
  ck_assert_int_lt(compare_strings_limited(str13, str14, 1), 0);
  ck_assert_int_gt(compare_strings_limited(str14, str13, 1), 0);
}
END_TEST

// strncpy
START_TEST(test_strncpy_1) {  // Тест 1: Копирование первых 5 символов
  char dest[20];
  const char *src = "Hello, World!";
  ck_assert_ptr_eq(copy_string_limited(dest, src, 5), dest);
  dest[5] = '\0';
  ck_assert_str_eq(dest, "Hello");
}
END_TEST

START_TEST(test_strncpy_2) {  // Тест 2: Копирование всей строки
  char dest2[20];
  const char *src = "Hello, World!";
  ck_assert_ptr_eq(copy_string_limited(dest2, src, 13), dest2);
  dest2[13] = '\0';
  ck_assert_str_eq(dest2, "Hello, World!");
}
END_TEST

START_TEST(
    test_strncpy_3) {  // Тест 3: Копирование с длиной меньше, чем длина строки
  char dest3[20];
  const char *src = "Hello, World!";
  ck_assert_ptr_eq(copy_string_limited(dest3, src, 10), dest3);
  dest3[10] = '\0';
  ck_assert_str_eq(dest3, "Hello, Wor");
}
END_TEST

START_TEST(test_strncpy_4) {  // Тест 4: Копирование в пустой dest
  char dest4[20] = "";
  const char *src = "Hello, World!";
  ck_assert_ptr_eq(copy_string_limited(dest4, src, 5), dest4);
  dest4[5] = '\0';
  ck_assert_str_eq(dest4, "Hello");
}
END_TEST

START_TEST(test_strncpy_5) {  // Тест 5: Копирование с нулевой длиной
  char dest5[20] = "Initial";
  const char *src = "Hello, World!";
  ck_assert_ptr_eq(copy_string_limited(dest5, src, 0), dest5);
  ck_assert_str_eq(dest5, "Initial");
}
END_TEST

START_TEST(test_strncpy_6) {  // Тест 6: Копирование в строку, которая уже
                              // содержит данные
  char dest6[20] = "Old Data";
  const char *src = "Hello, World!";
  ck_assert_ptr_eq(copy_string_limited(dest6, src, 5), dest6);
  dest6[5] = '\0';
  ck_assert_str_eq(dest6, "Hello");
}
END_TEST

START_TEST(
    test_strncpy_7) {  // Тест 7: Копирование в строку с недостаточным размером
  char dest7[5];
  const char *src = "Hello, World!";
  ck_assert_ptr_eq(copy_string_limited(dest7, src, 5), dest7);
  dest7[4] = '\0';
  ck_assert_str_eq(dest7, "Hell");
}
END_TEST

START_TEST(test_strncpy_8) {  // Тест 8: Копирование пустой строки
  char dest8[20];
  const char *src8 = "";
  ck_assert_ptr_eq(copy_string_limited(dest8, src8, 5), dest8);
  dest8[0] = '\0';
  ck_assert_str_eq(dest8, "");
}
END_TEST

START_TEST(
    test_strncpy_9) {  // Тест 9: Копирование в неинициализированный массив
  char uninitialized_dest[20];
  const char *src = "Hello, World!";
  ck_assert_ptr_eq(copy_string_limited(uninitialized_dest, src, 13),
                   uninitialized_dest);
  uninitialized_dest[13] = '\0';
  ck_assert_str_eq(uninitialized_dest, "Hello, World!");
}
END_TEST

START_TEST(test_strncpy_10) {  // Тест 11: Копирование строки с нулевым символом
  char null_char_src[] = "Hello\0World";
  char null_dest[20];
  ck_assert_ptr_eq(copy_string_limited(null_dest, null_char_src, 10), null_dest);
  null_dest[10] = '\0';
  ck_assert_str_eq(null_dest, "Hello");
}
END_TEST

START_TEST(
    test_strncpy_11) {  // Тест 12: Проверка на модификацию исходной строки
  char original[20] = "Original";
  const char *src = "Hello, World!";
  ck_assert_ptr_eq(copy_string_limited(original, src, 5), original);
  original[5] = '\0';
  ck_assert_str_eq(original, "Hello");
}
END_TEST

// strcspn
START_TEST(test_strcspn_1) {  // Тест 1: Проверка длины, до первого вхождения
                              // символов из str2
  const char *str1 = "abcdef";
  const char *str2 = "de";
  ck_assert_int_eq(count_not_matching_chars(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_strcspn_2) {  // Тест 2: Проверка, когда str2 пустая
  const char *str1 = "abcdef";
  const char *str3 = "";
  ck_assert_int_eq(count_not_matching_chars(str1, str3), strcspn(str1, str3));
}
END_TEST

START_TEST(test_strcspn_3) {  // Тест 3: Проверка, когда str1 пустая
  const char *str4 = "";
  const char *str5 = "abc";
  ck_assert_int_eq(count_not_matching_chars(str4, str5), strcspn(str4, str5));
}
END_TEST

START_TEST(test_strcspn_4) {  // Тест 4: Проверка, когда str1 и str2 совпадают
  const char *str6 = "abc";
  const char *str7 = "abc";
  ck_assert_int_eq(count_not_matching_chars(str6, str7), strcspn(str6, str7));
}
END_TEST

START_TEST(test_strcspn_5) {  // Тест 5: Проверка, когда str2 содержит символ,
                              // который отсутствует в str1
  const char *str8 = "abcdef";
  const char *str9 = "xyz";
  ck_assert_int_eq(count_not_matching_chars(str8, str9), strcspn(str8, str9));
}
END_TEST

START_TEST(test_strcspn_6) {  // Тест 6: Проверка, когда str2 содержит символы,
                              // находящиеся в начале str1
  const char *str10 = "abcdef";
  const char *str11 = "ab";
  ck_assert_int_eq(count_not_matching_chars(str10, str11), strcspn(str10, str11));
}
END_TEST

START_TEST(test_strcspn_7) {  // Тест 7: Проверка, когда str2 содержит символы,
                              // находящиеся в конце str1
  const char *str12 = "abcdef";
  const char *str13 = "ef";
  ck_assert_int_eq(count_not_matching_chars(str12, str13), strcspn(str12, str13));
}
END_TEST

START_TEST(test_strcspn_8) {  // Тест 8: Проверка, когда str1 содержит
                              // повторяющиеся символы из str2
  const char *str14 = "abacabad";
  const char *str15 = "cd";
  ck_assert_int_eq(count_not_matching_chars(str14, str15), strcspn(str14, str15));
}
END_TEST



START_TEST(test_strlen_1) {  // Тест 1: Проверка длины обычной строки
  const char *str1 = "Hello, World!";
  ck_assert_int_eq(get_string_length(str1), 13);
}
END_TEST

START_TEST(test_strlen_2) {  // Тест 2: Проверка длины пустой строки
  const char *str2 = "";
  ck_assert_int_eq(get_string_length(str2), 0);
}
END_TEST

START_TEST(test_strlen_3) {  // Тест 3: Проверка длины строки с пробелами
  const char *str3 = "   ";
  ck_assert_int_eq(get_string_length(str3), 3);
}
END_TEST

START_TEST(test_strlen_4) {  // Тест 4: Проверка длины строки с символами
  const char *str4 = "12345";
  ck_assert_int_eq(get_string_length(str4), 5);
}
END_TEST

START_TEST(
    test_strlen_5) {  // Тест 5: Проверка длины строки с символами и пробелами
  const char *str5 = "Hello 123";
  ck_assert_int_eq(get_string_length(str5), 9);
}
END_TEST

START_TEST(
    test_strlen_6) {  // Тест 6: Проверка длины строки с специальными символами
  const char *str6 = "!@#$%^&*()";
  ck_assert_int_eq(get_string_length(str6), 10);
}
END_TEST

START_TEST(test_strlen_7) {  // Тест 7: Проверка длины строки с длинными словами
  const char *str7 = "A long string with multiple words.";
  ck_assert_int_eq(get_string_length(str7), 34);
}
END_TEST

START_TEST(
    test_strlen_8) {  // Тест 8: Проверка длины строки с символами новой строки
  const char *str9 = "Hello\nWorld";
  ck_assert_int_eq(get_string_length(str9), 11);
}
END_TEST

START_TEST(test_strlen_9) {  // Тест 9: Проверка длины строки с табуляцией
  const char *str10 = "Hello\tWorld";
  ck_assert_int_eq(get_string_length(str10), 11);
}
END_TEST

START_TEST(
    test_strpbrk_1) {  // Тест 1: Проверка нахождения первого вхождения символа
  const char *str1 = "abcdef";
  const char *str2 = "de";
  ck_assert_str_eq(find_first_matching_char(str1, str2), "def");
}
END_TEST

START_TEST(test_strpbrk_2) {  // Тест 2: Проверка, когда нет совпадений
  const char *str3 = "abcdef";
  const char *str4 = "xyz";
  ck_assert_ptr_eq(find_first_matching_char(str3, str4), NULL);
}
END_TEST

START_TEST(test_strpbrk_3) {  // Тест 3: Проверка на пустую str2
  const char *str5 = "abcdef";
  const char *str6 = "a";
  ck_assert_str_eq(find_first_matching_char(str5, str6), strpbrk(str5, str6));
}
END_TEST

START_TEST(test_strpbrk_4) {  // Тест 4: Проверка на пустую str1
  const char *str7 = "";
  const char *str8 = "abc";
  ck_assert_ptr_eq(find_first_matching_char(str7, str8), NULL);
}
END_TEST

START_TEST(test_strpbrk_5) {  // Тест 5: Проверка, когда str1 и str2 совпадают
  const char *str9 = "abc";
  const char *str10 = "abc";
  ck_assert_str_eq(find_first_matching_char(str9, str10), "abc");
}
END_TEST

START_TEST(test_strpbrk_6) {  // Тест 6: Проверка, когда str2 содержит символы,
                              // находящиеся в конце str1
  const char *str11 = "abcdef";
  const char *str12 = "ef";
  ck_assert_str_eq(find_first_matching_char(str11, str12), "ef");
}
END_TEST

START_TEST(test_strpbrk_7) {  // Тест 7: Проверка, когда str2 содержит символ,
                              // который встречается несколько раз
  const char *str13 = "hello world";
  const char *str14 = "lo";
  ck_assert_str_eq(find_first_matching_char(str13, str14), strpbrk(str13, str14));
}
END_TEST

START_TEST(test_strpbrk_8) {  // Тест 8: Проверка, когда str1 содержит
                              // специальные символы
  const char *str15 = "abc!@#$%^&*()";
  const char *str16 = "!$";
  ck_assert_str_eq(find_first_matching_char(str15, str16), "!@#$%^&*()");
}
END_TEST

START_TEST(test_strpbrk_9) {  // Тест 9: Проверка, когда str1 содержит толькo
                              // символы str2
  const char *str17 = "xyzxyz";
  const char *str18 = "xyz";
  ck_assert_str_eq(find_first_matching_char(str17, str18), "xyzxyz");
}
END_TEST

START_TEST(test_strpbrk_10) {  // Тест 10: Проверка, когда str2 содержит
                               // символы, которые не присутствуют в str1
  const char *str19 = "abcdef";
  const char *str20 = "ghijkl";
  ck_assert_ptr_eq(find_first_matching_char(str19, str20), NULL);
}
END_TEST

START_TEST(test_strrchr_1) {  // Тест 1: Проверка нахождения последнего
                              // вхождения символа
  const char *str1 = "hello world";
  ck_assert_str_eq(find_last_char(str1, 'o'), "orld");
}
END_TEST

START_TEST(
    test_strrchr_2) {  // Тест 2: Проверка, когда символ отсутствует в строке
  const char *str2 = "hello world";
  ck_assert_ptr_eq(find_last_char(str2, 'x'), NULL);
}
END_TEST

START_TEST(test_strrchr_3) {  // Тест 3: Проверка на пустую строку
  const char *str3 = "";
  ck_assert_ptr_eq(find_last_char(str3, 'a'), NULL);
}
END_TEST

START_TEST(test_strrchr_4) {  // Тест 4: Проверка, когда символ находится в
                              // начале строки
  const char *str4 = "banana";
  ck_assert_str_eq(find_last_char(str4, 'b'), "banana");
}
END_TEST

START_TEST(test_strrchr_5) {  // Тест 5: Проверка, когда символ находится в
                              // конце строки
  const char *str5 = "apple";
  ck_assert_str_eq(find_last_char(str5, 'e'), "e");
}
END_TEST

START_TEST(test_strrchr_6) {  // Тест 6: Проверка, когда строка состоит из
                              // одинаковых символов
  const char *str6 = "aaaaaa";
  ck_assert_str_eq(find_last_char(str6, 'a'), strrchr(str6, 'a'));
}
END_TEST

START_TEST(test_strrchr_7) {  // Тест 7: Проверка, когда символ встречается
                              // несколько раз
  const char *str7 = "character";
  ck_assert_str_eq(find_last_char(str7, 'c'), strrchr(str7, 'c'));
}
END_TEST

START_TEST(
    test_strrchr_8) {  // Тест 8: Проверка, когда символ является пробелом
  const char *str8 = "hello world";
  ck_assert_str_eq(find_last_char(str8, ' '), " world");
}
END_TEST

START_TEST(test_strrchr_9) {  // Тест 9: Проверка, когда строка содержит
                              // специальные символы
  const char *str9 = "abc!@#def";
  ck_assert_str_eq(find_last_char(str9, '!'), "!@#def");
}
END_TEST

START_TEST(test_strrchr_10) {  // Тест 10: Проверка, когда символ является
                               // последним в строке
  const char *str10 = "test string";
  ck_assert_str_eq(find_last_char(str10, 'g'), "g");
}
END_TEST

// START_TEST(test_strstr_1) {  // Тест 1: Проверка нахождения подстроки в строке
//   const char *str1 = "Hello, world!";
//   const char *substr1 = "world";
//   ck_assert_str_eq(split_string(str1, substr1), "world!");
// }
// END_TEST

// START_TEST(test_strstr_2) {  // Тест 2: Проверка, когда подстрока отсутствует
//   const char *str2 = "Hello, world!";
//   const char *substr2 = "earth";
//   ck_assert_ptr_eq(split_string(str2, substr2), NULL);
// }
// END_TEST

// START_TEST(test_strstr_3) {  // Тест 3: Проверка на пустую строку
//   const char *str3 = "";
//   const char *substr3 = "test";
//   ck_assert_ptr_eq(split_string(str3, substr3), NULL);
// }
// END_TEST

// START_TEST(test_strstr_4) {  // Тест 4: Проверка на пустую подстроку
//   const char *str4 = "Hello, world!";
//   const char *substr4 = "";
//   ck_assert_str_eq(split_string(str4, substr4), strstr(str4, substr4));
// }
// END_TEST

// START_TEST(test_strstr_5) {  // Тест 5: Проверка, когда подстрока находится в
//                              // начале строки
//   const char *str5 = "Hello, world!";
//   const char *substr5 = "Hello";
//   ck_assert_str_eq(split_string(str5, substr5), "Hello, world!");
// }
// END_TEST

// START_TEST(test_strstr_6) {  // Тест 6: Проверка, когда подстрока находится в
//                              // конце строки
//   const char *str6 = "Hello, world!";
//   const char *substr6 = "world!";
//   ck_assert_str_eq(split_string(str6, substr6), "world!");
// }
// END_TEST

// START_TEST(test_strstr_7) {  // Тест 7: Проверка, когда подстрока состоит из
//                              // одинаковых символов
//   const char *str7 = "aaaaaa";
//   const char *substr7 = "aa";
//   ck_assert_str_eq(split_string(str7, substr7), "aaaaaa");
// }
// END_TEST

// START_TEST(test_strstr_8) {  // Тест 8: Проверка, когда подстрока встречается
//                              // несколько раз
//   const char *str8 = "banana";
//   const char *substr8 = "ana";
//   ck_assert_str_eq(split_string(str8, substr8), strstr(str8, substr8));
// }
// END_TEST

// START_TEST(test_strstr_9) {  // Тест 9: Проверка, когда строка содержит
//                              // специальные символы
//   const char *str9 = "abc!@#def";
//   const char *substr9 = "!@#";
//   ck_assert_str_eq(split_string(str9, substr9), "!@#def");
// }
// END_TEST

// START_TEST(test_strstr_10) {  // Тест 10: Проверка, когда подстрока является
//                               // самой строкой
//   const char *str10 = "test";
//   const char *substr10 = "test";
//   ck_assert_str_eq(split_string(str10, substr10), "test");
// }
// END_TEST

START_TEST(test_strtok_1) {  // Тест 1: Проверка разбивки строки
  char str1[] = "Hello, world! This is a test.";
  char *token1 = split_string(str1, " ,.!?");
  ck_assert_str_eq(token1, "Hello");
  token1 = split_string(NULL, " ,.!?");
  ck_assert_str_eq(token1, "world");
}
END_TEST

START_TEST(test_strtok_2) {  // Тест 2: Проверка на пустую строку
  char str2[] = "";
  char *token2 = split_string(str2, " ,.!?");
  ck_assert_ptr_eq(token2, NULL);
}
END_TEST

START_TEST(test_strtok_3) {  // Тест 3: Проверка, когда строка состоит только из
                             // разделителей
  char str3[] = ",,!!";
  char *token3 = split_string(str3, ",!?");
  ck_assert_ptr_eq(token3, NULL);
}
END_TEST

START_TEST(
    test_strtok_4) {  // Тест 4: Проверка, когда строка не содержит разделителей
  char str4[] = "NoDelimitersHere";
  char *token4 = split_string(str4, ",.!?");
  ck_assert_str_eq(token4, "NoDelimitersHere");
}
END_TEST

START_TEST(
    test_strtok_5) {  // Тест 5: Проверка, когда разделитель в начале строки
  char str5[] = " ,Hello";
  char *token5 = split_string(str5, " ,");
  ck_assert_str_eq(token5, "Hello");
}
END_TEST

START_TEST(
    test_strtok_6) {  // Тест 6: Проверка, когда разделитель в конце строки
  char str6[] = "Goodbye, ";
  char *token6 = split_string(str6, " ,");
  ck_assert_str_eq(token6, "Goodbye");
}
END_TEST

START_TEST(test_strtok_7) {  // Тест 7: Проверка нескольких последовательных
                             // разделителей
  char str7[] = "This,,is,,a,,test.";
  char *token7 = split_string(str7, ",");
  ck_assert_str_eq(token7, "This");
  token7 = split_string(NULL, ",");
  ck_assert_str_eq(token7, "is");
  token7 = split_string(NULL, ",");
  ck_assert_str_eq(token7, "a");
  token7 = split_string(NULL, ",");
  ck_assert_str_eq(token7, "test.");
}
END_TEST

START_TEST(test_strtok_8) {  // Тест 8: Проверка, когда строка заканчивается
                             // разделителем
  char str8[] = "EndWithDelimiter,";
  char *token8 = split_string(str8, ",");
  ck_assert_str_eq(token8, "EndWithDelimiter");
}
END_TEST

START_TEST(test_strtok_9) {  // Тест 9: Проверка на многократные разделители
  char str9[] = "one::two::three";
  char *token9 = split_string(str9, ":");
  ck_assert_str_eq(token9, "one");
  token9 = split_string(NULL, ":");
  ck_assert_str_eq(token9, "two");
  token9 = split_string(NULL, ":");
  ck_assert_str_eq(token9, "three");
}
END_TEST

START_TEST(test_strtok_10) {  // Тест 10: Проверка, когда строка состоит из
                              // одного токена
  char str10[] = "OnlyOneToken";
  char *token10 = split_string(str10, ",");
  ck_assert_str_eq(token10, "OnlyOneToken");
}
END_TEST

START_TEST(test_to_upper_1) {  // Тест 1: Проверка преобразования строки в
                               // верхний регистр
  const char *str1 = "hello world";
  char *result1 = convert_to_uppercase(str1);
  ck_assert_str_eq(result1, "HELLO WORLD");
  free(result1);
}
END_TEST

START_TEST(test_to_upper_2) {  // Тест 2: Проверка на пустую строку
  const char *str2 = "";
  char *result2 = convert_to_uppercase(str2);
  ck_assert_str_eq(result2, "");
  free(result2);
}
END_TEST

START_TEST(
    test_to_upper_3) {  // Тест 3: Проверка строки, уже в верхнем регистре
  const char *str3 = "HELLO";
  char *result3 = convert_to_uppercase(str3);
  ck_assert_str_eq(result3, "HELLO");
  free(result3);
}
END_TEST

START_TEST(test_to_upper_4) {  // Тест 4: Проверка строки с символами, которые
                               // не требуют изменения
  const char *str4 = "Hello123";
  char *result4 = convert_to_uppercase(str4);
  ck_assert_str_eq(result4, "HELLO123");
  free(result4);
}
END_TEST

START_TEST(test_to_upper_5) {  // Тест 5: Проверка строки с пробелами
  const char *str6 = "  hello  ";
  char *result6 = convert_to_uppercase(str6);
  ck_assert_str_eq(result6, "  HELLO  ");
  free(result6);
}
END_TEST

START_TEST(test_to_upper_6) {  // Тест 6: Проверка строки с цифрами и
                               // специальными символами
  const char *str7 = "123abc!@#";
  char *result7 = convert_to_uppercase(str7);
  ck_assert_str_eq(result7, "123ABC!@#");
  free(result7);
}
END_TEST

START_TEST(test_to_upper_7) {  // Тест 7: Проверка строки с символами, не
                               // требующими преобразования
  const char *str9 = "12345";
  char *result9 = convert_to_uppercase(str9);
  ck_assert_str_eq(result9, "12345");
  free(result9);
}
END_TEST

START_TEST(test_to_lower_1) {  // Тест 1: Проверка преобразования строки в
                               // нижний регистр
  const char *str1 = "HELLO WORLD";
  char *result1 = convert_to_lowercase(str1);
  ck_assert_str_eq(result1, "hello world");
  free(result1);
}
END_TEST

START_TEST(test_to_lower_2) {  // Тест 2: Проверка на пустую строку
  const char *str2 = "";
  char *result2 = convert_to_lowercase(str2);
  ck_assert_str_eq(result2, "");
  free(result2);
}
END_TEST

START_TEST(test_to_lower_3) {  // Тест 3: Проверка строки, уже в нижнем регистре
  const char *str3 = "hello";
  char *result3 = convert_to_lowercase(str3);
  ck_assert_str_eq(result3, "hello");
  free(result3);
}
END_TEST

START_TEST(test_to_lower_4) {  // Тест 4: Проверка строки с символами, которые
                               // не требуют изменения
  const char *str4 = "Hello123";
  char *result4 = convert_to_lowercase(str4);
  ck_assert_str_eq(result4, "hello123");
  free(result4);
}
END_TEST

START_TEST(test_to_lower_5) {  // Тест 5: Проверка строки с пробелами
  const char *str6 = "  HELLO  ";
  char *result6 = convert_to_lowercase(str6);
  ck_assert_str_eq(result6, "  hello  ");
  free(result6);
}
END_TEST

START_TEST(test_to_lower_6) {  // Тест 6: Проверка строки с цифрами и
                               // специальными символами
  const char *str7 = "123ABC!@#";
  char *result7 = convert_to_lowercase(str7);
  ck_assert_str_eq(result7, "123abc!@#");
  free(result7);
}
END_TEST

START_TEST(test_to_lower_7) {  // Тест 7: Проверка строки с символами, не
                               // требующими преобразования
  const char *str9 = "12345";
  char *result9 = convert_to_lowercase(str9);
  ck_assert_str_eq(result9, "12345");
  free(result9);
}
END_TEST

START_TEST(test_insert_1) {  // Тест 1: Проверка вставки строки в начало
  const char *src1 = "world";
  const char *str1 = "Hello, ";
  char *result1 = insert_string(src1, str1, 0);
  ck_assert_str_eq(result1, "Hello, world");
  free(result1);
}
END_TEST

START_TEST(test_insert_2) {  // Тест 2: Проверка вставки строки в конец
  const char *src2 = "Hello";
  const char *str2 = ", world";
  char *result2 = insert_string(src2, str2, 5);
  ck_assert_str_eq(result2, "Hello, world");
  free(result2);
}
END_TEST

START_TEST(test_insert_3) {  // Тест 3: Проверка вставки строки в середину
  const char *src3 = "Hello, !";
  const char *str3 = "world ";
  char *result3 = insert_string(src3, str3, 7);
  ck_assert_str_eq(result3, "Hello, world !");
  free(result3);
}
END_TEST

START_TEST(
    test_insert_4) {  // Тест 4: Проверка вставки строки в недопустимый индекс
  const char *src4 = "Hello";
  const char *str4 = "world";
  char *result4 = insert_string(src4, str4, 10);
  ck_assert_ptr_eq(result4, NULL);
}
END_TEST

START_TEST(test_insert_5) {  // Тест 5: Проверка вставки пустой строки
  const char *src5 = "Hello";
  const char *str5 = "";
  char *result5 = insert_string(src5, str5, 2);
  ck_assert_str_eq(result5, "Hello");
  free(result5);
}
END_TEST

START_TEST(
    test_insert_6) {  // Тест 6: Проверка вставки строки в начале пустой строки
  const char *src6 = "";
  const char *str6 = "Hello";
  char *result6 = insert_string(src6, str6, 0);
  ck_assert_str_eq(result6, "Hello");
  free(result6);
}
END_TEST

START_TEST(test_insert_7) {  // Тест 7: Проверка вставки строки в середину
                             // строки с пробелами
  const char *src7 = "Hello there!";
  const char *str7 = "beautiful ";
  char *result7 = insert_string(src7, str7, 6);
  ck_assert_str_eq(result7, "Hello beautiful there!");
  free(result7);
}
END_TEST

START_TEST(test_insert_8) {  // Тест 8: Проверка вставки строки в строку,
                             // состоящую из одного символа
  const char *src10 = "A";
  const char *str10 = "B";
  char *result10 = insert_string(src10, str10, 1);
  ck_assert_str_eq(result10, "AB");
  free(result10);
}
END_TEST

START_TEST(
    test_trim_1) {  // Тест 1: Проверка удаления пробелов в начале и конце
  const char *src1 = "   Hello, world!   ";
  const char *trim_chars1 = " ";
  char *result1 = trim_string_edges(src1, trim_chars1);
  ck_assert_str_eq(result1, "Hello, world!");
  free(result1);
}
END_TEST

START_TEST(
    test_trim_2) {  // Тест 2: Проверка удаления символов в начале и конце
  const char *src2 = "***Hello***";
  const char *trim_chars2 = "*";
  char *result2 = trim_string_edges(src2, trim_chars2);
  ck_assert_str_eq(result2, "Hello");
  free(result2);
}
END_TEST

END_TEST

START_TEST(test_trim_3) {  // Тест 5: Проверка, когда нет символов для удаления
  const char *src5 = "NoTrimNeeded";
  const char *trim_chars5 = " ";
  char *result5 = trim_string_edges(src5, trim_chars5);
  ck_assert_str_eq(result5, "NoTrimNeeded");
  free(result5);
}
END_TEST

START_TEST(test_trim_4) {  // Тест 6: Проверка удаления пробелов и символов в
                           // начале и конце
  const char *src6 = "   ***Hello, world!***   ";
  const char *trim_chars6 = " *";
  char *result6 = trim_string_edges(src6, trim_chars6);
  ck_assert_str_eq(result6, "Hello, world!");
  free(result6);
}
END_TEST

START_TEST(test_trim_5) {  // Тест 7: Проверка строки с пробелами и символами
  const char *src7 = "   Hello***   ";
  const char *trim_chars7 = " *";
  char *result7 = trim_string_edges(src7, trim_chars7);
  ck_assert_str_eq(result7, "Hello");
  free(result7);
}
END_TEST

START_TEST(
    test_trim_6) {  // Тест 8: Проверка, когда строка состоит только из пробелов
  const char *src8 = "     ";
  const char *trim_chars8 = " ";
  char *result8 = trim_string_edges(src8, trim_chars8);
  ck_assert_str_eq(result8, "");
  free(result8);
}
END_TEST

START_TEST(
    test_trim_7) {  // Тест 9: Проверка удаления нескольких различных символов
  const char *src9 = "###Hello###World###";
  const char *trim_chars9 = "#";
  char *result9 = trim_string_edges(src9, trim_chars9);
  ck_assert_str_eq(result9, "Hello###World");
  free(result9);
}
END_TEST

START_TEST(test_trim_8) {  // Тест 10: Проверка, когда строка содержит только
                           // символы trim_chars
  const char *src10 = "abcxyzabc";
  const char *trim_chars10 = "abc";
  char *result10 = trim_string_edges(src10, trim_chars10);
  ck_assert_str_eq(result10, "xyz");
  free(result10);
}
END_TEST



Suite *string_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("String Functions");
  tc_core = tcase_create("Core");

  // memchr
  tcase_add_test(tc_core, test_memchr_1);
  tcase_add_test(tc_core, test_memchr_2);
  tcase_add_test(tc_core, test_memchr_3);
  tcase_add_test(tc_core, test_memchr_4);
  tcase_add_test(tc_core, test_memchr_5);
  tcase_add_test(tc_core, test_memchr_6);
  tcase_add_test(tc_core, test_memchr_7);
  tcase_add_test(tc_core, test_memchr_8);
  tcase_add_test(tc_core, test_memchr_9);
  tcase_add_test(tc_core, test_memchr_10);

  // memcmp
  tcase_add_test(tc_core, test_memcmp_1);
  tcase_add_test(tc_core, test_memcmp_2);
  tcase_add_test(tc_core, test_memcmp_3);
  tcase_add_test(tc_core, test_memcmp_4);
  tcase_add_test(tc_core, test_memcmp_5);
  tcase_add_test(tc_core, test_memcmp_6);
  tcase_add_test(tc_core, test_memcmp_7);
  tcase_add_test(tc_core, test_memcmp_8);
  tcase_add_test(tc_core, test_memcmp_9);

  // memcpy
  tcase_add_test(tc_core, test_memcpy_1);
  tcase_add_test(tc_core, test_memcpy_2);
  tcase_add_test(tc_core, test_memcpy_3);
  tcase_add_test(tc_core, test_memcpy_4);
  tcase_add_test(tc_core, test_memcpy_5);
  tcase_add_test(tc_core, test_memcpy_6);
  tcase_add_test(tc_core, test_memcpy_7);
  tcase_add_test(tc_core, test_memcpy_8);
  tcase_add_test(tc_core, test_memcpy_9);

  // memset
  tcase_add_test(tc_core, test_memset_1);
  tcase_add_test(tc_core, test_memset_2);
  tcase_add_test(tc_core, test_memset_3);
  tcase_add_test(tc_core, test_memset_4);
  tcase_add_test(tc_core, test_memset_5);

  // strncat
  tcase_add_test(tc_core, test_strncat_1);
  tcase_add_test(tc_core, test_strncat_2);
  tcase_add_test(tc_core, test_strncat_3);
  tcase_add_test(tc_core, test_strncat_4);
  tcase_add_test(tc_core, test_strncat_5);
  tcase_add_test(tc_core, test_strncat_6);
  tcase_add_test(tc_core, test_strncat_7);
  tcase_add_test(tc_core, test_strncat_8);

  // strchr
  tcase_add_test(tc_core, test_strchr_1);
  tcase_add_test(tc_core, test_strchr_2);
  tcase_add_test(tc_core, test_strchr_3);
  tcase_add_test(tc_core, test_strchr_4);
  tcase_add_test(tc_core, test_strchr_5);
  tcase_add_test(tc_core, test_strchr_6);
  tcase_add_test(tc_core, test_strchr_7);
  tcase_add_test(tc_core, test_strchr_8);
  tcase_add_test(tc_core, test_strchr_9);

  // strncmp
  tcase_add_test(tc_core, test_strncmp_1);
  tcase_add_test(tc_core, test_strncmp_2);
  tcase_add_test(tc_core, test_strncmp_3);
  tcase_add_test(tc_core, test_strncmp_4);
  tcase_add_test(tc_core, test_strncmp_5);
  tcase_add_test(tc_core, test_strncmp_6);
  tcase_add_test(tc_core, test_strncmp_7);
  tcase_add_test(tc_core, test_strncmp_8);

  // strncpy
  tcase_add_test(tc_core, test_strncpy_1);
  tcase_add_test(tc_core, test_strncpy_2);
  tcase_add_test(tc_core, test_strncpy_3);
  tcase_add_test(tc_core, test_strncpy_4);
  tcase_add_test(tc_core, test_strncpy_5);
  tcase_add_test(tc_core, test_strncpy_6);
  tcase_add_test(tc_core, test_strncpy_7);
  tcase_add_test(tc_core, test_strncpy_8);
  tcase_add_test(tc_core, test_strncpy_9);
  tcase_add_test(tc_core, test_strncpy_10);
  tcase_add_test(tc_core, test_strncpy_11);

  // strcspn
  tcase_add_test(tc_core, test_strcspn_1);
  tcase_add_test(tc_core, test_strcspn_2);
  tcase_add_test(tc_core, test_strcspn_3);
  tcase_add_test(tc_core, test_strcspn_4);
  tcase_add_test(tc_core, test_strcspn_5);
  tcase_add_test(tc_core, test_strcspn_6);
  tcase_add_test(tc_core, test_strcspn_7);
  tcase_add_test(tc_core, test_strcspn_8);

  // strlen
  tcase_add_test(tc_core, test_strlen_1);
  tcase_add_test(tc_core, test_strlen_2);
  tcase_add_test(tc_core, test_strlen_3);
  tcase_add_test(tc_core, test_strlen_4);
  tcase_add_test(tc_core, test_strlen_5);
  tcase_add_test(tc_core, test_strlen_6);
  tcase_add_test(tc_core, test_strlen_7);
  tcase_add_test(tc_core, test_strlen_8);
  tcase_add_test(tc_core, test_strlen_9);

  // strpbrk
  tcase_add_test(tc_core, test_strpbrk_1);
  tcase_add_test(tc_core, test_strpbrk_2);
  tcase_add_test(tc_core, test_strpbrk_3);
  tcase_add_test(tc_core, test_strpbrk_4);
  tcase_add_test(tc_core, test_strpbrk_5);
  tcase_add_test(tc_core, test_strpbrk_6);
  tcase_add_test(tc_core, test_strpbrk_7);
  tcase_add_test(tc_core, test_strpbrk_8);
  tcase_add_test(tc_core, test_strpbrk_9);
  tcase_add_test(tc_core, test_strpbrk_10);

  // strrchr
  tcase_add_test(tc_core, test_strrchr_1);
  tcase_add_test(tc_core, test_strrchr_2);
  tcase_add_test(tc_core, test_strrchr_3);
  tcase_add_test(tc_core, test_strrchr_4);
  tcase_add_test(tc_core, test_strrchr_5);
  tcase_add_test(tc_core, test_strrchr_6);
  tcase_add_test(tc_core, test_strrchr_7);
  tcase_add_test(tc_core, test_strrchr_8);
  tcase_add_test(tc_core, test_strrchr_9);
  tcase_add_test(tc_core, test_strrchr_10);

  // strstr
  // tcase_add_test(tc_core, test_strstr_1);
  // tcase_add_test(tc_core, test_strstr_2);
  // tcase_add_test(tc_core, test_strstr_3);
  // tcase_add_test(tc_core, test_strstr_4);
  // tcase_add_test(tc_core, test_strstr_5);
  // tcase_add_test(tc_core, test_strstr_6);
  // tcase_add_test(tc_core, test_strstr_7);
  // tcase_add_test(tc_core, test_strstr_8);
  // tcase_add_test(tc_core, test_strstr_9);
  // tcase_add_test(tc_core, test_strstr_10);

  // strtok
  tcase_add_test(tc_core, test_strtok_1);
  tcase_add_test(tc_core, test_strtok_2);
  tcase_add_test(tc_core, test_strtok_3);
  tcase_add_test(tc_core, test_strtok_4);
  tcase_add_test(tc_core, test_strtok_5);
  tcase_add_test(tc_core, test_strtok_6);
  tcase_add_test(tc_core, test_strtok_7);
  tcase_add_test(tc_core, test_strtok_8);
  tcase_add_test(tc_core, test_strtok_9);
  tcase_add_test(tc_core, test_strtok_10);

  // to upper
  tcase_add_test(tc_core, test_to_upper_1);
  tcase_add_test(tc_core, test_to_upper_2);
  tcase_add_test(tc_core, test_to_upper_3);
  tcase_add_test(tc_core, test_to_upper_4);
  tcase_add_test(tc_core, test_to_upper_5);
  tcase_add_test(tc_core, test_to_upper_6);
  tcase_add_test(tc_core, test_to_upper_7);

  // to lower
  tcase_add_test(tc_core, test_to_lower_1);
  tcase_add_test(tc_core, test_to_lower_2);
  tcase_add_test(tc_core, test_to_lower_3);
  tcase_add_test(tc_core, test_to_lower_4);
  tcase_add_test(tc_core, test_to_lower_5);
  tcase_add_test(tc_core, test_to_lower_6);
  tcase_add_test(tc_core, test_to_lower_7);

  // insert_string
  tcase_add_test(tc_core, test_insert_1);
  tcase_add_test(tc_core, test_insert_2);
  tcase_add_test(tc_core, test_insert_3);
  tcase_add_test(tc_core, test_insert_4);
  tcase_add_test(tc_core, test_insert_5);
  tcase_add_test(tc_core, test_insert_6);
  tcase_add_test(tc_core, test_insert_7);
  tcase_add_test(tc_core, test_insert_8);

  // trim_string_edges
  tcase_add_test(tc_core, test_trim_1);
  tcase_add_test(tc_core, test_trim_2);
  tcase_add_test(tc_core, test_trim_3);
  tcase_add_test(tc_core, test_trim_3);
  tcase_add_test(tc_core, test_trim_4);
  tcase_add_test(tc_core, test_trim_5);
  tcase_add_test(tc_core, test_trim_6);
  tcase_add_test(tc_core, test_trim_7);
  tcase_add_test(tc_core, test_trim_8);

  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = string_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}
