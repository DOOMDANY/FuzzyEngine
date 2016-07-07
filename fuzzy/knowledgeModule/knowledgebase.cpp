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
#include "fuzzy/exceptions/commonexception.hpp"

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
void KnowledgeBase::createRule(const string &ruleStr)
{
    if(_rules.empty())
    {
        _rules.insert(pair<tsize, Rule>(1u, Rule(ruleStr, *this)));
    }
    else
        _rules.insert(pair<tsize, Rule>(_rules.crbegin()->first + 1u, Rule(ruleStr, *this)));
}

const Rule &KnowledgeBase::rule(tsize idRule) const
{
    map<tsize, Rule>::const_iterator it;

    it = _rules.find(idRule);
    if(it == _rules.cend())
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);
    else
        return it->second;
}

const map<tsize, Rule> &KnowledgeBase::rules() const
{
    return _rules;
}

tsize KnowledgeBase::ruleCount() const
{
    return _rules.size();
}

vector<tsize> KnowledgeBase::ruleIds() const
{
    vector<tsize> ids;

    ids.reserve(_rules.size());
    for(map<tsize, Rule>::const_iterator it = _rules.cbegin(); it != _rules.end(); it++)
    {
        ids.push_back(it->first);
    }

    return ids;
}

void KnowledgeBase::replaceRule(tsize idRule, const string &ruleStr)
{
    map<tsize, Rule>::iterator it;

    it = _rules.find(idRule);
    if(it != _rules.end())
    {
        it->second = Rule(ruleStr, *this);
    }
}

void KnowledgeBase::removeRule(tsize idRule)
{
    _rules.erase(idRule);
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Linguistic Variables Management
void KnowledgeBase::createLinguisticVariable(const string &name, double lowerLimit, double upperLimit, bool isInput)
{
    map<tsize, LinguisticVariable> &variables = isInput ? _inputs : _outputs;

    if(variables.empty())
    {
        variables.insert(pair<tsize, LinguisticVariable>(1u, LinguisticVariable(name, lowerLimit, upperLimit)));
    }
    else
    {
        if(idLinguisticVariable(name, isInput) >= 0)
        {
            throw(CommonException(CommonException::DUPLICATED_ITEM));
        }
        else
        {
            variables.insert(pair<tsize, LinguisticVariable>(variables.crbegin()->first + 1u,
                                                             LinguisticVariable(name, lowerLimit, upperLimit)));
        }
    }
}

const LinguisticVariable &KnowledgeBase::linguisticVariable(tsize idLv, bool isInput) const
{
    map<tsize, LinguisticVariable>::const_iterator it;
    map<tsize, LinguisticVariable>::const_iterator end;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.cend() : _outputs.cend();
    if(it == end)
    {
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);
    }
    else
    {
        return it->second;
    }
}

const map<tsize, LinguisticVariable> &KnowledgeBase::linguisticVariables(bool isInput) const
{
    if(isInput)
        return _inputs;
    return _outputs;
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
        {
            return it->first;
        }
        it++;
    }

    return -1;
}

tsize KnowledgeBase::linguisticVariableCount(bool isInput) const
{
    return isInput ? _inputs.size() : _outputs.size();
}

void KnowledgeBase::renameLinguisticVariable(const string &name, tsize idLv, bool isInput)
{
    map<tsize, LinguisticVariable>::iterator it;
    map<tsize, LinguisticVariable>::iterator end;

    int idAux;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.end(): _outputs.end();

    if(it != end)
    {
        if(it->second.name() == name)
        {
            it->second.rename(name);
        }
        else
        {
            idAux = idLinguisticVariable(name, isInput);

            if(idAux == -1)
            {
                it->second.rename(name);
            }
            else
            {
                throw CommonException(CommonException::DUPLICATED_ITEM);
            }
        }
    }
    else
    {
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);
    }
}

void KnowledgeBase::setLinguisticVariableLimits(double lowerLimit, double upperLimit, int idLv, bool isInput)
{
    map<tsize, LinguisticVariable>::iterator it;
    map<tsize, LinguisticVariable>::iterator end;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.end(): _outputs.end();

    if(it != end)
    {
        it->second.setLimits(lowerLimit, upperLimit);
    }
    else
    {
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);
    }
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
            {
                flag = false;
            }

            dependenciesIt++;
        }

        if(flag)
        {
            rulesIt++;
        }
        else
        {
            rulesIt = _rules.erase(rulesIt);
        }
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

//this method can throws: fuzzy::exceptions::CommonException(CommonException::NON_EXISTENT_ELEMENT)
const MembershipFunction &KnowledgeBase::membershipFunction(tsize idLv, tsize idMf, bool isInput) const
{
    map<tsize, LinguisticVariable>::const_iterator it;
    map<tsize, LinguisticVariable>::const_iterator end;

    it = isInput ? _inputs.find(idLv) : _outputs.find(idLv);
    end = isInput ? _inputs.cend() : _outputs.cend();

    if(it != end)
    {
        return it->second.membershipFunction(idMf);
    }

    throw CommonException(CommonException::NON_EXISTENT_ELEMENT);
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












