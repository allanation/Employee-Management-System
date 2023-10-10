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
        // OPTIMIZATION: KEEP TRACK OF ID TO AUTOMATICALLY ASSIGN ID WITHOUT CHECKING FOR DUPS
        id = _id;
        departmentId = _departmentId;
        firstName = _firstName;
        lastName = _lastName;
        jobTitle = _jobTitle;
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

    int getId() const
    {

        return id;
    }
    int getDepartmentId() const
    {
        return departmentId;
    }
    const string &getFirstName() const
    {
        return firstName;
    }
    const string &getLastName() const
    {
        return lastName;
    }
    const string &getJobTitle() const
    {
        return jobTitle;
    }

    void printEmployee()
    {
        cout << "Employee ID: " << id << endl;
        cout << "Dapartment ID: " << departmentId << endl;
        cout << "First Name: " << firstName << endl;
        cout << "Last Name: " << lastName << endl;
        cout << "Job Title: " << jobTitle << endl;
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
        // OPTIMIZATION: KEEP TRACK OF ID TO AUTOMATICALLY ASSIGN ID WITHOUT CHECKING FOR DUPS
        id = _id;
        companyId = _companyId;
        managedBy = _managedBy;
        name = _name;
        location = _location;
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
    int getCompanyId() const
    {
        return companyId;
    }
    int getManagedBy() const
    {
        return managedBy;
    }
    const string &getName() const
    {
        return name;
    }
    const string &getLocation() const
    {
        return location;
    }
    void printDepartment()
    {
        cout << "Department ID: " << id << endl;
        cout << "Company ID: " << companyId << endl;
        cout << "Managed By: " << managedBy << endl;
        cout << "Name: " << name << endl;
        cout << "Location: " << location << endl;
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
        // OPTIMIZATION: KEEP TRACK OF ID TO AUTOMATICALLY ASSIGN ID WITHOUT CHECKING FOR DUPS
        id = _id;
        name = _name;
    }
    Company()
    {
        id = 0;
        name = "";
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
    int getId() const
    {
        return id;
    }
    const string &getName() const
    {
        return name;
    }
    void printCompany()
    {
        cout << "Company ID: " << id << endl;
        cout << "Name: " << name << endl;
    }
};

// struct Database
// {
//     // Initialize tables
//     map<int, Employee> employeesD;
//     map<int, Department> departmentsD;
//     map<int, Company> companiesD;
// };

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

string *processString(string &_string)
{

    if (_string.find_first_of('"') == 0 && _string.find_last_of('"'))
    {
        _string.erase(0, 1);
        _string.erase(_string.find_last_not_of('"') + 1);
        string *pointer = new string(_string);
        return pointer;
    }
    else
    {
        cout << "Invalid string: " << _string << "Missing quotation marks (\"...\")" << endl;
        exit(0);
    }
}

int processInt(string &_int)
{
    int num;

    try
    {
        num = std::stoi(_int);
        return num;
    }
    catch (const invalid_argument &e)
    {
        cout << "Invalid argument: " << e.what() << std::endl;
        exit(0);
    }
    catch (const out_of_range &e)
    {
        cout << "Out of range: " << e.what() << std::endl;
        exit(0);
    }
}

// OPTIMIZATION: MAKE FACTORY METHOD FOR TABLES
// check this: https://www.geeksforgeeks.org/factory-method-for-designing-pattern/

// Initialize tables
map<int, Employee> employees;
map<int, Department> departments;
map<int, Company> companies;

void select(int tableSelected, string &_columns)
{
    // insert after destructuring
    vector<string> deconstructedColumns;
    string query;

    istringstream iss(_columns);

    while (getline(iss, query, ','))
    {
        // Trim leading and trailing spaces
        query.erase(0, query.find_first_not_of(" "));
        query.erase(query.find_last_not_of(" ") + 1);

        deconstructedColumns.push_back(query);
    }

    switch (tableSelected)
    {
    case 1:
    {
        if (deconstructedColumns[0] == "*")
        {
            cout << "ID\t\tDEPARTMENTID\t\tFIRSTNAME\t\tLASTNAME\t\tJOBTITLE" << endl;
            for (const auto &employee : employees)
            {
                cout << employee.first << "\t\t" << employee.second.getDepartmentId() << "\t\t" << employee.second.getFirstName() << "\t\t" << employee.second.getLastName() << "\t\t" << employee.second.getJobTitle() << endl;
            }
        }
        else
        {

            for (int i = 0; i < employees.size(); i++)
            {
                vector<string> uppercaseColumns;
                // print column headers
                if (i == 0)
                {
                    for (const auto &entry : deconstructedColumns)
                    {
                        string *uppercase = toUppercase(entry);
                        uppercaseColumns.push_back(*uppercase);
                        cout << *uppercase << "\t\t";
                    }
                    cout << endl;
                }

                // OPTIMIZATION: remove double for-loop
                // loop through table and print desired columns
                for (const auto &employee : employees)
                {
                    for (int i = 0; i < uppercaseColumns.size(); i++)
                    {
                        if (uppercaseColumns[i] == "ID")
                        {
                            cout << employee.first << "\t\t";
                        }
                        else if (uppercaseColumns[i] == "DEPARTMENTID")
                        {
                            cout << employee.second.getDepartmentId() << "\t\t";
                        }
                        else if (uppercaseColumns[i] == "FIRSTNAME")
                        {
                            cout << employee.second.getFirstName() << "\t\t";
                        }
                        else if (uppercaseColumns[i] == "LASTNAME")
                        {
                            cout << employee.second.getLastName() << "\t\t";
                        }
                        else if (uppercaseColumns[i] == "JOBTITLE")
                        {
                            cout << employee.second.getJobTitle() << "\t\t";
                        }
                        else
                        {
                            cout << "Invalid columns: Employees table's only columns are:\nid, departmentId, firstName, lastName, jobTitle" << endl;
                            exit(0);
                        }

                        if (i == uppercaseColumns.size() - 1)
                        {
                            cout << endl;
                        }
                    }
                }
            }
        }
        cout << "\nemployees table selected!" << endl;
    }
    break;
    case 2:
    {
        if (deconstructedColumns[0] == "*")
        {
            cout << "ID\t\tCOMPANYID\t\tMANAGEDBY\t\tNAME\t\tLOCATION" << endl;
            for (const auto &department : departments)
            {
                cout << department.first << "\t\t" << department.second.getCompanyId() << "\t\t" << department.second.getManagedBy() << "\t\t" << department.second.getName() << "\t\t" << department.second.getLocation() << endl;
            }
        }
        else
        {
            for (int i = 0; i < departments.size(); i++)
            {
                vector<string> uppercaseColumns;
                // print column headers
                if (i == 0)
                {
                    for (const auto &entry : deconstructedColumns)
                    {
                        string *uppercase = toUppercase(entry);
                        uppercaseColumns.push_back(*uppercase);
                        cout << *uppercase << "\t\t";
                    }
                    cout << endl;
                }

                // OPTIMIZATION: remove double for-loop
                // loop through table and print desired columns
                for (const auto &department : departments)
                {
                    for (int i = 0; i < uppercaseColumns.size(); i++)
                    {
                        if (uppercaseColumns[i] == "ID")
                        {
                            cout << department.first << "\t\t";
                        }
                        else if (uppercaseColumns[i] == "COMPANYID")
                        {
                            cout << department.second.getCompanyId() << "\t\t";
                        }
                        else if (uppercaseColumns[i] == "MANAGEDBY")
                        {
                            cout << department.second.getManagedBy() << "\t\t";
                        }
                        else if (uppercaseColumns[i] == "NAME")
                        {
                            cout << department.second.getName() << "\t\t";
                        }
                        else if (uppercaseColumns[i] == "LOCATION")
                        {
                            cout << department.second.getLocation() << "\t\t";
                        }
                        else
                        {
                            cout << "Invalid columns: Departments table's only columns are:\nid, companyId, managedBy, name, location" << endl;
                            exit(0);
                        }

                        if (i == uppercaseColumns.size() - 1)
                        {
                            cout << endl;
                        }
                    }
                }
            }
        }
        cout << "departments table selected!" << endl;
    }
    break;
    case 3:
    {
        if (deconstructedColumns[0] == "*")
        {
            cout << "ID\t\tNAME" << endl;
            for (const auto &company : companies)
            {
                cout << company.first << "\t\t" << company.second.getName() << endl;
            }
        }
        else
        {
            for (int i = 0; i < departments.size(); i++)
            {
                vector<string> uppercaseColumns;
                // print column headers
                if (i == 0)
                {
                    for (const auto &entry : deconstructedColumns)
                    {
                        string *uppercase = toUppercase(entry);
                        uppercaseColumns.push_back(*uppercase);
                        cout << *uppercase << "\t\t";
                    }
                    cout << endl;
                }

                // OPTIMIZATION: remove double for-loop
                // loop through table and print desired columns
                for (const auto &company : companies)
                {
                    for (int i = 0; i < uppercaseColumns.size(); i++)
                    {
                        if (uppercaseColumns[i] == "ID")
                        {
                            cout << company.first << "\t\t";
                        }
                        else if (uppercaseColumns[i] == "NAME")
                        {
                            cout << company.second.getName() << "\t\t";
                        }
                        else
                        {
                            cout << "Invalid columns: Companies table's only columns are:\nid, name" << endl;
                            exit(0);
                        }

                        if (i == uppercaseColumns.size() - 1)
                        {
                            cout << endl;
                        }
                    }
                }
            }
        }
        cout << "companies table selected!" << endl;
    }
    break;
    default:
        cout << "How did you get here?" << endl;
        exit(0);
        break;
    }
}

void create(int tableSelected, string &_values)
{
    // OPTIMIZATION: this can be a method BELOW
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

    // Formatting deconstructedQuery to be validated
    for (int i = 0; i < deconstructedQuery.size(); i++)
    {
        if (i == 0)
        {
            deconstructedQuery[0].erase(0, 1);
        }

        if (i == deconstructedQuery.size() - 1)
        {
            deconstructedQuery[i].erase(deconstructedQuery[i].find_last_not_of(";") + 1);
            deconstructedQuery[i].erase(deconstructedQuery[i].find_last_not_of(")") + 1);
        }
    }
    // OPTIMIZATION: this can be a method ABOVE

    switch (tableSelected)
    {
    case 1:
    {
        if (deconstructedQuery.size() == 5)
        {
            int id = processInt(deconstructedQuery[0]);
            int departmentId = processInt(deconstructedQuery[1]);
            string *firstName = processString(deconstructedQuery[2]);
            string *lastName = processString(deconstructedQuery[3]);
            string *jobTitle = processString(deconstructedQuery[4]);

            employees.insert(pair<int, Employee>(id, Employee(id, departmentId, *firstName, *lastName, *jobTitle)));

            for (const auto &entry : employees)
            {
                cout << "Employee ID: " << entry.first << ", First Name: " << entry.second.getFirstName() << endl;
            }

            cout << "Created Employee!" << _values << endl;
        }
        else
        {
            cout << "DID NOT Created Employee!" << _values << endl;
        }
    }
    break;

    case 2:
    {
        if (deconstructedQuery.size() == 5)
        {
            int id = processInt(deconstructedQuery[0]);
            int companyId = processInt(deconstructedQuery[1]);
            int managedBy = processInt(deconstructedQuery[2]);
            string *name = processString(deconstructedQuery[3]);
            string *location = processString(deconstructedQuery[4]);

            departments.insert(pair<int, Department>(id, Department(id, companyId, managedBy, *name, *location)));

            for (const auto &entry : departments)
            {
                cout << "Department ID: " << entry.first << ", Name: " << entry.second.getManagedBy() << endl;
            }

            cout << "Created Department!" << _values << endl;
        }
        else
        {
            cout << "DID NOT Created Department!" << _values << endl;
        }
    }

    break;

    case 3:
    {
        if (deconstructedQuery.size() == 2)
        {
            int id = processInt(deconstructedQuery[0]);
            string *name = processString(deconstructedQuery[1]);

            companies.insert(pair<int, Company>(id, Company(id, *name)));
            for (const auto &entry : companies)
            {
                cout << "Company ID: " << entry.first << ", Name: " << entry.second.getName() << endl;
            }
            cout << "Created Company!" << _values << endl;
        }
        else
        {
            cout << "DID NOT Created Company!" << _values << endl;
        }
    }
    break;

    default:
        cout << "I don't even know how you got here!" << endl;
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

    // Format operator to be capitalized
    string *uppercaseOperator = toUppercase(deconstructedQuery[0]);

    // Search for the target word within the vector
    size_t fromPosition = std::string::npos;
    for (size_t i = 0; i < deconstructedQuery.size(); ++i)
    {
        // OPTIMIZATION: ERROR HANDLING: "from" needs to be uppercased but like howd i find it do i just assume?
        if (deconstructedQuery[i] == "from")
        {
            fromPosition = i;
            table = deconstructedQuery[fromPosition + 1];
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
                // check validity of VALUES (...)
                // find position of ( and then find position of ) THEN concat THEN send as props for create()
                string values;
                size_t pos1 = std::string::npos;
                size_t pos2 = std::string::npos;
                string valueString;
                for (int i = 4; i < deconstructedQuery.size(); i++)
                {
                    // Ensure that right after VALUES comes the (...)
                    // OPTIMIZATION: figure out error handling here bc it still proceeds to look for pos2
                    if (deconstructedQuery[4].find_first_of('(') == 0 && pos1 == std::string::npos)
                    {
                        pos1 = i;
                    }

                    // Append values
                    if (pos1 != std::string::npos)
                    {
                        valueString.append(deconstructedQuery[i]);
                    }

                    // Find when it ends
                    if (deconstructedQuery[i].find_last_of(')') == deconstructedQuery[i].length() - 1 || (deconstructedQuery[i].find_last_of(')') == deconstructedQuery[i].length() - 2 && deconstructedQuery[i].find_last_of(';') == deconstructedQuery[i].length() - 1))
                    {
                        pos2 = i;
                        break;
                    }
                }

                if (pos1 == std::string::npos || pos2 == std::string::npos)
                {
                    cout << "Invalid VALUES missing either '(' or ')'" << endl;
                    exit(0);
                }

                if (table == "employees")
                {
                    create(1, valueString);
                }
                if (table == "departments")
                {
                    create(2, valueString);
                }
                if (table == "companies")
                {
                    create(3, valueString);
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
        string columns;
        size_t pos1 = std::string::npos;
        string columnString;
        for (int i = 1; i < fromPosition; i++)
        {
            // Ensure that right after VALUES comes the (...)
            // OPTIMIZATION: figure out error handling here bc it still proceeds to look for pos2
            if (deconstructedQuery[1] != "from" && pos1 == std::string::npos)
            {
                pos1 = i;
            }

            columnString.append(deconstructedQuery[i]);
        }
        table.erase(table.find_last_not_of(';') + 1);
        if (table == "employees")
        {
            select(1, columnString);
        }
        if (table == "departments")
        {
            select(2, columnString);
        }
        if (table == "companies")
        {
            select(3, columnString);
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

    // Populate tables
    companies.insert(pair<int, Company>(1000, Company(1000, "Apple")));
    companies.insert(pair<int, Company>(1001, Company(1001, "Microsoft")));

    departments.insert(pair<int, Department>(2000, Department(2000, 1000, 3000, "Finance", "New York")));
    departments.insert(pair<int, Department>(2001, Department(2001, 1000, 3001, "Engineering", "New York")));
    departments.insert(pair<int, Department>(2002, Department(2002, 1000, 3002, "Design", "Los Angeles")));
    departments.insert(pair<int, Department>(2003, Department(2003, 1001, 3003, "Design", "Montreal")));
    departments.insert(pair<int, Department>(2004, Department(2004, 1001, 3004, "Engineering", "New York")));

    employees.insert(pair<int, Employee>(3000, Employee(3000, 2000, "Allan", "Lopez", "Manager")));
    employees.insert(pair<int, Employee>(3001, Employee(3001, 2001, "Jacob", "Smith", "Manager")));
    employees.insert(pair<int, Employee>(3002, Employee(3002, 2002, "Elena", "Stroop", "Manager")));
    employees.insert(pair<int, Employee>(3003, Employee(3003, 2003, "Victor", "Kiltz", "Manager")));
    employees.insert(pair<int, Employee>(3004, Employee(3004, 2004, "Ting", "Chen", "Manager")));
    employees.insert(pair<int, Employee>(3005, Employee(3005, 2002, "Justine", "Khan", "Designer")));
    employees.insert(pair<int, Employee>(3006, Employee(3006, 2000, "Edgar", "Mohamed", "Finance")));
    employees.insert(pair<int, Employee>(3007, Employee(3007, 2000, "Fiona", "Appleton", "Finance")));
    employees.insert(pair<int, Employee>(3008, Employee(3008, 2001, "Manon", "Messier", "Engineer")));
    employees.insert(pair<int, Employee>(3009, Employee(3009, 2003, "Katelyn", "Ronston", "Designer")));
    employees.insert(pair<int, Employee>(3010, Employee(3010, 2004, "Paul", "Patel", "Engineer")));
    employees.insert(pair<int, Employee>(3011, Employee(3011, 2001, "Lucas", "Strong", "Engineer")));

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