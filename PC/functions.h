#ifndef functions
#define functions

#include <iostream>
#include "ArduSerial/ArduSerial.h"
#include "ArduSerial/pch.h"

using namespace std;

string updateReceive (string &s)
{
	int pos = 0;
	for(; pos < s.size() and s[pos] != '#' ; pos++){}

	if(pos == s.size())
		return "";

	string ret = s.substr(0, pos);
	s = s.substr(pos+1);
	return ret;
}


void ipTest (bool feedback = true){
	char a[] = "cu000000#";

	if(!system("ping 192.168.1.103 -w 400 -n 1"))
		a[2] = '1';

	if(!system("ping moodle.uclv.edu.cu -w 1000 -n 1"))
		a[3] = '1';

	if(!system("ping cubadebate.cu -w 1000 -n 1"))
		a[4] = '1';

	if(!system("ping google.com -w 1000 -n 1"))
		a[5] = '1';

	if(!system("ping 192.168.1.102 -w 400 -n 1"))
		a[6] = '1';

	if(!system("ping 192.168.1.111 -w 400 -n 1"))
		a[7] = '1';

	if(feedback)
		cout << a << endl ;

	Serial3.print(a);
}

void volUpd ()
{
	int ret = system("SetVol report");
	string toSend = "vu";

	if(ret < 0)
	{
		ret *= -1;
		toSend += '-';
	}

	else
		toSend += '+';

	toSend += to_string(ret / 100);
	ret %= 100;
	toSend += to_string(ret / 10);
	ret %= 10;
	toSend += to_string(ret);
	toSend += '#';

	Serial3.print(toSend);
}

#endif //functions