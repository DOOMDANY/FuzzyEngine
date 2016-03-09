#ifndef MFSINGLETON_HPP
#define MFSINGLETON_HPP

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
 * \file    mfsingleton.hpp                                     *
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

/*in params: params[0] -> membership value
*/
class MFSingleton : public IMemberFunction
{
public:
/**===================================== CONSTRUCTORS =====================================**/
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    MFSingleton(const double *params, const LinguisticVariable *proprietary);

/**===================================== DESTRUCTOR =====================================**/
    virtual ~MFSingleton();

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    virtual double membershipGrade(double value) const;
};

}
}
}

#endif // MFSINGLETON_HPP
