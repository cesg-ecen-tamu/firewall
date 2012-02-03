/*
 * MurmurHashFunctor.cpp
 *
 *  Created on: Jan 27, 2012
 *      Author: arka
 */

#include "MurmurHashFunctor.h"

template <class T> MurmurHashFunctor<T>::MurmurHashFunctor(std::string host_arch) {
	// TODO Auto-generated constructor stub
	architecture = host_arch;

}

template <class T> MurmurHashFunctor<T>::~MurmurHashFunctor() {
	// TODO Auto-generated destructor stub
}

template <class T> void MurmurHashFunctor<T>::operator ()(T key,int length,uint32_t seed,void* out){
	if(architecture=="x86_32")
		MurmurHash3_x86_32(key,length,seed,out);
	if(architecture=="x86_128")
			MurmurHash3_x86_128(key,length,seed,out);
	if(architecture=="x64_128")
			MurmurHash3_x64_128(key,length,seed,out);
	return;
}
