#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

template <class T>
struct Node
{
    T *key;
    int t;
    Node<T> **C;
    int n;
    bool leaf;
    string filename;

    Node<T>(int t1, string file, bool leaf1)
    {
        t = t1;
        leaf = leaf1;

        key = new T[2 * t - 1];
        C = new Node *[2 * t];
        filename = file;
        n = 0;
    }
    void insertIfNodeNotFull(T k, string file)
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
            C[i + 1]->insertIfNodeNotFull(k, file);
        }
    }

    void SplitChild(int i, Node<T> *y)
    {
        Node<T> *z = new Node<T>(y->t, y->filename, y->leaf);
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

            cout << key[i] << "   ";
        }

        if (leaf == false)
            C[i]->Traverse();
    }

    Node<T> *search(T k)
    {
        int i = 0;
        while (i < n && k > key[i])
        {
            i++;
        }

        if (key[i] == k)
            return this;

        if (leaf == true)
            return NULL;

        return C[i]->search(k);
    }
};

template <class Q>
class BTree
{
    Node<Q> *root;
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
    Node<Q> *search(Q k)
    {
        if (root != NULL)
        {
            root->search(k);
        }
    }
    void insert(Q k, string file)
    {
        if (root == NULL)
        {
            root = new Node<Q>(t, file, true);
            root->key[0] = k;
            root->n = 1;
         
            ofstream fout("./B_tree/root.dat", ios::out | ios::binary);
            if (!fout)
            {
                cout << "Cannot open Bin file\n";
                exit(1);
            }
            for (int i = 0; i < 6; i++){

                fout.write((char *)&root[i], sizeof(root));
            }
            fout.close();
            if (!fout.good())
            {
                cout << "Error occurred at writing time!" << endl;
                return;
            }
        }
        else
        {
            
            if (root->n == 2 * t - 1)
            {
                Node<Q> *s = new Node<Q>(t, file, false);

                s->C[0] = root;

                s->SplitChild(0, root);

                int i = 0;
                if (s->key[0] < k)
                    i++;
                s->C[i]->insertIfNodeNotFull(k, file);

                root = s;
            }
            else
                root->insertIfNodeNotFull(k, file);
        }
    }
};
