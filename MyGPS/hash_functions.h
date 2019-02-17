// Copyright 2018 Iuga Florin

#ifndef HASH_FUNCTIONS_H_
#define HASH_FUNCTIONS_H_
#include <string>
// functie hash pentru int-uri
unsigned int hash_ints(unsigned int x) {
return (7927 * x) % 8387;
}
// functie hash pentru string-uri
unsigned int hash_strings(std::string key) {
	unsigned const int prime_nr = 0x811C9DC5;
    unsigned int hash = 0;
    unsigned int i = 0;
    for (int i = 0; i < key.length(); ++i)
	 {
		hash *= prime_nr;
		hash ^= (key[i]);
	 }
return hash;
}

#endif  // HASH_FUNCTIONS_H_
