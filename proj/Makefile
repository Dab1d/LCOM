
PROG = proj

CFLAGS += -pedantic -D __LCOM_OPTIMIZED__
CFLAGS += -I/home/lcom/labs/lab3
#CFLAGS += -I/home/lcom/labs/lab4
CFLAGS += -I/home/lcom/labs/lab5

DPADD += ${LIBLCF} \
         /home/lcom/labs/lab2/libtimer.a \
         /home/lcom/labs/lab3/libkbc.a \
         /home/lcom/labs/lab4/libmouse.a \
         /home/lcom/labs/lab5/libvideo.a

LDADD += -llcf \
         /home/lcom/labs/lab2/libtimer.a \
         /home/lcom/labs/lab3/libkbc.a \
         /home/lcom/labs/lab4/libmouse.a \
         /home/lcom/labs/lab5/libvideo.a
LDLIBS += -lm

SRCS = proj.c \
       src/model/game/game.c \
       src/model/element/element.c \
       src/model/car/car.c \
       src/model/track/track.c \
       src/model/obstacle/obstacle.c \
       src/model/sprite/sprite.c \
       src/controller/input/input.c \
       src/controller/graphics/graphics.c \
       src/view/view.c


# Headers — listados explicitamente para dependências corretas
HDRS = src/model/game/game.h \
       src/model/element/element.h \
       src/model/car/car.h \
       src/model/track/track.h \
       src/model/obstacle/obstacle.h \
       src/model/sprite/sprite.h \
       src/controller/input/input.h \
       src/controller/graphics/graphics.h \
       src/view/view.h

#       src/controller/timer/timer.h \
#       src/controller/rtc/rtc.h \
#       src/controller/kbc/kbc.h \
#       src/controller/kbc/kbd.h \
# Regras de compilação
proj.o: proj.c ${HDRS}
	${CC} ${CFLAGS} -c $< -o $@

src/model/game/game.o: src/model/game/game.c src/model/game/game.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/element/element.o: src/model/element/element.c src/model/element/element.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/car/car.o: src/model/car/car.c src/model/car/car.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/track/track.o: src/model/track src/model/track
	${CC} ${CFLAGS} -c $< -o $@

src/model/obstacle/obstacle.o: src/model/obstacle/obstacle.c src/model/obstacle/obstacle.h
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