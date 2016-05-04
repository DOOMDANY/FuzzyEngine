#ifndef LOGICALOPERATOR_HPP
#define LOGICALOPERATOR_HPP

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
 * \file    logicaloperator.hpp                                 *
 *                                                              *
 ****************************************************************/

/**===================*~* STL LIBRARIES *~*===================**/
#include <string>

/**===================*~* OWN LIBRARIES *~*===================**/
#include "knowledgemodule.hpp"
#include "irulepart.hpp"

namespace fuzzy
{
namespace knowledgeModule
{

class LogicalOperator : public IRulePart
{
public:
/**===================================== PUBLIC STATIC FUNCTIONS =====================================**/
    static double average(const double *list, int n);
    static double complement(double a);
    static double maximum(double a, double b);
    static double minimum(double a, double b);
    static double absoluteDifference(double a, double b);

    static int toLogicalOperator(char c);
    static int toLogicalOperator(const std::string &str);
    static int priority(LogicalOperators logicalOperator);

/**===================================== CONSTRUCTORS =====================================**/
    //it can throws fuzzy::exceptions::BadInstanceException
    LogicalOperator(LogicalOperators type = AND);

/**===================================== SETTER & GETTER =====================================**/
    //it can throws fuzzy::exceptions::BadInstanceException
    void setType(LogicalOperators type);
    LogicalOperators type() const;

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    int priority() const;

private:
/**===================================== PRIVATE MEMBER VARIABLES =====================================**/
    LogicalOperators _type;
};

}
}

#endif // LOGICALOPERATOR_HPP
