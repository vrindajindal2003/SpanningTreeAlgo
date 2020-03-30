// #include"bridge.h"
#include"bridgesim.h"
#include<bits/stdc++.h>
using namespace std;

void send_message(lan* l, string sender, string receiver,bridge* prev_bridge,int time,vector<string> &to_print){
	// cout<<"lan:"<<l->l_name<<endl;
	auto bv=l->bridges;
	for(int i=0;i<bv.size();i++){
		auto current_bridge=bv[i];
		if(current_bridge==prev_bridge){
			continue;
		}

		// cout<<"current_bridge: "<<current_bridge->b_name<<endl;
		if(current_bridge->type_lans[(l->l_name)[0]-65]!="NP"){
			(current_bridge->table)[sender]=l;
				string s1=to_string(time)+" "+"r"+" "+current_bridge->b_name;
		to_print.push_back(s1);
			
			

			if((current_bridge->table).find(receiver)!=(current_bridge->table).end()){
				if((current_bridge->table)[receiver]!=l){
					string s2=to_string(time)+" s "+current_bridge->b_name;
					to_print.push_back(s2);
				send_message((current_bridge->table)[receiver],sender,receiver,current_bridge,time+1,to_print);
				
				}
			}
			else{
				for(int k=0;k<(current_bridge->lans).size();k++){
					auto current_lan=(current_bridge->lans)[k];
					if(current_bridge->type_lans[(current_lan->l_name)[0]-65]!="NP"){
						if(current_lan!=l){
								string s2=to_string(time)+" s "+current_bridge->b_name;
					to_print.push_back(s2);
						send_message(current_lan,sender,receiver,current_bridge,time+1,to_print);
						
						}
					}
				}
			}

			
		}
	}

}

string my_string(int time, string type, bridge* b, message m){
	string ans="";
	if(type=="s" && b->b_name!=m.senderb){
		
			return ans;}
		
		else{
			ans=to_string(time)+" "+type+" "+b->b_name+" ("+m.rootb+","+to_string(m.dist)+","+m.senderb+")";
			return ans;
		}
	}
