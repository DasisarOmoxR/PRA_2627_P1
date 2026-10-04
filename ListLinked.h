#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

    private:

        Node<T>* first;
        int n;

    public:

        ListLinked();
        ~ListLinked();

        T operator [](int pos);

		// Declaración explícita de que la función amiga es template
		template <typename U>
		friend std::ostream& operator <<(std::ostream &out, ListLinked<U> &List);
};

template <typename T>
ListLinked<T>::ListLinked() : first(nullptr), n(0) {}

template <typename T>
ListLinked<T>::~ListLinked() {

    // Recorremos todos los nodos, eliminando el nodo y haciendo que el puntero de first apunte al siguiente
    while(first != nullptr) {

        Node<T>* aux = first -> next;
        delete first;
        first = aux;
    }
}

template <typename T>
T ListLinked<T>::operator[](int pos) {

	if (pos < 0 || pos > Node<T>::size() - 1) throw std::out_of_range("Posición invalida! \n");

	else {
        for (int i = 0; i < pos; i++) first = first -> next;
        return first;
    }
}

template <typename T>
std::ostream& operator <<(std::ostream &out, ListLinked<T> &List) {
    
	out << "=================" << std::endl;
    out << "Elemento: " << List.first -> data << std::endl;
	out << "=================" << std::endl;

	return out;
}