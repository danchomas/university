use std::i32;

fn get_step(a: &mut Vec<i32>, b: &mut Vec<i32>, c: &mut Vec<Vec<i32>>) -> i32 {
    let mut min_el = c[0][0];
    let mut min_el_ind = (0, 0);

    // Находим минимальную стоимость перевозки
    for i in 0..a.len() {
        for j in 0..b.len() {
            if c[i][j] < min_el {
                min_el = c[i][j];
                min_el_ind = (i, j);
            }
        }
    }

    // Количество перевозимого груза
    let sum = a[min_el_ind.0].min(b[min_el_ind.1]);

    // Обновляем запас и потребность
    a[min_el_ind.0] -= sum;
    b[min_el_ind.1] -= sum;

    // Считаем стоимость
    let cost = sum * c[min_el_ind.0][min_el_ind.1];

    // Помечаем клетку как использованную
    c[min_el_ind.0][min_el_ind.1] = i32::MAX;

    cost
}

fn solve_distributive_method(mut a: Vec<i32>, mut b: Vec<i32>, mut c: Vec<Vec<i32>>) -> i32 {
    let mut total_sum = 0;

    // Вычисляем сумму всех потребностей
    let mut total_b: i32 = b.iter().sum();

    while total_b > 0 {
        total_sum += get_step(&mut a, &mut b, &mut c);
        total_b = b.iter().sum();
    }

    total_sum
}

fn main() {
    let a = vec![23, 24, 21, 15]; // Вектор запасов
    let b = vec![19, 16, 16, 16, 16]; // Вектор потребностей
    let c = vec![
        vec![8, 28, 17, 19, 11],
        vec![27, 5, 10, 6, 19],
        vec![29, 11, 3, 7, 8],
        vec![25, 16, 19, 24, 13],
    ]; // Матрица стоимостей
    let result = solve_distributive_method(a, b, c);
    println!(
        "Минимальная стоимость перевозки распределительным методом: {}",
        result
    );
}
