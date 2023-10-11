#include <iostream>
#include <string>

class Task {
public:
    Task(int id, const std::string& task) : id(id), task(task), next(nullptr) {}

    int getID() const {
        return id;
    }

    void display() const {
        std::cout << id << "\t\t" << task << std::endl;
    }

    Task* getNext() const {
        return next;
    }

    void setNext(Task* task) {
        next = task;
    }

private:
    int id;
    std::string task;
    Task* next;
};

class ToDoList {
public:
    ToDoList() : first(nullptr) {}

    void addTask(const std::string& taskStr) {
        int nextID = getNextID();
        Task* newTask = new Task(nextID, taskStr);
        if (!first) {
            first = newTask;
        } else {
            Task* current = first;
            while (current->getNext()) {
                current = current->getNext();
            }
            current->setNext(newTask);
        }
        std::cout << "Task added successfully!" << std::endl;
    }

    void showTasks() const {
        if (!first) {
            std::cout << "No tasks to display." << std::endl;
            return;
        }

        // Print table header
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "ID\t\tTask" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;

        // Iterate through tasks and display them in a table format
        Task* current = first;
        while (current) {
            current->display();
            current = current->getNext();
        }

        std::cout << "-----------------------------------------" << std::endl;
    }

    void deleteTask(int id) {
        if (!first) {
            std::cout << "Task not found." << std::endl;
            return;
        }

        if (first->getID() == id) {
            Task* temp = first;
            first = first->getNext();
            delete temp;
            std::cout << "Task deleted successfully!" << std::endl;
            return;
        }

        Task* current = first;
        while (current->getNext()) {
            if (current->getNext()->getID() == id) {
                Task* temp = current->getNext();
                current->setNext(current->getNext()->getNext());
                delete temp;
                std::cout << "Task deleted successfully!" << std::endl;
                return;
            }
            current = current->getNext();
        }
        std::cout << "Task not found." << std::endl;
    }

    ~ToDoList() {
        while (first) {
            Task* temp = first;
            first = first->getNext();
            delete temp;
        }
    }

private:
    Task* first;

    int getNextID() const {
        int nextID = 1;
        Task* current = first;
        while (current) {
            if (current->getID() >= nextID) {
                nextID = current->getID() + 1;
            }
            current = current->getNext();
        }
        return nextID;
    }
};

int main() {
    ToDoList todoList;

    while (true) {
        std::cout << "1. Add Task\n2. Show Tasks\n3. Delete Task\n4. Exit\n";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cin.ignore();
                std::string taskStr;
                std::cout << "Enter a New Task: ";
                std::getline(std::cin, taskStr);
                todoList.addTask(taskStr);
                break;
            }
            case 2:
                std::cout << "Tasks:\n";
                todoList.showTasks();
                break;
            case 3: {
                std::cout << "Enter the ID of the task to delete: ";
                int id;
                std::cin >> id;
                todoList.deleteTask(id);
                break;
            }
            case 4:
                return 0;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
        }
    }

    return 0;
}
