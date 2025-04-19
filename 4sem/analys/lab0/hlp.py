import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats

# Заданные значения
i, j, k = 2, 10, 7

# Вычисляем вероятности для дискретной случайной величины
denominator = 2 * (i + j + k)
p0 = i / denominator
p1 = (j + k) / denominator
p2 = (i + k) / denominator
p3 = j / denominator

# Генерация дискретной случайной величины
n_samples = 10000
samples_discrete = np.random.choice([0, 1, 2, 3], size=n_samples, p=[p0, p1, p2, p3])

# Подсчёт частот
unique, counts = np.unique(samples_discrete, return_counts=True)
frequencies = counts / n_samples

# Вывод результатов
print("Заданные вероятности:")
print(f"P(0) = {p0:.4f}, P(1) = {p1:.4f}, P(2) = {p2:.4f}, P(3) = {p3:.4f}")

print("\nСгенерированные частоты:")
for value, freq in zip(unique, frequencies):
    print(f"Частота {value}: {freq:.4f}")

# Проверка соответствия распределения (критерий хи-квадрат)
expected_counts = np.array([p0, p1, p2, p3]) * n_samples
observed_counts = np.zeros(4)
for value, count in zip(unique, counts):
    observed_counts[value] = count

# Вычисляем статистику хи-квадрат
chi2_stat = np.sum((observed_counts - expected_counts)**2 / expected_counts)

# Критическое значение для уровня значимости 0.05 и df=3 (4 категории - 1)
critical_value = stats.chi2.ppf(0.95, df=3)

# P-value
p_value = 1 - stats.chi2.cdf(chi2_stat, df=3)

print("\nПроверка соответствия распределению (критерий хи-квадрат):")
print(f"Наблюдаемые частоты: {observed_counts}")
print(f"Ожидаемые частоты: {expected_counts}")
print(f"Статистика хи-квадрат: {chi2_stat:.4f}")
print(f"Критическое значение (α=0.05): {critical_value:.4f}")
print(f"P-value: {p_value:.4f}")

if chi2_stat < critical_value:
    print("Гипотеза о соответствии распределению принимается (p > 0.05)")
else:
    print("Гипотеза о соответствии распределению отвергается (p ≤ 0.05)")

# Вторая часть: генерация экспоненциального распределения методом обратной функции
lambda_param = 14 / 4

# Генератор экспоненциального распределения (НЕ ИСПОЛЬЗУЕМ random.expovariate)
uniform_samples = np.random.uniform(0, 1, n_samples)
samples_exponential = -np.log(uniform_samples) / lambda_param

# Построение гистограммы
plt.hist(samples_exponential, bins=30, density=True, alpha=0.6, color='b', edgecolor='black')

# Теоретическая плотность распределения
x = np.linspace(0, np.max(samples_exponential), 1000)
plt.plot(x, lambda_param * np.exp(-lambda_param * x), 'r', label='Теоретическая плотность')
plt.title("Гистограмма и теоретическая плотность распределения")
plt.xlabel("Значение")
plt.ylabel("Плотность вероятности")
plt.legend()
plt.show()

# Среднее арифметическое
mean_sample = np.mean(samples_exponential)

# Проверка соответствия показательному распределению (К-С тест)
ks_stat, ks_p_value = stats.kstest(samples_exponential, 'expon', args=(0, 1/lambda_param))

# Вывод результатов
print("\nСреднее значение выборки:", mean_sample)
print("P-значение критерия Колмогорова-Смирнова:", ks_p_value)

if ks_p_value > 0.05:
    print("Гипотеза о соответствии экспоненциальному распределению принимается.")
else:
    print("Гипотеза о соответствии экспоненциальному распределению отвергается.")