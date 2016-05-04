#ifndef EXCEPTIONS
#define EXCEPTIONS

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
 * \file    exceptions.hpp                                      *
 *                                                              *
 ****************************************************************/

/**===================*~* OWN LIBRARIES *~*===================**/
#include "fuzzy.hpp"

namespace fuzzy
{
namespace exceptions
{

/**===================================== NAMESPACE CLASSES =====================================**/
class BadInstanceException;
class DuplicatedItemException;
template<class T>
class NonExistentElementException;

}
}

#endif // EXCEPTIONS

