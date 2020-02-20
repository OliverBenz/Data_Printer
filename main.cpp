#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

#include "lib/Date.hpp"
#include "lib/Time.hpp"
#include "lib/Print.hpp"

using namespace std;

// Formatting functions
Print getPrint(string line);
Time getTime(string t);
Date getDate(string d);

// Analytic functions
void mostPrints(vector<Print>& prints);

int main() {
	ifstream file("res/data.csv");

	vector<Print> prints;

	if (file.is_open()) {
		string line;
		while (getline(file, line))
			prints.push_back(getPrint(line));
	}
	else cout << "Could not open file" << endl;

	// if(!prints.empty()) cout << prints.back() << endl;

	cout << "Person with the most prints: ";
	mostPrints(prints);

	file.close();
	return 0;
}

void mostPrints(vector<Print>& prints) {
	map<string, int> userPrints;
	
	// Insert users and printCount to map
	for (auto& i : prints) {
		if (userPrints.find(i.getUser()) != userPrints.end())
			userPrints.find(i.getUser())->second += 1;
		else {
			userPrints.insert(make_pair(i.getUser(), 1));
		}
	}

	// Get pair with most prints from map
	pair<string, int> most = *userPrints.begin();
	for (auto& i : userPrints)
		if (i.second > most.second)
			most = i;

	cout << most.first << " - " << most.second << endl;
}


// Formatting functions
Print getPrint(string line) {
	stringstream ssLine(line);

	vector<string> values;
	string temp;
	while (getline(ssLine, temp, '@')) values.push_back(temp);

	// Replace ',' in float values with '.'
	for (size_t i = 13; i <= 15; i++) replace(values[i].begin(), values[i].end(), ',', '.');

	Print test(stoi(values[0]), stoi(values[1]), stoi(values[2]), stof(values[13]), stof(values[14]), stof(values[15]));
	test.setTime(getTime(values[12]), getTime(values[16]));
	test.setInfo(values[3], values[8], values[9], values[10], values[11]);
	test.setDate(getDate(values[4]), getDate(values[5]), getDate(values[6]), getDate(values[7]));

	return test;
};

Time getTime(string t) {
	if (t == "") return Time();
	Time time;

	string val = "";
	for (size_t i = 0; i < t.size(); i++) {
		if (t[i] == 'h') {
			time.hours = stoi(val);
			val = "";
		}
		else if (t[i] == 'm') {
			time.minutes = stoi(val);
		}
		else if (t[i] == 's') {
			time.seconds = stoi(val);
			break;
		}
		else val += t[i];
	}

	return time;
}

Date getDate(string d) {
	if(d == "") return Date();
	stringstream ss(d);
	
	vector<string> vals;
	string temp;
	while (getline(ss, temp, '.')) vals.push_back(temp);

	Date date(stoi(vals[0]), stoi(vals[1]), stoi(vals[2]));

	return date;
}