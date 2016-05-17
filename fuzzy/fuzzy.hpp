#ifndef FUZZY_HPP
#define FUZZY_HPP

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
 * \file    fuzzy.hpp                                           *
 *                                                              *
 ****************************************************************/

/**===================*~* OWN LIBRARIES *~*===================**/
#include "knowledgeModule/knowledgemodule.hpp"
#include "memoryModule/memorymodule.hpp"

namespace fuzzy
{

/**===============================*~* NAMESPACE TYPES *~*===============================**/
typedef unsigned int tsize;

/**===============================*~* NAMESPACE ENUMS *~*===============================**/
enum LogicalOperators
{
    AND,
    OR,
    NOT,
    XOR
};

enum LogicalFunctions
{
    AVERAGE,
    MINIMUM,
    MAXIMUM,
    COMPLEMENT,
    DIFFERENCE,
    CUSTOM
};

/**===============================*~* NAMESPACE CLASES *~*===============================**/
class FuzzyEngine;

}

#endif // FUZZY_HPP

