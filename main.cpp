#include <iostream>
#include <map>
#include <string>

using namespace std;

// Define the Employee class for more complex behavior and encapsulation
class Employee
{
private:
    string firstName, lastName, jobTitle;
    int id, departmentId;

public:
    // // Constructor for the Employee class
    Employee(int _id, int _departmentId, const string &_firstName, const string &_lastName, const string &_jobTitle)
    {
        id = _id;
        departmentId = _departmentId;
        firstName = _firstName;
        lastName = _lastName;
        jobTitle = _jobTitle;
    }

    void createEmployee()
    {
    }
    void readEmployee()
    {
        cout << "Library is now open for employee number " << id << endl;
    }
    void updateEmployee()
    {
    }
    void deleteEmployee()
    {
    }

    const string &getFirstName() const
    {
        return firstName;
    }

    int getDepartmentId() const
    {

        return departmentId;
    }
};

// Define the Department class for more complex behavior and encapsulation
class Department
{
private:
    string name, location;
    int id, companyId, managedBy;

public:
    // Constructor for the Department class$
    Department(int _id, int _companyId, int _managedBy, const string &_name, const string &_location)
    {
        id = _id;
        companyId = _companyId;
        managedBy = _managedBy;
        name = _name;
        location = _location;
    }

    void createDepartment()
    {
    }
    void readDepartment()
    {
        cout << "\n\nYou are reading the department \n";
    }
    void updateDepartment()
    {
    }
    void deleteDepartment()
    {
    }
    int getId() const
    {
        return id;
    }
    int getManagedBy() const
    {
        return managedBy;
    }
};

class Company
{
private:
    string name;
    int id;

public:
    // Constructor for the Company class
    Company(int _id, const string &_name)
    {
        id = _id;
        name = _name;
    }

    void createCompany()
    {
    }
    void readCompany()
    {
        cout << "Read company hoe!";
    }
    void updateCompany()
    {
    }
    void deleteCompany()
    {
    }

    const string &getName() const
    {
        return name;
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
    companies.insert(pair<int, Company>(1, Company(1, "Apple")));
    companies.insert(pair<int, Company>(2, Company(2, "Microsoft")));

    departments.insert(pair<int, Department>(10, Department(10, 1, 100, "Finance", "New York")));
    departments.insert(pair<int, Department>(11, Department(11, 1, 101, "Engineering", "New York")));
    departments.insert(pair<int, Department>(12, Department(12, 1, 102, "Design", "Los Angeles")));
    departments.insert(pair<int, Department>(13, Department(13, 2, 103, "Design", "Montreal")));
    departments.insert(pair<int, Department>(14, Department(14, 2, 104, "Engineering", "New York")));

    employees.insert(pair<int, Employee>(100, Employee(100, 10, "Allan", "Lopez", "Manager")));
    employees.insert(pair<int, Employee>(101, Employee(101, 11, "Jacob", "Smith", "Manager")));
    employees.insert(pair<int, Employee>(102, Employee(102, 12, "Elena", "Stroop", "Manager")));
    employees.insert(pair<int, Employee>(103, Employee(103, 13, "Victor", "Kiltz", "Manager")));
    employees.insert(pair<int, Employee>(104, Employee(104, 14, "Ting", "Chen", "Manager")));
    employees.insert(pair<int, Employee>(105, Employee(105, 12, "Justine", "Khan", "Designer")));
    employees.insert(pair<int, Employee>(106, Employee(106, 10, "Edgar", "Mohamed", "Finance")));
    employees.insert(pair<int, Employee>(107, Employee(107, 10, "Fiona", "Appleton", "Finance")));
    employees.insert(pair<int, Employee>(108, Employee(108, 11, "Manon", "Messier", "Engineer")));
    employees.insert(pair<int, Employee>(109, Employee(109, 13, "Katelyn", "Ronston", "Designer")));
    employees.insert(pair<int, Employee>(110, Employee(110, 14, "Paul", "Patel", "Engineer")));
    employees.insert(pair<int, Employee>(111, Employee(111, 11, "Lucas", "Strong", "Engineer")));

    for (const auto &entry : employees)
    {
        cout << "Employee ID: " << entry.first << ", Name: " << entry.second.getFirstName() << endl;
    }
    for (const auto &entry : departments)
    {
        cout << "Department ID: " << entry.first << ", Managed By: " << entry.second.getManagedBy() << endl;
    }
    for (const auto &entry : companies)
    {
        cout << "Company ID: " << entry.first << ", Name: " << entry.second.getName() << endl;
    }

    // CRUD OPS
    // personal rules:
    //  1- CANNOT update or drop tables
    //  2- CAN crud records in tables
    // CREATE when INSERT INTO <table>(col1,col2,...) VALUES (val1,val2,...)
    // READ when SELECT (col1,col2,...,*) FROM <table> WHERE <expression>
    // UPDATE when UPDATE <table> SET col1=val1, col2=val2,... WHERE <expression>
    // DELETE when DELETE FROM <table> WHERE <expression>

    // string sqlQuery;
    // cout << "ENTER SQL QUERY" << endl;
    // getline(cin, sqlQuery);
    // cout << "Your input: " << sqlQuery << endl;

    return 0;
}