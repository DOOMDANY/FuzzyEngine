#ifndef KNOWLEDGEBASE_HPP
#define KNOWLEDGEBASE_HPP

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
 * \file    knowledgebase.hpp                                   *
 *                                                              *
 ****************************************************************/

/**===================*~* STL LIBRARIES *~*===================**/
#include <map>
#include <string>
#include <vector>

/**===================*~* OWN LIBRARIES *~*===================**/
#include "knowledgemodule.hpp"
#include "linguisticvariable.hpp"
#include "rule.hpp"

namespace fuzzy
{
namespace knowledgeModule
{

class KnowledgeBase
{
public:
/**===================================== CONSTRUCTORS =====================================**/
    KnowledgeBase(const std::string &name);

/**===================================== DESTRUCTOR =====================================**/
    virtual ~KnowledgeBase();

/**===================================== SETTER & GETTER =====================================**/
    void rename(const std::string &name);
    const std::string &name() const;

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Rules Management
    //this method can throws: fuzzy::exceptions::RuleCompilerException
    void createRule(const std::string &ruleStr);
    //this method can throws: fuzzy::exceptions::NonExistentElementException<tsize>
    const Rule &rule(tsize idRule) const;
    tsize ruleCount() const;
    std::vector<tsize> ruleIds() const;
    //this method can throws: fuzzy::exceptions::RuleCompilerException
    void replaceRule(tsize idRule, const std::string &ruleStr);
    void removeRule(tsize idRule);

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Linguistic Variables Management
    bool createLinguisticVariable(const std::string &name, double lowerLimit, double upperLimit, bool isInput = true);
    //this method can throws: fuzzy::exceptions::NonExistentElementException<tsize>
    const LinguisticVariable &linguisticVariable(tsize idLv, bool isInput = true) const;
    int idLinguisticVariable(const std::string &name, bool isInput = true) const;
    tsize linguisticVariableCount(bool isInput = true) const;
    bool renameLinguisticVariable(const std::string &name, tsize idLv, bool isInput = true);
    bool setLinguisticVariableLimits(double lowerLimit, double upperLimit, int idLv, bool isInput = true);
    void removeLinguisticVariable(tsize idLv, bool isInput = true);

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Membership Functions Management
    bool createMembershipFunction(const std::string &name, memberFunctions::MFType type, const double *params,
                                  tsize idLv, bool isInput = true);
    bool createMembershipFunction(const std::string &name, const std::string &expression, tsize idLv,
                                  bool isInput = true);
    //this method can throws: fuzzy::exceptions::NonExistentElementException< vector<tsize> >
    const memberFunctions::MembershipFunction &membershipFunction(tsize idLv, tsize idMf, bool isInput = true) const;
    int idMembershipFunction(tsize idLv, const std::string &name, bool isInput = true) const;
    //this method can throws: std::out_of_range
    tsize membershipFunctionCount(tsize idLv, bool isInput = true) const;
    bool renameMembershipFunction(const std::string &name, tsize idLv, tsize idMf, bool isInput = true);
    bool setMembershipFunctionParameters(const double *params, tsize idLv, tsize idMf, bool isInput = true);
    bool setMembershipFunctionExpression(const std::string &expression, tsize idLv, tsize idMf, bool isInput = true);
    bool setMembershipFunctionType(memberFunctions::MFType type, const double *params, tsize idLv, tsize idMf,
                                   bool isInput = true);
    void removeMembershipFunction(tsize idLv, tsize idMf, bool isInput = true);

private:
/**===================================== PRIVATE MEMBER VARIABLES =====================================**/
    std::string _name;

    std::map<tsize, Rule> _rules;
    std::map<tsize, LinguisticVariable> _inputs;
    std::map<tsize, LinguisticVariable> _outputs;

};

}
}

#endif // KNOWLEDGEBASE_HPP











