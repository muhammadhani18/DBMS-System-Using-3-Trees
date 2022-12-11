#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

template <class T>
struct BNode
{
    T* key;
    int degree;
    BNode<T>** C;
    int order;
    bool isLeaf;
    string filename;

    BNode<T>(int degree_val, string filename_val, bool leaf_val)
    {
        degree = degree_val;
        isLeaf = leaf_val;
        key = new T[2 * degree - 1];
        C = new BNode * [2 * degree];
        filename = filename_val;
        order = 0;
    }
    void Traverse()
    {
        int i = 0;
        for (; i < order; i++)
        {
            if (isLeaf == false)
                C[i]->Traverse();

            cout << key[i] << "  ";
        }

        if (isLeaf == false)
            C[i]->Traverse();
    }

    BNode<T>* search(T data)
    {
        int i = 0;
        while (i < order && data > key[i])
        {
            i++;
        }

        if (key[i] == data)
            cout << "Key found\n";
            return C[i];

        if (isLeaf == true)
            return NULL;

        return C[i]->search(data);
    }

    int findKey(T data) {
        int Index = 0;
        while (Index < order && key[Index] < data) {
            ++Index;
        }
        return Index;
    }

    void Deletion(T data)
    {
        int Index = findKey(data);

        if (Index < order && key[Index] == data)
        {
            if (isLeaf)
                removeFromLeaf(Index);
            else
                removeFromNonLeaf(Index);
        }
        else
        {
            if (isLeaf)
            {
                cout << "ID DOES NOT EXIST TO BE DELETED\n";
                return;
            }

            bool flag;// = ((Index == n) ? true : false);
            if (Index == order) {
                flag = true;
            }
            else {
                flag = false;
            }
            if (C[Index]->order < degree) {

                fill(Index);
            }

            if (flag && Index > order) {

                C[Index - 1]->Deletion(data);
            }
            else {

                C[Index]->Deletion(data);
            }
        }
        return;
    }
    void removeFromLeaf(int Index)
    {
        for (int i = Index + 1; i < order; ++i) {

            key[i - 1] = key[i];
        }

        order--;

        return;
    }
    void removeFromNonLeaf(int Index)
    {
        T data = key[Index];

        if (C[Index]->order >= degree)
        {
            T pred = getPredecessor(Index);
            key[Index] = pred;
            C[Index]->Deletion(pred);
        }

        else if (C[Index + 1]->degree >= degree)
        {
            T succ = getSuccessor(Index);
            key[Index] = succ;
            C[Index + 1]->Deletion(succ);
        }

        else
        {
            merge(Index);
            C[Index]->Deletion(data);
        }
        return;
    }

    T getPredecessor(int Index)
    {
        BNode* cur = C[Index];
        while (!cur->isLeaf)
            cur = cur->C[cur->degree];

        return cur->key[cur->degree - 1];
    }
    T getSuccessor(int Index)
    {
        BNode* cur = C[Index + 1];
        while (!cur->isLeaf)
            cur = cur->C[0];

        return cur->key[0];
    }

    void fill(int Index)
    {
        if (Index != 0 && C[Index - 1]->order >= degree)
            borrowFromPrev(Index);

        else if (Index != order && C[Index + 1]->order >= degree)
            borrowFromNext(Index);

        else
        {
            if (Index != order)
                merge(Index);
            else
                merge(Index - 1);
        }
        return;
    }

    // Borrow from previous
    void borrowFromPrev(int Index)
    {
        BNode<T>* child = C[Index];
        BNode<T>* sibling = C[Index - 1];

        for (int i = child->degree - 1; i >= 0; --i)
            child->key[i + 1] = child->key[i];

        if (!child->isLeaf)
        {
            for (int i = child->degree; i >= 0; --i)
                child->C[i + 1] = child->C[i];
        }

        child->key[0] = key[Index - 1];

        if (!child->isLeaf)
            child->C[0] = sibling->C[sibling->degree];

        key[Index - 1] = sibling->key[sibling->degree - 1];

        child->degree += 1;
        sibling->degree -= 1;

        return;
    }

    // Borrow from the next
    void borrowFromNext(int Index)
    {
        BNode* child = C[Index];
        BNode* sibling = C[Index + 1];

        child->key[(child->degree)] = key[Index];

        if (!(child->isLeaf))
            child->C[(child->degree) + 1] = sibling->C[0];

        key[Index] = sibling->key[0];

        for (int i = 1; i < sibling->degree; ++i)
            sibling->key[i - 1] = sibling->key[i];

        if (!sibling->isLeaf)
        {
            for (int i = 1; i <= sibling->degree; ++i)
                sibling->C[i - 1] = sibling->C[i];
        }

        child->degree += 1;
        sibling->degree -= 1;

        return;
    }

    // Merge
    void merge(int Index)
    {
        BNode* child = C[Index];
        BNode* sibling = C[Index + 1];

        child->key[degree - 1] = key[Index];

        for (int i = 0; i < sibling->degree; ++i)
            child->key[i + degree] = sibling->key[i];

        if (!child->isLeaf)
        {
            for (int i = 0; i <= sibling->order; ++i)
                child->C[i + degree] = sibling->C[i];
        }

        for (int i = Index + 1; i < order; ++i)
            key[i - 1] = key[i];

        for (int i = Index + 2; i <= order; ++i)
            C[i - 1] = C[i];

        child->order += sibling->order + 1;
        order--;

        delete (sibling);
        return;
    }
    void insertIfBNodeNotFull(T data, string filename_val)
    {
        int i = order - 1;

        if (isLeaf == true)
        {
            while (i >= 0 && key[i] > data)
            {
                key[i + 1] = key[i];
                i--;
            }

            key[i + 1] = data;
            // filename = filename_val;
            order = order + 1;
        }
        else
        {
            while (i >= 0 && key[i] > data)
                i--;

            if (C[i + 1]->order == 2 * degree - 1)
            {
                SplitChild(i + 1, C[i + 1]);

                if (key[i + 1] < data)
                    i++;
            }
            C[i + 1]->insertIfBNodeNotFull(data, filename_val);
        }
    }

    void SplitChild(int i, BNode<T>* y)
    {
        BNode<T>* z = new BNode<T>(y->degree, y->filename, y->isLeaf);
        z->order = degree - 1;

        for (int j = 0; j < degree - 1; j++)
            z->key[j] = y->key[j + degree];

        if (y->isLeaf == false)
        {
            for (int j = 0; j < degree; j++)
                z->C[j] = y->C[j + degree];
        }

        y->order = degree - 1;
        for (int j = order; j >= i + 1; j--)
            C[j + 1] = C[j];

        C[i + 1] = z;

        for (int j = order - 1; j >= i; j--)
            key[j + 1] = key[j];

        key[i] = y->key[degree - 1];
        order = order + 1;
    }

};


//-------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------//


template <class Q>
class BTree
{
    BNode<Q>* root;
    int t;

public:
    BTree(int temp)
    {
        t = temp;
        root = NULL;
    }
    void traverse()
    {
        if (root == NULL)
        {
            return;
        }
        root->Traverse();
    }
    BNode<Q>* search(Q data)
    {
        if (root != NULL)
        {
            return root->search(data);
        }
        else
        {
            return NULL;
        }
    }
    void insert(Q data, string filename_val)
    {
        if (root == NULL)
        {
            root = new BNode<Q>(t, filename_val, true);
            root->key[0] = data;
            root->order = 1;
        }
        else
        {

            if (root->order == 2 * t - 1)
            {
                BNode<Q>* s = new BNode<Q>(t, filename_val, false);

                s->C[0] = root;

                s->SplitChild(0, root);

                int i = 0;
                if (s->key[0] < data)
                    i++;
                s->C[i]->insertIfBNodeNotFull(data, filename_val);

                root = s;
            }
            else
                root->insertIfBNodeNotFull(data, filename_val);
        }
    }
    void deletion(Q data) {
        if (root == NULL) {
            cout << "Tree is empty.\n";
            return;
        }
        else {
            root->Deletion(data);
        }
    }
};

void CreateIndex(string index, int order, BTree<string> *t)
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
            // cout << file_name << endl;
            cout << "Cannot open file " << endl;
        }
        else
        {

            for (int i = 0; i < 6; i++)
            {
                getline(fin, garbage, ',');
                if (garbage == index)
                {
                    counter = i;
                    break;
                }
            }

            while (!fin.eof())
            {
                garbage = "";
                s = "";

                getline(fin, garbage, '\n');

                for (int i = 0; i < counter; i++)
                {
                    getline(fin, garbage, ',');
                }

                getline(fin, s, ',');
                cout << s << endl;
                t->insert(s, file_name);

                getline(fin, garbage, '\n');
                counter++;

                // break;
            }

            fin.close();
            break;
        }
    }
    //   t->traverse();
}

void IndexOnID(string index, int order, BTree<string> *t)
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

                t->insert(s, file_name);
                ofstream fw("./B_tree/ID/bt" + s + ".txt");
                getline(fin, garbage, '\n');
                fw << garbage << endl;
                fw.close();
            }
            fin.close();
        }
    }
    // t->traverse();
}

void IndexBTree(BTree<string> *t, int index)
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
                
                ofstream fw("./B_tree/Year/bt" + Year + ".txt", ios::app);
                fw << one << ",";
                getline(fin, one);
                fw << one << endl;
                fw.close();

                t->insert(Year,file_name);
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
                ofstream fw("./B_tree/113_Cause_Name/bt" + cause_name + ".txt", ios::app);
                fw << temp << endl;
                fw.close();

                t->insert(cause_name,file_name);
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
                
                ofstream fw("./B_tree/Cause_Name/bt" + cause_name + ".txt", ios::app);
                fw << temp << endl;
                fw.close();

                t->insert(cause_name,file_name);
                
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
                ofstream fw("./B_tree/State/bt" + cause_name + ".txt", ios::app);
                fw << temp << endl;
                fw.close();

                t->insert(cause_name,file_name);
                
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
                ofstream fw("./B_tree/Deaths/bt" + cause_name + ".txt", ios::app);
                fw << temp << endl;
                fw.close();

                t->insert(cause_name,file_name);
                
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
                ofstream fw("./B_tree/Death_Rate/bt" + cause_name + ".txt", ios::app);
                fw << temp << endl;
                fw.close();

                t->insert(cause_name,file_name);
               
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

void PointSearch_BTree(BTree<string> *t, string key, int index)
{
    if (t->search(key) == NULL)
    {
        cout << "Key not found\n";
        return;
    }

    else
    {

        string data = "";
        string filename;
        if(index == 1) {
            filename = "./B_tree/ID/bt" + key + ".txt";
        }
        if(index == 2) {
            filename = "./B_tree/Year/bt" + key + ".txt";
        }
        if(index == 3) {
            filename = "./B_tree/113_Cause_Name/bt" + key + ".txt";
        }
        if(index == 4) {
            filename = "./B_tree/Cause_Name/bt" + key + ".txt";
        }
        if(index == 5) {
            filename = "./B_tree/State/bt" + key + ".txt";
        }
        if(index == 6) {
            filename = "./B_tree/Deaths/bt" + key + ".txt";
        }
        if(index == 7) {
            filename = "./B_tree/Death_Rate/bt" + key + ".txt";
        }

        ifstream fin(filename);
        if (!fin)
        {
            cout << "ID with this key not found\n";
            return;
        }
        else{
            while(!fin.eof()){

                getline(fin, data, '\n');
                if(data!="") {
                    cout << "The data for " << key << " is: " << data << endl;
                }

            }
        }

        return;
    }
}

void DeleteRecord_BTree(string key, BTree<string> *t,int index)
{

    if (t->search(key) == NULL)
    {
        cout << "Key not found to be Deleted\n";
        return;
    }
    else
    {
        t->deletion(key);
        
        string filename;
        if(index == 1) {
            filename = "./B_tree/ID/bt" + key + ".txt";
        }
        if(index == 2) {
            filename = "./B_tree/Year/bt" + key + ".txt";
        }
        if(index == 3) {
            filename = "./B_tree/113_Cause_Name/bt" + key + ".txt";
        }
        if(index == 4) {
            filename = "./B_tree/Cause_Name/bt" + key + ".txt";
        }
        if(index == 5) {
            filename = "./B_tree/State/bt" + key + ".txt";
        }
        if(index == 6) {
            filename = "./B_tree/Deaths/bt" + key + ".txt";
        }
        if(index == 7) {
            filename = "./B_tree/Death_Rate/bt" + key + ".txt";
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

void RangeSearch_BTree(BTree<string> *t)
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

        if (t->search(to_string(i)) == NULL)
        {
            cout << i << " not found\n";
        }
        else
        {

            string filename = "";
            filename = "./B_tree/" + choice + "/bt" + to_string(i) + ".txt";
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


