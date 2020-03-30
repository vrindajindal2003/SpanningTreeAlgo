#include<bits/stdc++.h>
// #include "bridge.h"
#include "bridgesim.h"
using namespace std;

// vector<messsge> to_receive;
vector<string> my_split(string s){
	bool b=1;
	string word="";
	vector<string> ans;
	for(int i=0;i<s.size();i++){
		if(s[i]!=' '){
			word=word+s[i];
		}
		else{
			if(b){
				word.pop_back();
				ans.push_back(word);
				b=0;
				word="";
			}
			else{
				ans.push_back(word);
				word="";
			}
		}
	}
	if(b){
		word.pop_back();
		ans.push_back(word);
		b=0;
		word="";
	}
	else{
		ans.push_back(word);
		word="";
	}
	return ans;
}

vector<string> my_split2(string s){
	string word="";
	vector<string> ans;
	for(int i=0;i<s.size();i++){
		if(s[i]!=' '){
			word=word+s[i];
			// cout<<word<<endl;
		}
		else{
			ans.push_back(word);
			word="";
		}

	}
	ans.push_back(word);
	return ans;
}




int main(){
	// cout<<"!!!!!!!1"<<endl;

	int trace;
	cin>>trace;
	int num_bridges;
	cin>>num_bridges;
	vector<bridge* > all_bridges;
	vector<bool> lan_present(26,false);
	vector<lan* > all_lans;
	vector<lan* > alphabetic_lans(26);
	int num_lans=0;

	for(int i=0;i<=num_bridges;i++){
		string s;
		getline(cin,s);
		if(i==0){
			continue;
		}
		vector<string> words=my_split(s);
		string bridge_name=words[0];
		// cout<<bridge_name<<endl;
		vector<lan*> vl;
		vector<string> tl(26,"");
		// vector<string> tl;
		
		for(int j=1;j<words.size();j++){
			// cout<<"!!!!!"<<endl;
			// cout<<j<<endl;
			// cout<<words[j]<<endl;
			// cout<<(int)words[j][0]-65<<endl;
			if(lan_present[(int)words[j][0]-65]==0){
				num_lans++;
				// cout<<words[i][0]<<" not present"<<endl;
				lan_present[(int)words[j][0]-65]=1;
				vector<bridge*> b;
				lan* l=new lan(words[j],b);
				alphabetic_lans[(int)words[j][0]-65]=l;
			}
			// cout<<"......"<<endl;

			vl.push_back(alphabetic_lans[(int)words[j][0]-65]);
			tl[(int)words[j][0]-65]="DP";
			// cout<<vl.size()<<"qqq"<<endl;

			// tl.push_back("DP");
		}
		bridge* b=new bridge(vl,bridge_name,tl);

		// cout<<b->b_name<<" made"<<endl;
		for(int j=0;j<words.size()-1;j++){
			((b->lans)[j])->bridges.push_back(b);
		}
		all_bridges.push_back(b);
		// cout<<"for"<<endl;
	}



	vector<message> to_receive;

	int time=0;


	while(true){
		// cout<<"----------------------------------"<<p<<endl;
		int num_updates=0;
		vector<string> to_print;


		for(int i=0;i<to_receive.size();i++){

			message m=to_receive[i];
			string cln=m.connectedl;//connected lan name
			// cout<<"r"<<" "<<m.senderb<<endl;
			auto connected_bv=(alphabetic_lans[(int)cln[0]-65])->bridges;//vector of pointer to bridges that are connected to that lan
			string s=m.senderb;

			for(int j=0;j<connected_bv.size();j++){
				// cout<<"receive"<<" "<<connected_bv[j]->b_name<<endl;
				if((connected_bv[j])->b_name == s){
					// cout<<"XXXXXXX"<<endl;
					continue;
				}
				// cout<<"sender:"<<m.senderb<<" distance:"<<m.dist<<" receive:"<<connected_bv[j]->b_name<<" lanreceived"<<m.connectedl<<" currentlan :"<<connected_bv[j]->parent_lan<<endl;

				connected_bv[j]->update(m,num_updates);
				string pr=my_string(time, "r",connected_bv[j],m);
				to_print.push_back(pr);
				// to_print.push_back(make_pair(time,make_pair(connected_bv[i],m)));

			}
		}

		vector<message> to_send;

		for(int i=0;i<all_bridges.size();i++){
			auto b=all_bridges[i];//pointer to bridge
			auto cl=b->lans;//vector of pointer to lans connected to that bridge
			for(int j=0;j<cl.size();j++){
				if(!(b->type_lans[(int)(cl[j]->l_name)[0]-65]=="DP")){
					continue;
				}
				// cout<<"S "<<b->b_name<<endl;
				message m(b->root,b->d,b->b_name,cl[j]->l_name);
				to_send.push_back(m);
				string prt=my_string(time,"s",b,m);
				if(prt!=""){
				to_print.push_back(prt);
			}}
		}
		if(trace==1){
			sort(to_print.begin(),to_print.end());
			for(int w=0;w<to_print.size();w++){
				cout<<to_print[w]<<endl;
			}
		}
		// cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	
		to_receive=to_send;
		if(num_updates==0 && time!=0){
			// cout<<"BB"<<endl;
			break;
		}
		time++;
	}

	for(int i=0;i<all_bridges.size();i++){
		auto b=all_bridges[i];
		auto cl=b->lans;
		cout<<b->b_name<<":";
		for(int j=0;j<26;j++){
			if(b->type_lans[j]!=""){
				char c=j+65;
				cout<<" "<<c<<"-"<<b->type_lans[j];
							}}
							cout<<endl;}
		// }
		// for(int j=0;j<cl.size();j++){
		// 	cout<<cl[j]->l_name<<"-";
		// 	cout<<(b->type_lans)[(cl[j]->l_name)[0]-65]<<" ";

		// }
		// cout<<endl;
	
	map<string,lan*> hosts;
	for(int i=0;i<num_lans;i++){
		// cout<<"!!!!!!!!!!"<<endl;
		string s;
		getline(cin,s);
		// cout<<s<<endl;
		// if(i==0){
		// 	continue;
		// }
		vector<string> words;
		words=my_split(s);
		// cout<<words[0]<<endl;
		for(int j=1;j<words.size();j++){
			// cout<<words[j]<<endl;
			hosts[words[j]]=alphabetic_lans[(int)words[0][0]-65];
			// hosts.insert(words[j],alphabetic_lans[(int)words[0][0]-65]);
		}
	}

	int num_messages;
	cin>>num_messages;
	for(int z=0;z<num_messages+1;z++){
		// cout<<"########"<<endl;
		string s;
		getline(cin,s);
		// cout<<s<<endl;
		if(z==0){
			// cout<<"^^^^^^^^^^^"<<endl;
			continue;
		}
		// cout<<s<<endl;
		// cout<<"~~~~~~~~~~~"<<endl;
		vector<string> w=my_split2(s);
		string sender=w[0];
		// cout<<sender<<endl;
		string receiver=w[1];
		// cout<<receiver<<endl;
		vector<string> printer;
		send_message(hosts[sender],sender,receiver,NULL,0,printer);
		// if(z!=1){
		// 	cout<<endl;
		// 	// cout<<endl;
		// }
		for(int j=0;j<all_bridges.size();j++){
			// if(z!=1){
			// if( j==0){
			// 	if(z!=0)
			// 	cout<<endl;
			// }
			// if(!(z==1 and j==0))

			// cout<<endl;
			
			cout<<all_bridges[j]->b_name<<":"<<endl;
			cout<<"HOST ID | FORWARDING PORT"<<endl;
			map<string,lan*> :: iterator iter;
			map<int,string> printing;
			for(iter=(all_bridges[j]->table).begin();iter!=(all_bridges[j]->table).end();iter++){
				string name=iter->first;
				stringstream abc(name.substr(1,name.size()-1));
				int x;
				abc >> x;
				printing[x]=(iter->second)->l_name;

				// cout<<iter->first<<" | "<<(iter->second)->l_name<<endl;
			}
			map<int,string> :: iterator itr;
			for(itr=printing.begin();itr!=printing.end();itr++){
				cout<<"H"<<itr->first<<" | "<<itr->second<<endl;

			}
			// cout<<endl;
		}

		// cout<<endl;
		// if(z!=num_messages+1 ){
		// cout<<endl;}
		if(trace==1){
			sort(printer.begin(),printer.end());
			for(int l=0;l<printer.size();l++){
				cout<<printer[l]+" "+hosts[sender]->l_name+"-->"+hosts[receiver]->l_name<<endl;
			}
		}
		cout<<endl;
	}





	}

