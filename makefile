#OBJS specifies which files to compile as part of the project
#OBJS = Source\main.cpp Source\game.cpp Source\card.cpp Source\font_writer.cpp Source\card_collection.cpp
OBJS = Source\main.cpp Source\GameCore\game.cpp \
	   Source\GameCore\game_object.cpp \
	   Source\GameCore\AssetsManager\font_assets_manager.cpp \
	   Source\draw_card_game.cpp Source\game_play_scene.cpp \
	   Source\GameCore\UIObject\text.cpp \
	   Source\GameObjects\card.cpp \
	   Source\GameObjects\card_collection.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\Users\yuuta\Documents\DrawCard\Library\i686-w64-mingw32\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\Users\yuuta\Documents\DrawCard\Library\i686-w64-mingw32\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
DEBUG_COMPILER_FLAGS = -w #-Wl,-subsystem,windows
RELEASE_COMPILER_FLAGS = -w -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Build\main.exe

#This is the target that compiles our executable
debug : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(DEBUG_COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

release : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(RELEASE_COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)