#ifndef USER_H
#define USER_H
#include<vector>
#include<string>
using namespace std;

class User {
 public:
	User(int id, string name, int year, int zip);
	~User();
	void add_friend(int id);
	void delete_friend(int id);
	int get_id();
	string get_name();
	int get_year();
	int get_zip();
	int get_friend_size();
	int get_friend_id(int j);

	int get_pre();
	void set_pre(int pre);
	int get_depth();
	void set_depth(int depth);
	int get_set_member();
	void set_set_member(int member);
	int get_score();
	void set_score(int score);

 private:
	int _id;
	string _name;
	int _year;
	int _zip;
	vector<int> _friend;

	int _depth;
	int _pre;
	int _score;
	int _set_member;
};


#endif
