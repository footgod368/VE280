#ifndef DLIST_IMPL_H
#define DLIST_IMPL_H

template <class T>
Dlist<T>::Dlist() : first(NULL), last(NULL) {}

template <class T>
void Dlist<T>::insertFront(T *op)
{
    node *newNode = new node;
    newNode->next = first;
    newNode->prev = NULL;
    newNode->op = op;
    if (isEmpty())
    {
        first = last = newNode;
    }
    else
    {
        first->prev = newNode;
        first = newNode;
    }
}

template <class T>
void Dlist<T>::insertBack(T *op)
{
    node *newNode = new node;
    newNode->next = NULL;
    newNode->prev = last;
    newNode->op = op;
    if (isEmpty())
    {
        first = last = newNode;
    }
    else
    {
        last->next = newNode;
        last = newNode;
    }
}

template <class T>
bool Dlist<T>::isEmpty() const
{
    return first == NULL && last == NULL;
}

template <class T>
T *Dlist<T>::removeFront()
{
    if (isEmpty())
    {
        emptyList e;
        throw e;
    }
    T *result;
    if (first == last)
    {
        result = first->op;
        first = last = NULL;
    }
    else
    {
        node *victim = first;
        first = victim->next;
        first->prev = NULL;
        result = victim->op;
        delete victim;
    }
    return result;
}

template <class T>
T *Dlist<T>::removeBack()
{
    if (isEmpty())
    {
        emptyList e;
        throw e;
    }
    T *result;
    if (first == last)
    {
        result = last->op;
        first = last = NULL;
    }
    else
    {
        node *victim = last;
        last = victim->prev;
        last->next = NULL;
        result = victim->op;
        delete victim;
    }
    return result;
}

template <class T>
void Dlist<T>::removeAll()
{
    while (first)
    {
        T *victim = removeFront();
        delete victim;
    }
}

template <class T>
void Dlist<T>::copyAll(const Dlist &l)
{
    node *p = l.last;
    while (p)
    {
        T *thisObject = new T(*p->op);
        insertFront(thisObject);
        p = p->prev;
    }
}

template <class T>
Dlist<T>::Dlist(const Dlist &l) : first(NULL), last(NULL)
{
    copyAll(l);
}

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l)
{
    if (this != &l)
    {
        removeAll();
        copyAll(l);
    }
    return *this;
}

template <class T>
Dlist<T>::~Dlist()
{
    removeAll();
}

#endif