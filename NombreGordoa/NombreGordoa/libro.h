#include <iostream>

using namespace std;

class Libro  {
private:
	string autor;
	string titulo;
	string editorial;

public:
	Libro();

	Libro(string autor, string titulo, string editorial);

	string getAutor();
	void setAutor(string a);

	string getTitulo();
	void setTitutlo(string t);

	string getEditorial();
	void setEditorial(string e);

	void imprime();
};