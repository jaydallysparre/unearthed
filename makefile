FILES = main.cpp MathUtil.h Level.h Level.cpp Entity.cpp Entity.h InputHandler.h InputHandler.cpp KBMInput.h KBMInput.cpp HBSprite.h HBSprite.cpp Commando.cpp Commando.h

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

EXEC = sfml-app

all:
	g++ ${FILES} ${LIBS} -o ${EXEC}

cpp11:
	g++ -std=c++11 ${FILES} ${LIBS} -o ${EXEC}
