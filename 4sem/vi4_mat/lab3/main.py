import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import fsolve

def nonlinear_equations(variables):
    x1, x2 = variables
    equation1 = np.sqrt(np.exp(x2)) + x1**2 - 6
    equation2 = np.sin(x1) + np.cosh(x2) - 2
    return [equation1, equation2]

def plot_solution_and_equations(solution):
    x1_values = np.linspace(-5, 5, 400)
    x2_values = np.linspace(-5, 5, 400)
    X1, X2 = np.meshgrid(x1_values, x2_values)
    Z1 = np.sqrt(np.exp(X2)) + X1**2 - 6
    Z2 = np.sin(X1) + np.cosh(X2) - 2

    plt.figure(figsize=(8, 6))
    contour1 = plt.contour(X1, X2, Z1, levels=[0], colors='r')
    plt.clabel(contour1, inline=True, fontsize=10, fmt='Уравнение 1')
    contour2 = plt.contour(X1, X2, Z2, levels=[0], colors='b')
    plt.clabel(contour2, inline=True, fontsize=10, fmt='Уравнение 2')
    plt.plot(solution[0], solution[1], 'ko', label='Решение')
    plt.text(solution[0], solution[1], ' Решение', verticalalignment='bottom')
    plt.xlabel('x1')
    plt.ylabel('x2')
    plt.title('Решение системы нелинейных уравнений')
    plt.grid(True)
    plt.legend()
    plt.show()

initial_guess = [1.0, 1.0]

solution = fsolve(nonlinear_equations, initial_guess)
print(f"Решение: x1 = {solution[0]}, x2 = {solution[1]}")

plot_solution_and_equations(solution)