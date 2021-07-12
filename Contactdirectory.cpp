// 2019306 - Sem Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/* Note towards the checker:
1) The differentiating element between each node is the integer variable(data member) KEY. No two records can have the same KEY through out the program.
*/
#include <fstream>
#include <iostream>
#include<string>
using namespace std;
struct node {                                                                      // Node is the structure which saves each record with KEY as the record that differentiates between records
	int key;string primarycontact, secondarycontact, address;
	node* nextnode = NULL;
	char name[10];
};
int stringhashing(string const word) {                                           //This is the hashing function which converts string to array indexes
	int count = 0;
	for(; word[count]!= NULL;count++){}
	int c1 = 53, c2 = 1000000009;unsigned long int sum;
	for (int count2 = 0;count2 < count;count2++) {
		sum = word[count2] * unsigned long int(pow(c1, count2));
	}
	sum = sum % 19;
	return sum;
}
bool stringcomparison( char str1[], char str2[]) {                      //compares two strings to tell wether they are equal or not
	int min;
	if (sizeof(str1) > sizeof(str2))
		min = sizeof(str2);
	else
		min = sizeof(str1);
	bool check = true;
	for (int count = 0;count < min;count++) {
		if (str1[count] != str2[count]) {
			check = false;
			break;
		}
	}
	return check;
}
class hashtablelist {                                                 
	struct node *table[20];
public:
	bool checkkey(int key) {                                  //checks key and makes sure each record has a different key
		for (int count = 0;count < 20;count++) {
			if (table[count] == NULL)
				continue;
			else {
				node* currnode = table[count];
				while (currnode != NULL) {
					if (currnode->key == key) {
						cout << "Error while handling records i.e. two records have the same key. EACH RECORD MUST HAVE A DIFFERENT KEY ";
						return false;
					}
					currnode = currnode->nextnode;
				}
			}
		}
		return true;
	}
	hashtablelist() {                                              //constructor for hastable
		for (int count = 0;count < 20;count++) {                   //initialises the hashtable with each index as NULL
			table[count] = NULL;
		}
		ifstream f;
		f.open("file.txt", ios::in);
		int key = -1, input;
		f >> input;
		while (input != key) {                                     //reads from files and intialises hashtable accordingly 
			struct node* currnode = new struct node;
			if (checkkey(input)) {
				f >> currnode->name; f >> currnode->primarycontact;f >> currnode->secondarycontact;f >> currnode->address;
				int indexarr = stringhashing(currnode->name);
				if (table[indexarr] == NULL) {
					table[indexarr] = currnode;
				}
				else {
					node* ptr = table[indexarr];
					int count = 2;
					for (;ptr->nextnode != NULL;count++)
						ptr = ptr->nextnode;
					ptr->nextnode = currnode;
				}
				currnode->key = input;
				key = input;
				f >> input;
			}
			else {
				cout << "Error occured while reading from file...  Please check the existing records  " << endl;
				return;
			}
		}
			f.close();
	}
	void insert() {                                                  //function to insert new records
		struct node* currnode = new node;
		cout << "Enter the unique key of record ";
		cin >> currnode->key;
		if (!(checkkey(currnode->key))) {                          //makes sure same key is not repeated
			cout << "Error caused while adding new record "<<endl;
		}
		else {
			cout << "Enter name of new record ";
			cin >> currnode->name;
			currnode->name[9] = NULL;
			cout << "Enter Primary Contact No.";
			cin >> currnode->primarycontact;
			cout << "Enter Secondary Contact No. ";
			cin >> currnode->secondarycontact;
			cout << "Enter Address ";
			cin >> currnode->address;
			int arrindex = stringhashing(currnode->name);
			if (table[arrindex] == NULL)
				table[arrindex] = currnode;
			else
			{
				node* ptr = table[arrindex];
				while (ptr->nextnode != NULL) {
					ptr = ptr->nextnode;
				}
				ptr->nextnode = currnode;
			}
		}
	}
	~hashtablelist() {                                        //destructor to delete all the nodes linked to the hashtable
		for (int count = 0;count < 20;count++) {
			node* prevnode = table[count];            
			while (prevnode != NULL) {
				table[count]= prevnode->nextnode;
				delete prevnode;
				prevnode = table[count];
			}
		}
	}
	void displayelement() {                                 //takes the name of the record as an input and displays all records with that name
		cout << "Input name of contact you seek details of ";
		char name[10];
		cin >> name;
		int index = stringhashing(name);
		if (table[index] != NULL) {
			node* ptr = table[index]; bool flag = false;
			for (int count = 0; ptr != NULL;count++) {
				if (stringcomparison((table[index]->name), name)) {
					cout << ptr->key << "\t" << ptr->name << "\t" << ptr->primarycontact << "\t" << ptr->secondarycontact << "\t" << ptr->address << endl ;
					flag = true;
				}
				ptr = ptr->nextnode;
			}
			if (!flag)
			{
				cout << "Your given name is not present in records. Please try again " << endl;
				return;
			}
		}
		else {
			cout << "Your given name is not present in records. Please try again "<<endl;
			return;
		}
	}
	void deleterecord() {                                           //deletes record ... first take name as an input and then takes key to make sure correct record is deleted only
		char name[10];int index; bool flag = false;
		cout << "Enter name of contact you wish to delete" << endl;
		cin >> name;
		index = stringhashing(name);
		if (table[index] != NULL){
			node* ptr = table[index];
			for (int count = 0;ptr != NULL; count++) {                //checks if there are any records matching to the user's inputted name if yess then display all their details
				if (stringcomparison(table[index]->name, name)){
					cout << ptr->key << " " << ptr->name << "\t" << ptr->primarycontact << "\t" << ptr->secondarycontact << " " << ptr->address << endl;
					flag = true;
				}
				ptr = ptr->nextnode;
			}
		}
		else {
			cout << "We are sorry!! Your entered contact was not found in our records. Please try again "<<endl;
			deleterecord();
		}
		if (!flag) {                                          //flag tells whether any contacts with that name exists or not
			cout << "We are sorry!! Your entered contact was not found in our records.Please try again " << endl;
			deleterecord();
		}
		else {
			int key;
			cout << "Please enter the unique key for the contact you wish to delete ";           //input the key to make sure the correct record is deleted
			cin >> key;
			node* currnode = table[index]; node* prevnode = NULL;
			for (int count = 0;currnode != NULL; count++) {
				if (currnode->key == key) {
					if (prevnode == NULL)
						table[index] = currnode->nextnode;
					else
						prevnode->nextnode = currnode->nextnode;
					delete currnode;
					break;
				}
				else {
					prevnode = currnode;
					currnode = currnode->nextnode;
				}
			}
		}
	}
	void savetofile() {                         //function which saves all the data that has been manipulated through the program to the file
		ofstream f;
		f.open("file.txt", ios::out);
		for (int count = 0;count < 20;count++) {
			if (table[count] == NULL)
				continue;
			else {
				node* currnode = table[count];
				do {
					f << currnode->key << "\t" << currnode->name <<"\t" << currnode->primarycontact<<"\t"<<currnode->secondarycontact<<"\t"<<currnode->address<<endl;
					currnode = currnode->nextnode;
				} while (currnode != NULL);
			}
		}
	}

	};
int main()
{
	hashtablelist table1;
	int choice; bool input = true;
	enum STR2INT_ERROR { SUCCESS, OW, UW, INCONVERTIBLE };
	cout << "Data from records read " << endl;
	while (input) {                                                                            // The menu we wish to use in the project
		cout << "Press \t 1 for adding new contact \t 2 for deleting record \t 3 for displaying specific records \t 4 to exit ";
		cin >> choice;
		switch (choice) {
		case 1: table1.insert();
			break;
		case 2: table1.deleterecord();
			break;
		case 3: table1.displayelement();
			break;
		case 4:
			cout << "Do you wish to save the changes to files ? Y for YES N for NO " << endl;
			char i;
			cin >> i;
			if (i == 'Y')
			{
				table1.savetofile();
				cout << "Saving and Closing...... Please wait!!";
				input = false;
			}
			else if (i == 'N') {
				input = false;
				cout << "Closing without Saving....... Please wait!!";
			}
			else {
				cout << "Invalid input. Can not close program " << endl;
				break;
			}
			break;
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
