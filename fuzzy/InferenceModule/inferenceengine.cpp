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
 * \file    inferenceengine.cpp                                 *
 *                                                              *
 ****************************************************************/

/**===================*~* Class Definition *~*===================**/
#include "inferenceengine.hpp"

/**===================*~* Class Definition *~*===================**/
#include <stack>

/**===================*~* Own Classes *~*===================**/
#include "fuzzy/knowledgeModule/logicaloperator.hpp"
#include "fuzzy/exceptions/commonexception.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::inferenceModule;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;
using namespace fuzzy::memoryModule;
using namespace fuzzy::exceptions;

/**===================*~* CONSTRUCTORS *~*===================**/
InferenceEngine::InferenceEngine(const knowledgeModule::KnowledgeBase *kb, memoryModule::WorkMemory *memory) :
    _kb(kb),
    _memory(memory)
{
    if(kb == NULL || memory == NULL)
    {
        throw CommonException(CommonException::NULL_POINTER);
    }
}

/**===================*~* DESTRUCTOR *~*===================**/
InferenceEngine::~InferenceEngine()
{

}

/**===================*~* SETTER & GETTER *~*===================**/
bool InferenceEngine::setKnowledgeBase(const KnowledgeBase *kb)
{
    if(kb == NULL)
    {
        return false;
    }

    _kb = kb;
    return true;
}

const KnowledgeBase *InferenceEngine::knowledgeBase() const
{
    return _kb;
}

bool InferenceEngine::setWorkMemory(WorkMemory *memory)
{
    if(memory == NULL)
    {
        return false;
    }

    _memory = memory;
    return true;
}

const WorkMemory *InferenceEngine::workMemory() const
{
    return _memory;
}

bool InferenceEngine::setAndFunction(LogicalFunctions functionType)
{
    if(functionType != LogicalFunctions::AVERAGE &&
            functionType != LogicalFunctions::CUSTOM &&
            functionType != LogicalFunctions::DIFFERENCE &&
            functionType != LogicalFunctions::MAXIMUM &&
            functionType != LogicalFunctions::MINIMUM)
    {
        return false;
    }

    _andFunction = functionType;
    return true;
}

int InferenceEngine::andFunction() const
{
    return _andFunction;
}

bool InferenceEngine::setOrFunction(LogicalFunctions functionType)
{
    if(functionType != LogicalFunctions::AVERAGE &&
            functionType != LogicalFunctions::CUSTOM &&
            functionType != LogicalFunctions::DIFFERENCE &&
            functionType != LogicalFunctions::MAXIMUM &&
            functionType != LogicalFunctions::MINIMUM)
    {
        return false;
    }

    _orFunction = functionType;
    return true;
}

int InferenceEngine::orFunction() const
{
    return _orFunction;
}

bool InferenceEngine::setNotFunction(LogicalFunctions functionType)
{
    if(functionType != LogicalFunctions::COMPLEMENT &&
            functionType != LogicalFunctions::CUSTOM)
    {
        return false;
    }

    _notFunction = functionType;
    return true;
}

int InferenceEngine::notFunction() const
{
    return _notFunction;
}

bool InferenceEngine::setXorFunction(LogicalFunctions functionType)
{
    if(functionType != LogicalFunctions::AVERAGE &&
            functionType != LogicalFunctions::CUSTOM &&
            functionType != LogicalFunctions::DIFFERENCE &&
            functionType != LogicalFunctions::MAXIMUM &&
            functionType != LogicalFunctions::MINIMUM)
    {
        return false;
    }

    _xorFunction = functionType;
    return true;
}

int InferenceEngine::xorFunction() const
{
    return _xorFunction;
}

int InferenceEngine::lastError() const
{
    return _lastError;
}

/**===================*~* PUBLIC MEMBER FUNCTIONS *~*===================**/
void InferenceEngine::fuzzify()
{
    const MembershipFunction *mf;
    const LogicalOperator *oper;

    stack<double> evalStack;
    double temp;

    for(map<tsize, Rule>::const_iterator it = _kb->rules().cbegin(); it != _kb->rules().cend(); it++)
    {
        while(!evalStack.empty())
        {
            evalStack.pop();
        }

        for(const IRulePart *atom: it->second.condition())
        {
            oper = dynamic_cast<const LogicalOperator*>(atom);
            if(oper != NULL)
            {
                temp = evalStack.top();
                evalStack.pop();

                switch(oper->type())
                {
                case AND:
                    temp = LogicalOperator::binaryOperation(evalStack.top(), temp, _andFunction);
                    evalStack.pop();
                    break;
                case OR:
                    temp = LogicalOperator::binaryOperation(evalStack.top(), temp, _orFunction);
                    evalStack.pop();
                    break;
                case XOR:
                    temp = LogicalOperator::binaryOperation(evalStack.top(), temp, _xorFunction);
                    evalStack.pop();
                    break;
                case NOT:
                    temp = LogicalOperator::unaryOperation(temp, _notFunction);
                    break;
                }

                evalStack.push(temp);
            }
            else
            {
                mf = (const MembershipFunction*) atom;
                evalStack.push(mf->membershipGrade(_memory->inputValue(mf->proprietary())));
            }
        }

        _memory->setRuleValue(&it->second, evalStack.top());
    }
}

void InferenceEngine::fuzzifyAll()
{
    const LinguisticVariable *lv;
    const MembershipFunction *mf;
    const LogicalOperator *oper;

    stack<double> evalStack;
    double temp;

    for(map<tsize, LinguisticVariable>::const_iterator itLv = _kb->linguisticVariables().cbegin();
        itLv != _kb->linguisticVariables().cend(); itLv++)
    {
        lv = &itLv->second;
        for(map<tsize, MembershipFunction>::const_iterator itMf = lv->membershipFunctions().cbegin();
            itMf != lv->membershipFunctions().cend(); itMf++)
        {
            mf = &itMf->second;
            _memory->setFunctionValue(lv, mf, mf->membershipGrade(_memory->inputValue(lv)));
        }
    }

    for(map<tsize, Rule>::const_iterator it = _kb->rules().cbegin(); it != _kb->rules().cend(); it++)
    {
        while(!evalStack.empty())
        {
            evalStack.pop();
        }

        for(const IRulePart *atom: it->second.condition())
        {
            oper = dynamic_cast<const LogicalOperator*>(atom);
            if(oper != NULL)
            {
                temp = evalStack.top();
                evalStack.pop();

                switch(oper->type())
                {
                case AND:
                    temp = LogicalOperator::binaryOperation(evalStack.top(), temp, _andFunction);
                    evalStack.pop();
                    break;
                case OR:
                    temp = LogicalOperator::binaryOperation(evalStack.top(), temp, _orFunction);
                    evalStack.pop();
                    break;
                case XOR:
                    temp = LogicalOperator::binaryOperation(evalStack.top(), temp, _xorFunction);
                    evalStack.pop();
                    break;
                case NOT:
                    temp = LogicalOperator::unaryOperation(temp, _notFunction);
                    break;
                }

                evalStack.push(temp);
            }
            else
            {
                mf = (const MembershipFunction*) atom;
                evalStack.push(_memory->functionValue(mf->proprietary(), mf));
            }
        }

        _memory->setRuleValue(&it->second, evalStack.top());
    }
}











