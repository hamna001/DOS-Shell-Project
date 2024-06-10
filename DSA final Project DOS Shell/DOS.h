#pragma once
#include "Tree.h"
#include "File.h"
#include <cctype>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <conio.h> 
#include <string>
#include <sstream>

using namespace std;


class DOS
{
private:

   deque<File*> priorityPrintQueue;
   queue<File*> regularPrintQueue;


    string lower(string str)
    {
        for (char& c : str)
        {
            c = tolower(c);
        }
        return str;
    }

    bool prompt = false;

public:
    Tree t;
    string user = " ";

    DOS() {}

    void print()
    {
        cout << "\t\t\t\t\t" << "Hamna Kamran | 2022-CS-210 | DSA-UET-2023 " << endl 
            << endl;
        t.print();
    }

    void run()
    {
        print();
        bool exit = false;
        while (!exit)
        {
            exit = input();
        }
    }

                 void displayVersion()
                 {
                     std::cout << "DOS Version 1.0" << std::endl;
                 }


    bool input()
    {
        try
        {
            string command;
            getline(cin, command);
            string opr;
            size_t pos = command.find(' ');
            if (pos != string::npos)
            {
                opr = lower(command.substr(0, pos));
            }
            else
            {
                opr = lower(command);
            }

            //=============================

            if (opr == "mkdir") {
                string folderName = command.substr(6, command.length());


                if (t.Curr_Folder->FindFolder(folderName) == nullptr) {

                    t.Curr_Folder->CreateFolder(folderName);
                    cout << "Directory created successfully: " << folderName << endl;
                }
                else {
                    cout << "Directory already exists: " << folderName << endl;
                }
            }


            //=============================

            else if (opr == "creat")
            {
                size_t pos = command.find(' ');

                if (pos != string::npos)
                {
                    string fileName = command.substr(pos + 1);

                    if (t.Curr_Folder->FileExists(fileName))
                    {
                        cout << "File '" << fileName << "' already exists." << endl;
                    }
                    else
                    {

                        bool readOnly;
                        int priority;

                        cout << "Enter readOnly attribute (0 for No, 1 for Yes): ";
                        cin >> readOnly;

                        cout << "Enter priority attribute: ";
                        cin >> priority;


                        int timeToPrint = t.Curr_Folder->CalculateTimeToPrint();

                        ofstream newFile(fileName + ".txt");

                        if (newFile.is_open())
                        {
                            newFile.close();

                            File* f = new File(fileName, user);
                            f->readOnly = (readOnly != 0);
                            f->priority = priority;
                            f->timeToPrint = timeToPrint;

                            t.Curr_Folder->Files.push_back(f);
                            cout << "File '" << fileName << ".txt' created successfully." << endl;
                        }
                        else
                        {
                            cout << "Error creating file '" << fileName << ".txt'" << endl;
                        }
                    }
                }
                else
                {
                    cout << "Invalid 'creat' command. Usage: creat <filename>" << endl;
                }
            }





            //===============================
            else if (opr == "del")
            {
                size_t pos = command.find(' ');

                if (pos != string::npos)
                {
                    string fileName = command.substr(pos + 1);

                    if (t.Curr_Folder->FileExists(fileName))
                    {
                        t.Curr_Folder->RemoveFile(fileName);

                        string fullFileName = fileName + ".txt";

                        if (remove(fullFileName.c_str()) == 0)
                        {
                            cout << "File '" << fullFileName << "' deleted successfully." << endl;
                        }
                        else
                        {
                            cout << "Error deleting file '" << fullFileName << "'" << endl;
                        }
                    }
                    else
                    {
                        cout << "File '" << fileName << "' not found." << endl;
                    }
                }
                else
                {
                    cout << "Invalid 'del' command. Usage: del <filename>" << endl;
                }
            }


            //===============================

            else if (opr == "cd")
            {
                size_t pos = command.find(' ');

                if (pos != string::npos)
                {
                    string folder = command.substr(pos + 1);

                    //  cout << "Attempting to change to directory: " << folder << endl; 

                    if (t.Folder_Exists(folder))
                    {
                        t.Curr_Folder = t.FindFolder(folder);
                        cout << "Current directory changed to: " << t.Curr_Folder->path << "\\" << t.Curr_Folder->name << endl;
                    }
                    else
                    {
                        cout << "No such directory found: " << folder << endl;
                    }
                }
                else
                {
                    cout << "Invalid 'cd' command. Usage: cd <directory>" << endl;
                }
            }

            //===============================

            else if (opr == "cd..")
            {
                if (t.Curr_Folder->parent != nullptr)
                {
                    t.Curr_Folder = t.Curr_Folder->parent;
                    cout << "Current directory changed to: " << t.Curr_Folder->path << "\\" << t.Curr_Folder->name << endl;
                }
                else
                {
                    cout << "Already at the root directory." << endl;
                }
            }


            //===============================

            else if (opr == "cd\\")
            {
                t.Curr_Folder = t.root;
                cout << "Changed current directory to the root directory." << endl;
            }

            //===============================
            else if (opr == "dir" || opr == "cd.")
            {
                t.Curr_Folder->print();
            }
            //===============================
            else if (opr == "cls")
            {
                system("cls");
                print();
            }
            //===============================
            else if (opr == "exit")
            {
                return true;
            }
            //===============================

            else if (opr == "find")
            {
                size_t pos = command.find(' ');

                if (pos != string::npos)
                {
                    std::string name = command.substr(pos + 1);
                    File* foundFile = t.FindFile(name);

                    if (foundFile != nullptr)
                    {
                        std::cout << "File found. Content:\n" << foundFile->data << endl;
                    }
                    else
                    {
                        std::cout << "File not found." << std::endl;
                    }
                }
                else
                {
                    std::cout << "Invalid 'find' command. Usage: find <filename>" << endl;
                }
            }


            //===============================
            else if (opr == "attrib")
            {
                size_t pos = command.find(' ');

                if (pos != string::npos)
                {
                    std::string name = command.substr(pos + 1);
                    File* fileToDisplay = t.FindFile(name);

                    if (fileToDisplay != nullptr)
                    {
                        fileToDisplay->printAttributes();
                    }
                    else
                    {
                        std::cout << "File not found." << endl;
                    }
                }
                else
                {
                    std::cout << "Invalid 'attrib' command. Usage: attrib <filename>" << endl;
                }
            }

            //===============================
            else if (opr == "format")
            {
                for (auto file : t.Curr_Folder->Files)
                {
                    delete file;
                }
                t.Curr_Folder->Files.clear();

                for (auto folder : t.Curr_Folder->Folders)
                {
                    delete folder;
                }
                t.Curr_Folder->Folders.clear();
            }

            //===============================
            else if (opr == "rmdir")
            {
                size_t pos = command.find(' ');

                if (pos != string::npos)
                {
                    string folderName = command.substr(pos + 1);
                    Folder* folderToRemove = t.Curr_Folder->FindFolder(folderName);

                    if (folderToRemove != nullptr)
                    {
                        cout << "Found directory: " << folderToRemove->name << endl;


                        if (!folderToRemove->IsEmpty())
                        {
                            cout << "Directory '" << folderToRemove->name << "' is not empty. Remove its contents first." << endl;
                        }
                        else
                        {

                            t.Curr_Folder->RemoveFolder(folderToRemove->name);
                            cout << "Directory '" << folderToRemove->name << "' removed successfully." << endl;
                        }
                    }
                    else
                    {
                        cout << "Directory not found: " << folderName << endl;
                        cout << "Contents of the current folder:" << endl;
                        t.Curr_Folder->print();
                    }
                }
                else
                {
                    cout << "Invalid 'rmdir' command. Usage: rmdir <directory>" << endl;
                }

            }




            //===============================
            else if (opr == "prompt")
            {
                prompt = !prompt;

                if (prompt)
                {
                    t.print("$");
                }
                else
                {
                    t.print();
                }
            }

            //===============================
            else if (opr == "rename")
            {
                size_t pos = command.find(' ');

                if (pos != string::npos)
                {
                    string fileName = command.substr(pos + 1);
                    size_t spacePos = fileName.find(' ');
                    string currentname = fileName.substr(0, spacePos);
                    string new_name = fileName.substr(spacePos + 1);

                    File* f = t.Curr_Folder->FindFile(currentname);

                    if (f != nullptr)
                    {
                        f->name = new_name;
                        cout << "File '" << currentname << "' renamed to '" << new_name << "' successfully." << endl;
                    }
                    else
                    {
                        // cout << "File not found." << endl;
                    }
                }
                else
                {
                    cout << "Invalid 'rename' command. Usage: rename <currentname> <newname>" << endl;
                }
            }


            //===============================


            else if (opr == "copy")
            {
                command = command.substr(opr.length() + 1, command.length());
                int ind = command.find(' ');
                string sourcepath = command.substr(0, ind);
                string destinationpath = command.substr(ind + 1, command.length());


                stringstream str = stringstream(sourcepath);
                File* file_to_copy = nullptr;
                Folder* currentFolder = t.Curr_Folder;
                string g;
                while (getline(str, g, '\\')) {
                    Folder* next2 = currentFolder->FindFolder(g);
                    if (next2 == nullptr) {
                        File* next = currentFolder->FindFile(g);
                        if (next == nullptr) {
                            return false;
                        }
                        else {

                            file_to_copy = new File(*next);
                        }
                    }
                    currentFolder = next2;
                }


                stringstream str1 = stringstream(destinationpath);
                Folder* currentFolder1 = t.Curr_Folder;
                string f;
                while (getline(str1, f, '\\'))
                {
                    Folder* next = currentFolder1->FindFolder(f);
                    if (next == nullptr) {
                        return false;
                    }
                    currentFolder1 = next;
                }
                currentFolder1->InsertFile(file_to_copy);
                return true;
            }



            //===============================



            else if (opr == "move")
            {
                command = command.substr(opr.length() + 1, command.length());
                int ind = command.find(' ');
                string sourcepath = command.substr(0, ind);
                string destinationpath = command.substr(ind + 1, command.length());
                stringstream str = stringstream(destinationpath);
                Folder* currentFolder1 = t.Curr_Folder;
                string f;
                while (getline(str, f, '\\')) {
                    Folder* next = currentFolder1->FindFolder(f);
                    if (next == nullptr) {
                        return false;
                    }
                    currentFolder1 = next;
                }
                stringstream str1 = stringstream(sourcepath);
                File* file_to_move = nullptr;
                Folder* currentFolder = t.Curr_Folder;
                string g;
                while (getline(str1, g, '\\')) {
                    Folder* next2 = currentFolder->FindFolder(g);
                    if (next2 == nullptr) {
                        File* next = currentFolder->FindFile(g);
                        if (next == nullptr)
                        {
                            return false;
                        }
                        else {

                            currentFolder1->InsertFile(next);
                        }
                    }
                    currentFolder = next2;
                }
                return false;

            }



            //===============================

            else if (opr == "convert")
            {
                string file = command.substr(8, command.length());
                File* f = t.Curr_Folder->FindFile(file);
                if (f)
                {
                    string new_ext;
                    cout << "enter new extension" << endl;
                    cin >> new_ext;


                    if (new_ext == "txt" || new_ext == "text")
                    {
                        cout << "file extension changed to:" << new_ext << endl;

                    }
                    else
                    {
                        cout << "invalid" << endl;
                    }
                }
                else
                {
                    cout << "file not found" << endl;
                }
            }
        

            //===============================

            else if (opr == "edit") {
                size_t pos = command.find(' ');

                if (pos != std::string::npos) {
                    std::string fileName = command.substr(pos + 1);

                   
                    File* fileToEdit = t.Curr_Folder->FindFile(fileName);

                    if (fileToEdit != nullptr) {
                        system("cls");
                        system("color F0");

                             std::cout << "Editing file: " << fileName << ". Type your text and press ENTER to move to the next line. Press Ctrl+S to save." << std::endl;

                        int ch;
                        bool ctrlPressed = false;
                        while (true) {
                            ch = _getch();

                            if (ch == 13) {
                                fileToEdit->insertChar('\n');
                                std::cout << std::endl;
                            }
                            else if (ch == 27) {
                                std::cout << "Edit mode canceled." << std::endl;
                                system("color 0F");
                                return false;
                            }
                            else if (ch == 19) {
                                fileToEdit->saveToFile();
                                std::cout << "File saved." << std::endl;
                                      _getch();
                            }
                            else if (ch == 32) {
                                fileToEdit->insertChar(' ');
                                std::cout << ' ';
                            }
                            else if (ch == 8) {
                                fileToEdit->handleBackspace();
                                system("cls");
                                fileToEdit->print();
                                //     cout << "Editing file: " << fileName << ". Type your text and press ENTER to move to the next line. Press Ctrl+S to save." << endl;
                            }
                            else if (ch == 224)
                            {
                                ch = _getch();
                                if (ch == 75) {

                                    // ch = _getch();
                                     //if (ch == 75 )
                                    fileToEdit->moveCursorLeft();
                                }
                                else if (ch == 77) {
                                    fileToEdit->moveCursorRight();
                                }
                                //else if (ch == 26) { 
                                // //   fileToEdit->undo();
                                //}
                                //else if (ch == 18) {  
                                //   // fileToEdit->redo();
                                //}

                            }
                            else {
                                fileToEdit->insertChar(ch);
                            }
                            system("cls");
                            fileToEdit->print();
                            //    cout << "Editing file: " << fileName << ". Type your text and press ENTER to move to the next line. Press Ctrl+S to save." << endl;
                        }
                    }
                    else {
                        std::cout << "File not found." << std::endl;
                    }
                }
                else {
                    std::cout << "Invalid 'edit' command. Usage: edit <filename>" << std::endl;
                }

            }


            //===============================


            else if (opr == "findf")
            {
                string fileName;
                cout << "Enter the file name: ";
                getline(cin, fileName);

                File* f = t.Curr_Folder->FindFile(fileName);

                if (f)
                {
                    string searchString;
                    cout << "Enter the string to find: ";
                    getline(cin, searchString);

                    std::ifstream fileStream(f->name);

                    if (fileStream.is_open())
                    {
                        std::string line;
                        int lineNumber = 0;

                        while (std::getline(fileStream, line))
                        {
                            lineNumber++;

                            size_t found = line.find(searchString);
                            if (found != std::string::npos)
                            {
                                cout << "Found '" << searchString << "' in " << fileName << " at line " << lineNumber << ":" << endl;
                                cout << line << endl;
                            }
                        }

                        fileStream.close();
                    }
                    else
                    {
                        cout << "Error opening file '" << fileName << "' for reading." << endl;
                    }
                }
                else
                {
                    cout << "File not found." << endl;
                }
            }


            //===============================

            else if (opr == "pwd")
            {
                Folder* folder = t.Curr_Folder;
                while (folder != nullptr)
                {
                    cout << "/" << folder->name << endl;
                    folder = folder->parent;
                }
                cout << endl;
            }



            //===============================
            else if (opr == "tree")
            {
            Folder* f=t.Curr_Folder;
            f->displayDriveTree(f, 0);
            }
             //===============================


            else if (opr == "ver")
            {
                displayVersion();
            }

            //queue functions

            //===============================

            else if (opr == "pprint")
            {
                string fileName;
                cout << "Enter the file name to add to the priority print queue: ";
                getline(cin, fileName);

                File* fileToPrint = t.Curr_Folder->FindFile(fileName);

                if (fileToPrint)
                {
                    fileToPrint->fileaddToPrintQueue(fileToPrint, priorityPrintQueue);
                    cout << "File added to priority print queue successfully." << endl;
                }
                else
                {
                    cout << "File not found." << endl;
                }
            }
            else if (opr == "pqueue")
            {
                t.Curr_Folder->displayPriorityQueue(priorityPrintQueue);
            }

   
            else if (opr == "print")
            {
                string fileName;
                cout << "Enter the file name to add to the regular print queue: ";
                getline(cin, fileName);

                File* fileToPrint = t.Curr_Folder->FindFile(fileName);

                if (fileToPrint)
                {
                    fileToPrint->addToRegularQueue(fileToPrint, regularPrintQueue);
                    cout << "File added to regular print queue successfully." << endl;
                }
                else
                {
                    cout << "File not found." << endl;
                }
            }
            else if (opr == "queue")
            {
                t.Curr_Folder->displayQueue(regularPrintQueue);
            }
        



          //===============================
            else if (opr == "help")
            {
            cout << "enter mkdir for making directory"<<endl;
            cout << "enter creat for making file" << endl;
            cout << "enter del for deleting file" << endl;
            cout << "enter cd for changing directory" << endl;
            cout << "enter cd.. to goto root" << endl;
            cout << "enter cd// for going to v directory" << endl;
            cout << "cls for erasing everything" << endl;
            cout << "enter dir or cd. for printing dir" << endl;
            cout << "exit for canceling program" << endl;
            cout << "enter find for finding file" << endl;
            cout << "enter attrib for attributes of file" << endl;
            cout << "enter format for removing" << endl;
            cout << "enter rmdir for removing folder" << endl;
            cout << "prompt for changing sign" << endl;
            cout << "enter rename for renaming file" << endl;
            cout << "enter copy for copying file" << endl;
            cout << "enter move for moving file" << endl;
            cout << "enter convert for converting extension" << endl;
            cout << "edit for using notepad" << endl;
            cout << "findf for finding string" << endl;
            cout << "enter pwd for v" << endl;
            cout << "tree for seeing all folder and files" << endl;
            cout << "ver for seeing version" << endl;
            cout << "pprint to add file to priority queue" << endl;
            cout << "pqueue for current status" << endl;
            cout << "print for displaying current queue" << endl;
            cout << "queue for current status of queue" << endl;
            }
            //===============================
            else if (opr == "cls")
            {
                if (prompt)
                {
                    t.print("$");
                } 
                else
                {
                    t.print();
                }
                return false;
            }

            return false; 
        }
     
               

          //===============================




        catch (const std::exception& e)
        {
            std::cerr << "Exception caught: " << e.what() << std::endl;
            return false; 
        }
        catch (...)
        {
            std::cerr << "An unexpected exception occurred." << std::endl;
            return false; 
        }
    }
};
