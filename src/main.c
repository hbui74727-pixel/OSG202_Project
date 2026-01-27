#include <stdio.h>
#include <stdlib.h>    // Để dùng hàm system("cls") xóa màn hình
#include <stdbool.h>
#include "structs.h"

void displayMenu(GameState game) {
    // system("cls"); // Mở dòng này nếu muốn mỗi lần chọn menu là màn hình tự xóa sạch
    printf("\n====================================");
    printf("\n  NGAY: %d | TIEN: %d $", game.time.day, game.player.money);
    printf("\n====================================\n");
    printf("1. Xem ban do nong trai\n");
    printf("2. Nghi ngoi (Qua ngay moi)\n");
    printf("3. Cua hang\n");
    printf("0. Thoat va Luu game\n");
    printf("Chon hanh dong: ");
}

int main() {
    GameState game = {0}; 
    game.player.money = 1000;
    game.time.day = 1;
    
    int choice;
    bool isRunning = true;

    while (isRunning) {
        displayMenu(game);
        
        // Kiểm tra nếu người dùng nhập chữ thay vì số để tránh vòng lặp vô tận
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Xóa bộ nhớ đệm
            printf("\n[!] Vui long chi nhap so!\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("\n[Visual]: Dang ve ban do... (Cho ngay 4)\n");
                break;
            case 2:
                game.time.day++;
                printf("\n[System]: Chuc mung ngay moi! Hien tai la ngay %d.\n", game.time.day);
                break;
            case 0:
                isRunning = false;
                printf("\nDang thoat game...\n");
                break;
            default:
                printf("\n[!] Lua chon khong ton tai!\n");
        }
    }
    return 0;
}