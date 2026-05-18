PROG=project

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D __LCOM_OPTIMIZED__

# list of library dependencies (LCF)
DPADD += ${LIBLCF}
LDADD += -llcf
LDLIBS += -lm

# define headers dependencies
HDRS = $(find . -name *.h)

# compilation rules for each source file
proj.o: proj.c ${HDRS}
	${CC} ${CFLAGS} -c $< -o $@

model/game/game.o: model/game/game.c model/game/game.h
	${CC} ${CFLAGS} -c $< -o $@

controller/timer/timer.o: controller/timer/timer.c controller/timer/timer.h
	${CC} ${CFLAGS} -c $< -o $@

controller/rtc/rtc.o: controller/rtc/rtc.c controller/rtc/rtc.h
	${CC} ${CFLAGS} -c $< -o $@

controller/kbc/kbc.o: controller/kbc/kbc.c controller/kbc/kbc.h
	${CC} ${CFLAGS} -c $< -o $@

controller/kbc/kbd.o: controller/kbc/kbd.c controller/kbc/kbd.h
	${CC} ${CFLAGS} -c $< -o $@

controller/graphics/graphics.o: controller/graphics/graphics.c controller/graphics/graphics.h
	${CC} -O0 -fno-inline -fno-unroll-loops ${CFLAGS} -c $< -o $@

# include LCOM's makefile that does all the "heavy liftinng"
.include <minix.lcom.mk>