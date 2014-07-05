#include<stdlib.h>
#include<stdio.h>
#include<time.h>


   //tablice
int *alokuj_jednowymiarowe(int n)
{
	int *tab;
	tab=(int*)malloc(n*sizeof(int));
	return tab;

}
int **alokuj_dwuwymiarowe(int n,int m)
{

  int i;
  int **tab; 
  tab = (int **) malloc(sizeof(int*)* n);
  for ( i = 0; i < n; i++)
     { 
       tab[i] = (int *) malloc(sizeof(int)* m);
      }   
    return tab;
}

void zwolnij_jednowymiarowe(int *tab)
{
	free(tab);
}
void zwolnij_dwuwymiarowe(int **tab,int m)
{
	int i;
	for(i=0;i<m;i++)
	  free(*tab);

	 free(tab);
}
void uzupelnij_jednowymiarowa(int *tab,int n,int m)
{
	int i;
	for(i=0;i<n;i++)
     {
         tab[i]=rand()%10+2;
      }

}
void uzupelnij_dwuwymiarowa(int **tab,int n,int m)
{
	int i,j;
	for(i=0;i<n;i++)
       {
         for(j=0;j<m;j++)
             {
               tab[i][j]=rand()%10+2;
		 }
	}

}

//macierze
void wypisz(int **tablica,int n,int m)
{
	int i,j;
	for(i=0;i<n;i++)
       {
         for(j=0; j<m; j++)
             {
               printf("%3d ", tablica[i][j]);
		 }
		 printf("\n");
	}
}
void transkrypcja_macierzy(int **tablica,int n,int m)
{
	int i,j,**tablica2;

	tablica2=(int**)malloc(n*sizeof(int *));

for(i=0; i<m; i++)
{
tablica2[i]=(int*)malloc(n*sizeof(int));

}
	

	/*kopiowanie tablica 1 do 2*/
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			tablica2[i][j]=tablica[i][j];
			}
		}

	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			tablica[i][j]=tablica2[j][i];
			}
		}
}
int **dodawanie_macierzy(int **tablica,int **tablica2,int n,int m)
{
	int i,j,**tablica3;

	tablica3=(int**)malloc(n*sizeof(int *));

for(i=0; i<n; i++)
{
tablica3[i]=(int*)malloc(m*sizeof(int));

}
	

	
	

	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			tablica3[i][j]=tablica2[i][j]+tablica[i][j];
			}
		}
	return tablica3;
	
}
int **odejmowanie_macierzy(int **tablica,int **tablica2,int n,int m)
{
	int i,j,**tablica3;

	tablica3=(int**)malloc(n*sizeof(int *));

for(i=0; i<n; i++)
{
tablica3[i]=(int*)malloc(m*sizeof(int));

}
	

	
	

	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			tablica3[i][j]=tablica2[i][j]-tablica[i][j];
			}
		}
	return tablica3;
	
}
int **mnozenie_macierzy(int **tab,int **tab2,int n,int m,int i,int j)
{
	if(m==i)
	{
	int **tab3,licznik1,licznik2,licznik3;
	//przygotowanie tablicy wynikowej
	tab3=(int**)malloc(n*sizeof(int *));

	for(licznik1=0; licznik1<n; licznik1++)
    {
          tab3[licznik1]=(int*)malloc(j*sizeof(int));
	}
        //zerowanie tablicy 3
	for(licznik1=0;licznik1<n;licznik1++)
             {
	           for(licznik2=0;licznik2<j;licznik2++)
                  tab3[licznik1][licznik2]=0;

              }
	

                  //mnozenie
	for(licznik1=0;licznik1<n;licznik1++)
	{
		for(licznik2=0;licznik2<j;licznik2++)
		{
			for(licznik3=0;licznik3<m;licznik3++)
			{
                tab3[licznik1][licznik2]+=tab[licznik1][licznik3]*tab2[licznik3][licznik2];
			}
		}
	}

	return tab3;
	}
	else 
		return NULL;

}
void mnozenie_macierzy_przezliczbe(int **tab,int n,int m,int liczba)
{
	int i,j;
	for(i=0;i<n;i++)
	  {
		  for(j=0;j<m;j++)
			  tab[i][j]=(liczba*tab[i][j]);
	}
}


main()
{
	int wybor=1,m,n,**tab,**tab2;
	printf("Co chcesz zrobic?\n");
	printf("1-Trankrypcja\n");
	printf("2-dodac\n");
	scanf("%d",&wybor);
	printf("Podaj wymiar macierzy(tab[n][m]\n");
	printf("n=");
	scanf("%d",&n);
	printf("m=");
	scanf("%d",&m);
	tab=alokuj_dwuwymiarowe(n,m);
	uzupelnij_dwuwymiarowa(tab,n,m);
	wypisz(tab,n,m);
	printf("\n");
     switch(wybor)
	 {
	 case 1:
		 {
			 
			 transkrypcja_macierzy(tab,n,m);
			 wypisz(tab,n,m);
			break;
		 }
	 case 2:
		 {
			 
			 tab2=alokuj_dwuwymiarowe(n,m);
	         uzupelnij_dwuwymiarowa(tab2,n,m);
			 wypisz(tab2,n,m);
			 wypisz(dodawanie_macierzy(tab,tab2,n,m),n,m);
			break;
		 }

		 zwolnij_dwuwymiarowe(tab,m);
		 zwolnij_dwuwymiarowe(tab2,m);

	 }
	 system("pause");


}
