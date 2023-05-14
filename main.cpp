#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include <list>

// Display Employee
#define ID_SPACE 5
#define NAME_SPACE 25
#define DATE_SPACE 15
#define GENDER_SPACE 10
#define PHONE_SPACE 15
#define POSITION_SPACE 15
#define WORK_AT_SPACE 15

// Display Department

// Regulation
#define PHONE_LENGTH 10

using namespace std;


struct EmployeeInfo
{
    unsigned int id = 0;
    string name;
    string date;
    string gender;
    string phone;
    string position;
    unsigned int departmentID = 0;
};

struct DepartmentInfo
{
    unsigned int id = 0;
    string name;
    unsigned int manager_id = 0;
    string manager_name;
};

struct Salary {
    unsigned int id = 0;
    string name;
    string month;
    double income = 0;
    double bonus = 0;
    double salary = 0;
};

struct Timekeeping {
    unsigned int id = 0;
    string name;
    unsigned int days = 0;
    string month;
};

template <typename T>
struct Node
{
    T data;
    Node<T>* next = NULL;
    Node<T>* prev = NULL;
};

template <typename T>
struct List
{
private:
    Node<T>* head = NULL;
    Node<T>* tail = NULL;
    int len;

public:
    List()
    {
        head = NULL;
        tail = NULL;
        len = 0;
    }
    int isEmpty() { return head == NULL; }
    int getLen() { return len; }
    Node<T>* getHead() { return head; }
    Node<T>* getTail() { return tail; }

    // Ham lay phan tu trong List
    Node<T>* getItem(int ps)
    {
        if (ps > len || ps <= 0)
        {
            return NULL;
        }
        else
        {
            if (ps <= len / 2)
            {
                Node<T>* q = head;
                for (int i = 0; i < ps - 1; i++)
                {
                    if (q->next == NULL)
                    {
                        return q;
                    }
                    q = q->next;
                }
                return q;
            }
            else
            {
                Node<T>* q = tail;
                for (int i = len; i > ps; i--)
                {
                    if (q->prev == NULL)
                    {
                        return q;
                    }
                    q = q->prev;
                }
                return q;
            }
        }
    }

    Node<T>* getFirstItem()
    {
        Node<T>* p = head;
        return p;
    }

    Node<T>* getLastItem()
    {
        Node<T>* p = tail;
        return p;
    }

    // Ham them phan tu
    int addFirst(T x)
    {
        Node<T>* p = new Node<T>();
        p->data = x;
        p->prev = NULL;
        if (head != NULL)
        {
            p->next = head;
        }
        head = p;
        len++;
        return 1;
    }

    int addLast(T x)
    {
        Node<T>* p = new Node<T>();
        p->data = x;
        p->next = NULL;
        p->prev = tail;
        if (tail != NULL)
        {
            tail->next = p;
        }
        else
        {
            head = p;
        }
        tail = p;
        len++;
        return 1;
    }

    int addItem(Node<T>* p, T x)
    {
        Node<T>* q = new Node<T>();
        q->data = x;
        if (p != NULL)
        {
            q->prev = p;
            q->next = p->next;
            if (p->next != NULL)
            {
                q->next->prev = q;
                q->prev->next = q;
            }
        }
        else
        {
            q->next = head;
            head = q;
        }
        len++;
        return 1;
    }

    // Ham xoa phan tu
    int removeFirst()
    {
        Node<T>* p = head;
        if (p != NULL)
        {
            p->next->prev = p->prev;
            head = p->next;
            delete p;
            len--;
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int removeLast()
    {
        Node<T>* p = tail;
        if (p != NULL)
        {
            p->prev->next = NULL;
            tail = p->prev;
            delete p;
            len--;
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int removeItem(Node<T>* p)
    {
        if (head != NULL)
        {
            if (head == p)
            {
                removeFirst();
                return 1;
            }

            if (p->next != NULL)
            {
                Node<T>* q = head;
                while (q->next != p)
                {
                    q = q->next;
                }
                p->prev->next = p->next;
                p->next->prev = p->prev;
                delete p;
                len--;
                return 1;
            }
            else
            {
                removeLast();
                return 1;
            }
        }
        else
        {
            return 0;
        }
    }

    void removeAll()
    {
        if (head != NULL)
        {
            Node<T>* q = head;
            while (q->next != NULL)
            {
                Node<T>* tmp = q;
                q = q->next;
                delete tmp;
            }
            head = NULL;
            len = 0;
            delete q;
        }
        else
        {
            cout << "Empty list!!" << endl;
        }
    }

    // Ham cap nhat gia phan tu
    int updateItem(int p, T x)
    {
        if (p > len || p <= 0)
        {
            return 0;
        }
        if (head != NULL)
        {
            Node<T>* q = head;
            for (int i = 0; i < p - 1; i++)
            {
                q = q->next;
            }
            q->data = x;
            return 1;
        }
    }

    // Ham gop List
    void addRange(List<T>& list)
    {
        Node<T>* q = head;
        while (q->next != NULL)
        {
            q = q->next;
        }
        q->next = list.getHead();
    }
};

struct Company
{
    List<EmployeeInfo> listOfEmployee;
    List<DepartmentInfo> listOfDepartment;
    List<Timekeeping> listOfTimeKeeping;
    List<Salary> listOfSalary;
};

// ------ Local Variable --------- //

// -------- Declare Functions ----------//

void App(Company& company, bool& isRunning);

// -------- Interaction function
void pressAnyKey();
bool confirm();
void print(Company& company);

// Get item
EmployeeInfo getEmployeeByID(Company& company, unsigned int id);
DepartmentInfo getDepartmentByID(Company& company, unsigned int id);

// Handle Add New Item
int addNewEmployee(Company& company);
int addNewDepartment(Company& company);

// Handle Delete
int deleteEmployee(Company& company);
int deleteDepartment(Company& company);

// Handle Search
int searchEmployee(Company& company);
int searchDepartment(Company& company);

// Handle Update Information
int update(Company& company);

// Handle Arrange
int arrange(Company& company);

// Handle Budget
int budget(Company& company);
int payrollForMonth(Company& company);

// Handle Timekeeping
int timeKeeping(Company& company);

// Handle Format & Check
string formatName(string name);
bool checkPhoneInput(string phone);
bool hasEmployeeWithID(Company& company, unsigned int id);
bool hasEmployeeWithPosition(Company& company, string position);
bool hasDepartmentWithID(Company& company, unsigned int id);
bool hasDepartmentWithName(Company& company, string name);
bool hasTimekeepingWithID(Company& company, unsigned int id);
bool hasTimekeepingWithMonth(Company& company, string month);
bool hasTimekeepingWithIDandMonth(Company& company, unsigned int id, string month);
bool isValidDate(string input);
string toLower(string str);

// ------ Import/Export from files
int readDataFromFile(Company& company);
void writeDataToFile(Company& company);

// ------- Main ------ //
int main()
{
    Company company;
    readDataFromFile(company);
    bool isRunning = true;
    while (isRunning)
    {
        App(company, isRunning);
        system("cls");
    }
    return 0;
}
// Display
void App(Company& company, bool& isRunning)
{
    cout << "==========HUMAN RESOURCE MANAGEMENT======" << endl;
    cout << "=================MENU====================" << endl;
    cout << "*   1. Add new employee                 *" << endl; // done
    cout << "*   2. Delete employee                  *" << endl; // done
    cout << "*   3. Search employee                  *" << endl; // done
    cout << "*   4. Add new department               *" << endl; // done
    cout << "*   5. Delete department                *" << endl; // done
    cout << "*   6. Search department                *" << endl; // done
    cout << "*   7. Update information               *" << endl; // done
    cout << "*   8. Arrange                          *" << endl; // done
    cout << "*   9. Display                          *" << endl; // done
    cout << "*  10. Timekeeping                      *" << endl; // done
    cout << "*  11. Budget manager                   *" << endl; // done
    cout << "*  12. Export data to file              *" << endl; // done
    cout << "*   0. Exit                             *" << endl; // done
    cout << "=========================================" << endl;
    cout << "Input your select: ";
    int key;
    cin >> key;
    switch (key)
    {
    case 1:
        addNewEmployee(company);
        pressAnyKey();
        break;
    case 2:
        deleteEmployee(company);
        pressAnyKey();
        break;
    case 3:
        searchEmployee(company);
        pressAnyKey();
        break;
    case 4:
        addNewDepartment(company);
        pressAnyKey();
        break;
    case 5:
        deleteDepartment(company);
        pressAnyKey();
        break;
    case 6:
        searchDepartment(company);
        pressAnyKey();
        break;
    case 7:
        update(company);
        pressAnyKey();
        break;
    case 8:
        arrange(company);
        pressAnyKey();
        break;
    case 9:
        print(company);
        pressAnyKey();
        break;
    case 10:
        timeKeeping(company);
        pressAnyKey();
        break;
    case 11:
        budget(company);
        pressAnyKey();
        break;
    case 12:
        writeDataToFile(company);
        pressAnyKey();
        break;
    case 0:
        isRunning = false;
        cout << "Shutdown the program!";
        pressAnyKey();
        break;
    default:
        cout << "Without this function !!" << endl;
        pressAnyKey();
        break;
    }
}

// ----------------------- Interaction function----------------- //
void pressAnyKey()
{
    cout << endl;
    cout << "\nPress any key to back!";
    _getch();
    system("cls");
}

bool confirm()
{
    cout << "Are your sure ?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    bool isConfirm = false;
    bool isChose = false;
    int select;
    cin >> select;
    while (!isChose)
    {
        switch (select)
        {
        case 1:
            isConfirm = true;
            isChose = true;
            break;
        case 2:
            isConfirm = false;
            isChose = true;
            break;
        default:
            break;
        }
    }
    return isConfirm;
}

string trim(string str)
{
    string result = str;
    result.erase(0, result.find_first_not_of(' ')); 
    result.erase(result.find_last_not_of(' ') + 1); 
    return result;
}

// Print
void printAllEmployee(Company& company)
{
    Node<EmployeeInfo>* head = company.listOfEmployee.getHead();

    if (company.listOfEmployee.getLen() == 0)
    {
        cout << "Empty list !";
        return;
    }

    cout << setw(ID_SPACE) << "Id";
    cout << setw(NAME_SPACE) << "Name";
    cout << setw(DATE_SPACE) << "Date";
    cout << setw(GENDER_SPACE) << "Gender";
    cout << setw(PHONE_SPACE) << "Phone number";
    cout << setw(POSITION_SPACE) << "Position";
    cout << setw(WORK_AT_SPACE) << "Work at";
    cout << endl;
    for (int i = 0; i < company.listOfEmployee.getLen(); i++)
    {
        if (head != NULL)
        {
            cout << setw(ID_SPACE) << head->data.id;
            cout << setw(NAME_SPACE) << head->data.name;
            cout << setw(DATE_SPACE) << head->data.date;
            cout << setw(GENDER_SPACE) << head->data.gender;
            cout << setw(PHONE_SPACE) << head->data.phone;
            cout << setw(POSITION_SPACE) << head->data.position;
            cout << setw(WORK_AT_SPACE) << getDepartmentByID(company, head->data.departmentID).name;
            cout << endl;
        }
        head = head->next;
    }
}

void printEmployeeList(Company& company, List<EmployeeInfo>& list)
{
    Node<EmployeeInfo>* head = list.getHead();

    if (list.getLen() == 0)
    {
        cout << "Empty list !";
        return;
    }

    cout << setw(ID_SPACE) << "Id";
    cout << setw(NAME_SPACE) << "Name";
    cout << setw(DATE_SPACE) << "Date";
    cout << setw(GENDER_SPACE) << "Gender";
    cout << setw(PHONE_SPACE) << "Phone number";
    cout << setw(POSITION_SPACE) << "Position";
    cout << setw(WORK_AT_SPACE) << "Work at";
    cout << endl;
    for (int i = 0; i < list.getLen(); i++)
    {
        if (head != NULL)
        {
            cout << setw(ID_SPACE) << head->data.id;
            cout << setw(NAME_SPACE) << head->data.name;
            cout << setw(DATE_SPACE) << head->data.date;
            cout << setw(GENDER_SPACE) << head->data.gender;
            cout << setw(PHONE_SPACE) << head->data.phone;
            cout << setw(POSITION_SPACE) << head->data.position;
            cout << setw(WORK_AT_SPACE) << getDepartmentByID(company, head->data.departmentID).name;
            cout << endl;
        }
        head = head->next;
    }
}

void printEmployee(Company& company, EmployeeInfo employee)
{
    cout << setw(ID_SPACE) << "Id";
    cout << setw(NAME_SPACE) << "Name";
    cout << setw(DATE_SPACE) << "Date";
    cout << setw(GENDER_SPACE) << "Gender";
    cout << setw(PHONE_SPACE) << "Phone number";
    cout << setw(POSITION_SPACE) << "Position";
    cout << setw(WORK_AT_SPACE) << "Work at";
    cout << endl;
    cout << setw(ID_SPACE) << employee.id;
    cout << setw(NAME_SPACE) << employee.name;
    cout << setw(DATE_SPACE) << employee.date;
    cout << setw(GENDER_SPACE) << employee.gender;
    cout << setw(PHONE_SPACE) << employee.phone;
    cout << setw(POSITION_SPACE) << employee.position;
    cout << setw(WORK_AT_SPACE) << getDepartmentByID(company, employee.departmentID).name;
    cout << endl;
}

void printAllDepartment(Company& company)
{
    Node<DepartmentInfo>* head = company.listOfDepartment.getHead();

    if (company.listOfDepartment.getLen() == 0)
    {
        cout << "Empty list !";
        return;
    }

    cout << setw(ID_SPACE) << "ID";
    cout << setw(NAME_SPACE) << "Name";
    cout << setw(NAME_SPACE) << "Manager ID";
    cout << setw(NAME_SPACE) << "Manager name";
    cout << endl;
    for (int i = 0; i < company.listOfDepartment.getLen(); i++)
    {
        if (head != NULL)
        {
            cout << setw(ID_SPACE) << head->data.id;
            cout << setw(NAME_SPACE) << head->data.name;
            cout << setw(NAME_SPACE) << head->data.manager_id;
            cout << setw(NAME_SPACE) << head->data.manager_name;
            cout << endl;
        }
        head = head->next;
    }
}

void printDepartmentList(List<DepartmentInfo>& list)
{
    Node<DepartmentInfo>* head = list.getHead();

    if (list.getLen() == 0)
    {
        cout << "Empty list !";
        return;
    }

    cout << setw(ID_SPACE) << "ID";
    cout << setw(NAME_SPACE) << "Name";
    cout << setw(NAME_SPACE) << "Manager ID";
    cout << setw(NAME_SPACE) << "Manager name";
    cout << endl;
    for (int i = 0; i < list.getLen(); i++)
    {
        if (head != NULL)
        {
            cout << setw(ID_SPACE) << head->data.id;
            cout << setw(NAME_SPACE) << head->data.name;
            cout << setw(NAME_SPACE) << head->data.manager_id;
            cout << setw(NAME_SPACE) << head->data.manager_name;
            cout << endl;
        }
        head = head->next;
    }
}

void printDepartment(DepartmentInfo department)
{
    cout << setw(ID_SPACE) << "ID";
    cout << setw(NAME_SPACE) << "Name";
    cout << setw(NAME_SPACE) << "Manager ID";
    cout << setw(NAME_SPACE) << "Manager name";
    cout << endl;
    cout << setw(ID_SPACE) << department.id;
    cout << setw(NAME_SPACE) << department.name;
    cout << setw(NAME_SPACE) << department.manager_id;
    cout << setw(NAME_SPACE) << department.manager_name;
    cout << endl;
}

void printTimekeepingList(List<Timekeeping> &list) {
    Node<Timekeeping>* head = list.getHead();

    if (list.getLen() == 0)
    {
        cout << "Empty list !";
        return;
    }

    cout << setw(ID_SPACE) << "ID";
    cout << setw(NAME_SPACE) << "Name";
    cout << setw(DATE_SPACE) << "Month";
    cout << setw(DATE_SPACE) << "Days";
    cout << endl;
    for (int i = 0; i < list.getLen(); i++)
    {
        if (i > 10) {
            cout << list.getLen() - i << " " << "item more." << endl;
        }
        if (head != NULL)
        {
            cout << setw(ID_SPACE) << head->data.id;
            cout << setw(NAME_SPACE) << head->data.name;
            cout << setw(DATE_SPACE) << head->data.month;
            cout << setw(DATE_SPACE) << head->data.days;
            cout << endl;
        }
        head = head->next;
    }
}

void printSalaryForMonth(List<Salary>& list) {
    Node<Salary>* head = list.getHead();

    if (list.getLen() == 0)
    {
        cout << "Empty list !";
        return;
    }

    cout << setw(ID_SPACE) << "ID";
    cout << setw(NAME_SPACE) << "Name";
    cout << setw(DATE_SPACE) << "Month";
    cout << setw(DATE_SPACE) << "Income";
    cout << setw(DATE_SPACE) << "Bonus";
    cout << setw(DATE_SPACE) << "Total";
    cout << endl;
    for (int i = 0; i < list.getLen(); i++)
    {
        /*if (i > 10) {
            cout << list.getLen() - i << " " << "item more." << endl;
            break;
        }
        */
        if (head != NULL)
        {
            cout << setw(ID_SPACE) << head->data.id;
            cout << setw(NAME_SPACE) << head->data.name;
            cout << setw(DATE_SPACE) << head->data.month;
            cout << setw(DATE_SPACE) << head->data.income;
            cout << setw(DATE_SPACE) << head->data.bonus;
            cout << setw(DATE_SPACE) << head->data.salary;
            cout << endl;
        }
        head = head->next;
    }
}

void print(Company& company)
{
    bool isChose = false;
    int select;
    while (!isChose)
    {
        cout << "Chose a print option ?" << endl;
        cout << "1. Employee list" << endl;
        cout << "2. Department list" << endl;
        cout << "3. Timekeeping list" << endl;
        cout << "4. Back" << endl;
        cout << "Input your select: ";
        cin >> select;
        switch (select)
        {
        case 1:
            printAllEmployee(company);
            isChose = true;
            break;
        case 2:
            printAllDepartment(company);
            isChose = true;
            break;
        case 3:
            printTimekeepingList(company.listOfTimeKeeping);
            isChose = true;
            break;
        case 4:
            pressAnyKey();
            isChose = true;
            break;
        default:
            cout << "Invalid selection!" << endl;
            pressAnyKey();
            break;
        }
    }
}

// Handle Add New Employee
int addNewEmployee(Company& company)
{
    int n;
    cout << "Input number of new employee: ";
    cin >> n;
    while (n <= 0)
    {
        cout << "Invalid number!!" << endl;
        cout << "Input number of new employee: " << endl;
        cin >> n;
    }
    for (int i = 0; i < n; i++)
    {
        EmployeeInfo newEmployee;
        cout << "Employee " << i + 1 << endl;
        // Name
        cout << "Input employee name: ";
        cin.ignore();
        getline(cin, newEmployee.name);
        // Date
        cout << "Input employee date: ";
        getline(cin, newEmployee.date);
        while (!isValidDate(newEmployee.date)) {
            cout << "Invalid date!!" << endl;
            cout << "Input employee date: ";
            getline(cin, newEmployee.date);
        }
        cout << "Input employee gender: ";
        cout << endl;
        bool isChoseG = false;
        int selectG;
        while (!isChoseG)
        {
            cout << "1. Male" << endl;
            cout << "2. Female" << endl;
            cout << "3. Other" << endl;
            cout << "Input your select: ";
            cin >> selectG;
            switch (selectG)
            {
            case 1:
                isChoseG = true;
                newEmployee.gender = "Male";
                break;
            case 2:
                isChoseG = true;
                newEmployee.gender = "Female";
                break;
            case 3:
                isChoseG = true;
                newEmployee.gender = "Other";
                break;
            default:
                cout << "Invalid selection!";
                break;
            }
        }
        // Phone number
        cout << "Input employee phone: ";
        cin.ignore();
        getline(cin, newEmployee.phone);
        while (!checkPhoneInput(newEmployee.phone))
        {
            cout << "Input employee phone again: ";
            getline(cin, newEmployee.phone);
        }
        // Position
        cout << "Chose position: " << endl;
        bool isChoseP = false;
        int selectP;
        while (!isChoseP)
        {
            cout << "1. President" << endl;
            cout << "2. Manager" << endl;
            cout << "3. Employee" << endl;
            cout << "4. Customer" << endl;
            cout << "Input your select: ";
            cin >> selectP;
            switch (selectP)
            {
            case 1:
                isChoseP = true;
                newEmployee.position = "President";
                break;
            case 2:
                isChoseP = true;
                newEmployee.position = "Manager";
                break;
            case 3:
                isChoseP = true;
                newEmployee.position = "Employee";
                break;
            case 4:
                isChoseP = true;
                newEmployee.position = "Customer";
                break;
            default:
                cout << "Invalid selection!" << endl;
                break;
            }
        }
        cout << "Input department ID: ";
        cin >> newEmployee.departmentID;
        while (!hasDepartmentWithID(company, newEmployee.departmentID))
        {
            cout << "Haven't department with this ID!" << endl;
            cout << "Input department ID: ";
            cin >> newEmployee.departmentID;
        }

        // Format
        newEmployee.name = formatName(newEmployee.name);

        // Add
        newEmployee.id = company.listOfEmployee.getLen() + 1;

        printEmployee(company, newEmployee);

        if (!confirm())
        {
            cout << "Cancel !" << endl;
            return 0;
        }
        else
        {
            company.listOfEmployee.addFirst(newEmployee);
            cout << "Create new employee successful!" << endl;
        }
    }
    return 1;
}

// Handle get item
EmployeeInfo getEmployeeByID(Company& company, unsigned int id)
{
    Node<EmployeeInfo>* head = company.listOfEmployee.getHead();

    EmployeeInfo employee;
    if (head != NULL)
    {
        while (head != NULL)
        {
            if (head->data.id == id)
            {
                employee = head->data;
                break;
            }
            head = head->next;
        }
    }
    return employee;
}

DepartmentInfo getDepartmentByID(Company& company, unsigned int id) {
    Node<DepartmentInfo>* head = company.listOfDepartment.getHead();

    DepartmentInfo department;
    if (head != NULL)
    {
        while (head != NULL)
        {
            if (head->data.id == id)
            {
                department = head->data;
                break;
            }
            head = head->next;
        }
    }
    return department;
}

Timekeeping getTimekeepingByID(Company& company, unsigned int id) {
    Node<Timekeeping>* head = company.listOfTimeKeeping.getHead();

    Timekeeping timekeeping;
    if (head != NULL)
    {
        while (head != NULL)
        {
            if (head->data.id == id)
            {
                timekeeping = head->data;
                break;
            }
            head = head->next;
        }
    }
    return timekeeping;
}

Timekeeping getTimekeepingByIDandMonth(Company& company, unsigned int id, string month) {
    Node<Timekeeping>* head = company.listOfTimeKeeping.getHead();

    Timekeeping timekeeping;
    if (head != NULL)
    {
        while (head != NULL)
        {
            if (head->data.id == id && head->data.month.find(month) != string::npos)
            {
                timekeeping = head->data;
                break;
            }
            head = head->next;
        }
    }
    return timekeeping;
}

// Handle Add New Department
int addNewDepartment(Company& company)
{
    DepartmentInfo newDepartment;
    EmployeeInfo manager;
    // Name
    cout << "Input department name: ";
    cin.ignore();
    getline(cin, newDepartment.name);

    if (hasDepartmentWithName(company, newDepartment.name)) {
        cout << "Departments already exist" << endl;
        return 0;
    }

    newDepartment.name = formatName(newDepartment.name);
    // Manager
    unsigned int id;
    cout << "Input ID of manager: ";
    cin >> id;
    while (hasEmployeeWithID(company, id) == false)
    {
        cout << "Can't find this manager ID!";
        cout << "Input manager ID again: ";
        cin >> id;
    }
    manager = getEmployeeByID(company, id);
    newDepartment.id = company.listOfDepartment.getLen() + 1;
    newDepartment.manager_name = manager.name;
    newDepartment.manager_id = manager.id;
    company.listOfDepartment.addLast(newDepartment);
    cout << "Create new department successful!!" << endl;
    printDepartment(newDepartment);
    return 1;
}

// Handle Delete Employee
int deleteEmployeeByID(Company& company)
{
    Node<EmployeeInfo>* head = company.listOfEmployee.getHead();
    unsigned int id;
    cout << "Input employee ID: ";
    cin >> id;
    if (!confirm())
        return 0;

    if (head != NULL)
    {
        bool isDeleted = false;
        while (head != NULL)
        {
            if (head->data.id == id)
            {
                company.listOfEmployee.removeItem(head);
                isDeleted = true;
                break;
            }
            head = head->next;
        }
        if (isDeleted)
        {
            cout << "Delete employee successful!!" << endl;
        }
        else
        {
            cout << "Can not find employee with this ID!!" << endl;
        }
    }
    else
    {
        cout << "Empty list ! Cannot delete employee !!" << endl;
    }
    return 1;
}

int deleteEmployeeByName(Company& company)
{
    List<EmployeeInfo> result;
    Node<EmployeeInfo>* head = company.listOfEmployee.getHead();

    string name;
    cout << "Input employee name: ";
    cin.ignore();
    getline(cin, name);

    if (head != NULL)
    {
        int count = 0;
        while (head != NULL)
        {
            if (head->data.name.find(name) != string::npos)
            {
                result.addLast(head->data);
                count++;
            }
            head = head->next;
        }
        if (result.getLen() == 0)
        {
            cout << "Haven't employee with this name !!" << endl;
            return 0;
        }
        else
        {
            cout << "Find " << count << " results" << endl;
            printEmployeeList(company, result);

            Node<EmployeeInfo>* _head = company.listOfEmployee.getHead();
            Node<EmployeeInfo>* _result = result.getHead();
            unsigned int id;
            cout << "Please input employee ID: ";
            cin >> id;

            bool isValidID = false;
            if (_result != NULL)
            {
                while (_result != NULL)
                {
                    if (_result->data.id == id)
                    {
                        isValidID = true;
                        break;
                    }
                    _result = _result->next;
                }
            }

            if (isValidID)
            {
                if (_head != NULL)
                {
                    while (_head != NULL)
                    {
                        if (_head->data.id == id)
                        {
                            company.listOfEmployee.removeItem(_head);
                            cout << "Delete employee successful!!" << endl;
                            break;
                        }
                        _head = _head->next;
                    }
                }
                else
                {
                    cout << "Empty list ! Cannot delete employee !!" << endl;
                }
            }
            else
            {
                cout << "Invalid ID !!" << endl;
            }
        }
    }
    else
    {
        cout << "Empty list ! Cannot search employee !!" << endl;
    }

    return 1;
}

int deleteEmployeeByPosition(Company& company)
{
    Node<EmployeeInfo>* head = company.listOfEmployee.getHead();

    string position;
    int select;
    bool isSelect = false;
    cout << "Select position for delete :";
    cout << "1. President" << endl;
    cout << "2. Manager" << endl;
    cout << "3. Employee" << endl;
    cout << "4. Customer" << endl;
    cout << "Input your select: " << endl;
    cin >> select;

    while (!isSelect)
    {
        switch (select)
        {
        case 1:
            if (!confirm())
                break;
            position = "President";
            isSelect = true;
            break;
        case 2:
            if (!confirm())
                break;
            position = "Manager";
            isSelect = true;
            break;
        case 3:
            if (!confirm())
                break;
            position = "Employee";
            isSelect = true;
            break;
        case 4:
            if (!confirm())
                break;
            position = "Customer";
            isSelect = true;
            break;
        default:
            cout << "Invalid selection!" << endl;
            return 0;
        }
    }

    if (head != NULL)
    {
        int count = 0;
        while (head != NULL)
        {
            if (head->data.position.find(position) != string::npos)
            {
                company.listOfEmployee.removeItem(head);
                count++;
            }
            head = head->next;
        }
        if (count == 0)
        {
            cout << "Haven't employee with this position !!" << endl;
            return 0;
        }
        else
        {
            cout << "Delete successful!!" << endl;
        }
    }
    else
    {
        cout << "Empty list ! Cannot search employee !!" << endl;
    }

    return 1;
}

int deleteAllEmployee(Company& company)
{
    if (!confirm())
        return 0;
    company.listOfEmployee.removeAll();
    cout << "Delete all employee successful!" << endl;
    return 1;
}

int deleteEmployee(Company& company)
{
    bool isChose = false;
    int select;
    while (!isChose)
    {
        cout << "Chose a delete option ?" << endl;
        cout << "1. ID" << endl;
        cout << "2. Name" << endl;
        cout << "3. Position" << endl;
        cout << "4. Delete all" << endl;
        cout << "5. Back" << endl;
        cout << "Input your select: ";
        cin >> select;
        switch (select)
        {
        case 1:
            deleteEmployeeByID(company);
            isChose = true;
            break;
        case 2:
            deleteEmployeeByName(company);
            isChose = true;
            break;
        case 3:
            deleteEmployeeByPosition(company);
            isChose = true;
            break;
        case 4:
            deleteAllEmployee(company);
            isChose = true;
            break;
        case 5:
            isChose = true;
            break;
        default:
            cout << "Invalid selection!" << endl;
            pressAnyKey();
            break;
        }
    }
    return 1;
}

int deleteDepartmentByID(Company& company)
{
    Node<DepartmentInfo>* head = company.listOfDepartment.getHead();
    unsigned int id;
    cout << "Input department ID: ";
    cin >> id;
    if (!confirm())
        return 0;

    if (head != NULL)
    {
        bool isDeleted = false;
        while (head != NULL)
        {
            if (head->data.id == id)
            {
                company.listOfDepartment.removeItem(head);
                isDeleted = true;
                break;
            }
            head = head->next;
        }
        if (isDeleted)
        {
            cout << "Delete department successful!!" << endl;
        }
        else
        {
            cout << "Can not find department with this ID!!" << endl;
        }
    }
    else
    {
        cout << "Empty list ! Cannot delete department !!" << endl;
    }
    return 1;
}

int deleteDepartmentByName(Company& company) {
    Node<DepartmentInfo>* head = company.listOfDepartment.getHead();

    string name;
    cout << "Input department name: ";
    cin.ignore();
    getline(cin, name);

    name = toLower(name);

    if (head != NULL) {
        while (head != NULL) {
            string str = toLower(head->data.name);
            if (str.find(name) != string::npos) {
                printDepartment(head->data);
                if (!confirm())
                    return 0;
                company.listOfDepartment.removeItem(head);
                cout << "Remove department successful!" << endl;
                return 1;
            }
            head = head->next;
        }
    }
    else {
        cout << "Empty list!!" << endl;
        return 0;
    }

    cout << "Haven't department with this name!!" << endl;

    return 0;
}

int deleteAllDepartment(Company& company) {
    if (!confirm())
        return 0;
    company.listOfDepartment.removeAll();
    cout << "Delete all department successful!" << endl;
    return 1;
}

int deleteDepartment(Company& company)
{
    bool isChose = false;
    int select;
    while (!isChose)
    {
        cout << "Chose a delete option ?" << endl;
        cout << "1. ID" << endl;
        cout << "2. Name" << endl;
        cout << "3. Delete all" << endl;
        cout << "4. Back" << endl;
        cout << "Input your select: ";
        cin >> select;
        switch (select)
        {
        case 1:
            deleteDepartmentByID(company);
            isChose = true;
            break;
        case 2:
            deleteDepartmentByName(company);
            isChose = true;
            break;
        case 3:
            deleteAllDepartment(company);
            isChose = true;
            break;
        case 4:
            isChose = true;
            break;
        default:
            cout << "Invalid selection!" << endl;
            break;
        }
    }
    return 1;
}

// Handle Search Employee
int searchEmployeeByID(Company& company)
{
    Node<EmployeeInfo>* head = company.listOfEmployee.getHead();

    unsigned int id;
    cout << "Input employee ID: ";
    cin >> id;

    while (id <= 0)
    {
        cout << "Invalid ID!!" << endl;
        cout << "Input employee ID: ";
        cin >> id;
    }

    bool found = false;
    if (head != NULL)
    {
        while (head != NULL)
        {
            if (head->data.id == id)
            {
                found = true;
                printEmployee(company, head->data);
                return 1;
            }
            head = head->next;
        }
    }
    else
    {
        cout << "Empty list ! Cannot search employee !!" << endl;
    }

    if (found == false)
    {
        cout << "Haven't employee with this ID !!" << endl;
    }
    return 1;
}

int searchEmployeeByName(Company& company)
{
    List<EmployeeInfo> result;
    Node<EmployeeInfo>* head = company.listOfEmployee.getHead();

    string name;
    cout << "Input employee name: ";
    cin.ignore();
    getline(cin, name);
    name = toLower(name);

    if (head != NULL)
    {
        int count = 0;
        while (head != NULL)
        {
            string str = toLower(head->data.name);
            if (str.find(name) != string::npos)
            {
                result.addLast(head->data);
                count++;
            }
            head = head->next;
        }
        if (result.getLen() == 0)
        {
            cout << "Haven't employee with this name !!" << endl;
        }
        else
        {
            cout << "Find " << count << " results" << endl;
            printEmployeeList(company, result);
        }
    }
    else
    {
        cout << "Empty list ! Cannot search employee !!" << endl;
    }

    return 1;
}

int searchEmployeeByPosition(Company& company)
{
    List<EmployeeInfo> result;
    Node<EmployeeInfo>* head = company.listOfEmployee.getHead();

    string position;
    int select;
    bool isSelect = false;
    cout << "Select position" << endl;
    cout << "1. President" << endl;
    cout << "2. Manager" << endl;
    cout << "3. Employee" << endl;
    cout << "4. Customer" << endl;
    cout << "Input your select: ";
    cin >> select;

    while (!isSelect)
    {
        switch (select)
        {
        case 1:
            position = "President";
            isSelect = true;
            break;
        case 2:
            position = "Manager";
            isSelect = true;
            break;
        case 3:
            position = "Employee";
            isSelect = true;
            break;
        case 4:
            position = "Customer";
            isSelect = true;
            break;
        default:
            cout << "Invalid option!!" << endl;
        }
    }

    position = toLower(position);

    if (head != NULL)
    {
        int count = 0;
        while (head != NULL)
        {
            string str = toLower(head->data.position);
            if (str.find(position) != string::npos)
            {
                result.addLast(head->data);
                count++;
            }
            head = head->next;
        }
        if (result.getLen() == 0)
        {
            cout << "Haven't employee with this name !!" << endl;
        }
        else
        {
            cout << "Find " << count << " results" << endl;
            printEmployeeList(company, result);
        }
    }
    else
    {
        cout << "Empty list ! Cannot search employee !!" << endl;
    }
    return 1;
}

int searchEmployee(Company& company)
{
    bool isChose = false;
    bool isSelect = false;
    int select;
    while (!isChose)
    {
        cout << "Do you want search by ?" << endl;
        cout << "1. ID" << endl;
        cout << "2. Name" << endl;
        cout << "3. Position" << endl;
        cout << "4. Back" << endl;
        cout << "Input your select: ";
        cin >> select;
        switch (select)
        {
        case 1:
            searchEmployeeByID(company);
            isChose = true;
            break;
        case 2:
            searchEmployeeByName(company);
            isChose = true;
            break;
        case 3:
            searchEmployeeByPosition(company);
            isChose = true;
            break;
        case 4:
            isChose = true;
            break;
        default:
            cout << "Invalid selection!" << endl;
            break;
        }
    }
    return 1;
}

int searchDepartmentByID(Company& company)
{
    Node<DepartmentInfo>* head = company.listOfDepartment.getHead();

    unsigned int id;
    cout << "Input department ID: ";
    cin >> id;

    while (id <= 0)
    {
        cout << "Invalid ID!!" << endl;
        cout << "Input department ID: ";
        cin >> id;
    }

    bool found = false;
    if (head != NULL)
    {

        while (head != NULL)
        {
            if (head->data.id == id)
            {
                found = true;
                printDepartment(head->data);
                return 1;
            }
            head = head->next;
        }
    }
    else
    {
        cout << "Empty list ! Cannot search department !!" << endl;
    }

    if (found == false)
    {
        cout << "Haven't department with this ID !!" << endl;
    }
    return 1;
}

int searchDepartmentByName(Company& company)
{
    List<DepartmentInfo> result;
    Node<DepartmentInfo>* head = company.listOfDepartment.getHead();

    string name;
    cout << "Input department name: ";
    cin.ignore();
    getline(cin, name);

    name = toLower(name);

    if (head != NULL)
    {
        int count = 0;
        while (head != NULL)
        {
            string str = toLower(head->data.name);
            if (str.find(name) != string::npos)
            {
                result.addLast(head->data);
                count++;
            }
            head = head->next;
        }
        if (result.getLen() == 0)
        {
            cout << "Haven't department with this name !!" << endl;
        }
        else
        {
            cout << "Find " << count << " results" << endl;
            printDepartmentList(result);
        }
    }
    else
    {
        cout << "Empty list ! Cannot search department !!" << endl;
    }

    return 1;
}

int searchDepartment(Company& company)
{
    bool isChose = false;
    bool isSelect = false;
    int select;
    while (!isChose)
    {
        cout << "Do you want search by ?" << endl;
        cout << "1. ID" << endl;
        cout << "2. Name" << endl;
        cout << "3. Back" << endl;
        cout << "Input your select: ";
        cin >> select;
        switch (select)
        {
        case 1:
            searchDepartmentByID(company);
            isChose = true;
            break;
        case 2:
            searchDepartmentByName(company);
            isChose = true;
            break;
        case 3:
            isChose = true;
            break;
        default:
            cout << "Invalid selection!" << endl;
            break;
        }
    }
    return 1;
}

// Handle Update Information
int updateNameOfEmployee(Company& company, EmployeeInfo& employee)
{
    string newName;
    cout << "Input new employee name: ";
    cin.ignore();
    getline(cin, newName);
    if (!confirm())
        return 0;

    employee.name = formatName(newName);
    cout << "Update successful!!" << endl;
    printEmployee(company, employee);
    return 1;
}

int updateDateOfEmployee(Company& company, EmployeeInfo& employee)
{
    string newDate;
    cout << "Input new employee date: ";
    cin.ignore();
    getline(cin, newDate);
    if (!confirm())
        return 0;

    employee.date = newDate;
    cout << "Update successful!!" << endl;
    printEmployee(company, employee);
    return 1;
}

int updateGenderOfEmployee(Company& company, EmployeeInfo& employee)
{
    string newGender;
    cout << "Input new employee gender: ";
    cin.ignore();
    getline(cin, newGender);
    if (!confirm())
        return 0;

    employee.gender = newGender;
    cout << "Update successful!!" << endl;
    printEmployee(company, employee);
    return 1;
}

int updatePhoneOfEmployee(Company& company, EmployeeInfo& employee)
{
    string newPhone;
    cout << "Input new employee phone: ";
    cin.ignore();
    getline(cin, newPhone);
    if (!confirm())
        return 0;

    employee.phone = newPhone;
    cout << "Update successful!!" << endl;
    printEmployee(company, employee);
    return 1;
}

int updatePositionOfEmployee(Company& company, EmployeeInfo& employee)
{
    string position;
    int select;
    bool isSelect = false;
    cout << "Select position" << endl;
    cout << "1. President" << endl;
    cout << "2. Manager" << endl;
    cout << "3. Employee" << endl;
    cout << "4. Customer" << endl;
    cout << "Input your select: " << endl;
    cin >> select;

    while (!isSelect)
    {
        switch (select)
        {
        case 1:
            position = "President";
            isSelect = true;
            break;
        case 2:
            position = "Manager";
            isSelect = true;
            break;
        case 3:
            position = "Employee";
            isSelect = true;
            break;
        case 4:
            position = "Customer";
            isSelect = true;
            break;
        default:
            cout << "Invalid option!!" << endl;
            return 0;
        }
    }

    employee.position = position;
    cout << "Update successful!!" << endl;
    printEmployee(company, employee);
    return 1;
}

int updateDepartmentOfEmployee(Company& company, EmployeeInfo& employee)
{
    unsigned int newDepartmentID;
    cout << "Input new department ID: ";
    cin >> newDepartmentID;
    while (!hasDepartmentWithID(company, newDepartmentID))
    {
        cout << "Can't find this department ID!!" << endl;
        cout << "Input new department ID: ";
        cin >> newDepartmentID;
    }
    if (!confirm())
        return 0;

    employee.departmentID = newDepartmentID;
    cout << "Update successful!!" << endl;
    printEmployee(company, employee);
    return 1;
}

int updateInfoEmployee(Company& company)
{
    Node<EmployeeInfo>* head = company.listOfEmployee.getHead();
    unsigned int id;
    cout << "Input employee ID for edit: ";
    cin >> id;

    if (head != NULL)
    {
        bool isValidID = false;
        while (head != NULL)
        {
            if (head->data.id == id)
            {
                isValidID = true;
                printEmployee(company, head->data);

                bool isSelect = false;
                while (!isSelect)
                {
                    cout << "What do you want to edit?" << endl;
                    int select;
                    cout << "1. Name" << endl;
                    cout << "2. Date" << endl;
                    cout << "3. Gender" << endl;
                    cout << "4. Phone" << endl;
                    cout << "5. Position" << endl;
                    cout << "6. Department" << endl;
                    cout << "7. Back" << endl;
                    cout << "Input your selection: ";
                    cin >> select;
                    switch (select)
                    {
                    case 1:
                        updateNameOfEmployee(company, head->data);
                        isSelect = true;
                        break;
                    case 2:
                        updateDateOfEmployee(company, head->data);
                        isSelect = true;
                        break;
                    case 3:
                        updateGenderOfEmployee(company, head->data);
                        isSelect = true;
                        break;
                    case 4:
                        updatePhoneOfEmployee(company, head->data);
                        isSelect = true;
                        break;
                    case 5:
                        updatePositionOfEmployee(company, head->data);
                        isSelect = true;
                        break;
                    case 6:
                        updateDepartmentOfEmployee(company, head->data);
                        isSelect = true;
                        break;
                    case 7:
                        isSelect = true;
                        break;
                    default:
                        cout << "Invalid selection!" << endl;
                        break;
                    }
                }
                return 1;
            }
            head = head->next;
        }
        if (!isValidID)
        {
            cout << "Can't find employee with this ID!!" << endl;
            return 0;
        }
    }
    return 1;
}

int updateNameOfDepartment(DepartmentInfo& department)
{
    string newName;
    cout << "Input new department name: ";
    cin.ignore();
    getline(cin, newName);
    if (!confirm())
        return 0;

    department.name = formatName(newName);
    cout << "Update successful!!" << endl;
    printDepartment(department);
    return 1;
}

int updateManagerOfDepartment(Company& company, DepartmentInfo& department)
{
    unsigned int id;
    cout << "Input new department manager ID: ";
    cin >> id;
    while (!hasEmployeeWithID(company, id))
    {
        cout << "Can't find employee with this ID!" << endl;
        cout << "Input new department manager ID: ";
        cin >> id;
    }
    if (!confirm())
        return 0;
    EmployeeInfo employee = getEmployeeByID(company, id);
    department.manager_name = employee.name;
    department.manager_id = employee.id;
    cout << "Update successful!!" << endl;
    printDepartment(department);
    return 1;
}

int updateInfoDepartment(Company& company)
{
    Node<DepartmentInfo>* head = company.listOfDepartment.getHead();
    unsigned int id;
    cout << "Input department ID for edit: ";
    cin >> id;

    if (head != NULL)
    {
        bool isValidID = false;
        while (head != NULL)
        {
            if (head->data.id == id)
            {
                isValidID = true;
                printDepartment(head->data);

                bool isSelect = false;
                while (!isSelect)
                {
                    cout << "What do you want to edit?" << endl;
                    int select;
                    cout << "1. Name" << endl;
                    cout << "2. Manager" << endl;
                    cout << "3. Back" << endl;
                    cout << "Input your selection: ";
                    cin >> select;
                    switch (select)
                    {
                    case 1:
                        updateNameOfDepartment(head->data);
                        isSelect = true;
                        break;
                    case 2:
                        updateManagerOfDepartment(company, head->data);
                        isSelect = true;
                        break;
                    case 3:
                        isSelect = true;
                        break;
                    default:
                        cout << "Invalid selection!" << endl;
                        break;
                    }
                }
                return 1;
            }
            head = head->next;
        }
        if (!isValidID)
        {
            cout << "Can't find department with this ID!!" << endl;
            return 0;
        }
    }
    return 1;
}

int update(Company& company)
{
    bool isChose = false;
    bool isSelect = false;
    int select;
    while (!isChose)
    {
        cout << "What do you want update ?" << endl;
        cout << "1. Employee" << endl;
        cout << "2. Department" << endl;
        cout << "3. Back" << endl;
        cout << "Input your select: ";
        cin >> select;
        switch (select)
        {
        case 1:
            updateInfoEmployee(company);
            isChose = true;
            break;
        case 2:
            updateInfoDepartment(company);
            isChose = true;
            break;
        case 3:
            isChose = true;
            break;
        default:
            cout << "Invalid selection!" << endl;
            break;
        }
    }
    return 1;
}

// Handle Arrange
int arrangeEmployeeByID(Company& company)
{
    Node<EmployeeInfo>* head = company.listOfEmployee.getHead();
    int len = company.listOfEmployee.getLen();

    if (head != NULL) {
        Node<EmployeeInfo>* current = head->next;

        while (current != NULL) {
            Node<EmployeeInfo>* temp = current;
            EmployeeInfo tempData = temp->data;

            while (temp != head && temp->prev->data.id > tempData.id) {
                temp->data = temp->prev->data;
                temp = temp->prev;
            }

            temp->data = tempData;
            current = current->next;
        }

        cout << "Arrange successful!" << endl;
    } else {
        cout << "Empty list !! Can not arrange empty list!" << endl;
        return 0;
    }

    return 1;

    
}

int arrangeEmployeeByName(Company& company)
{
    Node<EmployeeInfo>* head = company.listOfEmployee.getHead();
    int len = company.listOfEmployee.getLen();
    if (head != NULL)
    {
        while (head->next != NULL)
        {
            Node<EmployeeInfo>* _head = company.listOfEmployee.getHead();
            while (_head->next != NULL)
            {
                if (_head->data.name[0] > _head->next->data.name[0])
                {
                    EmployeeInfo temp;
                    temp = _head->data;
                    _head->data = _head->next->data;
                    _head->next->data = temp;
                }
                _head = _head->next;
            }
            head = head->next;
        }
        cout << "Arrange successful!" << endl;
    }
    else
    {
        cout << "Empty list !! Can not arrange empty list!" << endl;
        return 0;
    }

    return 1;
}

int arrangeEmployeeByPosition(Company& company)
{
    Node<EmployeeInfo>* head = company.listOfEmployee.getHead();
    int len = company.listOfEmployee.getLen();

    if (head != NULL) {
        Node<EmployeeInfo>* current = head;

        while (current->next != NULL) {
            Node<EmployeeInfo>* minNode = current;
            Node<EmployeeInfo>* temp = current->next;

            while (temp != NULL) {
                if (temp->data.position[0] < minNode->data.position[0]) {
                    minNode = temp;
                }
                temp = temp->next;
            }

            if (minNode != current) {
                EmployeeInfo tempData = current->data;
                current->data = minNode->data;
                minNode->data = tempData;
            }

            current = current->next;
        }

        cout << "Arrange successful!" << endl;
    }
    else {
        cout << "Empty list !! Can not arrange empty list!" << endl;
        return 0;
    }

    return 1;

}

int arrange(Company& company)
{
    bool isChose = false;
    bool isSelect = false;
    int select;
    while (!isChose)
    {
        cout << "Do you want arrange by ?" << endl;
        cout << "1. ID" << endl;
        cout << "2. Name" << endl;
        cout << "3. Position" << endl;
        cout << "4. Back" << endl;
        cout << "Input your select: ";
        cin >> select;
        switch (select)
        {
        case 1:
            if (!confirm())
                break;
            arrangeEmployeeByID(company);
            isChose = true;
            break;
        case 2:
            arrangeEmployeeByName(company);
            isChose = true;
            break;
        case 3:
            arrangeEmployeeByPosition(company);
            isChose = true;
            break;
        case 4:
            isChose = true;
            break;
        default:
            cout << "Invalid selection!" << endl;
            break;
        }
    }
    return 1;
};

// Handle budget
int payrollForMonth(Company &company) {
    Node<Timekeeping>* head = company.listOfTimeKeeping.getHead();

    List<Timekeeping> result;

    string month;
    cout << "Input month: ";
    cin.ignore();
    getline(cin, month);

    if (!hasTimekeepingWithMonth(company, month)) {
        cout << "No result!!" << endl;
        return 0;
    }
    else {
        if (head != NULL) {
            while (head != NULL) {
                if (stoi(head->data.month) == stoi(month)) {
                    result.addFirst(head->data);
                }
                head = head->next;
            }
        }

        if (result.getLen() == 0) {
            cout << "No result!" << endl;
        }
        else {
            double total = 0;
            List<Salary> salaryList;
            Node<Timekeeping>* _head_timekeeping = result.getHead();
            while (_head_timekeeping != NULL) {
                Salary salary;
                salary.id = _head_timekeeping->data.id;
                salary.name = _head_timekeeping->data.name;
                salary.month = _head_timekeeping->data.month;
                salary.income = (_head_timekeeping->data.days) * 15;
                salary.bonus = (salary.income) / 10;
                salary.salary = (salary.income) + (salary.bonus);
                total = total + salary.salary;
                salaryList.addFirst(salary);
                _head_timekeeping = _head_timekeeping->next;
            }

            printSalaryForMonth(salaryList);
            cout << "\nTotal: $" << total << endl;
        }
    }
    return 1;
}

int payrollForAll(Company& company) {
    Node<Timekeeping>* head = company.listOfTimeKeeping.getHead();
    double total = 0;
    List<Salary> salaryList;
    while (head != NULL) {
        Salary salary;
        salary.id = head->data.id;
        salary.name = head->data.name;
        salary.month = head->data.month;
        salary.income = (head->data.days) * 15;
        salary.bonus = (salary.income) / 10;
        salary.salary = (salary.income) + (salary.bonus);
        total = total + salary.salary;
        salaryList.addFirst(salary);
        head = head->next;
    }

    printSalaryForMonth(salaryList);
    cout << "\nTotal: $" << total << endl;
    return 1;
}

int budget(Company& company) {
    bool isChose = false;
    bool isSelect = false;
    int select;
    while (!isChose)
    {
        cout << "Chose your option ?" << endl;
        cout << "1. Payroll for a month" << endl;
        cout << "2. Payroll for all" << endl;
        cout << "3. Back" << endl;
        cout << "Input your select: ";
        cin >> select;
        switch (select)
        {
        case 1:
            payrollForMonth(company);
            isChose = true;
            break;
        case 2:
            payrollForAll(company);
            isChose = true;
            break;
        case 3:
            isChose = true;
            break;
        default:
            cout << "Invalid selection!" << endl;
            break;
        }
    }
    return 1;
}

// Handle Timekeeping
int timeKeeping(Company &company) {
    unsigned int id;
    cout << "Input your ID: ";
    cin >> id;
    while (!hasEmployeeWithID(company, id)) {
        cout << "Haven't employee with thí ID!!" << endl;
        cout << "Input your ID: ";
        cin >> id;
    }
    Timekeeping timekeeping;
    timekeeping.id = id;
    timekeeping.name = getEmployeeByID(company, timekeeping.id).name;

    cout << "Input month: ";
    cin >> timekeeping.month;
    while ((stoi(timekeeping.month) > 12) || (stoi(timekeeping.month) < 0)) {
        cout << "Invalid month!!" << endl;
        cout << "Input month: ";
        cin >> timekeeping.month;
    }

    if (hasTimekeepingWithIDandMonth(company, timekeeping.id, timekeeping.month)) {
        cout << "This month was has timekeeping!" << endl;
        return 0;
    }

    int daysInMonth = 31;
    int year = 2023;
    switch (stoi(timekeeping.month)) {
    case 2:
        daysInMonth = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        daysInMonth = 30;
        break;
    }

    cout << "Input day: ";
    cin >> timekeeping.days;
    while (timekeeping.days > daysInMonth) {
        cout << "Invalid month!!" << endl;
        cout << "Input month: ";
        cin >> timekeeping.days;
    }
    company.listOfTimeKeeping.addFirst(timekeeping);
    cout << "Timekeeping successful!" << endl;
    return 1;
}

// Handle Format & Check
string formatName(string name)
{
    string newString = trim(name);
    int len = newString.length();
    for (int i = 0; i < len; i++)
    {
        if (i == 0)
        {
            newString[i] = toupper(newString[i]);
        }
        else
        {
            newString[i] = tolower(newString[i]);
            if (newString[i - 1] == ' ' && newString[i] != ' ')
            {
                newString[i] = toupper(newString[i]);
            }
        }
    }
    string result;
    bool space = false;
    for (int i = 0; i < len; i++)
    {
        if (newString[i] == ' ')
        {
            if (!space)
            {
                result += newString[i];
            }
            space = true;
        }
        else
        {
            result += newString[i];
            space = false;
        }
    }

    return result;
}

bool checkPhoneInput(string phone)
{
    for (int i = 0; i < phone.length(); i++)
    {
        if ((int)(phone[i]) > 57 || (int)(phone[i]) < 48)
        {
            cout << "Value :" << (int)(phone[i]) << endl;
            return false;
        }
    }
    if (phone.length() < PHONE_LENGTH)
    {
        cout << "Invalid phone length!" << endl;
        return false;
    }
    if (phone[0] != '0')
    {
        cout << "Invalid phone format!" << endl;
        return false;
    }
    return true;
}

bool isValidDate(string input) {
    int day, month, year;
    char sep = '/';
    int pos1 = input.find(sep);
    int pos2 = input.find(sep, pos1 + 1);

    if (pos1 == string::npos || pos2 == string::npos) {
        return false;
    }

    day = stoi(input.substr(0, pos1));
    month = stoi(input.substr(pos1 + 1, pos2 - pos1 - 1));
    year = stoi(input.substr(pos2 + 1));

    if (year < 0 || year > 9999 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    int daysInMonth = 31;
    switch (month) {
    case 2:
        daysInMonth = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        daysInMonth = 30;
        break;
    }

    return (day <= daysInMonth);
}

string toLower(string str) {
    string temp = str;
    for (int i = 0; i < str.length(); i++) {
        temp[i] = tolower(str[i]);
    }
    return temp;
}

bool hasEmployeeWithID(Company& company, unsigned int id)
{
    Node<EmployeeInfo>* head = company.listOfEmployee.getHead();
    if (head != NULL)
    {
        while (head != NULL)
        {
            if (head->data.id == id)
            {
                return true;
            }
            head = head->next;
        }
    }
    return false;
}

bool hasEmployeeWithPosition(Company& company, string position)
{
    Node<EmployeeInfo>* head = company.listOfEmployee.getHead();
    if (head != NULL)
    {
        while (head != NULL)
        {
            if (head->data.position.find(position) != string::npos)
            {
                return true;
            }
            head = head->next;
        }
    }
    return false;
}

bool hasDepartmentWithID(Company& company, unsigned int id)
{
    Node<DepartmentInfo>* head = company.listOfDepartment.getHead();
    if (head != NULL)
    {
        while (head != NULL)
        {
            if (head->data.id == id)
            {
                return true;
            }
            head = head->next;
        }
    }
    return false;
}

bool hasDepartmentWithName(Company& company, string name) {
    Node<DepartmentInfo>* head = company.listOfDepartment.getHead();
    if (head != NULL)
    {
        while (head != NULL)
        {
            if (head->data.name.find(name) != string::npos) {
                return true;
            }
            head = head->next;
        }
    }
    return false;
}

bool hasTimekeepingWithID(Company& company, unsigned int id) {
    Node<Timekeeping>* head = company.listOfTimeKeeping.getHead();
    if (head != NULL)
    {
        while (head != NULL)
        {
            if (head->data.id == id)
            {
                return true;
            }
            head = head->next;
        }
    }
    return false;
}

bool hasTimekeepingWithMonth(Company& company, string month) {
    Node<Timekeeping>* head = company.listOfTimeKeeping.getHead();
    if (head != NULL)
    {
        while (head != NULL)
        {
            if (head->data.month.find(month) != string::npos) {
                return true;
            }
            head = head->next;
        }
    }
    return false;
}

bool hasTimekeepingWithIDandMonth(Company& company, unsigned int id, string month) {
    Node<Timekeeping>* head = company.listOfTimeKeeping.getHead();
    if (head != NULL)
    {
        while (head != NULL)
        {
            if (head->data.id == id && head->data.month.find(month) != string::npos) {
                return true;
            }
            head = head->next;
        }
    }
    return false;
}

// Import/Export from files
void writeDataToFile(Company& company)
{
    char fileEmployee[18] = "employee-list.txt";

    cout << "Exporting to " << fileEmployee << "..." << endl;

    ofstream fileEmployeeOut(fileEmployee);
    Node<EmployeeInfo>* head_employee = company.listOfEmployee.getHead();
    fileEmployeeOut << company.listOfEmployee.getLen();
    fileEmployeeOut << endl;
    fileEmployeeOut << setw(ID_SPACE) << "ID";
    fileEmployeeOut << setw(NAME_SPACE) << "Name";
    fileEmployeeOut << setw(DATE_SPACE) << "Date";
    fileEmployeeOut << setw(GENDER_SPACE) << "Gender";
    fileEmployeeOut << setw(PHONE_SPACE) << "Phone number";
    fileEmployeeOut << setw(POSITION_SPACE) << "Position";
    fileEmployeeOut << setw(WORK_AT_SPACE) << "Work at";
    fileEmployeeOut << endl;

    for (int i = 0; i < company.listOfEmployee.getLen(); i++)
    {
        if (head_employee != NULL)
        {
            fileEmployeeOut << setw(ID_SPACE) << head_employee->data.id;
            fileEmployeeOut << setw(NAME_SPACE) << head_employee->data.name;
            fileEmployeeOut << setw(DATE_SPACE) << head_employee->data.date;
            fileEmployeeOut << setw(GENDER_SPACE) << head_employee->data.gender;
            fileEmployeeOut << setw(PHONE_SPACE) << head_employee->data.phone;
            fileEmployeeOut << setw(POSITION_SPACE) << head_employee->data.position;
            fileEmployeeOut << setw(WORK_AT_SPACE) << head_employee->data.departmentID;
            fileEmployeeOut << endl;
        }
        head_employee = head_employee->next;
    }
    cout << "Exported to " << fileEmployee << " successful." << endl;

    char fileDepartment[20] = "department-list.txt";
    cout << "Exporting to " << fileDepartment << "..." << endl;

    ofstream fileDepartmentOut(fileDepartment);
    Node<DepartmentInfo>* head_department = company.listOfDepartment.getHead();
    fileDepartmentOut << company.listOfDepartment.getLen();
    fileDepartmentOut << endl;
    fileDepartmentOut << setw(ID_SPACE) << "ID";
    fileDepartmentOut << setw(NAME_SPACE) << "Name";
    fileDepartmentOut << setw(NAME_SPACE) << "Manager ID";
    fileDepartmentOut << setw(NAME_SPACE) << "Manager name";
    fileDepartmentOut << endl;

    for (int i = 0; i < company.listOfDepartment.getLen(); i++)
    {
        if (head_department != NULL)
        {
            fileDepartmentOut << setw(ID_SPACE) << head_department->data.id;
            fileDepartmentOut << setw(NAME_SPACE) << head_department->data.name;
            fileDepartmentOut << setw(NAME_SPACE) << head_department->data.manager_id;
            fileDepartmentOut << setw(NAME_SPACE) << head_department->data.manager_name;
            fileDepartmentOut << endl;
        }
        head_department = head_department->next;
    }
    cout << "Exported to " << fileDepartment << " successful." << endl;

    char fileTimekeeping[25] = "timekeeping-list.txt";
    cout << "Exporting to " << fileTimekeeping << "..." << endl;

    ofstream fileTimekeepingOut(fileTimekeeping);
    Node<Timekeeping>* head_timekeeping = company.listOfTimeKeeping.getHead();
    fileTimekeepingOut << company.listOfTimeKeeping.getLen();
    fileTimekeepingOut << endl;
    fileTimekeepingOut << setw(ID_SPACE) << "ID";
    fileTimekeepingOut << setw(NAME_SPACE) << "Name";
    fileTimekeepingOut << setw(DATE_SPACE) << "Month";
    fileTimekeepingOut << setw(DATE_SPACE) << "Days";
    fileTimekeepingOut << endl;

    for (int i = 0; i < company.listOfTimeKeeping.getLen(); i++)
    {
        if (head_timekeeping != NULL)
        {
            fileTimekeepingOut << setw(ID_SPACE) << head_timekeeping->data.id;
            fileTimekeepingOut << setw(NAME_SPACE) << head_timekeeping->data.name;
            fileTimekeepingOut << setw(DATE_SPACE) << head_timekeeping->data.month;
            fileTimekeepingOut << setw(DATE_SPACE) << head_timekeeping->data.days;
            fileTimekeepingOut << endl;
        }
        head_timekeeping = head_timekeeping->next;
    }
    cout << "Exported to " << fileTimekeeping << " successful." << endl;
}

EmployeeInfo handleDataEmployeeFromLine(string data)
{
    EmployeeInfo employee;

    // Get ID from file
    employee.id = stoi(trim(data.substr(0, ID_SPACE)));

    // Get name from file
    employee.name = trim(data.substr(ID_SPACE, NAME_SPACE));

    // Get name from file
    employee.date = trim(data.substr(ID_SPACE + NAME_SPACE, DATE_SPACE));

    // Get name from file
    employee.gender = trim(data.substr(ID_SPACE + NAME_SPACE + DATE_SPACE, GENDER_SPACE));

    // Get name from file
    employee.phone = trim(data.substr(ID_SPACE + NAME_SPACE + DATE_SPACE + GENDER_SPACE, PHONE_SPACE));

    // Get position from file
    employee.position = trim(data.substr(ID_SPACE + NAME_SPACE + DATE_SPACE + GENDER_SPACE + PHONE_SPACE, POSITION_SPACE));

    // Get department from file
    employee.departmentID = stoi(trim(data.substr(ID_SPACE + NAME_SPACE + DATE_SPACE + GENDER_SPACE + PHONE_SPACE + POSITION_SPACE, WORK_AT_SPACE)));

    return employee;
}

DepartmentInfo handleDataDepartmentFromLine(string data)
{
    DepartmentInfo department;

    // Get ID from file
    department.id = stoi(trim(data.substr(0, ID_SPACE)));

    // Get name from file
    department.name = trim(data.substr(ID_SPACE, NAME_SPACE));

    // Get manager id from file
    department.manager_id = stoi(trim(data.substr(ID_SPACE + NAME_SPACE, NAME_SPACE)));

    // Get manager name from file
    department.manager_name = trim(data.substr(ID_SPACE + NAME_SPACE + NAME_SPACE, NAME_SPACE));

    return department;
}

Timekeeping handleDataTimekeepingFromFile(string data) {
    Timekeeping timekeeping;

    // Get ID from file
    timekeeping.id = stoi(trim(data.substr(0, ID_SPACE)));

    // Get name from file
    timekeeping.name = trim(data.substr(ID_SPACE, NAME_SPACE));

    // Get manager name from file
    timekeeping.month = trim(data.substr(ID_SPACE + NAME_SPACE, DATE_SPACE));

    // Get manager name from file
    timekeeping.days = stoi(trim(data.substr(ID_SPACE + NAME_SPACE + DATE_SPACE, DATE_SPACE)));

    return timekeeping;
}

int readDataFromFile(Company& company)
{
    // Read employee data from file
    char fileEmployee[18] = "employee-list.txt";
    cout << "Importing data from " << fileEmployee << "..." << endl;

    ifstream fileEmployeeIn(fileEmployee);

    // Get number of employee at first line
    int numOfEmployees;
    fileEmployeeIn >> numOfEmployees;

    string dataEmployee;
    // Skip first and second line in file
    getline(fileEmployeeIn, dataEmployee);
    getline(fileEmployeeIn, dataEmployee);

    // Get data from file
    for (int i = 0; i < numOfEmployees; i++)
    {
        getline(fileEmployeeIn, dataEmployee);
        EmployeeInfo employee = handleDataEmployeeFromLine(dataEmployee);
        company.listOfEmployee.addLast(employee);
    }

    cout << "Importing data from " << fileEmployee << " successful." << endl;
    fileEmployeeIn.close();

    // Read department data from file
    char fileDepartment[20] = "department-list.txt";
    cout << "Importing data from " << fileDepartment << "..." << endl;

    ifstream fileDepartmentIn(fileDepartment);

    // Get number of department at first line
    int numOfDepartment;
    fileDepartmentIn >> numOfDepartment;

    string dataDepartment;
    // Skip first and second line in file
    getline(fileDepartmentIn, dataDepartment);
    getline(fileDepartmentIn, dataDepartment);

    // Get data from file
    for (int i = 0; i < numOfDepartment; i++)
    {
        getline(fileDepartmentIn, dataDepartment);
        DepartmentInfo department = handleDataDepartmentFromLine(dataDepartment);
        company.listOfDepartment.addLast(department);
    }

    cout << "Importing data from " << fileDepartment << " successful." << endl;
    fileDepartmentIn.close();
    
    // Read timekeeping data from file
    char fileTimekeeping[25] = "timekeeping-list.txt";
    cout << "Importing data from " << fileTimekeeping << "..." << endl;

    ifstream fileTimekeepingIn(fileTimekeeping);

    // Get number of timekeeping at first line
    int numOfTimekeeping;
    fileTimekeepingIn >> numOfTimekeeping;

    string dataTimekeeping;
    // Skip first and second line in file
    getline(fileTimekeepingIn, dataTimekeeping);
    getline(fileTimekeepingIn, dataTimekeeping);

    // Get data from file
    for (int i = 0; i < numOfTimekeeping; i++)
    {
        getline(fileTimekeepingIn, dataTimekeeping);
        Timekeeping timekeeping = handleDataTimekeepingFromFile(dataTimekeeping);
        company.listOfTimeKeeping.addLast(timekeeping);
    }

    cout << "Importing data from " << fileTimekeeping << " successful." << endl;
    fileTimekeepingIn.close();
    
    return 1;
}
