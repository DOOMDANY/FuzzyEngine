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
    pair<map<tsize, InputRegister>::iterator, bool> inserted;

    inserted = _inputs.emplace(idLv, InputRegister(initialValue));

    return !inserted.second;
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
    pair<map<tsize, double>::iterator, bool> inserted;
    bool success = false;

    iter = _inputs.find(idLv);
    if(iter != _inputs.end())
    {
        inserted = iter->second.functions.emplace(idMf, initialValue);
        success = !inserted.second;
    }

    return success;
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

void WorkMemory::addRule(tsize idRule, const knowledgeModule::Rule &rule, double initialValue)
{

}

double WorkMemory::ruleValue(tsize idRule) const
{

}

tsize WorkMemory::ruleCount() const
{

}

vector<tsize> WorkMemory::ruleIds() const
{

}

void WorkMemory::setRuleValue(tsize idRule, double value)
{

}

void WorkMemory::removeRule(tsize idRule)
{

}

void WorkMemory::addOutput(tsize idLv, double defaultValue)
{

}

double WorkMemory::outputValue(tsize idLv) const
{

}

tsize WorkMemory::outputCount() const
{

}

vector<tsize> WorkMemory::outputIds() const
{

}

void WorkMemory::setOutputValue(tsize idLv, double value)
{

}

void WorkMemory::removeOutput(tsize idLv)
{

}















