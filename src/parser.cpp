#include "parser.h"
#include <allegro.h>
#include <stdio.h>
#include "gerror.h" // manejo de errores

Parser::Parser()
{
}

Parser::~Parser()
{
	// DEBUG - TODO - descargar todo aca

	for (unsigned int i=0; i < codigo.size(); i++)
	{
		delete(codigo[i]);
	}
	codigo.clear();

}

// devuelve false si todo ok, true si fallo
bool Parser::cargar(const char *archivo)
{
	char linea[1024];

	FILE *pf = fopen (archivo,"r");

	if (!pf) 
		return true; // fallo

	// leer el puto archivo
	while(fgets(linea,sizeof(linea),pf) != NULL)
	{
		// parsear linea - TODO
		printf("%s", linea); // mostrar
		Linea *l = new Linea();
		if (l->parsear(linea))
		{
			// TODO  error de sintaxis
		}
		else
		{
			codigo.push_back(l); // cargar		
		}
	}

	fclose(pf);
	return false;
}

void Parser::ejecutar()
{
	int c = makecol(255,255,255); // color actual
  	clear_to_color(screen, makecol(0, 0, 0)); // limpiar pantalla

	// TODO hacer

	// mostrar lineas cargadas -- debug
	for (unsigned int i=0; i < codigo.size(); i++)
	{
		printf("[%d] %s\n", i+1, codigo[i]->linea.c_str());
	}


	// INTERPRETAR
	for (unsigned int i=0; i < codigo.size(); i++)
	{
			if (!codigo[i]->tokens[0].compare("ESPERAR"))
			{
				readkey(); // esperar una tecla
				clear_keybuf();
			}

			if (!codigo[i]->tokens[0].compare("LIMPIAR"))
			{
				clear_to_color(screen, c); // limpiar pantalla al ultimo color seteado
			}

			if (!codigo[i]->tokens[0].compare("COLOR")) // setear color
			{
				if (codigo[i]->tokens.size() != 4)
				{
					raise_error( "ERROR: Parametros en linea %d > %s",i+1, codigo[i]->linea.c_str() ); // error de parametros
				}
				else
				{
					c = makecol(codigo[i]->tokens_i[1],codigo[i]->tokens_i[2],codigo[i]->tokens_i[3]);
				}
			}

			if (!codigo[i]->tokens[0].compare("LINEA")) // linea
			{
				if (codigo[i]->tokens.size() != 5)
				{
					raise_error( "ERROR: Parametros en linea %d > %s",i+1, codigo[i]->linea.c_str() ); // error de parametros
				}
				else
				{
					line(screen, codigo[i]->tokens_i[1],codigo[i]->tokens_i[2],codigo[i]->tokens_i[3],codigo[i]->tokens_i[4],c);
				}
			}

			if (!codigo[i]->tokens[0].compare("RECTANGULO")) // rectangulo
			{
				if (codigo[i]->tokens.size() != 5)
				{
					raise_error( "ERROR: Parametros en linea %d > %s",i+1, codigo[i]->linea.c_str() ); // error de parametros
				}
				else
				{
					rect(screen, codigo[i]->tokens_i[1],codigo[i]->tokens_i[2],codigo[i]->tokens_i[3],codigo[i]->tokens_i[4],c);
				}
			}

			if (!codigo[i]->tokens[0].compare("RECTANGULO_LLENO")) // rectangulo lleno
			{
				if (codigo[i]->tokens.size() != 5)
				{
					raise_error( "ERROR: Parametros en linea %d > %s",i+1, codigo[i]->linea.c_str() ); // error de parametros
				}
				else
				{
					rectfill(screen, codigo[i]->tokens_i[1],codigo[i]->tokens_i[2],codigo[i]->tokens_i[3],codigo[i]->tokens_i[4],c);
				}
			}


			if (!codigo[i]->tokens[0].compare("CIRCULO")) // CIRCULO
			{
				if (codigo[i]->tokens.size() != 4)
				{
					raise_error( "ERROR: Parametros en linea %d > %s",i+1, codigo[i]->linea.c_str() ); // error de parametros
				}
				else
				{
					circle(screen, codigo[i]->tokens_i[1],codigo[i]->tokens_i[2],codigo[i]->tokens_i[3], c);
				}
			}

			if (!codigo[i]->tokens[0].compare("CIRCULO_LLENO")) // CIRCULO lleno
			{
				if (codigo[i]->tokens.size() != 4)
				{
					raise_error( "ERROR: Parametros en linea %d > %s",i+1, codigo[i]->linea.c_str() ); // error de parametros
				}
				else
				{
					circlefill(screen, codigo[i]->tokens_i[1],codigo[i]->tokens_i[2],codigo[i]->tokens_i[3], c);
				}
			}



	}


}
