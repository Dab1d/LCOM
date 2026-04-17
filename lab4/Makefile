PROG=lab4

SRCS = lab4.c mouse.c

# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic
CFLAGS += -I../lab2
#CFLAGS += -I../lab3
CFLAGS += -I.

#Tell the Linker where to look (-L) and what to link (-l)
# This matches your professor's example exactly!

LDADD += -llcf 				#lcom lib
LDADD += -L../lab2 -ltimer
#LDADD += -L../lab3 -lkbc

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
