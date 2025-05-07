import pandas as pd
import numpy as np
from scipy import stats
import matplotlib.pyplot as plt
import seaborn as sns

# Замените на точное имя файла, если отличается
file_path = 'covid.csv'
data = pd.read_csv(file_path)

# Подготовка данных
data['DateTime'] = pd.to_datetime(data['DateTime'])
data = data.rename(columns={'Заражений за день': 'Cases'})
data['Year'] = data['DateTime'].dt.year
data['Month'] = data['DateTime'].dt.month

# Фильтрация по август-сентябрь-октябрь 2020
filtered_data = data[(data['Year'] == 2021) & (data['Month'].isin([4, 5, 6]))].copy()
filtered_data['Days'] = (filtered_data['DateTime'] - filtered_data['DateTime'].min()).dt.days

# Удаление нулей перед логарифмом
filtered_data['Cases'].replace(0, np.nan, inplace=True)
filtered_data.dropna(subset=['Cases'], inplace=True)
filtered_data['Log_Cases'] = np.log(filtered_data['Cases'])

# Проверка линейной зависимости
x = filtered_data['Days']
y = filtered_data['Log_Cases']
r, p_value = stats.pearsonr(x, y)

print(f"Коэффициент корреляции: {r}")
print(f"P-значение: {p_value}")
alpha = 0.05
if p_value < alpha:
    print("Гипотеза об экспоненциальном росте подтверждается.")
else:
    print("Гипотеза об экспоненциальном росте не подтверждается.")

# МНК и остатки
slope = np.sum((x - x.mean()) * (y - y.mean())) / np.sum((x - x.mean()) ** 2)
intercept = y.mean() - slope * x.mean()
filtered_data['Predicted_Log_Cases'] = intercept + slope * x
filtered_data['Residuals'] = y - filtered_data['Predicted_Log_Cases']

# Проверка нормальности остатков
sigma = np.std(filtered_data['Residuals'], ddof=1)
num_bins = 5
observed_frequencies, bin_edges = np.histogram(filtered_data['Residuals'], bins=num_bins)

expected_probabilities = []
for i in range(num_bins):
    lower = bin_edges[i]
    upper = bin_edges[i + 1]
    prob = stats.norm.cdf(upper, loc=0, scale=sigma) - stats.norm.cdf(lower, loc=0, scale=sigma)
    expected_probabilities.append(prob)

expected_frequencies = np.array(expected_probabilities) * len(filtered_data['Residuals'])
expected_frequencies *= (sum(observed_frequencies) / sum(expected_frequencies))

K, _ = stats.chisquare(observed_frequencies, f_exp=expected_frequencies)
K_T = stats.chi2.ppf(1 - alpha, num_bins - 1)

print(f"Статистика хи-квадрат (K): {K}")
print(f"Критическое значение (K_T): {K_T}")
if K > K_T:
    print("Остатки не распределены нормально с нулевым математическим ожиданием.")
else:
    print("Остатки распределены нормально с нулевым математическим ожиданием.")

# Визуализация
plt.figure(figsize=(10, 5))
sns.scatterplot(x=x, y=y, label="Логарифм случаев")
plt.plot(x, intercept + slope * x, color='red', label="Линейная аппроксимация")
plt.xlabel("Дни с начала периода")
plt.ylabel("Логарифм случаев")
plt.legend()
plt.title("Проверка экспоненциального роста")
plt.show()