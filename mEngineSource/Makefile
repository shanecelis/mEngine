# This makefile can be used to build all or some of the sample
# programs.  To build all of them, use the command
# 'make all'.  To build one, say addtwo, use the command
# 'make addtwo'.

# Portions of this makefile require the use of GNU make.
# see http://www.gnu.org/software/make for more information.

VERSION=8.0
SYS = MacOSX-x86-64
CADDSDIR = /Applications/Mathematica.app/SystemFiles/Links/MathLink/DeveloperKit/CompilerAdditions
#EXTRA_CFLAGS=-Wno-long-double
EXTRA_CFLAGS = -I /Applications/MATLAB_R2011a_Student.app/extern/include/
EXTRA_LDFLAGS = -L /Applications/MATLAB_R2011a_Student.app/extern/lib -leng -lmx
EXTRA_LDFLAGS = -L/Applications/MATLAB_R2011a_Student.app/bin/maci64 -leng -lmx
INCDIR = ${CADDSDIR}
LIBDIR = ${CADDSDIR}

MPREP = ${CADDSDIR}/mprep
RM = rm

CC = /usr/bin/gcc
CXX = /usr/bin/c++

BINARIES = mEngine

all : $(BINARIES)

mEngine : templatetm.o close.o cmd.o get.o isopen.o main.o open.o put.o util.o vis.o
	${CXX} ${EXTRA_CFLAGS} -I${INCDIR} templatetm.o close.o cmd.o get.o isopen.o main.o open.o put.o util.o vis.o ${EXTRA_LDFLAGS} -L${LIBDIR} -lMLi3 -lstdc++ -framework Foundation -o $@

.c.o :
	${CC} -c ${EXTRA_CFLAGS} -I${INCDIR} $<

templatetm.c : template.tm
	${MPREP} $? -o $@

clean :
	@ ${RM} -rf *.o *tm.c $(BINARIES)
