import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

# Загрузка и подготовка данных
data = pd.read_csv('covid.csv', parse_dates=['DateTime'])
data = data.sort_values('DateTime')

# Выбираем период: апрель 2021 + 90 дней
start_date = pd.to_datetime('2021-04-01')
end_date = start_date + pd.Timedelta(days=90)
selected_data = data[(data['DateTime'] >= start_date) & (data['DateTime'] <= end_date)].copy()

# Преобразуем даты в числовые значения (дни с начала периода)
selected_data['Days'] = (selected_data['DateTime'] - selected_data['DateTime'].min()).dt.days

# Логарифмируем данные о заражениях
selected_data['Заражений за день'].replace(0, np.nan, inplace=True)
selected_data.dropna(subset=['Заражений за день'], inplace=True)
selected_data['LogInfections'] = np.log(selected_data['Заражений за день'])

# Ручная реализация линейной регрессии
n = len(selected_data)
x = selected_data['Days']
y = selected_data['LogInfections']

r_value, p_value = stats.pearsonr(x, y)

# Вычисляем коэффициенты регрессии вручную
x_mean = np.mean(x)
y_mean = np.mean(y)

numerator = np.sum((x - x_mean) * (y - y_mean))
denominator = np.sum((x - x_mean)**2)
slope = numerator / denominator
intercept = y_mean - slope * x_mean

# Параметры экспоненциальной модели
A = np.exp(intercept)
b = slope

# Выводим результаты
print("\nРезультаты анализа:")
print(f"Коэффициент корреляции Пирсона (r): {r_value:.4f}")
print(f"p-value: {p_value:.3e}")  # Например, "1.23e-100"
print(f"\nПараметры экспоненциальной модели:")
print(f"A = {A:.2f}")
print(f"b = {b:.4f}")
print(f"R² (коэффициент детерминации): {r_value**2:.4f}")

# Проверяем гипотезу
alpha = 0.05
if p_value < alpha:
    print("\nВывод: p-значение < 0.05, отвергаем нулевую гипотезу.")
    print("Рост заражений COVID-19 статистически значимо описывается экспоненциальной моделью.")
else:
    print("\nВывод: p-значение ≥ 0.05, нет оснований отвергать нулевую гипотезу.")
    print("Нет статистически значимых доказательств экспоненциального роста.")

# Визуализация
plt.figure(figsize=(10, 6))
plt.plot(selected_data['DateTime'], selected_data['Заражений за день'], 'b-', label='Фактические данные')
plt.plot(selected_data['DateTime'], A * np.exp(b * selected_data['Days']), 'r--', 
         label=f'Экспоненциальная модель: y = {A:.0f}e^{b:.3f}t')
plt.xlabel('Дата')
plt.ylabel('Заражений за день')
plt.title('Рост заражений COVID-19 и экспоненциальная модель')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()