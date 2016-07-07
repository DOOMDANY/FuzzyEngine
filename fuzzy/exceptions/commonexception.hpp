#ifndef COMMONEXCEPTION_HPP
#define COMMONEXCEPTION_HPP

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
 * \file    commonexception.hpp                                 *
 *                                                              *
 ****************************************************************/

/**===================*~* STL LIBRARIES *~*===================**/
#include <exception>
#include <string>

/**===================*~* OWN LIBRARIES *~*===================**/
#include "exceptions.hpp"

namespace fuzzy
{
namespace exceptions
{

class CommonException : public std::exception
{
public:
/**===================================== PUBLIC MEMBERS =====================================**/
    enum ExceptionType
    {
        UNKNOWN,
        BAD_INSTANCE,
        DUPLICATED_ITEM,
        NON_EXISTENT_ELEMENT,
        NULL_POINTER
    };

/**===================================== PUBLIC STATIC MEMBERS =====================================**/
    static const std::string _exceptionTypeStr[];

/**===================================== CONSTRUCTORS =====================================**/
    CommonException(ExceptionType type);
    CommonException(const std::string &arg);

/**===================================== DESTRUCTOR =====================================**/
    virtual ~CommonException();

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    virtual const char *what() const throw();

    ExceptionType type() const;

protected:
/**===================================== PROTECTED MEMBER VARIABLES =====================================**/
    ExceptionType _type;
    std::string _msg;

};

}
}

#endif // COMMONEXCEPTION_HPP
