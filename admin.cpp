#include "admin.h"
#include <vector>
#include "News.h"
#include <list>
#include <set>
#include<iostream>

using namespace std;


admin::admin(string adminUserName, string adminPassword) {
	userName = adminUserName;
	password = adminPassword;
}

int admin::searchNews(vector<News> allNews, string title, string category) {
	vector<News>::iterator it = allNews.begin();
	int index = 0;
	while (it != allNews.end()) {
		if ((*it).title == title && (*it).category == category)
			return index;
		else
		{
			index++;
			it++;
		}
	}
	return -1;
}

void admin::postNews(vector<News>& allNews)
{
	News newnews;
	cout << "Enter the Title" << endl;
	cin >> newnews.title;
	cout << "Enter the Date (dd mm yyyy)" << endl;
	cin >> newnews.date.day >> newnews.date.month >> newnews.date.year;
	cout << "Enter the Category" << endl;
	cin >> newnews.category;
	categories.insert(newnews.category);
	cout << "Enter the Description" << endl;
	cin >> newnews.description;
	if (allNews.empty()) {
		allNews.push_back(newnews);
	}
	else {
		if ((allNews[allNews.size() - 1].date.year < newnews.date.year) ||
			(allNews[allNews.size() - 1].date.year == newnews.date.year && allNews[allNews.size() - 1].date.month < newnews.date.month) ||
			(allNews[allNews.size() - 1].date.year == newnews.date.year && allNews[allNews.size() - 1].date.month == newnews.date.month && allNews[allNews.size() - 1].date.day < newnews.date.day) ||
			(allNews[allNews.size() - 1].date.year == newnews.date.year && allNews[allNews.size() - 1].date.month == newnews.date.month && allNews[allNews.size() - 1].date.day == newnews.date.day))
		{
			allNews.push_back(newnews);
		}
		else {

			for (int i = 0; i <= allNews.size() - 1; i++) {
				if ((allNews[i].date.year > newnews.date.year) ||
					(allNews[i].date.year == newnews.date.year && allNews[i].date.month > newnews.date.month) ||
					(allNews[i].date.year == newnews.date.year && allNews[i].date.month == newnews.date.month && allNews[i].date.day > newnews.date.day) ||
					(allNews[i].date.year == newnews.date.year && allNews[i].date.month == newnews.date.month && allNews[i].date.day == newnews.date.day))
				{
					vector<News>::iterator it = allNews.begin() + i;
					allNews.insert(it, newnews);
					break;
				}
			}
		}
	}
	cout << "\n\nNews is posted successfully\n" << endl;
}

void admin::updateNews(vector<News>& allNews, string title, string category) {
	int index = searchNews(allNews, title, category);
	if (index != -1)
	{
	rechoose:
		cout << "what do you need to update?" << endl;
		int updateChoice;
		cout << "1- Update title\n";
		cout << "2- Update description\n";
		cout << "3- Update category\n";
		cin >> updateChoice;
		switch (updateChoice) {
		case 1: {
			string newTitle;
			cout << "Enter New title\n";
			cin >> newTitle;
			allNews[index].title = newTitle;
			cout << "\n\ntitle is updated successfully\n" << endl;
			break;
		}
		case 2: {
			string newDescription;
			cout << "Enter New description\n";
			cin >> newDescription;
			allNews[index].description = newDescription;
			cout << "\n\ndescription is updated successfully\n" << endl;
			break;
		}
		case 3: {
			string newCategory;
			cout << "Enter New category\n";
			cin >> newCategory;
			allNews[index].category = newCategory;
			cout << "\n\ncategory is updated successfully\n" << endl;
			break;
		}
		default: {
			cout << "\n\ninvalid number\n";
			system("pause");
			system("cls");
			goto rechoose;
		}
		}
	}
	else
		cout << "\n\nThe News you want to update dose not exist\n";
	system("pause");
}

void admin::deleteNews(vector<News>& allNews, string title, string category) {
	int index = searchNews(allNews, title, category);
	if (index != -1) {
		vector<News>::iterator it = (allNews.begin() + index);
		allNews.erase(it);
		cout << "\n\nNews is deleted successfully\n" << endl;
	}
	else
		cout << "\n\nThe News you want to delete dose not exist\n";
	system("pause");
}
