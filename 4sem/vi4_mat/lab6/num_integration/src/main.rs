fn main() {
    let a = 0.0;
    let b = 10.0;
    let n = 100; // Начальное число шагов (можно оптимизировать)
    let h = (b - a) / n as f64;

    // Интегрируемая функция
    let f = |x: f64| (3.0 * x.powi(3) + 2.0 * x.powi(2) - 5.0 * x + 1.0) / (x.sqrt() + 1.0);

    // Метод левых прямоугольников (первый порядок)
    let left_rect = (0..n).fold(0.0, |acc, i| {
        let x = a + i as f64 * h;
        acc + f(x) * h
    });

    // Метод трапеций (второй порядок)
    let trapezoid = (0..n).fold(0.0, |acc, i| {
        let x1 = a + i as f64 * h;
        let x2 = a + (i + 1) as f64 * h;
        acc + (f(x1) + f(x2)) * h / 2.0
    });

    // Метод Симпсона (четвертый порядок, требует чётное n)
    let simpson = (0..n / 2).fold(0.0, |acc, i| {
        let x0 = a + 2.0 * i as f64 * h;
        let x1 = x0 + h;
        let x2 = x0 + 2.0 * h;
        acc + (f(x0) + 4.0 * f(x1) + f(x2)) * h / 3.0
    });

    println!("Метод левых прямоугольников: {}", left_rect);
    println!("Метод трапеций: {}", trapezoid);
    println!("Метод Симпсона: {}", simpson);
}
