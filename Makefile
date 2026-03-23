SRC	=	src/Board.cpp	\
		src/main.cpp


OBJ	=	${SRC}

NAME	=	MyDemin

all:	${NAME}

${NAME}:
	g++ -o ${NAME} -std=c++17 ${SRC} -g3

clean:
	rm -f *~
	rm -f ${NAME}
	rm -f *.o

fclean: clean

re: fclean all
