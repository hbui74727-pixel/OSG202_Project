#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H
#include "types.h"

void Account_LoadAll(void);
void Account_SaveAll(void);
bool Account_Register(const char *user, const char *pass, PlayerRole role, char *errOut);
bool Account_Login(const char *user, const char *pass, char *errOut);
void Account_Logout(void);
void Account_ToggleAdmin(void);
void Account_HandleLoginInput(void);
void Account_HandleRegisterInput(void);
#endif
