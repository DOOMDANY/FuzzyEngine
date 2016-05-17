#ifndef MEMBERSHIPFUNCTION_HPP
#define MEMBERSHIPFUNCTION_HPP

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
 * \file    membershipfunction.hpp                              *
 *                                                              *
 ****************************************************************/

/**===================*~* STL LIBRARIES *~*===================**/
#include <string>

/**===================*~* OWN LIBRARIES *~*===================**/
#include "memberfunctions.hpp"
#include "imemberfunction.hpp"
#include "fuzzy/knowledgeModule/irulepart.hpp"

namespace fuzzy
{
namespace knowledgeModule
{
namespace memberFunctions
{

class MembershipFunction : public IRulePart
{
public:
/**===================================== CONSTRUCTORS =====================================**/
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    //                        std::bad_alloc
    MembershipFunction(const std::string &name, MFType type, const double *params,
                       const LinguisticVariable *proprietary);
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    //                        std::bad_alloc
    MembershipFunction(const std::string &name, const std::string &expression, const LinguisticVariable *proprietary);

    MembershipFunction(const MembershipFunction &other);

/**===================================== DESTRUCTOR =====================================**/
    virtual ~MembershipFunction();

/**===================================== SETTER & GETTER =====================================**/
    void rename(const std::string &name);
    const std::string &name() const;

    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    void setParameters(const double *params);
    const double *parameters() const;

    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    void setExpression(const std::string &expression);
    const std::string &expression() const;

    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    //                        std::bad_alloc
    void setType(MFType type, const double *newParams = NULL);
    MFType type() const;

    const LinguisticVariable *proprietary() const;

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    double membershipGrade(double value) const;

/**===================================== OVERLOADED OPERATORS =====================================**/
    const MembershipFunction &operator = (const MembershipFunction &other);
    MembershipFunction &operator = (MembershipFunction &&other);

private:
/**===================================== PRIVATE MEMBER VARIABLES =====================================**/
    std::string _name;
    IMemberFunction *_memberFunction;

/**===================================== PRIVATE MEMBER FUNCTIONS =====================================**/
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    //                        std::bad_alloc
    void createMemberFunction(MFType type, const double *params, const LinguisticVariable *proprietary);
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    //                        std::bad_alloc
    void createMemberFunction(const std::string &expression, const LinguisticVariable *proprietary);

};

}
}
}

#endif // MEMBERSHIPFUNCTION_HPP











