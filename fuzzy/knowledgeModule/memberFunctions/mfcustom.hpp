#ifndef MFCUSTOM_HPP_INCLUDED
#define MFCUSTOM_HPP_INCLUDED

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
 * \file    MFCustom.hpp                                        *
 *                                                              *
 ****************************************************************/

/**===================*~* STL LIBRARIES *~*===================**/
#include <string>

/**===================*~* OWN LIBRARIES *~*===================**/
#include "imemberfunction.hpp"

namespace fuzzy
{
namespace knowledgeModule
{
namespace memberFunctions
{

class MFCustom : public IMemberFunction
{
public:
/**===================================== CONSTRUCTORS =====================================**/
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    MFCustom(const std::string &expression, const LinguisticVariable *proprietary);

/**===================================== DESTRUCTOR =====================================**/
    virtual ~MFCustom();

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    virtual double membershipGrade(double value) const;

/**===================================== SETTER & GETTER =====================================**/
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    virtual void setExpression(const std::string &expression);
    virtual const std::string &expression() const;

protected:
/**===================================== PRIVATE MEMBER VARIABLES =====================================**/
    std::string _expression;

};

}
}
}

#endif // MFCUSTOM_HPP_INCLUDED
