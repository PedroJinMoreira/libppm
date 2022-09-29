name:=	$(shell pwd | rev | cut -d '/' -f 1 | rev)

CC:=		gcc

CC_FLAGS:=	-O3

INCLUDE:=	

LIBS:=		

all:
	$(CC) $(CC_FLAGS) $(INCLUDE) $(LIBS)  -c src/$(name).c -o build/$(name).o
