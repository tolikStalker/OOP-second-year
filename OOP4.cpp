#include <algorithm>
#include <fstream>
#include <iomanip>w
#include <iostream>
#include <map>
#include <vector>
using namespace std;

// ����� ������������
class University {
  string name_,  // �������� ������������
      city_,     // �������� ������
      specialization_;  // ���������� ��������� �����������
  unsigned mark_;  // ��������� ����� �� �������� �����������

 public:
  University(string& name, string& city, string specializations, unsigned marks)
      : name_(name),
        city_(city),
        specialization_(specializations),
        mark_(marks) {}
  // �������� �������� ������������
  string getName() { return name_; }
  // �������� �������� ������
  string getCity() { return city_; }
  // �������� ��������� ���� �� ����������� ������
  unsigned getMark() { return mark_; }
  // �������� �������� ������������� �� ����������� ������
  string getSpecialization() { return specialization_; }

  ~University() {}
};

// ������� �����-���������
class Interface {
 public:
  Interface() = default;
  // �����, ��������� �� ����� ��� ������������ � ����������
  virtual void print(string specialization) = 0;
  // �����, ����������� ����� ����������� � ���������
  virtual void emplace(string name, string city, string specialization,
                       unsigned mark) = 0;
  // �����, ��������� ����� ���������, ��������� ������ �� ��������
  // �������������
  virtual void find(string& specialization, Interface*& univer) = 0;
  // ����������� ��������� �����, ����������� ��������� ����������� ���
  // ����������
  static Interface* addUniversity(const char& choice);
  // �����, ������������ ������ ����������
  virtual size_t size() = 0;
  virtual ~Interface() = default;
};

// ����� ���������� map
class Map : public Interface {
  multimap<string, University> mp_;

 public:
  Map() = default;

  void print(string specialization) override {
    for (auto& i : mp_)
      cout << setw(10) << i.second.getCity() << "\t\t \t" << i.second.getName()
           << "\t \t \t" << i.second.getMark() << '\n';
  }

  void emplace(string name, string city, string specialization,
               unsigned mark) override {
    mp_.emplace(specialization, University(name, city, specialization, mark));
  }

  void find(string& specialization, Interface*& univer) override {
    auto it = mp_.equal_range(specialization);
    for (auto& finded = it.first; finded != it.second; ++finded)
      univer->emplace(finded->second.getName(), finded->second.getCity(),
                      specialization, finded->second.getMark());
  }

  size_t size() override { return mp_.size(); }

  ~Map() override = default;
};

// ����� ���������� vector
class Vector : public Interface {
  vector<University> vec_;

 public:
  Vector() = default;

  void emplace(string name, string city, string specialization,
               unsigned mark) override {
    vec_.emplace_back(University(name, city, specialization, mark));
  }

  void print(string specialization) override {
    for (auto& i : vec_)
      cout << setw(10) << i.getCity() << "\t\t \t" << i.getName() << "\t \t \t"
           << i.getMark() << '\n';
  }

  void find(string& specialization, Interface*& univer) override {
    for_each(vec_.begin(), vec_.end(),
             [&univer, &specialization](auto& vect) -> void {
               if (specialization == vect.getSpecialization())
                 univer->emplace(vect.getName(), vect.getCity(),
                                 vect.getSpecialization(), vect.getMark());
             });
  }

  size_t size() override { return vec_.size(); }

  ~Vector() override = default;
};

Interface* Interface::addUniversity(const char& choice) {
  switch (choice) {
    case 'v':
    case 'V':
      return new Vector();
    case 'm':
    case 'M':
      return new Map();
    default:
      return nullptr;
  }
}

int main() {
  setlocale(LC_ALL, "russian");
  Interface *container = nullptr, *requestContainer = nullptr;
  char choice;
  do {
    cout << "�������� vector (v) ��� map (m): ";
    cin >> choice;
    container = Interface::addUniversity(choice);
    // requestContainer = Interface::addUniversity(choice);
    if (container == nullptr) cout << "������ ��� ���������� �� ����������!\n";
  } while (container == nullptr);

  ifstream input("input.txt");
  constexpr int maxCountSpecialization = 5;
  vector<string> specs;
  try {
    if (!input.is_open()) throw runtime_error("File does not exist!");
  } catch (...) {
    cout << "���� �� ����������!";
    return EXIT_FAILURE;
  }

  while (!input.eof()) {
    // �������� ������ �� ���������
    string name, city, specializations,
        allSpecializations[maxCountSpecialization];
    unsigned specializationCount = 0U, marks[maxCountSpecialization]{};
    input >> city >> name >> specializations;
    for (size_t pos = 0; (pos = specializations.find('/')) != string::npos;
         specializationCount++) {
      allSpecializations[specializationCount] = specializations.substr(0, pos);
      specializations.erase(0, pos + 1);

      if (find(specs.begin(), specs.end(),
               allSpecializations[specializationCount]) == specs.end())
        specs.emplace_back(allSpecializations[specializationCount]);
    }
    allSpecializations[specializationCount++] = specializations;
    if (find(specs.begin(), specs.end(), specializations) == specs.end())
      specs.emplace_back(specializations);
    try {
      // ���� ��������� ������
      unsigned markCount = 0U;
      while (input.peek() != '\n' && !input.eof()) {
        if (markCount >= maxCountSpecialization)
          throw runtime_error("Array size exceeded!");
        input >> marks[markCount++];
      }
      if (markCount != specializationCount)
        throw runtime_error("Mark count not equal specialization count!");
    } catch (...) {
      cout << "���������� �������������� �� ��������� � ����������� ������!";
      return EXIT_FAILURE;
    }
    for (unsigned i = 0U; i < specializationCount; ++i)
      container->emplace(name, city, allSpecializations[i], marks[i]);
  }
  input.close();

  // ������������ ������ ���������� �� �������� ��������� ������ � ����� ���
  // ��������� �� �����
  do {
    requestContainer = Interface::addUniversity(choice);
    cout << "\n��������� �������������: ";
    for (auto& i : specs) cout << i << ", ";
    cout << "\n\n������� �������� �������������: ";
    string specialization;
    cin >> specialization;
    container->find(specialization, requestContainer);
    size_t size = requestContainer->size();
    if (size == 0)
      cout << "�� ������� �� ������� �� ������ ������������!\n";
    else {
      cout << "������������� " << specialization << " ������� � " << size
           << " �������������:\n�����\t\t\t|\t�����������\t|\t��������� "
              "����\n\n";
      requestContainer->print(specialization);
      requestContainer->~Interface();
    }
  } while (true);
  delete container;
  delete requestContainer;
}