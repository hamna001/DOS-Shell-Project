#pragma once
#include <List>
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include "File.h"
using namespace std;

class Folder
{
  public:
	string name;
	vector<Folder*> Folders;
	vector<File*> Files;
	Folder* parent;
	time_t creation_time;
	string owner;
	string path;
	bool hidden;

  public:
	  Folder(string n="NULL",string p="",Folder* parent_=nullptr,vector<File*> fs=vector<File*>(),vector<Folder*> FS=vector<Folder*>())
	  {
		  name = n;
		  Folders = FS;
		  Files = fs;
		  path = p;
		  parent = parent_;
	  }

	  void RemoveFile(string name)
	  {
		  for (int i = 0; i < Files.size(); i++)
		  {
			  if (Files[i]->name == name)
			  {
				  swap(Files[i], Files[Files.size() - 1]);
				  Files.pop_back();
			  }
		  }
	  }

	  void RemoveFolder(string name)
	  {
		  for (int i = 0; i < Folders.size(); i++)
		  {
			  if (Folders[i]->name == name)
			  {
				  Folders[i]->EmptyDir();

				  swap(Folders[i], Folders[Folders.size() - 1]);
				  Folders.pop_back();
			  }
		  }
	  }
	  void printFolders()
	  {
		  if (Folders.empty())
		  {
			  cout << "No subfolders." << endl;
			  return;
		  }

		  cout << "Subfolders:" << endl;
		  for (const auto& folder : Folders)
		  {
			  cout << folder->name << endl;
		  }
	  }


	  void EmptyDir()
	  {
		  Files.resize(0);
		  Folders.resize(0);
	  }

	  File* FindFile(string name)
	  {
		  for (int i = 0; i < Files.size(); i++)
		  {
			  if (Files[i]->name == name)
			  {
				  return Files[i];
			  }
		  }
		  return nullptr;
	  }

	  /*Folder* FindFolder(string name)
	  {
		  for (int i = 0; i < Folders.size(); i++)
		  {
			  if (Folders[i]->name == name)
			  {
				  return Folders[i];
			  }
		  }
		  return nullptr;
	  }*/

	  Folder* FindFolder(string name)
	  {
		  for (int i = 0; i < Folders.size(); i++)
		  {
			  if (Folders[i]->name == name)
			  {
				  cout << "Found folder: " << name << endl;
				  return Folders[i];
			  }
		  }

		//  cout << "Folder not found: " << name << endl;
		//  cout << "Contents of the current folder:" << endl;
		  print(); 

		  return nullptr;
	  }


	  void InsertFile(File* f)
	  {
		  Files.push_back(f);
	  }
	  void InsertFolder(Folder* f)
	  {
		  Folders.push_back(f);
	  }

	  void print()
	  {
		  cout << "Directory of" << path << "\\" << name << endl;
		  for (int i = 0; i < Folders.size(); i++)
		  {
			  cout << "                      <DIR>      " << Folders[i]->name << endl;
		  }
		  for (int i = 0; i < Files.size(); i++)
		  {
			  cout << "                                 " << Files[i]->name << endl;
		  }
	  }

	  bool FileExists(const string& fileName) const
	  {
		  for (const auto& file : Files)
		  {
			  if (file->name == fileName)
			  {
				  return true;
			  }
		  }
		  return false;
	  }

	  int CalculateTimeToPrint() 
	  {
	
		  const int baseTime = 5; 
		  const int timePerCharacter = 1;  

		  int dataLength = 0;
		  for (const auto& file : Files)
		  {
			  dataLength += file->data.length();
		  }

		  return baseTime + timePerCharacter * dataLength;
	  }

	  bool IsEmpty() const {
		  return Files.empty() && Folders.empty();
	  }


	  void displayPriorityQueue(const std::deque<File*>& printQueue)
	  {
		  std::cout << "Priority Based Print Queue:" << endl;
		  for (const File* file : printQueue) {
			  std::cout << file->name << " - Time Left: " << file->timeToPrint << " seconds" << endl;
		  }
	  }

	  void displayQueue(const std::queue<File*>& printQueue) {

		  std::cout << "Print Queue:" <<endl;
		  std::queue<File*> tempQueue = printQueue;
		  while (!tempQueue.empty()) {
			  File* file = tempQueue.front();
			  tempQueue.pop();
			  std::cout << file->name << " - Time Left: " << file->timeToPrint << " seconds" << endl;
		  }
	  }

	  

	  void CreateFolder(const std::string& folderName) {
		  Folder* newFolder = new Folder(folderName);
		  InsertFolder(newFolder);
	  }


	  void displayDriveTree(Folder* r, int depth)
	  {
		  if (!r)
			  return;
		  for (Folder* temp : r->Folders)
		  {
			  cout << "|";
			  for (int i = 0; i < depth; i++)
			  {
				  cout << "\t";
			  }
			  cout << "|--";
			  cout << temp->name << endl;
			  displayDriveTree(temp, depth + 1);
		  }

		  for (File* temp : r->Files)
		  {
			  cout << "|";
			  for (int i = 0; i < depth; i++)
			  {
				  cout << "\t";
			  }
			  cout << "|--";
			  cout << temp->name << "." << "txt" << endl;
		  }
	  }



};

