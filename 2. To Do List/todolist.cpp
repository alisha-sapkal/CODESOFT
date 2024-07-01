#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Start{
public:
    string description;
    bool isCompleted;

    Start(string desc) : description(desc), isCompleted(false) {}
};

class ToDoList{
private:
    vector<Start> task;

    void display(){
        cout << "To Do List" << endl;
        cout << "1. ADD TASK" << endl;
        cout << "2. VIEW TASK" << endl;
        cout << "3. MARK AS COMPLETED" << endl;
        cout << "4. REMOVE TASK" << endl;
        cout << "5. EXIT" <<endl;
        cout << "ENTER YOUR CHOICE: ";
    }

    int getInput(){
        int choice;
        cin >> choice;
        while(choice < 1 || choice > 5){
            cout << "Invalid choice. Enter the valid choice: ";
            cin >> choice;
        }
        return choice;
    }

public:
    void addTask() {
    string description;
    cout << "ENTER THE DESCRIPTION OF YOUR TASK: ";
    cin.ignore();
    getline(cin, description);
    task.emplace_back(description);
    cout << "TASK ADDED SUCCESSFULLY.\n" << endl;
}

void viewTasks() {
    if (task.empty()) {
        cout << "NO TASK IN YOUR LIST.\n" << endl;
        return;
    }
    cout << "TASKS: \n" << endl;
    for (int i = 0; i < task.size(); i++) {
        cout << i + 1 << ". " << task[i].description << " - " << (task[i].isCompleted ? "COMPLETED\n" : "PENDING\n") << endl;
    }
}

void mark() {
    if (task.empty()) {
        cout << "NO TASK TO MARK AS COMPLETE IN YOUR LIST.\n" << endl;
        return;
    }
    int n;
    cout << "ENTER THE TASK NUMBER TO MARK AS COMPLETED: ";
    cin >> n;
    while (n < 1 || n > task.size()) {
        cout << "INVALID TASK NUMBER. ENTER A VALID TASK NUMBER: ";
        cin >> n;
    }
    task[n - 1].isCompleted = true;
    cout << "TASK IS MARKED AS COMPLETED.\n" << endl;
}

void remove() {
    if (task.empty()) {
        cout << "NO TASK TO REMOVE.\n" << endl;
        return;
    }
    int n;
    cout << "ENTER THE TASK NUMBER TO REMOVE: ";
    cin >> n;
    while (n < 1 || n > task.size()) {
        cout << "INVALID TASK NUMBER. ENTER A VALID TASK NUMBER: ";
        cin >> n;
    }
    task.erase(task.begin() + n - 1);
    cout << "TASK REMOVED SUCCESSFULLY\n" << endl;
}

void output() {
    while (true) {
        display();
        int choice = getInput();

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                mark();
                break;
            case 4:
                remove();
                break;
            case 5:
                cout << "EXITING...\n" << endl;
                return;
            default:
                cout << "INVALID CHOICE, PLEASE TRY AGAIN\n" << endl;
        }
    }
}

}; 

int main(){
    ToDoList tdl;
    tdl.output();
    return 0;
}