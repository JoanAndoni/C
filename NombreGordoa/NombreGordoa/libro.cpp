#include "libro.h"

Libro::Libro()
{
	autor = "";
	titulo = "";
	editorial = "";
}

Libro::Libro(string autor, string titulo, string editorial)
{
	autor = autor;
	titulo = titulo;
	editorial = editorial;
}

string Libro::getAutor()
{
	return autor;
}

void Libro::setAutor(int a)
{
	autor = a;
}

string Libro::getEditorial()
{
	return editorial;
}

void Libro::setEditorial(int e)
{
	editorial = e;
}

string Libro::getTitulo()
{
	return titulo;
}

void Libro::setTitutlo(int t)
{
	titulo = t;
}

float Libro::imprimir()
{
}