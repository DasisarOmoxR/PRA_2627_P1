#include <ostream>
#include <stdexcept>
#include <iostream>
#include "List.h"

template <typename T>
class ListArray : public List<T> {

	private:
		
		T* arr;
		int max;
		int n;
		static const int MINSIZE = 2;
	
	public:

		ListArray();
		~ListArray() override;

		T operator [](int pos);

		// Declaración explícita de que la función amiga es template
		template <typename U>
		friend std::ostream& operator <<(std::ostream &out, ListArray<U> &List);

		void insert(int pos, T e);
		void append(T e);
		void prepend(T e);

		T remove(int pos);
		T get(int pos);

		int search(T e);
		bool empty();
		int size();

	private:

		void resize(int new_size);
};

template <typename T>
ListArray<T>::ListArray() : arr(new T[MINSIZE]), max(MINSIZE), n(0) {}

template <typename T>
ListArray<T>::~ListArray() { delete[] arr; arr = nullptr; }

template <typename T>
T ListArray<T>::operator[](int pos) {
	if (pos < 0 || pos > size() - 1) throw std::out_of_range("Posición invalida! \n");
	else return arr[pos];
}

template <typename T>
std::ostream& operator <<(std::ostream &out, ListArray<T> &List) {

	out << "=================" << std::endl;
	out << "Array: " << List.arr << std::endl;
	out << "Tamaño actual del array: " << List.max << std::endl;
	out << "Número de elementos en el array: " << List.n << std::endl;
	out << "=================" << std::endl;
	return out;
}

template <typename T>
void ListArray<T>::insert(int pos, T e) {

	// Validamos que la posición sea válida
	if (pos < 0 || pos > size()) throw std::out_of_range("Posición inválida! \n");

	// Validamos que haya espacio en el array, si no lo hay, duplicamos su tamaño
	if (n + 1 > max) resize(max * 2);

	// Desplazamos los valores a partir de pos a la derecha
	int i = n;
	while (i > pos) { arr[i] = arr[i - 1]; i--; }

	// Colocamos el nuevo elemento en la posición libre
	arr[pos] = e;

	// Incrementamos el número de elementos del array
	n++;
}

template <typename T>
void ListArray<T>::append(T e) {

	// Validamos que haya espacio en el array, si no lo hay, duplicamos su tamaño
	if (n + 1 > max) resize(max * 2);

	// Colocamos el nuevo elemento al final del array
	arr[n] = e;

	// Incrementamos el número de elementos del array
	n++;
}

template <typename T>
void ListArray<T>::prepend(T e) {

	// Validamos que haya espacio en el array, si no lo hay, duplicamos su tamaño
	if (n + 1 > max) resize(max * 2);

	// Desplazamos todos los valores a la derecha
	for (int i = n; i > size(); i--) arr[i] = arr[i - 1];

	// Colocamos el nuevo elemento al inicio del array
	arr[0] = e;

	// Incrementamos el número de elementos del array
	n++;
}

template <typename T>
T ListArray<T>::remove(int pos) {

	// Validamos que la posición sea válida
	if (pos < 0 || pos > size()) throw std::out_of_range("Posición inválida! \n");

	// Nos guardamos una copia del elemento a eliminar
	T aux = arr[pos];

	// Desplazamos los valores del array
	for (int i = pos; i < n; i++) arr[i] = arr[i + 1];

	n--;
	return aux;
}

template <typename T>
T ListArray<T>::get(int pos) {
	
	// Validamos que la posición sea válida
	if (pos < 0 || pos > size()) throw std::out_of_range("Posición inválida! \n");

	return arr[pos];
}

template <typename T>
int ListArray<T>::search(T e) {
	
	// Recorremos todo el array, si entcontramos el elemento, devolvemos el índice
	for (int i = 0; i < size(); i++) if (arr[i] == e) return i;

	// Si no hemos encontrado el elemento, devolvemos -1
	return -1;
}

template <typename T>
bool ListArray<T>::empty() { return n == 0; }

template <typename T>
int ListArray<T>::size() { return n; }


template <typename T>
void ListArray<T>::resize(int new_size) {

	// Creamos un nuevo array para la lista
	T* new_arr = new T[new_size];

	// Asignamos los elementos del array antiguo al nuevo
	for (int i = 0; i < n; i++) new_arr[i] = arr[i];

	// Borramos el puntero del array y hacemos que apunte al nuevo array creado
	delete[] arr;
	arr = new_arr;
	
	// Actualizamos el tamaño establecido al nuevo
	max = new_size;

}