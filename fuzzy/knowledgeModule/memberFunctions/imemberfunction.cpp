/*! *************************************************************
 *                                                              *
 * \author  Daniel Alejandro Plascencia Ruiz.                   *
 *          Guadalajara, Jalisco, México.                       *
 *          dapr.service@gmail.com                              *
 *          Tel. (33) 3812 5330                                 *
 *          Cel. +52 1 33 1074 1591                             *
 * \date    February, 2016                                      *
 * \version 0.3                                                 *
 *                                                              *
 * \file    imemberfunction.cpp                                 *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "imemberfunction.hpp"

/**===================*~* OWN CLASSES *~*===================**/
#include "mfexception.hpp"

using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;

const tsize IMemberFunction::MFSizes[] = {
    3u,
    0u,
    2u,
    2u,
    1u,
    4u,
    3u
};

/**===================================== PUBLIC STATIC FUNCTIONS =====================================**/
tsize IMemberFunction::parameterCount(MFType type)
{
    if(type < 0 || type >= MFType::MAX_TYPE)
        return 0u;
    else
        return MFSizes[type];
}

/**===================================== CONSTRUCTORS =====================================**/
IMemberFunction::IMemberFunction(MFType type, const double *params, tsize paramNumber,
                                 const LinguisticVariable *proprietary) :
    _type(type),
    _proprietary(proprietary),
    _params(new double[paramNumber]),
    _paramNumber(paramNumber)
{
    if(proprietary == NULL)
        throw MFException(MFException::NULL_PROPRIETARY);

    if(params == NULL && paramNumber != 0)
        throw MFException(MFException::BAD_PARAMS);

    for(tsize i = 0; i < paramNumber; i++)
        _params[i] = params[i];
}

/**===================================== DESTRUCTOR =====================================**/
IMemberFunction::~IMemberFunction()
{
    if(_params != NULL)
        delete _params;
}

/**===================================== SETTER & GETTER =====================================**/
MFType IMemberFunction::type() const
{
    return _type;
}

const LinguisticVariable *IMemberFunction::proprietary() const
{
    return _proprietary;
}

void IMemberFunction::setParameters(const double *params)
{
    for(tsize i = 0; i < _paramNumber; i++)
        _params[i] = params[i];
}

const double *IMemberFunction::parameters() const
{
    return _params;
}











