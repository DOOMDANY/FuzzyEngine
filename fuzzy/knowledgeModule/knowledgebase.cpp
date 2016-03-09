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

using namespace std;
using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;

/**===================================== CONSTRUCTORS =====================================**/
KnowledgeBase::KnowledgeBase(const string &name)
{

}

/**===================================== DESTRUCTOR =====================================**/
KnowledgeBase::~KnowledgeBase()
{

}

/**===================================== SETTER & GETTER =====================================**/
void KnowledgeBase::rename(const string &name)
{

}

const string &KnowledgeBase::name() const
{

}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
bool KnowledgeBase::createRule(const vector<string> &atomList)
{

}

//this method can throws: out_of_range
const Rule &KnowledgeBase::rule(int ruleId) const
{

}

tsize KnowledgeBase::ruleCount() const
{

}

bool KnowledgeBase::replaceRule(tsize ruleId, const string &atomList)
{

}

void KnowledgeBase::RemoveRule(tsize ruleId)
{

}

bool KnowledgeBase::createLinguisticVariable(const string &name, double lowerLimit, double upperLimit, bool isInput)
{

}

//this method can throws: out_of_range
const LinguisticVariable &KnowledgeBase::linguisticVariable(tsize lvId, bool isInput) const
{

}

int KnowledgeBase::linguisticVariableId(const string &name, bool isInput) const
{

}

tsize KnowledgeBase::linguisticVariableCount(bool isInput) const
{

}

bool KnowledgeBase::renameLinguisticVariable(tsize lvId, bool isInput, const string &name)
{

}

bool KnowledgeBase::setLinguisticVariableLimits(int lvId, bool isInput, double lowerLimit, double upperLimit)
{

}

void KnowledgeBase::removeLinguisticVariable(tsize lvId, bool isInput)
{

}

bool KnowledgeBase::createMembershipFunction(tsize lvId, const string &name, MFType type, const vector<double> &params,
                                             bool isInput)
{

}

bool KnowledgeBase::createMembershipFunction(tsize lvId, const string &name, const string &expression, bool isInput)
{

}

const MembershipFunction &KnowledgeBase::membershipFunction(tsize lvId, int mfId, bool isInput) const
{

}

int KnowledgeBase::membershipFunctionId(tsize lvId, const string &name, bool isInput) const
{

}

//this method can throws: out_of_range
tsize KnowledgeBase::membershipFunctionCount(tsize lvId, bool isInput) const
{

}

bool KnowledgeBase::renameMembershipFunction(tsize lvId, tsize mfId, bool isInput, const string &name)
{

}

bool KnowledgeBase::setMembershipFunctionParameters(tsize lvId, tsize mfId, bool isInput, const vector<double> &params)
{

}

bool KnowledgeBase::setMembershipFunctionType(tsize lvId, bool isInput, tsize mfId, MFType type)
{

}

void KnowledgeBase::RemoveMembershipFunction(tsize lvId, tsize mfId, bool isInput)
{

}









