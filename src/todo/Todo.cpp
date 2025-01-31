#include "todo/Todo.h"
#include <iostream>
#include <fstream>
#include <algorithm>  // Add this line for std::remove_if
#include <iomanip>
#include <sstream>

std::string TodoList::formatTimestamp(time_t timestamp) {
    std::stringstream ss;
    ss << std::put_time(localtime(&timestamp), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void TodoList::addTask(const std::string& description) {
    tasks.push_back({nextId++, description, false, std::time(nullptr)});
}

void TodoList::removeTask(int id) {
    tasks.erase(
        std::remove_if(tasks.begin(), tasks.end(),
            [id](const Task& task) { return task.id == id; }),
        tasks.end()
    );
}

void TodoList::markAsCompleted(int id) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.completed = true;
            break;
        }
    }
}

void TodoList::showTasks() const {
    for (const auto& task : tasks) {
        std::cout << "ID: " << task.id << " [" 
                 << (task.completed ? "✓" : " ") << "] "
                 << task.description
                 << " (Created: " << formatTimestamp(task.timestamp) << ")"
                 << std::endl;
    }
}

void TodoList::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return; // Silently fail if can't open file
    }
    for (const auto& task : tasks) {
        file << task.id << "|" << task.description << "|" 
             << task.completed << "|" << task.timestamp << "\n";
    }
}

void TodoList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return; // Silently fail if file doesn't exist
    }
    tasks.clear();
    nextId = 1;
    
    std::string line;
    while (std::getline(file, line)) {
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1 + 1);
        size_t pos3 = line.find("|", pos2 + 1);
        if (pos1 != std::string::npos && pos2 != std::string::npos && pos3 != std::string::npos) {
            int id = std::stoi(line.substr(0, pos1));
            std::string desc = line.substr(pos1 + 1, pos2 - pos1 - 1);
            bool completed = (line.substr(pos2 + 1, pos3 - pos2 - 1) == "1");
            time_t timestamp = std::stoll(line.substr(pos3 + 1));
            tasks.push_back({id, desc, completed, timestamp});
            if (id >= nextId) nextId = id + 1;
        }
    }
}

std::vector<Task> TodoList::getTasks() const {
    return tasks;
}
