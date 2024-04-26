#include <cstddef> // для std::size_t
#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

struct Student {
    int id;
    std::string name;
    int age;
};

class Database {
    std::unordered_map<int, std::shared_ptr<Student>> students;
public:
    bool insert(const Student& student) {
        auto it = students.find(student.id);
        if (it != students.end()) {
            // студент с таким id уже в базе данных
            return false;
        }
        students.emplace(student.id, std::make_shared<Student>(student));
        return true;
    }
    
    // пытается удалить студента по id
    // возвращает количество удалённых студентов (0 или 1)
    std::size_t remove_student(int id) {
        return students.erase(id);
    }
    
    Student get_student_info(int id) {
        auto it = students.find(id);
        if (it == students.end()) {
            // студента с таким id не существует
            return Student{ 0, std::string{}, 0 };
        }
        return *it->second;
    }
};

int main()
{
    Database db;
    db.insert(Student{1, "Alice", 18});
    db.insert(Student{2, "Bob", 18});
    db.insert(Student{3, "Harry", 20});
    db.insert(Student{4, "Tyler", 19});
    db.insert(Student{5, "Rex", 18});
    
    auto student = db.get_student_info(3);
    std::cout << "student with id=3 " << student.name << " age=" << student.age << '\n';
    if (db.remove_student(3) == 1) {
        std::cout << "deleted student with id = 3\n";
    };
    student = db.get_student_info(3);
    std::cout << "student with id=3 " << student.name << " age=" << student.age << '\n';
}