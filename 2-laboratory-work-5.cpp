#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <fstream>
#include <sstream>

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
	Student(std::string full_name, unsigned int group, unsigned int grade_book_number, int marks[4])
	{
		this->full_name = full_name;
		this->group = group;
		this->grade_book_number = grade_book_number;
		for (short i = 0; i < 4; i++) this->marks[i] = marks[i];
	}
	bool operator<(const Student& other)
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