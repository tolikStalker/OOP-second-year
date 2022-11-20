using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace Laba6 {
    // Класс университета
    public class University {
        public University(string name, string city, string specialization, int mark) {
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
    internal abstract class Interface {
        // Метод добавления университета в коллекцию
        public abstract void Emplace(string name, string city, string specialization,
                       int mark);
        // Метод, возвращающий список университетов с заданной специальностью
        public abstract List<University> CreateNewListWithSpecialization(string specialization);
    }

    // Производный класс списка
    internal class Vector : Interface {
        private readonly List<University> list = new List<University>();

        public override void Emplace(string name, string city, string specialization,
               int mark) {
            if (list.Find(x => x.Name == name && x.Specialization == specialization) != null)
                throw new Exception("University already found");
            list.Add(new University(name, city, specialization, mark));
        }

        public override List<University> CreateNewListWithSpecialization(string specialization) {
            return list.Where(u => u.Specialization.Equals(specialization)).ToList();
        }
    }

    // Производный класс словаря
    internal class Map : Interface {
        // Ключ - название университета, название специальности
        private readonly Dictionary<Tuple<string, string>, University> dictionary =
            new Dictionary<Tuple<string, string>, University>();

        public override void Emplace(string name, string city, string specialization, int mark) {
            if (dictionary.ContainsKey(new Tuple<string, string>(name, specialization)))
                throw new Exception("University already found");
            dictionary.Add(new Tuple<string, string>(name, specialization), new University(name, city, specialization, mark));
        }

        public override List<University> CreateNewListWithSpecialization(string specialization) {
            return dictionary.Where(d => d.Key.Item2.Equals(specialization)).ToDictionary(i => i.Key, i => i.Value).Values.ToList();
        }
    }

    // Перечисление коллекций
    public enum CollectionType {
        List,
        Dictionary
    }

    // Класс обработчика данных клиента
    public class Data {
        private Interface universityCollection; // Класс контейнера
        public readonly HashSet<string> specializationSet = new HashSet<string>();  // Множество всех специальностей

        // Получение списка пщ заданной специальности
        public List<University> GetRequest(string specialization) {
            return universityCollection.CreateNewListWithSpecialization(specialization);
        }

        // В зависимости от типа коллекции динамически создается нужный тип контейнера
        private Interface CollectionTypeChoice(CollectionType collectionType) {
            if (collectionType == CollectionType.List)
                return new Vector();
            return new Map();
        }

        // Обработчик файла, возвращает сообщение об ошибке
        public string FileHandler(OpenFileDialog dialog, CollectionType collectionType) {
            universityCollection = CollectionTypeChoice(collectionType);

            Stream stream = dialog.OpenFile();
            var reader = new StreamReader(stream, System.Text.Encoding.GetEncoding("windows-1251"));
            string line;
            // Пока введенная строка не равна null
            while ((line = reader.ReadLine()) != null) {
                // Разделяем строку по пробелам и табуляциям
                var words = line.Split(new char[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);
                // Разделяем специальности по '/'
                string[] specializations;
                try {
                    specializations = words[2].Split('/');
                }
                catch {
                    stream.Dispose();
                    reader.Dispose();
                    return "Некорректный ввод из файла!";
                }
                specializationSet.UnionWith(specializations);
                if (specializations.Length > 5) {
                    stream.Dispose();
                    reader.Dispose();
                    return "Некорректный ввод из файла! Превышено количество специальностей!";
                }

                var mark = new int[specializations.Length];
                // Преобразуем баллы из строки в числа
                try {
                    for (int i = 0; i < specializations.Length; ++i)
                        if (!int.TryParse(words[words.Length - mark.Length + i], out mark[i])) {
                            stream.Dispose();
                            reader.Dispose();
                            return "Некорректный ввод из файла! Не удалось преобразовать баллы в числа!Проверьте корректность данных файла";
                        }
                }
                catch {
                    stream.Dispose();
                    reader.Dispose();
                    return "Некорректный ввод из файла! Количество специальностей не совпадает с количеством баллов!";
                }
                try {
                    for (int i = 0; i < specializations.Length; ++i)
                        universityCollection.Emplace(words[1], words[0], specializations[i], mark[i]);
                }
                catch {
                    stream.Dispose();
                    reader.Dispose();
                    return "Некорректный ввод из файла! Университет обработан несколько раз";
                }
            }
            stream.Dispose();
            reader.Dispose();
            return null;
        }
    }
}
