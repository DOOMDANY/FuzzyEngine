#ifndef DUPLICATEDITEMEXCEPTION_HPP
#define DUPLICATEDITEMEXCEPTION_HPP

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
 * \file    duplicateditemexception.hpp                         *
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

class DuplicatedItemException : public std::exception
{
public:
/**===================================== CONSTRUCTORS =====================================**/
    DuplicatedItemException();
    DuplicatedItemException(const std::string &arg);

/**===================================== DESTRUCTOR =====================================**/
    virtual ~DuplicatedItemException();

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    virtual const char *what() const throw();

protected:
/**===================================== PROTECTED MEMBER VARIABLES =====================================**/
    std::string msg;
};

}
}

#endif // DUPLICATEDITEMEXCEPTION_HPP
