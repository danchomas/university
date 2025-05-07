from scipy.linalg import lu_factor, lu_solve
import numpy as np

A = np.array([[-54.00000001, 16.00000001, -35.00000001],
              [29.00000001, -66.00000001, 40.00000001],
              [45.00000001, -21.00000001, 63.00000001]], dtype=float)

b = np.array([10, -5, 20.00000001], dtype=float)

x = np.linalg.solve(A, b)
print("решение системы с использованием numpy.linalg.solve:", x)

lu, piv = lu_factor(A)
x_lu = lu_solve((lu, piv), b)
print("решение системы с использованием scipy.linalg:", x_lu)

def gauss(A, b):
    numEquations = len(b)
    for pivotRow in range(numEquations):
        for currentRow in range(pivotRow + 1, numEquations):
            factor = A[currentRow, pivotRow] / A[pivotRow, pivotRow]
            for currentCol in range(pivotRow, numEquations):
                A[currentRow, currentCol] -= factor * A[pivotRow, currentCol]
            b[currentRow] -= factor * b[pivotRow]
    solutionVector = np.zeros(numEquations)
    for currentRow in range(numEquations - 1, -1, -1):
        sum_ax = 0
        for currentCol in range(currentRow + 1, numEquations):
            sum_ax += A[currentRow, currentCol] * solutionVector[currentCol]
        solutionVector[currentRow] = (b[currentRow] - sum_ax) / A[currentRow, currentRow]
    return solutionVector

print("решение системы методом Гаусса:", gauss(A.copy(), b.copy()))

def gauss_elimination_with_partial_pivoting(matrix, vector):
    matrix_size = len(matrix)
    for current_column in range(matrix_size):
        max_index = np.argmax(np.abs(matrix[current_column:, current_column])) + current_column
        matrix[[current_column, max_index]], vector[[current_column, max_index]] = \
            matrix[[max_index, current_column]], vector[[max_index, current_column]]
        for i in range(current_column + 1, matrix_size):
            factor = matrix[i][current_column] / matrix[current_column][current_column]
            matrix[i, current_column:] -= factor * matrix[current_column, current_column:]
            vector[i] -= factor * vector[current_column]
    solution = np.zeros(matrix_size)
    for i in range(matrix_size - 1, -1, -1):
        solution[i] = (vector[i] - np.dot(matrix[i, i + 1:], solution[i + 1:])) / matrix[i][i]
    return solution

print("решение системы методом Гаусса с частичным выбором ведущего элемента:",
      gauss_elimination_with_partial_pivoting(A.copy(), b.copy()))

def lu_decomposition(matrix, vector):
    matrix_size = len(matrix)
    L = np.zeros((matrix_size, matrix_size))
    U = np.zeros((matrix_size, matrix_size))
    for row in range(matrix_size):
        L[row, row] = 1
        for col in range(row, matrix_size):
            sum_upper = sum(L[row, sum_index] * U[sum_index, col] for sum_index in range(row))
            U[row, col] = matrix[row, col] - sum_upper
        for col in range(row + 1, matrix_size):
            sum_lower = sum(L[col, sum_index] * U[sum_index, row] for sum_index in range(row))
            L[col, row] = (matrix[col, row] - sum_lower) / U[row, row]
    y = np.zeros(matrix_size)
    for row in range(matrix_size):
        y[row] = vector[row] - np.dot(L[row, :row], y[:row])
    x = np.zeros(matrix_size)
    for row in range(matrix_size - 1, -1, -1):
        x[row] = (y[row] - np.dot(U[row, row + 1:], x[row + 1:])) / U[row, row]
    return x

print("решение системы с использованием LU-разложения:", lu_decomposition(A.copy(), b.copy()))
