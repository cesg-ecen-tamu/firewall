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

template<class T> class BloomFilter {

private:

	const static short bit_array_size_multiplier = 32;
	const static short number_of_hashes_per_element = 22;

	std::string architecture;
	std::vector<bool> bloom_filter_bit_vector;

	MurmurHashFunctor<T> murmur_functor;

public:
	BloomFilter(long num_of_elements, std::string host_architecture) :
			architecture(host_architecture), bloom_filter_bit_vector(
					num_of_elements * bit_array_size_multiplier), murmur_functor(
					host_architecture) {
		/* with most bloom filter implementations it is found that the minimum
		 * false positive rate is observed at m/n=32 and k=22, where m=size of
		 * bit array, n= number of elements to be hashed and k = number of hash
		 * functions. For now we will assume these values to be absolute and will
		 * hard-code these for the bloom filter calculations*/
//		bloom_filter_bit_vector = new std::vector<bool>(
//				num_of_elements * bit_array_size_multiplier, false);
//		murmur_functor = new MurmurHashFunctor<T>(host_architecture);
	}
	~BloomFilter() {
		delete &bloom_filter_bit_vector;
		//delete
	}
	void add_element(T key) {
		void *hash1, *hash2;
		murmur_functor(key, sizeof(key), 0l, hash1);
		murmur_functor(key, sizeof(key), (long)hash1, hash2);
		for (int i = 1; i <= number_of_hashes_per_element; i++) {
			SETBIT(
					bloom_filter_bit_vector,
					((uint32_t)hash1+i*(uint32_t)hash2)%(bloom_filter_bit_vector.size()));
		}
	}
	bool check_element(T key) {
		void *hash1, *hash2;
		murmur_functor(key, sizeof(key), 0l, hash1);
		murmur_functor(key, sizeof(key), (long)hash1, hash2);
		for (int i = 1; i <= number_of_hashes_per_element; i++) {
			if (!GETBIT(bloom_filter_bit_vector,((uint32_t)hash1+i*(uint32_t)hash2)%(bloom_filter_bit_vector.size())))
				return false;
		}
		return true;
	}

	void clear() {
		bloom_filter_bit_vector.clear();
	}
};

#endif /* BLOOMFILTER_H_ */
