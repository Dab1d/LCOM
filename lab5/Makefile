PROG=lab5

SRCS=lab5.c video_gr.c

CFLAGS += -pedantic -I../lab3

DPADD += ${LIBLCF} ../lab3/libkbc.a
LDADD += -llcf ../lab3/libkbc.a

all: kbc_lib

kbc_lib:
	${MAKE} -C ../lab3 lib

.include <minix.lcom.mk>   