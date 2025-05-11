use std::f64::EPSILON as EPS;

// Функция для проверки наличия седловой точки в матрице
fn check_saddle_point(payoff_matrix: &[Vec<i32>]) -> bool {
    let mut a = Vec::new(); // массив минимальных значений строк (игрок 2)
    let mut b = Vec::new(); // массив максимальных значений столбцов (игрок 1)

    // Заполняем массив a (минимальные значения строк)
    for row in payoff_matrix {
        a.push(*row.iter().min().unwrap());
    }

    // Заполняем массив b (максимальные значения столбцов)
    for j in 0..payoff_matrix[0].len() {
        let mut max_val = payoff_matrix[0][j];
        for row in payoff_matrix.iter().skip(1) {
            if row[j] > max_val {
                max_val = row[j];
            }
        }
        b.push(max_val);
    }

    let a_max = *a.iter().max().unwrap(); // нижняя цена игры
    let b_min = *b.iter().min().unwrap(); // верхняя цена игры

    println!("\nАнализ седловой точки:");
    println!("----------------------");
    println!("Нижняя цена игры: {}", a_max);
    println!("Верхняя цена игры: {}", b_min);

    // Проверяем наличие седловой точки
    if a_max == b_min {
        let row = a.iter().position(|&x| x == a_max).unwrap() + 1;
        let col = b.iter().position(|&x| x == b_min).unwrap() + 1;
        println!("\nНайдена седловая точка в позиции ({}, {})", row, col);
        println!("Цена игры (v): {}", a_max);
        true
    } else {
        println!("\nСедловая точка не найдена, игра требует смешанных стратегий");
        false
    }
}

// Структура для реализации симплекс-метода
struct Simplex {
    table: Vec<Vec<f64>>,
    m: usize,
    n: usize,
}

impl Simplex {
    fn new(a: &[Vec<f64>], b: &[f64], c: &[f64]) -> Self {
        let m = b.len();
        let n = c.len();
        let mut table = vec![vec![0.0; n + m + 1]; m + 1];

        for j in 0..n {
            table[0][j] = -c[j];
        }

        for i in 0..m {
            for j in 0..n {
                table[i + 1][j] = a[i][j];
            }
            table[i + 1][n + i] = 1.0;
            table[i + 1][n + m] = b[i];
        }

        Simplex { table, m, n }
    }

    fn pivot(&mut self, p: usize, q: usize) {
        for i in 0..=self.m {
            for j in 0..=self.n + self.m {
                if i != p && j != q {
                    self.table[i][j] -= self.table[p][j] * self.table[i][q] / self.table[p][q];
                }
            }
        }

        for i in 0..=self.m {
            if i != p {
                self.table[i][q] = 0.0;
            }
        }

        for j in 0..=self.n + self.m {
            if j != q {
                self.table[p][j] /= self.table[p][q];
            }
        }
        self.table[p][q] = 1.0;
    }

    fn solve(&mut self, x: &mut Vec<f64>) -> bool {
        loop {
            let mut q = 0;
            for j in 1..self.n + self.m {
                if self.table[0][j] < self.table[0][q] {
                    q = j;
                }
            }
            if self.table[0][q] >= -EPS {
                break;
            }

            let mut p = None;
            let mut min_ratio = f64::MAX;
            for i in 1..=self.m {
                if self.table[i][q] > EPS {
                    let ratio = self.table[i][self.n + self.m] / self.table[i][q];
                    if ratio < min_ratio {
                        min_ratio = ratio;
                        p = Some(i);
                    }
                }
            }
            let p = match p {
                Some(p) => p,
                None => return false,
            };

            self.pivot(p, q);
        }

        x.resize(self.n, 0.0);
        for j in 0..self.n {
            let mut basic = false;
            let mut p = None;
            for i in 1..=self.m {
                if (self.table[i][j] - 1.0).abs() < EPS {
                    if p.is_none() {
                        p = Some(i);
                        basic = true;
                    } else {
                        basic = false;
                        break;
                    }
                } else if self.table[i][j].abs() > EPS {
                    basic = false;
                    break;
                }
            }
            if basic && p.is_some() {
                x[j] = self.table[p.unwrap()][self.n + self.m];
            }
        }

        true
    }

    fn get_objective(&self) -> f64 {
        self.table[0][self.n + self.m]
    }
}

// Функция для вывода стратегии
fn print_strategy(strategy: &[f64], player_name: &str) {
    println!("\nОптимальная стратегия для {}:", player_name);
    for (i, &val) in strategy.iter().enumerate() {
        print!(" p{} = {:.4}", i + 1, val);
        if i % 3 == 2 || i == strategy.len() - 1 {
            println!();
        } else {
            print!(" |");
        }
    }
}

// Решение для игрока 1 (максимизация выигрыша)
fn solve_player_1(matrix: &[Vec<i32>]) {
    let rows = matrix.len();
    let cols = matrix[0].len();

    let mut a = vec![vec![0.0; rows + 1]; cols];
    let mut b = vec![0.0; cols];
    let mut c = vec![0.0; rows + 1];
    c[rows] = 1.0;

    for j in 0..cols {
        for i in 0..rows {
            a[j][i] = -(matrix[i][j] as f64);
        }
        a[j][rows] = 1.0;
    }

    let mut eq_row = vec![0.0; rows + 1];
    for i in 0..rows {
        eq_row[i] = 1.0;
    }
    a.push(eq_row);
    b.push(1.0);

    let mut simplex = Simplex::new(&a, &b, &c);
    let mut solution = Vec::new();
    if !simplex.solve(&mut solution) {
        eprintln!("Ошибка решения для Игрока 1");
        return;
    }

    let v = simplex.get_objective();
    let x = solution[..rows].to_vec();

    println!("\nРезультаты для Игрока 1 (максимизация):");
    println!("--------------------------------------");
    println!("Цена игры: {:.4}", v);
    print_strategy(&x, "Игрока 1 (x)");
    println!();
}

// Решение для игрока 2 (минимизация проигрыша)
fn solve_player_2(matrix: &[Vec<i32>]) {
    let rows = matrix.len();
    let cols = matrix[0].len();

    let mut a = vec![vec![0.0; cols + 1]; rows];
    let mut b = vec![0.0; rows];
    let mut c = vec![0.0; cols + 1];
    c[cols] = 1.0;

    for i in 0..rows {
        for j in 0..cols {
            a[i][j] = matrix[i][j] as f64;
        }
        a[i][cols] = -1.0;
    }

    let mut eq_row = vec![0.0; cols + 1];
    for j in 0..cols {
        eq_row[j] = 1.0;
    }
    a.push(eq_row);
    b.push(1.0);

    let mut simplex = Simplex::new(&a, &b, &c);
    let mut solution = Vec::new();
    if !simplex.solve(&mut solution) {
        eprintln!("Ошибка решения для Игрока 2");
        return;
    }

    let v = simplex.get_objective();
    let y = solution[..cols].to_vec();

    println!("\nРезультаты для Игрока 2 (минимизация):");
    println!("--------------------------------------");
    println!("Цена игры: {:.4}", v);
    print_strategy(&y, "Игрока 2 (y)");
    println!();
}

fn main() {
    let payoff_matrix = vec![
        vec![10, 7],
        vec![6, 5],
        vec![21, 8],
        vec![3, 4],
        vec![18, 13],
    ];

    println!("Платежная матрица игры:");
    println!("-----------------------");
    for row in &payoff_matrix {
        for val in row {
            print!("{:4}", val);
        }
        println!();
    }

    if !check_saddle_point(&payoff_matrix) {
        solve_player_1(&payoff_matrix);
        solve_player_2(&payoff_matrix);
    }
}
