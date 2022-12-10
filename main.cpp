#include <iostream>
#include "B_tree.cpp"
#include "Red_Black.cpp"

using namespace std;

void Menu() {
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
            if (choice == 1)
            {
                cout << "Please enter the Order of B-tree: ";
                cin >> order;
                cout << "Please enter on which data field you want to perform indexing\n";
                cout << "(ID - Year - 113 Cause Name - Cause Name - State - Deaths - Age-adjusted Death Rate)\n";
                cout << "Index: ";
                cin >> index;

                BTree<string> *tree = new BTree<string>(order);

                IndexOnID(index,order,tree);
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
                        PointSearch_BTree(tree,key);
                    } 
                    cout << endl;
                }
            }
        }
        else if(choice == 3) {
            string index;
            if (choice == 3)
            {
                cout << "Please enter on which data field you want to perform indexing\n";
                cout << "(ID - Year - 113 Cause Name - Cause Name - State - Deaths - Age-adjusted Death Rate)\n";
                cout << "Index: ";
                cin >> index;


                RedBlackTree<string> *RB_tree = new RedBlackTree<string>;
                IndexOnIDRB(index,RB_tree);
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
                        //PointSearch_BTree(tree,key);
                    } 
                    cout << endl;
                }
            }

        }
    return 0;
}

// int main() {
//     BTree<string> t(3);
//     t.insert("13","f");
//     t.insert("8","f");
//     t.insert("5","f");
//     t.insert("6","f");
//     t.insert("11","f");
//     t.insert("3","f");
//     t.insert("7","f");
//     t.insert("27","f");

//     t.traverse();
//     return 0;
// }