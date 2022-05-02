#pragma once
#include<string>
#include <list>
#include<vector>
using namespace std;
class Article
{
private:
	string url;
	double clicks, impressions;
	double ctr;
	vector<string> keyWords;
	vector <Article*> hyperLinks;
	vector <Article*> fromLinks;
	double pageRank, intitalPageRank;
	double score;
public:
	int index;
	Article();
	Article( string url, double impressions, int ind);
	void setimpressions(double imp);
	void setClicks(double cl);
	double getimpressions();
	double getclicks();
	double calculateScore();
	void addKeyword(string keyword);
	void updateImpressions();
	bool  operator<(Article a);
	bool  operator>(Article a);
	double getPageRank();
	double getHyperLinkNum();
	void updatePageRank(double val);
	void updateInitialPageRank(double val);
	void updateCt();
	double getInitialPageRank();
	string getUrl();
	Article HyperLinkAt(int i);
	Article FromHyperLinkAt(int i);
	void printPage();
	double getfromHyperLinkNum();
	double getPageRankAt(int j);
	void addfromHyperLink(Article *hLink);
	void addHyperLink(Article *hLink);
	Article getfromhyperlinkAt(int j);
	void print();
};

