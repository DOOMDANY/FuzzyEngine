#ifndef FUZZYENGINE_HPP
#define FUZZYENGINE_HPP

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
 * \file    fuzzyengine.hpp                                     *
 *                                                              *
 ****************************************************************/

/**===================*~* STL LIBRARIES *~*===================**/
#include <map>
#include <vector>
#include <string>

/**===================*~* OWN LIBRARIES *~*===================**/
#include "fuzzy.hpp"
#include "fuzzy/knowledgeModule/knowledgebase.hpp"

/**===================*~* FORWARD DECLARATIONS *~*===================**/

namespace fuzzy
{
class FuzzyEngine
{
public:
/**===============================*~* PUBLIC MEMBERS *~*===============================**/
    /*!
     * \brief   States - enum, represents the error states into Fuzzy Engine
     *
     *          Each value in the enumeration represents an state of the system, this state is stored in
     *          the variable last_error which has the task to inform about errors in some processes or
     *          when some exception occurs.
     */
    enum States
    {
        OK,                 /*!< It means that everything went well. */
        KB_NOT_FOUND,       /*!< If a KB ID was greater than the number of KBs in the system. */
        LV_NOT_FOUND,       /*!< If a LV ID was greater than the number of LVs inside of some KB. */
        MF_NOT_FOUND,       /*!< If a MF ID was greater than the number of MFs inside of some LV. */
        RULE_NOT_FOUND,     /*!< If a Rule ID was greater than the number of MFs inside of some KB. */
        REPEATED_NAME,      /*!< When it's tried to create or rename a KB,
                                 LV or MF and the name already exists. */
        BAD_PARAMS,         /*!< When a set of parameter for any MF is inconsistent (depends on each MF). */
        BAD_LIMITS,         /*!< If it's tried to set the lower limit greater than the upper limit. */
        BAD_ALLOC,          /*!< When any function or process throws a bad_alloc exception because of doesn't
                                 have enough memory. */
        INVALID_RULE_FORMAT,/*!< It means that one string evaluated to be a rule failed the parsing. */
        OUT_OF_RANGE,       /*!< When any value is less or bigger than the limits or when a
                                 std::out_of_range has been thrown. */
        BAD_CONFIG,         /*!< This state occurs when a BadConfig Exception is thrown into the
                                 Inference Engine. */
        INVALID_MF,
        UNKNOWN_ERROR       /*!< When an unknown error has occurred. */
    };

/**===================================== PUBLIC STATIC VARIABLES =====================================**/
    static std::string errorStr[];

/**===================================== CONSTRUCTORS =====================================**/
    FuzzyEngine();

/**===================================== DESTRUCTOR =====================================**/
    ~FuzzyEngine();

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    // >>>>>>>>>>>>>>>>>>>>>>> FuzzyEngine Management
    void resetState();
    int lastError() const;
    std::string lastErrorStr() const;

    // >>>>>>>>>>>>>>>>>>>>>>> Knowledge Base Management
        // ----------------------- Knowledge Bases
    bool createKnowledgeBase(const std::string &name);
    std::string knowledgeBaseName(tsize idKb) const;
    int idKnowledgeBase(const std::string &name) const;
    tsize linguisticVariableCount(tsize idKb, bool isInput = true) const;
    tsize ruleCount(tsize idKb) const;
    bool renameKnowledgeBase(tsize idKb, const std::string &name);
    void removeKnowledgeBase(tsize idKb);

        // ----------------------- Rules
    //pending reformat de rule string IF LV IS MF AND LV IS MF THEN LV IS MF instead of LV=MF&LV=MF->LV=MF
    bool createRule(tsize idKb, const std::string &ruleStr);
    //pending reformat de rule string IF LV IS MF AND LV IS MF THEN LV IS MF instead of LV=MF&LV=MF->LV=MF
    std::string rule(tsize idKb, tsize idRule) const;
    bool replaceRule(tsize idKb, tsize idRule, const std::string &ruleStr);
    void removeRule(tsize idKb, tsize idRule);

        // ----------------------- Linguistic Variables
    bool createLinguisticVariable(tsize idKb, const std::string &name, double lowerLimit, double upperLimit,
                                  bool isInput = true);
    std::string linguisticVariableName(tsize idKb, tsize idLv, bool isInput = true) const;
    int idLinguisticVariable(tsize idKb, const std::string &name, bool isInput = true) const;
    tsize membershipFunctionCount(tsize idKb, tsize idLv, bool isInput = true) const;
    double upperLimit(tsize idKb, tsize idLv, bool isInput = true) const;
    double lowerLimit(tsize kbId, tsize idLv, bool isInput = true) const;
    bool renameLinguisticVariable(tsize idKb, tsize idLv, bool isInput, const std::string &name);
    bool setLinguisticVariableLimits(tsize idKb, tsize idLv, bool isInput, double lowerLimit, double upperLimit);
    void removeLinguisticVariable(tsize idKb, tsize idLv, bool isInput = true);

        // ----------------------- Membership Functions
    bool createMembershipFunction(tsize idKb, tsize idLv, bool isInput,
                                  const std::string &name, const double *params,
                                  knowledgeModule::memberFunctions::MFType type);
    const std::string &membershipFunctionName(tsize kbId, tsize idLv, bool isInput, tsize idMf) const;
    tsize membershipFunctionId(tsize kbId, tsize lvId, bool isInput, const std::string &name) const;
    const std::vector<double> &parameters(tsize kbId, tsize lvId, bool isInput, tsize mfId) const;
    tsize parameterCount(tsize kbId, tsize lvId, bool isInput, tsize mfId) const;
    knowledgeModule::memberFunctions::MFType membershipFunctionType(tsize kbId, tsize lvId, bool isInput,
                                                                    tsize mfId) const;
    bool renameMembershipFunction(tsize kbId, tsize lvId, bool isInput, tsize mfId, const std::string &name);
    bool setMembershipFunctionParameters(tsize kbId, tsize lvId, bool isInput, tsize mfId,
                                         const std::vector<double> &params);
    bool setMembershipFunctionType(tsize kbId, tsize lvId, bool isInput, tsize mfId,
                                   knowledgeModule::memberFunctions::MFType type);
    void removeMembershipFunction(tsize kbId, tsize lvId, bool isInput, tsize mfId);

    // >>>>>>>>>>>>>>>>>>>>>>> Work Memory Management
    double output(tsize kbId, tsize lvId) const;
    double input(tsize kbId, tsize lvId) const;
    const std::string &inputStr(tsize kbId, tsize lvId) const;
    bool setInput(tsize kbId, tsize lvId, double grade);
    bool setInput(tsize kbId, tsize lvId, const std::string &membershipFunctionName);

    // >>>>>>>>>>>>>>>>>>>>>>> Inference Engine Management
    bool setDefuzzifyMethod();
    bool setLogicalOperation();

private:
    mutable States _lastError;

    mutable std::map<tsize, knowledgeModule::KnowledgeBase> _knowledgeBases;

/**===================================== PRIVATE MEMBER FUNCTIONS =====================================**/
    inline knowledgeModule::KnowledgeBase *findKnowledgeBase(tsize idKb) const;
    inline knowledgeModule::Rule *findRule(tsize idKb, tsize idRule) const;
    inline knowledgeModule::LinguisticVariable *findLinguisticVariable(
            tsize idKb, tsize idLv, bool isInput = true) const;
    inline knowledgeModule::memberFunctions::MembershipFunction *findMembershipFunction(
            tsize idKb, tsize idLv, tsize idMf, bool isInput = true) const;

};

}

#endif // FUZZYENGINE_HPP










