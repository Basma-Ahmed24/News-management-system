#include "user.h"
#include"admin.h"
#include"News.h"
#include <iostream>
#include <cctype>
#include <cmath>
#include <stack>
#include <algorithm>
using namespace std;

int News::newsCount = 0;

user::user() {
	userName = "";
	password = "";
}

user::user(string inputUserName, string inputPassword) {
	userName = inputUserName;
	password = inputPassword;
}

bool user::findNews(list<int> newsIndex, News obj) {
	bool flag = false;
	list<int> ::iterator it;
	for (it = newsIndex.begin(); it != newsIndex.end(); it++) {
		if ((*it) == obj.newsID)
			flag = true;
	}
	return flag;
}


void user::rateNews(News& obj)
{
	float newrate = 0;

	if (findNews(ratedNews, obj))
	{
		cout << "\n\nYou are already rated!\n" ;
	}
	else {
		do
		{
		here:
			cout << "\n\nYour Rate (Please Enter Number from 1 To 5): ";
			cin >> newrate;
			if (!cin) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				goto here;
			}

			int isInt = newrate;
			if (isInt != newrate)
			{
				cin.clear();
				goto here;
			}

		} while (newrate > 5 || newrate <= 0);
		obj.numOfRatedUsers++;
		obj.rate = ceil(((obj.rate * (obj.numOfRatedUsers - 1)) + newrate) / obj.numOfRatedUsers);
		ratedNews.push_back(obj.newsID);
	}

}


void user::spamNews(News& obj) {
	spammedNews.push_back(obj.newsID);
	obj.spamCount++;
	cout << "\n\nNews spammed successfully.\n";
}


void user::addComment(News& obj) {
	Comment userComment;
	cout << "\n\nEnter your comment :" << endl;
	cin >> userComment.commentContent;
	userComment.username = userName;
	obj.comments.push_back(userComment);
}

void user::displayComments(News& obj) {
	if (obj.comments.empty()) {
		cout << "\n\nNo comments yet\n enter 1 to add a new comment or press any key to continue\n ";
		int choice;
		cin >> choice;
		if (choice == 1)
			addComment(obj);
		else
			return;
	}
	else {
		list<Comment>::iterator it;
		cout << "\n\n";
		for (it = obj.comments.begin(); it != obj.comments.end(); it++) {
			cout << "user name: " << it->username << endl;
			cout << "comment: " << it->commentContent << endl;
			cout << "\t\t-----------------" << endl;
		}
	}
}

void user::displayNews(News& obj)
{
	if (obj.rate != 1 && !findNews(spammedNews, (obj))) {
		system("cls");
		cout << obj.date.day << "-" << obj.date.month << "-" << obj.date.year << endl;
		cout << "Title : " << obj.title << endl;
		cout << "Rate : " << obj.rate << endl;
		cout << "Number of users who spammed it : " << obj.spamCount << endl;
		cout << "Category : " << obj.category << endl;
		cout << "Description : " << endl;
		cout << obj.description << endl;
		int choice = 0;
		do {
			cout << "=====================================" << endl;
			cout << "Enter the number you want to choose " << endl;
			cout << "1- rate \n2- add comment \n3- display all comment \n4- spam this news \n5- skip to next news\n";

			cin >> choice;
			if (choice == 1)
				rateNews((obj));
			else if (choice == 2)
				addComment((obj));
			else if (choice == 3)
				displayComments((obj));
			else if (choice == 4)
				spamNews((obj));
			else if (choice == 5)
				system("cls");
			else
			{
				cout << "invalid number!\n\n";

				system("pause");
			}
		} while (choice != 5);

	}



}

void user::displayByDate(vector<News>& allNews)
{
	vector<News>::iterator it = allNews.end();
	while (it != allNews.begin())
	{
		--it;
		displayNews((*it));
	}
}

void user::displayByRate(vector<News>& allNews) {

	int currentRate = 5;
	vector<News>::iterator it = allNews.end();
	while (currentRate > -1) {
		while (it != allNews.begin()) {
			it--;
			if ((*it).rate == currentRate) {
				displayNews((*it));
			}

		}
		currentRate--;
		it = allNews.end();
	}
}


void user::displayByCategory(vector<News>& allNews, admin obj) {

	set<string>::iterator itC = obj.categories.begin();
	cout << "please enter the category you want" << endl;

	while (itC != obj.categories.end())
	{
		cout << (*itC) << endl;
		itC++;
	}
	string choise;
	cin >> choise;
	bool FoundCategory = false;
	vector<News>::iterator it = allNews.end();
	while (it != allNews.begin())
	{
		it--;
		if ((*it).category == choise)
		{
			displayNews((*it));
			FoundCategory = true;
		}
	}

	if (!FoundCategory)
		cout << "No news is posted in this category yet\n";

}
