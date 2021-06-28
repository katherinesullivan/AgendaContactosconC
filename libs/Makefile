# Makefile

# Macros
INTERPRETE = interprete.c
ANDOR = andor.c
TABLAHASH = tablahash.c
STREE = stree.c
SLIST = slist.c 
ARBOL = arbol.c
CONTACTO = contacto.c
ACCIONES = acciones.c
FLAGS = -Wall -Wextra -Werror -g -std=c99

.PHONY : all
all: main clean

# Ejecutable de la implementación del programa.
main: main.c $(INTERPRETE:.c=.o) $(TABLAHASH:.c=.o) $(ANDOR:.c=.o) $(STREE:.c=.o) $(SLIST:.c=.o) $(ARBOL:.c=.o) $(CONTACTO:.c=.o) $(ACCIONES:.c=.o)
	$(CC) $(FLAGS) -o $@ $^ -pthread

# Archivo objeto de la implementación de las listas de acciones para deshacer y rehacer
$(ACCIONES:.c=.o) : $(ACCIONES) $(ACCIONES:.c=.h)
	$(CC) $(FLAGS) -c $(ACCIONES)

# Archivo objeto de la implementación de la estructura contacto
$(CONTACTO:.c=.o) : $(CONTACTO) $(CONTACTO:.c=.h)
	$(CC) $(FLAGS) -c $(CONTACTO)

# Archivo objeto de la implementación de listas simplemente enlazadas
$(SLIST:.c=.o) : $(SLIST) $(SLIST:.c=.h)
	$(CC) $(FLAGS) -c $(SLIST)

# Archivo objeto de la implementación de árboles avl
$(ARBOL:.c=.o) : $(ARBOL) $(ARBOL:.c=.h) $(SLIST:.c=.o)
	$(CC) $(FLAGS) -c $(ARBOL)

# Archivo objeto de la implementación de árboles simples
$(STREE:.c=.o) : $(STREE) $(STREE:.c=.h) $(SLIST:.c=.o)
	$(CC) $(FLAGS) -c $(STREE)

# Archivo objeto de la implementación de la tabla hash.
$(TABLAHASH:.c=.o) : $(TABLAHASH) $(TABLAHASH:.c=.h) $(ARBOL:.c=.o) $(CONTACTO:.c=.o)
	$(CC) $(FLAGS) -c $(TABLAHASH)

# Archivo objeto de la implementación de las funciones relacionada a and y or.
$(ANDOR:.c=.o) : $(ANDOR) $(ANDOR:.c=.h) $(STREE:.c=.o) $(TABLAHASH:.c=.o)
	$(CC) $(FLAGS) -c $(ANDOR)

# Archivo objeto de la implementación del intérprete.
$(INTERPRETE:.c=.o) : $(INTERPRETE) $(INTERPRETE:.c=.h) $(ANDOR:.c=.o) $(ACCIONES:.c=.o)
	$(CC) $(FLAGS) -c $(INTERPRETE)

# Destino simbólico que borra todos los archivos con extensión .o cuando se invoca.
clean: 
	rm *.o

.PHONY : clean