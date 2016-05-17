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
#include "fuzzy/knowledgeModule/knowledgemodule.hpp"

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
    bool addInput(const knowledgeModule::LinguisticVariable *lv, double initialValue = 0.0);
    //this method can throws: fuzzy::exceptions::CommonException(NON_EXISTENT_ELEMENT)
    double inputValue(const knowledgeModule::LinguisticVariable *lv) const;
    bool existsInput(const knowledgeModule::LinguisticVariable *lv) const;
    tsize inputCount() const;
    //this method can throws: fuzzy::exceptions::CommonException(NON_EXISTENT_ELEMENT)
    void setInputValue(const knowledgeModule::LinguisticVariable *lv, double value);
    void removeInput(const knowledgeModule::LinguisticVariable *lv);

    bool addFunction(const knowledgeModule::LinguisticVariable *lv,
                     const knowledgeModule::memberFunctions::MembershipFunction *mf,
                     double initialValue = 0.0);
    //this method can throws: fuzzy::exceptions::CommonException(NON_EXISTENT_ELEMENT)
    double functionValue(const knowledgeModule::LinguisticVariable *lv,
                         const knowledgeModule::memberFunctions::MembershipFunction *mf) const;
    bool existsFunction(const knowledgeModule::LinguisticVariable *lv,
                        const knowledgeModule::memberFunctions::MembershipFunction *mf) const;
    int functionCount(const knowledgeModule::LinguisticVariable *lv) const;
    //this method can throws: fuzzy::exceptions::CommonException(NON_EXISTENT_ELEMENT)
    void setFunctionValue(const knowledgeModule::LinguisticVariable *lv,
                          const knowledgeModule::memberFunctions::MembershipFunction *mf, double value);
    void removeFunction(const knowledgeModule::LinguisticVariable *lv,
                        const knowledgeModule::memberFunctions::MembershipFunction *mf);

    bool addRule(const knowledgeModule::Rule *rule, double initialValue = 0.0);
    //this method can throws: fuzzy::exceptions::CommonException(NON_EXISTENT_ELEMENT)
    double ruleValue(const knowledgeModule::Rule *rule) const;
    bool existsRule(const knowledgeModule::Rule *rule) const;
    tsize ruleCount() const;
    //this method can throws: fuzzy::exceptions::CommonException(NON_EXISTENT_ELEMENT)
    void setRuleValue(const knowledgeModule::Rule *rule, double value);
    void removeRule(const knowledgeModule::Rule *rule);

    bool addOutput(const knowledgeModule::LinguisticVariable *lv, double initialValue = 0.0);
    //this method can throws: fuzzy::exceptions::CommonException(NON_EXISTENT_ELEMENT)
    double outputValue(const knowledgeModule::LinguisticVariable *lv) const;
    bool existsOutput(const knowledgeModule::LinguisticVariable *lv) const;
    tsize outputCount() const;
    //this method can throws: fuzzy::exceptions::CommonException(NON_EXISTENT_ELEMENT)
    void setOutputValue(const knowledgeModule::LinguisticVariable *lv, double value);
    void removeOutput(const knowledgeModule::LinguisticVariable *lv);

private:
/**===================================== PRIVATE MEMBERS =====================================**/
    struct InputRegister
    {
        double value;
        std::map<const knowledgeModule::memberFunctions::MembershipFunction*, double> functions;

        InputRegister(double value,
                      std::map<const knowledgeModule::memberFunctions::MembershipFunction*, double> functions =
                std::map<const knowledgeModule::memberFunctions::MembershipFunction*, double>()) :
            value(value),
            functions(functions)
        {

        }
    };

/**===================================== PRIVATE MEMBER VARIABLES =====================================**/
    std::map<const knowledgeModule::LinguisticVariable*, InputRegister> _inputs;
    std::map<const knowledgeModule::Rule*, double> _rules;
    std::map<const knowledgeModule::LinguisticVariable*, double> _outputs;

};

}
}

#endif // WORKMEMORY_HPP
