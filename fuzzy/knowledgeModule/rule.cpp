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
 * \file    rule.hpp                                            *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "rule.hpp"

/**===================*~* STL CLASSES *~*===================**/
#include <stack>
#include <iostream>

/**===================*~* OWN CLASSES *~*===================**/
#include "logicaloperator.hpp"
#include "fuzzy/exceptions/rulecompilerexception.hpp"
#include "util/stringtokenizer.hpp"
#include "knowledgebase.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;
using namespace fuzzy::exceptions;
using namespace util;

/**===================================== CONSTRUCTORS =====================================**/
//this method can throws: fuzzy::exceptions::BadInstanceException
Rule::Rule(const std::string &ruleStr, const KnowledgeBase &proprietary)
{
    try
    {
        createRule(ruleStr, proprietary);
    }
    catch(RuleCompilerException &rce)
    {
        dropRule();
        throw rce;
    }
}

Rule::Rule(const Rule &other)
{
    *this = other;
}

/**===================================== DESTRUCTOR =====================================**/
Rule::~Rule()
{
    dropRule();
}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
const string &Rule::toString() const
{
    return _ruleStr;
}

const vector<const IRulePart *> &Rule::condition() const
{
    return _condition;
}

const vector<const IRulePart*> &Rule::conclusion() const
{
    return _conclusion;
}

const vector<pair<tsize, tsize> > &Rule::dependencies(bool isInput) const
{
    return isInput ? _inputDependencies : _outputDependencies;
}

/**===================================== PRIVATE MEMBER FUNCTIONS =====================================**/
void Rule::createRule(const std::string &ruleStr, const KnowledgeBase &proprietary)
{
    string conditionStr;
    string conclusionStr;
    StringTokenizer tokens(ruleStr);

    tokens.tokenize("->");
    if(tokens.hasNext())
    {
        conditionStr = tokens.next();
        if(tokens.hasNext())
        {
            conclusionStr = tokens.next();
            compile(conditionStr, proprietary, _condition);
            compile(conclusionStr, proprietary, _conclusion, false);
        }
    }
}

void Rule::compile(const std::string &source, const KnowledgeBase &proprietary,
                   std::vector<const IRulePart *> &postfixVector, bool isInput)
{
    string::const_iterator iterator = source.cbegin();
    stack<LogicalOperator*> operatorStack;

    LogicalOperator *logicalOperator;
    int logOper;

    string temp;
    string auxStr;
    int idLv = 0;
    int idMf = 0;

    while(*iterator != '\0')
    {
        if(isOperator(*iterator))
        {
            logOper = LogicalOperator::toLogicalOperator(*iterator);
            if(logOper > -1)
            {
                if(idMf < 1)
                {
                    idMf = proprietary.idMembershipFunction(idLv, temp, isInput);
                    if(idMf > 0)
                    {
                        postfixVector.push_back(&proprietary.membershipFunction(idLv, idMf, isInput));
                        if(isInput)
                            _inputDependencies.push_back(pair<tsize, tsize>(idLv, idMf));
                        else
                            _outputDependencies.push_back(pair<tsize, tsize>(idLv, idMf));

                        idLv = -1;
                        idMf = -1;

                        logicalOperator = new LogicalOperator((LogicalOperators) logOper);

                        while(!operatorStack.empty())
                        {
                            if(operatorStack.top()->priority() > logicalOperator->priority())
                            {
                                postfixVector.push_back(operatorStack.top());
                                operatorStack.pop();
                            }
                            else
                                break;
                        }
                    }
                    else
                    {
                        throw RuleCompilerException(RuleCompilerException::UNKNOWN_MF, "indentifier: " + temp);
                    }

                    operatorStack.push(logicalOperator);
                    temp.clear();
                }
                else
                {
                    throw RuleCompilerException(RuleCompilerException::UNEXPECTED_SYMBOL,
                                                "expected: assignment operator, found: logical operator");
                }
            }
            else if(isAssignmentOperator(*iterator))
            {
                if(idLv < 1)
                {
                    idLv = proprietary.idLinguisticVariable(temp, isInput);
                    if(idLv < 1)
                    {
                        throw RuleCompilerException(RuleCompilerException::UNKNOWN_LV, "indentifier: " + temp);
                    }
                    temp.clear();
                }
                else
                {
                    throw RuleCompilerException(RuleCompilerException::UNEXPECTED_SYMBOL,
                                                "expected: logical operator, found: assignment operator");
                }
            }
            else
            {
                auxStr = "operator: ";
                auxStr.push_back(*iterator);
                throw RuleCompilerException(RuleCompilerException::INVALID_OPERATOR, auxStr);
            }
        }
        else
        {
            temp.push_back(*iterator);
        }

        iterator++;
    }

    if(idLv > 0)
    {
        if(idMf < 1)
        {
            idMf = proprietary.idMembershipFunction(idLv, temp, isInput);
            if(idMf > 0)
            {
                postfixVector.push_back(&proprietary.membershipFunction(idLv, idMf, isInput));
                if(isInput)
                    _inputDependencies.push_back(pair<tsize, tsize>(idLv, idMf));
                else
                    _outputDependencies.push_back(pair<tsize, tsize>(idLv, idMf));

                while(!operatorStack.empty())
                {
                    postfixVector.push_back(operatorStack.top());
                    operatorStack.pop();
                }
            }
            else
            {
                throw RuleCompilerException(RuleCompilerException::UNKNOWN_MF, "identifier: " + temp);
            }
        }
        else
        {
            throw RuleCompilerException(RuleCompilerException::UNEXPECTED_SYMBOL,
                                        "expected: Linguistic Variable, found: End of string");
        }
    }
    else
    {
        throw RuleCompilerException(RuleCompilerException::UNEXPECTED_SYMBOL,
                                    "expected: Assignment operator, found: End of string");
    }
}

void Rule::dropRule()
{
    const LogicalOperator *ruleOperator;

    while(!_condition.empty())
    {
        ruleOperator = dynamic_cast<const LogicalOperator*>(_condition.back());
        if(ruleOperator == NULL)
            delete ruleOperator;
        _condition.pop_back();
    }
    while(!_conclusion.empty())
    {
        ruleOperator = dynamic_cast<const LogicalOperator*>(_conclusion.back());
        if(ruleOperator == NULL)
            delete ruleOperator;
        _conclusion.pop_back();
    }

    _inputDependencies.clear();
    _outputDependencies.clear();
}












