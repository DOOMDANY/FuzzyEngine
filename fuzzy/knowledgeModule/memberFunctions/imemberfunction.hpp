#ifndef IMEMBERFUNCTION_HPP
#define IMEMBERFUNCTION_HPP

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
 * \file    imemberfunction.hpp                                 *
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

class IMemberFunction
{
public:
/**===================================== PUBLIC STATIC FUNCTIONS =====================================**/
    static tsize parameterCount(MFType type);

/**===================================== CONSTRUCTORS =====================================**/
    //throws: fuzzy::knowledgeModule::memberFunctions::MFException
    IMemberFunction(MFType type, const double *params, tsize paramNumber, const LinguisticVariable *proprietary);

    IMemberFunction(const IMemberFunction &other);

/**===================================== DESTRUCTOR =====================================**/
    virtual ~IMemberFunction();

/**===================================== SETTER & GETTER =====================================**/
    MFType type() const;

    const LinguisticVariable *proprietary() const;

    virtual void setParameters(const double *params);
    const double *parameters() const;

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    virtual double membershipGrade(double value) const = 0;

/**===================================== OVERLOADED OPERATORS =====================================**/
    const IMemberFunction &operator = (const IMemberFunction &other);
    IMemberFunction &operator = (IMemberFunction &&other);

protected:
/**===================================== PROTECTED MEMBER VARIABLES =====================================**/
    const MFType _type;
    const LinguisticVariable *const _proprietary;

    double *const _params;
    const tsize _paramNumber;

private:
/**===================================== PRIVATE STATIC VARIABLES =====================================**/
    static const tsize MFSizes[MAX_TYPE];

};

}
}
}

#endif // IMEMBERFUNCTION_HPP









