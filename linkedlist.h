#pragma once

#include <iostream>

template<typename T>
class Node;

template<typename T, typename Allocator = std::allocator<T> >
class List
{
public:
    List();
    List(const Allocator& listAlloc);
    void pushBack(T& data);
    void print();

private:
    typedef typename Allocator::template rebind<Node<T>>::other nodeAlloc;
    nodeAlloc allocator;
    Node<T>* head;
    Node<T>* tail;
};

template<typename T>
class Node
{
public:
    Node(Node* n, T d): next(n), data(d) {  }
private:
    Node* next;
    T data;

    template<typename U, typename Allocator>
    friend class List;
};

template<typename T, typename Allocator>
List<T, Allocator>::List():
    allocator{},
    head(nullptr),
    tail(nullptr)
{  }

template<typename T, typename Allocator>
List<T, Allocator>::List(const Allocator& listAlloc):
    allocator(listAlloc),
    head(nullptr),
    tail(nullptr)
{  }

template<typename T, typename Allocator>
void List<T, Allocator>::pushBack(T& data)
{
    if (head == nullptr)
    {
        head = allocator.allocate(1);
        allocator.construct(head, nullptr, data);
        tail = head;
    }
    else
    {
        tail->next = allocator.allocate(1);
        allocator.construct(tail->next, nullptr, data);
        tail = tail->next;
    }
}

template<typename T, typename Allocator>
void List<T, Allocator>::print()
{
    auto curr = head;
    while (curr != nullptr)
    {
        std::cout << curr->data << std::endl;
        curr = curr->next;
    }
}
