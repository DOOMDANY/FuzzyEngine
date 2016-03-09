#ifndef MFBELL_HPP_INCLUDED
#define MFBELL_HPP_INCLUDED

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
 * \file    mfbell.hpp                                          *
 *                                                              *
 ****************************************************************/

/**===================*~* OWN LIBRARIES *~*===================**/
#include "imemberfunction.hpp"

namespace fuzzy
{
namespace knowledgeModule
{
namespace memberFunctions
{

/*in params: params[0] -> a
 *           params[1] -> b
 *           params[2] -> c
 */
class MFBell : public IMemberFunction
{
public:
/**===================================== CONSTRUCTORS =====================================**/
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    MFBell(const double *params, const LinguisticVariable *proprietary);

/**===================================== DESTRUCTOR =====================================**/
    virtual ~MFBell();

/**===================================== SETTER & GETTER =====================================**/
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    virtual void setParameters(const double *params);

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    virtual double membershipGrade(double value) const;
};

}
}
}

#endif // MFBELL_HPP_INCLUDED
