#define _USE_MATH_DEFINES
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;

// ��������� �����
struct Point {
  double x = 0., y = 0.;  // ���������� �����

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

// ����� ������
class Shape {
 protected:
  // ���������� ������ ������
  Point* vertices_ = nullptr;
  // ���������� ������ ������
  const unsigned vertices_number_ = 0U;
  // ������ ������� ��������
  double radius_ = 0.;

 public:
  // ID ������
  string id;

  explicit Shape(const unsigned verticesNumber)
      : vertices_number_(verticesNumber) {}
  // �����, ����������� ������� ������
  virtual double calcSquare() = 0;
  // �����, ����������� ����� ������� ������
  virtual Point calcGravityCenter() = 0;
  // �����, �������������� �������� ������ �� �������� ���� �� ������� �������
  // ������������ ������ �������
  virtual void rotate(double) = 0;
  // �����, �������������� ����������� ������ �� �������� ��������
  virtual void move(Point&) = 0;

  // ����� ��� ��������� ���������� ������ ������
  [[nodiscard]] unsigned getVerticesCount() const { return vertices_number_; }

  // ���������� ������� �� ��������� ������
  void setVertex(const unsigned& index, const Point& newPoint) const {
    if (index > vertices_number_) throw "The point index is too large";
    vertices_[index] = newPoint;
  }

  // �����, ��������� ���������� � ������ �� �����
  void printShape() {
    cout << '\n' << id << "\n�����:";
    for (unsigned i = 0U; i < vertices_number_; ++i)
      cout << "\nx" << i << ": " << vertices_[i].x << " y" << i << ": "
           << vertices_[i].y;
    const auto [x, y] = calcGravityCenter();
    cout << "\n�������: " << calcSquare() << "\n����� � �����: " << x << ' '
         << y << "\n\n";
  }

  // �����, ����������� ������ ������� ��������
  virtual double getShapeRadius() = 0;
  // �������� �� ������������ �����
  virtual bool isCorrectInput() = 0;
  virtual ~Shape() = default;
};

// ����������� ����� ��������
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
    // ����� ������������� ��� ������� �������������� ����� ����� ���������
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
    // �������� �� ��������� ���� ������
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

// ����������� ����� ���������������
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
    // ����� ������������� ��� ������� �������������� ����� ����� ���������
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
    // �������� �� ��������� ��������������� ������
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

// ��������� �������, ����������� ����������� ��������� �������
struct FactoryShape {
  // ����������� ����� �������� ������ �� ������ ����� ID
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

// ����� ����������� ��������
struct Operation {
  // ����������� �����, ����������� ��������� ������ ������ �� ������
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
  // ����������� �����, ����������� ����������� ������ � ������ ������
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
  // ����������� ����� ��������� �������� ���� �����
  static double compare(Shape*& first, Shape*& second) {
    return first->calcSquare() / second->calcSquare();
  }
};

int main() {
  setlocale(LC_ALL, "russian");
  constexpr int figureCount = 2;
  Shape* shape[figureCount]{};
  char type;
  // ���� ���� �����
  for (int j = 0; j < figureCount; ++j) {
    cout << "������� ��� ������: ";
    cin >> type;
    shape[j] = FactoryShape::createShape(type);
    if (shape[j] != nullptr) {
      cout << shape[j]->id << '\n';
      cout << "������� " << shape[j]->getVerticesCount()
           << " ������� (x � y): ";
      for (unsigned i = 0U; i < shape[j]->getVerticesCount(); ++i) {
        Point entered;
        cin >> entered.x >> entered.y;
        shape[j]->setVertex(i, entered);
      }
      if (!shape[j]->isCorrectInput()) {
        cout << "\n������ ������� �������!\n";
        --j;
      } else
        shape[j]->printShape();
    } else {
      cout << "������ ������ �� ����������!\n";
      --j;
    }
  }
  // ����� �������� ��� ��������
  do {
    cout << std::setprecision(3) << std::fixed
         << "1. ��������� ������;\n2. ��������� ������;\n"
            "3. �������� ��� ������� �� �������;\n"
            "4. ���������� ���� ����������� ��������;\n"
            "5. ���������� ���� ��������� ������ ������� � ������.\n";
    int choice;
    cin >> choice;
    try {
      unsigned number = 0U;
      double angle, compRes;
      Point offset;
      switch (choice) {
        case 1:  // �������
          cout << "����� ������: ";
          cin >> number;
          if (number - 1 > figureCount) throw "Shape does not exist!";
          cout << "���� ��������: ";
          cin >> angle;
          shape[number - 1]->rotate(angle);
          shape[number - 1]->printShape();
          break;
        case 2:  // ��������� ������
          cout << "����� ������: ";
          cin >> number;
          if (number - 1 > figureCount) throw "Shape does not exist!";
          cout << "�������� �� ��� � � y: ";
          cin >> offset.x >> offset.y;
          shape[number - 1]->move(offset);
          shape[number - 1]->printShape();
          break;
        case 3:  // �������� �������
          compRes = Operation::compare(shape[0], shape[1]);
          if (compRes == 1)
            cout << "������� �����.\n";
          else if (compRes > 1)
            cout << "������ 1 ������ ������ 2 � " << compRes << " ���(�)\n";
          else
            cout << "������ 2 ������ ������ 1 � " << 1 / compRes << " ���(�)\n";
          break;
        case 4:  // ��������� �����������
          if (Operation::isIntersect(shape[0], shape[1]))
            cout << "������ ������������.\n";
          else
            cout << "������ �� ������������.\n";
          break;
        case 5:  // ��������� ���������
          if (Operation::isInclude(shape[0], shape[1]))
            cout << "������ 1 ���������� � ������ 2.\n";
          else
            cout << "������ 1 �� ���������� � ������ 2.\n";
          if (Operation::isInclude(shape[1], shape[0]))
            cout << "������ 2 ���������� � ������ 1.\n";
          else
            cout << "������ 2 �� ���������� � ������ 1.\n";
          break;
        default:
          break;
      }
      if (choice == -1) break;
    } catch (...) {
      cout << "������ �� ����������!";
      for (auto& i : shape) delete i;
      return 0;
    }
  } while (true);
  for (auto& i : shape) delete i;
}