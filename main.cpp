#include <iostream>
#include "B_tree.cpp"
using namespace std;

void CreateIndex(int choice)
{
    if (choice == 1)
    {
        int order;
        string index;
        if (choice == 1) {
            cout << "Please enter the Order of B-tree: ";
            cin >> order;
            cout << "Please enter on which data field you want to perform indexing\n";
            cout << "(ID - Year - 113 Cause Name - Cause Name - State - Deaths - Age-adjusted Death Rate)\n";
            cout << "Index: ";
            cin >> index;
        }
        
        BTree<string> t(order);
        ifstream fin;

        string s, garbage;
        string file_name;
        
        int counter = 0;
        


        for (int i = 1; i <= 10; i++)
        {
            file_name = "";
            file_name = "NCHS_-_Leading_Causes_of_Death__United_States_";
            file_name.append(to_string(i));
            file_name.append(".csv");
            
            fin.open(file_name, ios::out | ios::in);
            if (!fin)
            {
                //cout << file_name << endl;
                cout << "Cannot open file " << i << endl;
            }
            else
            {
                
                for(int i=0;i<6;i++) {
                    getline(fin, garbage, ',');
                    if(garbage == index) {
                        counter = i;
                        break; 
                    }
                    
                }
                while (!fin.eof())
                {
                    getline(fin,garbage,'\n');
                    
                    for(int i=0; i < counter;i++){
                        getline(fin, garbage, ',');
                        //cout << garbage << endl;
                    }
                    getline(fin, s, ',');
                    
                    
                    t.insert(s,file_name);
                    
                    getline(fin, garbage, '\n');
                    
                    //break;
                    
                }
 
                fin.close();
                
            }
        }

        // cout << "The B-tree is: ";
        t.traverse();
    }
}

int main()
{
    int choice;

    cout << "############################################################\n";
    cout << "#    Welcome to DBMS System made by Ali Anas and Hani      #\n";
    cout << "#               Press 1 to Create Index                    #\n";
    cout << "#               Press 2 to do Point Search                 #\n";
    cout << "#               Press 3 to do Range Search                 #\n";
    cout << "#               Press 4 to Update key field                #\n";
    cout << "#               Press 5 to Delete a Record                 #\n";
    cout << "############################################################\n";

    cout << "\nChoice: ";
    cin >> choice; 


    if(choice == 1) {
        CreateIndex(choice);
    }


    return 0;
}