
PROG = proj

CFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf
LDLIBS += -lm

SRCS = proj.c \
       src/model/game/game.c \
       src/model/element/element.c \
       src/model/car/car.c \
       src/model/sprite/sprite.c \
       src/controller/timer/timer.c \
       src/controller/rtc/rtc.c \
       src/controller/kbc/kbc.c \
       src/controller/kbc/kbd.c \
       src/controller/input/input.c \
       src/view/view.c \
       src/controller/graphics/graphics.c

# Headers — listados explicitamente para dependências corretas
HDRS = proj.h \
       src/model/game/game.h \
       src/model/element/element.h \
       src/model/car/car.h \
       src/model/sprite/sprite.h \
       src/controller/timer/timer.h \
       src/controller/rtc/rtc.h \
       src/controller/kbc/kbc.h \
       src/controller/kbc/kbd.h \
       src/controller/input/input.h \
       src/view/view.h \
       src/controller/graphics/graphics.h

# Regras de compilação
proj.o: proj.c ${HDRS}
	${CC} ${CFLAGS} -c $< -o $@

src/model/game/game.o: src/model/game/game.c src/model/game/game.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/element/element.o: src/model/element/element.c src/model/element/element.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/car/car.o: src/model/car/car.c src/model/car/car.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/sprite/sprite.o: src/model/sprite/sprite.c src/model/sprite/sprite.h
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

src/controller/graphics/graphics.o: src/controller/graphics/graphics.c src/controller/graphics/graphics.h
	${CC} -O0 -fno-inline -fno-unroll-loops ${CFLAGS} -c $< -o $@

.include <minix.lcom.mk>