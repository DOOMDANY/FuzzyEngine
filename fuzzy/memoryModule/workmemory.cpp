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
#include "fuzzy/exceptions/nonexistentelementexception.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::memoryModule;
using namespace fuzzy::exceptions;

/**===================================== CONSTRUCTORS =====================================**/
WorkMemory::WorkMemory()
{

}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
bool WorkMemory::addInput(tsize idLv, double initialValue)
{
    return _inputs.emplace(idLv, InputRegister(initialValue)).second;
}

double WorkMemory::inputValue(tsize idLv) const
{
    map<tsize, InputRegister>::const_iterator iter;

    iter = _inputs.find(idLv);
    if(iter == _inputs.cend())
        throw NonExistentElementException<tsize>(idLv);

    return iter->second.value;
}

bool WorkMemory::existsInput(tsize idLv) const
{
    return _inputs.find(idLv) != _inputs.cend();
}

tsize WorkMemory::inputCount() const
{
    return _inputs.size();
}

vector<tsize> WorkMemory::inputIds() const
{
    vector<tsize> ids;

    ids.reserve(_inputs.size());
    for(map<tsize, InputRegister>::const_iterator it = _inputs.cbegin(); it != _inputs.cend(); it++)
    {
        ids.push_back(it->first);
    }

    return ids;
}

void WorkMemory::setInputValue(tsize idLv, double value)
{
    map<tsize, InputRegister>::iterator iter;

    iter = _inputs.find(idLv);

    if(iter == _inputs.end())
        throw NonExistentElementException<tsize>(idLv);

    iter->second = value;
}

void WorkMemory::removeInput(tsize idLv)
{
    _inputs.erase(idLv);
}

bool WorkMemory::addFunction(tsize idLv, tsize idMf, double initialValue)
{
    map<tsize, InputRegister>::iterator iter;

    iter = _inputs.find(idLv);
    if(iter != _inputs.end())
    {
        return iter->second.functions.emplace(idMf, initialValue).second;
    }

    return false;
}

double WorkMemory::functionValue(tsize idLv, tsize idMf) const
{
    map<tsize, InputRegister>::const_iterator inputIter;
    map<tsize, double>::const_iterator functionIter;

    inputIter = _inputs.find(idLv);

    if(inputIter == _inputs.cend())
        throw NonExistentElementException<tsize>(idLv);

    functionIter = inputIter->second.functions.find(idMf);

    if(functionIter == inputIter->second.functions.cend())
        throw NonExistentElementException< pair<tsize, tsize> >(pair<tsize, tsize>(idLv, idMf));

    return functionIter->second;
}

bool WorkMemory::existsFunction(tsize idLv, tsize idMf) const
{
    map<tsize, InputRegister>::const_iterator iter;

    iter = _inputs.find(idLv);
    if(iter != _inputs.cend())
    {
        return iter->second.functions.find(idMf) != iter->second.functions.cend();
    }

    return false;
}

int WorkMemory::functionCount(tsize idLv) const
{
    map<tsize, InputRegister>::const_iterator iter;
    int count = -1;

    iter = _inputs.find(idLv);
    if(iter != _inputs.cend())
    {
        return iter->second.functions.size();
    }

    return count;
}

vector<tsize> WorkMemory::functionIds(tsize idLv) const
{
    vector<tsize> ids;
    map<tsize, InputRegister>::const_iterator iter;

    iter = _inputs.find(idLv);
    if(iter != _inputs.cend())
    {
        ids.reserve(iter->second.functions.size());
        for(map<tsize, double>::const_iterator it = iter->second.functions.cbegin();
            it != iter->second.functions.cend(); it++)
        {
            ids.push_back(it->first);
        }
    }

    return ids;
}

void WorkMemory::setFunctionValue(tsize idLv, tsize idMf, double value)
{
    map<tsize, InputRegister>::iterator inputIter;
    map<tsize, double>::iterator functionIter;

    inputIter = _inputs.find(idLv);

    if(inputIter == _inputs.end())
        throw NonExistentElementException<tsize>(idLv);

    functionIter = inputIter->second.functions.find(idMf);

    if(functionIter == inputIter->second.functions.cend())
        throw NonExistentElementException< pair<tsize, tsize> >(pair<tsize, tsize>(idLv, idMf));

    functionIter->second = value;
}

void WorkMemory::removeFunction(tsize idLv, tsize idMf)
{
    map<tsize, InputRegister>::iterator iter;

    iter = _inputs.find(idLv);
    if(iter != _inputs.end())
    {
        iter->second.functions.erase(idMf);
    }
}

bool WorkMemory::addRule(tsize idRule, const knowledgeModule::Rule &rule, double initialValue)
{
    return _rules.emplace(idRule, RuleRegister(&rule, initialValue)).second;
}

double WorkMemory::ruleValue(tsize idRule) const
{
    map<tsize, RuleRegister>::const_iterator iter;

    iter = _rules.find(idRule);

    if(iter == _rules.cend())
        throw NonExistentElementException<tsize>(idRule);

    return iter->second.value;
}

bool WorkMemory::existsRule(tsize idRule) const
{
    return _rules.find(idRule) != _rules.cend();
}

tsize WorkMemory::ruleCount() const
{
    return _rules.size();
}

vector<tsize> WorkMemory::ruleIds() const
{
    vector<tsize> ids;

    ids.reserve(_rules.size());
    for(map<tsize, RuleRegister>::const_iterator it = _rules.cbegin(); it != _rules.cend(); it++)
    {
        ids.push_back(it->first);
    }

    return ids;
}

void WorkMemory::setRuleValue(tsize idRule, double value)
{
    map<tsize, RuleRegister>::iterator iter;

    iter = _rules.find(idRule);

    if(iter == _rules.end())
        throw NonExistentElementException<tsize>(idRule);

    iter->second.value = value;
}

void WorkMemory::removeRule(tsize idRule)
{
    _rules.erase(idRule);
}

bool WorkMemory::addOutput(tsize idLv, double initialValue)
{
    return _outputs.emplace(idLv, initialValue).second;
}

double WorkMemory::outputValue(tsize idLv) const
{
    map<tsize, double>::const_iterator iter;

    iter = _outputs.find(idLv);

    if(iter == _outputs.cend())
        throw NonExistentElementException<tsize>(idLv);

    return iter->second;
}

bool WorkMemory::existsOutput(tsize idLv) const
{
    return _outputs.find(idLv) != _outputs.cend();
}

tsize WorkMemory::outputCount() const
{
    return _outputs.size();
}

vector<tsize> WorkMemory::outputIds() const
{
    vector<tsize> ids;

    ids.reserve(_outputs.size());
    for(map<tsize, double>::const_iterator it = _outputs.cbegin(); it != _outputs.cend(); it++)
    {
        ids.push_back(it->first);
    }

    return ids;
}

void WorkMemory::setOutputValue(tsize idLv, double value)
{
    map<tsize, double>::iterator iter;

    iter = _outputs.find(idLv);

    if(iter == _outputs.end())
        throw NonExistentElementException<tsize>(idLv);

    iter->second = value;
}

void WorkMemory::removeOutput(tsize idLv)
{
    _outputs.erase(idLv);
}















