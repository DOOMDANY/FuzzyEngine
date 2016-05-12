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
 * \file    mfsingleton.cpp                                     *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "mfsingleton.hpp"

/**===================*~* OWN LIBRARIES *~*===================**/
#include "fuzzy/knowledgeModule/linguisticvariable.hpp"
#include "mfexception.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;

/**===================================== CONSTRUCTORS =====================================**/
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
MFSingleton::MFSingleton(const double *params, const LinguisticVariable *proprietary) :
    IMemberFunction(SINGLETON, params, 1u, proprietary)
{

}

/**===================================== DESTRUCTOR =====================================**/
MFSingleton::~MFSingleton()
{

}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
/*in params: params[0] -> membership value
 */
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
double MFSingleton::membershipGrade(double value) const
{
    double grade;

    if(value < _proprietary->lowerLimit() || value > _proprietary->upperLimit())
        throw(MFException(MFException::OUT_OF_RANGE));

    grade = (value == _params[0] ? 1.0 : 0.0);

    return grade;
}






