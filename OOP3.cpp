#define _USE_MATH_DEFINES
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;

// Структура точки
struct Point {
  double x = 0., y = 0.;  // Координаты точки

  Point& operator+=(const Point& pt) {
    x += pt.x, y += pt.y;
    return *this;
  }
  Point& operator-=(const Point& pt) {
    x -= pt.x, y -= pt.y;
    return *this;
  }
  Point operator+(const Point& pt) const {
    Point temp(*this);
    temp += pt;
    return temp;
  }
  Point operator-(const Point& pt) const {
    Point temp(*this);
    temp -= pt;
    return temp;
  }
};

// Класс фигуры
class Shape {
 protected:
  // Координаты вершин фигуры
  Point* vertices_ = nullptr;
  // Количество вершин фигуры
  const unsigned vertices_number_ = 0U;
  // Радиус области вращения
  double radius_ = 0.;

 public:
  // ID фигуры
  string id;

  explicit Shape(const unsigned verticesNumber)
      : vertices_number_(verticesNumber) {}
  // Метод, вычисляющий площадь фигуры
  virtual double calcSquare() = 0;
  // Метод, вычисляющий центр тяжести фигуры
  virtual Point calcGravityCenter() = 0;
  // Метод, осуществляющий вращение фигуры на заданный угол по часовой стрелке
  // относительно центра тяжести
  virtual void rotate(double) = 0;
  // Метод, осуществляющий перемещение фигуры на заданное смещение
  virtual void move(Point&) = 0;

  // Метод для получения количества вершин фигуры
  [[nodiscard]] unsigned getVerticesCount() const { return vertices_number_; }

  // Установить вершину по заданному номеру
  void setVertex(const unsigned& index, const Point& newPoint) const {
    if (index > vertices_number_) throw "The point index is too large";
    vertices_[index] = newPoint;
  }

  // Метод, выводящий информацию о фигуре на экран
  void printShape() {
    cout << '\n' << id << "\nТочки:";
    for (unsigned i = 0U; i < vertices_number_; ++i)
      cout << "\nx" << i << ": " << vertices_[i].x << " y" << i << ": "
           << vertices_[i].y;
    const auto [x, y] = calcGravityCenter();
    cout << "\nПлощадь: " << calcSquare() << "\nЦентр в точке: " << x << ' '
         << y << "\n\n";
  }

  // Метод, вычисляющий радиус области вращения
  virtual double getShapeRadius() = 0;
  // Проверка на корректность ввода
  virtual bool isCorrectInput() = 0;
  virtual ~Shape() = default;
};

// Производный класс квадрата
class Square : public Shape {
 public:
  Square() : Shape(4) {
    this->vertices_ = new Point[vertices_number_];
    id = "Square";
  }

  double calcSquare() override {
    return pow(
        hypot(vertices_[1].x - vertices_[0].x, vertices_[1].y - vertices_[0].y),
        2);
  }

  Point calcGravityCenter() override {
    // Центр высчитывается как среднее арифметическое между всеми вершинами
    return {
        (vertices_[0].x + vertices_[1].x + vertices_[2].x + vertices_[3].x) /
            vertices_number_,
        (vertices_[0].y + vertices_[1].y + vertices_[2].y + vertices_[3].y) /
            vertices_number_};
  }

  void rotate(double angle) override {
    angle *= M_PI / 180.;
    const auto [x, y] = calcGravityCenter();
    for (unsigned i = 0U; i < vertices_number_; ++i) {
      const Point temp{vertices_[i].x - x, vertices_[i].y - y};
      const double cosin =
          std::numeric_limits<double>::epsilon() > cos(angle) ? 0. : cos(angle);
      const double sinus =
          std::numeric_limits<double>::epsilon() > sin(angle) ? 0. : sin(angle);
      vertices_[i] = {temp.x * cosin - temp.y * sinus + x,
                      temp.x * sinus + temp.y * cosin + y};
    }
  }

  void move(Point& offset) override {
    for (unsigned i = 0U; i < vertices_number_; ++i) vertices_[i] += offset;
  }

  bool isCorrectInput() override {
    // Проверка на равенство всех сторон
    if (hypot(vertices_[1].x - vertices_[0].x,
              vertices_[1].y - vertices_[0].y) ==
            hypot(vertices_[2].x - vertices_[1].x,
                  vertices_[2].y - vertices_[1].y) &&
        hypot(vertices_[3].x - vertices_[2].x,
              vertices_[3].y - vertices_[2].y) ==
            hypot(vertices_[2].x - vertices_[1].x,
                  vertices_[2].y - vertices_[1].y) &&
        hypot(vertices_[1].x - vertices_[0].x,
              vertices_[1].y - vertices_[0].y) ==
            hypot(vertices_[3].x - vertices_[0].x,
                  vertices_[3].y - vertices_[0].y))
      return true;
    return false;
  }

  double getShapeRadius() override {
    const auto [x, y] = calcGravityCenter();
    return hypot(vertices_[0].x - x, vertices_[0].y - y);
  }

  ~Square() override { delete[] vertices_; }
};

// Производный класс параллелограмма
class Parallelogram : public Shape {
 public:
  Parallelogram() : Shape(4) {
    vertices_ = new Point[vertices_number_];
    id = "Parallelogram";
  }

  double calcSquare() override {
    const Point ab = {vertices_[0].x - vertices_[1].x,
                      vertices_[0].y - vertices_[1].y};
    const Point cb = {vertices_[0].x - vertices_[3].x,
                      vertices_[0].y - vertices_[3].y};

    const double dot = ab.x * cb.x + ab.y * cb.y;
    const double cross = ab.x * cb.y - ab.y * cb.x;

    const double angle = atan2(dot, cross);
    return hypot(vertices_[1].x - vertices_[0].x,
                 vertices_[1].y - vertices_[0].y) *
           hypot(vertices_[3].x - vertices_[0].x,
                 vertices_[3].y - vertices_[0].y) *
           sin(angle);
  }

  Point calcGravityCenter() override {
    // Центр высчитывается как среднее арифметическое между всеми вершинами
    return {
        (vertices_[0].x + vertices_[1].x + vertices_[2].x + vertices_[3].x) /
            vertices_number_,
        (vertices_[0].y + vertices_[1].y + vertices_[2].y + vertices_[3].y) /
            vertices_number_};
  }

  void rotate(const double angle) override {
    const auto [x, y] = calcGravityCenter();
    for (unsigned i = 0U; i < vertices_number_; ++i) {
      const Point temp{vertices_[i].x - x, vertices_[i].y - y};
      const double cosin =
          std::numeric_limits<double>::epsilon() > cos(angle) ? 0 : cos(angle);
      double sinus =
          std::numeric_limits<double>::epsilon() > sin(angle) ? 0 : sin(angle);
      vertices_[i] = {temp.x * cosin - temp.y * sinus + x,
                      temp.x * sinus + temp.y * cosin + y};
    }
  }

  void move(Point& offset) override {
    for (unsigned i = 0U; i < vertices_number_; ++i) vertices_[i] += offset;
  }

  bool isCorrectInput() override {
    // Проверка на равенство противоположных сторон
    if (hypot(vertices_[1].x - vertices_[0].x,
              vertices_[1].y - vertices_[0].y) ==
            hypot(vertices_[3].x - vertices_[2].x,
                  vertices_[3].y - vertices_[2].y) &&
        hypot(vertices_[3].x - vertices_[0].x,
              vertices_[3].y - vertices_[0].y) ==
            hypot(vertices_[2].x - vertices_[1].x,
                  vertices_[2].y - vertices_[1].y))
      return true;
    return false;
  }

  double getShapeRadius() override {
    auto [x, y] = calcGravityCenter();
    return std::max(hypot(vertices_[0].x - x, vertices_[0].y - y),
                    hypot(vertices_[1].x - x, vertices_[1].y - y));
  }

  ~Parallelogram() override { delete[] vertices_; }
};

// Структура фабрики, позволяющей динамически создавать объекты
struct FactoryShape {
  // Статический метод создания фигуры по первой букве ID
  static Shape* createShape(const char& ch) {
    switch (ch) {
      case 's':
      case 'S':
        return new Square();
      case 'p':
      case 'P':
        return new Parallelogram();
      default:
        return nullptr;
    }
  }
};

// Класс выполняемых операций
struct Operation {
  // Статический метод, проверяющий включение первой фигуры во вторую
  static bool isInclude(Shape*& first, Shape*& second) {
    const Point center1 = first->calcGravityCenter(),
                center2 = second->calcGravityCenter();
    const double radius1 = first->getShapeRadius(),
                 radius2 = second->getShapeRadius();
    if (radius1 < radius2 &&
        (center1.x - center2.x) * (center1.x - center2.x) +
                (center1.y - center2.y) * (center1.y - center2.y) <=
            radius2 * radius2 - 2 * radius1 * radius2 + radius1 * radius1)
      return true;
    return false;
  }
  // Статический метод, проверяющий пересечение первой и второй фигуры
  static bool isIntersect(Shape*& first, Shape*& second) {
    const double centerDistance =
        hypot(first->calcGravityCenter().x - second->calcGravityCenter().x,
              first->calcGravityCenter().y - second->calcGravityCenter().y);
    const double radius1 = first->getShapeRadius(),
                 radius2 = second->getShapeRadius();
    if (abs(radius1 - radius2) <= centerDistance &&
        centerDistance <= radius1 + radius2)
      return true;
    return false;
  }
  // Статический метод сравнения площадей двух фигур
  static double compare(Shape*& first, Shape*& second) {
    return first->calcSquare() / second->calcSquare();
  }
};

int main() {
  setlocale(LC_ALL, "russian");
  constexpr int figureCount = 2;
  Shape* shape[figureCount]{};
  char type;
  // Ввод двух фигур
  for (int j = 0; j < figureCount; ++j) {
    cout << "Введите тип фигуры: ";
    cin >> type;
    shape[j] = FactoryShape::createShape(type);
    if (shape[j] != nullptr) {
      cout << shape[j]->id << '\n';
      cout << "Введите " << shape[j]->getVerticesCount()
           << " вершины (x и y): ";
      for (unsigned i = 0U; i < shape[j]->getVerticesCount(); ++i) {
        Point entered;
        cin >> entered.x >> entered.y;
        shape[j]->setVertex(i, entered);
      }
      if (!shape[j]->isCorrectInput()) {
        cout << "\nФигура введена неверно!\n";
        --j;
      } else
        shape[j]->printShape();
    } else {
      cout << "Данной фигуры не существует!\n";
      --j;
    }
  }
  // Выбор операций над фигурами
  do {
    cout << std::setprecision(3) << std::fixed
         << "1. Повернуть фигуру;\n2. Подвинуть фигуру;\n"
            "3. Сравнить два объекта по площади;\n"
            "4. Определить факт пересечения объектов;\n"
            "5. определить факт включения одного объекта в другой.\n";
    int choice;
    cin >> choice;
    try {
      unsigned number = 0U;
      double angle, compRes;
      Point offset;
      switch (choice) {
        case 1:  // Поворот
          cout << "Номер фигуры: ";
          cin >> number;
          if (number - 1 > figureCount) throw "Shape does not exist!";
          cout << "Угол поворота: ";
          cin >> angle;
          shape[number - 1]->rotate(angle);
          shape[number - 1]->printShape();
          break;
        case 2:  // Подвинуть фигуру
          cout << "Номер фигуры: ";
          cin >> number;
          if (number - 1 > figureCount) throw "Shape does not exist!";
          cout << "Смещение по оси х и y: ";
          cin >> offset.x >> offset.y;
          shape[number - 1]->move(offset);
          shape[number - 1]->printShape();
          break;
        case 3:  // Сравнить площади
          compRes = Operation::compare(shape[0], shape[1]);
          if (compRes == 1)
            cout << "Площади равны.\n";
          else if (compRes > 1)
            cout << "Фигура 1 больше фигуры 2 в " << compRes << " раз(а)\n";
          else
            cout << "Фигура 2 больше фигуры 1 в " << 1 / compRes << " раз(а)\n";
          break;
        case 4:  // Проверить пересечение
          if (Operation::isIntersect(shape[0], shape[1]))
            cout << "Фигуры пересекаются.\n";
          else
            cout << "Фигуры не пересекаются.\n";
          break;
        case 5:  // Проверить включение
          if (Operation::isInclude(shape[0], shape[1]))
            cout << "Фигура 1 включается в фигуру 2.\n";
          else
            cout << "Фигура 1 не включается в фигуру 2.\n";
          if (Operation::isInclude(shape[1], shape[0]))
            cout << "Фигура 2 включается в фигуру 1.\n";
          else
            cout << "Фигура 2 не включается в фигуру 1.\n";
          break;
        default:
          break;
      }
      if (choice == -1) break;
    } catch (...) {
      cout << "Фигура не существует!";
      for (auto& i : shape) delete i;
      return 0;
    }
  } while (true);
  for (auto& i : shape) delete i;
}