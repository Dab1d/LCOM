CC = clang
CFLAGS = -Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter -pedantic

LIB_NAME = liblab1proj.a
LIB_SRCS = rtc.c
LIB_OBJS = ${LIB_SRCS:.c=.o}

HDRS = rtc.h

all: ${LIB_NAME}

${LIB_NAME}: ${LIB_OBJS}
	ar rcs ${LIB_NAME} ${LIB_OBJS}

rtc.o: rtc.c ${HDRS}
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f ${LIB_NAME} ${LIB_OBJS}
