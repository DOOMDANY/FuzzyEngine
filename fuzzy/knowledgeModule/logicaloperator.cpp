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
 * \file    logicaloperator.cpp                                 *
 *                                                              *
 ****************************************************************/

/**===================*~* CLASS DEFINITION *~*===================**/
#include "logicaloperator.hpp"

/**===================*~* CLASS DEFINITION *~*===================**/
#include "util/util.hpp"
#include "fuzzy/exceptions/commonexception.hpp"

using namespace std;
using namespace fuzzy;
using namespace fuzzy::knowledgeModule;
using namespace fuzzy::exceptions;
using namespace util;

/**===================================== PUBLIC STATIC FUNCTIONS =====================================**/
double LogicalOperator::average(const double *list, int n)
{
    double result = 0.0;

    for(int i = 0; i < n; i++)
        result += list[i];
    result /= n;

    return result;
}

double LogicalOperator::average(double a, double b)
{
    return (a + b) / 2.0;
}

double LogicalOperator::complement(double a)
{
    return 1 - a;
}

double LogicalOperator::maximum(double a, double b)
{
    return a > b ? a : b;
}

double LogicalOperator::minimum(double a, double b)
{
    return a < b ? a : b;
}

double LogicalOperator::absoluteDifference(double a, double b)
{
    if(a < b)
        return b - a;
    return a - b;
}

double LogicalOperator::unaryOperation(double a, LogicalFunctions function)
{
    switch(function)
    {
        case COMPLEMENT:
            return complement(a);
            break;
        default:
            return 0.0;
    }
}

double LogicalOperator::binaryOperation(double a, double b, LogicalFunctions function)
{
    switch(function)
    {
        case AVERAGE:
            return average(a, b);
            break;
        case MINIMUM:
            return minimum(a, b);
            break;
        case MAXIMUM:
            return maximum(a, b);
            break;
        case DIFFERENCE:
            return absoluteDifference(a, b);
            break;
        default:
            return 0.0;
    }
}

int LogicalOperator::toLogicalOperator(char c)
{
    if(c == '&')
        return AND;
    else if(c == '|')
        return OR;
    else if(c == '~')
        return NOT;
    else if(c == '^')
        return XOR;
    else
        return -1;
}

int LogicalOperator::toLogicalOperator(const std::string &str)
{
    string upperStr = toUpper(str);

    if(upperStr == "AND")
        return AND;
    else if(upperStr == "OR")
        return OR;
    else if(upperStr == "NOT")
        return NOT;
    else if(upperStr == "XOR")
        return XOR;
    else
        return -1;
}

int LogicalOperator::priority(LogicalOperators logicalOperator)
{
    if(logicalOperator == NOT)
        return 3;
    else if(logicalOperator == AND)
        return 2;
    else if(logicalOperator == XOR)
        return 1;
    else if(logicalOperator == OR)
        return 0;
    else
        return -1;
}

/**===================================== CONSTRUCTORS =====================================**/
LogicalOperator::LogicalOperator(LogicalOperators type) :
    IRulePart(),
    _type(type)
{
    if(type < AND || type > XOR)
        throw CommonException(CommonException::DUPLICATED_ITEM);
}

/**===================================== SETTER & GETTER =====================================**/
LogicalOperators LogicalOperator::type() const
{
    return _type;
}

int LogicalOperator::priority() const
{
    if(_type == NOT)
        return 3;
    else if(_type == AND)
        return 2;
    else if(_type == XOR)
        return 1;
    else
        return 0;
}

void LogicalOperator::setType(LogicalOperators type)
{
    if(type < AND || type > XOR)
        throw CommonException(CommonException::BAD_INSTANCE);

    _type = type;
}








