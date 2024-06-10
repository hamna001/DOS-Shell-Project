#pragma once
#include "Folder.h"

class Tree
{
public:
    Folder* root;
    Folder* Curr_Folder;

public:
    Tree()
    {
        Curr_Folder = root = new Folder("V");
    }

    void insert(Folder* f)
    {
        Curr_Folder->Folders.push_back(f);
        SetPath(f);
    }

    void SetPath(Folder* f)
    {
        string path = Curr_Folder->name;
        Folder* parent = Curr_Folder->parent; 
        while (parent != nullptr)
        {
            path = parent->name + "/" + path;
            parent = parent->parent; 
        }
        f->path = path;
    }


    void print(string prompt = "\\>")
    {
        if (Curr_Folder->name == "V")
        {
            cout << "V:" << prompt;
        }
        else
        {
            cout << "V:" << Curr_Folder->path.substr(2, Curr_Folder->path.length()) << "\\" << Curr_Folder->name << prompt;
        }
    }

    bool Folder_Exists(string name)
    {
        for (int i = 0; i < Curr_Folder->Folders.size(); i++) 
        {
            if (Curr_Folder->Folders[i]->name == name)
            {
                return true;
            }
        }
        return false;
    }

    File* FindFile(string name)
    {
        for (int i = 0; i < Curr_Folder->Files.size(); i++) 
        {
            if (Curr_Folder->Files[i]->name == name)
            {
                return Curr_Folder->Files[i];
            }
        }
        return nullptr;
    }

    Folder* FindFolder(string name)
    {
        for (int i = 0; i < Curr_Folder->Folders.size(); i++)
        {
            if (Curr_Folder->Folders[i]->name == name)
            {
                return Curr_Folder->Folders[i];
            }
        }
        return nullptr;
    }
   
};
