#pragma once
#include <string>
#include <vector>

struct Task {
    int id;
    std::string description;
    bool completed;
};

class TodoList {
public:
    TodoList() : nextId(1) {}  // Add this constructor
    void addTask(const std::string& description);
    void removeTask(int id);
    void markAsCompleted(int id);
    void showTasks() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    std::vector<Task> getTasks() const;

private:
    std::vector<Task> tasks;
    int nextId = 1;
};
