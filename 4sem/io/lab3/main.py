from math import fabs
from itertools import *

def read_matrix():
    """Чтение матрицы из стандартного ввода."""
    count_string = int(input("Введите количество строк: "))
    print("Введите матрицу: ")
    return [[float(x) for x in input().split()] for _ in range(count_string)]

def make_unit_column(matrix, row_index, col_index):
    """Преобразование ведущего столбца в единичный."""
    cof = matrix[row_index][col_index]
    matrix[row_index] = [x / cof for x in matrix[row_index]]

    for i in range(len(matrix)):
        if i != row_index:
            cof = matrix[i][col_index]
            matrix[i] = [matrix[i][j] - matrix[row_index][j] * cof for j in range(len(matrix[i]))]
    return matrix

def remove_zero_rows(matrix):
    """Удаление строк с нулевыми коэффициентами и проверка на несовместимость."""
    for i in range(len(matrix) - 1, -1, -1):
        if all(x == 0 for x in matrix[i]):
            if matrix[i][-1] == 0:
                matrix.pop(i)
            else:
                print("Ваша система несовместима")
                exit(6)

def get_basic_variables(matrix):
    """Получение списка базисных переменных."""
    basic_list = []
    usage_rows = []
    for col in range(len(matrix[0])):
        count_one = sum(1 for row in matrix if row[col] == 1)
        count_another = sum(1 for row in matrix if row[col] != 0 and row[col] != 1)
        if count_one == 1 and count_another == 0:
            one_index = next(i for i, row in enumerate(matrix) if row[col] == 1)
            basic_list.append(col)
            usage_rows.append(one_index)
    return basic_list, usage_rows

def check_equal_basis(arr, basic, comb):
    """Проверка равенства базисных переменных."""
    for i in range(len(arr) - 1):
        for j in range(i + 1, len(arr)):
            if arr[i] == arr[j] and basic[i] in comb and basic[j] in comb:
                return True
    return False

def get_basic_matrix(matrix, comb):
    """Получение базисной матрицы."""
    new_matrix = [row[:] for row in matrix]
    basic_list, basic_rows = get_basic_variables(new_matrix)
    usage_rows = []

    for var in comb:
        if var not in basic_list:
            for i in range(len(new_matrix)):
                if new_matrix[i][var] != 0 and i not in usage_rows:
                    new_matrix = make_unit_column(new_matrix, i, var)
                    usage_rows.append(i)
                    break
            remove_zero_rows(new_matrix)
            basic_list, basic_rows = get_basic_variables(new_matrix)
            if check_equal_basis(basic_rows, basic_list, comb):
                return []
        else:
            usage_rows.append(basic_rows[basic_list.index(var)])

    return new_matrix

def read_function():
    """Чтение функции Z."""
    print("Input Z: ")
    return [float(x) for x in input().split()]

def get_first_table(matrix, z):
    """Получение первой таблицы."""
    basic, basic_rows = get_basic_variables(matrix)
    basic = [basic[i] for i in range(len(basic) - len(matrix), len(basic))]
    basic_rows = [basic_rows[i] for i in range(len(basic_rows) - len(matrix), len(basic_rows))]

    table = [[0 for _ in range(len(matrix[0]) + 1)] for _ in range(len(basic) + 2)]
    table[0][0] = "Базисные переменные"
    table[0][1] = "Свободные члены"
    for i in range(2, len(table[0])):
        table[0][i] = f'X{i - 1}'

    for x in range(len(basic)):
        table[basic_rows[x] + 1][0] = f'X{basic[x] + 1}'
    for i in range(1, len(table) - 1):
        table[i][1] = matrix[i - 1][-1]
    for i in range(len(matrix)):
        for j in range(len(matrix[0]) - 1):
            table[i + 1][j + 2] = matrix[i][j]

    table[-1][0] = 'Z'
    table[-1][1] = z[0]
    for i in range(1, len(z)):
        table[-1][i + 1] = -z[i]

    return table

def check_solution(table):
    """Проверка решения."""
    return all(table[-1][i] >= 0 for i in range(2, len(table[0])))

def get_pivot_column(table):
    """Получение опорного столбца."""
    return min(range(2, len(table[0])), key=lambda i: table[-1][i] if table[-1][i] < 0 else float('inf'))

def next_step(table):
    """Выполнение следующего шага в методе искусственного базиса."""
    pivot_col = get_pivot_column(table)
    pivot_row = min((i for i in range(1, len(table) - 1) if table[i][pivot_col] > 0),
                    key=lambda i: table[i][1] / table[i][pivot_col], default=None)

    if pivot_row is None:
        print("Функция не ограничена")
        exit(5)

    pivot_value = table[pivot_row][pivot_col]
    table[pivot_row] = [x / pivot_value for x in table[pivot_row]]
    table[pivot_row][0] = f'X{pivot_col - 1}'

    for i in range(len(table)):
        if i != pivot_row:
            cof = -table[i][pivot_col]
            table[i] = [table[i][j] + table[pivot_row][j] * cof for j in range(len(table[i]))]

    return table

def print_table(table):
    """Вывод таблицы."""
    for row in table:
        print(" ".join(map(str, row)))

def print_solution(table):
    """Вывод решения."""
    print("Решение")
    solution = [0] * (len(table[0]) - 2)
    for i in range(1, len(table) - 1):
        solution[int(table[i][0][1]) - 1] = table[i][1]
    print(solution)
    print("Значение в точке максимума")
    print(f"Zmax = {table[-1][1]}")

def get_pivot_column_fict(table):
    """Получение опорного столбца во вспомогательной таблице."""
    return min(range(2, len(table[0])), key=lambda i: table[-2][i] if table[-2][i] < 0 else float('inf'))

def next_step_fict(table):
    """Выполнение следующего шага в вспомогательной таблице."""
    pivot_col = get_pivot_column_fict(table)
    pivot_row = min((i for i in range(1, len(table) - 2) if table[i][pivot_col] > 0),
                    key=lambda i: table[i][1] / table[i][pivot_col], default=None)

    if pivot_row is None or table[pivot_row][0][0] != 'Y':
        pivot_row = next(i for i in range(1, len(table) - 2) if table[i][0][0] == 'Y')
        if table[pivot_row][pivot_col] == 0:
            pivot_col = next(i for i in range(2, len(table[0]) - len(table) + 2) if abs(table[pivot_row][i]) > 1e-5)

    pivot_value = table[pivot_row][pivot_col]
    table[pivot_row] = [x / pivot_value for x in table[pivot_row]]
    table[pivot_row][0] = f'X{pivot_col - 1}'

    for i in range(len(table)):
        if i != pivot_row:
            cof = -table[i][pivot_col]
            table[i] = [table[i][j] + table[pivot_row][j] * cof for j in range(len(table[i]))]

    return table

def add_fict_variables(matrix):
    """Добавление фиктивных переменных."""
    new_matrix = [[0.0] * (len(matrix[0]) + len(matrix)) for _ in range(len(matrix))]
    for i in range(len(matrix)):
        for j in range(len(matrix[0]) - 1):
            new_matrix[i][j] = -matrix[i][j] if matrix[i][-1] < 0 else matrix[i][j]
        new_matrix[i][len(matrix[0]) + i - 1] = 1.0
        new_matrix[i][-1] = -matrix[i][-1] if matrix[i][-1] < 0 else matrix[i][-1]
    return new_matrix

def calculate_fict_z(matrix):
    """Вычисление значений Z в вспомогательной таблице."""
    zf = [0.0] * len(matrix[0])
    for j in range(len(matrix)):
        zf[0] -= matrix[j][-1]
    for i in range(1, len(zf) - len(matrix)):
        for j in range(len(matrix)):
            zf[i] += matrix[j][i - 1]
    return zf

def get_fict_basis_table(matrix, z):
    """Получение таблицы с фиктивным базисом."""
    new_matrix = add_fict_variables(matrix)
    zf = calculate_fict_z(new_matrix)
    table = get_first_table(new_matrix, zf)
    table.append([0] * len(table[0]))
    table[-1][0] = 'Z'
    table[-1][1] = z[0]
    for i in range(1, len(z)):
        table[-1][i + 1] = -z[i]
    for i in range(1, len(table) - 2):
        table[i][0] = f'Y{table[i][0][1]}'
    print_fict(table, len(matrix[0]) - 1)
    for _ in range(len(matrix)):
        table = next_step_fict(table)
        print_fict(table, len(matrix[0]) - 1)
    new_table = [[0] * (len(table[0]) - len(matrix)) for _ in range(len(table))]
    for i in range(len(new_table)):
        for j in range(len(new_table[0])):
            new_table[i][j] = table[i][j]
    new_table.pop(-2)
    new_table[-1][0] = 'Z'
    return new_table

def print_fict(table, n):
    """Вывод вспомогательной таблицы."""
    for i in range(len(table) - 1):
        print(" ".join(map(str, table[i])))

def print_fict_solution(matrix, z):
    """Вывод решения с фиктивными переменными."""
    table = get_fict_basis_table(matrix, z)
    print_table(table)
    while not check_solution(table):
        table = next_step(table)
        print_table(table)
    print_solution(table)

def calculate_mz(matrix, z, M):
    """Вычисление значений Z с большими штрафами."""
    zf = [0.0] * len(matrix[0])
    for i in range(len(z)):
        zf[i] += z[i]
    for j in range(len(matrix)):
        zf[0] -= M * matrix[j][-1]
    for i in range(1, len(zf) - len(matrix)):
        for j in range(len(matrix)):
            zf[i] += M * matrix[j][i - 1]
    return zf

def get_big_table(matrix, z):
    """Получение таблицы с большими штрафами."""
    M = 1000
    new_matrix = add_fict_variables(matrix)
    zf = calculate_mz(new_matrix, z, M)
    return get_first_table(new_matrix, zf)

def print_big_solution(matrix, z):
    """Вывод решения с большими штрафами."""
    table = get_big_table(matrix, z)
    print_table(table)
    while not check_solution(table):
        table = next_step(table)
        print_table(table)
    print_solution(table)

def main():
    """Основная функция."""
    matrix = read_matrix()
    z = read_function()
    print("Искусственный базис")
    print_fict_solution(matrix, z)
    print("\nБольшие штрафы")
    print_big_solution(matrix, z)

if __name__ == "__main__":
    main()
