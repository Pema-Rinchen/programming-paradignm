#include <iostream> 
#include <string>
#include <fstream>

using namespace std; 

// Put all the functions and the Structure inside a Class
//parent class

struct todolist
{
    int id;
    string task;
};

int ID = 0;

void banner() {
    // Add the Todo List Banner (something fancy like a box)
}

void addTask() {
    system("cls");
    banner();
    todolist todo;
    cout << "Enter a New Task: " << endl;
    cin.get();
    getline(cin, todo.task);
    char save;
    cout << "Save? (y/n): ";
    cin >> save;

    if (save == 'y')
    {
        ID++;
        ofstream fout;
        fout.open("todo.txt", ios::app);
        fout << "\n" << ID;
        fout << "\n" << todo.task;
        fout.close();

        char more;
        cout << "Add More Tasks? (y/n): ";
        cin >> more;

        if (more == 'y')
        {
           addTask();
        }
        
        else
        {
            system("cls");
            cout << "Added Successfully!" << endl;
            return;
        }
    }

    system("cls");
}

void showTask() {
    system("cls");
    banner();
    todolist todo;
    
    ifstream fin;
    fin.open("todo.txt");
    cout << "Task: " << endl;

    while (!fin.eof())
    {
        fin >> todo.id;
        fin.ignore();
        getline(fin, todo.task);

        if (todo.task != "")
        {
            cout << "\t" << todo.id << ": " << todo.task << endl;
        }

        else
        {
            cout << "\tEmpty!" << endl;
        }
        
    }

    fin.close();
    char exit;
    cout << "Exit? (y/n): ";
    cin >> exit;

    if (exit != 'y')
    {
        showTask();
    }

    system("cls");
    
}

int searchTask() {
    system("cls");
    banner();
    int id;
    cout << "Enter Task ID: ";
    cin >> id;
    todolist todo;

    ifstream fin("todo.txt");
    
    while (!fin.eof())
    {
        fin >> todo.id;
        fin.ignore();
        getline(fin, todo.task);

        if (todo.id == id)
        {
            system("cls");
            cout << "\t" << todo.id << ": " << todo.task << endl;
            
            return id;
        }
        
    }

    system("cls");
    cout << "Task Not Found" << endl;
    return 0;
    
}

void deleteTask() {
    system("cls");
    int id = searchTask();

    if (id != 0)
    {
        char del;
        cout << "\n\tDelete? (y/n): ";
        cin >> del;

        if (del == 'y')
        {
            todolist todo;

            ofstream tempFile;
            tempFile.open("temp.txt");
            
            ifstream fin;
            fin.open("todo.txt");
            
            int index = 1;

            while (!fin.eof())
            {
                fin >> todo.id;
                fin.ignore();
                getline(fin, todo.task);

                if (todo.id != id)
                {
                    tempFile << "\n" << index;
                    tempFile << "\n" << todo.task;
                    index++;
                    ID--;
                }
                
            }

            fin.close();
            tempFile.close();
            remove("todo.txt");
            rename("temp.txt", "todo.txt");

            system("cls");
            cout << "\n\tDeleted Successfully!" << endl;
            
        }

        else 
        {
            system("cls");
            cout << "Task Not Deleted." << endl;
        }
        
    }
    
}

void updateTask() {
    system("cls");
    int id = searchTask();

    if (id != 0) 
    {
        todolist todo;

        ifstream fin("todo.txt");
        ofstream tempFile("temp.txt");

        while (!fin.eof()) 
        {
            fin >> todo.id;
            fin.ignore();
            getline(fin, todo.task);

            if (todo.id == id) 
            {
                cout << "\nCurrent Task: " << todo.task << endl;
                cout << "Enter the Updated Task: ";
                cin.get();
                getline(cin, todo.task);
            }

            tempFile << "\n" << todo.id;
            tempFile << "\n" << todo.task;
        }

        fin.close();
        tempFile.close();
        remove("todo.txt");
        rename("temp.txt", "todo.txt");

        system("cls");
        cout << "\nTask Updated Successfully!" << endl;
    }
}


int main() {
    system("cls");
    while (true)
    {
        banner();
        cout << "\n\t 1. Add Task";
        cout << "\n\t 2. Show Task";
        cout << "\n\t 3. Search Task";
        cout << "\n\t 4. Delete Task";
        cout << "\n\t 5. Update Task";

        int choice;
        cout << "\n\t Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                addTask();
                break;
            }

            case 2:
            {
                showTask();
                break;
            }

            case 3:
            {
                searchTask();
                break;
            }

            case 4:
            {
                deleteTask();
                break;
            }

            case 5:
            {
                updateTask();
                break;
            }


            default:
                cout << "Invalid Option." << endl;
                break;
        }

    }

    
    return 0;
}
