#include "linea.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <stdlib.h>

Linea::Linea()
{
	opcode = 0;	
}

Linea::~Linea()
{
	tokens.clear();
	tokens_i.clear();
}


// tokenizador
void Linea::Tokenize(const std::string& str,
                      std::vector<std::string>& tokens,
                      const std::string& delimiters)
{
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}


// devuelve true si error, false si todo ok
bool Linea::parsear(const char *l)
{
	linea = l;
	// sacar espacios adelante y atras a la linea
	// le saco los numeros y eso pq es basura que queda en los nombres de MP3s...
	size_t lspace=linea.find_first_not_of(" \n\r\t");
	if (lspace!=std::string::npos)
		linea = linea.substr(lspace);

	size_t rspace=linea.find_last_not_of(" \n\r\t");
	if (rspace!=std::string::npos)
		linea.erase(rspace+1);
	else
	{
		linea.clear(); // es todo en blanco, ignorar la linea
		return true;
	}

	// cortar en pedazos
 	Tokenize(linea, tokens);

	// convertir a integer y almacenar
	for (unsigned int i =0; i < tokens.size(); i++)
	{
		tokens_i.push_back(atoi(tokens[i].c_str()));
	}


	// es un comentario? decirle que lo ignore
	if (tokens[0].compare("//")==0)
	{
		return true;
	}

	// pasar a mayusculas el comando
	for (unsigned int i=0; i < tokens[0].size();i++)
	{
			tokens[0][i]=toupper(tokens[0][i]);
	}	

	// DEBUG mostrar parametro
	for (unsigned int i =0; i < tokens.size(); i++)
		printf("P[%d] > %s == %d\n", i, tokens[i].c_str(), tokens_i[i]);


	return false;
}
