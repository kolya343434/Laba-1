#pragma once
#include <iostream>
#include <memory>
#include <exception>
#include "unique_ptr.h"

template <typename T>
class LinkedList {
    template <typename U>
    friend std::ostream& operator<<(std::ostream&, const LinkedList<U>&);
public:
    // default constructor
    LinkedList() : ptrHead{ nullptr } {}

    // copy constructor: duplicate a list object
    LinkedList(LinkedList&);

    // move constructor
    LinkedList(LinkedList&&);

    // destructor
    ~LinkedList();

    // TODO: Add overloaded assignment and move assignment operators
    // For now, just delete them.
    const LinkedList& operator=(const LinkedList&) = delete;
    const LinkedList& operator=(const LinkedList&&) noexcept = delete;

    // utility methods
    void push(const T&);
    void pop();
    T peek() const;
    void clean();
    void print(std::ostream&) const;

private:
    // basic node structure
    struct Node {
        // constructor
        explicit Node(const T& data) : element{ data }, ptrNext{ nullptr } {}
        // destructor (only for testing deallocation)
        ~Node() {
            std::cout << "Destroying Node with data " << element << std::endl;
        }

        T element;
        unique_ptr<Node> ptrNext;
    };

    unique_ptr<Node> ptrHead;  // head of the list
};


/////////////////////////////////////////////////////////////////////////////
// Implementation of Linked List

/**
 * Copy constructor
 *
 * @param list
 */
template <typename T>
LinkedList<T>::LinkedList(LinkedList& list) {
    // the new head of list
    unique_ptr<Node> ptrNewHead{ nullptr };

    // raw pointer cursor for traversing the new (copied) list
    Node* ptrCurrNode{ nullptr };

    // raw pointer for traversing the list to be copied
    Node* ptrCursor{ list.ptrHead.get() };

    while (ptrCursor) {
        // allocate a new node, copying the element of the current node
        unique_ptr<Node>
            ptrTemp{ unique_ptr<Node>(ptrCursor->element) };

        // add it to the new list, as appropriate
        if (ptrNewHead == nullptr) {
            ptrNewHead = std::move(ptrTemp);
            ptrCurrNode = ptrNewHead.get();
        }
        else {
            ptrCurrNode->ptrNext = std::move(ptrTemp);
            ptrCurrNode = ptrCurrNode->ptrNext.get();
        }

        ptrCursor = ptrCursor->ptrNext.get();
    }

    ptrHead = std::move(ptrNewHead);
}

/**
 * Copy move constructor
 *
 * @param list
 */
template <typename T>
LinkedList<T>::LinkedList(LinkedList&& list) {
    ptrHead = std::move(list.ptrHead);
}

// TODO: Add overloaded assignment and move assignment operators

/**
 * Destructor
 *
 */
template <typename T>
LinkedList<T>::~LinkedList() {
    clean();
}

/**
 * Push a T value onto the list
 *
 * @param data
 */
template <typename T>
void LinkedList<T>::push(const T& data) {
    auto ptrTemp = unique_ptr<Node>(data);
    ptrTemp->ptrNext = std::move(ptrHead);
    ptrHead = std::move(ptrTemp);
}


/**
 * Pop the top element off the list
 *
 */
template <typename T>
void LinkedList<T>::pop() {
    if (ptrHead == nullptr) {
        return;
    }

    // can we safely avoid the ptrDetached intermediary?
    // std::unique_ptr<Node> ptrDetached = std::move(ptrHead);
    // ptrHead = std::move(ptrDetached->ptrNext);

    ptrHead = std::move(ptrHead->ptrNext);
}

/**
 * Peek at the value of the top element.
 *
 * Throws an exception if the list is empty.
 *
 * @return
 */
template <typename T>
T LinkedList<T>::peek() const {
    if (ptrHead == nullptr) {
        throw std::out_of_range{ "Empty list: Attempt to dereference a NULL pointer" };
    }
    return ptrHead->element;
}

/**
 * Clean the list
 *
 */
template <typename T>
void LinkedList<T>::clean() {
    while (ptrHead) {
        // can we safely avoid the ptrDetached intermediary?
        // std::unique_ptr<Node> ptrDetached = std::move(ptrHead);
        // ptrHead = std::move(ptrDetached->ptrNext);
        ptrHead = std::move(ptrHead->ptrNext);
    }
}

/**
 * Print the list on ostream os
 *
 * @param os
 */
template <typename T>
void LinkedList<T>::print(std::ostream& os) const {
    Node* ptrCursor{ ptrHead.get() }; // raw pointer for iteration

    while (ptrCursor) {
        os << ptrCursor->element << " -> ";
        ptrCursor = ptrCursor->ptrNext.get();
    }
    os << "NULL" << std::endl;
}


/**
 * Overloaded operator << for the LinkedList
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
    list.print(os);
    return os;
}