#include<iostream>
#include<string>
#include<vector>
#include"user.h"
using namespace std;

User::User(int id, string name, int year, int zip) // constructor
{
	_id = id;
	_name = name;
	_year = year;
	_zip = zip;
}

User::~User() // no dynamically allocated memory
{
}

void User::add_friend(int id)
{
	_friend.push_back(id);
}

void User::delete_friend(int id)
{
	for(unsigned int i = 0; i < _friend.size(); i++) {
		if (_friend[i] == id) {
			_friend.erase(_friend.begin()+i); //
		}
	}
}

int User::get_id( )
{
	return _id;
}

string User::get_name( )
{
	return _name;
}

int User::get_year( )
{
	return _year;
}

int User::get_zip( )
{
	return _zip;
}

int User::get_friend_size()
{
	return _friend.size();
}

int User::get_friend_id(int j)
{
	return _friend[j];
}

int User::get_pre()
{
	return _pre;
}

void User::set_pre(int pre)
{
	_pre = pre;
}

int User::get_depth()
{
	return _depth;
}

void User::set_depth(int depth)
{
	_depth = depth;
}

int User::get_set_member()
{
	return _set_member;
}

void User::set_set_member(int member)
{
	_set_member = member;
}

int User::get_score()
{
	return _score;
}

void User::set_score(int score)
{
	_score = score;
}


