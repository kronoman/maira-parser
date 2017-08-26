
#include <allegro.h>
#include <string.h>
#include <stdio.h>
#include "gerror.h" // manejo de errores
#include "parser.h" // parseador

// chequea un comando de la linea de parametros
int chequear_comando( int argc, char *argv[], char *search_command )
{
	for ( int i = 1; i < argc; i++ )
		if ( stricmp( argv[ i ], search_command ) == 0 )
			return -1;

	return 0;
}

// arranca la libreria allegro
void arrancar_allegro( int vid_m, int vid_w, int vid_h, int color_depth, int want_sound )
{
	int desk_bpp;

	allegro_init(); 

	desk_bpp = desktop_color_depth(); // esto hace que ande mas rapido

	if ( desk_bpp != 8 && desk_bpp != 0 && color_depth < 8 )
		color_depth = desk_bpp; // bpp del escritorio

	if ( color_depth < 8 )
		color_depth = 16; // necesito por lo menos 16 bpp

	srand( time( NULL ) ); // numeros al azar

	if ( install_timer() != 0 )
		raise_error( "arrancar_allegro() : can't install timer driver" );


	if ( install_keyboard() != 0 )
		raise_error( "arrancar_allegro() : can't install keyboard driver" );

	set_color_depth( color_depth );

	if ( set_gfx_mode( vid_m, vid_w, vid_h, 0, 0 ) )
	{
		set_color_depth( 16 );

		if ( set_gfx_mode( vid_m, vid_w, vid_h, 0, 0 ) )
		{
			set_color_depth( 32 );

			if ( set_gfx_mode( vid_m, vid_w, vid_h, 0, 0 ) )
			{
				set_color_depth( 24 );

				if ( set_gfx_mode( vid_m, vid_w, vid_h, 0, 0 ) )
				{
					set_color_depth( 15 );

					if ( set_gfx_mode( vid_m, vid_w, vid_h, 0, 0 ) )
					{
						raise_error( "arrancar_allegro() : I can't set the graphics mode (%3d x %3d @ %2d bpp)\nI also tried with 16 bpp, 15 bpp, 32 bpp and 24 bpp\n", vid_w, vid_h, color_depth );
					}
				}
			}
		}
	}


}

// arranca el hardware
void arrancar_main( int argc, char *argv[] )
{
	int vid_m = GFX_AUTODETECT_FULLSCREEN;
	int color_depth = -1; 
	int vid_w = 640;
	int vid_h = 480;

	if ( chequear_comando( argc, argv, "-w" ) )
		vid_m = GFX_AUTODETECT_WINDOWED;

	if ( chequear_comando( argc, argv, "-win" ) )
		vid_m = GFX_AUTODETECT_WINDOWED;

	if ( chequear_comando( argc, argv, "-bpp15" ) )
		color_depth = 15;

	if ( chequear_comando( argc, argv, "-bpp16" ) )
		color_depth = 16;

	if ( chequear_comando( argc, argv, "-bpp24" ) )
		color_depth = 24;

	if ( chequear_comando( argc, argv, "-bpp32" ) )
		color_depth = 32;


// resoluciones extra

	if ( chequear_comando( argc, argv, "-800x600" ) )
	{
		vid_w = 800;
		vid_h = 600;
	}

	if ( chequear_comando( argc, argv, "-1024x768" ) )
	{
		vid_w = 1024;
		vid_h = 768;
	}
	
	if ( chequear_comando( argc, argv, "-320x200" ) )
	{
		vid_w = 320;
		vid_h = 200;
	}

	arrancar_allegro( vid_m, vid_w, vid_h, color_depth, false );

}





int main( int argc, char *argv[] )
{
	arrancar_main( argc, argv );

	if (argc < 2)
	{
		raise_error( "Necesito saber el nombre de archivo a ejecutar, incluirlo en la linea de comandos> %s [archivo.mai]", argv[0] );
		return -1;
	}



	Parser *p = new Parser();
	if (!p->cargar(argv[1]))
	{
		p->ejecutar();
	}
	else
	{
		// TODO ERROR
		raise_error( "ERROR: No se pudo cargar> %s", argv[1] );
	}

	printf("-- FIN -- \n");

		
	return 0;
}
END_OF_MAIN();
