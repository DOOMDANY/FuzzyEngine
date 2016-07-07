/*! *************************************************************
 *                                                              *
 * \author  Daniel Alejandro Plascencia Ruiz.                   *
 *          Guadalajara, Jalisco, México.                       *
 *          dapr.service@gmail.com                              *
 *          Tel. (33) 3812 5330                                 *
 *          Cel. +52 1 33 1074 1591                             *
 * \date    May, 2016                                           *
 * \version 0.3                                                 *
 *                                                              *
 * \file    commonexception.cpp                                 *
 *                                                              *
 ****************************************************************/

/**===================*~* Class Definition *~*===================**/
#include "commonexception.hpp"

using namespace std;
using namespace fuzzy::exceptions;

const string CommonException::_exceptionTypeStr[] = {
    "UNKNOWN: unknown exception.",
    "BAD_INSTANCE: The Object could not be instantiated.",
    "DUPLICATED_ITEM: Some Item or Object is duplicated.",
    "NON_EXISTENT_ELEMENT: Requestet item does not exists.",
    "NULL_POINTER: A null pointer has been detected."
};

/**===================================== CONSTRUCTORS =====================================**/
CommonException::CommonException(ExceptionType type) :
    _type(type)
{

}

CommonException::CommonException(const std::string &arg) :
    _type(UNKNOWN),
    _msg(arg)
{

}

/**===================================== DESTRUCTOR =====================================**/
CommonException::~CommonException()
{

}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
const char *CommonException::what() const throw()
{
    if(_msg.empty())
    {
        return _exceptionTypeStr[_type].c_str();
    }

    return _msg.c_str();
}

CommonException::ExceptionType CommonException::type() const
{
    return _type;
}













