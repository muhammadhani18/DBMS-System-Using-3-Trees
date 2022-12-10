#include <iostream>
#include <fstream>
using namespace std;

template <typename T>
struct ANode
{
	T data;
	ANode<T>* left;
	ANode<T>* right;
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
	ANode<Q>* root;
	AVLTree()
	{
		root = NULL;
	}

	int GetHeight(ANode<Q>* current) 
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
	int balance(ANode<Q>* current)
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
	ANode<Q>* left_left_rotate(ANode<Q>* temp)
	{
		ANode<Q>* temp2;
		ANode<Q>* temp3;
		temp2 = temp;
		temp3 = temp2->left;
		temp2->left = temp3->right;
		temp3->right = temp2;
		return temp3;
	}
	ANode<Q>* right_right_rotate(ANode<Q>* temp)
	{
		ANode<Q>* temp2;
		ANode<Q>* temp3;
		temp2 = temp;
		temp3 = temp2->right;
		temp2->right = temp3->left;
		temp3->left = temp2;
		return temp3;
	}
	ANode<Q>* right_left_rotate(ANode<Q>* temp)
	{					//temp = n
		ANode<Q>* temp2;//temp2 =p
		ANode<Q>* temp3;// temp3 = tp 
		ANode<Q>* temp4;// temp4 = tp2
		temp2 = temp;
		temp3 = temp2->right;
		temp4 = temp2->right->left;

		temp2->right = temp4->left;
		temp3->left = temp4->right;
		temp4->left = temp2;
		temp4->right = temp3;

		return temp4;
	}


	ANode<Q>* left_right_rotate(ANode<Q>* temp)
	{
		ANode<Q>* temp2;
		ANode<Q>* temp3;
		ANode<Q>* temp4;
		temp2 = temp;
		temp3 = temp2->left;
		temp4 = temp2->left->right;

		temp2->left = temp4->right;
		temp3->right = temp4->left;
		temp4->right = temp2;
		temp4->left = temp3;

		return temp4;
	}
	ANode<Q>* Pre_Order_Successor(ANode<Q>* current) {
		while (current->right != NULL)
			current = current->right;
		return current;
	}
	ANode<Q>* In_Order_Successor(ANode<Q>* current) {
		while (current->left != NULL)
			current = current->left;
		return current;
	}



	ANode<Q>* Insert(ANode<Q>* current, Q value)
	{
		if (current == NULL)
		{
			ANode<Q>* temp = new ANode<Q>;
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

	ANode<Q>* deleteNode(ANode<Q>* current, Q data) {

		if (current->left == NULL && current->right == NULL) {
			if (current == this->root)
				this->root = NULL;
			delete current;
			return NULL;
		}

		ANode<Q>* temp2;
		if (current->data < data) {
			current->right = deleteNode(current->right, data);
		}
		else if (current->data > data) {
			current->left = deleteNode(current->left, data);
		}
		else {
			if (current->left != NULL) {
				temp2 = Pre_Order_Successor(current->left);
				current->data = temp2->data;
				current->left = deleteNode(current->left, temp2->data);
			}
			else {
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


	void PreOrderTraversal(ANode<Q>* current)
	{
		if (current != NULL)
		{
			cout << current->data << " ";
			PreOrderTraversal(current->left);
			PreOrderTraversal(current->right);
		}
		else
			return;
	}
	void PostOrderTraversal(ANode<Q>* current)
	{
		if (current != NULL)
		{
			PostOrderTraversal(current->left);
			PostOrderTraversal(current->right);
			cout << current->data << " ";
		}
		else
			return;
	}
	void InOrderTraversal(ANode<Q>* current)
	{
		if (current != NULL)
		{
			InOrderTraversal(current->left);
			cout << current->data << " ";
			InOrderTraversal(current->right);
		}
		else
			return;
	}
	ANode<Q>* Root()
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

				t->root = t->Insert(t->root,s);

                ofstream fw("./AVL_tree/ID/avl" + s + ".txt");
                getline(fin, garbage, '\n');
                fw << garbage << endl;
                fw.close();
            }
            fin.close();
        }
    }
}
