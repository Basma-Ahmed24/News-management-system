#pragma once
#include <string>
#include<list>
using namespace std;
class Date
{
public:
	int year, month, day;
};

class Comment {
public:
	string commentContent;
	string username;
};

class News
{
	static int newsCount;

public:
	News();
	string title;
	string description;
	Date date;
	int rate;
	string category;
	list<Comment> comments;
	int spamCount;
	int newsID;
	int numOfRatedUsers;

};

