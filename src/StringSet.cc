#include<string>
#include<set>
#include<utility>
#include<iterator>
#include "StringSet.h"

using namespace cpb;

/***********************
 *lazy eval of _sortstring so only built when required, and only built once.
 */        
     
           std::pair<std::set<std::string>::iterator,bool> StringSet::insert (const std::string & val)
          {
               std::pair<std::set<std::string>::iterator,bool> retVal(_stringSet.insert(val));
            // CFR: update to sortstring done lazily before calls to comparisons
            // is much more efficient.  BUT, we need (???) comparison operators to 
            // be const.  everything should be automated to support tree operations.
            makeSortString();
                
                return retVal;
           }
               
       
        size_t StringSet::erase (const std::string & val)
        {
            
            size_t retVal(_stringSet.erase(val));
            
            // CFR: update to sortstring done lazily before calls to comparisons
            // is much more efficient.  BUT, we need (???) comparison operators to 
            // be const.  everything should be automated to support tree operations.
            makeSortString();
            return retVal;
        
        }
        
        void StringSet::makeSortString()
        {
           this->_sortstring="{";
           for(auto w:_stringSet)
           {
               _sortstring+=w;
              _sortstring+=".";
           }
           _sortstring=_sortstring.substr(0,_sortstring.length()-1);
_sortstring+="}";
           }
        