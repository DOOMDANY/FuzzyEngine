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
 * \file    badinstanceexception.hpp                            *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "badinstanceexception.hpp"

/**===================*~* STL LIBRARIES *~*===================**/
#include <exception>
#include <string>

using namespace std;
using namespace fuzzy::exceptions;

/**===================================== CONSTRUCTORS =====================================**/
BadInstanceException::BadInstanceException()
{
    msg = "The Object could not be instantiated";
}

BadInstanceException::BadInstanceException(const string &arg)
{
    msg = arg;
}

/**===================================== DESTRUCTOR =====================================**/
BadInstanceException::~BadInstanceException()
{

}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
const char *BadInstanceException::what() const throw()
{
    return msg.c_str();
}











