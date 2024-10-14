FILES =	 ${wildcard Entity/*.cpp} ${wildcard Entity/Input/*.cpp} ${wildcard Scene/*.cpp} ${wildcard Scene/Game/*.cpp} ${wildcard Scene/Menu/*.cpp} ${wildcard UI/*.cpp} ${wildcard Item/*.cpp}

FLAGS = -IEntity -IScene -IEntity/Input -IUI -IScene/Game -IScene/Menu -IItem -I.

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

EXEC = unearthed

all:
	g++ ${FLAGS} ${FILES} main.cpp ${LIBS} -o ${EXEC}

debug:
	g++ ${FLAGS} ${FILES} main.cpp ${LIBS} -o ${EXEC} -g

tests: ${FILES} Testing/Tester.cpp
	g++ ${FLAGS} ${FILES} -ITesting Testing/Tester.cpp testmain.cpp ${LIBS} -o tests

