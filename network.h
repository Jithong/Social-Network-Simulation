#ifndef NETWORK_H
#define NETWORK_H
#include"user.h"
#include<vector>
#include<string>
using namespace std;

class Network {
 public:
	Network();
	~Network();
	int add_user(int id, string name, int year, int zip, string friends);
	void add_user(int id, string name, int year, int zip);
	int add_connection(int id, int id2);
	int remove_connection(int id, int id2);
	int get_id(string name);
	int read_friends(char* file);
	int write_friends(char* file);
	int get_user_size();
	void print_user_info();
	int print_friends_info(string name);
	void print_user_size(); // may not be used
	int print_distance(int id, int id2);
	void print_groups();
	int friend_suggestion(int id);
 private:
	vector<User> user;
	
};


#endif
