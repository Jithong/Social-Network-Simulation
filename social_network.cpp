#include<iostream>
#include<string>
#include<cstring>
#include<iomanip>
#include<fstream>

#include "network.h"
#include "user.h"

using namespace std;

int main(int argc, char *argv[])
{
	Network network;
	network.read_friends(argv[1]);
	// menu below
	cout << "===========================================================================================" << endl;
	cout << "To add a user: 1 FirstName LastName Year Zip" << endl;
	cout << "To add a friend connection: 2 FirstName LastName FirstName LastName" << endl;
	cout << "To remove a friend connection: 3 FirstName LastName FirstName LastName" << endl;
	cout << "To print out a list of users with their associated data: 4" << endl;
	cout << "To print out a list of a user's friends with their associated data: 5 FirstName LastName" << endl;
	cout << "To make a text file out of current users and their data: 6 filename" << endl;
	cout << "To find the distance between two users: 7 FirstName LastName FirstName LastName" << endl;
	cout << "To print out a list of disjoint groups and their users: 8" << endl;
	cout << "To print out a friend suggestion: 9 FirstName LastName" << endl;
	cout << "To exit: 0 or an integer not between 1 and 9" << endl;
	cout << "===========================================================================================" << endl;

	int f; // first cin; function call number
	string fname;
	string lname;
	string fname2;
	string lname2;
	int y; // cin year
	int z; // cin zip

	while (true || -1) {
	cin >> f;
		if (f == 1) { // add user
			cin >> fname >> lname >> y >> z;
			fname += " ";
			fname += lname; // combines first and last name
			int idSize = network.get_user_size();
			
			network.add_user(idSize, fname, y, z);
		}

		else if (f == 2) { // add connection
			cin >> fname >> lname >> fname2 >> lname2;
			fname += " ";
			fname += lname;
			fname2 += " ";
			fname2 += lname2;

			int id = network.get_id(fname);
			int id2 = network.get_id(fname2);
			int e = network.add_connection(id, id2);
			if (e == -1) {
				cout << "The user(s) does not exist, or the users are already friends." << endl;
			}
		}

		else if (f == 3) { // remove connection
			cin >> fname >> lname >> fname2 >> lname2;
			fname += " ";
			fname += lname;
			fname2 += " ";
			fname2 += lname2;

			int id = network.get_id(fname);
			int id2 = network.get_id(fname2);

			int e = network.remove_connection(id, id2);
			if (e == -1) {
				cout << "The user(s) does not exist." << endl;
			}
		}

		else if (f == 4) { // print user info
			network.print_user_info();
		}

		else if (f == 5) { // print all info
			cin >> fname >> lname;
			fname += " ";
			fname += lname;

			int e = network.print_friends_info(fname);
			if (e == -1) { // if returns 1, it's an error
					cout << "The user does not exist." << endl;
			}
		}

		else if (f == 6) { // output file
			char* output;
			char temp[35];
			cin >> temp;
			int len = strlen(temp);
			output = new char[len+1];
			strcpy(output, temp);

			int e = network.write_friends(output);
			if (e == -1) {
				cout << "Failed writing an output file." << endl;
			}
			delete [] output;
		}

		else if (f == 7) { // distance cout
			cin >> fname >> lname >> fname2 >> lname2;
			fname += " ";
			fname += lname;
			fname2 += " ";
			fname2 += lname2;

			int id = network.get_id(fname);
			int id2 = network.get_id(fname2);
			if (id == -1 || id2 == -1) {
				cout << "The user(s) does not exist, or the two users are not connected." << endl;
			}
			else {
				int e = network.print_distance(id, id2);
				if (e == -1) {
					cout << "The user(s) does not exist, or the two users are not connected." << endl;
				}
			}

		}

		else if (f == 8) { // disjoint groups
			network.print_groups();
		}

		else if (f == 9) { // friend suggestion
			cin >> fname >> lname;
			fname += " ";
			fname += lname;
			int id = network.get_id(fname);
			if (id == -1) {
				cout << "The user does not exist." << endl;
			}
			else {
				int e = network.friend_suggestion(id);
				if (e == -1) {
					cout << "The user does not exist." << endl;
				}
			}
		}

		else {
			break;
		}
	}
return 0;
}






