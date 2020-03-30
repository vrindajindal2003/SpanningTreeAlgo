#include "bridge.h"
#include<bits/stdc++.h>
using namespace std;
// int convert_to_int(string s){
// 	stringstream abc(s.substr(1,s.size()-1));
// 	int ans;
// 	abc >> ans;
// 	return ans;
// }
bool bigger(string s1,string s2){
	stringstream one(s1.substr(1,s1.size()-1));
	stringstream two(s2.substr(1,s2.size()-1));
	int f;
	int s;
	one >> f;
	two >> s;
	return f > s;
}
bool equal_to(string s1,string s2){
	stringstream one(s1.substr(1,s1.size()-1));
	stringstream two(s2.substr(1,s2.size()-1));
	int f;
	int s;
	one >> f;
	two >> s;
	return f == s;
}
bridge::bridge(vector<lan *> vl, string s, vector<string> tl){
	b_name=s;
	// b_id=id;
	lans=vl;
	// vector<string> v(vl.size(), "DP");
	type_lans=tl;
	d=0;
	root=s;
	parent=s;
	parent_lan="";
}

void bridge::update(message m,int &u){
	// cout<<"u  "<<b_name<<endl;
	if(bigger(root,m.rootb)){//better rootm.rootb < root
		root=m.rootb;
		d=m.dist+1;
		parent=m.senderb;
		parent_lan=m.connectedl;
		for(int i=0;i<lans.size();i++){
			type_lans[(int)(lans[i]->l_name)[0]-65]="DP";
		}
		
		type_lans[(int)m.connectedl[0]-65]="RP";
		u++;
		return ;
	}
	else if(root==m.rootb){//equal root
		if((m.dist+1)<d){//better distance
			d=m.dist+1;
			parent=m.senderb;
			
			parent_lan=m.connectedl;
			for(int i=0;i<lans.size();i++){
			type_lans[(int)(lans[i]->l_name)[0]-65]="DP";
			}
			type_lans[(int)m.connectedl[0]-65]="RP";
			u++;
			return;
		}
		else if((m.dist+1)==d){//equal distance
		
			if(bigger(m.senderb,parent)){//bad sender  parent < m.senderb
				
				if(type_lans[(int)m.connectedl[0]-65]=="DP"){
					
				type_lans[(int)m.connectedl[0]-65]="NP";
				u++;
				return;
			}
		
			}
			else if(bigger(parent,m.senderb)){//better sender  parent > m.senderb
				parent=m.senderb;

				
				type_lans[(int)parent_lan[0]-65]="NP";
					type_lans[(int)m.connectedl[0]-65]="RP";
				
				parent_lan=m.connectedl;


				// cout<<"old best null"<<" "<<b_name<<endl;
				u++;
				return ;
			}
			else if(parent==m.senderb){//parent==m.senderb
				// cout<<"parent==senderb"<<endl;
				if(m.connectedl<parent_lan){
					// cout<<"+++++++++"<<endl;
					type_lans[(int)parent_lan[0]-65]="NP";
					type_lans[(int)m.connectedl[0]-65]="RP";
					parent_lan=m.connectedl;
					u++;
					return;

				}
				else if(m.connectedl>parent_lan){
					// cout<<"*************"<<endl;
					if(type_lans[(int)m.connectedl[0]-65]!="NP"){
						type_lans[(int)m.connectedl[0]-65]="NP";
						u++;
						return;
					}
				}
			}
		}
		else if(m.dist==d){
			if(bigger(b_name,m.senderb)){//m.senderb<b_name
				if(type_lans[m.connectedl[0]-65]=="DP"){
					type_lans[m.connectedl[0]-65]="NP";
				u++;
				return;}
			}
		}
	}
	return;
}





lan::lan(string s, vector<bridge*> vb){
	l_name=s;
	bridges=vb;
}

message::message(string r, int d, string s, string l){
	rootb=r;
	dist=d;
	senderb=s;
	connectedl=l;
}