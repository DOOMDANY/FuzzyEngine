#ifndef MEMBERFUNCTIONS
#define MEMBERFUNCTIONS

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
 * \file    memberfunctions.hpp                                 *
 *                                                              *
 ****************************************************************/

/**===================*~* OWN LIBRARIES *~*===================**/
#include "fuzzy/knowledgeModule/knowledgemodule.hpp"

namespace fuzzy
{
namespace knowledgeModule
{
namespace memberFunctions
{

/**===================================== NAMESPACE MEMBERS =====================================**/
enum MFType
{
    BELL,
    CUSTOM,
    GAUSSIAN,
    SIGMOID,
    SINGLETON,
    TRAPEZOID,
    TRIANGLE,
    MAX_TYPE
};

/**===================================== NAMESPACE CLASSES =====================================**/
class MembershipFunction;
class IMemberFunction;
class MFException;

}
}
}

#endif // MEMBERFUNCTIONS

