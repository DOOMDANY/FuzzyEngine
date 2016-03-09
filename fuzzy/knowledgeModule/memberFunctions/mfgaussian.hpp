#ifndef MFGAUSSIAN_HPP
#define MFGAUSSIAN_HPP

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
 * \file    mfgaussian.hpp                                      *
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

/*in params: params[0] -> k (bell's width)
 *           params[1] -> m (value where membership is 1.0, bell's center)
 */
class MFGaussian : public IMemberFunction
{
public:
/**===================================== CONSTRUCTORS =====================================**/
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    MFGaussian(const double *params, const LinguisticVariable *proprietary);

/**===================================== DESTRUCTOR =====================================**/
    virtual ~MFGaussian();

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    //this method can throws: fuzzy::knowledgeModule::memberFunctions::MFException
    virtual double membershipGrade(double value) const;

/**===================================== SETTER & GETTER =====================================**/
    void setParameters(const double *params);

};

}
}
}

#endif // MFGAUSSIAN_HPP
