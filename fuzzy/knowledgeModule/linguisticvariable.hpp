#ifndef LINGUISTICVARIABLE_HPP
#define LINGUISTICVARIABLE_HPP

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
 * \file    linguisticvariable.hpp                              *
 *                                                              *
 ****************************************************************/

/**===================*~* STL LIBRARIES *~*===================**/
#include <map>
#include <string>

/**===================*~* OWN LIBRARIES *~*===================**/
#include "knowledgemodule.hpp"
#include "fuzzy/knowledgeModule/memberFunctions/membershipfunction.hpp"

namespace fuzzy
{
namespace knowledgeModule
{

class LinguisticVariable
{
public:
/**===================================== CONSTRUCTORS =====================================**/
    //this method can throws: std::out_of_range
    LinguisticVariable(const std::string &name, double lowerLimit, double upperLimit);

/**===================================== DESTRUCTOR =====================================**/
    ~LinguisticVariable();

/**===================================== SETTER & GETTER =====================================**/
    void rename(const std::string &name);
    const std::string &name() const;

    bool setLimits(double lowerLimit, double upperLimit);

    bool setLowerLimit(double lowerLimit);
    double lowerLimit() const;

    bool setUpperLimit(double upperLimit);
    double upperLimit() const;

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Membership Functions Management
    //this method can throws: fuzzy::exceptions::CommonException(DUPLICATED_ITEM),
    //                        fuzzy::knowledgeModule::memberFunctions::MFException
    //                        std::bad_alloc
    void createMembershipFunction(const std::string &functionName, const double *params, memberFunctions::MFType type);
    //this method can throws: fuzzy::util::exceptions::CommonException(DUPLICATED_ITEM),
    //                        fuzzy::knowledgeModule::memberFunctions::MFException
    //                        std::bad_alloc
    void createMembershipFunction(const std::string &functionName, const std::string &expression);
    tsize membershipFunctionCount() const;
    //this method can throws: fuzzy::exceptions::CommonException(CommonException::NON_EXISTENT_ELEMENT)
    const knowledgeModule::memberFunctions::MembershipFunction &membershipFunction(tsize id) const;
    //this method can throws: fuzzy::exceptions::CommonException(CommonException::NON_EXISTENT_ELEMENT)
    knowledgeModule::memberFunctions::MembershipFunction &membershipFunction(tsize id);
    const std::map<tsize, memberFunctions::MembershipFunction> &membershipFunctions() const;
    int idMembershipFunction(const std::string &name) const;
    //this method can throws: fuzzy::exceptions::CommonException(CommonException::NON_EXISTENT_ELEMENT)
    void replaceMembershipFunction(const knowledgeModule::memberFunctions::MembershipFunction &membershipFunction,
                                   tsize id);
    void removeMembershipFunction(tsize id);

private:
/**===================================== PRIVATE MEMBER VARIABLES =====================================**/
    std::string _name;
    double _lowerLimit;
    double _upperLimit;

    std::map<tsize, memberFunctions::MembershipFunction> _memberFunctions;
};

}
}

#endif // LINGUISTICVARIABLE_HPP
