#include <iostream>
#include"Article.h"
#include<fstream>
#include <bits/stdc++.h>
#include<vector>
#include<unordered_map>
#include <string>
#include<algorithm>
using namespace std;
// merge sort for sorting the resulting websites according to scores. 
template<typename T>
void merge_results(vector<T>& vec, vector<T>& v1, vector<T>& v2) {
	auto siz1 = v1.size();
	auto siz2 = v2.size();
	size_t p1 = 0;
	size_t p2 = 0;

	while (p1 < siz1 && p2 < siz2)
	{
		if (v1[p1].calculateScore() > v2[p2].calculateScore())
			vec.push_back(v1.at(p1++));
		else
			vec.push_back(v2.at(p2++));
	}

	while (p1 < siz1) vec.push_back(v1.at(p1++));
	while (p2 < siz2) vec.push_back(v2.at(p2++));
}
template<typename T>
void mergeSort_results(vector<T>& vec) {
	if (vec.size() <= 1)
		return;

	auto iter = vec.begin() + vec.size() / 2;
	vector<T> v1(vec.begin(), iter);
	vector<T> v2(iter, vec.end());

	mergeSort_results(v1);
	mergeSort_results(v2);

	vec.clear();
	merge_results(vec, v1, v2);
}
bool binarySearch(vector<Article>arr, Article x, int n)
{
	int l = 0;
	int r = n - 1;
	while (l <= r)
	{
		int m = l + (r - l) / 2;

		int res = -1000;   //some random value assigned because if res is already 0 then
							 //it will always return 0    
		if (x.getUrl() == (arr[m].getUrl()))
			res = 0;    


		// Check if x is present at mid
		if (res == 0)
			return 1;

		// If x greater, ignore left half
		if (x > (arr[m]))
			l = m + 1;

		// If x is smaller, ignore right half
		else
			r = m - 1;
	}

	return 0;
}

void heapify(vector<Article>& arr, int n, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l<n && arr[l]>arr[largest]) {
		largest = l;
	}

	if (r<n && arr[r]>arr[largest]) {
		largest = r;
	}

	if (largest != i) {
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}

}



void build_heap(vector<Article>& arr, int n) {
	int c = 0;
	for (int i = n / 2 - 1; i >= 0; i--) {

		heapify(arr, n, i);

	}


}

void heap_sort(vector<Article>& arr, int n) {

	build_heap(arr, n);
	for (int i = n - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}

}
void pageRank(vector<Article>& articles ) {
	for (int i = 0; i < articles.size(); i++) {
		double prI = 1.0 / articles.size();
		
		articles[i].updateInitialPageRank(prI);
	
	}
	
	for (int i = 0; i < articles.size(); i++) {
		
		double pr = 0;
		
		for (int j = 0; j < articles[i].getfromHyperLinkNum(); j++) {
			
			
			pr += (articles[i].getfromhyperlinkAt(j).getInitialPageRank() / articles[i].getfromhyperlinkAt(j).getHyperLinkNum());
			
			//cout << articles[i].getfromhyperlinkAt(j).getHyperLinkNum() << "    ";
		}
		//pr = (1 - d) + d * pr;
		//cout << endl;
		articles[i].updateInitialPageRank(pr);
		//cout << articles[i].getInitialPageRank() << endl;
		
		
	}

	for (int i = 0; i < articles.size(); i++) {

		double pr = 0;

		for (int j = 0; j < articles[i].getfromHyperLinkNum(); j++) {
			

			pr += (articles[i].getfromhyperlinkAt(j).getInitialPageRank() / articles[i].getfromhyperlinkAt(j).getHyperLinkNum());
			
		}
		
		articles[i].updatePageRank(pr);



	}

}

vector<Article> getResults(string entry, unordered_map<string, vector<Article>> &search) {
	string s = entry;
	string first;
	string second;
	string del1 = " AND ";
	string del2 = " OR ";
	if (entry[0] == '"' && entry[entry.size() - 1] == '"') {
		entry = entry.substr(1, entry.size() - 2);
		return search[entry];
	}
	else if(entry.find(del1) != string::npos) {
		first = s.substr(0, s.find(del1));
		second = entry.substr(entry.find(del1) + del1.size());
		vector<Article> a;
		heap_sort(search[second], search[second].size());
		for (int i = 0; i < search[first].size(); i++) {
			if (binarySearch(search[second], search[first][i], search[second].size())) {
				a.push_back(search[first][i]);
			}
		}
		return a;
	}
	else if (entry.find(del2) != string::npos ) {
		first = s.substr(0, s.find(del2));
		second = entry.substr(entry.find(del2) + del2.size());
		vector<Article> a;
		for (int i = 0; i < search[first].size(); i++) {
			a.push_back(search[first][i]);
		}
		heap_sort(a, a.size());
		for (int i = 0; i < search[second].size(); i++) {
			if (!binarySearch(a, search[second][i], a.size()) ){
				a.push_back(search[second][i]);
			}
		}
		return a;
	}
	else {
		vector<Article> a;
		for (int i = 0; i < search[entry].size(); i++) {
			a.push_back(search[entry][i]);
		}
		heap_sort(a, a.size());
		stringstream s(entry);
		while (getline(s, first, ' ')) {
			for (int i = 0; i < search[first].size(); i++) {
				if (!binarySearch(a, search[first][i], a.size())) {
					a.push_back(search[first][i]);
				}
			}
		}
		return a;
	}
}
int welcome() {
	int choice;
	string hi;
	cout << "Welcome! What would you like to do?" << endl;
	cout << "1. New search" << endl;
	cout << "2. Exit" << endl;
	do {
		cout << "Enter your choice";
		cin >> choice;
	} while (choice != 1 && choice != 2);
	return choice;

}
string newSearch() {
	string entry;
	cout << "Search: ";
	//cin >> entry;
	cin.ignore();
	getline(cin, entry);
	//cout << endl;
	return entry;
}
int displayResults(string s, unordered_map<string, vector<Article>> &search) {
	int choice;
	int i = 1;
	vector<Article> a = getResults(s, search);
	mergeSort_results(a);
	for (auto x : a) {
		cout << i << ". " << x.getUrl() << endl;
		i++;
	}
	cout << "Would you like to: " << endl;
	if (getResults(s, search).size()) {
		cout << "1. Choose webpage" << endl;
		cout << "2. New search" << endl;
		cout << "3. Exit" << endl;
	}
	else {
		cout << "1. Choose webpage" << endl;
		cout << "2. New search" << endl;
		cout << "3. Exit" << endl;
	}
	do {
		cout << "Enter your choice";
		cin >> choice;
	} while (choice < 1 && choice >3);
	return choice;
}
int chooseWebpage(string s, unordered_map<string, vector<Article>> search) {
	int choice;
	do {
		cout << "Choose webpage";
		cin >> choice;
	} while (choice < 1 && choice >getResults(s, search).size() - 1);
	return choice;
}

void write2file(vector<Article> pages) {
	fstream fout;
	fout.open("C:\\Users\\elsha\\Desktop\\SearchEngine\\SearchEngine\\Impressions.csv");
	for (int i = 0; i < pages.size(); i++) {
		if (i == pages.size() - 1) {
			fout << pages[i].getUrl() << " " << pages[i].getimpressions() << " " << pages[i].getclicks() ;
		}
		else {
			fout << pages[i].getUrl() << " " << pages[i].getimpressions() << " " << pages[i].getclicks() << endl;
		}
	}
}
void display(int x, bool m, string entry) {
	ifstream data;
	string url1;
	string keyword;
	string keywords;
	vector <Article> pages;
	string userEntry;
	unordered_map<string, vector<Article>> Search;
	data.open("C:\\Users\\elsha\\Desktop\\SearchEngine\\SearchEngine\\Impressions.csv");
	int impresh, clicks;
	if (!data) { // file couldn't be opened
		cerr << "Error: file could not be opened" << endl;
		exit(1);
	}
	int ind = 0;
	while (!data.eof()) {
		data >> url1;
		data >> impresh;
		data >> clicks;
		Article a(url1, impresh, ind);
		a.setClicks(clicks);
		pages.push_back(a);
		ind++;
	}
	data.close();
	data.open("C:\\Users\\elsha\\Desktop\\SearchEngine\\SearchEngine\\webGraph.csv");
	if (!data) { // file couldn't be opened
		cerr << "Error: file could not be opened" << endl;
		exit(1);
	}
	string url2;
	int ind1 = 0, ind2 = 0;
	while (!data.eof()) {
		data >> url1;
		data >> url2;
		for (int i = 0; i < pages.size(); i++) {
			if (url1 == pages[i].getUrl()) {
				ind1 = i;
			}
		}
		//cout <<url1 <<" --> " << url2 << endl;
		for (int j = 0; j < pages.size(); j++) {
			if (url2 == pages[j].getUrl()) {
				ind2 = j;
			}
		}

		//cout << ind1 << "    " << ind2 << endl;
		pages[ind1].addHyperLink(&pages[ind2]);
		pages[ind2].addfromHyperLink(&pages[ind1]);
	}
	data.close();
	data.open("C:\\Users\\elsha\\Desktop\\SearchEngine\\SearchEngine\\KeyWord.csv");

	while (!data.eof()) {

		getline(data, keywords);
		//cout << keywords << endl;

		stringstream ss(keywords);
		while (ss.good()) {
			getline(ss, keyword, ',');
			for (int i = 0; i < pages.size(); i++) {
				if (keyword == pages[i].getUrl()) {
					ind1 = i;
				}
			}
			if (keyword != pages[ind1].getUrl()) {
				pages[ind1].addKeyword(keyword);
				Search[keyword].push_back(pages[ind1]);
			}


		}

	}
	
	pageRank(pages);
	
	int choiceAfterdisplay;
	//newSearch();
		system("CLS");
		if (m) {
			userEntry = newSearch();
		}
		else {
			userEntry = entry;
		}
		
		choiceAfterdisplay = displayResults(userEntry, Search);
		for (auto& x : getResults(userEntry, Search)) {
			for (auto& y : pages) {
				if (x.getUrl() == y.getUrl()) {
					y.updateImpressions();
					//cout << y.getimpressions();
				}
			}
		}
		int choice;
		int res;
		switch (choiceAfterdisplay) {
		case 1: choice = chooseWebpage(userEntry, Search);
			cout << "1. Back to results" << endl;
			cout << "2. New search" << endl;
			cout << "3. Exit" << endl;
			cout << "Enter your choice ";
			cin >> res;
			switch (res) {
			case 1: display(res,0,userEntry);
				break;
			case 2: newSearch();
				break;
			default:
				exit(1);
			}
			getResults(userEntry, Search)[choice - 1].print();
			for (auto& y : pages) {
				if (getResults(userEntry, Search)[choice - 1].getUrl() == y.getUrl()) {
					y.updateCt();
				}
			}
			break;
		case 2:
			display(choiceAfterdisplay, 1 ,entry);
			break;
		default:
			exit(1);
		}
		

	write2file(pages);
}
int main() {
	int x = welcome();
	if (x == 2) {
		exit(1);
	}
	else {
		display(x,1,"");

	}
	//display(2);
}
//double start_time = clock();
//searching_query(temp_str);
//generate_searching_results();
//double end_time = clock();
//double execution_time = (end_time - start_time) / CLOCKS_PER_SEC;
//cout << " time needed to get websites results \n";
//cout << execution_time << " secs" << endl;

