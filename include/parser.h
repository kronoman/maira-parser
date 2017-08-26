#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "linea.h"

class Parser
{
	public:
		Parser();
		~Parser();

		bool cargar(const char *archivo);
		void ejecutar();

	private:


	std::vector <Linea *>codigo; // lineas de codigo ya parseadas
};

#endif
