#pragma once
#include "News.h"
#include <vector>
#include <string>
#include<set>

using namespace std;

class admin
{

	int searchNews(vector<News> allNews, string title, string category);
public:
	string userName;
	string password;
	set<string> categories;
	admin(string adminUserName, string adminPassword);
	void postNews(vector<News>& allNews);
	void updateNews(vector<News>& allNews, string title, string category);
	void deleteNews(vector<News>& allNews, string title, string category);
};

