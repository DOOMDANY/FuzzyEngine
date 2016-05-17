/*! *************************************************************
 *                                                              *
 * \author  Daniel Alejandro Plascencia Ruiz.                   *
 *          Guadalajara, Jalisco, México.                       *
 *          dapr.service@gmail.com                              *
 *          Tel. (33) 3812 5330                                 *
 *          Cel. +52 1 33 1074 1591                             *
 * \date    May, 2016                                           *
 * \version 0.3                                                 *
 *                                                              *
 * \file    workmemory.cpp                                      *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "workmemory.hpp"

/**===================*~* OWN CLASSES *~*===================**/
#include "fuzzy/exceptions/commonexception.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;
using namespace fuzzy::memoryModule;
using namespace fuzzy::exceptions;

/**===================================== CONSTRUCTORS =====================================**/
WorkMemory::WorkMemory()
{

}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
bool WorkMemory::addInput(const LinguisticVariable *lv, double initialValue)
{
    return (lv == NULL) ? false : _inputs.emplace(lv, InputRegister(initialValue)).second;
}

double WorkMemory::inputValue(const LinguisticVariable *lv) const
{
    map<const LinguisticVariable*, InputRegister>::const_iterator iter;

    iter = _inputs.find(lv);
    if(iter == _inputs.cend())
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);

    return iter->second.value;
}

bool WorkMemory::existsInput(const LinguisticVariable *lv) const
{
    return _inputs.find(lv) != _inputs.cend();
}

tsize WorkMemory::inputCount() const
{
    return _inputs.size();
}

void WorkMemory::setInputValue(const LinguisticVariable *lv, double value)
{
    map<const LinguisticVariable*, InputRegister>::iterator iter;

    iter = _inputs.find(lv);

    if(iter == _inputs.end())
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);

    iter->second = value;
}

void WorkMemory::removeInput(const LinguisticVariable *lv)
{
    _inputs.erase(lv);
}

bool WorkMemory::addFunction(const LinguisticVariable *lv, const MembershipFunction *mf, double initialValue)
{
    map<const LinguisticVariable*, InputRegister>::iterator iter;

    if(lv != NULL && mf != NULL)
    {
        iter = _inputs.find(lv);
        if(iter != _inputs.end())
        {
            return iter->second.functions.emplace(mf, initialValue).second;
        }
    }

    return false;
}

double WorkMemory::functionValue(const LinguisticVariable *lv, const MembershipFunction *mf) const
{
    map<const LinguisticVariable*, InputRegister>::const_iterator inputIter;
    map<const MembershipFunction*, double>::const_iterator functionIter;

    inputIter = _inputs.find(lv);

    if(inputIter == _inputs.cend())
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);

    functionIter = inputIter->second.functions.find(mf);

    if(functionIter == inputIter->second.functions.cend())
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);

    return functionIter->second;
}

bool WorkMemory::existsFunction(const LinguisticVariable *lv, const MembershipFunction *mf) const
{
    map<const LinguisticVariable*, InputRegister>::const_iterator iter;

    iter = _inputs.find(lv);
    if(iter != _inputs.cend())
    {
        return iter->second.functions.find(mf) != iter->second.functions.cend();
    }

    return false;
}

int WorkMemory::functionCount(const LinguisticVariable *lv) const
{
    map<const LinguisticVariable*, InputRegister>::const_iterator iter;
    int count = -1;

    iter = _inputs.find(lv);
    if(iter != _inputs.cend())
    {
        return iter->second.functions.size();
    }

    return count;
}

void WorkMemory::setFunctionValue(const LinguisticVariable *lv, const MembershipFunction *mf, double value)
{
    map<const LinguisticVariable*, InputRegister>::iterator inputIter;
    map<const MembershipFunction*, double>::iterator functionIter;

    inputIter = _inputs.find(lv);

    if(inputIter == _inputs.end())
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);

    functionIter = inputIter->second.functions.find(mf);

    if(functionIter == inputIter->second.functions.cend())
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);

    functionIter->second = value;
}

void WorkMemory::removeFunction(const LinguisticVariable *lv, const MembershipFunction *mf)
{
    map<const LinguisticVariable*, InputRegister>::iterator iter;

    iter = _inputs.find(lv);
    if(iter != _inputs.end())
    {
        iter->second.functions.erase(mf);
    }
}

bool WorkMemory::addRule(const Rule *rule, double initialValue)
{
    return (rule == NULL) ? false : _rules.emplace(rule, initialValue).second;
}

double WorkMemory::ruleValue(const Rule *rule) const
{
    map<const Rule*, double>::const_iterator iter;

    iter = _rules.find(rule);
    if(iter == _rules.cend())
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);

    return iter->second;
}

bool WorkMemory::existsRule(const Rule *rule) const
{
    return _rules.find(rule) != _rules.cend();
}

tsize WorkMemory::ruleCount() const
{
    return _rules.size();
}

void WorkMemory::setRuleValue(const Rule *rule, double value)
{
    map<const Rule*, double>::iterator iter;

    iter = _rules.find(rule);
    if(iter == _rules.end())
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);

    iter->second = value;
}

void WorkMemory::removeRule(const Rule *rule)
{
    _rules.erase(rule);
}

bool WorkMemory::addOutput(const LinguisticVariable *lv, double initialValue)
{
    return (lv == NULL) ? false : _outputs.emplace(lv, initialValue).second;
}

double WorkMemory::outputValue(const LinguisticVariable *lv) const
{
    map<const LinguisticVariable*, double>::const_iterator iter;

    iter = _outputs.find(lv);
    if(iter == _outputs.cend())
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);

    return iter->second;
}

bool WorkMemory::existsOutput(const LinguisticVariable *lv) const
{
    return _outputs.find(lv) != _outputs.cend();
}

tsize WorkMemory::outputCount() const
{
    return _outputs.size();
}

void WorkMemory::setOutputValue(const LinguisticVariable *lv, double value)
{
    map<const LinguisticVariable*, double>::iterator iter;

    iter = _outputs.find(lv);
    if(iter == _outputs.end())
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);

    iter->second = value;
}

void WorkMemory::removeOutput(const LinguisticVariable *lv)
{
    _outputs.erase(lv);
}















