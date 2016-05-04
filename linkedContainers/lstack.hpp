#ifndef LSTACK
#define LSTACK

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
 * \file    lstack.hpp                                          *
 *                                                              *
 ****************************************************************/

/**===================*~* STL LIBRARIES *~*===================**/
#include <stdexcept>

/**===================*~* OWN LIBRARIES *~*===================**/
#include "linkedcontainers.hpp"

namespace linkedContainers
{

template<typename T>
class LStack
{
public:
/**===================================== CONSTRUCTORS =====================================**/
    LStack();
    LStack(const LStack<T> &copyStack);
    LStack(T *array, tsize length);

/**===================================== DESTRUCTOR =====================================**/
    virtual ~LStack();

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
    void push(const T &elem);
    void pop();
    void pop() const;
    //this method can throws std::out_of_range
    T &top();
    //this method can throws std::out_of_range
    const T &top() const;
    tsize size() const;
    bool isEmpty();
    bool isEmpty() const;
    void toArray(T *array, tsize &length) const;
    void clear();
    void clear() const;

/**===================================== PUBLIC OVERLOADED OPERATORS =====================================**/
    LStack<T> &operator = (const LStack<T> &copyStack)
    {
        Node<T> *aux = _stack;
        Node<T> *cpy_aux = copyStack._stack->next;

        clear();
        _size = copyStack._size;
        while(cpy_aux != NULL)
        {
            aux->next = new Node<T>;
            aux = aux->next;
            aux->data = cpy_aux->data;
            cpy_aux = cpy_aux->next;
        }
        aux->next = NULL;
        _current = _stack->next;

        return *this;
    }

    LStack<T> &operator = (LStack<T> &&copyStack)
    {
        _current = _stack->next = copyStack._stack->next;
        _size = copyStack._size;

        _current = copyStack._stack->next = NULL;
        copyStack._size = 0;

        return *this;
    }

private:
/**===================================== PRIVATE MEMBER VARIABLES =====================================**/
    Node<T>* _stack;
    Node<T>* _current;
    tsize _size;
};

/**===================================== CONSTRUCTORS =====================================**/
template<typename T>
LStack<T>::LStack()
{
    _stack = new Node<T>;
    _stack->next = NULL;
    _current = NULL;
    _size = 0;
}

template<typename T>
LStack<T>::LStack(const LStack<T> &copyStack)
{
    _stack = new Node<T>;
    _stack->next = NULL;
    *this = copyStack;
}

template<typename T>
LStack<T>::LStack(T *array, tsize length)
{
    Node<T> *aux;

    _stack = new Node<T>;
    _stack->next = NULL;
    _size = length;
    aux = _stack;
    for(int i = 0; i < length; i++)
    {
        aux->next = new Node<T>;
        aux = aux->next;
        aux->data = array[i];
    }
    aux->next = NULL;
    _current = _stack->next;
}

/**===================================== DESTRUCTOR =====================================**/
template<typename T>
LStack<T>::~LStack()
{
    clear();
    delete _stack;
}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
template<typename T>
void LStack<T>::push(const T &elem)
{
    Node<T> *aux;

    aux = new Node<T>;
    aux->data = elem;
    aux->next = _stack->next;
    _current = _stack->next = aux;
    _size++;
}

template<typename T>
void LStack<T>::pop()
{
    Node<T>* aux = _stack->next;

    if(aux != NULL)
    {
        _current = _stack->next = aux->next;
        delete aux;
        _size--;
    }
}

template<typename T>
void LStack<T>::pop() const
{
    if(_current != NULL)
        const_cast<LStack<T>*>(this)->_current = _current->next;
}

//this method can throws std::out_of_range
template<typename T>
T &LStack<T>::top()
{
    if(isEmpty())
        throw std::out_of_range("Empty Stack");
    return _stack->next->data;
}

template<typename T>
const T &LStack<T>::top() const
{
    if(isEmpty())
        throw std::out_of_range("Empty Stack");
    return _current->data;
}

template<typename T>
tsize LStack<T>::size() const
{
    return _size;
}

template<typename T>
bool LStack<T>::isEmpty()
{
    return _stack->next == NULL;
}

template<typename T>
bool LStack<T>::isEmpty() const
{
    return _current == NULL;
}

template<typename T>
void LStack<T>::toArray(T *array, tsize &length) const
{
    Node<T> *aux = _stack->next;
    length = 0;

    while(aux != NULL)
    {
        array[length++] = aux->data;
        aux = aux->next;
    }
}

template<typename T>
void LStack<T>::clear()
{
    Node<T> *aux;

    while(_stack->next != NULL)
    {
        aux = _stack->next;
        _stack->next = aux->next;
        delete aux;
    }
    _size = 0;
}

template<typename T>
void LStack<T>::clear() const
{
    const_cast<LStack<T>*>(this)->_current = _stack->next;
}

}

#endif // LSTACK

