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
 * \file    mftriangle.cpp                                      *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "mftriangle.hpp"

/**===================*~* OWN LIBRARIES *~*===================**/
#include "mfexception.hpp"
#include "linguisticvariable.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;

/**===================================== CONSTRUCTORS =====================================**/
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
MFTriangle::MFTriangle(const double *params, const LinguisticVariable *proprietary) :
    IMemberFunction(TRIANGLE, params, 3, proprietary)
{
    for(tsize i = 1; i < _paramNumber; i++)
        if(params[i - 1] > params[i])
            throw(MFException(MFException::BAD_PARAMS));
}

/**===================================== DESTRUCTOR =====================================**/
MFTriangle::~MFTriangle()
{

}

/**===================================== SETTER & GETTER =====================================**/
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
void MFTriangle::setParams(const double *params)
{
    if(params == NULL)
        throw(MFException(MFException::BAD_PARAMS));
    for(tsize i = 1; i < _paramNumber; i++)
        if(params[i - 1] > params[i])
            throw(MFException(MFException::BAD_PARAMS));

    for(tsize i = 0; i < _paramNumber; i++)
        _params[i] = params[i];
}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
/*in params: params[0] -> a
 *           params[1] -> b
 *           params[2] -> c
 */
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
double MFTriangle::membershipGrade(double value) const
{
    double grade;

    if(value < _proprietary->lowerLimit() || value > _proprietary->upperLimit())
        throw(MFException(MFException::OUT_OF_RANGE));

    if(value <= _params[0])
        grade = 0.0;
    else if(value < _params[1])
        //M(x) = (x - a) / (b - a)
        grade = _params[1] == _params[0] ? 1.0 : (value - _params[0]) / (_params[1] - _params[0]);
    else if(value < _params[2])
        //M(x) = (c - x) / (c - b)
        grade = _params[2] == _params[1] ? 1.0 : (_params[2] - value) / (_params[2] - _params[1]);
    else
        grade = 0.0;

    return grade;
}










