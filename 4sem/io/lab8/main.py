import numpy as np
from scipy.optimize import linprog
def solve_ratio_optimization():
    """Решение задачи дробного программирования методом линеаризации"""
    # Коэффициенты целевой функции (числитель и знаменатель)
    num_coeffs = [9, 3, 2, 1]  # Коэффициенты числителя
    denom_coeffs = [2, 1, 3, 1]  # Коэффициенты знаменателя
    # Матрица условий и вектор ограничений исходной задачи
    constraint_matrix = [
        [6, 1, 1, 3],
        [1, 0, 3, 2],
        [2, 4, 1, 0]
    ]
    constraint_values = [280, 70, 320]
    # Формирование расширенной задачи
    objective = num_coeffs + [0]  # Целевая функция с дополнительной переменной
    # Подготовка ограничений равенств
    equality_constraints = []
    equality_values = []
    # Преобразование исходных ограничений
    for i in range(len(constraint_matrix)):
        new_row = constraint_matrix[i] + [-constraint_values[i]]
        equality_constraints.append(new_row)
        equality_values.append(0)
    # Добавление условия для знаменателя
    denom_condition = denom_coeffs + [-1]
    equality_constraints.append(denom_condition)
    equality_values.append(1)
    # Решение модифицированной задачи линейного программирования
    result = linprog(
        c=objective,
        A_eq=equality_constraints,
        b_eq=equality_values,
        bounds=[(0, None)] * (len(num_coeffs) + 1),
        method='highs'
    )
    if result.success:
        scale_factor = result.x[-1]
        if scale_factor > 1e-8:
            # Вычисление оптимального решения исходной задачи
            optimal_solution = [result.x[i] / scale_factor for i in range(4)]
            numerator_value = sum(num_coeffs[i] * optimal_solution[i] for i in range(4))
            denominator_value = sum(denom_coeffs[i] * optimal_solution[i] for i in range(4))
            optimal_value = numerator_value / denominator_value
            print("Найденное оптимальное решение:")
            print(f"x₁ = {optimal_solution[0]:.4f}")
            print(f"x₂ = {optimal_solution[1]:.4f}")
            print(f"x₃ = {optimal_solution[2]:.4f}")
            print(f"x₄ = {optimal_solution[3]:.4f}")
            print(f"Оптимальное значение целевой функции: {optimal_value:.6f}")
        else:
            print("Полученное решение не удовлетворяет условиям")
    else:
        print("Оптимальное решение не найдено")
if __name__ == "__main__":
    solve_ratio_optimization()
