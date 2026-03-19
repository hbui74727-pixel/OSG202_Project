#include "font_manager.h"
#include "types.h"
#include <stdint.h>

Font gameFont;

void Font_Load(void)
{
    // Thử load font Montserrat (hỗ trợ tiếng Việt)
    const char *fontPaths[] = {
        "assets/fonts/montserrat-font/MontserratBlack-3zOvZ.ttf",
    };
    
    int numPaths = sizeof(fontPaths) / sizeof(fontPaths[0]);
    bool fontLoaded = false;
    
    // Mảng codepoint đầy đủ cho tiếng Việt
    int codepoints[] = {
        // Ký tự cơ bản (0x0020-0x007F)
        0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
        0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F,
        0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
        0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F,
        0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
        0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F,
        0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
        0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F,
        0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
        0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F,
        0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077,
        0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E,
        
        // Ký tự Latin mở rộng (0x00A0-0x00FF) - có dấu cơ bản
        0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7,
        0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF,
        0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7,
        0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF,
        0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7,
        0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
        0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7,
        0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF,
        0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7,
        0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
        0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7,
        0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF,
        
        // Ký tự tiếng Việt (Latin Extended Additional - 0x1EA0-0x1EFF)
        0x1EA0, 0x1EA1, 0x1EA2, 0x1EA3, 0x1EA4, 0x1EA5, 0x1EA6, 0x1EA7,
        0x1EA8, 0x1EA9, 0x1EAA, 0x1EAB, 0x1EAC, 0x1EAD, 0x1EAE, 0x1EAF,
        0x1EB0, 0x1EB1, 0x1EB2, 0x1EB3, 0x1EB4, 0x1EB5, 0x1EB6, 0x1EB7,
        0x1EB8, 0x1EB9, 0x1EBA, 0x1EBB, 0x1EBC, 0x1EBD, 0x1EBE, 0x1EBF,
        0x1EC0, 0x1EC1, 0x1EC2, 0x1EC3, 0x1EC4, 0x1EC5, 0x1EC6, 0x1EC7,
        0x1EC8, 0x1EC9, 0x1ECA, 0x1ECB, 0x1ECC, 0x1ECD, 0x1ECE, 0x1ECF,
        0x1ED0, 0x1ED1, 0x1ED2, 0x1ED3, 0x1ED4, 0x1ED5, 0x1ED6, 0x1ED7,
        0x1ED8, 0x1ED9, 0x1EDA, 0x1EDB, 0x1EDC, 0x1EDD, 0x1EDE, 0x1EDF,
        0x1EE0, 0x1EE1, 0x1EE2, 0x1EE3, 0x1EE4, 0x1EE5, 0x1EE6, 0x1EE7,
        0x1EE8, 0x1EE9, 0x1EEA, 0x1EEB, 0x1EEC, 0x1EED, 0x1EEE, 0x1EEF,
        0x1EF0, 0x1EF1, 0x1EF2, 0x1EF3, 0x1EF4, 0x1EF5, 0x1EF6, 0x1EF7,
        0x1EF8, 0x1EF9, // Vietnamese base letters
<<<<<<< HEAD
<<<<<<< HEAD
0x0102, // Ă
0x0103, // ă
0x0110, // Đ
0x0111, // đ
0x01A0, // Ơ
0x01A1, // ơ
0x01AF, // Ư
0x01B0, // ư
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        0x0102, // Ă
        0x0103, // ă
        0x0110, // Đ
        0x0111, // đ
        0x01A0, // Ơ
        0x01A1, // ơ
        0x01AF, // Ư
        0x01B0, // ư
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        
        // Ký tự đặc biệt
        0x20AC, // €
        0x00A3, // £
        0x00A5, // ¥
        0x25CF, // ●
        0x25CB, // ○
        0x2714, // ✓
        0x2718, // ✘
        0x2190, // ←
        0x2191, // ↑
        0x2192, // →
<<<<<<< HEAD
<<<<<<< HEAD
        0x2193  // ↓
=======
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        0x2193,  // ↓

        0x0169, // ũ - chữ u ngã (Latin small letter u with tilde)
        0x0168 // Ũ - chữ U ngã (Latin capital letter U with tilde)
<<<<<<< HEAD
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
    };
    
    int codepointCount = sizeof(codepoints) / sizeof(codepoints[0]);
    
    for (int i = 0; i < numPaths; i++) {
        if (FileExists(fontPaths[i])) {
            gameFont = LoadFontEx(fontPaths[i], 64, codepoints, codepointCount);
            
            if (gameFont.texture.id > 0) {
                SetTextureFilter(gameFont.texture, TEXTURE_FILTER_BILINEAR);
                TraceLog(LOG_INFO, TextFormat("Loaded font: %s (with Vietnamese support)", fontPaths[i]));
                fontLoaded = true;
                break;
            }
        }
    }
    
    if (!fontLoaded) {
        TraceLog(LOG_WARNING, "No font found! Using default font");
        gameFont = GetFontDefault();
    }
}

void Font_Unload(void)
{
    if (gameFont.texture.id > 0) {
        UnloadFont(gameFont);
    }
}

// Vẽ text với kích thước cố định trên màn hình (không zoom)
void DrawTextShort(const char *text, int posX, int posY, int fontSize, Color color)
{
    if (!text || text[0] == '\0') return;
    
    if (gameFont.texture.id == 0) {
<<<<<<< HEAD
<<<<<<< HEAD
        DrawText(text, posX, posY, fontSize, color);
=======
        DrawTextShort(text, posX, posY, fontSize, color);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
        DrawTextShort(text, posX, posY, fontSize, color);
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        return;
    }
    
    if (fontSize < 6) fontSize = 6;
    if (fontSize > 72) fontSize = 72;
    
    Vector2 position = { (float)posX, (float)posY };
    DrawTextEx(gameFont, text, position, (float)fontSize, 0, color);
}

// Vẽ text căn giữa với kích thước cố định
void DrawTextCenteredShort(const char *text, int centerX, int y, int fontSize, Color color)
{
    if (!text || text[0] == '\0') return;
    
    if (gameFont.texture.id == 0) {
        int textWidth = MeasureText(text, fontSize);
<<<<<<< HEAD
<<<<<<< HEAD
        DrawText(text, centerX - textWidth / 2, y, fontSize, color);
=======
        DrawTextShort(text, centerX - textWidth / 2, y, fontSize, color);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
        DrawTextShort(text, centerX - textWidth / 2, y, fontSize, color);
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        return;
    }
    
    if (fontSize < 6) fontSize = 6;
    if (fontSize > 72) fontSize = 72;
    
    Vector2 size = MeasureTextEx(gameFont, text, (float)fontSize, 0);
    int x = centerX - (int)(size.x / 2);
    DrawTextEx(gameFont, text, (Vector2){ (float)x, (float)y }, (float)fontSize, 0, color);
}

void DrawTextWithOutline(const char *text, int posX, int posY, int fontSize, Color textColor, Color outlineColor)
{
    if (!text || text[0] == '\0') return;
    
    // Vẽ outline (đen) ở các vị trí lệch
    DrawTextShort(text, posX - 1, posY - 1, fontSize, outlineColor);
    DrawTextShort(text, posX + 1, posY - 1, fontSize, outlineColor);
    DrawTextShort(text, posX - 1, posY + 1, fontSize, outlineColor);
    DrawTextShort(text, posX + 1, posY + 1, fontSize, outlineColor);
    
    // Vẽ text chính
    DrawTextShort(text, posX, posY, fontSize, textColor);
}

// Vẽ text căn giữa có outline
void DrawTextCenteredWithOutline(const char *text, int centerX, int y, int fontSize, Color textColor, Color outlineColor)
{
    if (!text || text[0] == '\0') return;
    
    int textWidth = 0;
    if (gameFont.texture.id == 0) {
        textWidth = MeasureText(text, fontSize);
    } else {
        Vector2 size = MeasureTextEx(gameFont, text, (float)fontSize, 1);
        textWidth = (int)size.x;
    }
    
    int x = centerX - textWidth / 2;
    
    // Vẽ outline
    DrawTextShort(text, x - 1, y - 1, fontSize, outlineColor);
    DrawTextShort(text, x + 1, y - 1, fontSize, outlineColor);
    DrawTextShort(text, x - 1, y + 1, fontSize, outlineColor);
    DrawTextShort(text, x + 1, y + 1, fontSize, outlineColor);
    
    // Vẽ text chính
    DrawTextShort(text, x, y, fontSize, textColor);
}

// Hàm tiện ích: đo chiều rộng text
int MeasureTextShort(const char *text, int fontSize)
{
    if (!text || text[0] == '\0') return 0;
    
    if (gameFont.texture.id == 0) {
        return MeasureText(text, fontSize);
    }
    
    if (fontSize < 4) fontSize = 4;
    Vector2 size = MeasureTextEx(gameFont, text, (float)fontSize, 0);
    return (int)size.x;
}