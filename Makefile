CC = g++

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Nome do executável final gerado na raiz
TARGET = Trabalho1

# Detecção confiável de SO
ifeq ($(OS), Windows_NT)
    PLATFORM := Windows
else
    PLATFORM := $(shell uname -s 2>/dev/null || echo Unknown)
endif

ifeq ($(PLATFORM), Windows)
    SDL_PATH = C:/SDL2
    CFLAGS   = -Wall -g -std=c++17 -I$(INC_DIR) -I$(SDL_PATH)/include
    LDFLAGS  = -L$(SDL_PATH)/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
    TARGET   := $(TARGET).exe
    MKDIR    = if not exist $(1) mkdir $(1)
    RM       = rmdir /S /Q $(1) 2> NUL || exit 0
    RM_FILE  = del /Q $(1) 2> NUL || exit 0
    EXEC     = $(TARGET)
else
    CFLAGS   = -Wall -g -std=c++17 -I$(INC_DIR) $(shell sdl2-config --cflags)
    LDFLAGS  = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer
    MKDIR    = mkdir -p $(1)
    RM       = rm -rf $(1)
    RM_FILE  = rm -f $(1)
    EXEC     = ./$(TARGET)
endif

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: folders $(TARGET)

folders:
	@$(call MKDIR, $(OBJ_DIR))

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(call RM, $(OBJ_DIR))
	@$(call RM_FILE, $(TARGET))

run: all
	$(EXEC)

debug: CFLAGS += -DDEBUG
debug: all

.PHONY: all folders clean run debug