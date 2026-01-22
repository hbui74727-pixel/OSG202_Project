# Tên file thực thi đầu ra
TARGET = game.exe

# Các file nguồn
SRC = main.c

# Các cờ biên dịch và thư viện (Dành cho MSYS2)
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

# Lệnh mặc định khi gõ 'make'
all:
	gcc $(SRC) -o $(TARGET) $(LDFLAGS)

# Lệnh để chạy game sau khi dịch
run:
	./$(TARGET)

# Lệnh để xóa file exe cũ
clean:
	rm -f $(TARGET)