/*
 * MurmurHash_Functors.h
 *
 *  Created on: Jan 27, 2012
 *      Author: arka
 */

#ifndef MURMURHASH_FUNCTORS_H_
#define MURMURHASH_FUNCTORS_H_

template <class T> class MurMurHash_x86_32 {
public:
	MurMurHash_x86_32();
	virtual ~MurMurHash_x86_32();
	void operator()(T key);
};

class MurMurHash_x86_128 {
public:
	MurMurHash_x86_128();
	virtual ~MurMurHash_x86_128();
};

class MurMurHash_x64_128 {
public:
	MurMurHash_x64_128();
	virtual ~MurMurHash_x64_128();
};

#endif /* MURMURHASH_FUNCTORS_H_ */
