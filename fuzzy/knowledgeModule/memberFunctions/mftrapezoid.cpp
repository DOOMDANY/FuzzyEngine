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
 * \file    mftrapezoid.cpp                                     *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "mftrapezoid.hpp"

/**===================*~* OWN LIBRARIES *~*===================**/
#include "linguisticvariable.hpp"
#include "mfexception.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;

/**===================================== CONSTRUCTORS =====================================**/
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
MFTrapezoid::MFTrapezoid(const double *params, const LinguisticVariable *proprietary) :
    IMemberFunction(TRAPEZOID, params, 4, proprietary)
{
    for(unsigned int i = 1; i < _paramNumber; i++)
        if(_params[i - 1] > _params[i])
            throw(MFException(MFException::BAD_PARAMS));
}

/**===================================== DESTRUCTOR =====================================**/
MFTrapezoid::~MFTrapezoid()
{

}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
/*in params: params[0] -> a
 *           params[1] -> b
 *           params[2] -> c
 *           params[3] -> d
 */
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
double MFTrapezoid::membershipGrade(double value) const
{
    double grade;

    if(value < _proprietary->lowerLimit() || value > _proprietary->upperLimit())
        throw(MFException(MFException::OUT_OF_RANGE));

    if(value <= _params[0])
        grade = 0.0;
    else if(value < _params[1])
        //M(x) = (x - a) / (b - a)
        grade = _params[1] == _params[0] ? 1.0 : (value - _params[0]) / (_params[1] - _params[0]);
    else if(value <= _params[2])
        grade = 1.0;
    else if(value < _params[3])
        //M(x) = (d - x) / (d - c)
        grade = _params[3] == _params[2] ? 1.0 : (_params[3] - value) / (_params[3] - _params[2]);
    else
        grade = 0.0;

    return grade;
}

/**===================================== SETTER & GETTER =====================================**/
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
void MFTrapezoid::setParameters(const double *params)
{
    if(params == NULL)
        throw(MFException(MFException::BAD_PARAMS));
    for(tsize i = 1u; i < _paramNumber; i++)
        if(params[i - 1] > params[i])
            throw(MFException(MFException::BAD_PARAMS));

    for(tsize i = 0u; i < _paramNumber; i++)
        _params[i] = params[i];
}










