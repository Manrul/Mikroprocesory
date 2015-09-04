int funkcja(void)
{
	unsigned char  pom;//wy dajecie uint8_t;	
	int a = 0x4A3B2C1D;//uint32_t
	pom = a;
	if (pom == 0x4A)
		return 1;
	else if (pom == 0x1D)
		return 0;
	return -1;//jeśli bład
		
}
