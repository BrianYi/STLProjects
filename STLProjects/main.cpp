#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
using namespace std;


class Student
{
    int fId;
    string fName;
    int fAge;
    char fSex;
    float fChinese;
    float fMath;
    float fEnglish;
public:
    Student() {}
    ~Student() {}
    float TotalGrade() const { return fChinese + fMath + fEnglish; }
    float AverageGrade() const { return TotalGrade() / 3.0f; }
    friend bool operator==(const Student& stu, int id) { return stu.fId == id; }
    friend istream& operator >> (istream& in, Student& stu)
    {
        in >> stu.fId >> stu.fName >> stu.fAge >> stu.fSex >> stu.fChinese >> stu.fMath >> stu.fEnglish;
        return in;
    }
    friend ostream& operator << (ostream& out, const Student& stu)
    {
        out << stu.fId << stu.fName << stu.fAge <<
            stu.fSex << stu.fChinese << stu.fMath << stu.fEnglish;
        return out;
    }
};


class StudentManagementSystem
{
public:
    StudentManagementSystem() {}
    ~StudentManagementSystem() {}
private:
    fstream fIOfile;
};

enum struct[[what]] myenum :int
{
    fuck1,
    fuck2,
    fuck3
};

int main() 
{
    return 0;
}