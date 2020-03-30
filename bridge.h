#include<bits/stdc++.h>
using namespace std;

class bridge;
class lan;
class message;
class bridge{
private:

public:
	string b_name;
	int b_id;

	vector<lan* > lans;
	vector<string> type_lans;
	int d;
	string root;
	string parent;
	string parent_lan;
	map<string,lan*> table;

	bridge();

	bridge(vector<lan *> vl, string , vector<string> tl);
	void update(message m,int& u);
	// void update_best(message m,int u);
	// void update_null(message m,int u);
	// void receive(message m,int u);


};

class lan{
private:
public:
	string l_name;

	vector<bridge* > bridges;

	lan();
	lan(string s, vector<bridge*> vb);
};

class message{
private:
public:
	string rootb;
	int dist;
	string senderb;
	string connectedl;

	message();
	message(string r, int d,string s,string l);

};