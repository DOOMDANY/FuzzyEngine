#ifndef NONEXISTENTELEMENTEXCEPTION_HPP
#define NONEXISTENTELEMENTEXCEPTION_HPP

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
 * \file    nonexistentelementexception.hpp                     *
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

template<class T>
class NonExistentElementException : public std::exception
{
public:
/**===================================== CONSTRUCTORS =====================================**/
    NonExistentElementException(const T &element);
    NonExistentElementException(const T &element, const std::string &arg);

/**===================================== DESTRUCTOR =====================================**/
    virtual ~NonExistentElementException();

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    const T &element() const;
    virtual const char *what() const throw();

protected:
/**===================================== PROTECTED MEMBER VARIABLES =====================================**/
    T _element;
    std::string msg;

};

/**===================================== CONSTRUCTORS =====================================**/
template<class T>
NonExistentElementException<T>::NonExistentElementException(const T &element) :
    _element(element),
    msg("The requested element does not exists inside the container.")
{

}

template<class T>
NonExistentElementException<T>::NonExistentElementException(const T &element, const std::string &arg) :
    _element(element),
    msg(arg)
{

}

/**===================================== DESTRUCTOR =====================================**/
template<class T>
NonExistentElementException<T>::~NonExistentElementException()
{

}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
template<class T>
const T &NonExistentElementException<T>::element() const
{
    return _element;
}

template<class T>
const char *NonExistentElementException<T>::what() const throw()
{
    return msg.c_str();
}

}
}

#endif // NONEXISTENTELEMENTEXCEPTION_HPP









