/* 
 * File:   partitionSet.h
 * Author: collin
 *
 * Created on February 23, 2015, 2:03 PM
 */
#ifndef STRINGPARTITIONSET_H
#define	STRINGPARTITIONSET_H

#include<string>
#include<set>
#include"StringSet.h"

using namespace cpb;


class StringPartitionSet
{
    
    public:
      // Makes discrete partition from a set of strings
      StringPartitionSet(const StringSet & theseStrings);
      
      // makes a discrete partition for all words from an alphabet of size 
      // numLetters < 10 (1-9) and lengths less than length
      StringPartitionSet(unsigned int numLetters, unsigned int length);
      
      // makes a new StringPartitionSet from an old, together with two words that are to be forced into same equivalence class.
      StringPartitionSet(const StringPartitionSet & theseStrings,const std::string & firstString, const std::string & secondString);
      
      
              
        std::set<StringSet> & sset(){return this->_partition;}
        std::set<StringSet> const & cset() const {return this->_partition;}
      
      const std::string & sortString() const{return this->_sortstring;}
      const StringSet & strings()const{return this->_strings;}
      const StringSet & letters()const{return this->_letters;}
      
      // Modifies this StringPartitionSet with suggested gluing, and all forced consequences.
      int glueTwoSetsNoForce(const StringSet & oneSet,const StringSet & otherSet, StringSet & resultSet);

      int glueSetsByWords(const StringSet & words);
      int glueSetOfSets(const std::set<StringSet> & theseSets);
      
      const std::set<StringSet> & partition() {return this->_partition;}
      
        bool operator <(const StringPartitionSet &b) const{return this->_sortstring < b._sortstring;} 
        bool operator >(const StringPartitionSet &b) const{return this->_sortstring > b._sortstring;} 
        bool operator ==(const StringPartitionSet &b) const{return this->_sortstring == b._sortstring;}
        bool operator <=(const StringPartitionSet &b) const{return this->_sortstring <= b._sortstring;}
        bool operator >=(const StringPartitionSet &b) const{return this->_sortstring >= b._sortstring;}
        bool operator !=(const StringPartitionSet &b) const{return this->_sortstring != b._sortstring;}

        
        
    protected:
      // returns pointer to partition element with the given word in it.  NULL return if not found.
      int setWithWord(const std::string & word, StringSet & answerSet);
      
      //build De Bruijn Roll of a set for new letter `letter'
      int roll(std::string letter, const StringSet & setToRoll, StringSet & rollSet);

      StringSet lettersInWord(const std::string & word);
      StringSet lettersInWords(const StringSet & words);
      int force();
      
      void makeSortString();
      
  private:
      std::set<StringSet> _partition;
      std::set<StringSet> _forceQueue;
      StringSet _letters;
      StringSet _strings;
      std::string _sortstring;
          
};//EOStringPartitionSet

#endif	/* STRINGPARTITIONSET_H */

