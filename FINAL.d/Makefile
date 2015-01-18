COMP=g++
CFLAGS=-Wall -Wextra -Werror
FILES=\
main.cpp \
AModule.cpp \
ModuleCPU.cpp \
ModuleName.cpp \
ModuleNet.cpp \
ModuleOS.cpp \
ModuleRAM.cpp \
ModuleTime.cpp \
NcursesDisplay.cpp \
ft_timer.cpp

EXE=ft_gkrellm

GCK_S=`pkg-config --cflags gtk+-3.0`
GCK_E=`pkg-config --libs gtk+-3.0`
	


all: $(EXE)

$(EXE): $(FILES)
	$(COMP) $(CFLAGS) $(GTK_S) $(FILES) -o $(EXE) -lncurses $(GTK_E)


fclean:
	rm $(EXE)

re: fclean all