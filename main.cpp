#include <iostream>
#include "B_tree.cpp"
#include "Red_Black.cpp"
#include  "AVL_Tree.cpp"

using namespace std;

void Menu() {
    cout << endl;
    cout << "############################################################\n";
    cout << "#    Welcome to DBMS System made by RunTime Terror         #\n";
    cout << "#               Press 0 to Exit                            #\n";
    cout << "#               Press 2 to do Point Search                 #\n";
    cout << "#               Press 3 to do Range Search                 #\n";
    cout << "#               Press 4 to Update key field                #\n";
    cout << "#               Press 5 to Delete a Record                 #\n";
    cout << "############################################################\n";
    cout << "Choice: ";
}

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
            int index_1;
            if (choice == 1)
            {
                cout << "Please enter the Order of B-tree: ";
                cin >> order;

                cout << "Press 1 to do the Indexing on ID!\n\n";
                cout << "Press 2 to do the Indexing on Year!\n\n";
                cout << "Press 3 to do the Indexing on 113 Cause Name!\n\n";
                cout << "Press 4 to do the Indexing on Cause Name!\n\n";
                cout << "Press 5 to do the Indexing on State!\n\n";
                cout << "Press 6 to do the Indexing on Deaths!\n\n";
                cout << "Press 7 to do the Indexing on Age-adjusted Death Rate!\n\n";
                cout << "Press 8 to Exit!\n\n";
                cout << "Select: ";

                cin >> index_1;

                BTree<string> *tree = new BTree<string>(order);

                if(index_1==1) {
                    IndexOnID(index,order,tree);
                }
                else {
                    IndexBTree(tree,index_1);
                }
                while (1)
                {
                    Menu();
                    cin >> choice;
                    if (choice == 0){ 
                        exit(0);
                    }
                    if (choice == 2) {
                        string key;
                        cout << "Please enter the "  << index << " : ";
                        cin >> key;
                        PointSearch_BTree(tree,key,index_1);
                    } 
                    if (choice == 3) {
                        RangeSearch_BTree(tree);
                    } 
                    if(choice == 5) {
                        string key;
                        cout << "Please enter the key you wana delete: ";
                        cin >> key;
                        DeleteRecord_BTree(key,tree,index_1); 
                    }
                    
                    cout << endl;
                }
            }
        }
        else if(choice == 2) {
            string index;
            int index_1;
            if (choice == 2)
            {
                cout << "Press 1 to do the Indexing on ID!\n\n";
                cout << "Press 2 to do the Indexing on Year!\n\n";
                cout << "Press 3 to do the Indexing on 113 Cause Name!\n\n";
                cout << "Press 4 to do the Indexing on Cause Name!\n\n";
                cout << "Press 5 to do the Indexing on State!\n\n";
                cout << "Press 6 to do the Indexing on Deaths!\n\n";
                cout << "Press 7 to do the Indexing on Age-adjusted Death Rate!\n\n";
                cout << "Press 8 to Exit!\n\n";
                cout << "Select: ";

                cin >> index_1;

                AVLTree<string> *avl_tree = new AVLTree<string>;
                if(index_1==1) {

                    IndexOnIDAVL(index,avl_tree);
                }
                else {
                    IndexAVL(avl_tree,index_1);
                }
                
                
                while(1) {
                    Menu();
                    cin >> choice;
                    if (choice == 0){ 
                            exit(0);
                    }
                    if (choice == 2) {
                        string key;
                        cout << "Please enter the "  << index << " : ";
                        cin >> key;
                        PointSearch_AVLTree(avl_tree,key,index_1);
                    }
                    if (choice == 3) {
                        RangeSearch_AVLTree(avl_tree);
                    } 
                    if(choice == 5) {
                        string key;
                        cout << "Please enter the key you wana delete: ";
                        cin >> key;
                        DeleteRecord_AVLTree(key,avl_tree,index_1); 
                    } 
                     
                    cout << endl;
                }
            }

        }
        else if(choice == 3) {
            string index;
            int index_1;
            if (choice == 3)
            {
                cout << "Press 1 to do the Indexing on ID!\n\n";
                cout << "Press 2 to do the Indexing on Year!\n\n";
                cout << "Press 3 to do the Indexing on 113 Cause Name!\n\n";
                cout << "Press 4 to do the Indexing on Cause Name!\n\n";
                cout << "Press 5 to do the Indexing on State!\n\n";
                cout << "Press 6 to do the Indexing on Deaths!\n\n";
                cout << "Press 7 to do the Indexing on Age-adjusted Death Rate!\n\n";
                cout << "Press 8 to Exit!\n\n";
                cout << "Select: ";

                cin >> index_1;
                RedBlackTree<string> *RB_tree = new RedBlackTree<string>;
                if(index_1==1) {
                    IndexOnIDRB(index,RB_tree);
                }
                else {
                    IndexRBTree(RB_tree,index_1);
                }

                while(1) {
                    Menu();
                    cin >> choice;
                    if (choice == 0){ 
                            exit(0);
                    }
                    if (choice == 2) {
                        string key;
                        cout << "Please enter the "  << index << " : ";
                        cin >> key;
                        PointSearch_RBTree(RB_tree,key,index_1);
                    } 
                    if (choice == 3) {
                        RangeSearch_RBTree(RB_tree);
                    } 
                    if(choice == 5) {
                        string key;
                        cout << "Please enter the key you wana delete: ";
                        cin >> key;
                        DeleteRecord_RBTree(key,RB_tree,index_1); 
                    } 
                    cout << endl;
                }
            }

        }
    return 0;
}

