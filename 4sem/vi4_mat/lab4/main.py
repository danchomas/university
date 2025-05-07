import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime, timedelta
from scipy.interpolate import interp1d, lagrange
import pandas as pd
from prophet import Prophet
from statsmodels.tsa.arima.model import ARIMA
from statsmodels.tsa.holtwinters import ExponentialSmoothing

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

# Целевая дата и реальное значение (предполагается, что 2025-04-01 = 2.33)
test_date = datetime(2025, 4, 1)
actual_value = 2.33

# Преобразование дат в дни относительно начала
start_date = df['Дата'].iloc[0]
df['Дни'] = (df['Дата'] - start_date).dt.days
x = df['Дни'].values
y = df['Курс'].values

# Функции для интерполяции Ньютона
def calculate_divided_differences(x, y):
    n = len(y)
    coef = np.zeros((n, n))
    coef[:,0] = y
    for j in range(1, n):
        for i in range(n - j):
            coef[i][j] = (coef[i+1][j-1] - coef[i][j-1]) / (x[i+j] - x[i])
    return coef[0, :]

def newton_interpolate(x_val, xi, coefs):
    result = coefs[-1]
    for i in range(len(coefs)-2, -1, -1):
        result = result * (x_val - xi[i]) + coefs[i]
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

# Интерполяция Ньютона (базовая и с Чебышёвым)
coefs = calculate_divided_differences(x, y)
new_x, new_y = add_chebyshev_nodes(x, y)
coefs_cheb = calculate_divided_differences(new_x, new_y)

# Интерполяция Лагранжа
poly_lagrange = lagrange(x, y)

# Экстраполяция Prophet
prophet_df = df.rename(columns={'Дата': 'ds', 'Курс': 'y'})
model_prophet = Prophet()
model_prophet.fit(prophet_df)
future_prophet = model_prophet.make_future_dataframe(periods=30)
forecast_prophet = model_prophet.predict(future_prophet)

# Экстраполяция ARIMA
model_arima = ARIMA(y, order=(1,1,1)).fit()
forecast_arima = model_arima.forecast(steps=30)
forecast_arima = pd.Series(forecast_arima)

# Экстраполяция ETS
model_ets = ExponentialSmoothing(y).fit()
forecast_ets = model_ets.forecast(30)
forecast_ets = pd.Series(forecast_ets)

# Расчет дней для целевой даты
test_day = (test_date - start_date).days

# Прогнозы всех методов
newton_pred = newton_interpolate(test_day, x, coefs)
newton_cheb_pred = newton_interpolate(test_day, new_x, coefs_cheb)
lagrange_pred = poly_lagrange(test_day)
prophet_pred = forecast_prophet[forecast_prophet['ds'] == test_date]['yhat'].values[0]
arima_pred = forecast_arima.iloc[-1]
ets_pred = forecast_ets.iloc[-1]

# Сравнение ошибок
results = pd.DataFrame({
    'Метод': ['Ньютон', 'Ньютон+Чебышёв', 'Лагранж', 'Prophet', 'ARIMA', 'ETS'],
    'Прогноз': [newton_pred, newton_cheb_pred, lagrange_pred, prophet_pred, arima_pred, ets_pred],
    'Ошибка': [abs(p - actual_value) for p in [newton_pred, newton_cheb_pred, lagrange_pred, prophet_pred, arima_pred, ets_pred]]
})

# Визуализация
plt.figure(figsize=(14, 8))
plt.plot(df['Дата'], df['Курс'], 'ko-', label='Исторические данные')
plt.axvline(test_date, color='gray', linestyle='--', label='Целевая дата')

# Прогнозы
methods = results['Метод']
colors = ['red', 'orange', 'purple', 'blue', 'green', 'cyan']
for i, method in enumerate(methods):
    plt.plot(test_date, results.iloc[i]['Прогноз'], 'o', color=colors[i],
             markersize=10, label=f"{method}: {results.iloc[i]['Ошибка']:.2f}")

plt.title(f'Сравнение методов прогнозирования (Реальное значение: {actual_value})')
plt.xlabel('Дата')
plt.ylabel('Курс')
plt.legend()
plt.grid(True)
plt.xticks(rotation=45)
plt.tight_layout()
plt.show()

print("Результаты сравнения:")
print(results.to_string(index=False))
