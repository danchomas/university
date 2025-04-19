from fractions import Fraction

def print_table(iteration, basis, table, delta_row=None):
    headers = ["Базисные переменные", "x1", "x2", "x3", "x4", "x5", "x6", "x7", "u1", "u2", "Свободные члены"]
    col_width = 8  # Ширина каждого столбца

    print(f"\n{iteration}")

    # Вывод заголовков
    headers_str = "|".join(f"{header:^{col_width}}" for header in headers)
    print(headers_str)
    print("|".join("-" * col_width for _ in headers))

    # Вывод строк таблицы
    for i in range(len(basis)):
        row = [basis[i]] + [str(Fraction(val).limit_denominator()) for val in table[i]]
        row_str = "|".join(f"{item:^{col_width}}" for item in row)
        print(row_str)

    # Вывод строки дельта
    if delta_row:
        delta = ["Δ"] + [str(Fraction(val).limit_denominator()) if abs(val - round(val)) > 1e-6 else str(int(round(val))) for val in delta_row]
        delta_str = "|".join(f"{item:^{col_width}}" for item in delta)
        print(delta_str)

def solve_problem():
    print("Старт")

    # Начальная таблица с искусственными переменными
    basis = ["x8", "x6", "x9"]
    table = [
        [3, -1, 2, 3, 1, 0, 0, 1, 0, 22],
        [1, 4, 2, 5, -2, 1, 0, 0, 0, 46],
        [-1, 4, 6, 3, -8, 0, -1, 0, 1, 62]
    ]
    delta_row = [-12, 4, -1, -9, 5, 0, 0, 0, 0, -84]
    print_table("Начальная таблица", basis, table, delta_row)

    # Первая итерация (вводим x3 в базис)
    print("\nИтерация 1 (вводим x3 в базис)")
    basis = ["x8", "x6", "x3"]
    table = [
        [10/3, -7/3, 0, 2, 11/3, 0, 1/3, 1, -1/3, 4/3],
        [4/3, 8/3, 0, 4, 2/3, 1, 1/3, 0, -1/3, 76/3],
        [-1/6, 2/3, 1, 1/2, -4/3, 0, -1/6, 0, 1/6, 31/3]
    ]
    delta_row = [-73/6, 14/3, 0, -17/2, 11/3, 0, -1/6, 0, 1/6, 31/3]
    print_table("Промежуточная таблица", basis, table, delta_row)

    # Вторая итерация (вводим x5 в базис)
    print("\nИтерация 2 (вводим x5 в базис)")
    basis = ["x5", "x6", "x3"]
    table = [
        [10/11, -7/11, 0, 6/11, 1, 0, 1/11, 3/11, -1/11, 4/11],
        [8/11, 34/11, 0, 40/11, 0, 1, 3/11, -2/11, -3/11, 276/11],
        [23/22, -2/11, 1, 27/22, 0, 0, -1/22, 4/11, 1/22, 119/11]
    ]
    delta_row = [-31/2, 7, 0, -21/2, 0, 0, -1/2, -1, 1/2, 9]
    print_table("Промежуточная таблица", basis, table, delta_row)

    # Третья итерация (вводим x1 в базис)
    print("\nИтерация 3 (вводим x1 в базис)")
    basis = ["x1", "x6", "x3"]
    table = [
        [1, -7/10, 0, 3/5, 11/10, 0, 1/10, 3/10, -1/10, 2/5],
        [0, 18/5, 0, 16/5, -4/5, 1, 1/5, -2/5, -1/5, 124/5],
        [0, 11/20, 1, 3/5, -23/20, 0, -3/20, 1/20, 3/20, 52/5]
    ]
    delta_row = [0, -77/20, 0, -6/5, 341/20, 0, 21/20, 73/20, -21/20, 76/5]
    print_table("Промежуточная таблица", basis, table, delta_row)

    # Четвертая итерация (вводим x2 в базис)
    print("\nИтерация 4 (вводим x2 в базис)")
    basis = ["x1", "x2", "x3"]
    table = [
        [1, 0, 0, 11/9, 17/18, 7/36, 5/36, 2/9, -5/36, 47/9],
        [0, 1, 0, 8/9, -2/9, 5/18, 1/18, -1/9, -1/18, 62/9],
        [0, 0, 1, 1/9, -37/36, -11/72, -13/72, 1/9, 13/72, 119/18]
    ]
    delta_row = [0, 0, 0, 20/9, 583/36, 77/72, 91/72, 29/9, -91/72, 751/18]
    print_table("Финальная таблица", basis, table, delta_row)

    # Результат
    print("\nОптимальное решение:")
    print(f"x1 = {Fraction(47/9).limit_denominator()}")
    print(f"x2 = {Fraction(62/9).limit_denominator()}")
    print(f"x3 = {Fraction(119/18).limit_denominator()}")
    print(f"x4 = 0")
    print(f"x5 = 0")
    print(f"F(X) = {Fraction(751/18).limit_denominator()}")

# Запускаем решение
solve_problem()
