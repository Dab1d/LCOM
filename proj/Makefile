
PROG = proj

CFLAGS += -pedantic -D __LCOM_OPTIMIZED__
# Caminhos relativos em vez de /home/lcom/labs/labX — funcionam independentemente
# do mount point da pasta partilhada no MINIX
CFLAGS += -I../lab3
#CFLAGS += -I../lab4
CFLAGS += -I../lab5
CFLAGS += -I../lab1proj

DPADD += ${LIBLCF}

# Os .a dos labs têm de vir ANTES de -llcf. O linker resolve símbolos pela ordem
# em que encontra as bibliotecas: se -llcf viesse primeiro, usaria os stubs do LCF
# (ex: timer_set_frequency "not implemented") em vez das implementações dos labs.
LDADD += ../lab1proj/liblab1proj.a \
         ../lab2/libtimer.a \
         ../lab3/libkbc.a \
         ../lab4/libmouse.a \
         ../lab5/libvideo.a \
         -llcf
LDLIBS += -lm

SRCS = proj.c \
       src/model/game/game.c \
       src/model/element/element.c \
       src/model/car/car.c \
       src/model/track/track.c \
       src/model/obstacle/obstacle.c \
       src/model/sprite/sprite.c \
       src/controller/input/input.c \
       src/controller/palette/palette.c \
       src/controller/graphics/graphics.c \
       src/view/view.c \
       src/model/resources/resources.c \
       src/view/car/car_view.c \
       src/view/obstacle/obstacle_view.c \
       src/view/track/track_view.c \
       src/view/scenery/scenery_view.c \
       src/view/pause/pause_view.c \
       src/model/cursor/cursor.c \
       src/model/leaderboard/leaderboard.c


# Headers — listados explicitamente para dependências corretas
HDRS = src/model/game/game.h \
       src/model/element/element.h \
       src/model/car/car.h \
       src/model/track/track.h \
       src/model/obstacle/obstacle.h \
       src/model/sprite/sprite.h \
       src/controller/input/input.h \
       src/controller/palette/palette.h \
       src/controller/graphics/graphics.h \
       src/view/view.h \
       src/model/resources/resources.h \
       src/view/obstacle/obstacle_view.h \
       src/view/track/track_view.h \
       src/view/scenery/scenery_view.h \
       src/view/pause/pause_view.h \
       src/model/cursor/cursor.h \
       src/model/leaderboard/leaderboard.h

#       src/controller/timer/timer.h \
#       src/controller/rtc/rtc.h \
#       src/controller/kbc/kbc.h \
#       src/controller/kbc/kbd.h \
# Regras de compilação
proj.o: src/proj.c ${HDRS}
	${CC} ${CFLAGS} -c $< -o $@

src/model/game/game.o: src/model/game/game.c src/model/game/game.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/element/element.o: src/model/element/element.c src/model/element/element.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/car/car.o: src/model/car/car.c src/model/car/car.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/track/track.o: src/model/track/track.c src/model/track/track.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/obstacle/obstacle.o: src/model/obstacle/obstacle.c src/model/obstacle/obstacle.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/sprite/sprite.o: src/model/sprite/sprite.c src/model/sprite/sprite.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/cursor/cursor.o: src/model/cursor/cursor.c src/model/cursor/cursor.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/leaderboard/leaderboard.o: src/model/leaderboard/leaderboard.c src/model/leaderboard/leaderboard.h
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

src/controller/palette/palette.o: src/controller/palette/palette.c src/controller/palette/palette.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/view.o: src/view/view.c src/view/view.h
	${CC} ${CFLAGS} -c $< -o $@

src/model/resources/resources.o: src/model/resources/resources.c src/model/resources/resources.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/car/car_view.o: src/view/car/car_view.c src/view/car/car_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/obstacle/obstacle_view.o: src/view/obstacle/obstacle_view.c src/view/obstacle/obstacle_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/track/track_view.o: src/view/track/track_view.c src/view/track/track_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/scenery/scenery_view.o: src/view/scenery/scenery_view.c src/view/scenery/scenery_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/view/pause/pause_view.o: src/view/pause/pause_view.c src/view/pause/pause_view.h
	${CC} ${CFLAGS} -c $< -o $@

src/controller/graphics/graphics.o: src/controller/graphics/graphics.c src/controller/graphics/graphics.h
	${CC} -O0 -fno-inline -fno-unroll-loops ${CFLAGS} -c $< -o $@

.include <minix.lcom.mk>