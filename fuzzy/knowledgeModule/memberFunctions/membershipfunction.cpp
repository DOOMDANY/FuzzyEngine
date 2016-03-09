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
 * \file    membershipfunction.cpp                              *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "membershipfunction.hpp"

/**===================*~* OWN LIBRARIES *~*===================**/
#include "imemberfunction.hpp"
#include "mfexception.hpp"
#include "mfbell.hpp"
#include "mfcustom.hpp"
#include "mfgaussian.hpp"
#include "mfsigmoid.hpp"
#include "mfsingleton.hpp"
#include "mftrapezoid.hpp"
#include "mftriangle.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;

static string nonExpressionStr;

/**===================================== CONSTRUCTORS =====================================**/
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
MembershipFunction::MembershipFunction(const string &name, MFType type, const double *params,
                                       const LinguisticVariable *proprietary) :
    _name(name)
{
    createMemberFunction(type, params, proprietary);
}

//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
MembershipFunction::MembershipFunction(const string &name, const string &expression,
                                       const LinguisticVariable *proprietary) :
    _name(name)
{
    createMemberFunction(expression, proprietary);
}

/**===================================== DESTRUCTOR =====================================**/
MembershipFunction::~MembershipFunction()
{
    if(_memberFunction != NULL)
        delete _memberFunction;
}

/**===================================== SETTER & GETTER =====================================**/
void MembershipFunction::rename(const string &name)
{
    _name = name;
}

const string &MembershipFunction::name() const
{
    return _name;
}

void MembershipFunction::setParameters(const double *params)
{
    _memberFunction->setParameters(params);
}

const double *MembershipFunction::Parameters() const
{
    return _memberFunction->parameters();
}

void MembershipFunction::setExpression(const string &expression)
{
    MFCustom *mf = dynamic_cast<MFCustom*>(_memberFunction);
    if(mf != NULL)
        mf->setExpression(expression);
}

const string &MembershipFunction::expression() const
{
    MFCustom *mf = dynamic_cast<MFCustom*>(_memberFunction);
    if(mf != NULL)
        return mf->expression();
    else
        return nonExpressionStr;
}

void MembershipFunction::setType(MFType type)
{
    IMemberFunction *memberFunction;

    tsize oldParamCount = IMemberFunction::parameterCount(_memberFunction->type());
    tsize newParamCount = IMemberFunction::parameterCount(type);

    double params[newParamCount];

    memberFunction = _memberFunction;
    try
    {
        if(newParamCount <= oldParamCount)
            createMemberFunction(type, _memberFunction->parameters(), _memberFunction->proprietary());
        else
        {
            for(tsize i = 0; i < oldParamCount; i++)
                params[i] = _memberFunction->parameters()[i];
            for(tsize i = oldParamCount; i < newParamCount; i++)
                params[i] = _memberFunction->parameters()[i];

            createMemberFunction(type, params, _memberFunction->proprietary());
        }
    }
    catch(exception &e)
    {
        _memberFunction = memberFunction;
        throw e;
    }
}

MFType MembershipFunction::type() const
{
    return _memberFunction->type();
}

const LinguisticVariable *MembershipFunction::proprietary() const
{
    return _memberFunction->proprietary();
}

/**===================================== PRIVATE MEMBER FUNCTIONS =====================================**/
void MembershipFunction::createMemberFunction(MFType type, const double *params, const LinguisticVariable *proprietary)
{
    switch(type)
    {
        case MFType::BELL:
            _memberFunction = new MFBell(params, proprietary);
            break;
        case MFType::GAUSSIAN:
            _memberFunction = new MFGaussian(params, proprietary);
            break;
        case MFType::SIGMOID:
            _memberFunction = new MFSigmoid(params, proprietary);
            break;
        case MFType::SINGLETON:
            _memberFunction = new MFSingleton(params, proprietary);
            break;
        case MFType::TRAPEZOID:
            _memberFunction = new MFTrapezoid(params, proprietary);
            break;
        case MFType::TRIANGLE:
            _memberFunction = new MFTriangle(params, proprietary);
            break;
        default:
            throw(MFException(MFException::INVALID_MF));
    }
}

void MembershipFunction::createMemberFunction(const string &expression, const LinguisticVariable *proprietary)
{
    _memberFunction = new MFCustom(expression, proprietary);
}








