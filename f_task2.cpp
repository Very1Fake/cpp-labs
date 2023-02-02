// Полином вида: a0 + a1 ** x + a2 ** (x*2) + ... + a*k[n] ** (x * n)

#include <math.h>

#include <iostream>

using namespace std;

const size_t ITER_LIMIT = 10000;

// функция для решения данного полинома с заданным x
double solve_polynomial(double* coef_array, size_t degree, double x) {
    double temp = coef_array[0];

    for (size_t i = 1; i < degree; i++) {
        temp += coef_array[i] * pow(x, i);
    }

    return temp;
}

// проверка интервала на разность знаков двух чисел
// lhs - left-hand-side
// rhs - right-hand-side
bool sign_diff(double lhs, double rhs) { return lhs * rhs < 0.0; }

// функция для принта массива
void print_array(double* ref, size_t len) {
    for (size_t i = 0; i < len; i++) {
        cout << "Array [" << i << "] = " << ref[i] << "\n";
    }
}

int main() {
    // size_t - тип int с размером указателя (на пк с x64 архитектурой размер -
    // 64 бита (8 байт)). Нужен чтобы нормально работать с массивами.
    size_t degree, eps_input, iters = 0;
    double* coef_array;
    double a, b, eps;

    cout << "Enter polynomial function degree: ";
    cin >> degree;

    if (degree < 1) {
        cout << "Degree should be positive integer and > 1!";
        // код 1 означает что программа завершилась с ошибкой
        return 1;
    }

    // - malloc возвращает безымянный указатель (void*) и (double*) нужен чтобы
    //      привести его к нужному типу.
    // - sizeof(double) * degree - размер типа для коэффициентов на нужный
    //      размер (степень полинома)
    coef_array = (double*)malloc(sizeof(double) * degree);

    print_array(coef_array, degree);

    // спрашиваем у юзера коэффициенты
    for (size_t i = 0; i < degree; i++) {
        // BUG: Возможен выход за границы size_t
        cout << "Enter " << i + 1 << "th coefficient of polynomial function: ";
        cin >> coef_array[i];
    }

    print_array(coef_array, degree);

    cout << "Enter the start of the interval - a (should be less than the end "
            "of the interval - b): ";
    cin >> a;
    cout << "Enter the end of the interval - b (should be greater than the "
            "start of the interval - a): ";
    cin >> b;
    cout << "Enter precision - eps: ";
    cin >> eps_input;

    if (a > b) {
        cout << "a can't be greater than b!";
        return 1;
    }

    if (eps_input < 0) {
        cout << "Precision can't be less than 0";
        return 0;
    } else {
        // перевод из eps_input (кол-во чисел после запятой) в число для
        // множителя 1.0 / 10^eps_input
        // Пример: eps_input=3 -> eps=0.001
        eps = 1.0 / pow(10, eps_input);
        cout << "Precision: " << eps << endl;
    }

    // устанавливаем точность для принта float/double
    cout.precision(8);

    // Первичное сравнение знаков полинома на концах интервала
    if (sign_diff(solve_polynomial(coef_array, degree, a),
                  solve_polynomial(coef_array, degree, b))) {
        while (true) {
            if (iters > ITER_LIMIT) {
                cout
                    << "Root for polynomial was not found. Iter limit exceeded";
                break;
            }

            double xi = (a + b) / 2.0;

            // cout << "[" << a << ";" << b << "]"
            //      << "xi=" << xi
            //      << ";f(xi)=" << solve_polynomial(coef_array, degree, xi) <<
            //      "["
            //      << solve_polynomial(coef_array, degree, a) << ";"
            //      << solve_polynomial(coef_array, degree, b) << "]" << endl;

            // Проверка знаков полинома на a и xi
            if (sign_diff(solve_polynomial(coef_array, degree, a),
                          solve_polynomial(coef_array, degree, xi))) {
                // если знаки отличаются, то сдвигаем справа
                b = xi;
            } else {
                // если нет, то слева
                a = xi;
            }

            // проверяем точность
            if (abs(a - b) < eps) {
                cout << "Root for given polynomial: x=" << xi << endl
                     << "f(x)=" << solve_polynomial(coef_array, degree, xi);
                break;
            }

            iters++;
        }
    } else {
        cout << "Root for polynomial was not found. Interval signs are equal";
    }

    return 0;
}
