# $Id: Makefile 232 2015-04-26 11:41:11Z gerardo $
# Makefile para el caso 3 de la LIBRERÍA
# ©2010-2015 Los profesores de POO
#
# --- Parte configurable ---
#
# NOMBREALUMNO es el nombre del directorio donde el alumno guarda las
# prácticas de POO (C++). Dentro de ese directorio debe haber uno para
# cada práctica llamado NOMBREPRACTICA, que será de la forma P<n>,
# siendo <n> el número de práctica: P0, P1, etc.

NOMBREALUMNO   = Bazan_Munnoz_Adrian
NOMBREPRACTICA = P3

# CADENADIR y FECHADIR son los directorios donde están respectivamente
# los módulos objeto y cabeceras de Cadena y Fecha: 
# Makefile, cadena.{oh} y fecha.{oh}.
# TESTHDR es el directorio donde está la cabecera del test automático, fct.h
DIRFECHACADENA=P1
CADENADIR= ../${DIRFECHACADENA}/Cadena
FECHADIR = ../${DIRFECHACADENA}/Fecha
TESTHDR = ..

# ¿Compilador C++ de LLVM (clang++) o de GNU (g++)?
CXX	 = g++
#CXX      = clang++

# ¿Qué estándar seguir?
# ansi o c++98 o c++03: estándar de 1998, corregido en 2003
# c++0x: borrador del estándar de 2011
# c++11: estándar de 2011
# c++1y: estándar actual de 2014
# c++1z: estándar hipotético de 2017
STD=c++0x

CXXFLAGS = -g -pedantic -Wall -std=${STD} ${INCLUDES}

# --- Fin parte configurable

INCLUDES  = -I${CADENADIR} -I${FECHADIR} -I${TESTHDR}
LOCALLIBS = ${CADENADIR}/cadena.o ${FECHADIR}/fecha.o
EXTLIBS   = -lcrypt
LIBS      = ${LOCALLIBS} ${EXTLIBS}
VPATH     = .:${CADENADIR}:${FECHADIR}

COMM_SRCS = usuario.cpp tarjeta.cpp articulo.cpp \
	pedido.cpp pedido-articulo.cpp luhn.cpp
# Nota: usuario-pedido.cpp no hace falta.
MAIN_SRCS = $(COMM_SRCS) test-caso3-consola.cpp
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)
MAIN_EXE  = test-caso3-consola
TEST_SRCS = $(COMM_SRCS) test-caso3-auto.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_EXE  = test-caso3-auto

NOMBRETAR = ../../${NOMBREALUMNO}.tar.gz
NOMBREDIR = ${NOMBREALUMNO}/${NOMBREPRACTICA}

## OBJETIVOS PRINCIPALES #######################################################

.PHONY: all clean dist distclean test-consola test-auto

all: ${MAIN_EXE} ${TEST_EXE}

test-consola: ${MAIN_EXE}
	./$<

test-auto: ${TEST_EXE}
	./$<

#check: compra_check
#	./$< usuario.cpp tarjeta.cpp articulo.cpp -- -std=c++11 -I${CADENADIR} -I${FECHADIR}


clean:
	${RM} ${RMFLAGS} ${MAIN_EXE} ${MAIN_OBJS} ${TEST_EXE} ${TEST_OBJS} \
		*.d *.{aux,log,dvi,toc} *~ \#*
	make -C ${CADENADIR} clean
	make -C ${FECHADIR}  clean


## COMPILACIÓN #################################################################

${MAIN_EXE}: ${MAIN_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

${TEST_EXE}: ${TEST_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

# Detección automática de dependencias en código fuente C++ #

%.d: %.cpp
	@$(CXX) -MM $(CXXFLAGS) $< > $@
	@sed -ri 's,($*)\.o[ :]*,\1.o $@ : ,g' $@

-include $(MAIN_SRCS:.cpp=.d) $(TEST_SRCS:.cpp=.d)

## EMPAQUETADO #################################################################

${NOMBRETAR}: ${SRCS} ${HDRS}
ifeq ($(strip $(NOMBREALUMNO)),)
	@echo ""
	@echo "ATENCIÓN: debe definir en el Makefile la variable NOMBREALUMNO"
	@echo "con el nombre del directorio superior a este."
	@echo " Vea las instrucciones de entrega de las prácticas."
else
	tar -cvz -C../.. -f ${NOMBRETAR} ${NOMBREDIR} \
				${NOMBREALUMNO}/${DIRFECHACADENA}
endif

# Esto lo deberían usar los alumnos a la hora de la entrega:
# crea el archivo .tar.gz en el directorio padre tras borrar lo sobrante.
dist: clean ${NOMBRETAR}

distclean: clean
	${RM} ${RMFLAGS} ${NOMBRETAR}

