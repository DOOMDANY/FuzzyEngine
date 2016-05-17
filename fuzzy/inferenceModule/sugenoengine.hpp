#ifndef SUGENOENGINE_HPP
#define SUGENOENGINE_HPP

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
 * \file    sugenoengines.hpp                                   *
 *                                                              *
 ****************************************************************/

/**===================*~* Stl Classes *~*===================**/
#include <map>

/**===================*~* Own Classes *~*===================**/
#include "inferenceengine.hpp"
#include "fuzzy/knowledgeModule/logicaloperator.hpp"

namespace fuzzy
{
namespace inferenceModule
{

class SugenoEngine : public InferenceEngine
{
public:
/**===================*~* CONSTRUCTORS *~*===================**/
    //this method can throws fuzzy::exceptions::CommonException(NULL_POINTER)
    SugenoEngine(const knowledgeModule::KnowledgeBase *kb, memoryModule::WorkMemory *memory);

/**===================*~* DESTRUCTOR *~*===================**/
    virtual ~SugenoEngine();

/**===================*~* PUBLIC MEMBER FUNCTIONS *~*===================**/
    virtual void defuzzify();
    virtual void infer();

};

}
}

#endif // SUGENOENGINE_HPP













