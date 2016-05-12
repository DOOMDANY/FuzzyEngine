#ifndef FUZZYENGINE_HPP
#define FUZZYENGINE_HPP

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
 * \file    fuzzyengine.hpp                                     *
 *                                                              *
 ****************************************************************/

/**===================*~* STL LIBRARIES *~*===================**/
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
        BAD_CONFIG,         /*!< This state occurs when a BadConfigException is thrown into the
                                 Inference Engine. */
        CONCURRENCY_ERROR,  /*!< If a problem related with multi-threading features occurs */
        UNKNOWN_ERROR       /*!< When an unknown error has occurred. */
    };

    /**===================================== CONSTRUCTOR =====================================**/
    FuzzyEngine();

    /**===================================== DESTRUCTOR =====================================**/
    ~FuzzyEngine();

    /**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    // >>>>>>>>>>>>>>>>>>>>>>> FuzzyEngine Management
    void resetState();
    int lastError() const;
    std::string lastErrorStr() const;

    // >>>>>>>>>>>>>>>>>>>>>>> Knowledge Base Management
    bool createKnowledgeBase(const std::string &name);
    const std::string &knowledgeBaseName(tsize kbId) const;
    tsize knowledgeBaseId(const std::string &name) const;
    tsize linguisticVariableCount(tsize kbId) const;
    tsize ruleCount(tsize kbId) const;
    bool renameKnowledgeBase(tsize kbId, const std::string &name);
    void removeKnowledgeBase(tsize kbId);

    bool createRule(tsize kbId, const std::string &ruleStr);
    const std::string &rule(tsize kbId, tsize ruleId) const;
    std::string condition(tsize kbId, tsize ruleId) const;
    std::string conclusion(tsize kbId, tsize ruleId) const;
    bool replaceRule(tsize kbId, tsize ruleId, const std::string &ruleStr);
    void removeRule(tsize kbId, tsize ruleId);

    bool createLinguisticVariable(tsize kbId, const std::string &name, double lowerLimit, double upperLimit,
                                  bool isInput);
    const std::string &linguisticVariableName(tsize kbId, tsize lvId, bool isInput) const;
    tsize linguisticVariableId(tsize kbId, const std::string &name, bool isInput) const;
    tsize membershipFunctionCount(tsize kbId, tsize lvId, bool isInput) const;
    double upperLimit(tsize kbId, tsize lvId, bool isInput) const;
    double lowerLimit(tsize kbId, tsize lvId, bool isInput) const;
    bool renameLinguisticVariable(tsize kbId, tsize lvId, bool isInput, const std::string &name);
    bool setLinguisticVariableLimits(tsize kbId, tsize lvId, bool isInput, double lowerLimit, double upperLimit);
    void removeLinguisticVariable(tsize kbId, tsize lvId, bool isInput);

    bool createMembershipFunction(tsize kbId, tsize lvId, bool isInput,
                                  const std::string &name, const std::vector<double> &params,
                                  knowledgeModule::memberFunctions::MFType type);
    const std::string &membershipFunctionName(tsize kbId, tsize lvId, bool isInput, tsize mfId) const;
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
    States _lastError;


};

}

#endif // FUZZYENGINE_HPP
