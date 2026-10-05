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

    // Definimos un auxiliar para recorrer la lista
    Node<T>* actual = first;

	if (pos < 0 || pos > n - 1) throw std::out_of_range("Posición invalida! \n");

	else {
        for (int i = 0; i < pos; i++) actual = actual -> next;
        return actual -> data;
    }
}

template <typename T>
std::ostream& operator <<(std::ostream &out, ListLinked<T> &List) {
    
	out << "=================" << std::endl;
    if (List.n == 0) out << "Lista vacia." << std::endl;
	else {
		out << "Lista: [";
        Node<T>* actual = List.first; // Definimos un auxiliar para recorrer la lista
		while (actual != nullptr) { out << actual -> data; if (actual -> next != nullptr) out << ", "; else out << "]" << std::endl; actual = actual -> next; }
	}
	out << "=================" << std::endl;

	return out;
}

template <typename T>
void ListLinked<T>::insert(int pos, T e) {

	// Validamos que la posición sea válida
	if (pos < 0|| pos > n) throw std::out_of_range("Posición inválida! \n");

    // Creamos un nuevo nodo a partir de e
    Node<T>* nuevo_nodo = new Node<T>(e);

    // Caso especial: Lista vacia
    if (pos == 0) { prepend(e); return; }

    // Definimos un auxiliar para recorrer la lista
    Node<T>* actual = first;

    // Nos desplazamos hasta el puntero que queremos que apunte al nuevo nodo
    for (int i = 0; i < pos - 1; i++) actual = actual -> next;

    // Insertamos el nuevo elemento y actualizamos su puntero
    Node<T>* aux = actual -> next;
    actual -> next = nuevo_nodo;
    nuevo_nodo -> next = aux;

	// Incrementamos el número de elementos de la lista 
    n++;
}

template <typename T>
void ListLinked<T>::append(T e) {

    // Creamos un nuevo nodo a partir de e
    Node<T>* nuevo_nodo = new Node<T>(e);

    // Caso especial: Lista vacia
    if (first == nullptr) {
        first = nuevo_nodo;
        n++;
    return;
    }

    // Definimos un auxiliar para recorrer la lista
    Node<T>* actual = first;

    // Nos desplazamos hasta el puntero que apunte a nullptr (final de la lista)
    while (actual -> next != nullptr) actual = actual -> next;

    // Insertamos el nuevo elemento
    actual -> next = nuevo_nodo;

	// Incrementamos el número de elementos del array
	n++;
}

template <typename T>
void ListLinked<T>::prepend(T e) {

    // Creamos un nuevo nodo a partir de e
    Node<T>* nuevo_nodo = new Node<T>(e);

	// Colocamos el nuevo elemento al inicio de la lista y actualizamos su puntero
    nuevo_nodo -> next = first;
	first = nuevo_nodo;
    
	// Incrementamos el número de elementos del array
	n++;
}

template <typename T>
T ListLinked<T>::remove(int pos) {

	// Validamos que la posición sea válida
	if (pos < 0 || pos >= n) throw std::out_of_range("Posición inválida! \n");

    // Caso especial: Primera posición
    if (pos == 0) {

        Node<T>* aux = first;

        T dato = aux -> data;
        first = first -> next;

        delete aux;
        n--;

        return dato;
    }


    // Definimos un auxiliar para recorrer la lista
    Node<T>* actual = first;

    // Nos desplazamos hasta el puntero que apunta al elemento a eliminar
    for (int i = 0; i < pos - 1; i++) actual = actual -> next;

    // Nos guardamos una copia del dato del elemento a eliminar
    T dato = actual -> next -> data;

    // Eliminamos el elemento y actualizamos el puntero
    Node<T>* aux = actual -> next;
    actual -> next = aux -> next;
    delete aux;
    aux = nullptr;


	n--;
	return dato;
}

template <typename T>
T ListLinked<T>::get(int pos) {
	
	// Validamos que la posición sea válida
	if (pos < 0 || pos >= size()) throw std::out_of_range("Posición inválida! \n");
    
    // Definimos un auxiliar para recorrer la lista
    Node<T>* actual = first;

    // Nos desplazamos hasta el puntero que apunta al elemento a devolver
    for (int i = 0; i < pos - 1; i++) actual = actual -> next;

	return actual -> next -> data;
}

template <typename T>
int ListLinked<T>::search(T e) {
	
    // Definimos un auxiliar para recorrer la lista
    Node<T>* actual = first;

	// Recorremos toda la lista, si entcontramos el elemento, devolvemos el índice
    int i = 0;
	while (actual != nullptr) { if (actual -> data == e) return i; actual = actual -> next; i++;}

	// Si no hemos encontrado el elemento, devolvemos -1
	return -1;
}

template <typename T>
bool ListLinked<T>::empty() { return n == 0; }

template <typename T>
int ListLinked<T>::size() { return n; }