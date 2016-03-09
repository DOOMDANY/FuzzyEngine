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
 * \file    mfgaussian.cpp                                      *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "mfgaussian.hpp"

/**===================*~* STL LIBRARIES *~*===================**/
#include <cmath>

/**===================*~* OWN LIBRARIES *~*===================**/
#include "mfexception.hpp"
#include "linguisticvariable.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;

/**===================================== CONSTRUCTORS =====================================**/
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
MFGaussian::MFGaussian(const double *params, const LinguisticVariable *proprietary) :
    IMemberFunction(GAUSSIAN, params, 2, proprietary)
{
    if(params[0] < 0)
        throw(MFException(MFException::BAD_PARAMS));
}

/**===================================== DESTRUCTOR =====================================**/
MFGaussian::~MFGaussian()
{

}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
/*in params: params[0] -> k (bell's width)
 *           params[1] -> m (value where membership is 1.0)
 */
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
double MFGaussian::membershipGrade(double value) const
{
    double grade;

    if(value < _proprietary->lowerLimit() || value > _proprietary->upperLimit())
        throw(MFException(MFException::OUT_OF_RANGE));

    // exp(-k(x - m)^2)
    grade = exp(-_params[0] * (value - _params[1]) * (value - _params[1]));

    return grade;
}

/**===================================== SETTER & GETTER =====================================**/
void MFGaussian::setParameters(const double *params)
{
    if(params == NULL)
        throw(MFException(MFException::BAD_PARAMS));
    if(params[0] < 0)
        throw(MFException(MFException::BAD_PARAMS));

    _params[0] = params[0];
    _params[1] = params[1];
}








