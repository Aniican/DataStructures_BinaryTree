// Author: Lane Murray
// Date: 10/27/2021
#include <iostream>
#include <fstream>
#include <string>
#include "binarySearchTree.h"
#include "customer.h"

using namespace std;

int main()
{
	int choice, id = 0, idTop = 0; // idTop will always be the highest id.
	string name, address, addressPt2, phone;
	bSearchTreeType<customer> customerBinaryTree;

	ifstream myfile("customers.txt");
	if (myfile.is_open()) // Reads the txt file.
	{
		while (!myfile.eof())
		{
			myfile >> id;
			myfile.get();
			getline(myfile, name);
			getline(myfile, address);
			getline(myfile, phone);

			customerBinaryTree.insert(customer(name, id, address, phone)); // Creates a new customer inside the binary tree.

			if (idTop < id)
				idTop = id;
		}
		myfile.close(); // Closes the txt file.
	}

	do {
		cout << "Please choose from the following list.\n 1. Add Customer\n 2. Find Customer\n 3. Display Customers\n 4. Exit Program" << endl;
		cin >> choice;

		while (!cin || choice > 4 || choice < 1)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Error... Invalid Input!" << endl;
			cout << "Please choose from the following list.\n 1. Add Customer\n 2. Find Customer\n 3. Display Customers\n 4. Exit Program" << endl;
			cin >> choice;
		}

		if (choice == 1) // Add Customer
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please your customers Name." << endl;
			getline(cin, name);
			cout << "Please your customers Phone Number." << endl;
			getline(cin, phone);
			cout << "Please your customers Address." << endl;
			getline(cin, address);

			idTop++; // If the highest current id is 25, then idTop will now be 26. This will ensure that any new customer added will always have a new sequential ID.

			customerBinaryTree.insert(customer(name, idTop, address, phone)); // Adds a new customer. They will always be added with an ID higher than previously provided.
		}
		else if (choice == 2) // Find Customer
		{
			cout << "Please enter the ID of your customer." << endl;
			cin >> id;
			while (!cin)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Error... Invalid Input!" << endl;
				cout << "Please enter the ID of your customer." << endl;
				cin >> id;
			}

			if (customerBinaryTree.search(customer("John Doe", id, "1801 Jeff Anderson Street Frankfort, IN, 46041", "724-121-2424"))) // Searches for a customer with the given ID.
				cout << "Customer found with id #" << id << endl; // If customer is found.
			else
				cout << "Customer not found with id #" << id << endl; // If customer isn't found.

		}
		else if (choice == 3) // Display Customers
		{
			customerBinaryTree.inorderTraversal(); // Displays all the customers
		}

	} while (choice != 4); // Exit Program

	customerBinaryTree.destroyTree();
	
	return 0;
}