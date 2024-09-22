FILES =	${wildcard *.cpp} ${wildcard *.h} ${wildcard Entity/*.cpp} ${wildcard Entity/*.h} ${wildcard Scene/*.cpp} ${wildcard Scene/*.h}

FLAGS = -IEntity -IScene -I.

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

EXEC = sfml-app

all:
	g++ ${FLAGS} ${FILES} ${LIBS} -o ${EXEC}

cpp11:
	g++ -std=c++11 ${FLAGS} ${FILES} ${LIBS} -o ${EXEC}
