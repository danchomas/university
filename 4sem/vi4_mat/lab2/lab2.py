import numpy as np
from scipy.linalg import lu_factor, lu_solve
import time
import matplotlib.pyplot as plt

# Функция для дополнения матрицы до ближайшей степени двойки
def pad_matrix(matrix):
    n = matrix.shape[0]
    next_power_of_two = 2 ** int(np.ceil(np.log2(n)))
    padded_matrix = np.zeros((next_power_of_two, next_power_of_two))
    padded_matrix[:n, :n] = matrix
    return padded_matrix

# Функция для удаления дополнения из матрицы
def unpad_matrix(matrix, original_size):
    return matrix[:original_size, :original_size]

# Функция для умножения матриц по алгоритму Штрассена
def strassen_mat_mul(mat_left, mat_right):
    size = mat_left.shape[0]
    if size == 1:
        return mat_left * mat_right
    else:
        mid = size // 2
        left_top = mat_left[:mid, :mid]
        right_top = mat_left[:mid, mid:]
        left_bottom = mat_left[mid:, :mid]
        right_bottom = mat_left[mid:, mid:]
        
        top_left = mat_right[:mid, :mid]
        top_right = mat_right[:mid, mid:]
        bottom_left = mat_right[mid:, :mid]
        bottom_right = mat_right[mid:, mid:]
        
        m1 = strassen_mat_mul(left_top + right_bottom, top_left + bottom_right)
        m2 = strassen_mat_mul(left_bottom + right_bottom, top_left)
        m3 = strassen_mat_mul(left_top, top_right - bottom_right)
        m4 = strassen_mat_mul(right_bottom, bottom_left - top_left)
        m5 = strassen_mat_mul(left_top + right_top, bottom_right)
        m6 = strassen_mat_mul(left_bottom - left_top, top_left + top_right)
        m7 = strassen_mat_mul(right_top - right_bottom, bottom_left + bottom_right)
        
        result_top_left = m1 + m4 - m5 + m7
        result_top_right = m3 + m5
        result_bottom_left = m2 + m4
        result_bottom_right = m1 - m2 + m3 + m6
        
        result_matrix = np.vstack((np.hstack((result_top_left, result_top_right)),
                                   np.hstack((result_bottom_left, result_bottom_right))))
        
        return result_matrix

# Функция для умножения матриц с использованием алгоритма Штрассена
def strassen_multiply(mat_left, mat_right):
    original_size = mat_left.shape[0]
    padded_left = pad_matrix(mat_left)
    padded_right = pad_matrix(mat_right)
    
    result_padded = strassen_mat_mul(padded_left, padded_right)
    return unpad_matrix(result_padded, original_size)

# Функция для прямого умножения матриц
def multiply_matrices(mat_left, mat_right):
    rows_left, common_dim = mat_left.shape
    _, cols_right = mat_right.shape
    result_matrix = np.zeros((rows_left, cols_right))
    
    for row_index in range(rows_left):
        for col_index in range(cols_right):
            for common_index in range(common_dim):
                result_matrix[row_index, col_index] += mat_left[row_index, common_index] * mat_right[common_index, col_index]
    
    return result_matrix

# Функция для генерации случайной квадратной матрицы
def generate_square_matrix(n, min_val=0, max_val=10):
    matrix = np.random.randint(min_val, max_val+1, size=(n, n))
    return matrix.astype(np.float32)

# Функция для проверки корректности результатов умножения
def check_results(result_strassen, result_regular, tolerance=1e-5):
    return np.allclose(result_strassen, result_regular, atol=tolerance)

# Функция для измерения времени выполнения функции dot
def measure_time_dot(n_values):
    times = []
    for n in n_values:
        mat_left = generate_square_matrix(n)
        mat_right = generate_square_matrix(n)
        
        start_time = time.time()
        np.dot(mat_left, mat_right)
        end_time = time.time()
        
        times.append(end_time - start_time)
    return times

# Функция для нахождения обратной матрицы
def find_inverse_matrix(matrix):
    return np.linalg.inv(matrix)

# Функция для нахождения собственных чисел и векторов
def find_eigenvalues_and_eigenvectors(matrix):
    eigenvalues, eigenvectors = np.linalg.eig(matrix)
    return eigenvalues, eigenvectors

# Основной код
if __name__ == '__main__':
    # Исходные данные
    A = np.array([[-54, 16, -35],
                  [29, -66, 40],
                  [45, -21, 63]], dtype=float)

    b = np.array([10, -5, 20.00000001], dtype=float)

    # Умножение матриц по алгоритму Штрассена
    random_matrix = generate_square_matrix(3)
    result_strassen = strassen_multiply(A, random_matrix)
    result_regular = multiply_matrices(A, random_matrix)

    if check_results(result_strassen, result_regular):
        print("Результаты умножения матриц - ОК")
    else:
        print("Результаты умножения матриц НЕ совпадают")

    # Оценка временной сложности функции dot
    n_values = [4, 16, 32, 64, 128, 256, 512]  # Используем степени двойки
    times = measure_time_dot(n_values)

    plt.plot(n_values, times, marker='o')
    plt.xlabel('Размер матрицы (n x n)')
    plt.ylabel('Время выполнения (секунды)')
    plt.title('Временная сложность функции dot из NumPy')
    plt.grid(True)
    plt.show()

    # Нахождение обратной матрицы
    inverse_A = find_inverse_matrix(A)
    print("Обратная матрица A:\n", inverse_A)

    # Нахождение собственных чисел и векторов
    eigenvalues, eigenvectors = find_eigenvalues_and_eigenvectors(A)
    print("Собственные числа:\n", eigenvalues)
    print("Собственные векторы:\n", eigenvectors)

    # Решение СЛАУ методом обратной матрицы
    x = np.dot(inverse_A, b)
    print("Решение СЛАУ методом обратной матрицы:", x)

    # Сравнение с LU-разложением
    lu, piv = lu_factor(A)
    x_lu = lu_solve((lu, piv), b)
    print("Решение системы с использованием LU-разложения:", x_lu)

    if np.allclose(x, x_lu, atol=1e-5):
        print("Результаты совпадают.")
    else:
        print("Результаты НЕ совпадают.")