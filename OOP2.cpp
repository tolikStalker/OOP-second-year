#include <cmath>
#include <iostream>
using std::cin;
using std::cout;

class Function {
 protected:
  double x = 0., a = 0., b = 0.;

 public:
  Function(double a, double b) : a(a), b(b) {}
  // Функция вычисления значения функции
  virtual double calculateFunction() = 0;
  // Функция вывода значения функции
  virtual void print() = 0;
  // Функция, устанавливающая новое значение х
  void setX(double xVar) { x = xVar; }
  virtual ~Function() {}
};

// Производный класс эллипса
class Ellipse : public Function {
 public:
  Ellipse(double a, double b) : Function(a, b) {}

  double calculateFunction() override {
    if (a * a - x * x <= 0)
      throw std::runtime_error("Taking the root is impossible!");
    return sqrt(a * a - x * x) * b / a;
  }

  void print() override {
    try {
      cout << "Эллипс: ";
      double result = calculateFunction();
      cout << result << ' ' << -result << '\n';
    } catch (...) {
      cout << "невозможно взять корень!\n";
    }
  }
};

// Производный класс гиперболы
class Hiperbola : public Function {
 public:
  Hiperbola(double a, double b) : Function(a, b) {}

  double calculateFunction() override {
    if (x * x - a * a <= 0.)
      throw std::runtime_error("Taking the root is impossible!");
    return sqrt(x * x - a * a) * b / a;
  }

  void print() override {
    try {
      cout << "Гипербола: ";
      double result = calculateFunction();
      cout << result << '\n';
    } catch (...) {
      cout << "невозможно взять корень!\n";
    }
  }
};

// Производный класс параболы
class Parabola : public Function {
  double c;

 public:
  Parabola(double a, double b, double c) : Function(a, b), c(c) {}

  double calculateFunction() override { return a * x * x + b * x + c; }

  void print() override { cout << "Парабола: " << calculateFunction() << '\n'; }
};

// Класс, реализующий вывод уравнений для заданных параметров
class Series {
  Function** func = nullptr;
  int curSize = 0, maxSize = 0;

 public:
  double step = 0.5;

  Series(double step = 0.5) : step(step) {}

  // Устанавить максимальный размер массива
  void setMaxSize(int size) {
    maxSize = size;
    func = new Function*[maxSize];
  }

  // Добавить производную функцию в массив абстрактного класса
  void addFunction(Function* f) {
    if (curSize < maxSize)
      func[curSize++] = f;
    else
      throw std::runtime_error("Exceeded the maximum size of the array");
  }

  // Функция для всех производных классов в массиве устанавливает новое значение
  // х и выводит на экран значения функций
  void setFunctions(double& x) {
    for (int i = 0; i < curSize; ++i) {
      func[i]->setX(x);
      func[i]->print();
    }
  }

  ~Series() {
    for (int i = 0; i < curSize; i++) delete[] func[i];
    delete[] func;
  }
};

int main() {
  setlocale(LC_ALL, "russian");
  double a, b, c, x1, x2 = 0.;
  cout << "Введите a, b, c: ";
  cin >> a >> b >> c;
  Series ser;
  ser.setMaxSize(3);  // Установка максимального количество функций
  try {
    // Добавления функций в Series
    ser.addFunction(new Ellipse(a, b));
    ser.addFunction(new Hiperbola(a, b));
    ser.addFunction(new Parabola(a, b, c));
  } catch (...) {
    cout << "\nПревышен максимальный размер массива!\n";
    return 0;
  }

  do {
    cout << "\nВведите х: ";
    cin >> x1;
    double step = ser.step;
    // Если следующий х меньше предыдущего, то шаг цикла отрицательный
    if (x2 > x1) step *= -1.;
    for (auto i = x2;
         abs(x1 + step - i) > std::numeric_limits<double>::epsilon();
         i += step) {
      cout << "Текущее значение х: " << i << '\n';
      ser.setFunctions(i);
    }
    x2 = x1;
  } while (true);
}