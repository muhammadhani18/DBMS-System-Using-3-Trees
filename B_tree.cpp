#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

template <class T>
struct BNode
{
    T *key;
    int t;
    BNode<T> **C;
    int n;
    bool leaf;
    string filename;

    BNode<T>(int t1, string file, bool leaf1)
    {
        t = t1;
        leaf = leaf1;

        key = new T[2 * t - 1];
        C = new BNode *[2 * t];
        filename = file;
        n = 0;
    }
    void insertIfBNodeNotFull(T k, string file)
    {
        int i = n - 1;

        if (leaf == true)
        {
            while (i >= 0 && key[i] > k)
            {
                key[i + 1] = key[i];
                i--;
            }

            key[i + 1] = k;
            // filename = file;
            n = n + 1;
        }
        else
        {
            while (i >= 0 && key[i] > k)
                i--;

            if (C[i + 1]->n == 2 * t - 1)
            {
                SplitChild(i + 1, C[i + 1]);

                if (key[i + 1] < k)
                    i++;
            }
            C[i + 1]->insertIfBNodeNotFull(k, file);
        }
    }

    void SplitChild(int i, BNode<T> *y)
    {
        BNode<T> *z = new BNode<T>(y->t, y->filename, y->leaf);
        z->n = t - 1;

        for (int j = 0; j < t - 1; j++)
            z->key[j] = y->key[j + t];

        if (y->leaf == false)
        {
            for (int j = 0; j < t; j++)
                z->C[j] = y->C[j + t];
        }

        y->n = t - 1;
        for (int j = n; j >= i + 1; j--)
            C[j + 1] = C[j];

        C[i + 1] = z;

        for (int j = n - 1; j >= i; j--)
            key[j + 1] = key[j];

        key[i] = y->key[t - 1];
        n = n + 1;
    }

    void Traverse()
    {
        int i = 0;
        for (; i < n; i++)
        {
            if (leaf == false)
                C[i]->Traverse();

            cout << key[i] << "  ";
        }

        if (leaf == false)
            C[i]->Traverse();
    }

    BNode<T> *search(T k)
    {
        int i = 0;
        while (i < n && k > key[i])
        {
            i++;
        }

        if (key[i] == k)
            cout << "Key found\n";
        return C[i];

        if (leaf == true)
            return NULL;

        return C[i]->search(k);
    }

    int findKey(T k)
    {
        int idx = 0;
        while (idx < n && key[idx] < k)
        {
            ++idx;
        }
        return idx;
    }

    void Deletion(T k)
    {
        int idx = findKey(k);

        if (idx < n && key[idx] == k)
        {
            if (leaf)
                removeFromLeaf(idx);
            else
                removeFromNonLeaf(idx);
        }
        else
        {
            if (leaf)
            {
                cout << "ID DOES NOT EXIST TO BE DELETED\n";
                return;
            }

            bool flag; // = ((idx == n) ? true : false);
            if (idx == n)
            {
                flag = true;
            }
            else
            {
                flag = false;
            }
            if (C[idx]->n < t)
            {

                fill(idx);
            }

            if (flag && idx > n)
            {

                C[idx - 1]->Deletion(k);
            }
            else
            {

                C[idx]->Deletion(k);
            }
        }
        return;
    }
    void removeFromLeaf(int idx)
    {
        for (int i = idx + 1; i < n; ++i)
        {

            key[i - 1] = key[i];
        }

        n--;

        return;
    }
    void removeFromNonLeaf(int idx)
    {
        T k = key[idx];

        if (C[idx]->n >= t)
        {
            T pred = getPredecessor(idx);
            key[idx] = pred;
            C[idx]->Deletion(pred);
        }

        else if (C[idx + 1]->n >= t)
        {
            T succ = getSuccessor(idx);
            key[idx] = succ;
            C[idx + 1]->Deletion(succ);
        }

        else
        {
            merge(idx);
            C[idx]->Deletion(k);
        }
        return;
    }

    T getPredecessor(int idx)
    {
        BNode *cur = C[idx];
        while (!cur->leaf)
            cur = cur->C[cur->n];

        return cur->key[cur->n - 1];
    }
    T getSuccessor(int idx)
    {
        BNode *cur = C[idx + 1];
        while (!cur->leaf)
            cur = cur->C[0];

        return cur->key[0];
    }

    void fill(int idx)
    {
        if (idx != 0 && C[idx - 1]->n >= t)
            borrowFromPrev(idx);

        else if (idx != n && C[idx + 1]->n >= t)
            borrowFromNext(idx);

        else
        {
            if (idx != n)
                merge(idx);
            else
                merge(idx - 1);
        }
        return;
    }

    // Borrow from previous
    void borrowFromPrev(int idx)
    {
        BNode<T> *child = C[idx];
        BNode<T> *sibling = C[idx - 1];

        for (int i = child->n - 1; i >= 0; --i)
            child->key[i + 1] = child->key[i];

        if (!child->leaf)
        {
            for (int i = child->n; i >= 0; --i)
                child->C[i + 1] = child->C[i];
        }

        child->key[0] = key[idx - 1];

        if (!child->leaf)
            child->C[0] = sibling->C[sibling->n];

        key[idx - 1] = sibling->key[sibling->n - 1];

        child->n += 1;
        sibling->n -= 1;

        return;
    }

    // Borrow from the next
    void borrowFromNext(int idx)
    {
        BNode *child = C[idx];
        BNode *sibling = C[idx + 1];

        child->key[(child->n)] = key[idx];

        if (!(child->leaf))
            child->C[(child->n) + 1] = sibling->C[0];

        key[idx] = sibling->key[0];

        for (int i = 1; i < sibling->n; ++i)
            sibling->key[i - 1] = sibling->key[i];

        if (!sibling->leaf)
        {
            for (int i = 1; i <= sibling->n; ++i)
                sibling->C[i - 1] = sibling->C[i];
        }

        child->n += 1;
        sibling->n -= 1;

        return;
    }

    // Merge
    void merge(int idx)
    {
        BNode *child = C[idx];
        BNode *sibling = C[idx + 1];

        child->key[t - 1] = key[idx];

        for (int i = 0; i < sibling->n; ++i)
            child->key[i + t] = sibling->key[i];

        if (!child->leaf)
        {
            for (int i = 0; i <= sibling->n; ++i)
                child->C[i + t] = sibling->C[i];
        }

        for (int i = idx + 1; i < n; ++i)
            key[i - 1] = key[i];

        for (int i = idx + 2; i <= n; ++i)
            C[i - 1] = C[i];

        child->n += sibling->n + 1;
        n--;

        delete (sibling);
        return;
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
    BNode<Q> *root;
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
    BNode<Q> *search(Q k)
    {
        if (root != NULL)
        {
            return root->search(k);
        }
        else
        {
            return NULL;
        }
    }
    void insert(Q k, string file)
    {
        if (root == NULL)
        {
            root = new BNode<Q>(t, file, true);
            root->key[0] = k;
            root->n = 1;
        }
        else
        {

            if (root->n == 2 * t - 1)
            {
                BNode<Q> *s = new BNode<Q>(t, file, false);

                s->C[0] = root;

                s->SplitChild(0, root);

                int i = 0;
                if (s->key[0] < k)
                    i++;
                s->C[i]->insertIfBNodeNotFull(k, file);

                root = s;
            }
            else
                root->insertIfBNodeNotFull(k, file);
        }
    }
    void deletion(Q k)
    {
        if (root == NULL)
        {
            cout << "Tree is empty.\n";
            return;
        }
        else
        {
            root->Deletion(k);
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

void PointSearch_BTree(BTree<string> *t, string key)
{
    if (t->search(key) == NULL)
    {
        cout << "Key not found\n";
        return;
    }
    else
    {
        string data = "";
        string filename = "./B_tree/bt" + key + ".txt";
        ifstream fin(filename);
        if (!fin)
        {
            cout << "ID with this key not found\n";
            return;
        }

        getline(fin, data, '\n');
        cout << "The data for " << key << " is: " << data << endl;

        return;
    }
}

void DeleteRecord_BTree(string key, BTree<string> *t)
{

    if (t->search(key) == NULL)
    {
        cout << "Key not found to be Deleted\n";
        return;
    }
    else
    {
        cout << "Entered\n";
        t->deletion(key);
        string filename = "./B_tree/ID/bt" + key + ".txt";
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
