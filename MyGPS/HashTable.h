// Copyright 2018 Iuga Florin

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <iterator>
#include <list>
#include <string>
#define TRESHOLD 0.75

template <typename Tkey, typename Tvalue> struct elem_info {
	Tkey key;
	Tvalue value;
};
template <typename Tkey, typename Tvalue> class Hashtable {
 private:
    std::list<struct elem_info<Tkey, Tvalue> > * H;
	int HMAX = 10000;
    unsigned int (*hash)(Tkey);

 public:
    explicit Hashtable(unsigned int (*h)(Tkey)) {
        H = new std::list<struct elem_info<Tkey, Tvalue> > [HMAX];
		this->hash = h;
	}
    ~Hashtable() {
		delete[] H;
    }
    void put(Tkey key, Tvalue value) {
		int hkey = hash(key)%HMAX;
		struct elem_info<Tkey, Tvalue> info;
		typename std::list<struct elem_info<Tkey, Tvalue> >::iterator it;
		for (it = H[hkey].begin(); it != H[hkey].end(); ++it) {
			if (it->key == key) {
				it->value = value;
				return;
			}
		}
		// daca n-am gasit cheia,o  adaug in bucket
		info.key = key;
		info.value = value;
		H[hkey].push_back(info);
    }
    // intoarce valoarea asociata unei chei
	Tvalue get(Tkey key) {
		int hkey = hash(key)%HMAX;
		typename std::list<struct elem_info<Tkey, Tvalue> >::iterator it;
		for (it = H[hkey].begin(); it != H[hkey].end(); ++it) {
			if (it->key == key) {
				return it->value;
			}
		}
		return Tvalue();
    }
};
#endif  // HASHTABLE_H_
