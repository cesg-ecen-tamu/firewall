/*
 * BloomFilter.cpp
 *
 *  Created on: Jan 27, 2012
 *      Author: arka
 */

#include "BloomFilter.h"

template<class T> BloomFilter<T>::BloomFilter(long num_of_elements,
		std::string host_architecture) :
		architecture(host_architecture) {
	// TODO Auto-generated constructor stub
	/* with most bloom filter implementations it is found that the minimum
	 * false positive rate is observed at m/n=32 and k=22, where m=size of
	 * bit array, n= number of elements to be hashed and k = number of hash
	 * functions. For now we will assume these values to be absolute and will
	 * hard-code these for the bloom filter calculations*/
	bloom_filter_bit_vector(num_of_elements * bit_array_size_multiplier);
	murmur_functor(host_architecture);

}

template<class T> void BloomFilter<T>::add_element(T key){
	void *hash1,*hash2;
	murmur_functor(key,sizeof(key),0l,hash1);
	murmur_functor(key,sizeof(key),hash1,hash2);
	for(int i=1;i<=number_of_hashes_per_element;i++){
		SETBIT(bloom_filter_bit_vector,((uint32_t)hash1+i*(uint32_t)hash2)%(bloom_filter_bit_vector.size()));
	}
}

template<class T> bool BloomFilter<T>::check_element(T key){
	void *hash1,*hash2;
	murmur_functor(key,sizeof(key),0l,hash1);
	murmur_functor(key,sizeof(key),hash1,hash2);
	for(int i=1;i<=number_of_hashes_per_element;i++){
		if(!GETBIT(bloom_filter_bit_vector,((uint32_t)hash1+i*(uint32_t)hash2)%(bloom_filter_bit_vector.size())))
			return false;
	}
	return true;
}

template <class T> BloomFilter<T>::~BloomFilter() {
	delete bloom_filter_bit_vector;
}

