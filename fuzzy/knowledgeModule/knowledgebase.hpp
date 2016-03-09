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
#include <vector>
#include <string>

/**===================*~* OWN LIBRARIES *~*===================**/
#include "knowledgemodule.hpp"

/**===================*~* FORWARD DECLARATIONS *~*===================**/
namespace linkedContainers
{
    template<typename T>
    class LStack;
}

namespace fuzzy
{
namespace knowledgeModule
{

class KnowledgeBase
{
/**===================================== CONSTRUCTORS =====================================**/
    KnowledgeBase(const std::string &name);

/**===================================== DESTRUCTOR =====================================**/
    virtual ~KnowledgeBase();

/**===================================== SETTER & GETTER =====================================**/
    void rename(const std::string &name);
    const std::string &name() const;

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    bool createRule(const std::vector<std::string> &atomList);
    //this method can throws: std::out_of_range
    const Rule &rule(int ruleId) const;
    tsize ruleCount() const;
    bool replaceRule(tsize ruleId, const std::string &atomList);
    void RemoveRule(tsize ruleId);

    bool createLinguisticVariable(const std::string &name, double lowerLimit, double upperLimit, bool isInput);
    //this method can throws: std::out_of_range
    const LinguisticVariable &linguisticVariable(tsize lvId, bool isInput) const;
    int linguisticVariableId(const std::string &name, bool isInput) const;
    tsize linguisticVariableCount(bool isInput) const;
    bool renameLinguisticVariable(tsize lvId, bool isInput, const std::string &name);
    bool setLinguisticVariableLimits(int lvId, bool isInput, double lowerLimit, double upperLimit);
    void removeLinguisticVariable(tsize lvId, bool isInput);

    bool createMembershipFunction(tsize lvId, const std::string &name, memberFunctions::MFType type,
                                  const std::vector<double> &params, bool isInput);
    bool createMembershipFunction(tsize lvId, const std::string &name, const std::string &expression, bool isInput);
    const memberFunctions::MembershipFunction &membershipFunction(tsize lvId, int mfId, bool isInput) const;
    int membershipFunctionId(tsize lvId, const std::string &name, bool isInput) const;
    //this method can throws: std::out_of_range
    tsize membershipFunctionCount(tsize lvId, bool isInput) const;
    bool renameMembershipFunction(tsize lvId, tsize mfId, bool isInput, const std::string &name);
    bool setMembershipFunctionParameters(tsize lvId, tsize mfId, bool isInput, const std::vector<double> &params);
    bool setMembershipFunctionType(tsize lvId, bool isInput, tsize mfId, memberFunctions::MFType type);
    void RemoveMembershipFunction(tsize lvId, tsize mfId, bool isInput);

private:
/**===================================== PRIVATE MEMBER VARIABLES =====================================**/
    std::string _name;

};

}
}

#endif // KNOWLEDGEBASE_HPP











