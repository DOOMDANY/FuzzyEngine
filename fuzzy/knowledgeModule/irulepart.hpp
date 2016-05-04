#ifndef IRULEPART_HPP
#define IRULEPART_HPP

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
 * \file    irulepart.hpp                                       *
 *                                                              *
 ****************************************************************/

/**===================*~* OWN LIBRARIES *~*===================**/
#include "knowledgemodule.hpp"

namespace fuzzy
{
namespace knowledgeModule
{

class IRulePart
{
public:
/**===================================== CONSTRUCTORS =====================================**/
    IRulePart();

/**===================================== DESTRUCTOR =====================================**/
    virtual ~IRulePart();
};

}
}

#endif // IRULEPART_HPP








