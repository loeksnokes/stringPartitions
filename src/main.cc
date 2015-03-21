/* 
 * File:   main.cc
 * Author: Collin Bleak
 *
 * Created on February 23, 2015, 10:23 AM
 */

#include <cstdlib>
#include<iostream>
#include<string>
#include<set>
#include<boost/lexical_cast.hpp>
#include"const.h"
#include"StringSet.h"
#include"StringPartitionSet.h"
//#include "Enumerator.h"

using namespace cpb;

/*
 * 
 */
int main(int argc, char** argv)
{
    unsigned int alphabetSize, length;
    if (argc != 3)
    {
        std::cerr << "Usage `.\\string_partitions s n' where 0<s<10 is size of alphabet, 0<=n is length of strings." << std::endl;
        return cpb::FAIL;
    }
    try
    {
        alphabetSize = boost::lexical_cast<unsigned int>(argv[1]);
        length = boost::lexical_cast<unsigned int>(argv[2]);
    } catch (boost::bad_lexical_cast e)
    {
        std::cerr << "Usage `.\\enumerator s n' where 0<s<10 is size of alphabet, 0<=n is length of strings." << std::endl;
        return cpb::FAIL;
    }
    if (alphabetSize < 1 || alphabetSize > 9 || length<0)
    {
        std::cerr << "Usage `.\\string_partitions s n' where 0<s<10 is size of alphabet, 0<=n is length of strings." << std::endl;
        return cpb::FAIL;
    }

    //create initial partition which is discrete
    StringPartitionSet baseSPS(alphabetSize, length);

//Make all pairs of distinct words.
    std::set<StringSet> pairs;
  for (auto wordOne : baseSPS.strings().cset())
    {
        for (auto wordTwo : baseSPS.strings().cset())
        {
            if (wordOne < wordTwo)
            {
                StringSet pairString;
                pairString.insert(wordOne);
                pairString.insert(wordTwo);
                pairs.insert(pairString);
            }
        }
    }
    
    for(auto pair: pairs)
    {std::cout<<pair.sortString()<<" ";}
    std::cout<<std::endl;

    std::set<StringPartitionSet> partitions;
       partitions.insert(baseSPS);
       

    std::set<StringPartitionSet> workingPartitions;
    workingPartitions = partitions;

    std::cout<<baseSPS.sortString()<<std::endl;
    
    for (auto pair : pairs)
    {
        for (auto sps : partitions)
        {
            sps.glueSetsByWords(pair);
            if(workingPartitions.end()==workingPartitions.find(sps))
            {
                workingPartitions.insert(sps);
                std::cout<<sps.sortString()<<std::endl;
            }
            
        }
        partitions.clear();
        partitions=workingPartitions;
    }
    
    std::cout<< "There are "<< partitions.size() << " valid foldings of DB("<<alphabetSize<<", "<<length<<")."<<std::endl;
    return cpb::SUCCESS;
}

