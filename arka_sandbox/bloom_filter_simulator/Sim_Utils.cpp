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
	BloomFilter<std::string> filter((long)max_training_ruleset_size,"x86_32");
	//ERROR SECTION

	while (in_file.good()) {
		getline(in_file, line);
		//add_element into filter here
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

}
void evaluate_result_file(std::istream& in_file, std::ostream& out_file) {

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
