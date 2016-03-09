#ifndef MFTRAPEZOID_HPP
#define MFTRAPEZOID_HPP

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
 * \file    mftrapezoid.hpp                                     *
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

/*in params: params[0] -> a
 *           params[1] -> b
 *           params[2] -> c
 *           params[3] -> d
 */
class MFTrapezoid : public IMemberFunction
{
public:
/**===================================== CONSTRUCTORS =====================================**/
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    MFTrapezoid(const double *params, const LinguisticVariable *proprietary);

/**===================================== DESTRUCTOR =====================================**/
    virtual ~MFTrapezoid();

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    double membershipGrade(double value) const;

/**===================================== SETTER & GETTER =====================================**/
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    virtual void setParameters(const double *params);

};

}
}
}

#endif // MFTRAPEZOID_HPP
