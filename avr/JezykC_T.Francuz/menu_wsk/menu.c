#include "menu.h"

#define GetAddr(ptr, field)(void*)pmg_read_word(((uint8_t*)ptr)+offsetof(struct _menuitem, field))

static const struct _menuitem *currMenuPtr=&menu;
static uint8_t menuindex;
static uint8_t menufitstpos;

Void Menu_Back()
{
	const struct _menuitem *tmpMenuPtr=GetAddr(currMenuPtr,parent);
	menufirstpos=0;
	menuindex=0;
	currMenuPtr*tmpMenuPtr;
}
