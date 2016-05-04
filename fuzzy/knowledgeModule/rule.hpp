#ifndef RULE_HPP
#define RULE_HPP

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

/**===================*~* OWN LIBRARIES *~*===================**/
#include <string>
#include <vector>

/**===================*~* OWN LIBRARIES *~*===================**/
#include "knowledgemodule.hpp"

namespace fuzzy
{
namespace knowledgeModule
{

class Rule
{
public:
/**===================================== CONSTRUCTORS =====================================**/
    //this method can throws: fuzzy::exceptions::BadInstanceException
    Rule(const std::string &ruleStr, const KnowledgeBase &proprietary);
    Rule(const Rule &other);

/**===================================== DESTRUCTOR =====================================**/
    ~Rule();

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    const std::string &toString() const;
    const std::vector<const IRulePart*> &condition() const;
    const std::vector<const IRulePart*> &conclusion() const;
    const std::vector< std::pair<tsize, tsize> > &dependencies(bool isInput = true) const;

/**===================================== PUBLIC OVERLOADED OPERATORS =====================================**/
    const Rule &operator = (const Rule &rule)
    {
        _condition = rule._condition;
        _conclusion = rule._conclusion;

        _ruleStr = rule._ruleStr;

        _inputDependencies = rule._inputDependencies;
        _outputDependencies = rule._outputDependencies;

        return *this;
    }

    Rule &operator = (Rule &&rule)
    {
        _condition.swap(rule._condition);
        _conclusion.swap(rule._conclusion);

        _ruleStr.swap(rule._ruleStr);

        _inputDependencies.swap(rule._inputDependencies);
        _outputDependencies.swap(rule._outputDependencies);

        return *this;
    }

private:
/**===================================== PRIVATE MEMBER VARIABLES =====================================**/
    std::vector<const IRulePart*> _condition;
    std::vector<const IRulePart*> _conclusion;
    std::string _ruleStr;

    std::vector< std::pair<tsize, tsize> > _inputDependencies;
    std::vector< std::pair<tsize, tsize> > _outputDependencies;

/**===================================== PRIVATE MEMBER FUNCTIONS =====================================**/
    bool createRule(const std::string &ruleStr, const KnowledgeBase &proprietary);
    bool compile(const std::string &source, const KnowledgeBase &proprietary,
                 std::vector<const IRulePart*> &postfixVector, bool isInput = true);
    void dropRule();

};

}
}

#endif // RULE_HPP










