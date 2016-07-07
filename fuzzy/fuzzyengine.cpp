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
 * \file    fuzzyengine.cpp                                     *
 *                                                              *
 ****************************************************************/

#include "fuzzyengine.hpp"

#include "fuzzy/exceptions/rulecompilerexception.hpp"
#include "exceptions/commonexception.hpp"
#include "fuzzy/knowledgeModule/memberFunctions/mfexception.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::exceptions;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;

string FuzzyEngine::errorStr[] = {
    "OK: No error detected",
    "KB_NOT_FOUND: Knowledge Base not found",
    "LV_NOT_FOUND: Linguistic Variable not found",
    "MF_NOT_FOUND: Membership Funtion not found",
    "RULE_NOT_FOUND: Rule not found",
    "REPEATED_NAME: The requested name already exists",
    "BAD_PARAMS: One or more parameters are wrong",
    "BAD_LIMITS: Lower limit is greater than upper",
    "BAD_ALLOC: Some object cannot be allocated",
    "INVALID_RULE_FORMAT: The rule compiler has detected an error",
    "OUT_OF_RANGE: Some value is out of range",
    "BAD_CONFIG: The configuration is not valid",
    "CONCURRENCY_ERROR",
    "UNKNOWN_ERROR: Error detected but not identified"
};

/**===================================== CONSTRUCTORS =====================================**/
FuzzyEngine::FuzzyEngine() :
    _lastError(OK)
{

}

/**===================================== DESTRUCTOR =====================================**/
FuzzyEngine::~FuzzyEngine()
{

}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    // >>>>>>>>>>>>>>>>>>>>>>> FuzzyEngine Management
void FuzzyEngine::resetState()
{
    _lastError = OK;
}

int FuzzyEngine::lastError() const
{
    return _lastError;
}

string FuzzyEngine::lastErrorStr() const
{
    return errorStr[_lastError];
}

    // >>>>>>>>>>>>>>>>>>>>>>> Knowledge Base Management
        // ----------------------- Knowledge Bases
bool FuzzyEngine::createKnowledgeBase(const string &name)
{
    _lastError = OK;
    if(_knowledgeBases.empty())
    {
        _knowledgeBases.emplace(1u, KnowledgeBase(name));
    }
    else
    {
        if(idKnowledgeBase(name) > 0)
        {
            _lastError = REPEATED_NAME;
        }
        else
        {
            _knowledgeBases.emplace(_knowledgeBases.crbegin()->first + 1u, KnowledgeBase(name));
        }
    }

    return _lastError == OK;
}

string FuzzyEngine::knowledgeBaseName(tsize idKb) const
{
    map<tsize, KnowledgeBase>::const_iterator it;

    it = _knowledgeBases.find(idKb);
    if(it == _knowledgeBases.cend())
    {
        return "";
    }

    return it->second.name();
}

int FuzzyEngine::idKnowledgeBase(const string &name) const
{
    map<tsize, KnowledgeBase>::const_iterator it;
    map<tsize, KnowledgeBase>::const_iterator end;

    it = _knowledgeBases.cbegin();
    end = _knowledgeBases.cend();

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

tsize FuzzyEngine::linguisticVariableCount(tsize idKb, bool isInput) const
{
    map<tsize, KnowledgeBase>::const_iterator it;

    it = _knowledgeBases.find(idKb);
    if(it == _knowledgeBases.cend())
    {
        return 0u;
    }

    return it->second.linguisticVariableCount(isInput);
}

tsize FuzzyEngine::ruleCount(tsize idKb) const
{
    map<tsize, KnowledgeBase>::const_iterator it;

    it = _knowledgeBases.find(idKb);
    if(it == _knowledgeBases.cend())
    {
        return 0u;
    }

    return it->second.ruleCount();
}

bool FuzzyEngine::renameKnowledgeBase(tsize idKb, const string &name)
{
    map<tsize, KnowledgeBase>::iterator it;

    _lastError = OK;
    it = _knowledgeBases.find(idKb);
    if(it == _knowledgeBases.end())
    {
        _lastError = KB_NOT_FOUND;
    }
    else if(it->second.name() != name)
    {
        if(idKnowledgeBase(name) > 0)
        {
            _lastError = REPEATED_NAME;
        }
        else
        {
            it->second.rename(name);
        }
    }

    return _lastError == OK;
}

void FuzzyEngine::removeKnowledgeBase(tsize idKb)
{
    _knowledgeBases.erase(idKb);
}

        // ----------------------- Rules
bool FuzzyEngine::createRule(tsize idKb, const string &ruleStr)
{
    KnowledgeBase *kb = findKnowledgeBase(idKb);
    bool success = false;

    if(kb != NULL)
    {
        try
        {
            kb->createRule(ruleStr);
            success = true;
        }
        catch(RuleCompilerException &rce)
        {
            _lastError = INVALID_RULE_FORMAT;
        }
        catch(...)
        {
            _lastError = UNKNOWN_ERROR;
        }
    }

    return success;
}

string FuzzyEngine::rule(tsize idKb, tsize idRule) const
{
    Rule *rule = findRule(idKb, idRule);

    if(rule == NULL)
    {
        return "";
    }
    return rule->toString();
}

bool FuzzyEngine::replaceRule(tsize idKb, tsize idRule, const string &ruleStr)
{
    KnowledgeBase *kb = findKnowledgeBase(idKb);
    map<tsize, Rule>::const_iterator it;

    Rule *rule;
    bool success = false;

    if(kb != NULL)
    {
        try
        {
            it = kb->rules().find(idRule);
            if(it != kb->rules().cend())
            {
                rule = const_cast<Rule*>(&it->second);
                *rule = Rule(ruleStr, *kb);
                success = true;
            }
            else
            {
                _lastError = RULE_NOT_FOUND;
            }
        }
        catch(RuleCompilerException &rce)
        {
            _lastError = INVALID_RULE_FORMAT;
        }
        catch(...)
        {
            _lastError = UNKNOWN_ERROR;
        }
    }

    return success;
}

void FuzzyEngine::removeRule(tsize idKb, tsize idRule)
{
    KnowledgeBase *kb = findKnowledgeBase(idKb);

    if(kb != NULL)
    {
        kb->removeRule(idRule);
    }
}

        // ----------------------- Linguistic Variables
bool FuzzyEngine::createLinguisticVariable(tsize idKb, const string &name, double lowerLimit, double upperLimit,
                                           bool isInput)
{
    KnowledgeBase *kb = findKnowledgeBase(idKb);
    bool success = false;

    if(kb != NULL)
    {
        try
        {
            kb->createLinguisticVariable(name, lowerLimit, upperLimit, isInput);
            success = true;
            _lastError = OK;
        }
        catch(out_of_range &)
        {
            _lastError = BAD_LIMITS;
        }
        catch(CommonException &ce)
        {
            if(ce.type() == CommonException::DUPLICATED_ITEM)
            {
                _lastError = REPEATED_NAME;
            }
            else
            {
                _lastError = UNKNOWN_ERROR;
            }
        }
        catch(...)
        {
            _lastError = UNKNOWN_ERROR;
        }
    }

    return success;
}

string FuzzyEngine::linguisticVariableName(tsize idKb, tsize idLv, bool isInput) const
{
    LinguisticVariable *lv = findLinguisticVariable(idKb, idLv, isInput);

    if(lv != NULL)
    {
        _lastError = OK;
        return lv->name();
    }

    return "";
}

int FuzzyEngine::idLinguisticVariable(tsize idKb, const string &name, bool isInput) const
{
    KnowledgeBase *kb = findKnowledgeBase(idKb);
    int idLv = -1;

    if(kb != NULL)
    {
        idLv = kb->idLinguisticVariable(name, isInput);
        if(idLv > -1)
        {
            _lastError = LV_NOT_FOUND;
        }
        else
        {
            _lastError = OK;
        }
    }

    return idLv;
}

tsize FuzzyEngine::membershipFunctionCount(tsize idKb, tsize idLv, bool isInput) const
{
    LinguisticVariable *lv = findLinguisticVariable(idKb, idLv, isInput);

    if(lv != NULL)
    {
        _lastError = OK;
        return lv->membershipFunctionCount();
    }

    return 0u;
}

double FuzzyEngine::upperLimit(tsize idKb, tsize idLv, bool isInput) const
{
    LinguisticVariable *lv = findLinguisticVariable(idKb, idLv, isInput);

    if(lv == NULL)
    {
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);
    }
    _lastError = OK;

    return lv->upperLimit();
}

double FuzzyEngine::lowerLimit(tsize idKb, tsize idLv, bool isInput) const
{
    LinguisticVariable *lv = findLinguisticVariable(idKb, idLv, isInput);

    if(lv == NULL)
    {
        throw CommonException(CommonException::NON_EXISTENT_ELEMENT);
    }
    _lastError = OK;

    return lv->lowerLimit();
}

bool FuzzyEngine::renameLinguisticVariable(tsize idKb, tsize idLv, bool isInput, const string &name)
{
    KnowledgeBase *kb = findKnowledgeBase(idKb);

    if(kb != NULL)
    {
        try
        {
            kb->renameLinguisticVariable(name, idLv, isInput);
            _lastError = OK;
            return true;
        }
        catch(CommonException &ce)
        {
            if(ce.type() == CommonException::DUPLICATED_ITEM)
            {
                _lastError = REPEATED_NAME;
            }
            else if(ce.type() == CommonException::NON_EXISTENT_ELEMENT)
            {
                _lastError = LV_NOT_FOUND;
            }
            else
            {
                _lastError = UNKNOWN_ERROR;
            }
        }
        catch(...)
        {
            _lastError = UNKNOWN_ERROR;
        }
    }

    return false;
}

bool FuzzyEngine::setLinguisticVariableLimits(tsize idKb, tsize idLv, bool isInput,
                                              double lowerLimit, double upperLimit)
{
    KnowledgeBase *kb = findKnowledgeBase(idKb);

    if(kb != NULL)
    {
        try
        {
            kb->setLinguisticVariableLimits(lowerLimit, upperLimit, idLv, isInput);
            _lastError = OK;
            return true;
        }
        catch(CommonException &ce)
        {
            if(ce.type() == CommonException::NON_EXISTENT_ELEMENT)
            {
                _lastError = LV_NOT_FOUND;
            }
            else
            {
                _lastError = UNKNOWN_ERROR;
            }
        }
        catch(out_of_range &)
        {
            _lastError = BAD_LIMITS;
        }
        catch(...)
        {
            _lastError = UNKNOWN_ERROR;
        }
    }

    return false;
}

void FuzzyEngine::removeLinguisticVariable(tsize idKb, tsize idLv, bool isInput)
{
    KnowledgeBase *kb = findKnowledgeBase(idKb);

    if(kb != NULL)
    {
        kb->removeLinguisticVariable(idLv, isInput);
    }
}

        // ----------------------- Membership Functions
bool FuzzyEngine::createMembershipFunction(tsize idKb, tsize idLv, bool isInput,
                                           const string &name, const double *params, MFType type)
{
    LinguisticVariable *lv = findLinguisticVariable(idKb, idLv, isInput);

    if(lv != NULL)
    {
        try
        {
            lv->createMembershipFunction(name, params, type);
            _lastError = OK;
            return true;
        }
        catch(MFException &mfe)
        {
            if(mfe.stateCode() == MFException::BAD_PARAMS)
            {
                _lastError = BAD_PARAMS;
            }
            else
            {
                _lastError = INVALID_MF;
            }
        }
        catch(CommonException &ce)
        {
            if(ce.type() == CommonException::DUPLICATED_ITEM)
            {
                _lastError = REPEATED_NAME;
            }
            else
            {
                _lastError = UNKNOWN_ERROR;
            }
        }
        catch(bad_alloc &)
        {
            _lastError = BAD_ALLOC;
        }
        catch(...)
        {
            _lastError = UNKNOWN_ERROR;
        }
    }

    return false;
}

const string &FuzzyEngine::membershipFunctionName(tsize idKb, tsize idLv, bool isInput, tsize idMf) const
{

}

tsize FuzzyEngine::membershipFunctionId(tsize kbId, tsize lvId, bool isInput, const string &name) const
{

}

const vector<double> &FuzzyEngine::parameters(tsize kbId, tsize lvId, bool isInput, tsize mfId) const
{

}

tsize FuzzyEngine::parameterCount(tsize kbId, tsize lvId, bool isInput, tsize mfId) const
{

}

MFType FuzzyEngine::membershipFunctionType(tsize kbId, tsize lvId, bool isInput, tsize mfId) const
{

}

bool FuzzyEngine::renameMembershipFunction(tsize kbId, tsize lvId, bool isInput, tsize mfId, const string &name)
{

}

bool FuzzyEngine::setMembershipFunctionParameters(tsize kbId, tsize lvId, bool isInput, tsize mfId,
                                                  const vector<double> &params)
{

}

bool FuzzyEngine::setMembershipFunctionType(tsize kbId, tsize lvId, bool isInput, tsize mfId, MFType type)
{

}

void FuzzyEngine::removeMembershipFunction(tsize kbId, tsize lvId, bool isInput, tsize mfId)
{

}

    // >>>>>>>>>>>>>>>>>>>>>>> Work Memory Management
double FuzzyEngine::output(tsize kbId, tsize lvId) const
{

}

double FuzzyEngine::input(tsize kbId, tsize lvId) const
{

}

const string &FuzzyEngine::inputStr(tsize kbId, tsize lvId) const
{

}

bool FuzzyEngine::setInput(tsize kbId, tsize lvId, double grade)
{

}

bool FuzzyEngine::setInput(tsize kbId, tsize lvId, const string &membershipFunctionName)
{

}

    // >>>>>>>>>>>>>>>>>>>>>>> Inference Engine Management
bool FuzzyEngine::setDefuzzifyMethod()
{

}

bool FuzzyEngine::setLogicalOperation()
{

}

/**===================================== PRIVATE MEMBER FUNCTIONS =====================================**/
KnowledgeBase *FuzzyEngine::findKnowledgeBase(tsize idKb) const
{
    map<tsize, KnowledgeBase>::iterator it;

    it = _knowledgeBases.find(idKb);
    if(it == _knowledgeBases.cend())
    {
        _lastError = KB_NOT_FOUND;
        return NULL;
    }

    return &it->second;
}

Rule *FuzzyEngine::findRule(tsize idKb, tsize idRule) const
{
    KnowledgeBase *kb = findKnowledgeBase(idKb);
    map<tsize, Rule>::const_iterator it;

    if(kb == NULL)
    {
        return NULL;
    }

    it = kb->rules().find(idRule);
    if(it == kb->rules().cend())
    {
        _lastError = RULE_NOT_FOUND;
        return NULL;
    }

    return const_cast<Rule*>(&it->second);
}

LinguisticVariable *FuzzyEngine::findLinguisticVariable(tsize idKb, tsize idLv, bool isInput) const
{
    KnowledgeBase *kb = findKnowledgeBase(idKb);
    map<tsize, LinguisticVariable>::const_iterator it;

    if(kb == NULL)
    {
        return NULL;
    }

    it = kb->linguisticVariables(isInput).find(idLv);
    if(it == kb->linguisticVariables(isInput).cend())
    {
        _lastError = LV_NOT_FOUND;
        return NULL;
    }

    return const_cast<LinguisticVariable*>(&it->second);
}

MembershipFunction *FuzzyEngine::findMembershipFunction(tsize idKb, tsize idLv, tsize idMf, bool isInput) const
{
    LinguisticVariable *lv = findLinguisticVariable(idKb, idLv, isInput);
    map<tsize, MembershipFunction>::const_iterator it;

    if(lv == NULL)
    {
        return NULL;
    }

    it = lv->membershipFunctions().find(idMf);
    if(it == lv->membershipFunctions().cend())
    {
        _lastError = MF_NOT_FOUND;
        return NULL;
    }

    return const_cast<MembershipFunction*>(&it->second);
}












