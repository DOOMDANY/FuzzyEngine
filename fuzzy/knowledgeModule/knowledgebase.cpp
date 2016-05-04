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
 * \file    knowledgebase.cpp                                   *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "knowledgebase.hpp"

/**===================*~* STL CLASSES *~*===================**/
#include <vector>

/**===================*~* OWN CLASSES *~*===================**/
#include "rule.hpp"
#include "badinstanceexception.hpp"
#include "duplicateditemexception.hpp"
#include "nonexistentelementexception.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;
using namespace fuzzy::exceptions;

/**===================================== CONSTRUCTORS =====================================**/
KnowledgeBase::KnowledgeBase(const string &name) :
    _name(name)
{

}

/**===================================== DESTRUCTOR =====================================**/
KnowledgeBase::~KnowledgeBase()
{

}

/**===================================== SETTER & GETTER =====================================**/
void KnowledgeBase::rename(const string &name)
{
    _name = name;
}

const string &KnowledgeBase::name() const
{
    return _name;
}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Rules Management
bool KnowledgeBase::createRule(const string &ruleStr)
{
    try
    {
        if(_rules.empty())
        {
            _rules.insert(pair<tsize, Rule>(1u, Rule(ruleStr, *this)));
        }
        else
            _rules.insert(pair<tsize, Rule>(_rules.crbegin()->first + 1u, Rule(ruleStr, *this)));
    }
    catch(...)
    {
        return false;
    }

    return true;
}

//this method can throws: fuzzy::exceptions::NonExistentElementException<tsize>
const Rule &KnowledgeBase::rule(tsize idRule) const
{
    map<tsize, Rule>::const_iterator it;

    it = _rules.find(idRule);
    if(it == _rules.cend())
        throw NonExistentElementException<tsize>(idRule);
    else
        return it->second;
}

tsize KnowledgeBase::ruleCount() const
{
    return _rules.size();
}

bool KnowledgeBase::replaceRule(tsize idRule, const string &ruleStr)
{
    map<tsize, Rule>::iterator it;
    bool success = false;

    it = _rules.find(idRule);
    if(it != _rules.end())
        try
        {
            it->second = Rule(ruleStr, *this);
            success = true;
        }
        catch(...){}

    return success;
}

void KnowledgeBase::removeRule(tsize idRule)
{
    _rules.erase(idRule);
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Linguistic Variables Management
bool KnowledgeBase::createLinguisticVariable(const string &name, double lowerLimit, double upperLimit, bool isInput)
{
    map<tsize, LinguisticVariable> &variables = isInput ? _inputs : _outputs;
    bool success = true;

    try
    {
        if(variables.empty())
            variables.insert(pair<tsize, LinguisticVariable>
                             (1u, LinguisticVariable(name, lowerLimit, upperLimit)));
        else
        {
            if(idLinguisticVariable(name, isInput) >= 0)
                throw(DuplicatedItemException("The new Linguistic Variable name already exists"));
            else
                variables.insert(pair<tsize, LinguisticVariable>
                                 (variables.crbegin()->first + 1u, LinguisticVariable(name, lowerLimit, upperLimit)));
        }
    }
    catch(...){success = false;}

    return success;
}

//this method can throws: fuzzy::exceptions::NonExistentElementException<tsize>
const LinguisticVariable &KnowledgeBase::linguisticVariable(tsize idLv, bool isInput) const
{
    map<tsize, LinguisticVariable>::const_iterator it;
    map<tsize, LinguisticVariable>::const_iterator end;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.cend() : _outputs.cend();
    if(it == end)
        throw NonExistentElementException<tsize>(idLv);
    else
        return it->second;
}

int KnowledgeBase::idLinguisticVariable(const string &name, bool isInput) const
{
    map<tsize, LinguisticVariable>::const_iterator it;
    map<tsize, LinguisticVariable>::const_iterator end;

    it = isInput ? _inputs.cbegin() : _outputs.cbegin();
    end = isInput ? _inputs.cend() : _outputs.cend();

    while(it != end)
    {
        if(it->second.name() == name)
            return it->first;
        it++;
    }

    return -1;
}

tsize KnowledgeBase::linguisticVariableCount(bool isInput) const
{
    return isInput ? _inputs.size() : _outputs.size();
}

bool KnowledgeBase::renameLinguisticVariable(const string &name, tsize idLv, bool isInput)
{
    map<tsize, LinguisticVariable>::iterator it;
    map<tsize, LinguisticVariable>::iterator end;
    bool success = false;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.end(): _outputs.end();

    if(it != end)
    {
        it->second.rename(name);
        success = true;
    }

    return success;
}

bool KnowledgeBase::setLinguisticVariableLimits(double lowerLimit, double upperLimit, int idLv, bool isInput)
{
    map<tsize, LinguisticVariable>::iterator it;
    map<tsize, LinguisticVariable>::iterator end;
    bool success = false;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.end(): _outputs.end();

    if(it != end)
    {
        try
        {
            it->second.setLimits(lowerLimit, upperLimit);
            success = true;
        }
        catch(...){}
    }

    return success;
}

void KnowledgeBase::removeLinguisticVariable(tsize idLv, bool isInput)
{
    map<tsize, Rule>::iterator rulesIt = _rules.begin();
    vector< pair<tsize, tsize> >::const_iterator dependenciesIt;
    bool flag;

    while(rulesIt != _rules.end())
    {
        dependenciesIt = rulesIt->second.dependencies(isInput).cbegin();
        flag = true;
        while(flag && dependenciesIt != rulesIt->second.dependencies(isInput).cend())
        {
            if(dependenciesIt->first == idLv)
                flag = false;

            dependenciesIt++;
        }

        if(flag)
            rulesIt++;
        else
            rulesIt = _rules.erase(rulesIt);
    }

    isInput ? _inputs.erase(idLv) : _outputs.erase(idLv);
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Membership Functions Management
bool KnowledgeBase::createMembershipFunction(const string &name, MFType type, const double *params, tsize idLv,
                                             bool isInput)
{
    map<tsize, LinguisticVariable>::iterator it;
    map<tsize, LinguisticVariable>::iterator end;
    bool success = false;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.end() : _outputs.end();

    if(it != end)
        try
        {
            it->second.createMembershipFunction(name, params, type);
            success = true;
        }
        catch(...){}

    return success;
}

bool KnowledgeBase::createMembershipFunction(const string &name, const string &expression, tsize idLv, bool isInput)
{
    map<tsize, LinguisticVariable>::iterator it;
    map<tsize, LinguisticVariable>::iterator end;
    bool success = false;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.end() : _outputs.end();

    if(it != end)
        try
        {
            it->second.createMembershipFunction(name, expression);
            success = true;
        }
        catch(...){}

    return success;
}

//this method can throws: fuzzy::exceptions::NonExistentElementException< vector<tsize> >
const MembershipFunction &KnowledgeBase::membershipFunction(tsize idLv, tsize idMf, bool isInput) const
{
    map<tsize, LinguisticVariable>::const_iterator it;
    map<tsize, LinguisticVariable>::const_iterator end;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.cend() : _outputs.cend();

    if(it != end)
    {
        try
        {
            return it->second.membershipFunction(idMf);
        }
        catch(NonExistentElementException<tsize> &e)
        {
            throw NonExistentElementException< vector<tsize> >(vector<tsize>({idLv, idMf}));
        }
    }
    else
        throw NonExistentElementException< vector<tsize> >(vector<tsize>({idLv, idMf}));
}

int KnowledgeBase::idMembershipFunction(tsize idLv, const string &name, bool isInput) const
{
    map<tsize, LinguisticVariable>::const_iterator it;
    map<tsize, LinguisticVariable>::const_iterator end;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.cend() : _outputs.cend();

    if(it != end)
    {
        try
        {
            return it->second.idMembershipFunction(name);
        }
        catch(...){}
    }

    return -1;
}

tsize KnowledgeBase::membershipFunctionCount(tsize idLv, bool isInput) const
{
    map<tsize, LinguisticVariable>::const_iterator it;
    map<tsize, LinguisticVariable>::const_iterator end;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.cend() : _outputs.cend();

    if(it != end)
    {
        try
        {
            return it->second.membershipFunctionCount();
        }
        catch(...){}
    }

    return 0;
}

bool KnowledgeBase::renameMembershipFunction(const string &name, tsize idLv, tsize idMf, bool isInput)
{
    map<tsize, LinguisticVariable>::iterator it;
    map<tsize, LinguisticVariable>::iterator end;
    bool success = false;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.end() : _outputs.end();

    if(it != end)
    {
        try
        {
            it->second.membershipFunction(idMf).rename(name);
            success = true;
        }
        catch(...){}
    }

    return success;
}

bool KnowledgeBase::setMembershipFunctionParameters(const double *params, tsize idLv, tsize idMf, bool isInput)
{
    map<tsize, LinguisticVariable>::iterator it;
    map<tsize, LinguisticVariable>::iterator end;
    bool success = false;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.end() : _outputs.end();

    if(it != end)
    {
        try
        {
            it->second.membershipFunction(idMf).setParameters(params);
            success = true;
        }
        catch(...){}
    }

    return success;
}

bool KnowledgeBase::setMembershipFunctionExpression(const string &expression, tsize idLv, tsize idMf, bool isInput)
{
    map<tsize, LinguisticVariable>::iterator it;
    map<tsize, LinguisticVariable>::iterator end;
    bool success = false;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.end() : _outputs.end();

    if(it != end)
    {
        try
        {
            it->second.membershipFunction(idMf).setExpression(expression);
            success = true;
        }
        catch(...){}
    }

    return success;
}

bool KnowledgeBase::setMembershipFunctionType(MFType type, const double *params, tsize idLv, tsize idMf, bool isInput)
{
    map<tsize, LinguisticVariable>::iterator it;
    map<tsize, LinguisticVariable>::iterator end;
    bool success = false;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.end() : _outputs.end();

    if(it != end)
    {
        try
        {
            it->second.membershipFunction(idMf).setType(type, params);
            success = true;
        }
        catch(...){}//modificar para almacenar como ultimo error el error generado en este catch
    }

    return success;
}

void KnowledgeBase::removeMembershipFunction(tsize idLv, tsize idMf, bool isInput)
{
    map<tsize, Rule>::iterator rulesIt = _rules.begin();
    vector< pair<tsize, tsize> >::const_iterator dependenciesIt;
    bool flag;

    map<tsize, LinguisticVariable>::iterator it;
    map<tsize, LinguisticVariable>::iterator end;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.end() : _outputs.end();

    if(it != end)
    {
        while(rulesIt != _rules.end())
        {
            dependenciesIt = rulesIt->second.dependencies(isInput).cbegin();
            flag = true;
            while(flag && dependenciesIt != rulesIt->second.dependencies(isInput).cend())
            {
                if(dependenciesIt->first == idLv)
                    if(dependenciesIt->second == idMf)
                        flag = false;

                dependenciesIt++;
            }

            if(flag)
                rulesIt++;
            else
                rulesIt = _rules.erase(rulesIt);
        }

        it->second.removeMembershipFunction(idMf);
    }
}












