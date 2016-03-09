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
 * \file    duplicateditemexception.cpp                         *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "duplicateditemexception.hpp"

/**===================*~* STL LIBRARIES *~*===================**/
#include <exception>
#include <string>

using namespace std;
using namespace fuzzy;
using namespace fuzzy::exceptions;

/**===================================== CONSTRUCTORS =====================================**/
DuplicatedItemException::DuplicatedItemException() :
    msg("Some Item or Object has been duplicated")
{

}

DuplicatedItemException::DuplicatedItemException(const string &arg) :
    msg(arg)
{

}

/**===================================== DESTRUCTOR =====================================**/
DuplicatedItemException::~DuplicatedItemException()
{

}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
const char *DuplicatedItemException::what() const throw()
{
    return msg.c_str();
}












