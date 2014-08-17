 #include<avr/io.h>
 #include <avr/pgmspace.h>
 
 typedef void(*menuitemfuncptr)();
 struct PROGMEM _menuitem
 {
	 const char   *text;
	 menuitemfuncptr menuitemfunc;
	 const struct _menuitem *parent;
	 const struct _menuitem *submenu;
	 const struct _menuitem *next;
	 };
	 /* text-wskaznik do pamieci flash ,w której znajduje sie tekst opisuj?cy dan? pozycje menu
	 menuitemfunc-wskaznik do funcji wywolywanej po wybraniu danej funkcji
	 parent-wskaznik do struktury rodzica, lub null
	 submenu-wska?nik do struktury podmenu,lub null
	 next wskaznik do kolejnej struktury opisujaca kolejna pozycje menu*/
	 
	 void Menu_Back();
	 void menufunc7();
	 void menufunc6();
	 void menufunc5();
	 void menufunc4();
	 void menufunc3();
	 void menufunc2();
	 void menufunc1();
	 
	 const char __attribute__((__progmem__)) txt1[]="Menu1";
	 const char __attribute__((__progmem__)) txt2[]="Menu2";
	 const char __attribute__((__progmem__)) txt3[]="Menu3";
	 const char __attribute__((__progmem__)) txt4[]="Menu4";
	 
	 const char __attribute__((__progmem__)) txt5[]="Podmemu A1";
	 const char __attribute__((__progmem__)) txt6[]="Podmemu A2";
	 const char __attribute__((__progmem__)) txt7[]="Podmemu A3";
	 
	 const char __attribute__((__progmem__)) txt8[]="Podmemu B1";
	 const char __attribute__((__progmem__)) txt9[]="Podmemu B2";
	 const char __attribute__((__progmem__)) txt10[]="Powrot";
	 const char __attribute__((__progmem__)) txt11[]="F: ";
	 
	 
	 extern struct  _menuitem PROGMEM const menu;
	 
	 
	 struct _menuitem const menu;
	 struct _menuitem const menuA1;
	 struct _menuitem const menuB1;
	 
	 struct _menuitem const menuB3 PROGMEM = {txt10,Menu_Back,&menuB1,0,0};
	 struct _menuitem const menuB2 PROGMEM = {txt9,menufunc7,&menuB1,0,&menuB3};
	 struct _menuitem const menuB1 PROGMEM = {txt8,menufunc6,&menuA1,0,&menuB2};
	 
	 struct _menuitem const menuA4 PROGMEM = {txt10,Menu_Back,&menuA1,0,0};
	 struct _menuitem const menuA3 PROGMEM = {txt7,menufunc5,&menuA1,0,&menuA4};
	 struct _menuitem const menuA2 PROGMEM = {txt6,0,&menuA1,&menuB1,&menuA3};
	 struct _menuitem const menuA1 PROGMEM = {txt5,menufunc4,&menu,0,&menuA2};
	 
     struct _menuitem const menu3 PROGMEM = {txt4,menufunc3,&menu,0,0};
     struct _menuitem const menu2 PROGMEM = {txt3,menufunc2,&menu,0,&menu3};
	 struct _menuitem const menu1 PROGMEM = {txt2,0,&menu,&menuA1,&menu2};
     struct _menuitem const menu  PROGMEM = {txt1,menufunc1,0,0,&menu1};
		 
	
