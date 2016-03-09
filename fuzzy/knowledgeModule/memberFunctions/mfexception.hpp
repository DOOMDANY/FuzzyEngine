#ifndef MFEXCEPTION_HPP_INCLUDED
#define MFEXCEPTION_HPP_INCLUDED

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
 * \file    mfexception.hpp                                     *
 *                                                              *
 ****************************************************************/

/**===================*~* STL LIBRARIES *~*===================**/
#include <exception>
#include <string>

/**===================*~* OWN LIBRARIES *~*===================**/
#include "knowledgemodule.hpp"

namespace fuzzy
{
namespace knowledgeModule
{
namespace memberFunctions
{

class MFException : public std::exception
{
public:
/**===================================== PUBLIC MEMBERS =====================================**/
    enum StateCodes
    {
        BAD_PARAMS,
        INVALID_EXPRESSION,
        INVALID_MF,
        INVALID_NAME,
        NULL_PROPRIETARY,
        OUT_OF_RANGE,
        UNKNOWN
    };

/**===================================== CONSTRUCTORS =====================================**/
    MFException();
    MFException(const std::string &arg);
    MFException(StateCodes _code);

/**===================================== DESTRUCTOR =====================================**/
    virtual ~MFException();

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    StateCodes GetStateCode();
    virtual const char *what() const throw();

protected:
/**===================================== PROTECTED MEMBER VARIABLES =====================================**/
    StateCodes _code;
    std::string _msg;

/**===================================== PROTECTED MEMBER FUNCTIONS =====================================**/
    void BuildMessage();
};

}
}
}

#endif // MFEXCEPTION_HPP_INCLUDED
