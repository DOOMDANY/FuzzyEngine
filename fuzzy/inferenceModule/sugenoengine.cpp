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
 * \file    sugenoengine.cpp                                    *
 *                                                              *
 ****************************************************************/

/**===================*~* Class Definition *~*===================**/
#include "sugenoengine.hpp"
#include "fuzzy/knowledgeModule/logicaloperator.hpp"

/**===================*~* STL Classes *~*===================**/
#include <stack>

using namespace std;
using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;
using namespace fuzzy::memoryModule;
using namespace fuzzy::inferenceModule;

/**===================*~* CONSTRUCTORS *~*===================**/
SugenoEngine::SugenoEngine(const KnowledgeBase *kb, WorkMemory *memory) :
    InferenceEngine(kb, memory)
{

}

/**===================*~* DESTRUCTOR *~*===================**/
SugenoEngine::~SugenoEngine()
{

}

/**===================*~* PUBLIC MEMBER FUNCTIONS *~*===================**/
void SugenoEngine::defuzzify()
{
    const Rule *rule;
    mapLvMfV outputs;
    mapLvMfV::iterator itOutputs;
    mapMfV::iterator itMfvs;

    const LinguisticVariable *lv;
    const MembershipFunction *mf;
    const LogicalOperator *oper;

    double temp;
    double mx;
    double xmx;

    //prepare store space
    for(mapLv::const_iterator itLv = _kb->linguisticVariables(false).cbegin();
        itLv != _kb->linguisticVariables(false).cend(); itLv++)
    {
        lv = &itLv->second;
        itOutputs = outputs.insert(outputs.cbegin(), pairLvMfV(lv, map<const MembershipFunction*, double>()));

        for(mapMf::const_iterator itMf = lv->membershipFunctions().cbegin();
            itMf != lv->membershipFunctions().cend(); itMf++)
        {
            itOutputs->second.insert(itOutputs->second.cbegin(), pairMfV(&itMf->second, 0.0));
        }
    }

    //calculate the outputs unions
    for(map<tsize, Rule>::const_iterator itRules = _kb->rules().cbegin(); itRules != _kb->rules().cend(); itRules++)
    {
        rule = &itRules->second;

        for(const IRulePart *atom: itRules->second.condition())
        {
            oper = dynamic_cast<const LogicalOperator*>(atom);
            if(oper == NULL)
            {
                mf = (const MembershipFunction*) atom;
                itMfvs = outputs.find(mf->proprietary())->second.find(mf);
                temp = itMfvs->second;
                itMfvs->second = LogicalOperator::binaryOperation(
                            itMfvs->second, _memory->ruleValue(rule), _orFunction);
            }
            else if(oper->type() == NOT)
            {
                itMfvs->second = LogicalOperator::binaryOperation(
                            temp, LogicalOperator::unaryOperation(_memory->ruleValue(rule), _notFunction), _orFunction);
            }
        }
    }

    //obtain defuzzified output values
    while(!outputs.empty())
    {
        mx = xmx = 0.0;
        itOutputs = outputs.begin();
        while(!itOutputs->second.empty())
        {
            itMfvs = itOutputs->second.begin();
            mx += itMfvs->second;
            xmx += itMfvs->first->parameters()[0] * mx;

            itOutputs->second.erase(itMfvs);
        }

        lv = itOutputs->first;
        if(mx == 0.0)
        {
            _memory->setOutputValue(lv, (lv->lowerLimit() + lv->upperLimit()) / 2.0);
        }
        else
        {
            _memory->setOutputValue(itOutputs->first, xmx / mx);
        }

        outputs.erase(itOutputs);
    }
}

void SugenoEngine::infer()
{
    fuzzify();
    defuzzify();
}















