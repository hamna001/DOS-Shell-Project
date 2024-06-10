#pragma once
#include <string>
#include <iostream>
#include <fstream> 
#include <ctime>
#include <stack>
#include <iterator>
#include <list>
#include <deque>
#include <queue>

using namespace std;

class Folder;

class File {

private:
    struct Node
    {
        char data;
        Node* next;
        Node* prev;

        Node(char ch, Node* n = nullptr, Node* p = nullptr) : data(ch), next(n), prev(p) {}
    };

    Node* head;
    Node* tail;
    Node* cursor;
    int cursorPosition;

  /*  stack<list<char>> undoStack;
    stack<list<char>> redoStack;*/

public:
    list<char> dataList;
    list<char>::iterator Cursor;
    string name;
    string data;
    Folder* parent;
    time_t creation_time;
    string owner;
    bool hidden;
    size_t size;

    bool readOnly;
    int priority;
    int timeToPrint;

    File(string n = "NULL", std::string d = "", Folder* parent_ = nullptr, bool h = false) {
        name = n;
        data = d;
        parent = parent_;
        hidden = h;
        readOnly = false;
        priority = 0;
        timeToPrint = 0;
        cursorPosition = 0;
        head = tail = cursor = nullptr;
    }

    void print() {
        cout << "File: " << name << std::endl;

        for (list<char>::iterator i = dataList.begin(); i != dataList.end(); i++)
        {
            cout << *i;
            if (i == Cursor) {
                cout << "|";
            }
        }
    }

    void printAttributes() const {
        std::cout << "File Name: " << name << endl;
        std::cout << "File Size: " << size << " bytes" << endl;
        std::cout << "ReadOnly: " << (readOnly ? "Yes" : "No") <<endl;
        std::cout << "Priority: " << priority << std::endl;
        std::cout << "Time to Print: " << timeToPrint << " seconds" << endl;
    }

    void insertChar(char ch) {
        if (dataList.empty())
        {
            dataList.push_back(ch);
            Cursor = dataList.begin();
        }
        dataList.insert(Cursor, ch);
    }

    void handleBackspace() {
        if (Cursor != dataList.begin()) {
            Cursor = dataList.erase(--Cursor);
           // pushUndo();
        }
    }

    void moveCursorRight() {
        if (Cursor != dataList.end())
            Cursor++;
    }

    void moveCursorLeft() {
        if (Cursor != dataList.begin())
            Cursor--;
    }

    void saveToFile() {
        ofstream file(name);
        if (!file.is_open()) {
            std::cerr << "Error opening file '" << name << "' for writing." << endl;
            return;
        }

        for (char ch : dataList) {
            file << ch;
        }

        file.close();
        cout << "Changes saved to file." << std::endl;
    }

    void addToPrintQueue(File* file, deque<File*>& printQueue) {
        printQueue.push_back(file);

        displayPriorityQueue(printQueue);
    }

    void addToRegularQueue(File* file, queue<File*>& printQueue) {
        printQueue.push(file);

        displayQueue(printQueue);
    }

    void displayPriorityQueue(const deque<File*>& printQueue) {

        std::cout << "Priority Based Print Queue:" << std::endl;
        for (const File* file : printQueue) {
            cout << file->name << " - Time Left: " << file->timeToPrint << " seconds" <<endl;
        }
    }

    void displayQueue(const queue<File*>& printQueue) {

        std::cout << "Print Queue:" << std::endl;
        std::queue<File*> tempQueue = printQueue;
        while (!tempQueue.empty()) {
            File* file = tempQueue.front();
            tempQueue.pop();
            cout << file->name << " - Time Left: " << file->timeToPrint << " seconds" << endl;
        }
    }

   void fileaddToPrintQueue(File* file, deque<File*>& printQueue)
   {
        printQueue.push_back(file);
   }

   

   


};