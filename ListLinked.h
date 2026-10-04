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

        void insert(int pos, T e);
		void append(T e);
		void prepend(T e);

		T remove(int pos);
		T get(int pos);

		int search(T e);
		bool empty();
		int size();
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

template <typename T>
void ListLinked<T>::insert(int pos, T e) {

	// Validamos que la posición sea válida
	if (pos < 0) throw std::out_of_range("Posición inválida! \n");

    // Creamos un nuevo nodo a partir de e
    T nuevo_nodo = new Node(e);

    // Nos desplazamos hasta el puntero que queremos que apunte al nuevo nodo
    for (int i = 0; i < pos - 1; i++) first = first -> next;

    // Insertamos el nuevo elemento y actualizamos su puntero
    T aux = first -> next
    first -> next = nuevo_nodo:
    nuevo_nodo -> next = aux;

	// Incrementamos el número de elementos de la lista 
    n++;
}

template <typename T>
void ListLinked<T>::append(T e) {


    // Nos desplazamos hasta el puntero que apunte a nullptr (final de la lista)
    while (first -> next != nullptr) first = first -> next;

    // Creamos un nuevo nodo a partir de e
    T nuevo_nodo = new Node(e);

    // Insertamos el nuevo elemento
    first -> next = nuevo_nodo;

	// Incrementamos el número de elementos del array
	n++;
}

template <typename T>
void ListLinked<T>::prepend(T e) {

    // Creamos un nuevo nodo a partir de e
    T nuevo_nodo = new Node(e);

	// Colocamos el nuevo elemento al inicio de la lista y actualizamos su puntero
    T aux = first;
	first = nuevo_nodo:
    first -> next = aux;

	// Incrementamos el número de elementos del array
	n++;
}

template <typename T>
T ListLinked<T>::remove(int pos) {

	// Validamos que la posición sea válida
	if (pos < 0) throw std::out_of_range("Posición inválida! \n");

	
    // Nos desplazamos hasta el puntero que apunta al elemento a eliminar
    for (int i = 0; i < pos - 1; i++) first = first -> next;

    // Nos guardamos una copia del elemento a eliminar
	T aux = first -> next;

    // Eliminamos el elemento y actualizamos el puntero
    delete first -> next
    first next = aux -> next;

	n--;
	return aux;
}

template <typename T>
T ListLinked<T>::get(int pos) {
	
	// Validamos que la posición sea válida
	if (pos < 0 || pos >= size()) throw std::out_of_range("Posición inválida! \n");
    
    // Nos desplazamos hasta el puntero que apunta al elemento a devolver
    for (int i = 0; i < pos - 1; i++) first = first -> next;

	return first -> next;
}

template <typename T>
int ListLinked<T>::search(T e) {
	
	// Recorremos toda la lista, si entcontramos el elemento, devolvemos el índice
    int i = 0;
	while (first != nullptr) { if (first -> data == e) return i; first = first -> next; i++;}

	// Si no hemos encontrado el elemento, devolvemos -1
	return -1;
}

template <typename T>
bool ListLinked<T>::empty() { return n == 0; }

template <typename T>
int ListLinked<T>::size() { return n; }