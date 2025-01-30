#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include "todo/Todo.h"

class TodoGUI : public QMainWindow {
    Q_OBJECT

public:
    explicit TodoGUI(QWidget* parent = nullptr);
    virtual ~TodoGUI();  // Add virtual keyword

private slots:  // Change back to private slots
    void addTask();
    void removeTask();
    void completeTask();

private:
    void updateTaskList();
    void save();

    TodoList* todoList;
    QLineEdit* inputTask;
    QPushButton* addButton;
    QListWidget* taskList;
    QPushButton* removeButton;
    QPushButton* completeButton;
};
