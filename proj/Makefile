PROG=proj

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

src/model/game/game.o: src/model/game/game.c src/model/game/game.h
	${CC} ${CFLAGS} -c $< -o $@

src/controller/timer/timer.o: src/controller/timer/timer.c src/controller/timer/timer.h
	${CC} ${CFLAGS} -c $< -o $@

src/controller/rtc/rtc.o: src/controller/rtc/rtc.c src/controller/rtc/rtc.h
	${CC} ${CFLAGS} -c $< -o $@

src/controller/kbc/kbc.o: src/controller/kbc/kbc.c src/controller/kbc/kbc.h
	${CC} ${CFLAGS} -c $< -o $@

src/controller/kbc/kbd.o: src/controller/kbc/kbd.c src/controller/kbc/kbd.h
	${CC} ${CFLAGS} -c $< -o $@

src/controller/input/input.o: src/controller/input/input.c src/controller/input/input.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/view.o: src/view/view.c src/view/view.h
	${CC} ${CFLAGS} -c $< -o $@


src/model/sprite/sprite.o: src/model/sprite/sprite.c src/model/sprite/sprite.h
	${CC} ${CFLAGS} -c $< -o $@

src/controller/graphics/graphics.o: src/controller/graphics/graphics.c src/controller/graphics/graphics.h
	${CC} -O0 -fno-inline -fno-unroll-loops ${CFLAGS} -c $< -o $@

# include LCOM's makefile that does all the "heavy liftinng"
.include <minix.lcom.mk>