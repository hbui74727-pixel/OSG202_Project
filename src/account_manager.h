#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H
#include "types.h"

void Account_LoadAll(void);
void Account_SaveAll(void);
bool Account_Register(const char *user, const char *pass, PlayerRole role, char *errOut);
bool Account_Login(const char *user, const char *pass, char *errOut);
void Account_Logout(void);
void Account_ToggleAdmin(void);
<<<<<<< HEAD
<<<<<<< HEAD
void Account_ToggleTester(void);  // Thêm hàm mới
=======
>>>>>>> aec174b3ec2a899fec493f59b3c163f8d1262acc
=======
>>>>>>> 1084983ade6e0fbfb7534b983c027e2cc01c0e23
void Account_HandleLoginInput(void);
void Account_HandleRegisterInput(void);
#endif
