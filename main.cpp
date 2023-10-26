#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

string addSpaces(const string &_string)
{
    size_t maxWidth = 16;
    if (_string.length() >= maxWidth)
    {
        return _string;
    }

    size_t spacesToAdd = maxWidth - _string.length();

    string spaces(spacesToAdd, ' ');

    string spacedString = _string + spaces;
    return spacedString;
}

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
    Employee()
    {
        // OPTIMIZATION: KEEP TRACK OF ID TO AUTOMATICALLY ASSIGN ID WITHOUT CHECKING FOR DUPS
        id = 0;
        departmentId = 0;
        firstName = "_firstName";
        lastName = "_lastName";
        jobTitle = "_jobTitle";
    }

    int getId() const
    {
        return id;
    }
    void setDepartmentId(int _departmentId)
    {
        departmentId = _departmentId;
    }
    int getDepartmentId() const
    {
        return departmentId;
    }
    void setFirstName(const string &_firstName)
    {
        firstName = _firstName;
    }
    const string &getFirstName() const
    {
        return firstName;
    }
    void setLastName(const string &_lastName)
    {
        lastName = _lastName;
    }
    const string &getLastName() const
    {
        return lastName;
    }
    void setJobTitle(const string &_jobTitle)
    {
        jobTitle = _jobTitle;
    }
    const string &getJobTitle() const
    {
        return jobTitle;
    }

    void printEmployee()
    {
        cout << id << "\t\t" << departmentId << "\t\t" << addSpaces(firstName) << addSpaces(lastName) << addSpaces(jobTitle) << endl;
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
    Department()
    {
        // OPTIMIZATION: KEEP TRACK OF ID TO AUTOMATICALLY ASSIGN ID WITHOUT CHECKING FOR DUPS
        id = 0;
        companyId = 0;
        managedBy = 0;
        name = "_name";
        location = "_location";
    }

    int getId() const
    {
        return id;
    }
    void setCompanyId(int _companyId)
    {
        companyId = _companyId;
    }
    int getCompanyId() const
    {
        return companyId;
    }
    void setManagedBy(int _managedBy)
    {
        managedBy = _managedBy;
    }
    int getManagedBy() const
    {
        return managedBy;
    }
    void setName(const string &_name)
    {
        name = _name;
    }
    const string &getName() const
    {
        return name;
    }
    void setLocation(const string &_location)
    {
        location = _location;
    }
    const string &getLocation() const
    {
        return location;
    }
    void printDepartment()
    {
        cout << id << "\t\t" << companyId << "\t\t" << managedBy << "\t\t" << addSpaces(name) << addSpaces(location) << endl;
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
    int getId() const
    {
        return id;
    }
    void setName(const string &_name)
    {
        name = _name;
    }
    const string &getName() const
    {
        return name;
    }
    void printCompany()
    {
        cout << id << "\t\t" << addSpaces(name) << endl;
    }
};

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

void deleteFrom(int tableSelected, int _id)
{
    ofstream f4;
    ifstream f5;
    switch (tableSelected)
    {
    case 1:
    {
        Employee e;
        int flag = 0;

        f5.open("Employees.dat", ios::binary); // read mode
        f4.open("temp.dat", ios::binary);      // write mode

        while (!f5.eof())
        {
            if (f5.read(reinterpret_cast<char *>(&e), sizeof(e)))
            {
                if (_id != e.getId())
                {
                    f4.write(reinterpret_cast<char *>(&e), sizeof(e));
                }
                else
                    flag = 1;
            }
        }

        f5.close();
        f4.close();
        remove("Employees.dat");
        rename("temp.dat", "Employees.dat");

        flag == 1 ? cout << "Employee deleted!" << endl : cout << "No employee found!" << endl;
    }
    break;
    case 2:
    {
        Department d;
        int flag = 0;

        f5.open("Departments.dat", ios::binary); // read mode
        f4.open("temp.dat", ios::binary);        // write mode

        while (!f5.eof())
        {
            if (f5.read(reinterpret_cast<char *>(&d), sizeof(d)))
            {
                if (_id != d.getId())
                {
                    f4.write(reinterpret_cast<char *>(&d), sizeof(d));
                }
                else
                    flag = 1;
            }
        }

        f5.close();
        f4.close();
        remove("Departments.dat");
        rename("temp.dat", "Departments.dat");

        flag == 1 ? cout << "Department deleted!" << endl : cout << "No department found!" << endl;
    }
    break;
    case 3:
    {
        Company c;
        int flag = 0;

        f5.open("Companies.dat", ios::binary); // read mode
        f4.open("temp.dat", ios::binary);      // write mode

        while (!f5.eof())
        {
            if (f5.read(reinterpret_cast<char *>(&c), sizeof(c)))
            {
                if (_id != c.getId())
                {
                    f4.write(reinterpret_cast<char *>(&c), sizeof(c));
                }
                else
                    flag = 1;
            }
        }

        f5.close();
        f4.close();
        remove("Companies.dat");
        rename("temp.dat", "Companies.dat");

        flag == 1 ? cout << "Company deleted!" << endl : cout << "No company found!" << endl;
    }
    break;
    default:
    {
        cout << "HOW>?!" << endl;
        exit(0);
    }
    break;
    }
}

void update(int tableSelected, vector<string> _columns, vector<string> _values)
{
    fstream f6;
    string empId = _values[_values.size() - 1];
    int validId = processInt(empId);
    switch (tableSelected)
    {
    case 1:
    {
        Employee e;
        f6.open("Employees.dat", ios::binary | ios::out | ios::in);
        while (!f6.eof())
        {
            if (f6.read(reinterpret_cast<char *>(&e), sizeof(e)))
            {
                if (e.getId() == validId)
                {
                    for (int i = 0; i < _columns.size(); i++)
                    {
                        if (_columns[i] == "DEPARTMENTID")
                        {
                            int check = processInt(_values[i]);
                            e.setDepartmentId(check);
                        }
                        else if (_columns[i] == "FIRSTNAME")
                        {
                            string *check = processString(_values[i]);
                            e.setFirstName(*check);
                        }

                        else if (_columns[i] == "LASTNAME")
                        {
                            string *check = processString(_values[i]);
                            e.setLastName(*check);
                        }
                        else if (_columns[i] == "JOBTITLE")
                        {
                            string *check = processString(_values[i]);
                            e.setJobTitle(*check);
                        }
                        else if (_columns[i] == "ID")
                        {
                            // cout << "ID: " << _values[i] << endl;
                        }
                        else
                        {
                            cout << "Invalid column name!" << endl;
                        }
                    }
                    int pos = -1 * sizeof(e);
                    f6.seekp(pos, ios::cur);
                    f6.write(reinterpret_cast<char *>(&e), sizeof(e));
                    cout << "Employee successfully updated!" << endl;
                    return;
                }
            }
        }
        f6.close();
    }
    break;
    case 2:
    {
        Department d;
        f6.open("Departments.dat", ios::binary | ios::out | ios::in);
        while (!f6.eof())
        {
            if (f6.read(reinterpret_cast<char *>(&d), sizeof(d)))
            {
                if (d.getId() == validId)
                {
                    for (int i = 0; i < _columns.size(); i++)
                    {
                        if (_columns[i] == "COMPANYID")
                        {
                            int check = processInt(_values[i]);
                            d.setCompanyId(check);
                        }
                        else if (_columns[i] == "MANAGEDBY")
                        {
                            int check = processInt(_values[i]);
                            d.setManagedBy(check);
                        }

                        else if (_columns[i] == "NAME")
                        {
                            string *check = processString(_values[i]);
                            d.setName(*check);
                        }
                        else if (_columns[i] == "LOCATION")
                        {
                            string *check = processString(_values[i]);
                            d.setLocation(*check);
                        }
                        else if (_columns[i] == "ID")
                        {
                            // cout << "ID: " << _values[i] << endl;
                        }
                        else
                        {
                            cout << "Invalid column name!" << endl;
                        }
                    }
                    int pos = -1 * sizeof(d);
                    f6.seekp(pos, ios::cur);
                    f6.write(reinterpret_cast<char *>(&d), sizeof(d));
                    cout << "Department successfully updated!" << endl;
                    return;
                }
            }
        }
        f6.close();
    }
    break;
    case 3:
    {
        Company c;
        f6.open("Companies.dat", ios::binary | ios::out | ios::in);
        while (!f6.eof())
        {
            if (f6.read(reinterpret_cast<char *>(&c), sizeof(c)))
            {
                if (c.getId() == validId)
                {
                    for (int i = 0; i < _columns.size(); i++)
                    {
                        if (_columns[i] == "NAME")
                        {
                            string *check = processString(_values[i]);
                            c.setName(*check);
                        }
                        else if (_columns[i] == "ID")
                        {
                            // cout << "ID: " << _values[i] << endl;
                        }
                        else
                        {
                            cout << "Invalid column name!" << endl;
                        }
                    }
                    int pos = -1 * sizeof(c);
                    f6.seekp(pos, ios::cur);
                    f6.write(reinterpret_cast<char *>(&c), sizeof(c));
                    cout << "Company successfully updated!" << endl;
                    return;
                }
            }
        }
        f6.close();
    }
    break;
    default:
        cout << "Why are you here?" << endl;
        exit(0);
        break;
    }
}

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

    ifstream f2;

    switch (tableSelected)
    {
    case 1:
    {
        Employee e;
        f2.open("Employees.dat", ios::binary);
        if (deconstructedColumns[0] == "*")
        {

            cout << addSpaces("ID") << addSpaces("DEPARTMENTID") << addSpaces("FIRSTNAME") << addSpaces("LASTNAME") << addSpaces("JOBTITLE") << endl;
            while (!f2.eof())
            {
                if (f2.read(reinterpret_cast<char *>(&e), sizeof(e)))
                {
                    e.printEmployee();
                }
            };
            f2.close();
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
                        cout << addSpaces(*uppercase);
                    }
                    cout << endl;
                }
                while (!f2.eof())
                {
                    if (f2.read(reinterpret_cast<char *>(&e), sizeof(e)))
                    {
                        for (int i = 0; i < uppercaseColumns.size(); i++)
                        {
                            if (uppercaseColumns[i] == "ID")
                            {
                                cout << e.getId() << "\t\t";
                            }
                            else if (uppercaseColumns[i] == "DEPARTMENTID")
                            {
                                cout << e.getDepartmentId() << "\t\t";
                            }
                            else if (uppercaseColumns[i] == "FIRSTNAME")
                            {
                                cout << addSpaces(e.getFirstName());
                            }
                            else if (uppercaseColumns[i] == "LASTNAME")
                            {
                                cout << addSpaces(e.getLastName());
                            }
                            else if (uppercaseColumns[i] == "JOBTITLE")
                            {
                                cout << addSpaces(e.getJobTitle());
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
                };
                f2.close();
            }
        }
        cout << "\nEmployees table selected!" << endl;
    }
    break;
    case 2:
    {
        Department d;
        f2.open("Departments.dat", ios::binary);
        if (deconstructedColumns[0] == "*")
        {
            cout << addSpaces("ID") << addSpaces("COMPANYID") << addSpaces("MANAGEDBY") << addSpaces("NAME") << addSpaces("LOCATION") << endl;
            while (!f2.eof())
            {
                if (f2.read(reinterpret_cast<char *>(&d), sizeof(d)))
                {
                    d.printDepartment();
                }
            };
            f2.close();
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
                        cout << addSpaces(*uppercase);
                    }
                    cout << endl;
                }

                // OPTIMIZATION: remove double for-loop
                // loop through table and print desired columns
                while (!f2.eof())
                {
                    if (f2.read(reinterpret_cast<char *>(&d), sizeof(d)))
                    {
                        for (int i = 0; i < uppercaseColumns.size(); i++)
                        {
                            if (uppercaseColumns[i] == "ID")
                            {
                                cout << d.getId() << "\t\t";
                            }
                            else if (uppercaseColumns[i] == "COMPANYID")
                            {
                                cout << d.getCompanyId() << "\t\t";
                            }
                            else if (uppercaseColumns[i] == "MANAGEDBY")
                            {
                                cout << d.getManagedBy() << "\t\t";
                            }
                            else if (uppercaseColumns[i] == "NAME")
                            {
                                cout << addSpaces(d.getName());
                            }
                            else if (uppercaseColumns[i] == "LOCATION")
                            {
                                cout << addSpaces(d.getLocation());
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
                };
                f2.close();
            }
        }

        cout << "\nDepartments table selected!" << endl;
    }
    break;
    case 3:
    {
        Company c;
        f2.open("Companies.dat", ios::binary);
        if (deconstructedColumns[0] == "*")
        {
            cout << addSpaces("ID") << addSpaces("NAME") << endl;
            while (!f2.eof())
            {
                if (f2.read(reinterpret_cast<char *>(&c), sizeof(c)))
                {
                    c.printCompany();
                }
            };
            f2.close();
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
                        cout << addSpaces(*uppercase) << "\t\t";
                    }
                    cout << endl;
                }

                // OPTIMIZATION: remove double for-loop
                // loop through table and print desired columns
                while (!f2.eof())
                {
                    if (f2.read(reinterpret_cast<char *>(&c), sizeof(c)))
                    {
                        for (int i = 0; i < uppercaseColumns.size(); i++)
                        {
                            if (uppercaseColumns[i] == "ID")
                            {
                                cout << c.getId() << "\t\t";
                            }
                            else if (uppercaseColumns[i] == "NAME")
                            {
                                cout << addSpaces(c.getName()) << "\t\t";
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
                };
                f2.close();
            }
        }

        cout << "\nCompanies table selected!" << endl;
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

            ofstream f1;
            Employee e = Employee(id, departmentId, *firstName, *lastName, *jobTitle);

            f1.open("Employees.dat", ios::binary | ios::app);
            f1.write(reinterpret_cast<char *>(&e), sizeof(e));
            f1.close();

            employees.insert(pair<int, Employee>(id, Employee(id, departmentId, *firstName, *lastName, *jobTitle)));

            cout << "\nCreated Employee!" << endl;
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

            ofstream f1;
            Department d = Department(id, companyId, managedBy, *name, *location);

            f1.open("Departments.dat", ios::binary | ios::app);
            f1.write(reinterpret_cast<char *>(&d), sizeof(d));
            f1.close();

            departments.insert(pair<int, Department>(id, Department(id, companyId, managedBy, *name, *location)));

            cout << addSpaces("ID") << addSpaces("COMPANYID") << addSpaces("MANAGEDBY") << addSpaces("NAME") << addSpaces("LOCATION") << endl;
            for (const auto &department : departments)
            {
                cout << department.first << "\t\t" << department.second.getCompanyId() << "\t\t" << department.second.getManagedBy() << "\t\t" << addSpaces(department.second.getName()) << addSpaces(department.second.getLocation()) << endl;
            }

            cout << "\nCreated Department!" << endl;
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
            ofstream f1;
            Company c = Company(id, *name);

            f1.open("Companies.dat", ios::binary | ios::app);
            f1.write(reinterpret_cast<char *>(&c), sizeof(c));
            f1.close();

            companies.insert(pair<int, Company>(id, Company(id, *name)));

            cout << addSpaces("ID") << addSpaces("NAME") << endl;
            for (const auto &company : companies)
            {
                cout << company.first << "\t\t" << addSpaces(company.second.getName()) << endl;
            }
            cout << "\nCreated Company!" << endl;
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
        string *setCheck = toUppercase(deconstructedQuery[2]);
        if (*setCheck == "SET")
        {
            vector<string> columns;
            vector<string> values;
            size_t wherePos = std::string::npos;
            string findId;
            string appendedString;

            for (int i = 3; i < deconstructedQuery.size(); i++)
            {
                if (wherePos == std::string::npos)
                {
                    // look for where and when to stop
                    if (deconstructedQuery[i] == "where")
                    {
                        wherePos = i;
                    }
                    else
                    {
                        appendedString.append(deconstructedQuery[i]);
                    }
                }
                else
                {
                    // format id=<number>
                    findId.append(deconstructedQuery[i]);
                    // append to stringToProcess
                    if (i == deconstructedQuery.size() - 1)
                    {
                        if (findId[findId.length() - 1] == ';')
                        {
                            findId.erase(findId.length() - 1);
                        }
                        appendedString.append(",");
                        appendedString.append(findId);
                    }
                }
            }

            vector<std::string> tokens;
            istringstream ss(appendedString);
            string token;
            while (std::getline(ss, token, ','))
            {
                tokens.push_back(token); // Split and store the parts
            }

            for (const auto &entry : tokens)
            {
                // cout << "entry: " << entry << endl;
                size_t equalSignPos = std::string::npos;
                equalSignPos = entry.find('=');

                if (equalSignPos != std::string::npos)
                {
                    string *uppercaseColumn = toUppercase(entry.substr(0, equalSignPos));
                    columns.push_back(*uppercaseColumn);
                    values.push_back(entry.substr(equalSignPos + 1));
                }
                else
                {
                    cout << "Error: No '=' between column and value? is it where?" << entry << endl;
                    exit(0);
                }
            }

            table = deconstructedQuery[1];
            if (table == "employees")
            {
                update(1, columns, values);
            }
            if (table == "departments")
            {
                update(2, columns, values);
            }
            if (table == "companies")
            {
                update(3, columns, values);
            }
        }
        else
        {
            cout << "Invalid SQL: UPDATE <table> SET col1=val1,..." << endl;
        }
    }
    else if (*uppercaseOperator == "DELETE")
    {
        table = deconstructedQuery[2];
        string stringId;
        string temp;
        size_t semiPos = std::string::npos;
        for (int i = 4; i < deconstructedQuery.size(); i++)
        {

            semiPos = deconstructedQuery[i].find(';');
            if (semiPos != std::string::npos)
            {
                temp = deconstructedQuery[i].substr(0, semiPos);
                stringId.append(temp);
            }
            else
            {
                stringId.append(deconstructedQuery[i]);
            }
        }

        size_t equalPos = stringId.find('=');
        string id = stringId.substr(equalPos + 1);
        int validId = processInt(id);

        if (table == "employees")
        {
            deleteFrom(1, validId);
        }
        if (table == "departments")
        {
            deleteFrom(2, validId);
        }
        if (table == "companies")
        {
            deleteFrom(3, validId);
        }
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
    cout << "\n\n\n* WELCOME TO THE COMPANY DATABASE *" << endl;
    cout << "===================================" << endl;
    cout << "Company Database Structure:" << endl;
    cout << "\nCompanies" << endl;
    cout << "--ID" << endl;
    cout << "--NAME" << endl;
    cout << "Departments" << endl;
    cout << "--ID" << endl;
    cout << "--COMPANYID" << endl;
    cout << "--MANAGEDBY" << endl;
    cout << "--NAME" << endl;
    cout << "--LOCATION" << endl;
    cout << "Employees" << endl;
    cout << "--ID" << endl;
    cout << "--DEPARTMENTID" << endl;
    cout << "--FIRSTNAME" << endl;
    cout << "--LASTNAME" << endl;
    cout << "--JOBTITLE" << endl;
    cout << "\n===================================" << endl;

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

    string sqlQuery;

    cout << "\nTo add a record to the database: " << endl;
    cout << "INSERT INTO <table> VALUES (value1,value2,...);" << endl;
    cout << "\nTo see records from database: " << endl;
    cout << "SELECT column1,column2,... FROM <table>;" << endl;
    cout << "\nTo update a record from database: " << endl;
    cout << "UPDATE <table> SET column1=value1,column2=value2,... WHERE ID=1111;" << endl;
    cout << "\nTo delete a record from database: " << endl;
    cout << "DELETE FROM <table> WHERE ID=1111;" << endl;
    cout << "\n===================================" << endl;

    cout << "\nENTER SQL QUERY:" << endl;

    // ifstream f2;
    // f2.open("Companies.dat", ios::binary);

    // cout << "\n=======================================\n";
    // cout << "LIST OF EMPLOYEES";
    // cout << "\n=======================================\n";

    // Company e;
    // while (!f2.eof())
    // {
    //     if (f2.read(reinterpret_cast<char *>(&e), sizeof(e)))
    //     {
    //         e.printCompany();
    //         cout << "\n=======================================\n";
    //     }
    // };
    // f2.close();

    getline(cin, sqlQuery);
    cout << endl;
    processSQL(sqlQuery);

    return 0;
}