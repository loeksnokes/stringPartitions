/* 
 * File:   StringSet.h
 * Author: collin bleak
 *
 * This class enables one to represent a element in a partition of a global set of strings.  
 * We want these elements to be comparable for sorting as well.
 *
 *
 * Created on February 24, 2015, 4:47 PM
 */

#ifndef STRINGSET_H
#define	STRINGSET_H

#include<set>
#include<string>
#include<utility>
#include<iterator>

namespace cpb{
    class StringSet{
        
      public:
        const std::string & sortString() const{return this->_sortstring;}
        
        
        std::set<std::string> & sset(){return this->_stringSet;}
        std::set<std::string> const & cset() const {return this->_stringSet;}
        std::pair<std::set<std::string>::iterator,bool> insert (const std::string & val);
        
        void clear(){_stringSet.clear(); makeSortString();}
        
        
        size_t erase (const std::string & val);
        
        bool operator <(const StringSet &b) const{return this->_sortstring < b._sortstring;} 
        bool operator >(const StringSet &b) const{return this->_sortstring > b._sortstring;} 
        bool operator ==(const StringSet &b) const{return this->_sortstring == b._sortstring;}
        bool operator <=(const StringSet &b) const{return this->_sortstring <= b._sortstring;}
        bool operator >=(const StringSet &b) const{return this->_sortstring >= b._sortstring;}
        bool operator !=(const StringSet &b) const{return this->_sortstring != b._sortstring;}
      protected:
        void makeSortString();
      
      private:
        std::string _sortstring;
        std::set<std::string> _stringSet;
        
    };
}


#endif	/* STRINGSET_H */

