#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <fstream>
#include <sstream>
#include <set>
#include <unordered_set>

class Student
{
private:
	std::string full_name;
	unsigned int group;
	unsigned int grade_book_number;
	int marks[4];
public:
	Student()
	{
		full_name = "N/A";
		group = 0;
		grade_book_number = 0;
		for (short i = 0; i < 4; i++) marks[i] = 0;
	}
	Student(std::string full_name, unsigned int group, unsigned int grade_book_number, int marks[4])
	{
		this->full_name = full_name;
		this->group = group;
		this->grade_book_number = grade_book_number;
		for (short i = 0; i < 4; i++) this->marks[i] = marks[i];
	}
	Student& operator=(const Student& other) {
		if (this != &other) {
			full_name = other.full_name;
			group = other.group;
			grade_book_number = other.grade_book_number;
			for (int i = 0; i < 4; i++) {
				marks[i] = other.marks[i];
			}
		}
		return *this;
	}
	bool operator<(const Student& other) const
	{
		int avg_first = 0;
		int avg_second = 0;
		for (short i = 0; i < 4; i++)
		{
			avg_first += marks[i];
			avg_second += other.marks[i];
		}
		return avg_first < avg_second;
	}
	bool operator==(const Student& student) const 
	{
		return full_name == student.full_name
			&& group == student.group
			&& grade_book_number == student.grade_book_number
			&& std::equal(marks, marks + 4, student.marks);
	}
	friend std::ostream& operator<< (std::ostream& os, const Student& student)
	{
		os << "Полное имя: " << student.full_name << std::endl;
		os << "Номер группы: " << student.group << std::endl;
		os << "Номер зачетной книжки: " << student.grade_book_number << std::endl;
		os << "Оценки: [";
		for (short i = 0; i < 3; i++)
		{
			os << student.marks[i] << ", ";
		}
		os << student.marks[3] << "]" << std::endl << std::endl;
		return os;
	}
	friend struct std::hash<Student>;
};

namespace std
{
	template<>
	struct hash<Student>
	{
		size_t operator()(const Student& student) const
		{
			return hash<string>()(student.full_name) ^ 
				(hash<unsigned int>()(student.group) << 2) ^
				(hash<unsigned int>()(student.grade_book_number) << 4) ^
				hash<int>{}(student.marks[0]) ^
				hash<int>{}(student.marks[1]) ^
				hash<int>{}(student.marks[2]) ^
				hash<int>{}(student.marks[3]);
		}
	};
}

std::vector<Student> readData(std::string path)
{
	std::vector<Student> students;
	std::ifstream file(path);
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string name, group, grade_book_number, marks_string;
		int marks[4] = { 0, 0, 0, 0 };
		std::getline(ss, name, ';');
		std::getline(ss, group, ';');
		std::getline(ss, grade_book_number, ';');
		std::getline(ss, marks_string, ';');

		std::stringstream marks_ss(marks_string);
		std::string mark;
		short index = 0;
		while (std::getline(marks_ss, mark, ',') && index < 4)
		{
			marks[index++] = std::stoi(mark);
		}
		students.emplace_back(name, std::stoi(group), std::stoi(grade_book_number), marks);
	}
	return students;
}

template <class T>
void writeData(const T& data, const std::string& path)
{
	std::ofstream file(path, std::ios::app);
	if (!file) return;
	for (const auto& student : data) file << student;
	file << "=======================" << std::endl;
	file.close();

}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru_RU.1251");
	std::string input_path = argv[1];
	std::string output_path = argv[2];
	std::vector<Student> students_vector = readData(input_path);

	std::set<Student> studentSet;
	std::copy(students_vector.begin(), students_vector.end(),
		std::inserter(studentSet, studentSet.end()));

	std::unordered_set<Student> studentUnorderedSet;
	std::copy(students_vector.begin(), students_vector.end(),
		std::inserter(studentUnorderedSet, studentUnorderedSet.end()));

	std::ofstream file(output_path, std::ios::trunc);
	writeData(studentSet, output_path);
	writeData(studentUnorderedSet, output_path);
}