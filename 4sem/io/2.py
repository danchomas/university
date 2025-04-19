import itertools
import numpy as np

EPS = 1e-9

def rearrange_columns(matrix, basis):
    cols = len(matrix[0]) - 1
    new_matrix = []
    for row in matrix:
        new_row = [row[b] for b in basis]
        new_row += [row[c] for c in range(cols) if c not in basis]
        new_row.append(row[-1])
        new_matrix.append(new_row)
    return new_matrix

def gauss_jordan(matrix):
    rows = len(matrix)
    cols = len(matrix[0]) - 1
    leading_columns = []
    lead = 0

    for r in range(rows):
        if lead >= cols:
            break
        i = r
        while abs(matrix[i][lead]) < EPS:
            i += 1
            if i == rows:
                i = r
                lead += 1
                if cols == lead:
                    break
        if i == rows:
            continue
        matrix[i], matrix[r] = matrix[r], matrix[i]
        div = matrix[r][lead]
        matrix[r] = [x / div for x in matrix[r]]
        for i in range(rows):
            if i != r:
                factor = matrix[i][lead]
                matrix[i] = [matrix[i][j] - factor * matrix[r][j] for j in range(cols + 1)]
        leading_columns.append(lead)
        lead += 1
    return matrix, leading_columns

def is_valid_basis(basis, leading_columns):
    return len(leading_columns) == len(basis) and all(lc < len(basis) for lc in leading_columns)

def is_feasible(solution):
    return all(x >= -EPS for x in solution)

def objective_function(solution):
    return sum(solution)

def print_solution(matrix, basis, solution):
    print("базисные переменные:", " ".join(f"x{b+1}" for b in basis))
    print("решение:")
    for r in range(len(matrix)):
        lead_col = -1
        for c in range(len(basis)):
            if abs(matrix[r][c] - 1.0) < EPS:
                lead_col = c
                break
        if lead_col == -1:
            if abs(matrix[r][-1]) > EPS:
                print("система несовместна")
            continue
        actual_var = basis[lead_col]
        print(f"x{actual_var + 1} = {matrix[r][-1]:.2f}", end="")
        for c in range(len(basis), len(matrix[r]) - 1):
            coeff = matrix[r][c]
            if abs(coeff) > EPS:
                var_index = c - len(basis)
                if coeff < 0:
                    print(f" + {-coeff:.2f}*x{var_index + 1}", end="")
                else:
                    print(f" - {coeff:.2f}*x{var_index + 1}", end="")
        print()

def find_basic_solutions(original, num_vars):
    num_eqs = len(original)
    vars_list = list(range(num_vars))
    selector = [True] * num_eqs + [False] * (num_vars - num_eqs)
    feasible_solutions = []
    count = 0

    while True:
        basis = [i for i, selected in enumerate(selector) if selected]
        if len(basis) != num_eqs:
            continue
        matrix = rearrange_columns(original, basis)
        matrix, leading_columns = gauss_jordan(matrix)

        print(f"комбинация базиса {count + 1}:")
        print("преобразованная матрица:")
        for row in matrix:
            print(" ".join(f"{val:8.2f}" for val in row))
        count += 1

        if is_valid_basis(basis, leading_columns):
            solution = [0.0] * num_vars
            for r in range(len(matrix)):
                for c in range(len(basis)):
                    if abs(matrix[r][c] - 1.0) < EPS:
                        solution[basis[c]] = matrix[r][-1]
                        break

            if is_feasible(solution):
                feasible_solutions.append(solution)
                print_solution(matrix, basis, solution)
                print(f"целевая функция: {objective_function(solution)}\n")
            else:
                print("решение недопустимо (есть отрицательные переменные)\n")
        else:
            print("не является допустимым базисом\n")
        if not prev_permutation(selector):
            break

    if feasible_solutions:
        optimal_solution = min(feasible_solutions, key=objective_function)
        print("\nоптимальный опорный план:")
        print(" ".join(f"{x:.2f}" for x in optimal_solution))
        print(f"целевая функция: {objective_function(optimal_solution)}")
    else:
        print("\nдопустимые решения отсутствуют!")

def prev_permutation(arr):
    i = len(arr) - 1
    while i > 0 and arr[i - 1] <= arr[i]:
        i -= 1
    if i <= 0:
        return False
    j = len(arr) - 1
    while arr[j] >= arr[i - 1]:
        j -= 1
    arr[i - 1], arr[j] = arr[j], arr[i - 1]
    arr[i:] = arr[:i - 1:-1]
    return True

if __name__ == "__main__":
    matrix = [
        [-1, 5, -4, -6, 0, 1, -9],
        [8, 1, -1, 0, 2, 3, 8],
        [4, 3, -2, 9, 1, 7, 1]
    ]
    find_basic_solutions(matrix, 6)