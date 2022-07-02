#pragma once
#include "News.h"
#include "admin.h"
#include <vector>
#include <string>
#include <list>

using namespace std;
class user
{


public:
	string userName;
	string password;
	list<int> spammedNews;
	list<int>ratedNews;
	user();
	user(string inputUserName, string inputPassword);
	void addComment(News& obj);
	void displayComments(News& obj);
	bool findNews(list<int> newsIndex, News obj);
	void rateNews(News& obj);
	void spamNews(News& obj);
	void displayNews(News& obj); // all , date
	void displayByRate(vector<News>& allNews); // all, rate
	void displayByDate(vector<News>& allNews);
	void displayByCategory(vector<News>& allNews, admin obj); // category , date


};

