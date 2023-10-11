#include <iostream>
#include <fstream>
#include <string>

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
    AddTask(int& id, Todo*& todos, int& size) : ID(id), todos(todos), arraySize(size) {}

    void perform() override {
        system("cls");
        cout << "\t*******************************************************************" << endl;
        cout << "\t*                      To Do List Application                     *" << endl;
        cout << "\t*******************************************************************" << endl << endl << endl << endl;

        Todo todo;
        cout << "\n\tEnter new task: ";
        cin.get();
        getline(cin, todo.task);
        ID++;

        if (arraySize == 0) {
            arraySize = 1;
            todos = new Todo[arraySize];
        }
        else {
            arraySize++;
            Todo* newTodos = new Todo[arraySize];
            for (int i = 0; i < arraySize - 1; i++) {
                newTodos[i] = todos[i];
            }
            delete[] todos;
            todos = newTodos;
        }

        todos[arraySize - 1] = { ID, todo.task };

        ofstream write;
        write.open("todo.txt", ios::app);
        write << "\n" << ID << "\n" << todo.task;
        write.close();

        write.open("id.txt");
        write << ID;
        write.close();

        char ch;
        cout << "\n\tDo you want to add more tasks? y/n: ";
        cin >> ch;

        if (ch == 'y') {
            perform();
        }
        else {
            cout << "\n\tTask has been added successfully";
        }
    }

private:
    int& ID;
    Todo*& todos;
    int& arraySize;
};

class DisplayTask : public Task {
public:
    DisplayTask(const Todo* todos, int size) : todos(todos), arraySize(size) {}

    void perform() override {
        system("cls");
        cout << "\t*******************************************************************" << endl;
        cout << "\t*                      To Do List Application                     *" << endl;
        cout << "\t*******************************************************************" << endl << endl << endl << endl;

        cout << "\n\t------------------Your current Tasks in the list--------------------" << endl;

        for (int i = 0; i < arraySize; i++) {
            print(todos[i]);
        }
    }

private:
    const Todo* todos;
    int arraySize;

    static void print(const Todo& s) {
        cout << "\n\tID is : " << s.id;
        cout << "\n\tTask is : " << s.task;
    }
};

int main() {
    Todo* todos = nullptr;
    int ID = 0;
    int arraySize = 0;

    ifstream read;
    read.open("id.txt");
    if (!read.fail()) {
        read >> ID;
    }
    read.close();

    Task* tasks[2]; // A fixed-size array to store tasks

    while (true) {
        cout << endl;
        cout << "\n\t1.Add Task";
        cout << "\n\t2.Display Task";

        int choice;
        cout << "\n\n\tEnter choice : ";
        cin >> choice;

        switch (choice) {
        case 1:
            tasks[0] = new AddTask(ID, todos, arraySize);
            tasks[0]->perform();
            break;
        case 2:
            tasks[1] = new DisplayTask(todos, arraySize);
            tasks[1]->perform();
            break;
        }
    }

    // Deallocate memory for tasks
    for (int i = 0; i < 2; i++) {
        delete tasks[i];
    }

    // Deallocate memory for todos
    delete[] todos;

    return 0;
}
