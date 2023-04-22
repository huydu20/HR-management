#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <iomanip>

#define INDEX_SPACE 10
#define NAME_SPACE 30
#define POSITION_SPACE 15
#define NUMS_OF_ATTRIBUTE 3

using namespace std;

struct EmployeeInfo
{
    string name;
    string position;

    EmployeeInfo() {}

    EmployeeInfo(string name, string position)
    {
        this->name = name;
        this->position = position;
    }
};

struct Node
{
    EmployeeInfo data;
    Node *next;
    Node *prev;
};

struct List
{
private:
    Node *head;
    Node *tail;
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
    Node *getHead() { return head; }
    Node *getTail() { return tail; }

    // Ham lay phan tu trong List
    Node *getItem(int ps)
    {
        if (ps > len || ps <= 0)
        {
            return NULL;
        }
        else
        {
            if (ps <= len / 2)
            {
                Node *q = head;
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
                Node *q = tail;
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

    Node *getFirstItem()
    {
        Node *p = head;
        return p;
    }

    Node *getLastItem()
    {
        Node *p = tail;
        return p;
    }

    // Ham them phan tu
    int addFirst(EmployeeInfo x)
    {
        Node *p = new Node();
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

    int addLast(EmployeeInfo x)
    {
        Node *p = new Node();
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

    int addItem(Node *p, EmployeeInfo x)
    {
        Node *q = new Node();
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
        Node *p = head;
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
        Node *p = tail;
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

    int removeItem(Node *p)
    {
        if (head != NULL)
        {
            if (p->next != NULL)
            {
                Node *q = head;
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
            Node *q = head;
            while (q->next != NULL)
            {
                Node *tmp = q;
                q = q->next;
                delete tmp;
            }
            head = NULL;
            len = 0;
            delete q;
            cout << "\nDa xoa het phan tu!!";
        }
        else
        {
            cout << "\nDanh sach trong!!";
        }
    }

    // Ham cap nhat gia phan tu
    int updateItem(int p, EmployeeInfo x)
    {
        if (p > len || p <= 0)
        {
            return 0;
        }
        if (head != NULL)
        {
            Node *q = head;
            for (int i = 0; i < p - 1; i++)
            {
                q = q->next;
            }
            q->data = x;
            return 1;
        }
    }

    // Ham gop List
    void addRange(List &list)
    {
        Node *q = head;
        while (q->next != NULL)
        {
            q = q->next;
        }
        q->next = list.getHead();
    }
};

struct Company
{
    List listOfEmployee;
};

// ------ Local Variable --------- //

int lengthOfAttribute[NUMS_OF_ATTRIBUTE] = {INDEX_SPACE, NAME_SPACE, POSITION_SPACE};

// -------- Declare Functions ----------//

void App(Company &company, bool &isRunning);

// --------  Input
int createNewEmployee(Company &company);

// -------  Actions
string inputString();
void pressAnyKey();
void printEmployeeList(Company &company);
bool confirm();

// -------  Compare
int compareString(string fString, string SString);

// ------ Import/Export from files
void readDataFromFile(Company &company);
void writeDataToFile(Company &company);

// ------- Main ------ //
int main()
{
    Company company;
    bool isRunning = true;
    while (isRunning)
    {
        App(company, isRunning);
        system("cls");
    }
    return 0;
}

void App(Company &company, bool &isRunning)
{
    cout << "\n============QUAN LY NHAN SU TRONG CONG TY============";
    cout << "\n=================MENU====================";
    cout << "\n*   1. Them nhan vien                   *"; // done
    cout << "\n*   2. Xoa nhan vien                    *"; // done
    cout << "\n*   3. Tim kiem nhan vien               *"; // done
    cout << "\n*   4. Cap nhat thong tin nhan vien     *"; // done
    cout << "\n*   5. Sap xep                          *"; // done
    cout << "\n*   6. Hien thi                         *"; // done
    cout << "\n*   7. Ghi du lieu vao file             *"; // done
    cout << "\n*   8. Thoat chuong trinh               *"; // done
    cout << "\n=========================================";
    cout << "\nNhap chuc nang: ";
    int key;
    cin >> key;
    switch (key)
    {
    case 1:
        createNewEmployee(company);
        cout << "Create new employee successful!" << endl;
        pressAnyKey();
        break;
    case 2:
        readDataFromFile(company);
        pressAnyKey();
        break;
    case 6:
        printEmployeeList(company);
        pressAnyKey();
        break;
    case 7:
        writeDataToFile(company);
        pressAnyKey();
        break;
    case 8:
        isRunning = false;
        cout << "Shutdown the program!";
        break;
    default:
        cout << "Khong co chuc nang nay !!" << endl;
        pressAnyKey();
        break;
    }
}

// ----------------------- Ham tuong tac ----------------- //
void pressAnyKey()
{
    cout << endl;
    cout << "\nPress any key to back!";
    getch();
    system("cls");
}

string inputString()
{
    string str;
    cin.ignore();
    getline(cin, str);
    return str;
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

int compareString(string fString, string SString)
{
    int i;
    while (fString[i] != '\0')
    {
        if (fString[i] != SString[i])
        {
            return 0;
        }
        i++;
    }
    cout << "Found" << endl;
    return 1;
}

string trim(string str)
{
    string result = str;
    result.erase(0, result.find_first_not_of(' ')); // loại bỏ khoảng trắng đầu chuỗi
    result.erase(result.find_last_not_of(' ') + 1); // loại bỏ khoảng trắng cuối chuỗi
    return result;
}
// Create Employee
int createNewEmployee(Company &company)
{
    EmployeeInfo newEmployee;
    cout << "Input name: ";
    newEmployee.name = inputString();
    cout << "Chose position: " << endl;
    bool isChose = false;
    bool isSelect = false;
    int select;
    while (!isChose)
    {
        cout << "1. President" << endl;
        cout << "2. Manager" << endl;
        cout << "3. Employee" << endl;
        cout << "4. Customer" << endl;
        cout << "Input your select: ";
        cin >> select;
        switch (select)
        {
        case 1:
            if (!confirm())
                break;
            isChose = true;
            newEmployee.position = "President";
            break;
        case 2:
            if (!confirm())
                break;
            isChose = true;
            newEmployee.position = "Manager";
            break;
        case 3:
            if (!confirm())
                break;
            isChose = true;
            newEmployee.position = "Employee";
            break;
        case 4:
            if (!confirm())
                break;
            isChose = true;
            newEmployee.position = "Customer";
            break;
        default:
            cout << "Invalid selection!";
            break;
        }
    }
    company.listOfEmployee.addLast(newEmployee);
    return 1;
}

// Print
void printEmployeeList(Company &company)
{
    Node *head = company.listOfEmployee.getHead();

    if (company.listOfEmployee.getLen() == 0)
    {
        cout << "Empty list !";
        return;
    }

    cout << setw(INDEX_SPACE) << "Index";
    cout << setw(NAME_SPACE) << "Name";
    cout << setw(POSITION_SPACE) << "Position";
    cout << endl;
    for (int i = 0; i < company.listOfEmployee.getLen(); i++)
    {
        if (head != NULL)
        {
            cout << setw(INDEX_SPACE) << i + 1;
            cout << setw(NAME_SPACE) << head->data.name;
            cout << setw(POSITION_SPACE) << head->data.position;
            cout << endl;
        }
        head = head->next;
    }
}

// Import/Export from files
void writeDataToFile(Company &company)
{
    char file[18] = "employee-list.txt";

    cout << "Exporting to " << file << "..." << endl;

    ofstream fileOut(file);
    Node *head = company.listOfEmployee.getHead();
    fileOut << company.listOfEmployee.getLen();
    fileOut << endl;
    fileOut << setw(INDEX_SPACE) << "Index";
    fileOut << setw(NAME_SPACE) << "Name";
    fileOut << setw(POSITION_SPACE) << "Position";
    fileOut << endl;

    for (int i = 0; i < company.listOfEmployee.getLen(); i++)
    {
        if (head != NULL)
        {
            fileOut << setw(INDEX_SPACE) << i + 1;
            fileOut << setw(NAME_SPACE) << head->data.name;
            fileOut << setw(POSITION_SPACE) << head->data.position;
            fileOut << endl;
        }
        head = head->next;
    }
    cout << "Exported to " << file << " successful." << endl;
}

EmployeeInfo handleDataFromLine(string data)
{
    cout << "Data length: " << data.length() << endl;
    EmployeeInfo employee;

    // Get name from file
    employee.name = trim(data.substr(INDEX_SPACE, NAME_SPACE));
    cout << "Name: " << employee.name << endl;

    // Get position from file
    employee.position = trim(data.substr(INDEX_SPACE + NAME_SPACE));
    cout << "Position: " <<employee.position << endl;

    return employee;
}

void readDataFromFile(Company &company)
{
    char file[18] = "employee-list.txt";
    cout << "Importing data from " << file << "..." << endl;

    ifstream fileIn(file);
    int numOfEmployees;
    fileIn >> numOfEmployees;

    string data; 
    getline(fileIn, data);
    getline(fileIn, data);
    for(int i = 0; i < numOfEmployees; i++) {
        getline(fileIn, data);
        EmployeeInfo employee = handleDataFromLine(data);
        company.listOfEmployee.addLast(employee);
    }

    cout << "Importing data from " << file << " successful." << endl;
}
