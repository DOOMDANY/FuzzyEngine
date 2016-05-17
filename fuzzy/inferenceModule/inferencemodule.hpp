#ifndef INFERENCEMODULE_HPP
#define INFERENCEMODULE_HPP


/*! *************************************************************
 *                                                              *
 * \author  Daniel Alejandro Plascencia Ruiz.                   *
 *          Guadalajara, Jalisco, México.                       *
 *          dapr.service@gmail.com                              *
 *          Tel. (33) 3812 5330                                 *
 *          Cel. +52 1 33 1074 1591                             *
 * \date    May, 2016                                           *
 * \version 0.3                                                 *
 *                                                              *
 * \file    inferencemodule.hpp                                 *
 *                                                              *
 ****************************************************************/

/**===================*~* OWN LIBRARIES *~*===================**/
#include "fuzzy/fuzzy.hpp"

namespace fuzzy
{
namespace inferenceModule
{

/**===================================== NAMESPACE MEMBERS =====================================**/
enum DefuzzyTypes
{
    SUGENO,
    MAMDANI,
    TSUKAMOTO
};

enum DefuzzyFunctions
{
    CENTROID,
    AREA_CENTER,
    WEIGHTED_AVERAGE,
    FIRST_MAX,
    SUGENO_FUNC,
    TSUKAMOTO_FUNC
};

/**===================================== NAMESPACE CLASSES =====================================**/
class InferenceEngine;

}
}

#endif // INFERENCEMODULE_HPP














