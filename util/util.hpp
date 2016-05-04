#ifndef UTIL
#define UTIL

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
 * \file    util.hpp                                            *
 *                                                              *
 ****************************************************************/

/**===================*~* STL LIBRARIES *~*===================**/
#include <string>

namespace util
{

/**===================================== FUNCTIONS =====================================**/
bool isLogicalOperator(char c);
bool isAssignmentOperator(char c);
bool isOperator(char c);

bool isSpace(char c);
std::string simplify(const std::string &str);

std::string toUpper(const std::string &str);

/**===================================== NAMESPACE CLASSES =====================================**/
class StringTokenizer;

}

#endif // UTIL

