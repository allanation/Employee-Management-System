#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Define the Employee class for more complex behavior and encapsulation
class Employee
{
private:
    string firstName, lastName, jobTitle;
    int id, departmentId;

public:
    // Constructor for the Employee class
    Employee(int _id, int _departmentId, const string &_firstName, const string &_lastName, const string &_jobTitle)
    {
        id = _id;
        departmentId = _departmentId;
        firstName = _firstName;
        lastName = _lastName;
        jobTitle = _jobTitle;
    }
    // TO BE REMOVED
    Employee()
    {
        id = 0;
        departmentId = 0;
        firstName = "_firstName";
        lastName = "_lastName";
        jobTitle = "_jobTitle";
    }

    void createEmployee()
    {
        cout << "Created Employee!" << endl;
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
    // TO BE REMOVED
    Department()
    {
        id = 0;
        companyId = 0;
        managedBy = 0;
        name = "_name";
        location = "_location";
    }

    void createDepartment()
    {
        cout << "Created Department!" << endl;
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

    // TO BE REMOVED
    Company()
    {
        id = 0;
        name = "_name";
    }

    void createCompany()
    {
        cout << "Created Company!" << endl;
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

// FOR OPTIMIZATION USER STORY
string *toUppercase(const string &_word)
{
    string uppercase;
    for (char c : _word)
    {
        uppercase += toupper(c);
    }

    string *pointer = new string(uppercase);
    return pointer;
}

void create(int tableSelected, string &_values)
{
    // insert after destructuring
    vector<string> deconstructedQuery;
    string query;

    istringstream iss(_values);

    while (getline(iss, query, ','))
    {
        // Trim leading and trailing spaces
        query.erase(0, query.find_first_not_of(" "));
        query.erase(query.find_last_not_of(" ") + 1);
        deconstructedQuery.push_back(query);
    }
    for (const std::string &token : deconstructedQuery)
    {
        std::cout << "Token: " << token << std::endl;
    }

    switch (tableSelected)
    {
    case 1:
        // employees.insert(pair<int, Employee>(100, Employee(100, 10, "Allan", "Lopez", "Manager")));
        cout << "Created Employee! with: " << _values << endl;
        break;
    case 2:
        cout << "Created Department!" << _values << endl;
        break;
    case 3:
        cout << "Created Company!" << _values << endl;
        break;
    default:
        cout << "I don't even know how you got here" << endl;
        exit(0);
        break;
    }
}

void processSQL(string &_sqlQuery)
{
    // Deconstructing sql query into a vector
    istringstream iss(_sqlQuery);
    vector<string> deconstructedQuery;
    string query, table;

    while (iss >> query)
    {
        deconstructedQuery.push_back(query);
    }

    // print whats in the dQ
    for (const std::string &q : deconstructedQuery)
    {
        std::cout << q << std::endl;
    }

    // Format operator to be capitalized
    string *uppercaseOperator = toUppercase(deconstructedQuery[0]);

    // Search for the target word within the vector
    size_t fromPosition = std::string::npos;
    for (size_t i = 0; i < deconstructedQuery.size(); ++i)
    {
        cout << "checking: " << deconstructedQuery[i] << endl;
        if (deconstructedQuery[i] == "from")
        {
            fromPosition = i;
            table = deconstructedQuery[fromPosition + 1];
            cout << "found it at: " << fromPosition << " in table: " << table << endl;
            break; // Stop searching once the target is found
        }
    }

    if (*uppercaseOperator == "INSERT")
    {
        // check correctness of query
        string *uppercaseInto = toUppercase(deconstructedQuery[1]);

        if (*uppercaseInto == "INTO")
        {
            table = deconstructedQuery[2];
            if (table == "employees" || table == "departments" || table == "companies")
            {
                // check VALUES
                string values;
                // FIX THIS!
                //  find position of ( and then find position of ) THEN concat THEN send as props for create()
                if (deconstructedQuery[4].find_first_of('(') == 0 && (deconstructedQuery[4].find_last_of(')') == deconstructedQuery[4].length() - 1 || deconstructedQuery[4].find_last_of(';') == deconstructedQuery[4].length() - 1))
                {
                    values = deconstructedQuery[4];
                }
                else
                {
                    cout << "Must include VALUES in parenthesis.\nEx.: INSERT INTO <table> VALUES (values);" << endl;
                    exit(0);
                }

                if (table == "employees")
                {
                    create(1, values);
                }
                if (table == "departments")
                {
                    create(2, values);
                }
                if (table == "companies")
                {
                    create(3, values);
                }
            }
            else
            {
                cout << "Wrong table name.\nOnly have tables called: employees, departments, and companies.\nTry again!" << endl;
                exit(0);
            }
        }
        else
        {
            cout << "Must include INTO in your query.\nEx.: INSERT INTO <table> VALUES (values);" << endl;
            exit(0);
        }
    }
    else if (*uppercaseOperator == "SELECT")
    {
        cout << "READING~" << endl;
        if (deconstructedQuery[1] == "*")
        {
            cout << "ALL" << endl;
        }
        else
        {
            cout << deconstructedQuery[1] << endl;
        }
    }
    else if (*uppercaseOperator == "UPDATE")
    {
        cout << "UPDATING~" << endl;
    }
    else if (*uppercaseOperator == "DELETE")
    {
        cout << "DELETING~" << endl;
    }
    else
    {
        cout << "Invalid sql ciao~" << endl;
        exit(0);
    }
}

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

    // for (const auto &entry : employees)
    // {
    //     cout << "Employee ID: " << entry.first << ", Name: " << entry.second.getFirstName() << endl;
    // }
    // for (const auto &entry : departments)
    // {
    //     cout << "Department ID: " << entry.first << ", Managed By: " << entry.second.getManagedBy() << endl;
    // }
    // for (const auto &entry : companies)
    // {
    //     cout << "Company ID: " << entry.first << ", Name: " << entry.second.getName() << endl;
    // }

    // CRUD OPS
    // personal rules:
    //  1- CANNOT create or update or drop tables
    //  2- CAN crud records in tables
    // CREATE when INSERT INTO <table>(col1,col2,...) VALUES (val1,val2,...)
    // READ when SELECT (col1,col2,...,*) FROM <table> WHERE <expression>
    // UPDATE when UPDATE <table> SET col1=val1, col2=val2,... WHERE <expression>
    // DELETE when DELETE FROM <table> WHERE <expression>

    string sqlQuery, sqlOperator;
    cout << "ENTER SQL QUERY" << endl;
    getline(cin, sqlQuery);
    processSQL(sqlQuery);

    return 0;
}