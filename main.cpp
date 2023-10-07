#include <iostream>
#include <fstream>
#include <map>

using namespace std;

// Define the Employee class for more complex behavior and encapsulation
class Employee
{
private:
    char firstName[50], lastName[50], jobTitle[50];
    int id, departmentId;

public:
    // // Constructor for the Employee class
    Employee(int _id, int _departmentId, char *_firstName, char *_lastName, char *_jobTitle)
        : id(_id), departmentId(_departmentId)
    {
        strncpy(firstName, _firstName, sizeof(firstName));
        strncpy(lastName, _lastName, sizeof(lastName));
        strncpy(jobTitle, _jobTitle, sizeof(jobTitle));
        firstName[sizeof(firstName) - 1] = '\0'; // Ensure null-terminated strings
        lastName[sizeof(lastName) - 1] = '\0';
        jobTitle[sizeof(jobTitle) - 1] = '\0';
    }

    void createEmployee()
    {
    }
    void readEmployee()
    {
    }
    void updateEmployee()
    {
    }
    void deleteEmployee()
    {
    }
};

// Define the Department class for more complex behavior and encapsulation
class Department
{
private:
    char name[50], location[50];
    int id, companyId, managedBy;

public:
    // Constructor for the Department class
    Department(int _id, int _companyId, int _managedBy, char *_name, char *_location)
        : id(_id), companyId(_companyId), managedBy(_managedBy)
    {
        strncpy(name, _name, sizeof(name));
        strncpy(location, _location, sizeof(location));
        name[sizeof(name) - 1] = '\0';
        location[sizeof(location) - 1] = '\0';
    }

    void createDepartment()
    {
    }
    void readDepartment()
    {
    }
    void updateDepartment()
    {
    }
    void deleteDepartment()
    {
    }
};

class Company
{
private:
    char name[50];
    int id;

public:
    // Constructor for the Company class
    Company(int _id, char *_name) : id(_id)
    {
        strncpy(name, _name, sizeof(name));
        name[sizeof(name) - 1] = '\0';
    }

    void createCompany()
    {
    }
    void readCompany()
    {
    }
    void updateCompany()
    {
    }
    void deleteCompany()
    {
    }
};

int main()
{
    system("clear");
    cout
        << "\n\t\t\t* WELCOME TO THE COMPANY DATABASE *" << endl;
    cout << "\nDescription: Design a simple command-line database where you use pointers to manage records, tables, and data relationships. You can implement basic database operations like insertion, retrieval, and deletion.\n";

    // Initialize tables
    map<int, Employee> employees;
    map<int, Department> departments;
    map<int, Company> companies;

    // Populate tables
    companies[1] = Company(1, "Apple");
    companies[2] = Company(2, "Microsoft");

    departments[10] = Department(10, 1, 100, "Finance", "New York");
    departments[11] = Department(11, 1, 101, "Engineering", "New York");
    departments[12] = Department(12, 1, 102, "Design", "Los Angeles");
    departments[13] = Department(13, 2, 103, "Design", "Montreal");
    departments[14] = Department(14, 2, 104, "Engineering", "New York");

    employees[100] = Employee(100, 10, "Allan", "Lopez", "Manager");
    employees[101] = Employee(101, 11, "Jacob", "Smith", "Manager");
    employees[102] = Employee(102, 12, "Elena", "Stroop", "Manager");
    employees[103] = Employee(103, 13, "Victor", "Kiltz", "Manager");
    employees[104] = Employee(104, 14, "Ting", "Chen", "Manager");
    employees[105] = Employee(105, 12, "Justine", "Khan", "Designer");
    employees[106] = Employee(106, 10, "Edgar", "Mohamed", "Finance");
    employees[107] = Employee(107, 10, "Fiona", "Appleton", "Finance");
    employees[108] = Employee(108, 11, "Manon", "Messier", "Engineer");
    employees[109] = Employee(109, 13, "Katelyn", "Ronston", "Designer");
    employees[110] = Employee(110, 14, "Paul", "Patel", "Engineer");

    return 0;
}