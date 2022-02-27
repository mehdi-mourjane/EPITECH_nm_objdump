##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile for my project
##

NM	=	my_nm

OBJDUMP =	my_objdump

SRC_NM	=	nm_src/nm.c	\
			nm_src/symbol.c	\
			nm_src/lib.c	\

SRC_OBJDUMP	=	objdump_src/objdump.c	\
				objdump_src/lib.c	\

XX	=	gcc

NM_OBJ	=	$(SRC_NM:.c=.o)

OBJDUMP_OBJ	=	$(SRC_OBJDUMP:.c=.o)

CXXFLAGS= -Werror -Wextra

all	:	$(NM) $(OBJDUMP)

nm	:	$(NM)

objdump	:	$(OBJDUMP)

$(NM)	:	$(NM_OBJ)
		$(XX) -o $(NM) $(NM_OBJ)

$(OBJDUMP)	:	$(OBJDUMP_OBJ)
		$(XX) -o $(OBJDUMP) $(OBJDUMP_OBJ)

clean:
		rm -f $(NM_OBJ) $(OBJDUMP_OBJ)


fclean:		clean
			rm -f $(NM) $(OBJDUMP)

re:		fclean all

.PHONY:		all clean fclean re

