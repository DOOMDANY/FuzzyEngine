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

namespace fuzzy
{
namespace knowledgeModule
{
namespace memberFunctions
{

class MembershipFunction
{
public:
/**===================================== CONSTRUCTORS =====================================**/
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    MembershipFunction(const std::string &name, MFType type, const double *params,
                       const LinguisticVariable *proprietary);
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    MembershipFunction(const std::string &name, const std::string &expression, const LinguisticVariable *proprietary);

/**===================================== DESTRUCTOR =====================================**/
    virtual ~MembershipFunction();

/**===================================== SETTER & GETTER =====================================**/
    void rename(const std::string &name);
    const std::string &name() const;

    void setParameters(const double *params);
    const double *Parameters() const;

    void setExpression(const std::string &expression);
    const std::string &expression() const;

    void setType(MFType type);
    MFType type() const;

    const LinguisticVariable *proprietary() const;

private:
/**===================================== PRIVATE MEMBER VARIABLES =====================================**/
    std::string _name;
    IMemberFunction *_memberFunction;

/**===================================== PRIVATE MEMBER FUNCTIONS =====================================**/
    void createMemberFunction(MFType type, const double *params, const LinguisticVariable *proprietary);
    void createMemberFunction(const std::string &expression, const LinguisticVariable *proprietary);

};

}
}
}

#endif // MEMBERSHIPFUNCTION_HPP











