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
 * \file    fuzzyengine.cpp                                     *
 *                                                              *
 ****************************************************************/

#include "fuzzyengine.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;

/**===================================== CONSTRUCTOR =====================================**/
FuzzyEngine::FuzzyEngine()
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

}

int FuzzyEngine::lastError() const
{

}

string FuzzyEngine::lastErrorStr() const
{

}

// >>>>>>>>>>>>>>>>>>>>>>> Knowledge Base Management
bool FuzzyEngine::createKnowledgeBase(const string &name)
{

}

const string &FuzzyEngine::knowledgeBaseName(tsize kbId) const
{

}

tsize FuzzyEngine::knowledgeBaseId(const string &name) const
{

}

tsize FuzzyEngine::linguisticVariableCount(tsize kbId) const
{

}

tsize FuzzyEngine::ruleCount(tsize kbId) const
{

}

bool FuzzyEngine::renameKnowledgeBase(tsize kbId, const string &name)
{

}

void FuzzyEngine::removeKnowledgeBase(tsize kbId)
{

}

bool FuzzyEngine::createRule(tsize kbId, const string &ruleStr)
{

}

const string &FuzzyEngine::rule(tsize kbId, tsize ruleId) const
{

}

string FuzzyEngine::condition(tsize kbId, tsize ruleId) const
{

}

string FuzzyEngine::conclusion(tsize kbId, tsize ruleId) const
{

}

bool FuzzyEngine::replaceRule(tsize kbId, tsize ruleId, const string &ruleStr)
{

}

void FuzzyEngine::removeRule(tsize kbId, tsize ruleId)
{

}

bool FuzzyEngine::createLinguisticVariable(tsize kbId, const string &name, double lowerLimit, double upperLimit,
                                           bool isInput)
{

}

const string &FuzzyEngine::linguisticVariableName(tsize kbId, tsize lvId, bool isInput) const
{

}

tsize FuzzyEngine::linguisticVariableId(tsize kbId, const string &name, bool isInput) const
{

}

tsize FuzzyEngine::membershipFunctionCount(tsize kbId, tsize lvId, bool isInput) const
{

}

double FuzzyEngine::upperLimit(tsize kbId, tsize lvId, bool isInput) const
{

}

double FuzzyEngine::lowerLimit(tsize kbId, tsize lvId, bool isInput) const
{

}

bool FuzzyEngine::renameLinguisticVariable(tsize kbId, tsize lvId, bool isInput, const string &name)
{

}

bool FuzzyEngine::setLinguisticVariableLimits(tsize kbId, tsize lvId, bool isInput, double lowerLimit,
                                              double upperLimit)
{

}

void FuzzyEngine::removeLinguisticVariable(tsize kbId, tsize lvId, bool isInput)
{

}

bool FuzzyEngine::createMembershipFunction(tsize kbId, tsize lvId, bool isInput,
                                           const string &name, const vector<double> &params, MFType type)
{

}

const string &FuzzyEngine::membershipFunctionName(tsize kbId, tsize lvId, bool isInput, tsize mfId) const
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
