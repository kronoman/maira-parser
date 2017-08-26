#ifndef LINEA_H
#define LINEA_H
#include <string>
#include <vector>

class Linea
{
	public:
		Linea();
		~Linea();
		
		bool parsear(const char *l); // parsea la linea y la almacena


// todo publico para menos complicacion

		static const int max_p=20; // cantidad maxima de parametros que soporta

		int opcode; // codigo de operacion de la instruccion
		
		std::vector<std::string> tokens; // parametros en formato string
		std::vector<int> tokens_i; // parametros en formato integer

		std::string linea; // la linea completa, por si la necesito...

	private:
		void Tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " "); // auxiliar
};

#endif
