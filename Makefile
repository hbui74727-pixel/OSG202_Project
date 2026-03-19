# =============================================================
#  Farm Simulator — Makefile
# =============================================================

CC = gcc
TARGET = sunny_world.exe

SRCS = src/main.c \
       src/account_manager.c \
       src/audio_manager.c \
       src/access_control.c \
       src/achievement_system.c \
       src/admin_commands.c \
       src/data_manager.c \
       src/entity_manager.c \
       src/event_system.c \
       src/game_logic.c \
       src/quest_system.c \
       src/renderer.c \
       src/textures.c \
       src/draw/draw_animal.c \
       src/draw/draw_building.c \
       src/draw/draw_crop.c \
       src/draw/draw_debug.c \
       src/draw/draw_hud.c \
       src/draw/draw_player.c \
       src/font_manager.c \
       src/draw/draw_tile.c \
       src/tree_system.c \
       src/draw/draw_ui.c

CFLAGS = -Iinclude -Isrc -Isrc/draw
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

all: clean build run

build:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)