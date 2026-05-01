PROG=lab5

SRCS = lab5.c video_gr.c

# Flags e Includes
CFLAGS += -pedantic -I../lab3 -I../lab2

# Dependências 
DPADD += ${LIBLCF} ../lab3/libkbc.a ../lab2/libtimer.a
LDADD += -llcf ../lab3/libkbc.a ../lab2/libtimer.a

# Biblioteca local
LIB_NAME = libvideo.a
LIB_SRCS = video_gr.c
LIB_OBJS = ${LIB_SRCS:.c=.o}

.include <minix.lcom.mk>

all: libs ${LIB_NAME} ${PROG}

${LIB_NAME}: ${LIB_OBJS}
	ar rcs ${LIB_NAME} ${LIB_OBJS}

# Garante que os outros labs estão compilados
libs:
	${MAKE} -C ../lab2 lib
	${MAKE} -C ../lab3 lib
