#include <iostream>

#include "fuzzy/fuzzyengine.hpp"
#include "fuzzy/knowledgeModule/logicaloperator.hpp"
#include "fuzzy/exceptions/rulecompilerexception.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::knowledgeModule::memberFunctions;

int main()
{
    KnowledgeBase kb("KB 1");
    double params[] = {0.0, 0.5, 1.0};
    double paramsT[] = {0.0, 0.5, 1.0, 1.0};

    for(tsize i = 0; i < 5; i++)
    {
        cout << kb.createLinguisticVariable("INPUT" + to_string(i), 0.0, 1.0) << endl;
        for(tsize j = 0; j < 3; j++)
        {
            cout << kb.createMembershipFunction("MF" + to_string(i) + "," + to_string(j),
                                                MFType::TRIANGLE, params, i + 1);
            cout << "--" << kb.membershipFunctionCount(i + 1) << endl;
        }
    }

    for(int i = 0; i < 3; i++)
    {
        cout << kb.createLinguisticVariable("OUTPUT" + to_string(i), 0.0, 1.0, false) << endl;
        for(tsize j = 0; j < 3; j++)
        {
            cout << kb.createMembershipFunction("MF" + to_string(i) + "," + to_string(j),
                                                MFType::TRIANGLE, params, i + 1, false) << endl;
        }
    }

    cout << "input variables: " << kb.linguisticVariableCount() << endl;
    for(tsize i = 0; i < kb.linguisticVariableCount(); i++)
    {
        cout << kb.linguisticVariable(i + 1).name() << ": " <<
                kb.linguisticVariable(i + 1).membershipFunctionCount() << endl;
        for(tsize j = 0; j < kb.linguisticVariable(i + 1).membershipFunctionCount(); j++)
        {
            cout << kb.membershipFunction(i + 1, j + 1).name() << " -> " <<
                    kb.membershipFunction(i + 1, j + 1).type() << endl;
        }
    }

    cout << "output variables: " << kb.linguisticVariableCount(false) << endl;
    for(tsize i = 0; i < kb.linguisticVariableCount(false); i++)
    {
        cout << kb.linguisticVariable(i + 1, false).name() << ": " <<
                kb.linguisticVariable(i + 1, false).membershipFunctionCount() << endl;
        for(tsize j = 0; j < kb.linguisticVariable(i + 1, false).membershipFunctionCount(); j++)
        {
            cout << kb.membershipFunction(i + 1, j + 1, false).name() << " -> " <<
                    kb.membershipFunction(i + 1, j + 1).type() << endl;
        }
    }

    //cout << kb.createRule("INPUT0=MF1&INPUT1=MF2->OUTPUT0=MF0&OUTPUT2=MF1") << endl;
    try
    {
        kb.createRule("INPUT0=MF0,0&INPUT1=MF1,2->OUTPUT0=MF0,0");

        cout << "rule number: " << kb.ruleCount() << endl;
        cout << "rule ids size: " << kb.ruleIds().size() << endl;

        for(int i = 0; i < kb.ruleIds().size(); i++)
        {
            cout << "rule position: " << i << ", id: " << kb.ruleIds().at(i) << endl;
        }

        const MembershipFunction *mf;
        const LogicalOperator *lo;
        for(unsigned int i = 0u; i < kb.rule(1).condition().size(); i++)
        {
            mf = dynamic_cast<const MembershipFunction*>(kb.rule(1u).condition().at(i));

            if(mf != NULL)
            {
                cout << mf->name() << endl;
            }
            else
            {
                lo = dynamic_cast<const LogicalOperator*>(kb.rule(1u).condition().at(i));
                cout << lo->type() << endl;
            }
        }
    }
    catch(exceptions::RuleCompilerException &rce)
    {
        cout << rce.what() << ", " << rce.compilerMessage() << endl;
    }

    return 0;
}










