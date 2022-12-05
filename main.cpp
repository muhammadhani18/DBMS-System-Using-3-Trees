#include <iostream>
#include "B_tree.cpp"
using namespace std;


int main()
{
        int choice;

    
        cout << "Tell us on which tree to perform indexing\n";
        cout << "1 for B tree\n";
        cout << "2 for AVL tree\n";
        cout << "3 for Red-Black tree\n";

        cout << "\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
            int order;
            string index;
            if (choice == 1)
            {
                cout << "Please enter the Order of B-tree: ";
                cin >> order;
                cout << "Please enter on which data field you want to perform indexing\n";
                cout << "(ID - Year - 113 Cause Name - Cause Name - State - Deaths - Age-adjusted Death Rate)\n";
                cout << "Index: ";
                cin >> index;

                BTree<string> *tree = new BTree<string>(order);

                CreateIndex(index, order, tree);

                while (1)
                {
                    cout << endl;
                    cout << "############################################################\n";
                    cout << "#    Welcome to DBMS System made by Ali Anas and Hani      #\n";
                    cout << "#               Press 0 to Exit                            #\n";
                    cout << "#               Press 2 to do Point Search                 #\n";
                    cout << "#               Press 3 to do Range Search                 #\n";
                    cout << "#               Press 4 to Update key field                #\n";
                    cout << "#               Press 5 to Delete a Record                 #\n";
                    cout << "############################################################\n";
                    cout << "Choice: ";
                    cin >> choice;
                    if (choice == 0){ 
                        exit(0);
                    }
                    if (choice == 2) {
                        string key;
                        cout << "Please enter the "  << index << " : ";
                        cin >> key;
                        PointSearch_BTree(tree,key);
                    } 
                    cout << endl;
                }
            }
        }
    

    return 0;
}