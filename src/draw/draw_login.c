#include "draw_login.h"
#include <string.h>
#include "../font_manager.h"
static Texture2D bg;

static char username[32] = "";
static char password[32] = "";

static int usernameLen = 0;
static int passwordLen = 0;

static bool typingUser = false;
static bool typingPass = false;

static bool loginDone = false;

static Rectangle userBox;
static Rectangle passBox;
static Rectangle loginBtn;

void DrawLogin_Init()
{
    bg = LoadTexture("assets/backgrounds/login_bg.jpg");

    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    userBox = (Rectangle){sw/2 - 150, sh/2 - 40, 300, 40};
    passBox = (Rectangle){sw/2 - 150, sh/2 + 20, 300, 40};
    loginBtn = (Rectangle){sw/2 - 80, sh/2 + 90, 160, 45};
}

void DrawLogin_Update()
{
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        typingUser = CheckCollisionPointRec(mouse, userBox);
        typingPass = CheckCollisionPointRec(mouse, passBox);

        if (CheckCollisionPointRec(mouse, loginBtn))
        {
            if (usernameLen > 0)
                loginDone = true;
        }
    }

    int key = GetCharPressed();

    while (key > 0)
    {
        if (typingUser && usernameLen < 30)
        {
            username[usernameLen++] = (char)key;
            username[usernameLen] = '\0';
        }

        if (typingPass && passwordLen < 30)
        {
            password[passwordLen++] = (char)key;
            password[passwordLen] = '\0';
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (typingUser && usernameLen > 0)
        {
            usernameLen--;
            username[usernameLen] = '\0';
        }

        if (typingPass && passwordLen > 0)
        {
            passwordLen--;
            password[passwordLen] = '\0';
        }
    }
}

void DrawLogin_Render()
{
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    float scaleX = (float)sw / bg.width;
    float scaleY = (float)sh / bg.height;
    float scale = scaleX > scaleY ? scaleX : scaleY;

    DrawTextureEx(bg, (Vector2){0,0}, 0, scale, WHITE);

    DrawRectangle(0,0,sw,sh,(Color){0,0,0,120});

    DrawTextCentered("FARM GAME", sw/2 - 120, sh/2 - 150, 50, WHITE);

    DrawRectangleRec(userBox, typingUser ? SKYBLUE : LIGHTGRAY);
    DrawRectangleLinesEx(userBox,2,WHITE);
<<<<<<< HEAD
<<<<<<< HEAD
    DrawText(username, userBox.x+10, userBox.y+10, 20, BLACK);
    DrawText("Username", userBox.x, userBox.y-20, 18, WHITE);
=======
    DrawTextShort(username, userBox.x+10, userBox.y+10, 20, BLACK);
    DrawTextShort("Username", userBox.x, userBox.y-20, 18, WHITE);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
    DrawTextShort(username, userBox.x+10, userBox.y+10, 20, BLACK);
    DrawTextShort("Username", userBox.x, userBox.y-20, 18, WHITE);
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23

    DrawRectangleRec(passBox, typingPass ? SKYBLUE : LIGHTGRAY);
    DrawRectangleLinesEx(passBox,2,WHITE);

    char hidden[32];
    memset(hidden,'*',passwordLen);
    hidden[passwordLen] = '\0';

<<<<<<< HEAD
<<<<<<< HEAD
    DrawText(hidden, passBox.x+10, passBox.y+10, 20, BLACK);
    DrawText("Password", passBox.x, passBox.y-20, 18, WHITE);
=======
    DrawTextShort(hidden, passBox.x+10, passBox.y+10, 20, BLACK);
    DrawTextShort("Password", passBox.x, passBox.y-20, 18, WHITE);
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
    DrawTextShort(hidden, passBox.x+10, passBox.y+10, 20, BLACK);
    DrawTextShort("Password", passBox.x, passBox.y-20, 18, WHITE);
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23

    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, loginBtn);

    DrawRectangleRec(loginBtn, hover ? DARKGREEN : GREEN);
    DrawRectangleLinesEx(loginBtn,2,WHITE);

<<<<<<< HEAD
<<<<<<< HEAD
    DrawText("LOGIN",
=======
    DrawTextShort("LOGIN",
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
    DrawTextShort("LOGIN",
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
        loginBtn.x + 45,
        loginBtn.y + 12,
        20,
        WHITE);
}

bool Login_IsDone()
{
    return loginDone;
}

const char* Login_GetUsername()
{
    return username;
}

void DrawLogin_Unload()
{
    UnloadTexture(bg);
}