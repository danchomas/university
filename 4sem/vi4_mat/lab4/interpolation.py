import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime, timedelta
from scipy.interpolate import interp1d
import pandas as pd

# Исходные данные (Sui)
data = {
    'Дата': ["23/09/2024", "08/10/2024", "23/10/2024", "07/11/2024", "22/11/2024",
             "07/12/2024", "22/12/2024", "06/01/2025", "21/01/2025", "05/02/2025",
             "20/02/2025", "07/03/2025", "21/03/2025"],
    'Курс': [1.57804869892772, 2.02903121302639, 1.93605439439491, 2.30551725875415,
             3.64254927718127, 4.22049238320624, 4.35736768516244, 5.23788404785415,
             4.38228730890465, 3.61551275455427, 3.21522908182406, 2.74204256253017,
             2.32389204445761]
}

df = pd.DataFrame(data)
df['Дата'] = pd.to_datetime(df['Дата'], format='%d/%m/%Y')
df = df.sort_values('Дата').reset_index(drop=True)

# Преобразование дат в дни
start_date = df['Дата'].iloc[0]
df['Дни'] = (df['Дата'] - start_date).dt.days

# Функции для интерполяции Ньютона
def calculate_divided_differences(x, y):
    n = len(y)
    coef = np.zeros([n, n])
    coef[:,0] = y
    for j in range(1, n):
        for i in range(n - j):
            coef[i][j] = (coef[i+1][j-1] - coef[i][j-1]) / (x[i+j] - x[i])
    return coef[0, :]

def newton_interpolate(x, xi, coefs):
    result = coefs[-1]
    for i in range(len(coefs)-2, -1, -1):
        result = result * (x - xi[i]) + coefs[i]
    return result

# Добавление узлов Чебышёва
def add_chebyshev_nodes(x, y, num_nodes=5):
    a, b = min(x), max(x)
    k = np.arange(1, num_nodes+1)
    cheb_nodes = 0.5*(a + b) + 0.5*(b - a)*np.cos((2*k - 1)*np.pi/(2*num_nodes))
    interp = interp1d(x, y, kind='cubic', fill_value="extrapolate")
    cheb_values = interp(cheb_nodes)
    new_x = np.sort(np.concatenate([x, cheb_nodes]))
    new_y = interp(new_x)
    return new_x, new_y

# Расчет коэффициентов
x = df['Дни'].values
y = df['Курс'].values
coefs = calculate_divided_differences(x, y)

# Добавление узлов Чебышёва и пересчет
new_x, new_y = add_chebyshev_nodes(x, y)
new_coefs = calculate_divided_differences(new_x, new_y)

# Интерполяция для тестовой даты (21/03/2025)
test_date = datetime.strptime("21/03/2025", "%d/%m/%Y")
test_day = (test_date - start_date).days
interp_value = newton_interpolate(test_day, x, coefs)
actual_value = df['Курс'].iloc[-1]
error = abs(interp_value - actual_value)

# Визуализация
plt.figure(figsize=(12, 6))
plt.plot(df['Дата'], df['Курс'], 'bo', label='Исходные данные')
x_vals = np.linspace(min(x), max(x), 365)
y_vals = [newton_interpolate(day, x, coefs) for day in x_vals]
dates = [start_date + timedelta(days=int(day)) for day in x_vals]
plt.plot(dates, y_vals, 'r--', label='Полином Ньютона')

y_vals_cheb = [newton_interpolate(day, new_x, new_coefs) for day in x_vals]
plt.plot(dates, y_vals_cheb, 'g-', label='С узлами Чебышёва')

plt.plot(test_date, interp_value, 'k*', markersize=10, label=f'Ошибка: {error:.2f}')
plt.title('Интерполяция курса Sui')
plt.xlabel('Дата')
plt.ylabel('Курс')
plt.legend()
plt.grid(True)
plt.xticks(rotation=45)
plt.tight_layout()
plt.show()
