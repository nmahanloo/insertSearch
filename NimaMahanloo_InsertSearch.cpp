// Nima Mahanloo
// CISP 430
// InsertSearch
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cassert>
using namespace std;
// A node object of the binary tree
struct node
{
  char* name = (char*)malloc(sizeof(char));
  node* left = nullptr;
  node* right = nullptr;
  node* names = nullptr;
};
// Find the proper order for read name in the tree
void findPlace (node* (&curr), char* thisName)
{
  if (strcmp(curr->name, thisName) == 0)
  {
    while (curr->names)
    {
      curr  = curr->names;
    }
    curr->names = new node;
    curr = curr->names;
  }
  else if (strcmp(curr->name, thisName) < 0)
  {
    if (curr->left)
    {
      curr = curr->left;
      findPlace(curr, thisName);
    }
    else
    {
      curr->left = new node;
      curr = curr->left;
    }
  }
  else if (strcmp(curr->name, thisName) > 0)
  {
    if (curr->right)
    {
      curr = curr->right;
      findPlace(curr, thisName);
    }
    else
    {
      curr->right = new node;
      curr = curr->right;
    }  
  }
}
// Insert the read name on the tree in proper order
void pushName (node* (&tree), char* thisName)
{
  node* curr = tree;
  if (curr->name[0] != '\0')
  {
    findPlace (curr, thisName);
  }
  curr->name = thisName;
}
// Search the binary tree for a name
int treeSearch (node* tree, char* keyName)
{
  if (strcmp(tree->name, keyName) < 0)
  {
    if (tree->left)
    {
      tree = tree->left;
      treeSearch (tree, keyName);
    }
    else
      return 0;
  }
  else if (strcmp(tree->name, keyName) > 0)
  {
    if (tree->right)
    {
      tree = tree->right;
      treeSearch (tree, keyName);
    }
    else
      return 0;
  }
  else if (strcmp(tree->name, keyName) == 0)
  {
    int count = 1;
    while (tree->names)
    {
      count++;
      tree = tree->names;
    }
    return count;
  }
}
// Convert input name characters to lower case characters
char* toLower (char* thisName)
{
  int i = 0;
  char* lowerName = (char*)malloc(sizeof(char));
  while (thisName[i] != '\0')
  {
    lowerName[i] = tolower(thisName[i]);
    i++;
  }
  lowerName[i] = '\0';
  return lowerName;
}
// Read names from the file
void readFile (node* (&tree))
{
  ifstream readName ("names.txt");
  if (readName.is_open())
  {
    while (!(readName.eof()))
    {
      char* thisName = (char*)malloc(sizeof(char));
      char* lowerName = (char*)malloc(sizeof(char));
      readName >> thisName;
      lowerName = toLower(thisName);
      pushName (tree, lowerName);
      free (thisName);
    }
    readName.close ();
  }
  else
  {
    cout << "Error: Can't read the file!" << endl;
    assert (readName.is_open ());
  }
}
// Get a name from user to search for that in the binary tree
void search (node* tree)
{
  int result = 0;
  char* keyName = (char*)malloc(sizeof(char));
  char* lowerName = (char*)malloc(sizeof(char));
  cout << "Please enter a name to start search > ";
  cin >> keyName;
  lowerName = toLower(keyName);
  result = treeSearch(tree, lowerName);
  cout << "There is " << result << " '" << keyName << "' available in the binary tree!" << endl;
  free (keyName);
  free (lowerName);
}
// The binary tree destructor
void destructTree (node* (&tree))
{
	if (tree->names)
	{
		tree = tree->names;
		destructTree (tree);
		delete tree;
		tree = nullptr;
	}
	else if (tree->left)
	{
		tree = tree->left;
		destructTree (tree);
		delete tree;
		tree = nullptr;
	}
	else if (tree->right)
	{
		tree = tree->right;
		destructTree (tree);
		delete tree;
		tree = nullptr;		
	}
	else
	    delete tree;
	    tree = nullptr;	
}

int main()
{
  node* tree = new node;
  readFile (tree);
  search (tree);
  destructTree (tree);
/*  if (tree)
      cout << "Destructor failed!" << endl;
  else
      cout << "Tree deleted successfully!" << endl;*/
  return 0;
}