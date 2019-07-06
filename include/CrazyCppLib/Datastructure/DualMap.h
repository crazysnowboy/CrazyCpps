//
// Created by collin on 18-2-8.
//

#ifndef CRAZY_DUALMAP_H
#define CRAZY_DUALMAP_H

#include <map>
template<typename K, typename V>
using MapIterator = typename std::map<K,V>::const_iterator;


template <typename First,typename Sencod>
class DualMap
{
public:

    bool Insert(First key,Sencod value)
    {
        ForwardMap.insert(std::make_pair(key,value));
        BackwardMap.insert(std::make_pair(value,key));
        return true;
    }
    First Get(Sencod key)
    {
        return BackwardMap[key];
    }
    Sencod Get(First key)
    {
        return ForwardMap[key];
    }
    bool clear()
    {
        ForwardMap.clear();
        BackwardMap.clear();
    }
    MapIterator<First,Sencod> Begin()
    {
        return ForwardMap.begin();
    };

    MapIterator<First,Sencod> End()
    {
        return ForwardMap.end();
    };

private:
    std::map <First,Sencod>  ForwardMap;
    std::map <Sencod,First>  BackwardMap;

};


#endif //CRAZY_DUALMAP_H
