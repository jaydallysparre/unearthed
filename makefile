FILES =	${wildcard *.cpp} ${wildcard Entity/*.cpp} ${wildcard Entity/Input/*.cpp} ${wildcard Scene/*.cpp} ${wildcard Scene/Game/*.cpp} ${wildcard Scene/Menu/*.cpp} ${wildcard UI/*.cpp} ${wildcard Item/*.cpp}

FLAGS = -IEntity -IScene -IEntity/Input -IUI -IScene/Game -IScene/Menu -IItem -I.

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

EXEC = sfml-app

all: ${OBJS}
	g++ ${FLAGS} ${FILES} ${LIBS} -o ${EXEC}

debug:
	g++ ${FLAGS} ${FILES} ${LIBS} -o ${EXEC} -g

cpp11:
	g++ -std=c++11 ${FLAGS} ${FILES} ${LIBS} -o ${EXEC}
