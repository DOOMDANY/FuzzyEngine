#ifndef LINKEDCONTAINERS
#define LINKEDCONTAINERS

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
 * \file    linkedcontainers.hpp                                *
 *                                                              *
 ****************************************************************/

namespace linkedContainers
{
/**===================================== NAMESPACE MEMBERS =====================================**/
typedef unsigned int tsize;

/**===================================== NAMESPACE STRUCTURES =====================================**/
template<typename T>
struct Node
{
    T data;
    Node<T>* next;
};

template<typename T>
struct DLNode : public Node<T>
{
    Node<T>* prev;
};

/**===================================== NAMESPACE CLASSES =====================================**/
template<typename T>
class LStack;

}

#endif // LINKEDCONTAINERS








