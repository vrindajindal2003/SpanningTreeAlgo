#include"bridge.h"
#include<bits/stdc++.h>
using namespace std;

void send_message(lan* l,string sender, string receiver,bridge* prev_bridge,int time,vector<string> &to_print);
string my_string(int time, string type, bridge* b, message m);