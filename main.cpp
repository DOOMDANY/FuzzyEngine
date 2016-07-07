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
    try
    {
        throw(10);
    }
    catch(int &e)
    {
        cout << 10 << endl;
    }

    return 0;
}










