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
#include "badinstanceexception.hpp"
#include "stringtokenizer.hpp"
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
    if(!createRule(ruleStr, proprietary))
        throw BadInstanceException();
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
bool Rule::createRule(const std::string &ruleStr, const KnowledgeBase &proprietary)
{
    string conditionStr;
    string conclusionStr;
    StringTokenizer tokens(ruleStr);
    bool success = false;

    tokens.tokenize("->");
    if(tokens.hasNext())
    {
        conditionStr = tokens.next();
        if(tokens.hasNext())
        {
            conclusionStr = tokens.next();
            if(compile(conditionStr, proprietary, _condition))
                success = compile(conclusionStr, proprietary, _conclusion, false);
        }
    }

    return success;
}

bool Rule::compile(const std::string &source, const KnowledgeBase &proprietary,
                   std::vector<const IRulePart *> &postfixVector, bool isInput)
{
    bool success = true;

    string::const_iterator iterator = source.cbegin();
    stack<LogicalOperator*> operatorStack;

    LogicalOperator *logicalOperator;
    int logOper;

    string temp;
    int idLv = 0;
    int idMf = 0;

    while(*iterator != '\0')
    {
        if(isOperator(*iterator))
        {
            logOper = LogicalOperator::toLogicalOperator(*iterator);
            if(logOper > -1)
            {
                cout << temp << endl;
                if(idMf < 1)
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
                        if(operatorStack.top()->priority() > logicalOperator->priority())
                        {
                            postfixVector.push_back(operatorStack.top());
                            operatorStack.pop();
                        }
                        else
                            break;
                }
                else
                {
                    success = false;
                    break;
                }

                operatorStack.push(logicalOperator);
                temp.clear();
            }
            else if(isAssignmentOperator(*iterator))
            {
                cout << temp << endl;
                if(idLv < 1)
                    idLv = proprietary.idLinguisticVariable(temp, isInput);

                if(idLv < 1)
                {
                    success = false;
                    break;
                }
                temp.clear();
            }
            else
            {
                success = false;
                break;
            }
        }
        else
            temp.push_back(*iterator);

        iterator++;
    }

    if(success)
    {
        cout << temp << endl;
        if(idMf < 1 && idLv > 0)
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
            success = false;
    }

    if(!success)
        dropRule();

    return success;
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












