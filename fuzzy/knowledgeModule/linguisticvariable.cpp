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
 * \file    linguisticvariable.cpp                              *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "linguisticvariable.hpp"

/**===================*~* OWN CLASSES  *~*===================**/
#include "fuzzy/knowledgeModule/memberFunctions/membershipfunction.hpp"
#include "fuzzy/knowledgeModule/memberFunctions/mfexception.hpp"
#include "fuzzy/exceptions/commonexception.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;
using namespace fuzzy::exceptions;

/**===================================== CONSTRUCTORS =====================================**/
LinguisticVariable::LinguisticVariable(const string &name, double lowerLimit, double upperLimit) :
    _name(name)
{
    setLimits(lowerLimit, upperLimit);
}

/**===================================== DESTRUCTOR =====================================**/
LinguisticVariable::~LinguisticVariable()
{

}

/**===================================== SETTER & GETTER =====================================**/
void LinguisticVariable::rename(const string &name)
{
    _name = name;
}

const string &LinguisticVariable::name() const
{
    return _name;
}

void LinguisticVariable::setLimits(double lowerLimit, double upperLimit)
{
    if(lowerLimit > upperLimit)
        throw out_of_range("Lower limit is greater than upper limit.");
    else
    {
        _lowerLimit = lowerLimit;
        _upperLimit = upperLimit;
    }
}

void LinguisticVariable::setLowerLimit(double lowerLimit)
{
    if(lowerLimit > _upperLimit)
        throw out_of_range("Lower limit is greater than upper limit.");
    else
        _lowerLimit = lowerLimit;
}

double LinguisticVariable::lowerLimit() const
{
    return _lowerLimit;
}

void LinguisticVariable::setUpperLimit(double upperLimit)
{
    if(_lowerLimit > upperLimit)
        throw out_of_range("Lower limit is greater than upper limit.");
    else
        _upperLimit = upperLimit;
}

double LinguisticVariable::upperLimit() const
{
    return _upperLimit;
}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
void LinguisticVariable::createMembershipFunction(const string &functionName, const double *params, MFType type)
{
    if(_memberFunctions.empty())
        _memberFunctions.insert(pair<tsize, MembershipFunction>
                                (1u, MembershipFunction(functionName, type, params, this)));
    else
    {
        if(idMembershipFunction(functionName) > 0)
            throw(CommonException(CommonException::DUPLICATED_ITEM));
        else
        {
            _memberFunctions.insert(pair<tsize, MembershipFunction>
                                    (_memberFunctions.crbegin()->first + 1u,
                                     MembershipFunction(functionName, type, params, this)));
        }
    }
}

void LinguisticVariable::createMembershipFunction(const string &functionName, const string &expression)
{
    if(_memberFunctions.empty())
        _memberFunctions.insert(std::pair<tsize, MembershipFunction>
                                (1u, MembershipFunction(functionName, expression, this)));
    else
    {
        if(idMembershipFunction(functionName) > 0)
            throw(CommonException(CommonException::DUPLICATED_ITEM));
        else
            _memberFunctions.insert(pair<tsize, MembershipFunction>
                                    (_memberFunctions.crbegin()->first + 1u,
                                     MembershipFunction(functionName, expression, this)));
    }
}

tsize LinguisticVariable::membershipFunctionCount() const
{
    return _memberFunctions.size();
}

const MembershipFunction &LinguisticVariable::membershipFunction(tsize id) const
{
    map<tsize, MembershipFunction>::const_iterator it;

    it = _memberFunctions.find(id);
    if(it == _memberFunctions.cend())
    {
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);
    }

    return it->second;
}

MembershipFunction &LinguisticVariable::membershipFunction(tsize id)
{
    map<tsize, MembershipFunction>::iterator it;

    it = _memberFunctions.find(id);
    if(it == _memberFunctions.end())
    {
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);
    }

    return it->second;
}

const map<tsize, MembershipFunction> &LinguisticVariable::membershipFunctions() const
{
    return _memberFunctions;
}

int LinguisticVariable::idMembershipFunction(const string &name) const
{
    for(map<tsize, MembershipFunction>::const_iterator it = _memberFunctions.cbegin();
        it != _memberFunctions.cend(); it++)
        if(it->second.name() == name)
            return it->first;

    return -1;
}

void LinguisticVariable::replaceMembershipFunction(const MembershipFunction &membershipFunction, tsize id)
{
    map<tsize, MembershipFunction>::iterator it;

    it = _memberFunctions.find(id);
    if(it == _memberFunctions.end())
    {
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);
    }

    it->second = membershipFunction;
}

void LinguisticVariable::removeMembershipFunction(tsize id)
{
    _memberFunctions.erase(id);
}








