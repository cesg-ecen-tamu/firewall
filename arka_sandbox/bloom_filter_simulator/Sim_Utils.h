/*
 * Sim_Utils.h
 *
 *  Created on: Feb 1, 2012
 *      Author: arka
 */

#ifndef SIM_UTILS_H_
#define SIM_UTILS_H_

#include <fstream>
#include <stdint.h>		//<cstdint> not working for std::uint32_t
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <sstream>
#include <iterator>

#include "BloomFilter.h"


	/*enum{OFF,ON};
	static int ip_match_filter_size = 256;
	std::vector<bool> ip_match_bit_array(ip_match_filter_size);*/
	static int max_training_ruleset_size = 3000;
	static int max_test_ruleset_size = 10000;

	void generate_test_file(std::ostream& out_file);
	void simulate_filter(std::istream& in_file, std::ostream& out_file);
	void evaluate_result_file(std::istream& in_file, std::ostream& out_file);
	uint32_t generate_random_ip();

#endif /* SIM_UTILS_H_ */
