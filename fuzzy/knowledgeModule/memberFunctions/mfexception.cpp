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

/**===================*~* CLASS DEFINITION *~*===================**/
#include "mfexception.hpp"

/**===================*~* STL LIBRARIES *~*===================**/
#include <exception>
#include <string>

using namespace std;
using namespace fuzzy::knowledgeModule::memberFunctions;

/**===================================== CONSTRUCTORS =====================================**/
MFException::MFException()
{
    _code = UNKNOWN;
    BuildMessage();
}

MFException::MFException(const string &arg)
{
    _code = UNKNOWN;
    _msg = arg;
}

MFException::MFException(StateCodes code)
{
    _code = code;
    BuildMessage();
}

/**===================================== DESTRUCTOR =====================================**/
MFException::~MFException()
{

}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
MFException::StateCodes MFException::stateCode() const
{
    return _code;
}

const char *MFException::what() const throw()
{
    return _msg.c_str();
}

/**===================================== PROTECTED MEMBER FUNCTIONS =====================================**/
void MFException::BuildMessage()
{
    switch(_code)
    {
        case MFException::StateCodes::BAD_PARAMS:
            _msg = "BAD_PARAMS: Some parameter is missing or has a not allowed value";
        break;
        case MFException::StateCodes::INVALID_EXPRESSION:
            _msg = "INVALID_EXPRESSION: The mathematical expression is not valid";
        break;
        case MFException::StateCodes::INVALID_NAME:
            _msg = "INVALID_NAME: The MF name cannot be empty string";
        break;
        case MFException::StateCodes::NULL_PROPRIETARY:
            _msg = "NULL_PROPRIETARY: Ptr to the proprietary LV is NULL";
        break;
        case MFException::StateCodes::OUT_OF_RANGE:
            _msg = "OUT_OF_RANGE: The membership grade is less than lower limit or greater than upper limit";
        break;
        case MFException::StateCodes::INVALID_MF:
            _msg = "INVALID_MF: The requested MF does not exist";
        break;
        case UNKNOWN: default:
            _msg = "UNKNOWN: Unkown error";
    }
}
