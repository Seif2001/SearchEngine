#include "Article.h"
#include<iostream>
using namespace std;
Article::Article()
{
	pageRank = 0.0;
	url = "";
	impressions = 0.0;
	

}

Article::Article( string URL, double impresh, int ind)
{
	index = ind;
	pageRank = 0.0;
	url = URL;
	impressions = impresh;
	
}
void Article::setimpressions(double imp)
{
	impressions = imp;
}
void Article::setClicks(double cl)
{
	clicks = cl;
}
double Article::getimpressions()
{
	return impressions;
}
double Article::getclicks()
{
	return clicks;
}
double Article::calculateScore()
{	
	score = 0.4 * pageRank + (((1 - (0.1 * impressions) / 1 + 0.1 * impressions) * pageRank + (0.1 * impressions) / 1 + 0.1 * impressions) * (clicks/impressions)) * 0.6;
	return score;
}
void Article::printPage() {
	cout << "------------------------------------------------------" << endl;
	cout << url << "		" << impressions << endl;
	cout << "key Words:" << endl;
	for (int i = 0; i < keyWords.size(); i++) {
		cout << keyWords[i]<<endl;
	}
	

	cout << "HyperLinks: " << endl;
	for (auto& x:hyperLinks){
		cout<<(*x).url<<endl;
	}
	cout << "To HyperLinks: " << endl;
	for (auto& x : fromLinks) {
		cout << (*x).url << endl;
	}
	cout << "Page Rank: " << pageRank << endl;
}
void Article::addKeyword(string keyword)
{
	keyWords.push_back(keyword);
}

void Article::updateImpressions()
{
	impressions++;
}

bool Article::operator<(Article a)
{
	if (this->getUrl() < a.getUrl()) {
		return true;
	}
	return false;
}

bool Article::operator>(Article a)
{
	if (this->getUrl() > a.getUrl()) {
		return true;
	}
	return false;
}

double Article::getHyperLinkNum()
{
	return hyperLinks.size();
}

void Article::updatePageRank(double val)
{
	pageRank = val;
}

void Article::updateInitialPageRank(double val)
{
	intitalPageRank = val;
}

void Article::updateCt()
{
	clicks++;
}

double Article::getInitialPageRank()
{
	return intitalPageRank;
}

string Article::getUrl()
{
	return this->url;
}

Article Article::HyperLinkAt(int i)
{
	if (hyperLinks.size() > 0) {
		return *hyperLinks[i];
	}
}

Article Article::FromHyperLinkAt(int i)
{
	if (fromLinks.size() > 0) {
		return *fromLinks[i];
	}
}

void Article::addHyperLink(Article *hLink)
{
	hyperLinks.push_back(hLink);
}
Article Article::getfromhyperlinkAt(int j)
{
	return *fromLinks[j];
}
void Article::print()
{
	cout << "YOU ARE NOW VIEWING: " << url << endl;
}
double Article:: getfromHyperLinkNum() {
	return fromLinks.size();
}
double Article::getPageRankAt(int j)
{
	return (*fromLinks[j]).pageRank;
}
void Article::addfromHyperLink(Article *hLink)
{
	fromLinks.push_back(hLink);

}
double Article::getPageRank() {
	return pageRank;
}
