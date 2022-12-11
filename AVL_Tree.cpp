#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

template <typename T>
struct ANode
{
	T data;
	ANode<T> *left;
	ANode<T> *right;
	int height;
	ANode()
	{
		left = NULL;
		right = NULL;
	}
};
template <typename Q>
class AVLTree
{
public:
	ANode<Q> *root;
	AVLTree()
	{
		root = NULL;
	}

	int GetHeight(ANode<Q> *current)
	{
		if ((current->left != NULL) && (current->right != NULL))
		{
			if (current->right->height < current->left->height)
				return current->left->height + 1;
			else
				return current->right->height + 1;
		}
		else if ((current->left == NULL) && (current->right != NULL))
		{
			return current->right->height + 1;
		}
		else if ((current->left != NULL) && (current->right == NULL))
		{
			return current->left->height + 1;
		}
		return 0;
	}
	int balance(ANode<Q> *current)
	{
		if ((current->left != NULL) && (current->right != NULL))
		{
			return current->left->height - current->right->height;
		}
		else if ((current->left == NULL) && (current->right != NULL))
		{
			return -(current->right->height);
		}
		else if ((current->left != NULL) && (current->right == NULL))
		{
			return current->left->height;
		}
	}
	ANode<Q> *left_left_rotate(ANode<Q> *temp)
	{
		ANode<Q> *temp2;
		ANode<Q> *temp3;
		temp2 = temp;
		temp3 = temp2->left;
		temp2->left = temp3->right;
		temp3->right = temp2;
		return temp3;
	}
	ANode<Q> *right_right_rotate(ANode<Q> *temp)
	{
		ANode<Q> *temp2;
		ANode<Q> *temp3;
		temp2 = temp;
		temp3 = temp2->right;
		temp2->right = temp3->left;
		temp3->left = temp2;
		return temp3;
	}
	ANode<Q> *right_left_rotate(ANode<Q> *temp)
	{					 // temp = n
		ANode<Q> *temp2; // temp2 =p
		ANode<Q> *temp3; // temp3 = tp
		ANode<Q> *temp4; // temp4 = tp2
		temp2 = temp;
		temp3 = temp2->right;
		temp4 = temp2->right->left;

		temp2->right = temp4->left;
		temp3->left = temp4->right;
		temp4->left = temp2;
		temp4->right = temp3;

		return temp4;
	}

	ANode<Q> *left_right_rotate(ANode<Q> *temp)
	{
		ANode<Q> *temp2;
		ANode<Q> *temp3;
		ANode<Q> *temp4;
		temp2 = temp;
		temp3 = temp2->left;
		temp4 = temp2->left->right;

		temp2->left = temp4->right;
		temp3->right = temp4->left;
		temp4->right = temp2;
		temp4->left = temp3;

		return temp4;
	}
	ANode<Q> *Pre_Order_Successor(ANode<Q> *current)
	{
		while (current->right != NULL)
			current = current->right;
		return current;
	}
	ANode<Q> *In_Order_Successor(ANode<Q> *current)
	{
		while (current->left != NULL)
			current = current->left;
		return current;
	}

	ANode<Q> *Insert(ANode<Q> *current, Q value)
	{
		if (current == NULL)
		{
			ANode<Q> *temp = new ANode<Q>;
			temp->data = value;
			current = temp;
			current->left = NULL;
			current->right = NULL;
			current->height = 1;
			return temp;
		}
		else
		{
			if (value < current->data)
				current->left = Insert(current->left, value);
			else
				current->right = Insert(current->right, value);
		}

		current->height = GetHeight(current);

		if ((balance(current) > 1) && (balance(current->left) == 1))
			current = left_left_rotate(current);
		else if ((balance(current) < -1) && (balance(current->right) == -1))
			current = right_right_rotate(current);
		else if ((balance(current) > 1) && (balance(current->left) == -1))
			current = left_right_rotate(current);
		else if ((balance(current) < -1) && (balance(current->right) == 1))
			current = right_left_rotate(current);
		return current;
	}

	ANode<Q> *deleteNode(ANode<Q> *current, Q data)
	{

		if (current->left == NULL && current->right == NULL)
		{
			if (current == this->root)
				this->root = NULL;
			delete current;
			return NULL;
		}

		ANode<Q> *temp2;
		if (current->data < data)
		{
			current->right = deleteNode(current->right, data);
		}
		else if (current->data > data)
		{
			current->left = deleteNode(current->left, data);
		}
		else
		{
			if (current->left != NULL)
			{
				temp2 = Pre_Order_Successor(current->left);
				current->data = temp2->data;
				current->left = deleteNode(current->left, temp2->data);
			}
			else
			{
				temp2 = In_Order_Successor(current->right);
				current->data = temp2->data;
				current->right = deleteNode(current->right, temp2->data);
			}
		}
		if (current->height == -2)
			cout << "Lmao";
		if (balance(current) == 2 && balance(current->left) == 1)
		{
			current = left_left_rotate(current);
		}
		else if (balance(current) == 2 && balance(current->left) == -1)
		{
			current = left_right_rotate(current);
		}
		else if (balance(current) == 2 && balance(current->left) == 0)
		{
			current = left_left_rotate(current);
		}
		else if (balance(current) == -2 && balance(current->right) == -1)
		{
			current = right_right_rotate(current);
		}
		else if (balance(current) == -2 && balance(current->right) == 1)
		{
			current = right_left_rotate(current);
		}
		else if (balance(current) == -2 && balance(current->right) == 0)
		{
			current = left_left_rotate(current);
		}

		return current;
	}

	void PreOrderTraversal(ANode<Q> *current, Q key)
	{
		if (current != NULL)
		{
			if (current->data == key)
			{
				cout << "Key found in AVL tree\n";
				return;
			}
			PreOrderTraversal(current->left, key);
			PreOrderTraversal(current->right, key);
		}
	}

	ANode<Q> *Root()
	{
		return this->root;
	}
};

void IndexOnIDAVL(string index, AVLTree<string> *t)
{
	string s, garbage;
	string file_name;

	int counter = 0;

	for (int i = 1; i <= 10; i++)
	{
		ifstream fin;
		file_name = "";
		file_name = "NCHS_-_Leading_Causes_of_Death__United_States_";
		file_name.append(to_string(i));
		file_name.append(".csv");
		fin.open(file_name);
		if (!fin)
		{
			cout << "File not opened\n";
		}
		else
		{
			getline(fin, garbage, '\n');
			while (!fin.eof())
			{

				getline(fin, s, ',');

				t->root = t->Insert(t->root, s);

				ofstream fw("./AVL_tree/ID/avl" + s + ".txt");
				getline(fin, garbage, '\n');
				fw << garbage << endl;
				fw.close();
			}
			fin.close();
		}
	}
}

void PointSearch_AVLTree(AVLTree<string> *t, string key,int index)
{
	{
		string data = "";
        string filename;
        if(index == 1) {
            filename = "./AVL_Tree/ID/avl" + key + ".txt";
        }
        if(index == 2) {
            filename = "./AVL_Tree/Year/avl" + key + ".txt";
        }
        if(index == 3) {
            filename = "./AVL_Tree/113_Cause_Name/avl" + key + ".txt";
        }
        if(index == 4) {
            filename = "./AVL_Tree/Cause_Name/avl" + key + ".txt";
        }
        if(index == 5) {
            filename = "./AVL_Tree/State/avl" + key + ".txt";
        }
        if(index == 6) {
            filename = "./AVL_Tree/Deaths/avl" + key + ".txt";
        }
        if(index == 7) {
            filename = "./AVL_Tree/Death_Rate/avl" + key + ".txt";
        }

		ifstream fin(filename);
		if (!fin)
		{
			cout << "ID with this key not found\n";
			return;
		}

		t->PreOrderTraversal(t->root, key);
		while(!fin.eof())
		{
			getline(fin, data, '\n');
			if(data!="") {
				cout << "The data for " << key << " is: " << data << endl;
			}

        }
		

		return;
	}
}

void DeleteRecord_AVLTree(string key, AVLTree<string> *t,int index)
{

	{
		cout << "Entered\n";
		t->root = t->deleteNode(t->root, key);
		string filename;
        if(index == 1) {
            filename = "./AVL_Tree/ID/avl" + key + ".txt";
        }
        if(index == 2) {
            filename = "./AVL_Tree/Year/avl" + key + ".txt";
        }
        if(index == 3) {
            filename = "./AVL_Tree/113_Cause_Name/avl" + key + ".txt";
        }
        if(index == 4) {
            filename = "./AVL_Tree/Cause_Name/avl" + key + ".txt";
        }
        if(index == 5) {
            filename = "./AVL_Tree/State/avl" + key + ".txt";
        }
        if(index == 6) {
            filename = "./AVL_Tree/Deaths/avl" + key + ".txt";
        }
        if(index == 7) {
            filename = "./AVL_Tree/Death_Rate/avl" + key + ".txt";
        }

		int length = filename.length();
		char char_array[length + 1];

		strcpy(char_array, filename.c_str());

		int r = remove(char_array);

		if (r == 0)
		{
			cout << "File remove succeessfully\n";
		}
		else
		{
			cout << "File not removed\n";
		}
	}
}

void RangeSearch_AVLTree(AVLTree<string> *t)
{
	int starting, ending;
	string choice;
	cout << "Enter on which field to perform Range Search\n";
	cin >> choice;
	cout << "Enter starting point: ";
	cin >> starting;
	cout << "Enter endiing point: ";
	cin >> ending;

	if (starting > ending)
	{
		cout << "Not valid\n";
		return;
	}
	for (int i = starting; i <= ending; i++)
	{

		string filename = "";
		filename = "./AVL_tree/" + choice + "/avl" + to_string(i) + ".txt";
		ifstream fr;
		fr.open(filename);
		if (!fr)
		{
			cout << "File not opened\n";
		}
		else
		{
			while (!fr.eof())
			{
				string data;
				getline(fr, data, '\n');
				if (data != "")
				{
					cout << "Data against " << i << " is: " << data << endl;
				}
			}
		}
		fr.close();
	}
}



void IndexAVL(AVLTree<string> *t, int index)
{
    fstream fin;

    int option;
    int count = 0;
    string one;

    switch (index)
    {
    case 2:
    {
        system("CLS");

        for (int i = 1; i <= 10; i++)
        {
            string file_name = "NCHS_-_Leading_Causes_of_Death__United_States_";
            file_name.append(to_string(i));
            file_name.append(".csv");

            fin.open(file_name);
            getline(fin, one, '\n');

            count = 1;
            string Year;

            while (!fin.eof())
            {
                for (int i = 0; i < count; i++)
                    getline(fin, one, ',');
                
                getline(fin, Year, ',');
                
                ofstream fw("./AVL_Tree/Year/avl" + Year + ".txt", ios::app);
                fw << one << ",";
                getline(fin, one);
                fw << one << endl;
                fw.close();

                t->root = t->Insert(t->root,Year);
                //cout << Year << endl;
            }
            fin.close();
        }
        system("Pause");
        break;
    }
    case 3:
    {
        system("CLS");
        for (int i = 1; i <= 10; i++)
        {
            string file_name = "NCHS_-_Leading_Causes_of_Death__United_States_";
            file_name.append(to_string(i));
            file_name.append(".csv");

            fin.open(file_name);
            getline(fin, one, '\n');

            count = 2;
            string cause_name;
            string id;
            while (!fin.eof())
            {
                string temp = "";
                for (int i = 0; i < count; i++) {
                    getline(fin, one, ',');
                    temp+=one;
                    temp+=',';
                }

                // Last line
                if (one == "")
                    break;

                getline(fin, cause_name, ',');

                string extra = "";
                bool yes = false;
                getline(fin, one, '\n');
                one += "\n";
                int j = 0;
                while (one[j] != '\n')
                {
                    if (one[j] == '"')
                    {
                        yes = true;
                        break;
                    }
                    extra += one[j];
                    j++;
                }

                temp+=cause_name;
                temp+=',';
                if (yes)
                {
                    cause_name += extra;
                    cause_name += '"';
                }
                temp+=one;
                ofstream fw("./AVL_Tree/113_Cause_Name/avl" + cause_name + ".txt", ios::app);
                fw << temp << endl;
                fw.close();
               
				t->root = t->Insert(t->root,cause_name);
            }
            fin.close();
        }
        system("Pause");
        break;
    }
    case 4:
    {
        system("CLS");
        for (int i = 1; i <= 10; i++)
        {
            string file_name = "NCHS_-_Leading_Causes_of_Death__United_States_";
            file_name.append(to_string(i));
            file_name.append(".csv");

            fin.open(file_name);
            getline(fin, one, '\n');
            int m = 0;
            count = 2;
            string cause_name;

            while (!fin.eof())
            {
                string temp="";
                for (int i = 0; i < count; i++)
                {
                    getline(fin, one, ',');
                    temp += one;
                    temp += ',';
                }
                if (one == "")
                    break;

                getline(fin, cause_name, ',');

                string extra = "";
                bool yes = false;
                getline(fin, one, '\n');
                one += "\n";
                int j = 0;
                while (one[j] != '\n')
                {
                    if (one[j] == '"')
                    {
                        yes = true;
                        break;
                    }
                    extra += one[j];
                    j++;
                }

                temp +=cause_name;
                temp+=',';
                if (yes)
                {
                    cause_name += extra;
                    cause_name += '"';
                }
                temp+=one;
                cause_name = "";
                int k = 0;
                if (yes)
                    k = j + 2;

                while (one[k] != ',')
                {
                    cause_name += one[k];
                    k++;
                }
                m++;
                
                ofstream fw("./AVL_Tree/Cause_Name/avl" + cause_name + ".txt", ios::app);
                fw << temp << endl;
                fw.close();

                t->root = t->Insert(t->root,cause_name);
                
            }
            

            fin.close();
        }
        system("Pause");
        break;
    }
    case 5:
    {
        system("CLS");
        for (int i = 1; i <= 10; i++)
        {
            string file_name = "NCHS_-_Leading_Causes_of_Death__United_States_";
            file_name.append(to_string(i));
            file_name.append(".csv");

            fin.open(file_name);
            getline(fin, one, '\n');
            count = 2;
            string cause_name;

            while (!fin.eof())
            {
                string temp="";
                for (int i = 0; i < count; i++)
                {
                    getline(fin, one, ',');
                    temp+=one;
                    temp+=',';
                }
                if (one == "")
                    break;

                getline(fin, cause_name, ',');

                string extra = "";
                bool yes = false;
                getline(fin, one, '\n');
                one += "\n";
                int j = 0;
                while (one[j] != '\n')
                {
                    if (one[j] == '"')
                    {
                        yes = true;
                        break;
                    }
                    extra += one[j];
                    j++;
                }
                temp+=cause_name;
                temp+=',';
                if (yes)
                {
                    cause_name += extra;
                    cause_name += '"';
                }
                temp+=one;
                cause_name = "";
                int k = 0;
                if (yes)
                    k = j + 2;

                while (one[k] != ',')
                {
                    cause_name += one[k];
                    k++;
                }
                k++;
                cause_name = "";
                while (one[k] != ',')
                {
                    cause_name += one[k];
                    k++;
                }
                ofstream fw("./AVL_Tree/State/avl" + cause_name + ".txt", ios::app);
                fw << temp << endl;
                fw.close();

                t->root = t->Insert(t->root,cause_name);
                
            }
            fin.close();
        }
        system("Pause");
        break;
    }
    case 6:
    {
        system("CLS");
        for (int i = 1; i <= 10; i++)
        {
            string file_name = "NCHS_-_Leading_Causes_of_Death__United_States_";
            file_name.append(to_string(i));
            file_name.append(".csv");

            fin.open(file_name);
            getline(fin, one, '\n');
            count = 2;
            string cause_name;

            while (!fin.eof())
            {
                string temp="";
                for (int i = 0; i < count; i++)
                {
                    getline(fin, one, ',');
                    temp+=one;
                    temp+=',';
                }
                if (one == "")
                    break;

                getline(fin, cause_name, ',');

                string extra = "";
                bool yes = false;
                getline(fin, one, '\n');
                one += "\n";
                int j = 0;
                while (one[j] != '\n')
                {
                    if (one[j] == '"')
                    {
                        yes = true;
                        break;
                    }
                    extra += one[j];
                    j++;
                }
                temp+=cause_name;
                temp+=',';
                if (yes)   
                {
                    cause_name += extra;
                    cause_name += '"';
                }
                temp+=one;
                cause_name = "";
                int k = 0;
                if (yes)
                    k = j + 2;

                while (one[k] != ',')
                {
                    cause_name += one[k];
                    k++;
                }
                k++;
                cause_name = "";
                while (one[k] != ',')
                {
                    cause_name += one[k];
                    k++;
                }
                k++;
                cause_name = "";
                while (one[k] != ',')
                {
                    cause_name += one[k];
                    k++;
                }
                ofstream fw("./AVL_Tree/Deaths/avl" + cause_name + ".txt", ios::app);
                fw << temp << endl;
                fw.close();

                t->root = t->Insert(t->root,cause_name);
                
            }
            fin.close();
        }
        system("Pause");
        break;
    }
    case 7:
    {
        system("CLS");
        for (int i = 1; i <= 10; i++)
        {
            string file_name = "NCHS_-_Leading_Causes_of_Death__United_States_";
            file_name.append(to_string(i));
            file_name.append(".csv");

            fin.open(file_name);
            getline(fin, one, '\n');
            count = 2;
            string cause_name;

            while (!fin.eof())
            {
                string temp="";
                for (int i = 0; i < count; i++)
                {
                    getline(fin, one, ',');
                    temp+=one;
                    temp+=',';
                }
                if (one == "")
                    break;

                getline(fin, cause_name, ',');

                string extra = "";
                bool yes = false;
                getline(fin, one, '\n');
                one += "\n";
                int j = 0;
                while (one[j] != '\n')
                {
                    if (one[j] == '"')
                    {
                        yes = true;
                        break;
                    }
                    extra += one[j];
                    j++;
                }
                temp+=cause_name;
                temp+=',';
                if (yes)
                {
                    cause_name += extra;
                    cause_name += '"';
                }
                temp+=one;
                cause_name = "";
                int k = 0;
                if (yes)
                    k = j + 2;

                while (one[k] != ',')
                {
                    cause_name += one[k];
                    k++;
                }
                k++;
                cause_name = "";
                while (one[k] != ',')
                {
                    cause_name += one[k];
                    k++;
                }
                k++;
                cause_name = "";
                while (one[k] != ',')
                {
                    cause_name += one[k];
                    k++;
                }
                k++;
                cause_name = "";
                while (one[k] != '\n')
                {
                    cause_name += one[k];
                    k++;
                }
                ofstream fw("./AVL_Tree/Death_Rate/avl" + cause_name + ".txt", ios::app);
                fw << temp << endl;
                fw.close();

                t->root = t->Insert(t->root,cause_name);

            }
            fin.close();
        }
        system("Pause");
        break;
    }
    case 8:
    {
        exit(1);
    }
    }
}
