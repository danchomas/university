import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime
import pandas as pd
from prophet import Prophet
from statsmodels.tsa.arima.model import ARIMA
from statsmodels.tsa.holtwinters import ExponentialSmoothing

# Исходные данные
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

# Целевая дата и реальное значение
test_date = datetime(2025, 4, 1)
actual_value = 2.38

# Прогнозирование с помощью Prophet
prophet_df = df.rename(columns={'Дата': 'ds', 'Курс': 'y'})
model_prophet = Prophet()
model_prophet.fit(prophet_df)
future = model_prophet.make_future_dataframe(periods=30)
forecast_prophet = model_prophet.predict(future)

# Прогнозирование с помощью ARIMA
model_arima = ARIMA(df['Курс'], order=(1,1,1)).fit()
forecast_arima = model_arima.forecast(steps=30)

# Прогнозирование с помощью ETS
model_ets = ExponentialSmoothing(df['Курс']).fit()
forecast_ets = model_ets.forecast(30)

# Сбор прогнозов
prophet_pred = forecast_prophet[forecast_prophet['ds'] == test_date]['yhat'].values[0]
arima_pred = forecast_arima.iloc[-1]
ets_pred = forecast_ets.iloc[-1]

# Сравнение результатов
results = pd.DataFrame({
    'Метод': ['Prophet', 'ARIMA', 'ETS'],
    'Прогноз': [prophet_pred, arima_pred, ets_pred],
    'Ошибка': [abs(p - actual_value) for p in [prophet_pred, arima_pred, ets_pred]]
})

# Визуализация
plt.figure(figsize=(12, 6))
plt.plot(df['Дата'], df['Курс'], 'ko-', label='Исторические данные')
plt.axvline(test_date, color='r', linestyle='--', label='Целевая дата')

# Получаем последнюю историческую точку
last_date = df['Дата'].iloc[-1]
last_value = df['Курс'].iloc[-1]

# Цвета для методов
colors = ['blue', 'green', 'purple']

# Рисуем линии прогнозов и точки
for i, (method, pred) in enumerate(zip(results['Метод'], results['Прогноз'])):
    # Линия от последней точки к прогнозу (теперь сплошная)
    plt.plot([last_date, test_date], [last_value, pred],
             '-', color=colors[i], alpha=0.7, linewidth=1)
    # Точка прогноза
    plt.plot(test_date, pred, 'o', markersize=10, color=colors[i],
             label=f'{method}: {abs(pred-actual_value):.2f}')

# Линия и точка реального значения (теперь сплошная)
plt.plot([last_date, test_date], [last_value, actual_value],
         'k-', alpha=0.7, linewidth=1)
plt.plot(test_date, actual_value, 's', color='black', markersize=10,
         label=f'Реальное значение: {actual_value}')

plt.title(f'Сравнение методов экстраполяции')
plt.xlabel('Дата')
plt.ylabel('Курс')
plt.legend()
plt.grid(True)
plt.xticks(rotation=45)
plt.tight_layout()
plt.show()
