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
 * \file    mfsigmoid.cpp                                       *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "mfsigmoid.hpp"

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
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
MFSigmoid::MFSigmoid(const double *params, const LinguisticVariable *proprietary) :
    IMemberFunction(SIGMOID, params, 2u, proprietary)
{

}

/**===================================== DESTRUCTOR =====================================**/
MFSigmoid::~MFSigmoid()
{

}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
/*in params: params[0] -> a
 *           params[1] -> c
 */
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
double MFSigmoid::membershipGrade(double value) const
{
    double grade;

    if(value < _proprietary->lowerLimit() || value > _proprietary->upperLimit())
        throw(MFException(MFException::OUT_OF_RANGE));

    // 1 / (1 + exp(-a(x - c)))
    grade = 1.0 / (1.0 + exp(-_params[0] * (value - _params[1])));

    return grade;
}








