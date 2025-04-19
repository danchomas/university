use std::f64;

fn is_zero(n: f64, eps: f64) -> bool {
    n.abs() < eps
}

fn inverse_matrix_2x2(matrix: [[f64; 2]; 2], epsilon: f64) -> Result<[[f64; 2]; 2], &'static str> {
    let det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    if is_zero(det, epsilon) {
        return Err("Матрица вырождена");
    }
    Ok([
        [matrix[1][1] / det, -matrix[0][1] / det],
        [-matrix[1][0] / det, matrix[0][0] / det],
    ])
}

fn matrix_vector_multiply(matrix: [[f64; 2]; 2], vector: [f64; 2]) -> [f64; 2] {
    [
        matrix[0][0] * vector[0] + matrix[0][1] * vector[1],
        matrix[1][0] * vector[0] + matrix[1][1] * vector[1],
    ]
}

fn f(x: [f64; 2]) -> [f64; 2] {
    [
        x[0].powi(2) + f64::sqrt(f64::exp(x[1])) - 6.0,
        f64::sin(x[0]) + f64::cosh(x[1]) - 2.0,
    ]
}

fn jacobian(x: [f64; 2]) -> [[f64; 2]; 2] {
    [
        [2.0 * x[0], 0.5 * f64::exp(x[1]) / f64::sqrt(f64::exp(x[1]))],
        [f64::cos(x[0]), f64::sinh(x[1])],
    ]
}

fn newton_method(
    initial_guess: [f64; 2],
    epsilon: f64,
    max_iterations: usize,
) -> Result<[f64; 2], &'static str> {
    let mut x = initial_guess;
    for iteration in 0..max_iterations {
        let j = jacobian(x);
        let inv_j = inverse_matrix_2x2(j, epsilon)?;
        let fx = f(x);
        let delta = matrix_vector_multiply(inv_j, [-fx[0], -fx[1]]);
        x = [x[0] + delta[0], x[1] + delta[1]];

        if delta[0].abs() < epsilon && delta[1].abs() < epsilon {
            println!("Метод Ньютона сошелся за {} итераций", iteration);
            return Ok(x);
        }
    }
    Err("Метод Ньютона не сошелся")
}

// простая итерация
fn simple_iteration_method(
    initial_guess: [f64; 2],
    epsilon: f64,
    max_iterations: usize,
) -> Result<[f64; 2], &'static str> {
    let mut x = initial_guess;
    for iteration in 0..max_iterations {
        let x_new = [
            f64::sqrt(6.0 - f64::sqrt(f64::exp(x[1]))),
            f64::acosh(2.0 - f64::sin(x[0])),
        ];

        if (x_new[0] - x[0]).abs() < epsilon && (x_new[1] - x[1]).abs() < epsilon {
            println!("Метод простой итерации сошелся за {} итераций", iteration);
            return Ok(x_new);
        }
        x = x_new;
    }
    Err("Метод простой итерации не сошелся")
}

// градиентный спуск
fn gradient_descent(
    initial_guess: [f64; 2],
    learning_rate: f64,
    epsilon: f64,
    max_iterations: usize,
) -> Result<[f64; 2], &'static str> {
    let mut x = initial_guess;
    for iteration in 0..max_iterations {
        let grad = gradient(x);
        x = [
            x[0] - learning_rate * grad[0],
            x[1] - learning_rate * grad[1],
        ];

        if grad[0].abs() < epsilon && grad[1].abs() < epsilon {
            println!(
                "Метод градиентного спуска сошелся за {} итераций",
                iteration
            );
            return Ok(x);
        }
    }
    Err("Метод градиентного спуска не сошелся")
}

fn gradient(x: [f64; 2]) -> [f64; 2] {
    let h = 1e-6;
    let mut grad = [0.0; 2];

    for i in 0..2 {
        let mut x_plus_h = x;
        let mut x_minus_h = x;
        x_plus_h[i] += h;
        x_minus_h[i] -= h;

        grad[i] = (objective_function(x_plus_h) - objective_function(x_minus_h)) / (2.0 * h);
    }
    grad
}

fn objective_function(x: [f64; 2]) -> f64 {
    let eq1 = x[0].powi(2) + f64::sqrt(f64::exp(x[1])) - 6.0;
    let eq2 = f64::sin(x[0]) + f64::cosh(x[1]) - 2.0;
    eq1.powi(2) + eq2.powi(2)
}

fn main() {
    let initial_guess = [1.0, 1.0];

    let epsilon = 1e-6; // точность
    let max_iterations = 1000; // макс итераций
    let learning_rate = 0.0501; // шаг

    match newton_method(initial_guess, epsilon, max_iterations) {
        Ok(solution) => println!("Метод Ньютона: x1 = {}, x2 = {}", solution[0], solution[1]),
        Err(e) => println!("Метод Ньютона: {}", e),
    }

    match simple_iteration_method(initial_guess, epsilon, max_iterations) {
        Ok(solution) => println!(
            "Метод простой итерации: x1 = {}, x2 = {}",
            solution[0], solution[1]
        ),
        Err(e) => println!("Метод простой итерации: {}", e),
    }

    match gradient_descent(initial_guess, learning_rate, epsilon, max_iterations) {
        Ok(solution) => println!(
            "Метод градиентного спуска: x1 = {}, x2 = {}",
            solution[0], solution[1]
        ),
        Err(e) => println!("Метод градиентного спуска: {}", e),
    }
}
