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
 * \file    MFCustom.cpp                                        *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "mfcustom.hpp"

/**===================*~* STL LIBRARIES *~*===================**/
#include <vector>
#include <string>

/**===================*~* OWN LIBRARIES *~*===================**/
#include "mfexception.hpp"
#include "fuzzy/knowledgeModule/linguisticvariable.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;

/**===================================== CONSTRUCTORS =====================================**/
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
MFCustom::MFCustom(const std::string &expression, const LinguisticVariable *proprietary) :
    IMemberFunction(CUSTOM, NULL, 0u, proprietary)
{
    setExpression(expression);
}

/**===================================== DESTRUCTOR =====================================**/
MFCustom::~MFCustom()
{

}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
double MFCustom::membershipGrade(double value) const
{
    double grade = 0.0;

    if(value < _proprietary->lowerLimit() || value > _proprietary->upperLimit())
        throw(MFException(MFException::OUT_OF_RANGE));

    //evaluate the expression with a parser
    //value = parser.Evaluate(expression);

    return grade;
}

/**===================================== SETTER & GETTER =====================================**/
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
void MFCustom::setExpression(const std::string &expression)
{
    //expression needs to be parsed
    //if(parse fails)
        //throw(MFException(MFException::INVALID_EXPRESSION))
    _expression = expression;
}

const std::string &MFCustom::expression() const
{
    return _expression;
}







