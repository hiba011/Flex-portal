#pragma once

#include<iostream>
#include<windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <cstring>
#include<limits>
using namespace std;
class Attendance
{
private:
    string course_Code;
    int total_Classes;
    int classes_Attended;
public:
    Attendance();
    Attendance(string course_Code) : course_Code(course_Code), total_Classes(0), classes_Attended(0) { }
    void markAttendance(bool is_present);
    float getAttendancePercentage() const;
    void displayAttendance() const;
    string getCourseCode() const;
};

class marks
{
private:
    string assessment_type;
    float marks_obtained;
    float total;
    string subject;

public:
    marks();
    marks(const string& name, float m, float t, const string& sub) : assessment_type(name), marks_obtained(m), total(t), subject(sub) { }
    string getsubject();
    void setName(string name);
    void setmarks(float mark);
    void settotal(float total);
    string getName();
    float getmarks();
    float gettotal();
    void display();
};

class course;
class student // deals with basic information of individual students
{
private:
    string name;
    string rollnumber;
    int age;
    string contact;
    marks* assessments;
    int assessmentCount;
    int assessmentCapacity;
    //  course *enrolledcoursesname;
    string* enrolledcourses;
    float attendance;
    int totalcourses_enrolled;
    int currentcoursecount;
    string course;
    float attendancee;
    Attendance* track_attendance;
    int attendance_count;

public:
    student();
    student(string name, string rollnumber, string contact, int age);
    void setdata(string name, string rollnumber, int age, string contact, string course, float attendance, int totalcourses_enrolled);
    student(string name, string rollnumber, int age, string contact, string course, float attendance, int totalcourses_enrolled);
    string getname() const;
    string getrollnum() const;
    int getage() const;
    string getcontact() const;
    string getcourse();
    float getattendance();
    void input_details();
    void registercourse(string& code);
    void withdrawcourse(string& code);
    void setname(string updatename);
    void setcontact(string contact);
    void setrollnumber(string roll);
    void assignmarks(string code, string roll);
    bool check_course(string code);
    void arrayy();
    void displaymarks(string code);
    void mark_attendance(string code);
    void display_attendance(string code);
    int getassessmentcount();
    ~student();
};

class course
{
private:
    string code;
    string instructor;
    int credit;
    int count_ofstudents;
    student** enrolledstudents;
    int capacity;
public:
    course();
    course(string code, string instr, int cr, int cap);
    string getcode();
    void setcode(string code);
    void addstudent_tocourse(student* s);
    void removestudent_fromcourse(const string& rollnumber);
    void displayenrolled_students();
    string getinstructor();
    string getEnrolledStudentsDetails();
    int getcr();
    ~course();
};

class filehandler
{
    string studentfilename;
    string coursefilename;

public:
    filehandler() {}
    filehandler(string studentname, string coursename, student s) : studentfilename(studentname), coursefilename(coursename) {}
    static void savestudent_tofile(const student& Student);
    static void loadstudents();
    static void clear_and_update(student** Student, int& total);
    static void loadfromfile(student**& student, int& totalstudents);
    static void readfromfile(int& totalstudents);
    static void loadcoursesdetails(course** courses, int totalcourses);
    static void savemarks(const student& Student);
    ~filehandler() {}
};

class validator
{
public:
    validator() {}
    bool isValid(student* obj)
    {
        // check name is not empty
        int nameLength = 0;
        for (char c : obj->getname()) { ++nameLength; }
        if (nameLength == 0) {
            cout << "Name has to be provided." << endl;
            return false;
        }

        // check age is greater than 16
        if (obj->getage() <= 16) {
            cout << "Being older than 16 is required." << endl;
            return false;
        }

        int rollNumberLength = 0;
        for (char c : obj->getrollnum()) { ++rollNumberLength; }

        if (rollNumberLength != 8)
        {
            cout << "invalid roll number" << endl;
            return false;
        }

        // Check contact number is 11 digits
        int contactNumberLength = 0;
        for (char c : obj->getcontact()) { ++contactNumberLength; }
        if (contactNumberLength != 11) {
            cout << "Contact number must be 11 digits." << endl;
            return false;
        }
        for (char digit : obj->getcontact()) {
            if (digit < '0' || digit > '9') {
                cout << "Contact number must be 11 digits." << endl;
                return false;
            }
        }


        return true;
    }
    ~validator() {}
};

class Enrollment_Manager : public validator
{
private:
    student** enrollers; // keeps track of all the students enrolled in the application, central array
    int total_students;
    int MAX_STUDENTS;
    course** coursesarray;
    int MAX_COURSES;
    int totalcourses;

public:
    Enrollment_Manager();
    void addstudent();
    void current_students();
    void remove_student(string rollnumber);
    void update_studentinfo();
    course* findcoursebycode(const string& code, int totalcourses);
    void enrollStudentInCourse(const string& rollnumber);
    void addcourse(course* c);
    void availablecourses();
    string toLowercase(const string& str);
    void withdrawStudentFromCourse(string rollnum, string code);
    student** get_student_array();
    void enrolled_courses(string rollnum);
    void marksassignment(string code, string rollnum);
    void display_marks(string code, string roll);
    void markAttendance(string code, string roll);
    void display_attendance(string code, string rollnum);
    void fromfile();

    ~Enrollment_Manager();
};
