#ifndef HASH_TABLE
#define HASH_TABLE

#include <vector>
#include <list>
#include <iterator>
#include "HashFunction.h"


using std::list;
using std::vector;
using std::pair;


template <typename KEY, typename VAL, typename HASHFUNC = HashFunction<KEY>>
class HashTable
{
    vector<list<pair<KEY, VAL>>> data;    
    
    unsigned max_hash = 1000;
    unsigned _size;
    double fillCoef = 3;

    HASHFUNC hash;

    class Iterator : std::iterator<std::forward_iterator_tag, pair<KEY, VAL>>
    {
        std::vector<list<pair<KEY, VAL>>> * vec;
        int vector_index, list_index;


        void findNext() {
            ++vector_index;
            auto v_it = vec->begin() + vector_index;
            for (; v_it != vec->end(); ++v_it, ++vector_index) {
                if (!v_it->empty()) break;
            }

            if (v_it == vec->end()) vector_index = -1;

            list_index = 0;
        }

        pair<KEY, VAL>& getIterator() {
            auto it = vec->at(vector_index).begin();
            auto li = list_index;
            while (li--) ++it;

            return *it;
        }

    public:
        
        Iterator(std::vector<list<pair<KEY, VAL>>> * vec_ptr) : vec(vec_ptr), vector_index(0), list_index(0) {
            auto v_it = vec->begin();
            for (; v_it != vec->end(); ++v_it, ++vector_index) {
                if (!v_it->empty()) break;
            }

            if (v_it == vec->end()) vector_index = -1;
        }

        Iterator(std::vector<list<pair<KEY, VAL>>> * vec_ptr, std::string) : vec(vec_ptr), vector_index(-1) {
            //auto it = vec->rbegin();
            //vector_index = vec->size();

            //for (; it != vec->rend(); ++it, --vector_index) {
            //    if (!it->empty()) {
            //        auto list_it = it->begin();
            //        list_index = 0;
            //        while (++list_it != it->end()) list_index++;
            //        break;
            //    }
            //}
        }

        pair<KEY, VAL>& operator*() {            

            return getIterator();
        }

        pair<KEY, VAL>* operator->() {

            return &getIterator();
        }

        Iterator& operator++() {
            auto it = vec->at(vector_index).begin();

            if (it == vec->at(vector_index).end()) {
                findNext();
                return *this;
            }

            int li = ++list_index;

            while (li--) {
                ++it;
                if (it == vec->at(vector_index).end()) {
                    findNext();
                    return *this;
                }
            }

            return *this;
        }

        Iterator operator++(int) {
            auto tmp = *this;
            auto it = vec->at(vector_index).begin();

            if (it == vec->at(vector_index).end()) {
                findNext();

                return tmp;
            }

            int li = list_index;
            ++list_index;
            
            while (--li) {
                ++it;

                if (it == vec->at(vector_index).end()) {
                    findNext();
                    return tmp;
                }
            }

            return tmp;
        }

        bool operator==(const Iterator& it) {
            return (this->vector_index == it.vector_index) && (this->list_index == it.list_index);
        }

        bool operator!=(const Iterator& it) {
            return !(*this == it);
        }
        
    };


    void rehash() {
        auto prevTable = *this;
        this->clear();
        this->max_hash *= 2;
        this->data.resize(max_hash);

        for (auto it : prevTable) {
            this->put(it.first, it.second);
        }
    }

public:
    HashTable() : _size(0) {
        data.resize(max_hash);
    }

    Iterator begin() {        
        return Iterator(&data);
    }

    Iterator end() {
        return Iterator(&data, "end");
    }

    void put(const KEY & key, const VAL & val) {
        if (_size / double(max_hash) > fillCoef) rehash();

        unsigned i = hash(key) % max_hash;

        for (auto & pair : data[i]) {
            if (pair.first == key) {
                pair.second = val;
                return;
            }
        }

        data[i].push_back(make_pair(key, val));
        _size++;        
    }

    bool get(const KEY & key, VAL & val) const {
        unsigned i = hash(key) % max_hash;

        for (auto & pair : data[i]) {
            if (pair.first == key) {
                val = pair.second;
                return true;
            }
        }

        return false;
    }

    bool remove(const KEY & key) {
        unsigned i = hash(key) % max_hash;

        for (auto it = data[i].begin(); it != data[i].end(); ++it) {
            if (it->first == key) {
                data[i].erase(it);
                _size--;
                return true;
            }
        }
        
        return false;
    }

    VAL & operator[](const KEY & key) {
        if (_size / double(max_hash) > fillCoef) rehash();

        unsigned i = hash(key) % max_hash;

        for (auto & pair : data[i]) {
            if (pair.first == key) {
                return pair.second;
            }
        }

        data[i].push_back(make_pair(key, VAL{}));
        _size++;        

        return data[i].back().second;
    }

    bool find(const KEY & key) {
        unsigned i = hash(key) % max_hash;

        for (auto & pair : data[i]) {
            if (pair.first == key) {
                return true;
            }
        }

        return false;
    }

    void clear() {
        for (auto & vec_it : data) {
            vec_it.clear();
        }
        _size = 0;
    }

    unsigned size() { return _size; }

    ~HashTable() {};
};



#endif