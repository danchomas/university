import numpy as np
from scipy.optimize import linprog


def transform_fractional_problem():
    """Преобразование дробной задачи в линейную форму"""
    # Коэффициенты целевой функции и ограничений
    numerator_coeff = [9, 3, 2, 1]  # Числитель
    denominator_coeff = [2, 1, 3, 1]  # Знаменатель

    # Матрица ограничений исходной задачи
    A_orig = [
        [6, 1, 1, 3],
        [1, 0, 3, 2],
        [2, 4, 1, 0]
    ]
    b_orig = [280, 70, 320]

    # Создание расширенной системы переменных [y1, y2, y3, y4, t]
    c = numerator_coeff + [0]  # Целевая функция: 9y1 + 3y2 + 2y3 + y4

    # Матрица ограничений для преобразованной задачи
    A_eq = []
    b_eq = []

    # Добавление ограничений из исходной задачи
    for i in range(len(A_orig)):
        row = A_orig[i] + [-b_orig[i]]
        A_eq.append(row)
        b_eq.append(0)

    # Ограничение знаменателя: 2y1 + y2 + 3y3 + y4 = 1
    denom_row = denominator_coeff + [-1]
    A_eq.append(denom_row)
    b_eq.append(1)

    # Решение расширенной задачи ЛП
    res = linprog(
        c=c,
        A_eq=A_eq,
        b_eq=b_eq,
        bounds=[(0, None)] * 5,
        method='highs'
    )

    if res.success:
        t = res.x[-1]
        if t > 1e-8:
            solution = [res.x[i] / t for i in range(4)]
            z_value = sum(numerator_coeff[i] * solution[i] for i in range(4)) / sum(
                denominator_coeff[i] * solution[i] for i in range(4))

            print("Оптимальное решение:")
            print(f"x₁ = {solution[0]:.2f}")
            print(f"x₂ = {solution[1]:.2f}")
            print(f"x₃ = {solution[2]:.2f}")
            print(f"x₄ = {solution[3]:.2f}")
            print(f"Максимальное z = {z_value:.4f}")
        else:
            print("Решение не соответствует условиям")
    else:
        print("Оптимальное решение не найдено")


if __name__ == "__main__":
    transform_fractional_problem()