# maira-parser
A college project, a LOGO style compiler and virtual machine

Es una maquina virtual para un proyecto de la universidad, compila a codigo OP y luego grafica, como el viejo LOGO

Usa Allegro 4, probado en Linux Mint, DOS, y Windows con GCC

- levantar el archivo
- parsear linea a linea y separarlo en parametros> integer, string

el programa se guarda 
+ linea de codigo
	+ instruccion (op code)
	+ parametro 
		+ string
		+ integer

------
primera pasada compila

segunda pasada ejecuta

-------

sintaxis>

ESPERAR
LIMPIAR
COLOR R G B
LINEA X1 Y1 X2 Y2
RECTANGULO X1 Y1 X2 Y2
RECTANGULO_LLENO X1 Y1 X2 Y2
CIRCULO X1 Y1 RADIO
CIRCULO_LLENO X1 Y1 RADIO
