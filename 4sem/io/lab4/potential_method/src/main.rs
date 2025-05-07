use std::collections::{HashMap, HashSet, VecDeque};
use std::i32;

const INF: i32 = i32::MAX;

#[derive(Clone, Copy, Debug)]
struct Cell {
    i: usize,
    j: usize,
}

fn find_cycle(basis: &[Cell], entering_cell: Cell) -> Vec<Cell> {
    let mut graph: HashMap<String, Vec<String>> = HashMap::new();
    let mut parent: HashMap<String, String> = HashMap::new();
    let mut visited: HashSet<String> = HashSet::new();

    // Строим граф
    for &cell in basis {
        let row = format!("r{}", cell.i);
        let col = format!("c{}", cell.j);
        graph
            .entry(row.clone())
            .or_insert_with(Vec::new)
            .push(col.clone());
        graph.entry(col).or_insert_with(Vec::new).push(row);
    }

    // Добавляем входящую ячейку
    let start_row = format!("r{}", entering_cell.i);
    let start_col = format!("c{}", entering_cell.j);
    graph
        .entry(start_row.clone())
        .or_insert_with(Vec::new)
        .push(start_col.clone());
    graph
        .entry(start_col)
        .or_insert_with(Vec::new)
        .push(start_row.clone());

    // Ищем цикл
    let mut stack = VecDeque::new();
    stack.push_back((start_row.clone(), String::new()));
    let mut cycle = Vec::new();

    while let Some((node, prev)) = stack.pop_front() {
        if visited.contains(&node) {
            // Нашли цикл
            let mut current = node.clone();
            while !current.is_empty() {
                cycle.push(current.clone());
                current = parent[&current].clone();
            }
            cycle.reverse();
            break;
        }

        visited.insert(node.clone());
        parent.insert(node.clone(), prev.clone());

        if let Some(neighbors) = graph.get(&node) {
            for neighbor in neighbors {
                if neighbor != &prev {
                    stack.push_back((neighbor.clone(), node.clone()));
                }
            }
        }
    }

    // Преобразуем в координаты ячеек
    let mut cycle_coords = Vec::new();
    for i in 0..cycle.len() {
        if cycle[i].starts_with('r') {
            if i + 1 < cycle.len() {
                let row_str = &cycle[i][1..];
                let col_str = &cycle[i + 1][1..];
                let row: usize = row_str.parse().unwrap();
                let col: usize = col_str.parse().unwrap();
                cycle_coords.push(Cell { i: row, j: col });
            }
        }
    }

    cycle_coords
}

fn solve_potentials_method(a: Vec<i32>, b: Vec<i32>, c: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    let m = a.len();
    let n = b.len();
    let mut x = vec![vec![0; n]; m];
    let mut remaining_a = a.clone();
    let mut remaining_b = b.clone();

    // Построение начального допустимого плана минимальной стоимости
    loop {
        let mut has_remaining = false;
        for &val in &remaining_a {
            if val > 0 {
                has_remaining = true;
                break;
            }
        }
        if !has_remaining {
            break;
        }

        let mut min_cost = INF;
        let mut min_cell = Cell {
            i: usize::MAX,
            j: usize::MAX,
        };

        for i in 0..m {
            for j in 0..n {
                if remaining_a[i] > 0 && remaining_b[j] > 0 && c[i][j] < min_cost {
                    min_cost = c[i][j];
                    min_cell = Cell { i, j };
                }
            }
        }

        if min_cell.i == usize::MAX {
            break;
        }

        let amount = remaining_a[min_cell.i].min(remaining_b[min_cell.j]);
        x[min_cell.i][min_cell.j] = amount;
        remaining_a[min_cell.i] -= amount;
        remaining_b[min_cell.j] -= amount;
    }

    // Метод потенциалов
    let mut iteration = 0;
    const MAX_ITERATIONS: i32 = 100;

    while iteration < MAX_ITERATIONS {
        iteration += 1;
        let mut u = vec![0; m];
        let mut v = vec![0; n];
        let mut basis = Vec::new();

        // Собираем базисные клетки
        for i in 0..m {
            for j in 0..n {
                if x[i][j] > 0 {
                    basis.push(Cell { i, j });
                }
            }
        }

        // Вычисляем потенциалы
        let mut changed;
        loop {
            changed = false;
            for &cell in &basis {
                if u[cell.i] != 0 && v[cell.j] == 0 {
                    v[cell.j] = c[cell.i][cell.j] - u[cell.i];
                    changed = true;
                } else if v[cell.j] != 0 && u[cell.i] == 0 {
                    u[cell.i] = c[cell.i][cell.j] - v[cell.j];
                    changed = true;
                }
            }
            if !changed {
                break;
            }
        }

        // Проверка оптимальности
        let mut optimal = true;
        let mut entering_cell = Cell {
            i: usize::MAX,
            j: usize::MAX,
        };
        let mut min_delta = 0;

        for i in 0..m {
            for j in 0..n {
                if x[i][j] == 0 {
                    let delta = c[i][j] - (u[i] + v[j]);
                    if delta < min_delta {
                        min_delta = delta;
                        optimal = false;
                        entering_cell = Cell { i, j };
                    }
                }
            }
        }

        if optimal {
            break;
        }

        // Находим цикл
        let cycle = find_cycle(&basis, entering_cell);

        // Находим минимальное ограничение в цикле
        let mut theta = INF;
        for i in (1..cycle.len()).step_by(2) {
            theta = theta.min(x[cycle[i].i][cycle[i].j]);
        }

        // Обновляем план
        for i in 0..cycle.len() {
            let row = cycle[i].i;
            let col = cycle[i].j;
            if i % 2 == 0 {
                x[row][col] += theta;
            } else {
                x[row][col] -= theta;
            }
        }
    }

    x
}

fn main() {
    let a = vec![23, 24, 21, 15];
    let b = vec![19, 16, 16, 16, 16];
    let c = vec![
        vec![8, 28, 17, 19, 11],
        vec![27, 5, 10, 6, 19],
        vec![29, 11, 3, 7, 8],
        vec![25, 16, 19, 24, 13],
    ];

    let solution = solve_potentials_method(a, b, c.clone());

    // Вычисляем общую стоимость
    let total_cost: i32 = solution
        .iter()
        .enumerate()
        .map(|(i, row)| {
            row.iter()
                .enumerate()
                .map(|(j, &val)| val * c[i][j])
                .sum::<i32>()
        })
        .sum();

    println!(
        "Минимальная стоимость перевозки потенциальным методом: {}",
        total_cost
    );
}
