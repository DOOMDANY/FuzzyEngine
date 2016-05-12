#ifndef RULECOMPILEREXCEPTION_HPP
#define RULECOMPILEREXCEPTION_HPP

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
 * \file    rulecompilerexception.hpp                           *
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

class RuleCompilerException : public std::exception
{
public:
/**===================================== PUBLIC MEMBERS =====================================**/
    enum StateCodes
    {
        UNKNOWN_MF,
        UNKNOWN_LV,
        INVALID_OPERATOR,
        UNEXPECTED_SYMBOL,
        UNKNOWN_ERROR
    };

/**===================================== CONSTRUCTORS =====================================**/
    RuleCompilerException(const std::string &message);
    RuleCompilerException(StateCodes state, const std::string &compilerMessage);

/**===================================== DESTRUCTOR =====================================**/
    virtual ~RuleCompilerException();

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    StateCodes stateCode() const;
    const char *compilerMessage() const;
    virtual const char *what() const throw();

protected:
/**===================================== PUBLIC MEMBER VARIABLES =====================================**/
    StateCodes _code;
    std::string _msg;
    std::string _compilerMsg;

/**===================================== PROTECTED MEMBER FUNCTIONS =====================================**/
    void BuildMessage();

};

}
}

#endif // RULECOMPILEREXCEPTION_HPP
