#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
	fstream fin;

	int option;
	int count = 0;
	string one;


	while (true) {
		system("CLS");

		cout << "Press 1 to do the Indexing on ID!\n\n";
		cout << "Press 2 to do the Indexing on Year!\n\n";
		cout << "Press 3 to do the Indexing on 113 Cause Name!\n\n";
		cout << "Press 4 to do the Indexing on Cause Name!\n\n";
		cout << "Press 5 to do the Indexing on State!\n\n";
		cout << "Press 6 to do the Indexing on Deaths!\n\n";
		cout << "Press 7 to do the Indexing on Age-adjusted Death Rate!\n\n";
		cout << "Press 8 to Exit!\n\n";
		cout << "Select: ";

		cin >> option;

		switch (option) {
		case 1: {
			system("CLS");
			for (int i = 1; i <= 10; i++) {
				string file_name = "NCHS_-Leading_Causes_of_DeathUnited_States";
				file_name.append(to_string(i));
				file_name.append(".csv");

				fin.open(file_name);
				getline(fin, one, '\n');

				string ID;

				while (!fin.eof()) {
					getline(fin, ID, ',');
					getline(fin, one);
					cout << ID << endl;
				}
				fin.close();
			}
			system("Pause");
			break;
		}
		case 2: {
			system("CLS");

			for (int i = 1; i <= 10; i++) {
				string file_name = "NCHS_-Leading_Causes_of_DeathUnited_States";
				file_name.append(to_string(i));
				file_name.append(".csv");

				fin.open(file_name);
				getline(fin, one, '\n');

				count = 1;
				string Year;

				while (!fin.eof()) {
					for (int i = 0; i < count; i++)
						getline(fin, one, ',');

					getline(fin, Year, ',');
					getline(fin, one);
					cout << Year << endl;
				}
				fin.close();
			}
			system("Pause");
			break;
		}
		case 3: {
			system("CLS");
			for (int i = 1; i <= 1; i++) {
				string file_name = "NCHS_-Leading_Causes_of_DeathUnited_States";
				file_name.append(to_string(i));
				file_name.append(".csv");

				fin.open(file_name);
				getline(fin, one, '\n');

				count = 2;
				string cause_name;

				while (!fin.eof()) {
					for (int i = 0; i < count; i++)
						getline(fin, one, ',');

					// Last line
					if (one == "")
						break;

					getline(fin, cause_name, ',');

					string extra = "";
					bool yes = false;
					getline(fin, one, '\n');
					one += "\n";
					int j = 0;
					while (one[j] != '\n') {
						if (one[j] == '"') {
							yes = true;
							break;
						}
						extra += one[j];
						j++;
					}

					if (yes) {
						cause_name += extra;
						cause_name += '"';
					}
					cout << cause_name << endl;
				}
				fin.close();
			}
			system("Pause");
			break;
		}
		case 4: {
			system("CLS");
			for (int i = 1; i <= 10; i++) {
				string file_name = "NCHS_-Leading_Causes_of_DeathUnited_States";
				file_name.append(to_string(i));
				file_name.append(".csv");

				fin.open(file_name);
				getline(fin, one, '\n');
				int m = 0;
				count = 2;
				string cause_name;

				while (!fin.eof()) {
					for (int i = 0; i < count; i++) {
						getline(fin, one, ',');
					}
					if (one == "")
						break;

					getline(fin, cause_name, ',');

					string extra = "";
					bool yes = false;
					getline(fin, one, '\n');
					one += "\n";
					int j = 0;
					while (one[j] != '\n') {
						if (one[j] == '"') {
							yes = true;
							break;
						}
						extra += one[j];
						j++;
					}

					if (yes) {
						cause_name += extra;
						cause_name += '"';
					}

					cause_name = "";
					int k = 0;
					if (yes)
						k = j + 2;

					while(one[k] != ',') {
						cause_name += one[k];
						k++;
					}
					m++;
					cout << cause_name << endl;
				}
				cout << endl << endl << m;
				system("Pause");
				fin.close();
			}
			system("Pause");
			break;
		}
		case 5: {
			system("CLS");
			for (int i = 1; i <= 10; i++) {
				string file_name = "NCHS_-Leading_Causes_of_DeathUnited_States";
				file_name.append(to_string(i));
				file_name.append(".csv");

				fin.open(file_name);
				getline(fin, one, '\n');
				count = 2;
				string cause_name;

				while (!fin.eof()) {
					for (int i = 0; i < count; i++) {
						getline(fin, one, ',');
					}
					if (one == "")
						break;

					getline(fin, cause_name, ',');

					string extra = "";
					bool yes = false;
					getline(fin, one, '\n');
					one += "\n";
					int j = 0;
					while (one[j] != '\n') {
						if (one[j] == '"') {
							yes = true;
							break;
						}
						extra += one[j];
						j++;
					}

					if (yes) {
						cause_name += extra;
						cause_name += '"';
					}

					cause_name = "";
					int k = 0;
					if (yes)
						k = j + 2;

					while (one[k] != ',') {
						cause_name += one[k];
						k++;
					}
					k++;
					cause_name = "";
					while (one[k] != ',') {
						cause_name += one[k];
						k++;
					}
					cout << cause_name << endl;
				}
				fin.close();
			}
			system("Pause");
			break;
		}
		case 6: {
			system("CLS");
			for (int i = 1; i <= 10; i++) {
				string file_name = "NCHS_-Leading_Causes_of_DeathUnited_States";
				file_name.append(to_string(i));
				file_name.append(".csv");

				fin.open(file_name);
				getline(fin, one, '\n');
				count = 2;
				string cause_name;

				while (!fin.eof()) {
					for (int i = 0; i < count; i++) {
						getline(fin, one, ',');
					}
					if (one == "")
						break;

					getline(fin, cause_name, ',');

					string extra = "";
					bool yes = false;
					getline(fin, one, '\n');
					one += "\n";
					int j = 0;
					while (one[j] != '\n') {
						if (one[j] == '"') {
							yes = true;
							break;
						}
						extra += one[j];
						j++;
					}

					if (yes) {
						cause_name += extra;
						cause_name += '"';
					}

					cause_name = "";
					int k = 0;
					if (yes)
						k = j + 2;

					while (one[k] != ',') {
						cause_name += one[k];
						k++;
					}
					k++;
					cause_name = "";
					while (one[k] != ',') {
						cause_name += one[k];
						k++;
					}
					k++;
					cause_name = "";
					while (one[k] != ',') {
						cause_name += one[k];
						k++;
					}
					cout << cause_name << endl;
				}
				fin.close();
			}
			system("Pause");
			break;
		}
		case 7: {
			system("CLS");
			for (int i = 1; i <= 10; i++) {
				string file_name = "NCHS_-Leading_Causes_of_DeathUnited_States";
				file_name.append(to_string(i));
				file_name.append(".csv");

				fin.open(file_name);
				getline(fin, one, '\n');
				count = 2;
				string cause_name;

				while (!fin.eof()) {
					for (int i = 0; i < count; i++) {
						getline(fin, one, ',');
					}
					if (one == "")
						break;

					getline(fin, cause_name, ',');

					string extra = "";
					bool yes = false;
					getline(fin, one, '\n');
					one += "\n";
					int j = 0;
					while (one[j] != '\n') {
						if (one[j] == '"') {
							yes = true;
							break;
						}
						extra += one[j];
						j++;
					}

					if (yes) {
						cause_name += extra;
						cause_name += '"';
					}

					cause_name = "";
					int k = 0;
					if (yes)
						k = j + 2;

					while (one[k] != ',') {
						cause_name += one[k];
						k++;
					}
					k++;
					cause_name = "";
					while (one[k] != ',') {
						cause_name += one[k];
						k++;
					}
					k++;
					cause_name = "";
					while (one[k] != ',') {
						cause_name += one[k];
						k++;
					}
					k++;
					cause_name = "";
					while (one[k] != '\n') {
						cause_name += one[k];
						k++;
					}
					cout << cause_name << endl;
				}
				fin.close();
			}
			system("Pause");
			break;
		}
		case 8: {
			exit(1);
		}
		}
	}


	return 0;
}