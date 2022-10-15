#include <iostream>
#include <vector>
using namespace std;

class Matrix {
  unsigned numberOfRows = 0U,
           numberOfColomns = 0U;  // Количество строк и столбцов
  vector<vector<double>> numbers;  // Элементы матрицы

 public:
  Matrix(unsigned rowCount = 0U, unsigned colomnCount = 0U,
         double* numbers = nullptr)
      : numberOfRows(rowCount), numberOfColomns(colomnCount) {
    this->numbers.resize(numberOfRows);
    for (auto i = 0U; i < numberOfRows; ++i) {
      this->numbers[i].resize(numberOfColomns);
      if (numbers != nullptr)
        for (auto j = 0U; j < numberOfColomns; ++j)
          this->numbers[i][j] = numbers[i * numberOfColomns + j];
    }
  }

  // Ввод (инициализация) матрицы
  void initializeMatrix() {
    cout << "Введите размер матрицы (строки, столбцы):\n";
    cin >> numberOfRows >> numberOfColomns;

    cout << "Введите " << numberOfColomns * numberOfRows
         << " элемента(-ов) матрицы:\n";

    double* elements = new double[numberOfColomns * numberOfRows];
    for (auto i = 0U; i < numberOfRows; ++i)
      for (auto j = 0U; j < numberOfColomns; ++j)
        cin >> elements[i * numberOfColomns + j];

    Matrix temp(numberOfRows, numberOfColomns, elements);
    delete[] elements;
    *this = temp;
  }

  // Сложение матриц
  Matrix operator+(const Matrix& matrix) {
    // Две матрицы должны иметь равное количество добавляемых строк и столбцов
    if (numberOfRows != matrix.numberOfRows ||
        numberOfColomns != matrix.numberOfColomns)
      throw runtime_error("Matrices have different sizes!");

    // Сумма двух матриц A и B представляет собой матрицу с тем же количеством
    // строк и столбцов, что и A и B
    Matrix temp(numberOfRows, numberOfColomns);

    for (auto i = 0U; i < numberOfRows; ++i)
      for (auto j = 0U; j < numberOfColomns; ++j)
        // Поэлементное сложение
        temp.numbers[i][j] = numbers[i][j] + matrix.numbers[i][j];

    return temp;
  }

  // Умножение матрицы на число
  Matrix operator*(double number) {
    Matrix temp(numberOfRows, numberOfColomns);

    for (auto i = 0U; i < numberOfRows; ++i)
      for (auto j = 0U; j < numberOfColomns; ++j)
        temp.numbers[i][j] = this->numbers[i][j] * number;

    return temp;
  }

  // Перемножение матриц
  Matrix operator*(const Matrix& matrix) {
    // Число столбцов матрицы A должно быть равно числу строк B
    if (numberOfColomns != matrix.numberOfRows)
      throw runtime_error(
          "The number of columns of matrix A must be equal to the number of "
          "rows of matrix B!");

    Matrix temp(numberOfRows, matrix.numberOfColomns);  // Произведение матриц

    for (auto i = 0U; i < numberOfRows; ++i) {
      for (auto j = 0U; j < matrix.numberOfColomns; ++j) {
        auto sum = 0.0;
        for (auto k = 0U; k < matrix.numberOfRows; ++k) {
          // Скалярные произведения строк матрицы A и столбцов матрицы B
          sum += numbers[i][k] * matrix.numbers[k][j];
        }
        temp.numbers[i][j] = sum;
      }
    }
    return temp;
  }

  // Операция траспонирования матрицы
  void transpose() {
    Matrix temp(numberOfColomns, numberOfRows);

    for (auto i = 0U; i < numberOfRows; ++i)
      for (auto j = 0U; j < numberOfColomns; ++j)
        // Получение транспонированной матрицы путем замены строк на столбцы
        temp.numbers[j][i] = numbers[i][j];

    numbers = temp.numbers;
    //Количество строк и столбцов меняются местами
    swap(numberOfColomns, numberOfRows);
  }

  // Вывод матрицы на экран
  void printMatrix() {
    cout << '\n';
    for (auto i = 0U; i < numberOfRows; ++i) {
      for (auto j = 0U; j < numberOfColomns; ++j) {
        cout << numbers[i][j] << ' ';
      }
      cout << '\n';
    }
    cout << '\n';
  }

  ~Matrix() {}
};

enum Choise {
  CHOISE_AMOUNT = 1,
  CHOISE_MULTIPLY_A,
  CHOISE_MULTIPLY_B,
  CHOISE_MULTIPLY_A_ON_NUMBER,
  CHOISE_MULTIPLY_B_ON_NUMBER,
  CHOISE_TRANSPOSE_A,
  CHOISE_TRANSPOSE_B
};

int main() {
  setlocale(LC_ALL, "russian");
  Matrix a, b, c;

  a.initializeMatrix();
  cout << "Матрица A:\n";
  a.printMatrix();

  b.initializeMatrix();
  cout << "Матрица B:\n";
  b.printMatrix();

  int choise, number;
  do {
    cout << "Введите действие:\n1. Сумма А + В;\n2. Произведение А * В;\n"
            "3. Произведение В * А;\n4. Произведение А * число;\n"
            "5. Произведение B * число;\n6. Траспонирование А.\n"
            "7. Траспонирование B.\n";
    cin >> choise;
    switch (choise) {
      case CHOISE_AMOUNT:
        try {
          c = a + b;
        } catch (...) {
          cout << "\nКоличество столбцов матрицы А должно быть равно "
                  "количеству строк матрицы В!\n";
          return EXIT_FAILURE;
        }
        break;
      case CHOISE_MULTIPLY_A:
        try {
          c = a * b;
        } catch (...) {
          cout << "\nМатрицы имеют разные размеры!\n";
          return EXIT_FAILURE;
        }
        break;
      case CHOISE_MULTIPLY_B:
        try {
          c = b * a;
        } catch (...) {
          cout << "\nМатрицы имеют разные размеры!\n";
          return EXIT_FAILURE;
        }
        break;
      case CHOISE_MULTIPLY_A_ON_NUMBER:
        cout << "Введите число: ";
        cin >> number;
        c = a * number;
        break;
      case CHOISE_MULTIPLY_B_ON_NUMBER:
        cout << "Введите число: ";
        cin >> number;
        c = b * number;
        break;
      case CHOISE_TRANSPOSE_A:
        c = a;
        c.transpose();
        break;
      case CHOISE_TRANSPOSE_B:
        c = b;
        c.transpose();
        break;
      default:
        return EXIT_SUCCESS;
    }
    c.printMatrix();
  } while (true);
}
