/***************************************************      
 *     Author: C. Bleak 23.02.2015
 *     .cc file realising functionality of class StringPartitionSet.
 * 
 *      Member Data for StringPartitionSet:
 * 
 *
 *    std::set<StringSet> _partition;
 *    std::set<StringSet> _forceQueue;
 *    StringSet _letters;
 *    StringSet _strings;
 *    std::string _sortstring;
 *      std::set<StringSet > thisPartition
 *      StringSet letters;
 */

#include<sstream>
#include<iostream>
#include<boost/lexical_cast.hpp>

#include"StringPartitionSet.h"
#include"myUtils.h"
#include"const.h"


using namespace cpb;
extern const int cpb::FAIL;
extern const int cpb::SUCCESS;

/***************************************************
 * C'tor:  Receives set of words.
 * 
 * Given a set of words.  Creates the discrete partition and learns the alphabet
 * Note:  Assumes each alphabet chars are length one in original words.
 */
StringPartitionSet::StringPartitionSet(const StringSet & theseStrings)
{
    //create discrete partition.
    for (auto word : theseStrings.cset())
    {
        StringSet thisSet;
        thisSet.insert(word);
        this->_partition.insert(thisSet);
        this->_strings.insert(word);
    }
    this->_letters = lettersInWords(theseStrings);
}

/***************************************************
 * C'tor:  Receives set of words.
 * 
 * makes a discrete partition for all words from an alphabet of size 
 * numLetters < 10 (1-9) and lengths less than length
 */
StringPartitionSet::StringPartitionSet(unsigned int numLetters, unsigned int length)
{
    std::stringstream ss;
    std::string letter;
    for (int ll = 0; ll < numLetters; ++ll)
    {

        _letters.insert(toString<int>(ll));
        letter = "";
    }
    std::cout << "Alphabet is ";
    for (auto c : _letters.cset())
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    StringSet shortWords, longWords;
    shortWords.insert("");
    while (length > 0)
    {
        for (auto word : shortWords.cset())
        {
            for (auto letter : _letters.cset())
            {
                std::string result(word + letter);
                longWords.insert(result);
            }
        }
        shortWords.sset().clear();
        for (auto word : longWords.cset())
        {
            shortWords.insert(word);
        }
        longWords.sset().clear();
        --length;
    }

    //create discrete partition.
    for (auto word : shortWords.cset())
    {
        StringSet thisSet;
        thisSet.insert(word);
        _partition.insert(thisSet);
        _strings.insert(word);
    }
    this->makeSortString();
}

/************************
 * C'tor
 * 
 * Input: old StringPartitionSet, and two words 
 * Creates: new StringPartitionSet that is the finest partition of initial
 * set of words so that the new partition contains the old partition and 
 * glues together the two classes containing the two handed in words, as 
 * well as gluing together all consequential classes.
 * */
StringPartitionSet::StringPartitionSet(const StringPartitionSet & theseStrings, const std::string & firstString, const std::string & secondString)
{
}

// returns cpb::FAIL if fails to find partition element with the given word in it.  empty StringSet returned if not found.

void StringPartitionSet::makeSortString()
{
    this->_sortstring = "[";
    for (auto ss : this->_partition)
    {
        this->_sortstring += ss.sortString();
        this->_sortstring += ", ";
    }
    int len(_sortstring.length());
    if (len > 1)
    {
        _sortstring = _sortstring.substr(0, len - 2);
    }
    this->_sortstring += "]";
}

StringSet StringPartitionSet::lettersInWord(const std::string & word)
{
    StringSet letters;
    for (auto c : word)
    {
        std::string letter(boost::lexical_cast<std::string>(c));
        letters.insert(letter);
    }
    return letters;
}

StringSet StringPartitionSet::lettersInWords(const StringSet & words)
{
    StringSet letters;
    for (auto word : words.cset())
    {
        StringSet theseLetters(lettersInWord(word));
        for (auto letter : theseLetters.cset())
        {
            letters.insert(letter);
        }
    }
    return letters;
}

// modifies this StringPartitionSet by gluing two member stringSets together and forcing remaining consequences.
// will not glue if the two candidate sets are not members.

int StringPartitionSet::glueTwoSetsNoForce(const StringSet & oneSet, const StringSet & otherSet, StringSet & resultSet)
{
    resultSet.clear();

    if (oneSet == otherSet)
    {
        resultSet = oneSet;
        return 0;
    }

    std::set<StringSet>::iterator pitOne = _partition.find(oneSet);
    std::set<StringSet>::iterator pitOther = _partition.find(otherSet);
    const std::set<StringSet>::const_iterator pitE = _partition.end();

    if (pitOne != pitE && pitOther != pitE)
    {
        _partition.erase(pitOne);
        _partition.erase(pitOther);

        StringSet newSet;
        for (auto w : oneSet.cset())
        {
            resultSet.insert(w);
        }
        for (auto w : otherSet.cset())
        {
            resultSet.insert(w);
        }

        _partition.insert(resultSet);
        this->makeSortString();

        return 0;
    } else return cpb::FAIL;
}

// returns cpb::FAIL if fails to find partition element with the given word in it.  empty StringSet returned if not found.

int StringPartitionSet::setWithWord(const std::string & word, StringSet & answerSet)
{
    std::set<StringSet>::iterator pit(_partition.begin());
    const std::set<StringSet>::iterator pitE(_partition.end());
    for (; pit != pitE; ++pit)
    {
        if (pit->cset().find(word) != pit->cset().end())
        {
            break;
        }
    }
    if (pit != pitE)
    {
        answerSet = (*pit);
        return 0;
    }
    return cpb::FAIL;
}

int StringPartitionSet::glueSetsByWords(const StringSet & words)
{
    int retVal = cpb::FAIL;
    StringSet containerSet;
    std::set<StringSet> sets;
    for (auto word : words.cset())
    {
        if (cpb::FAIL != this->setWithWord(word, containerSet))
        {
            sets.insert(containerSet);
        } else
        {
            return cpb::FAIL;
        }
    }
    glueSetOfSets(sets);
    return 0;
}

int StringPartitionSet::glueSetOfSets(const std::set<StringSet> & theseSets)
{
    StringSet firstSet;
    StringSet secondSet;
    StringSet answerSet;



    if (1 < theseSets.size())
    {
        answerSet = *(theseSets.begin());
        for (auto set : theseSets)
        {
            firstSet = answerSet;
            if (cpb::FAIL == glueTwoSetsNoForce(firstSet, set, answerSet))
            {
                return cpb::FAIL;
            }
        }
    _forceQueue.insert(answerSet);
    force();
    }
    return 0;
}

int StringPartitionSet::force()
{
    std::set<StringSet> rolledSets;
    StringSet thisSet;
    StringSet rollSet;
    while (0 == setPop(_forceQueue, thisSet))
    {
        rolledSets.insert(thisSet);
        for (auto letter : _letters.cset())
        {
            if (0 == roll(letter, thisSet, rollSet))
            {
                rolledSets.insert(rollSet);
            }
        }
        for(auto rSet: rolledSets)
        {glueSetsByWords(rSet);
        }
    }
    return 0;
}

int StringPartitionSet::roll(std::string letter, const StringSet & setToRoll, StringSet & rollSet)
{
    rollSet.clear();
    for(auto word: setToRoll.cset())
    {
        word=word.substr(1,word.length()-1)+letter;
        rollSet.insert(word);
    }
    return 0;
}
