
#include "todo/Todo.h"  // Updated include path
#include <iostream>

int main() {
    TodoList todoList;
    std::string filename = "tasks.txt";
    
    // Try to load existing tasks
    todoList.loadFromFile(filename);
    
    while (true) {
        std::cout << "\n1. Add Task\n"
                  << "2. Remove Task\n"
                  << "3. Mark Task as Completed\n"
                  << "4. Show Tasks\n"
                  << "5. Save and Exit\n"
                  << "Choose an option: ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1: {
                std::cout << "Enter task description: ";
                std::string description;
                std::getline(std::cin, description);
                todoList.addTask(description);
                break;
            }
            case 2: {
                std::cout << "Enter task ID to remove: ";
                int id;
                std::cin >> id;
                todoList.removeTask(id);
                break;
            }
            case 3: {
                std::cout << "Enter task ID to mark as completed: ";
                int id;
                std::cin >> id;
                todoList.markAsCompleted(id);
                break;
            }
            case 4:
                todoList.showTasks();
                break;
            case 5:
                todoList.saveToFile(filename);
                return 0;
            default:
                std::cout << "Invalid option!\n";
        }
    }
    
    return 0;
}