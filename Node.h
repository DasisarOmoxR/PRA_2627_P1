#include <ostream>
#include <stdexcept>
#include <iostream>

template <typename T>
class Node {

    public:

    T data;
    Node<T>* next;

    Node(T d, Node<T>* n);
    Node(T d);

    // Declaración explícita de que la función amiga es template
	template <typename U>
	friend std::ostream& operator <<(std::ostream &out,const Node<U> &Node);

};

template <typename T>
Node<T>::Node(T d, Node<T>* n) : data(d), next(n) {}

template <typename T>
Node<T>::Node(T d) : data(d), next(nullptr) {}

template <typename T>
std::ostream& operator <<(std::ostream &out,const Node<T> &Node) {
    
    out << "=================" << std::endl;
	out << "Data: " << Node.data << std::endl;
    out << "=================" << std::endl;

    return out;
}