#ifndef STRINGTOKENIZER_HPP
#define STRINGTOKENIZER_HPP

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
 * \file    stringtokenizer.hpp                                 *
 *                                                              *
 ****************************************************************/

/**===================*~* STL LIBRARIES *~*===================**/
#include <string>
#include <vector>

/**===================*~* OWN LIBRARIES *~*===================**/
#include "util.hpp"

namespace util
{

class StringTokenizer
{
public:
/**===================================== CONSTRUCTORS =====================================**/
    StringTokenizer(const std::string &str);

/**===================================== DESTRUCTOR =====================================**/
    ~StringTokenizer();

/**===================================== PUBLI MEMBER FUNCTIONS =====================================**/
    void setStr(const std::string &str);
    const std::string &str() const;

/**===================================== PUBLI MEMBER FUNCTIONS =====================================**/
    void tokenize(const std::string &separator, bool keepEmptyParts = false);
    bool hasNext() const;
    const std::string &next() const;

private:
/**===================================== PRIVATE MEMBER VARIABLES =====================================**/
    std::string _str;
    std::vector<std::string> _tokens;
    mutable std::vector<std::string>::const_iterator _iterator;

};

}

#endif // STRINGTOKENIZER_HPP














