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
//                        std::bad_alloc
MembershipFunction::MembershipFunction(const string &name, MFType type, const double *params,
                                       const LinguisticVariable *proprietary) :
    IRulePart(),
    _name(name)
{
    createMemberFunction(type, params, proprietary);
}

//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
//                        std::bad_alloc
MembershipFunction::MembershipFunction(const string &name, const string &expression,
                                       const LinguisticVariable *proprietary) :
    IRulePart(),
    _name(name)
{
    createMemberFunction(expression, proprietary);
}

MembershipFunction::MembershipFunction(const MembershipFunction &other) :
    _memberFunction(NULL)
{
    *this = other;
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

//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
void MembershipFunction::setParameters(const double *params)
{
    _memberFunction->setParameters(params);
}

const double *MembershipFunction::parameters() const
{
    return _memberFunction->parameters();
}

//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
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

//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
//                        std::bad_alloc
void MembershipFunction::setType(MFType type, const double *newParams)
{
    IMemberFunction *memberFunction;

    tsize oldParamCount = IMemberFunction::parameterCount(_memberFunction->type());
    tsize newParamCount = IMemberFunction::parameterCount(type);

    double params[newParamCount];

    memberFunction = _memberFunction;
    try
    {
        if(params == NULL)
        {
            if(newParamCount <= oldParamCount)
            {
                createMemberFunction(type, _memberFunction->parameters(), _memberFunction->proprietary());
            }
            else
            {
                for(tsize i = 0; i < oldParamCount; i++)
                    params[i] = _memberFunction->parameters()[i];
                for(tsize i = oldParamCount; i < newParamCount; i++)
                    params[i] = 0.0;

                createMemberFunction(type, params, _memberFunction->proprietary());
            }
        }
        else
        {
            createMemberFunction(type, newParams, _memberFunction->proprietary());
        }
    }
    catch(exception *e)
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

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
double MembershipFunction::membershipGrade(double value) const
{
    return _memberFunction->membershipGrade(value);
}

/**===================================== OVERLOADED OPERATORS =====================================**/
const MembershipFunction &MembershipFunction::operator = (const MembershipFunction &other)
{
    IMemberFunction *mfAux = _memberFunction;

    _name = other._name;
    if(other.type() != CUSTOM)
        createMemberFunction(other.type(), other.parameters(), other.proprietary());
    else
        createMemberFunction(other.expression(), other.proprietary());

    if(mfAux != NULL)
        delete mfAux;

    return *this;
}

MembershipFunction &MembershipFunction::operator = (MembershipFunction &&other)
{
    IMemberFunction *mfAux = _memberFunction;

    _name = other._name;
    _memberFunction = other._memberFunction;

    other._memberFunction = mfAux;

    return *this;
}

/**===================================== PRIVATE MEMBER FUNCTIONS =====================================**/
//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
//                        std::bad_alloc
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

//this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
//                        std::bad_alloc
void MembershipFunction::createMemberFunction(const string &expression, const LinguisticVariable *proprietary)
{
    _memberFunction = new MFCustom(expression, proprietary);
}








