/*
 * BloomFilter.h
 *
 *  Created on: Jan 27, 2012
 *      Author: arka
 */

#ifndef BLOOMFILTER_H_
#define BLOOMFILTER_H_

#include <vector>
#include "MurmurHashFunctor.h"

#define SETBIT(bit_array,n) (bit_array[n]|=(1<<n))
#define GETBIT(bit_array,n) (bit_array[n]&=(1<<n))

template <class T> class BloomFilter {

private:

	const static short bit_array_size_multiplier=32;
	const static short number_of_hashes_per_element=22;

	std::vector<bool> bloom_filter_bit_vector;
	std::string architecture;

	MurmurHashFunctor<T> murmur_functor;

public:
	BloomFilter(long num_of_elements,std::string host_architecture);
	virtual ~BloomFilter();
	void add_element(T key);
	bool check_element(T key);
};

#endif /* BLOOMFILTER_H_ */
