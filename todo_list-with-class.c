#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Task {
public:
    virtual void perform() = 0;
    virtual ~Task() {}
};

struct Todo {
    int id;
    string task;
};

class AddTask : public Task {
public:
    AddTask(int& id, vector<Todo>& todos) : ID(id), todos(todos) {}

    void perform() override {
        system("cls");
        Todo todo;
        cout << "\n\tEnter new task: ";
        cin.ignore();
        getline(cin, todo.task);
        ID++;

        todo.id = ID;
        todos.push_back(todo);

        ofstream write;
        write.open("todo.txt", ios::app);
        write << todo.id << "\n" << todo.task << "\n";
        write.close();

        write.open("id.txt");
        write << ID;
        write.close();

        char ch;
        cout << "\n\tDo you want to add more tasks? y/n: ";
        cin >> ch;

        if (ch == 'y' || ch == 'Y') {
            perform();
        }
        else {
            cout << "\n\tTask has been added successfully" << endl;
        }
    }

private:
    int& ID;
    vector<Todo>& todos;
};

class DisplayTask : public Task {
public:
    DisplayTask(const vector<Todo>& todos) : todos(todos) {}

    void perform() override {
        system("cls");
        cout << "\n\t------------------Your current Tasks in the list--------------------" << endl;

        if (todos.empty()) {
            cout << "\n\tNo tasks to display." << endl;
        }
        else {
            // Print the table headers
            cout << "----------------------------------------" << endl;
            cout << "  ID  |     Task     " << endl;
            cout << "----------------------------------------" << endl;

            for (const Todo& task : todos) {
                printTaskInTable(task);
            }

            cout << "----------------------------------------" << endl;
        }
    }

private:
    const vector<Todo>& todos;

    void printTaskInTable(const Todo& s) {
        cout << "  " << s.id << "   |   " << s.task << endl;
    }
};

int main() {
    vector<Todo> todos;
    int ID = 0;

    ifstream read;
    read.open("id.txt");
    if (!read.fail()) {
        read >> ID;
    }
    read.close();

    Task* tasks[2]; // A fixed-size array to store tasks

    tasks[0] = new AddTask(ID, todos);
    tasks[1] = new DisplayTask(todos);

    while (true) {
        cout << "\n\t 1. Add Task";
        cout << "\n\t 2. Show Task";
        cout << "\n\t 3. Search Task";
        cout << "\n\t 4. Delete Task";
        cout << "\n\t 5. Update Task";
        cout << "\n\t 6. Exit";

        int choice;
        cout << "\n\t Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                tasks[0]->perform(); // Add Task
                break;
            case 2:
                tasks[1]->perform(); // Show Task
                break;
            case 3:
                // Implement searchTask() logic
                break;
            case 4:
                // Implement deleteTask() logic
                break;
            case 5:
                // Implement updateTask() logic
                break;
            case 6:
                // Exit the program
                return 0;
            default:
                cout << "Invalid Option." << endl;
                break;
        }
    }

    // Clean up memory for dynamically allocated tasks
    delete tasks[0];
    delete tasks[1];

    return 0;
}
