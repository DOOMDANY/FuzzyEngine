#ifndef WORKMEMORY_HPP
#define WORKMEMORY_HPP

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
 * \file    workmemory.hpp                                      *
 *                                                              *
 ****************************************************************/

/**===================*~* STL LIBRARIES *~*===================**/
#include <map>
#include <vector>

/**===================*~* OWN LIBRARIES *~*===================**/
#include "memorymodule.hpp"
#include "fuzzy/knowledgeModule/rule.hpp"

namespace fuzzy
{
namespace memoryModule
{

class WorkMemory
{
public:
/**===================================== CONSTRUCTORS =====================================**/
    WorkMemory();

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    bool addInput(tsize idLv, double initialValue = 0.0);
    //this method can throws: fuzzy::exceptions::NonExistentElementException<tsize>
    double inputValue(tsize idLv) const;
    bool existsInput(tsize idLv) const;
    tsize inputCount() const;
    std::vector<tsize> inputIds() const;
    //this method can throws: fuzzy::exceptions::NonExistentElementException<tsize>
    void setInputValue(tsize idLv, double value);
    void removeInput(tsize idLv);

    bool addFunction(tsize idLv, tsize idMf, double initialValue = 0.0);
    //this method can throws: fuzzy::exceptions::NonExistentElementException<tsize>
    //                        fuzzy::exceptions::NonExistentElementException< pair<tsize, tsize> >
    double functionValue(tsize idLv, tsize idMf) const;
    bool existsFunction(tsize idLv, tsize idMf) const;
    int functionCount(tsize idLv) const;
    std::vector<tsize> functionIds(tsize idLv) const;
    //this method can throws: fuzzy::exceptions::NonExistentElementException<tsize>
    //                        fuzzy::exceptions::NonExistentElementException< pair<tsize, tsize> >
    void setFunctionValue(tsize idLv, tsize idMf, double value);
    void removeFunction(tsize idLv, tsize idMf);

    bool addRule(tsize idRule, const knowledgeModule::Rule &rule, double initialValue = 0.0);
    //this method can throws: fuzzy::exceptions::NonExistentElementException<tsize>
    double ruleValue(tsize idRule) const;
    bool existsRule(tsize idRule) const;
    tsize ruleCount() const;
    std::vector<tsize> ruleIds() const;
    //this method can throws: fuzzy::exceptions::NonExistentElementException<tsize>
    void setRuleValue(tsize idRule, double value);
    void removeRule(tsize idRule);

    bool addOutput(tsize idLv, double initialValue = 0.0);
    //this method can throws: fuzzy::exceptions::NonExistentElementException<tsize>
    double outputValue(tsize idLv) const;
    bool existsOutput(tsize idLv) const;
    tsize outputCount() const;
    std::vector<tsize> outputIds() const;
    //this method can throws: fuzzy::exceptions::NonExistentElementException<tsize>
    void setOutputValue(tsize idLv, double value);
    void removeOutput(tsize idLv);

private:
/**===================================== PRIVATE MEMBERS =====================================**/
    struct InputRegister
    {
        double value;
        std::map<tsize, double> functions;

        InputRegister(double value, std::map<tsize, double> functions = std::map<tsize, double>()) :
            value(value),
            functions(functions)
        {

        }
    };

    struct RuleRegister
    {
        const knowledgeModule::Rule *rule;
        double value;

        RuleRegister(const knowledgeModule::Rule *rule, double value = 0.0) :
            rule(rule),
            value(value)
        {

        }
    };

/**===================================== PRIVATE MEMBER VARIABLES =====================================**/
    std::map<tsize, InputRegister> _inputs;
    std::map<tsize, RuleRegister> _rules;
    std::map<tsize, double> _outputs;

};

}
}

#endif // WORKMEMORY_HPP
