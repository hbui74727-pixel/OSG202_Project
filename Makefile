# =============================================================
#  Farm Simulator — Makefile
# =============================================================

CC = gcc
TARGET = sunny_world.exe

SRCS = src/main.c \
       src/account_manager.c \
<<<<<<< HEAD
=======
       src/audio_manager.c \
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
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
<<<<<<< HEAD
       src/draw/draw_admin_panel.c \
       src/draw/draw_tester_panel.c \
=======
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
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