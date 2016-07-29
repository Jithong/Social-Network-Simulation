#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<sstream>
#include"network.h"
#include"user.h"
#include<vector>
#include<deque>
using namespace std;


Network::Network() // no private variable used besides a vector; no constructor required
{
	
}

Network::~Network() // no dynamic memory allocated; no destructor required
{

}

int Network::get_user_size()
{
	return user.size();
}
void Network::add_user(int id, string name, int year, int zip) // function 1 adduser *no friends required
{
	User temp(id, name, year, zip);
	user.push_back(temp);
}

int Network::add_user(int id, string name, int year, int zip, string friends) // ifile adduser includes friends
{
	User temp(id, name, year, zip);
	stringstream ss(friends);
	int f;
	ss >> f;
	while ( ! ss.fail() ) {
		temp.add_friend(f);
		ss >> f;
	}
	user.push_back(temp);
return 0;
}

int Network::read_friends(char* file) // initial command line argv[1]
{
	ifstream ifile(file);
	int x; // initial number of users
	if(ifile.fail() ) {
		cout << "You fail this class." << endl;
		return -1;
	}
	ifile >> x;
	if ( ifile.fail() ) {
		cout << "Error reading an integer." << endl;
		return -1;
	}
	for (int i = 0; i < x; i++) {
		int id;
		ifile >> id;
		ifile.ignore(2);

		string name;
		getline(ifile,name);
		ifile.ignore(1);

		int year;
		ifile >> year;
		ifile.ignore(2);

		int zip;
		ifile >> zip;
		ifile.ignore(2);

		string friends;
		getline(ifile,friends);

		add_user(id, name, year, zip, friends);
	}
	return 0;
}

void Network::print_user_info() // function 4
{
	cout << setw(6) << "ID" << setw(26) << "Name" << setw(8) << "Year" << setw(10) << "zip" << setw(6) << endl;
	cout << "==================================================================" << endl;
	for (int unsigned i = 0; i < user.size(); i++) {
		int temp_id = user[i].get_id();
		string temp_name = user[i].get_name();
		int temp_year = user[i].get_year();
		int temp_zip = user[i].get_zip();
	
		cout << setw(5) << temp_id << "." << setw(26) << temp_name << setw(8) << temp_year << setw(10) << temp_zip << setw(6) << endl;
	}
}

int Network::print_friends_info(string name) // function 5
{
	int error = -1;
	for (int unsigned i = 0; i < user.size(); i++) {
		string temp_name = user[i].get_name();

		if (temp_name == name) {
			error--;
			int numFriends = user[i].get_friend_size();
			cout << setw(6) << "ID" << setw(26) << "Name" << setw(8) << "Year" << setw(10) << "zip" << setw(6) << endl;
			cout << "==================================================================" << endl;

			for (int j = 0; j < numFriends; j++) {
				int f = user[i].get_friend_id(j); // id of a friend
				int friend_id = user[f].get_id();
				string friend_name = user[f].get_name();
				int friend_year = user[f].get_year();
				int friend_zip = user[f].get_zip();
				cout << setw(5) << friend_id << "." << setw(26) << friend_name << setw(8) << friend_year << setw(10) << friend_zip << setw(6) << endl;
			}
		}
	}
return error;

}

int Network::get_id(string name)
{
	for (int unsigned i = 0; i < user.size(); i++) { // checks whether input name exists at all
		if (name == user[i].get_name() ) {
		
			return user[i].get_id();
		}
	}
return -1;
}

int Network::add_connection(int id, int id2) // function 2
{
	for (int i = 0; i < user[id].get_friend_size(); i++) { // this loop checks if the input users are already friends
		if (user[id].get_friend_id(i) == id2) {
			return -1;
		}
	}

	if (id == -1 || id2 == -1) {
		return -1;
	}
	else {
		user[id].add_friend(id2); // user 1 adds user 2 as an amigo
		user[id2].add_friend(id); // user 2 adds user 1 as a friend
	}
return 0;
}

int Network::remove_connection(int id, int id2) // function 3
{
	if (id == -1 || id2 == -1) {
		return -1;
	}
	else {
		user[id].delete_friend(id2);
		user[id2].delete_friend(id);
	}
return 0;
}

void Network::print_user_size()
{
	cout << user.size() << endl;
}

int Network::write_friends(char* file) // function 6
{
	ofstream ofile(file);

	if ( ofile.fail() ) {
		return -1;
	}

	ofile << user.size() << endl;
	for (int unsigned i = 0; i < user.size(); i++) {
		ofile << user[i].get_id() << endl;
		ofile << "\t" << user[i].get_name() << endl;
		ofile << "\t" << user[i].get_year() << endl;
		ofile << "\t" << user[i].get_zip() << endl;
		ofile << "\t";

		int friend_size = user[i].get_friend_size();
		if ( friend_size > 0 ) {
			ofile << user[i].get_friend_id(0);
		}

		for (int j = 1; j < friend_size; j++) {
			ofile << " " << user[i].get_friend_id(j);
		}
		ofile << endl;
	} ofile.close();
	return 0;
}

int Network::print_distance(int id, int id2) // function 7
{
	// set all predecessor to -1
	int user_size = get_user_size();
	for (int  i = 0; i < user_size; i++) {
		user[i].set_pre(-1);
	}

	deque<int> bfs;
	bfs.push_front(id); // first queue in bfs is source user
	user[id].set_depth(0); // source user depth = 0
	user[id].set_pre(-2); // source user pre = -2
	bool found = false;
	int found_location = 0;
	int i = 0; // bfs starts at 0
	while ( !bfs.empty() ) {
		int depth = user[ bfs[i] ].get_depth();
		// int pre = user[ bfs[i] ].get_pre();
		int friend_size = user[ bfs[i] ].get_friend_size();

		for (int j = 0; j < friend_size; j++) {
			int f = user[ bfs[i] ].get_friend_id(j); // frined id holder; f updates everytime!

			if (f == id2) { // has found a path to the destination user
				user[f].set_pre( bfs[i]);
				user[f].set_depth(depth+1);
				found_location = f;
				found = true;
				while (!bfs.empty()) { 
					bfs.pop_front(); 
					}
				bfs.push_back(1);
				break;
			}

			else if (f != id2 && user[f].get_pre() == -1) { 
				user[f].set_pre( bfs[i]);
				user[f].set_depth(depth+1);
				bfs.push_back(f);
			}
		}
		bfs.pop_front();
	}

	for (int i = 0; i < user[id].get_friend_size(); i++) { // direct friend detection code
		int f = user[id].get_friend_id(i);
		if (f == id2) {
			user[f].set_depth(1);
			user[f].set_pre(id);
			found = true;
			found_location = user[id].get_friend_id(i);
		}
	}
	
	if (found == true) { // cout code here
		cout << "Distance: " << user[found_location].get_depth() << endl;
		cout << user[found_location].get_name();

		int index = user[found_location].get_pre();
		while (user[index].get_pre() != -2) {
			cout << " -> " << user[index].get_name();
			index = user[index].get_pre();
		} 
		cout << " -> " << user[id].get_name() << endl;
	}

	else {
		return -1;
	}
return 0;
}

void Network::print_groups() // function 8
{
	int group = 0;
	int user_size = get_user_size();

	for (int i = 0; i < user_size; i++) { // all members are group 0 by default
		user[i].set_set_member(0);
	}

	for (int i = 0; i < user_size; i++) { // single and lonely groups just like me
		if (user[i].get_friend_size() == 0) {
			group++;
			user[i].set_set_member(group);
		}
	}

	for (int i = 0; i < user_size; i++) {
		if (user[i].get_set_member() == 0) { // if set_member is still 0, default, then do the bfs
			deque<int> bfs;
			int id = user[i].get_id();
			bfs.push_front(id);
			group++;

			while ( !bfs.empty() ) {
				int friend_size = user[ bfs[0] ].get_friend_size(); // always first item in bfs
				
				if (friend_size > 0) {
					bool newFriends;
					for (int k = 0; k < friend_size; k++) {
						int f = user[ bfs[0] ].get_friend_id(k); // frined id holder, 
						if (user[f].get_set_member() == 0)
							newFriends = true;
						}
					if (newFriends) {
						if (user[i].get_set_member() == 0) { // self member assignment
							user[i].set_set_member(group);
						}

						for (int j = 0; j < friend_size; j++) {
							int f = user[ bfs[0] ].get_friend_id(j); // frined id holder, 
							if (user[f].get_set_member() == 0) { 
								user[f].set_set_member(group);
								bfs.push_back(f);
							}
						}
						bfs.pop_front();
					}
				}
			}
		}	
	}
	int group_size = 0;
	for (int i = 0; i < user_size; i++) { // checks how many groups there are 
		if (user[i].get_set_member() > group_size) {
			group_size = user[i].get_set_member();
		}
	}

	for (int i = 1; i < (group_size+1); i++) {
		
		cout << "Set " << i << " => ";
		for (int j = 0; j < user_size; j++) {
			if ( user[j].get_set_member() == i) {
				cout << user[j].get_name() << ", ";
				
			}
		}
		cout << "\b\b \b"; 
		cout << endl;
	}
}
	
int Network::friend_suggestion(int id) // function 9
{
	int error = -1;
	for (int unsigned i = 0; i < user.size(); i++) {
		string temp_name = user[i].get_name();

		if (temp_name == user[id].get_name()) {
			error--;
		}
	}



	int user_size = get_user_size();
	for (int i = 0; i < user_size; i++) { // all scores are 0 by default
		user[i].set_score(0);
	}

	user[id].set_score(-1); // source score -1
	
	int source_friend_size = user[id].get_friend_size();
	for (int i = 0; i < source_friend_size; i++) {
		int friend_id = user[id].get_friend_id(i); // source's friends
		int friend_size = user[friend_id].get_friend_size(); 
		for (int j = 0; j < friend_size; j++) {
			int score_friend_id = user[friend_id].get_friend_id(j); // friends of source's friends inception
			if (user[score_friend_id].get_score() != -1) { // if the friends score is not -1, or not source, increment
				int current_score = user[score_friend_id].get_score();
				current_score++;
				user[score_friend_id].set_score(current_score);
			}
		}
	}

	int suggestion_score = 0;
	for (int i = 0; i < user_size; i++) { // checks the highest score to print out
		if (user[i].get_score() > suggestion_score) {
			suggestion_score = user[i].get_score();	
		}
	}
	cout << "The strongest candidates(s) is/are:" << endl;
	for (int i = 0; i < user_size; i++) { // cout all humans with the suggestion score
		if (user[i].get_score() == suggestion_score) {
			cout << setw(30) << user[i].get_name() << setw(23) << "Score: " << suggestion_score << endl;	
		}
	}
return error;
}


