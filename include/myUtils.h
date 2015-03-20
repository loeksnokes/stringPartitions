/* 
 * File:   myUtils.h
 * Author: collin
 *
 * Created on February 23, 2015, 2:59 PM
 */
#ifndef MYUTILS_H
#define	MYUTILS_H

#include<string>
#include<sstream>
#include<set>
#include"StringSet.h"
#include"const.h"

namespace cpb{
    
//#define  bforeach  BOOST_FOREACH
//#define  brforeach  BOOST_REVERSE_FOREACH
    

template <typename T> std::string toString(T input)
{
    std::string result;
    std::stringstream ss;
        ss<<input;
        ss>>result;
        return result;
}

// get first element from a set of type T, remove element from set.
template<typename T> int setPop(std::set<T> & thisSet, T & answer)
{
    if(0==thisSet.size())
    {return FAIL;}
    
    answer = *(thisSet.begin());
    
    thisSet.erase(answer);
    return 0;
}

bool AinB(cpb::StringSet A,cpb::StringSet B)
{
    bool retVal=true;
    std::set<std::string> const & Aset(A.sset()),Bset(B.sset());
    auto sitE=Bset.end();
    
    for(auto  w: Aset)
    {
        if(sitE==Bset.find(w))
        {retVal=false;break;}
    }
    return retVal;
}

}


#endif	/* MYUTILS_H */

