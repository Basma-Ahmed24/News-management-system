#include "News.h"
#include"admin.h"
#include"user.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
#include <list>
#include<unordered_map>

using namespace std;


void signUp();
void signIn();
void welcomePage();
void adminMenue();
void userPage(string username);
void writeCommentsOnFile(News obj);


fstream userFile;
fstream newsFile;
vector<News> allNews;
unordered_map<string, user> allUsers;
admin appAdmin("admin", "admin");

void main() {
	welcomePage();
}

void signUp()
{
	cout << "============ sign up page ============" << endl;
	char  tempChar;
	int i = 0;
	string username;
	char password[20];
	cout << "Enter username :"; cin >> username;
	cout << "Enter password :";
	for (i = 0;;) {
		tempChar = _getch();

		if ((tempChar >= 'a' && tempChar <= 'z') || (tempChar >= 'A' && tempChar <= 'Z') || (tempChar >= '0' && tempChar <= '9'))
		{
			password[i] = tempChar;
			++i;
			cout << "*";
		}

		if (tempChar == '\b' && i >= 1) {
			cout << "\b \b";
			--i;
		}

		if (tempChar == '\r') {
			password[i] = '\0';
			break;
		}
	}
	user temp(username, password);
	if (allUsers.find(username) != allUsers.end()) {
		cout << "This user already exists\n";
		system("cls");
		signUp();
	}
	else {
		userFile.open("userFile.txt", ios::app);
		userFile << username << endl << password<<endl;
		userFile.close();
		cout << endl;
		allUsers[username] = temp;
		signIn();
	}
}

void signIn() {
	char  tempChar;
	int i = 0;
	string username;
	char password[20];
	cout << "============ sign in page ============" << endl;
	cout << "Username :"; cin >> username;
	cout << "Password :";
	for (i = 0;;) {
		tempChar = _getch();

		if ((tempChar >= 'a' && tempChar <= 'z') || (tempChar >= 'A' && tempChar <= 'Z') || (tempChar >= '0' && tempChar <= '9'))
		{
			password[i] = tempChar;
			++i;
			cout << "*";
		}

		if (tempChar == '\b' && i >= 1) {
			cout << "\b \b";
			--i;
		}

		if (tempChar == '\r') {
			password[i] = '\0';
			break;
		}
	}
	if (username == appAdmin.userName && password == appAdmin.password) {
		system("cls");
		adminMenue();
	}
	else {

		if (allUsers.find(username) != allUsers.end() && password == allUsers[username].password) {
			system("cls");
			userPage(username);
		}
		else {
			cout << "\nFailed to login.\n";
			system("pause");
			system("cls");
			welcomePage();
		}
	}
}

void welcomePage() {
rechoose:
	cout << "============ welcome to News Whistler ============" << endl;
	string x;
	cout << "1- Sign Up" << endl << "2- Sign In" << endl << "3- Exit" << endl;
	cout << "Choose :"; cin >> x;
	if (x == "1")
		signUp();
	else if (x == "2")
		signIn();
	else if (x == "3") {
		system("cls");
		vector<News>::iterator it = allNews.begin();
		newsFile.open("newsFile.txt", ios::out);
		while (it != allNews.end())
		{
			newsFile << "Title: " << (*it).title << endl;
			newsFile << "Description: " << (*it).description << endl;
			newsFile << "Category: " << (*it).category << endl;
			newsFile << "Date: " << (*it).date.day << "-" << (*it).date.month << "-" << (*it).date.year << endl;
			newsFile << "Rate: " << (*it).rate << endl;
			newsFile << "Number of users who spammed it: " << (*it).spamCount << endl;
			writeCommentsOnFile(*it);
			it++;
		}
		newsFile.close();
		exit(EXIT_FAILURE);
	}
	else {
		cout << "invalid number!\n";
		system("pause");
		system("cls");
		goto rechoose;
	}
}

void adminMenue() {
rechoose:
	cout << "\n============ Admin page ============" << endl;
	cout << "\nwhich operation you want?" << endl;
	int adminChoice;
	cout << "1- post news\n";
	cout << "2- Update news\n";
	cout << "3- delete news\n";
	cout << "4- sign out\n";
	cin >> adminChoice;
	
	switch (adminChoice) {
	case 1: {
		system("cls");
		cout << "\n============ Post News ============" << endl;
		appAdmin.postNews(allNews);
		system("cls");
		goto rechoose;
		break;
	}
	case 2: {
		system("cls");
		string searchTitle;
		string searchCategory;
		cout << "\n============ Update News ============" << endl;
		cout << "Enter the title of the news you want to update\n";
		cin >> searchTitle;
		cout << "Enter the category of the news you want to update\n";
		cin >> searchCategory;
		appAdmin.updateNews(allNews, searchTitle, searchCategory);
		system("cls");
		goto rechoose;
		break;
	}
	case 3: {
		system("cls");
		string searchTitle;
		string searchCategory;
		cout << "\n============ Delete News ============" << endl;
		cout << "Enter the title of the news you want to delete\n";
		cin >> searchTitle;
		cout << "Enter the category of the news you want to delete\n";
		cin >> searchCategory;
		appAdmin.deleteNews(allNews, searchTitle, searchCategory);
		system("cls");
		goto rechoose;
		break;
	}
	case 4: {
		system("cls");
		welcomePage();
		break;
	}
	default: {
		cout << "invalid number\n";
		system("cls");
		goto rechoose;
	}
	}
	
}

void userPage(string username) {
rechoose:
	cout << "============ User Page ============" << endl;
	int userChoice;
	cout << "\nwhich operation you want?" << endl;
	cout << "1- Show News \n";
	cout << "2- Show News by a Specific Category\n";
	cout << "3- Show News by Highest Rate\n";
	cout << "4- sign out\n";
	cin >> userChoice;
	
	switch (userChoice)
	{
	case 1:
	{
		if (allNews.empty()) {
			cout << "\n\nNo news is posted yet\n";
			system("pause");
			system("cls");
			goto rechoose;
		}
		else
			allUsers[username].displayByDate(allNews);
		break;
	}

	case 2:
	{
		if (allNews.empty()) {
			cout << "\n\nNo news is posted yet\n";
			system("pause");
			system("cls");
			goto rechoose;
		}
		else
			allUsers[username].displayByCategory(allNews, appAdmin);
		break;
	}
	case 3:
	{
		if (allNews.empty()) {
		cout << "\n\nNo news is posted yet\n";
		system("pause");
		system("cls");
		goto rechoose;
		}
		else
		allUsers[username].displayByRate(allNews);
		break; 
	}

	case 4:
		system("cls");
		welcomePage();
		break;
	default:
		{
			cout << "invalid number\n";
			system("cls");
			
		}
	
	}

	goto rechoose;
}


void writeCommentsOnFile(News obj) {
	list<Comment>::iterator it = obj.comments.begin();
	while (it != obj.comments.end())
	{
		newsFile << "Username: " << (*it).username << endl;
		newsFile << "Comment: " << (*it).commentContent << endl;
		newsFile << "-------------------------------";
	}
}
