/*
 * MurmurHashFunctor.h
 *
 *  Created on: Jan 27, 2012
 *      Author: arka
 */

#ifndef MURMURHASHFUNCTOR_H_
#define MURMURHASHFUNCTOR_H_

#include <string>
#include <stdint.h>				//<cstdint> not working for std::uint32_t
#include "murmur3.h"

template<class T> class MurmurHashFunctor {

private:
	std::string architecture;
public:
	MurmurHashFunctor(std::string host_arch) {
		architecture = host_arch;
	}
	~MurmurHashFunctor(){};
	void operator ()(T key,int length,uint32_t seed,void* out){
		if(architecture=="x86_32")
			MurmurHash3_x86_32(key,length,seed,out);
		if(architecture=="x86_128")
				MurmurHash3_x86_128(key,length,seed,out);
		if(architecture=="x64_128")
				MurmurHash3_x64_128(key,length,seed,out);
		return;
	}


};

#endif /* MURMURHASHFUNCTOR_H_ */
