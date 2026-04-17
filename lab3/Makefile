PROG=lab3

# 1. Point directly to the source files
# This ensures your timer.c code is actually compiled into the lab3 binary
SRCS = lab3.c kbc.c utils.c ../lab2/timer.c

# 2. Keep your includes
CFLAGS += -I../lab2       # Specify directories to the compiler to search for header files
CFLAGS += -pedantic -DLAB3 -I../lab2 -I.

# 3. Only link the LCOM library (LCF)
LDADD += -llcf
LDADD += -L../lab2
LDADD += -ltimer

.include <minix.lcom.mk>
