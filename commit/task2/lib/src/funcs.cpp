#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

void f1(string* str) {

	sort(str->begin(), str->end(), greater<int>());

	string new_str = "";

	for (int i = 0; i < str->length();) {
		if (((*str)[i] - '0') % 2 == 0) {
			str->replace(i, 1, "KB");
			i+=2;
		} else
			i++;
	}
}

int f2(string str){
	int sum = 0;
	for (int i = 0; i < str.length(); i++){
		if (str[i] >= '0' and str[i] <= '9'){
			sum += str[i] - '0';
		}
	}

	return sum;
}

string f3(string str) {
	if (str.length() > 2 and (stoi(str) % 32) == 0)
		return "истина";
	else
		return "ложь";
}