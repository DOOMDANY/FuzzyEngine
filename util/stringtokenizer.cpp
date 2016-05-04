/*! *************************************************************
 *                                                              *
 * \author  Daniel Alejandro Plascencia Ruiz.                   *
 *          Guadalajara, Jalisco, México.                       *
 *          dapr.service@gmail.com                              *
 *          Tel. (33) 3812 5330                                 *
 *          Cel. +52 1 33 1074 1591                             *
 * \date    March, 2016                                         *
 * \version 0.3                                                 *
 *                                                              *
 * \file    stringtokenizer.cpp                                 *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "stringtokenizer.hpp"

using namespace std;
using namespace util;

/**===================================== CONSTRUCTORS =====================================**/
StringTokenizer::StringTokenizer(const string &str) :
    _str(str),
    _iterator(_tokens.cbegin())
{

}

/**===================================== DESTRUCTOR =====================================**/
StringTokenizer::~StringTokenizer()
{

}

/**===================================== PUBLI MEMBER FUNCTIONS =====================================**/
void StringTokenizer::setStr(const string &str)
{
    _str = str;
    _tokens.clear();
    _iterator = _tokens.cbegin();
}

const string &StringTokenizer::str() const
{
    return _str;
}

/**===================================== PUBLI MEMBER FUNCTIONS =====================================**/
void StringTokenizer::tokenize(const string &separator, bool keepEmptyParts)
{
    string token;
    string temp;
    string::const_iterator itStr = _str.cbegin();
    string::const_iterator itSep = separator.cbegin();

    while(itStr != _str.end())
    {
        if(*itStr == *itSep)
        {
            temp.push_back(*itStr);
            itSep++;

            if(itSep == separator.cend())
            {
                if(!token.empty() || keepEmptyParts)
                    _tokens.push_back(token);
                token.clear();
                temp.clear();
                itSep = separator.cbegin();
            }
        }
        else
        {
            token.append(temp);
            token.push_back(*itStr);
            temp.clear();
        }

        itStr++;
    }
    if(!token.empty() || keepEmptyParts)
        _tokens.push_back(token);

    _iterator = _tokens.cbegin();
}

bool StringTokenizer::hasNext() const
{
    return _iterator != _tokens.end();
}

const string &StringTokenizer::next() const
{
    vector<string>::const_iterator it = _iterator++;
    return *it;
}










