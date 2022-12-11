#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

template <class T>
struct Node
{
    T data;
    Node* parent;
    Node* left;
    Node* right;
    int col;
};

template <class Q>
class RedBlackTree
{
public:
    Node<Q>* root;
    Node<Q>* temp;

    RedBlackTree()
    {
        temp = new Node<Q>;
        temp->col = 0;
        temp->left = nullptr;
        temp->right = nullptr;
        root = temp;
    }
    // Inorder traversal
    void print_InOrder(Node<Q>* t)
    {
        if (t != temp)
        {
            print_InOrder(t->left);
            cout << t->data << " ";
            print_InOrder(t->right);
        }
    }

    Node<Q>* Search_Tree(Node<Q>* t, Q key)
    {
        if (t == temp || key == t->data)
        {
            return t;
        }
        if (key < t->data)
        {
            return Search_Tree(t->left, key);
        }
        return Search_Tree(t->right, key);
    }

    //fixing when deleted 
    void deleteFix(Node<Q>* x)
    {
        Node<Q>* s;
        while (x != root && x->col == 0)
        {
            if (x == x->parent->left)
            {
                s = x->parent->right;
                if (s->col == 1)
                {
                    s->col = 0;
                    x->parent->col = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->col == 0 && s->right->col == 0)
                {
                    s->col = 1;
                    x = x->parent;
                }
                else
                {
                    if (s->right->col == 0)
                    {
                        s->left->col = 0;
                        s->col = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->col = x->parent->col;
                    x->parent->col = 0;
                    s->right->col = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                s = x->parent->left;
                if (s->col == 1)
                {
                    s->col = 0;
                    x->parent->col = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->col == 0 && s->right->col == 0)
                {
                    s->col = 1;
                    x = x->parent;
                }
                else
                {
                    if (s->left->col == 0)
                    {
                        s->right->col = 0;
                        s->col = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->col = x->parent->col;
                    x->parent->col = 0;
                    s->left->col = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->col = 0;
    }

    void rbTransplant(Node<Q>* u, Node<Q>* v)
    {
        if (u->parent == nullptr)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(Node<Q>* node, Q key)
    {
        Node<Q>* z = temp;
        Node<Q>* x, * y;
        while (node != temp)
        {
            if (node->data == key)
            {
                z = node;
            }

            if (node->data <= key)
            {
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }

        if (z == temp)
        {
            cout << "Key not found in the tree" << endl;
            return;
        }

        y = z;
        int y_original_col = y->col;
        if (z->left == temp)
        {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == temp)
        {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            y_original_col = y->col;
            x = y->right;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->col = z->col;
        }
        delete z;
        if (y_original_col == 0)
        {
            deleteFix(x);
        }
    }

    
    void insertFix(Node<Q>* k) // For balancing the tree after insertion
    {
        Node<Q>* temp;

        while (k->parent->col == 1)
        {
            if (k->parent == k->parent->parent->right)
            {
                temp = k->parent->parent->left;
                if (temp->col == 1) //changing color if red
                {
                    temp->col = 0;
                    k->parent->col = 0;
                    k->parent->parent->col = 1;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->left)
                    {
                        k = k->parent;
                        rightRotate(k); //rotating right
                    }
                    int m = 0;

                    k->parent->col = 0; //changing color of parent to black

                    k->parent->parent->col = 1; //now making it's parent red and then left rotating it

                    leftRotate(k->parent->parent);
                }
            }
            else // if parent is not equal to the grandparent's right
            {
                temp = k->parent->parent->right;

                if (temp->col == 1) //if red
                {
                    temp->col = 0; //change it to black
                    k->parent->col = 0;
                    k->parent->parent->col = 1;
                    //switching colors
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->right) //if black then left rotate then right rotate to fix balance 
                    {
                        k = k->parent;
                        leftRotate(k);
                    }
                    int q = 0;
                    k->parent->col = 0;
                    k->parent->parent->col = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) 
            {
                break;
            }
        }
        root->col = 0;
    }

    void printHelper(Node<Q>* root, string indent, bool last)
    {
        if (root != temp)
        {
            cout << indent;
            if (last)
            {
                cout << "R----";
                indent += "   ";
            }
            else
            {
                cout << "L----";
                indent += "|  ";
            }

            string scol = root->col ? "RED" : "BLACK";
            cout << root->data << "(" << scol << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }


    void inorder()
    {
        print_InOrder(this->root);
    }

    Node<Q>* searchTree(Q k)
    {
        return Search_Tree(this->root, k);
    }

    Node<Q>* minimum(Node<Q>* node)
    {
        while (node->left != temp)
        {
            node = node->left;
        }
        return node;
    }

    Node<Q>* maximum(Node<Q>* node)
    {
        while (node->right != temp)
        {
            node = node->right;
        }
        return node;
    }

    Node<Q>* successor(Node<Q>* x)
    {
        if (x->right != temp)
        {
            return minimum(x->right);
        }

        Node<Q>* y = x->parent;
        while (y != temp && x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    Node<Q>* predecessor(Node<Q>* x)
    {
        if (x->left != temp)
        {
            return maximum(x->left);
        }

        Node<Q>* y = x->parent;
        while (y != temp && x == y->left)
        {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(Node<Q>* x)
    {
        Node<Q>* y = x->right;
        x->right = y->left;
        if (y->left != temp)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node<Q>* x)
    {
        Node<Q>* y = x->left;
        x->left = y->right;
        if (y->right != temp)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Inserting a node
    void insert(Q key)
    {
        Node<Q>* node = new Node<Q>;
        node->parent = nullptr;
        node->data = key;
        node->left = temp;
        node->right = temp;
        node->col = 1;

        Node<Q>* y = nullptr;
        Node<Q>* x = this->root;

        while (x != temp)
        {
            y = x;
            if (node->data < x->data)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr)
        {
            root = node;
        }
        else if (node->data < y->data)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }

        if (node->parent == nullptr)
        {
            node->col = 0;
            return;
        }

        if (node->parent->parent == nullptr)
        {
            return;
        }

        insertFix(node);
    }

    Node<Q>* getRoot()
    {
        return this->root;
    }

    void deleteNode(Q data)
    {
        deleteNodeHelper(this->root, data);
    }

    void printTree()
    {
        if (root)
        {
            printHelper(this->root, "", true);
        }
    }
};

void IndexOnIDRB(string index, RedBlackTree<string> *t)
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
            while (!fin.eof())
            {

                getline(fin, garbage, '\n');

                getline(fin, s, ',');

                getline(fin, garbage, '\n');
                t->insert(s);
                ofstream fw("./RB_tree/ID/rb" + s + ".txt");
                fw << garbage << endl;
                fw.close();
            }
            fin.close();
        }
    }
}

void DeleteRecord_RBTree(string key, RedBlackTree<string> *t)
{

    if (t->searchTree(key) == NULL)
    {
        cout << "Key not found to be Deleted\n";
        return;
    }
    else
    {
        cout << "Entered\n";
        t->deleteNode(key);
        string filename = "./RB_tree/ID/rb" + key + ".txt";
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

void PointSearch_RBTree(RedBlackTree<string> *t, string key,int index)
{
    if (t->searchTree((key)) == NULL)
    {
        cout << "Key not found\n";
        return;
    }
    else
    {
        string data = "";
        string filename;
        if(index == 1) {
            filename = "./RB_tree/ID/rb" + key + ".txt";
        }
        if(index == 2) {
            filename = "./RB_tree/Year/rb" + key + ".txt";
        }
        if(index == 3) {
            filename = "./RB_tree/113_Cause_Name/rb" + key + ".txt";
        }
        if(index == 4) {
            filename = "./RB_tree/Cause_Name/rb" + key + ".txt";
        }
        if(index == 5) {
            filename = "./RB_tree/State/rb" + key + ".txt";
        }
        if(index == 6) {
            filename = "./RB_tree/Deaths/rb" + key + ".txt";
        }
        if(index == 7) {
            filename = "./RB_tree/Death_Rate/rb" + key + ".txt";
        }
        ifstream fin(filename);
        if (!fin)
        {
            cout << "ID with this key not found\n";
            return;
        }

        while(!fin.eof()){

                getline(fin, data, '\n');
                if(data!="") {
                    cout << "The data for " << key << " is: " << data << endl;
                }

            }
        return;
    }
}

void RangeSearch_RBTree(RedBlackTree<string> *t)
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

        if (t->searchTree(to_string(i)) == NULL)
        {
            cout << i << " not found\n";
        }
        else
        {
            string filename = "";
            filename = "./RB_tree/" + choice + "/rb" + to_string(i) + ".txt";
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
}


void IndexRBTree(RedBlackTree<string> *t, int index)
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
                
                ofstream fw("./RB_tree/Year/rb" + Year + ".txt", ios::app);
                fw << one << ",";
                getline(fin, one);
                fw << one << endl;
                fw.close();

                t->insert(Year);
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
                ofstream fw("./RB_tree/113_Cause_Name/rb" + cause_name + ".txt", ios::app);
                fw << temp << endl;
                fw.close();

                t->insert(cause_name);
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
                
                ofstream fw("./RB_tree/Cause_Name/rb" + cause_name + ".txt", ios::app);
                fw << temp << endl;
                fw.close();

                t->insert(cause_name);
                
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
                ofstream fw("./RB_tree/State/rb" + cause_name + ".txt", ios::app);
                fw << temp << endl;
                fw.close();

                t->insert(cause_name);
                
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
                ofstream fw("./RB_tree/Deaths/rb" + cause_name + ".txt", ios::app);
                fw << temp << endl;
                fw.close();

                t->insert(cause_name);
                
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
                ofstream fw("./RB_tree/Death_Rate/rb" + cause_name + ".txt", ios::app);
                fw << temp << endl;
                fw.close();

                t->insert(cause_name);
               
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


void DeleteRecord_RBTree(string key, RedBlackTree<string> *t,int index)
{

    if (t->searchTree(key) == NULL)
    {
        cout << "Key not found to be Deleted\n";
        return;
    }
    else
    {
        t->deleteNode(key);
        string filename;
        if(index == 1) {
            filename = "./RB_tree/ID/rb" + key + ".txt";
        }
        if(index == 2) {
            filename = "./RB_tree/Year/rb" + key + ".txt";
        }
        if(index == 3) {
            filename = "./RB_tree/113_Cause_Name/rb" + key + ".txt";
        }
        if(index == 4) {
            filename = "./RB_tree/Cause_Name/rb" + key + ".txt";
        }
        if(index == 5) {
            filename = "./RB_tree/State/rb" + key + ".txt";
        }
        if(index == 6) {
            filename = "./RB_tree/Deaths/rb" + key + ".txt";
        }
        if(index == 7) {
            filename = "./RB_tree/Death_Rate/rb" + key + ".txt";
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
