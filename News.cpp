#include "News.h"
#include <string>

News::News() {
	title = "";
	rate = 0;
	category = "";
	date.day = 0;
	date.month = 0;
	date.year = 0;
	newsCount++;
	newsID = newsCount;
}