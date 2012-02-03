/*
 * Sim_Utils.cpp
 *
 *  Created on: Feb 1, 2012
 *      Author: arka
 */

#include "Sim_Utils.h"

void generate_test_file(std::ostream& out_file) {

	std::vector<bool> ipchecker_src(sizeof(uint32_t)), ipchecker_dest(
			sizeof(uint32_t));
	uint32_t generated_src_ip, generated_dest_ip;
	int count = 0;
	std::vector<std::string> ruleset_vector(max_training_ruleset_size);
	std::map<uint32_t, bool> ip_map;
	std::ostringstream rule_stream;

	srand(time(NULL));
	while (count < max_training_ruleset_size) {
		generated_src_ip = generate_random_ip();
		generated_dest_ip = generate_random_ip();
		if (ip_map[generated_src_ip] && ip_map[generated_dest_ip])
			continue;
		else {
			count++;
			ip_map.insert(std::pair<uint32_t, bool>(generated_src_ip, true));
			ip_map.insert(std::pair<uint32_t, bool>(generated_dest_ip, true));

			//can randomize ports too

			rule_stream << "" << generated_src_ip << "\t" << 8080 << "\t"
					<< generated_dest_ip << "\t" << 9080 << "accept\n";
			ruleset_vector.push_back(rule_stream.str());
			rule_stream.str("");
		}
	}
	copy(ruleset_vector.begin(), ruleset_vector.end(),
			std::ostream_iterator<std::string>(out_file));
	((std::ofstream&) out_file).close();
	ruleset_vector.clear();
}

void simulate_filter(std::istream& in_file, std::ostream& out_file) {

	std::string line;
	std::vector<std::string> input_rules_vector(max_training_ruleset_size);
	std::vector<std::string> test_rules_vector(max_test_ruleset_size);
	uint32_t generated_src_ip, generated_dest_ip;
	int count = 0;
	std::ostringstream rule_stream;
	std::vector<std::string>::iterator it;

	//ERROR SECTION
	BloomFilter<std::string> filter((long) max_training_ruleset_size, "x86_32");
	//ERROR SECTION

	while (in_file.good()) {
		getline(in_file, line);
		filter.add_element(line);
	}

	srand(time(NULL));
	while (count < max_test_ruleset_size) {
		generated_src_ip = generate_random_ip();
		generated_dest_ip = generate_random_ip();

		//can randomize ports too

		rule_stream << "" << generated_src_ip << "\t" << 8080 << "\t"
				<< generated_dest_ip << "\t" << 9080 << "accept\n";
		test_rules_vector.push_back(rule_stream.str());
		rule_stream.str("");
	}
	out_file << "Rule" << " " * 40 << "Match\n\n";
	for (it = test_rules_vector.begin(); it < test_rules_vector.end(); it++) {
		rule_stream << (*it);
		if (filter.check_element(*it))
			rule_stream << "\t" << 1 << "\n";
		else
			rule_stream << "\t" << 0 << "\n";

		out_file << rule_stream.str();
		rule_stream.str("");
	}
	((std::ofstream&) in_file).close();
	((std::ofstream&) out_file).close();
	test_rules_vector.clear();
	filter.clear();
}
void evaluate_result_file(std::istream& ruleset_file, std::istream& in_file,
		std::ostream& out_file) {
	std::map<std::string, bool> ip_map;
	std::string line;
	std::ostringstream rule_stream;
	std::string rule_string;
	int result;
	int count=0;
	while (ruleset_file.good()) {
		getline(ruleset_file, line);
		ip_map.insert(std::pair<std::string, bool>(line, true));
	}
	out_file<<"Rule"<<" "*40<<"Match"<<"\t"<<"FPos\n\n";
	while (in_file.good()) {

		/* ignore the file header */
		while(count<3){
			count++;
			getline(in_file, line);
			continue;
		}
		/* ignore the file header */
		getline(in_file, line);
		rule_string = line.substr(0,line.find_last_of('\t'));
		result = atoi((line.substr(line.find_last_of('\t'),1)).c_str());

		if(ip_map[rule_string] && result)
			rule_stream<<rule_string<<"\t"<<result<<"\t"<<MATCH<<"\n";
		else if(!ip_map[rule_string] && result)
			rule_stream<<rule_string<<"\t"<<result<<"\t"<<FALSE_POS<<"\n";
		else if(ip_map[rule_string] && !result)
			rule_stream<<rule_string<<"\t"<<result<<"\t"<<FALSE_NEG<<"\n";
		else
			rule_stream<<rule_string<<"\t"<<result<<"\t"<<MATCH<<"\n";

		out_file<<rule_stream.str();
		rule_stream.str("");
	}
	((std::ifstream&) ruleset_file).close();
	((std::ifstream&) in_file).close();
	((std::ofstream&) out_file).close();

}

uint32_t generate_random_ip() {

	uint32_t generated_ip;
	uint8_t ip_1 = rand() % 256;
	uint8_t ip_2 = rand() % 256;
	uint8_t ip_3 = rand() % 256;
	uint8_t ip_4 = rand() % 256;

	generated_ip = (ip_1 << 24) | (ip_2 << 16) | (ip_3 << 8) | (ip_4);
	return generated_ip;
}
