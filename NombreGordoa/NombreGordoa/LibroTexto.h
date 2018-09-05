#include "libro.h"

class LibroTexto : public Libro {
private:
	string materia;

public:
	LibroTexto();
	LibroTexto(string autor, string titulo, string editorial, string materia);

	string getMateria();
	void setMateria(string m);

	void imprime();
};