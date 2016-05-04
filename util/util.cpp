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
 * \file    util.cpp                                            *
 *                                                              *
 ****************************************************************/

/**===================*~* STL LIBRARIES *~*===================**/
#include "util.hpp"

using namespace std;

namespace util
{

bool isLogicalOperator(char c)
{
    return c == '&' || c == '|' || c == '~' || c == '^';
}

bool isAssignmentOperator(char c)
{
    return c == '=';
}

bool isOperator(char c)
{
    return isLogicalOperator(c) ||
            isAssignmentOperator(c);
}

bool isSpace(char c)
{
    return c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ';
}

string simplify(const string &str)
{
    string::const_iterator iterator = str.cbegin();
    string::const_iterator strEnd = str.cend();
    string simplifiedStr;
    bool prevSpace = false;

    while(iterator != strEnd && isSpace(*iterator)) iterator++;

    while(iterator != strEnd)
    {
        if(isSpace(*iterator))
        {
            if(!prevSpace)
            {
                simplifiedStr.push_back(' ');
                prevSpace = true;
            }
        }
        else
        {
            simplifiedStr.push_back(*iterator);
            prevSpace = false;
        }

        iterator++;
    }

    if(isSpace(simplifiedStr.back()))
        simplifiedStr.pop_back();

    return simplifiedStr;
}

string toUpper(const string &str)
{
    string upperStr;
    string::const_iterator end = str.cend();

    for(string::const_iterator iterator = str.cbegin(); iterator != end; iterator++)
        upperStr.push_back(toupper(*iterator));

    return upperStr;
}

}







