using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace OOP5 {
    // Класс университета
    public class University {
        public University(string name, string city, string specialization,
            int mark) {
            Name = name;
            City = city;
            Specialization = specialization;
            Mark = mark;
        }

        // Свойства получения private полей
        public string Name { get; }
        public string City { get; }
        public string Specialization { get; }
        public int Mark { get; }
    }

    // Базовый абстрактный класс интерфейса 
    public abstract class Interface {
        // Метод добавления университета в коллекцию
        public abstract void Emplace(string name, string city,
            string specialization, int mark);

        // Метод, возвращающий список университетов с заданной специальностью
        public abstract List<University> CreateNewListWithSpecialization(
            string? specialization);

        // Статический метод, реализующий фабричный метод
        public static Interface? GetCollection(char name) => name switch {
            'v' => new Vector(),
            'm' => new Map(),
            _ => null,
        };
    }

    // Производный класс списка
    public class Vector : Interface {
        private readonly List<University> list = new();

        public override void Emplace(string name, string city,
            string specialization, int mark) {
            if (list.Find(x => x.Name == name && x.Specialization == specialization) != null)
                throw new Exception("University already exist");
            list.Add(new University(name, city, specialization, mark));
        }

        public override List<University> CreateNewListWithSpecialization(
            string? specialization) {
            return list.Where(u => u.Specialization.Equals(specialization))
                .ToList();
        }
    }

    // Производный класс словаря
    public class Map : Interface {
        private readonly Dictionary<Tuple<string, string>, University> dictionary = new();

        public override void Emplace(string name, string city,
            string specialization, int mark) {
            if (dictionary.ContainsKey(new Tuple<string, string>(name, specialization)))
                throw new Exception("University already exist");
            dictionary.Add(new Tuple<string, string>(name, specialization),
                new University(name, city, specialization, mark));
        }

        public override List<University> CreateNewListWithSpecialization(
            string? specialization) {
            return dictionary
                .Where(d => d.Key.Item2.Equals(specialization))
                .ToDictionary(i => i.Key, i => i.Value).Values.ToList();
        }
    }

    public class Program {
        public static void Main() {
            Interface? universityCollection;
            // Фабричный метод выбора коллекции
            do {
                Console.Write("Выберите vector (v) или map (m): ");
                var c = Console.ReadKey().KeyChar;
                universityCollection = Interface.GetCollection(c);
                if (universityCollection == null)
                    Console.WriteLine("\nДанный тип контейнера не существует!");
            } while (universityCollection == null);

            HashSet<string> specializationSet = new();
            FileInfo file = new("input.txt");
            if (file.Exists) {
                using var stream = file.Open(FileMode.Open);
                using StreamReader reader = new(stream);
                string? line;
                // Пока введенная строка не равна null
                while ((line = reader.ReadLine()) != null) {
                    // Разделяем строку по пробелам и табуляциям
                    var words = line.Split(new[] { ' ', '\t' },
                        StringSplitOptions.RemoveEmptyEntries);
                    // Разделяем специальности по '/'
                    string[] specializations;
                    try {
                        specializations = words[2].Split('/');
                    }
                    catch {
                        Console.WriteLine("\nНекорректный ввод из файла!");
                        return;
                    }

                    specializationSet.UnionWith(specializations);
                    if (specializations.Length > 5) {
                        Console.WriteLine(
                            "\nПревышено количество специальностей!");
                        return;
                    }

                    var mark = new int[specializations.Length];
                    // Преобразуем баллы из строки в числа
                    try {
                        for (int i = 0; i < specializations.Length; ++i)
                            if (!int.TryParse(
                                    words[words.Length - mark.Length + i],
                                    out mark[i])) {
                                Console.WriteLine(
                                    "\nНе удалось преобразовать баллы в числа! Проверьте корректность данных файла.");
                                return;
                            }
                    }
                    catch {
                        Console.WriteLine(
                            "\nКоличество специальностей не совпадает с количеством баллов!");
                        return;
                    }

                    try {
                        for (int i = 0; i < specializations.Length; ++i)
                            universityCollection.Emplace(words[1], words[0],
                              specializations[i], mark[i]);
                    }
                    catch {
                        Console.WriteLine(
                            "\nУниверситет обработан несколько раз.");
                        return;
                    }
                }
                stream.Dispose();
                reader.Dispose();
            }
            else {
                Console.WriteLine("Файл не существует!");
                return;
            }
            
            // Ввод специальности
            do {
                Console.Write(
                    "\nДоступные специальности: {0}\nВведите название специальности: ",
                    string.Join(", ", specializationSet));
                string? specialization = Console.ReadLine();
                List<University> filteredList =
                    universityCollection.CreateNewListWithSpecialization(
                        specialization);
                if (filteredList.Any()) {
                    Console.WriteLine(
                        $"Специальность {specialization} найдена в {filteredList.Count} университетах:\nГород\t\t\t|\tУниверситет\t|\tПроходной балл\n");
                    filteredList.ForEach(i =>
                        Console.WriteLine(
                            $"{i.City,-8}\t\t \t{i.Name}\t\t \t{i.Mark}"));
                }
                else
                    Console.WriteLine(
                        "По запросу не найдено не одного университета!");
            } while (true);
        }
    }
}