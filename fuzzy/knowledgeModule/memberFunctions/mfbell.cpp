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
 * \file    mfbell.cpp                                          *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "mfbell.hpp"

/**===================*~* STL LIBRARIES *~*===================**/
#include <cmath>

/**===================*~* OWN LIBRARIES *~*===================**/
#include "linguisticvariable.hpp"
#include "mfexception.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;

/**===================================== CONSTRUCTORS =====================================**/
MFBell::MFBell(const double *params, const LinguisticVariable *proprietary) :
    IMemberFunction(BELL, params, 3u, proprietary)
{
    if(params[0] == 0)
        throw(MFException(MFException::BAD_PARAMS));
}

/**===================================== DESTRUCTOR =====================================**/
MFBell::~MFBell()
{

}

/**===================================== SETTER & GETTER =====================================**/
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
void MFBell::setParameters(const double *params)
{
    if(params == NULL)
        throw(MFException(MFException::BAD_PARAMS));
    if(params[0] == 0)
        throw(MFException(MFException::BAD_PARAMS));

    _params[0] = params[0];
    _params[1] = params[1];
    _params[2] = params[2];
}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
/*in params: params[0] -> a
 *           params[1] -> b
 *           params[2] -> c
 */
 //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
double MFBell::membershipGrade(double value) const
{
    double grade;

    if(value < _proprietary->lowerLimit() || value > _proprietary->upperLimit())
        throw(MFException(MFException::OUT_OF_RANGE));

    // 1 / (1 + |(x - c) / a|^2b)
    grade = 1 / (1 + pow(abs((value - _params[2]) / _params[0]), 2.0 * _params[1]));

    return grade;
}












