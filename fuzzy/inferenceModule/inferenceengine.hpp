#ifndef INFERENCEENGINE_HPP
#define INFERENCEENGINE_HPP

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
 * \file    inferenceengine.hpp                                 *
 *                                                              *
 ****************************************************************/

/**===================*~* OWN LIBRARIES *~*===================**/
#include "inferencemodule.hpp"
#include "fuzzy/knowledgeModule/knowledgebase.hpp"
#include "fuzzy/memoryModule/workmemory.hpp"

namespace fuzzy
{
namespace inferenceModule
{

class InferenceEngine
{
public:
/**===================*~* PUBLIC MEMBERS *~*===================**/
    typedef std::map<tsize, fuzzy::knowledgeModule::LinguisticVariable> mapLv;
    typedef std::map<tsize, fuzzy::knowledgeModule::memberFunctions::MembershipFunction> mapMf;
    typedef std::map<const fuzzy::knowledgeModule::memberFunctions::MembershipFunction*, double> mapMfV;
    typedef std::map<const fuzzy::knowledgeModule::LinguisticVariable*, mapMfV> mapLvMfV;

    typedef std::pair<const fuzzy::knowledgeModule::memberFunctions::MembershipFunction*, double> pairMfV;
    typedef std::pair<const fuzzy::knowledgeModule::LinguisticVariable*, mapMfV> pairLvMfV;

/**===================*~* CONSTRUCTORS *~*===================**/
    //hhis method can throws fuzzy::exceptions::CommonException(NULL_POINTER)
    InferenceEngine(const knowledgeModule::KnowledgeBase *kb, memoryModule::WorkMemory *memory);

/**===================*~* DESTRUCTOR *~*===================**/
    virtual ~InferenceEngine();

/**===================*~* SETTER & GETTER *~*===================**/
    bool setKnowledgeBase(const knowledgeModule::KnowledgeBase *kb);
    const knowledgeModule::KnowledgeBase *knowledgeBase() const;

    bool setWorkMemory(memoryModule::WorkMemory *memory);
    const memoryModule::WorkMemory *workMemory() const;

    bool setAndFunction(LogicalFunctions functionType);
    int andFunction() const;

    bool setOrFunction(LogicalFunctions functionType);
    int orFunction() const;

    bool setNotFunction(LogicalFunctions functionType);
    int notFunction() const;

    bool setXorFunction(LogicalFunctions functionType);
    int xorFunction() const;

    int lastError() const;

/**===================*~* PUBLIC MEMBER FUNCTIONS *~*===================**/
    virtual void fuzzify();
    virtual void fuzzifyAll();
    virtual void defuzzify() = 0;
    virtual void infer() = 0;

protected:
/**===================*~* PROTECTED MEMBER VARIABLES *~*===================**/
    const knowledgeModule::KnowledgeBase *_kb;
    memoryModule::WorkMemory *_memory;

    LogicalFunctions _andFunction;
    LogicalFunctions _orFunction;
    LogicalFunctions _notFunction;
    LogicalFunctions _xorFunction;

    int _lastError;

};

}
}

#endif // INFERENCEENGINE_HPP

















