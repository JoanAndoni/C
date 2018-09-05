#include "LibroTexto.h"

LibroTexto::LibroTexto()
{
	materia = "";
}

LibroTexto::LibroTexto(string autor, string titulo, string editorial, string materia)
{
	autor = autor;
	titulo = titulo;
	editorial = editorial;
	materia = materia;
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