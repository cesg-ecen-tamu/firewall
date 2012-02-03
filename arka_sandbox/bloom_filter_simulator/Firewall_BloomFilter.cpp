//============================================================================
// Name        : Firewall_BloomFilter.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <iterator>
#include "Sim_Utils.h"
using namespace std;

int main() {
	ofstream testfile_out("testfile.dat"), resultfile_out("resultfile.dat"),
			evalfile_out("evalfile.dat");
	ifstream testfile_in("testfile.dat"), resultfile_in("resultfile.dat");

//	generate_test_file(testfile_out);
//	simulate_filter(testfile_in,resultfile_out);
//	evaluate_result_file(resultfile_in,evalfile_out);

	std::ostringstream s_str;
	std::vector<std::string> vec(10);
	for(int i=0;i<10;i++){
		s_str<<"hello"<<i<<endl;
		vec.push_back(s_str.str());
		s_str.str("");
	}
	copy(vec.begin(),vec.end(),ostream_iterator<string>(cout, "\n"));
	return 0;
}

