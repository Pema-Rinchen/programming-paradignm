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
int ID = 0;

void banner() {
  // include banner
}

class AddTask : public Task {
public:
    AddTask(int& id, vector<Todo>& todos) : ID(id), todos(todos) {}

    void perform() override {
        system("cls");
        banner();
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
// inherited class of the class task
class DisplayTask : public Task {
public:
    DisplayTask(const vector<Todo>& todos) : todos(todos) {}

    void perform() override {
        system("cls");
        banner();
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

class SearchTask : public Task {
public:
    SearchTask(const vector<Todo>& todos) : todos(todos) {}

    void perform() override {
        system("cls");
        banner();
        cout << "\n\t------------------Search Task--------------------" << endl;
        int id;
        cout << "Enter Task ID: ";
        cin >> id;

        for (const Todo& task : todos) {
            if (task.id == id) {
                system("cls");
                cout << "Task Found:" << endl;
                cout << "  ID  |     Task     " << endl;
                cout << "----------------------------------------" << endl;
                printTaskInTable(task);
                return;
            }
        }

        system("cls");
        cout << "Task Not Found" << endl;
    }

private:
    const vector<Todo>& todos;

    void printTaskInTable(const Todo& s) {
        cout << "  " << s.id << "   |   " << s.task << endl;
    }
};

class DeleteTask : public Task {
public:
    DeleteTask(vector<Todo>& todos) : todos(todos) {}

    void perform() override {
        system("cls");
        banner();
        cout << "\n\t------------------Delete Task--------------------" << endl;
        int id;
        cout << "Enter Task ID to delete: ";
        cin >> id;

        for (auto it = todos.begin(); it != todos.end(); ++it) {
            if (it->id == id) {
                todos.erase(it);
                system("cls");
                cout << "Task Deleted Successfully!" << endl;
                return;
            }
        }

        system("cls");
        cout << "Task Not Found" << endl;
    }

private:
    vector<Todo>& todos;
};

class UpdateTask : public Task {
public:
    UpdateTask(vector<Todo>& todos) : todos(todos) {}

    void perform() override {
        system("cls");
        banner();
        cout << "\n\t------------------Update Task--------------------" << endl;
        int id;
        cout << "Enter Task ID to update: ";
        cin >> id;

        for (Todo& task : todos) {
            if (task.id == id) {
                system("cls");
                cout << "Current Task: " << task.task << endl;
                cout << "Enter the Updated Task: ";
                cin.ignore();
                getline(cin, task.task);
                system("cls");
                cout << "Task Updated Successfully!" << endl;
                return;
            }
        }

        system("cls");
        cout << "Task Not Found" << endl;
    }

private:
    vector<Todo>& todos;
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

    Task* tasks[5]; // A fixed-size array to store tasks

    tasks[0] = new AddTask(ID, todos);
    tasks[1] = new DisplayTask(todos);
    tasks[2] = new SearchTask(todos);
    tasks[3] = new DeleteTask(todos);
    tasks[4] = new UpdateTask(todos);

    while (true) {
        banner();
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
                tasks[2]->perform(); // Search Task
                break;
            case 4:
                tasks[3]->perform(); // Delete Task
                break;
            case 5:
                tasks[4]->perform(); // Update Task
                break;
            case 6:
                // Exit the program
                break;
            default:
                cout << "Invalid Option." << endl;
                break;
        }

        if (choice == 6) {
            // Exit the loop
            break;
        }
    }

    // Clean up memory for dynamically allocated tasks
    for (int i = 0; i < 5; ++i) {
        delete tasks[i];
    }

    return 0;
}
