
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <strings.h>

const int green=2; //lista stalych oznaczajacych kolory pisanego tekstu
const int red=4;
const int yellow=6;
const int white=7;
const int black=0;
const int N=10; //stala rozmiaru tablicy
const int N82=82; //rozmiar tablicy liczby wszystkich komorek
const int N3=3; //uzywane przy liscie komorek do wypelnienia
const int N51=51; //stale oznaczajace zakres ile ma byc pol pustych przy generownaiu planszy dla uzytkownika
const int N64=64;

//lista naglowkow funkcji uzytych w programie
void kolor(int const c); //zmiana koloru
void p(); //pausa
void c(); //czyszczenie ekranu
void wyzeruj(int W[N]); //wyzerowanie ciagu liczb, wykorzystywane przy sprawdzaniu czy liczby nie powtarzaja sie w wierszu, kolumnie, kwadracie
int poprawnaPlansza(int A[N][N]); //sprawdzenie czy wpisano poprawna plansze wejsciowa
int sprawdzRozwiazanie(int A[N][N]); //sprawdzenie czy aktualny stan planszy nie jest juz rozwiazaniem sudoku
int jestt(int liczba, int ii, int jj, int A[N][N]); //sprawdzenie czy liczba jest na planszy, uzywana na jednym z etapow rozwiazania
void wypisz (int A[N][N]); //wypisanie planszy rozwiazanej przez komputer
void wypiszU(int A[N][N], int Z[N][10]); //wypisywanie planszy rozwiazywanej przez uzytkownika, z kolorami
int wstawliczbe(int ii, int jj, int A[N][N]); //funkcja probujaca wstawic liczbe do planszy na dana pozycje, pierwsza mozliwa, uzywana przy rozwiazywaniu planszy przez komputer
void wstawliczbeU(int A[N][N], int Z[N][N], int indi, int indj, int L); //wstawianie liczby podanej przez uzytkownika na konkretne miejsce
void wczytanieDlakomputera(int As[N][N]); //wczytywanie planszy sudoku do rozwiazania przez komputer
int rozwiazujeKomputer(int T[N][N]); //rozwiazywanie planszy przez komputer, zwraca 1 jezeli udalo sie rozwiazac plansze, 0 - jezeli nie
int losuj(int a, int b); //losowanie liczby z zakresu [a, b] uzywana przy losowaniu liczb oraz stanow planszy
void permutuj(int P[N], int n); //losowe permutowanie ciagu 9 liczb, potrzebne przy generowaniu plansz dla uzytkownika
void Generuj(int G[N][N], int Z[N][N]); //generowanie planszy sudoku dla uzytkownika do rozwiazania
void instrukcja(); //wypisanie instrukcji dla uzytkownika programu

void wyzeruj(int W[N])
{
   int i;
   for (i=1;i<10;i++) W[i]=0;
}

//idea dzialania, zliczam poszczegolne liczby w kazdym wierszu kolumnie i kwadracie 3 x 3, jezeli gdzies znajde powtarzajaca sie liczbe, to plansza jest bledna
int poprawnaPlansza(int A[N][N])
{
   int ok=1;
   int i,j,wiersz,kolumna;
   int W[N];
   wiersz=1;
   while (wiersz<N && ok)
   {
      wyzeruj(W);
      for (j=1;j<N;j++) { if (A[wiersz][j]>0) W[A[wiersz][j]]++;} //sprawdzenie wierszy
      j=1;
      while (j<N && ok)
      {
         ok=(W[j]<2);
         j++;
      }
      wiersz++;
   }
   kolumna=1;
   while (kolumna<N && ok) //sprawdzenie kolumn
   {
     wyzeruj(W);
     for (i=1;i<N;i++) {if (A[i][kolumna]>0) W[A[i][kolumna]]++;}
     i=1;
     while (i<N && ok)
     {
       ok=(W[i]<2);
       i++;
     }
     kolumna++;
   }
   //.....
   wyzeruj(W);
   for (i=1;i<=3;i++) //sprawdzenie wszystkich 9 kwadratow
   for (j=1;j<=3;j++)
   {
       if (A[i][j]>0) W[A[i][j]]++;
   }
   i=1;
   while (i<N && ok)
   {
     ok=(W[i]<2);
     i++;
   }
   //.....
   wyzeruj(W);
   for (i=1;i<=3;i++)
   for (j=4;j<=6;j++)
   {
       if (A[i][j]>0) W[A[i][j]]++;
   }
   i=1;
   while (i<N && ok)
   {
     ok=(W[i]<2);
     i++;
   }
   //.............
   wyzeruj(W);
   for (i=1;i<=3;i++)
   for (j=7;j<=9;j++)
   {
       if (A[i][j]>0) W[A[i][j]]++;
   }
   i=1;
   while (i<N && ok)
   {
     ok=(W[i]<2);
     i++;
   }
   //........
   wyzeruj(W);
   for (i=4;i<=6;i++)
   for (j=1;j<=3;j++)
   {
       if (A[i][j]>0) W[A[i][j]]++;
   }
   i=1;
   while (i<N && ok)
   {
     ok=(W[i]<2);
     i++;
   }
//........
   wyzeruj(W);
   for (i=4;i<=6;i++)
   for (j=4;j<=6;j++)
   {
       if (A[i][j]>0) W[A[i][j]]++;
   }
   i=1;
   while (i<N && ok)
   {
     ok=(W[i]<2);
     i++;
   }
//.....
   wyzeruj(W);
   for (i=4;i<=6;i++)
   for (j=7;j<=9;j++)
   {
       if (A[i][j]>0) W[A[i][j]]++;
   }
   i=1;
   while (i<N && ok)
   {
     ok=(W[i]<2);
     i++;
   }
//.................
   wyzeruj(W);
   for (i=7;i<=9;i++)
   for (j=1;j<=3;j++)
   {
       if (A[i][j]>0) W[A[i][j]]++;
   }
   i=1;
   while (i<N && ok)
   {
     ok=(W[i]<2);
     i++;
   }
//...........
   wyzeruj(W);
   for (i=7;i<=9;i++)
   for (j=4;j<=6;j++)
   {
       if (A[i][j]>0) W[A[i][j]]++;
   }
   i=1;
   while (i<N && ok)
   {
     ok=(W[i]<2);
     i++;
   }
//............
   wyzeruj(W);
   for (i=7;i<=9;i++)
   for (j=7;j<=9;j++)
   {
       if (A[i][j]>0) W[A[i][j]]++;
   }
   i=1;
   while (i<N && ok)
   {
     ok=(W[i]<2);
     i++;
   }
  return ok;
}

int sprawdzRozwiazanie(int A[N][N]) //idea dzialania, sprawdzam czy na planszy nie zostalo gdzies 0, jezeli nie to sprawdzam poprawnosci planszy, jezeli znalazlem gdzies 0, to nierozwiazana
{
	int i, j, odp, jest0=0;
	for(i=1;i<N && !jest0; i++)
	for(j=1;j<N && !jest0; j++) if(A[i][i]==0) jest0=1;
	if(jest0) odp=0; else odp=poprawnaPlansza(A);
	return odp;
}

int jestt(int liczba, int ii, int jj, int A[N][N]) //sprawdzenie czy liczba jest w danym wierszu kolumnie lub kwadracie, czyli czy potem moge ja wstawic
{
   int jest=0;
   int i,j,i1,j1;

   j=1;
   while (j<N)
   {
     if (A[ii][j]==liczba) jest=1;
     j++;
   }
   i=1;
   while (i<N)
   {
     if (A[i][jj]==liczba) jest=1;
     i++;
   }
   if (ii<4) i=1; else
   {
       if (ii>3 && ii<7) i=4; else
       {
          i=7;
       }
   }
   if (jj<4) j=1; else
   {
       if (jj>3 && jj<7) j=4; else
       {
          j=7;
       }
   }
   for (i1=i;i1<i+3;i1++)
   for (j1=j;j1<j+3;j1++)
   {
     if (A[i1][j1]==liczba) jest=1;
   }
   return jest;
}

void wypisz (int A[N][N])
{
     int i;
     for (i=1; i<N; i++)
     {
     	    printf("  %d %d %d | %d %d %d | %d %d %d\n",
			        A[i][1], A[i][2], A[i][3], A[i][4], A[i][5], A[i][6], A[i][7], A[i][8], A[i][9]);
            if (i%3==0 && i<9) printf("  ----------------------\n");
     }
     printf("\n\n");
}

void wypiszU(int A[N][N], int Z[N][10])
{
	int i, j;
	kolor(white);
	for(i=1;i<N;i++)
	{
		printf("  ");
		for(j=1;j<=3;j++)
		{
			if(Z[i][j]==1) kolor(green); else if(Z[i][j]==0) kolor(black); else kolor(white); printf(" %d ", A[i][j]);
		}
		kolor(white); printf("|");
		for(j=4;j<=6;j++)
		{
			if(Z[i][j]==1) kolor(green); else if(Z[i][j]==0) kolor(black); else kolor(white); printf(" %d ", A[i][j]);
		}
		kolor(white); printf("|");
		for(j=7;j<=9;j++)
		{
			if(Z[i][j]==1) kolor(green); else if(Z[i][j]==0) kolor(black); else kolor(white); printf(" %d ", A[i][j]);
		}
		printf("\n");
		if (i%3==0 && i<9)
		{
			kolor(white);
			printf("  ----------------------------\n");
		}
	}
	printf("\n");
	kolor(white);
}

//idea dzialania, funkcja sprawdza czy na pozycje ii, jj moge wstawic inna liczbe niz jest obecnie, czyli szukam nastepnej mozliwej liczby do wstawienia
//jezeli sie da to podmieniam, jezeli nie to zwracam 0
int wstawliczbe(int ii, int jj, int A[N][N])
{
   int wpisano=0;
   int L, LL, min;

   min=A[ii][jj];
   A[ii][jj]=0;
   LL=min;
          for (L=N-1;L>min;L--)
          {
              if (!jestt(L,ii,jj,A))
              {
                LL=L;
              }

          }
          if (LL>min)
          {
             A[ii][jj]=LL;
             wpisano=1;
          } else
          {
             A[ii][jj]=0;
             wpisano=0;
          }
   return wpisano;
}

void wstawliczbeU(int A[N][N], int Z[N][N], int indi, int indj, int L)
{
   if(indi>=1 && indi<N && indj>=1 && indj<N && L>=0 && L<N)
   {
   	  if(Z[indi][indj]<=0) //jezeli jest to komorka mozliwa do zmiany
   	  {
   	  	  if(L==0) Z[indi][indj]=0; else Z[indi][indj]=-1; //jezeli uzytkownik chce wstawic 0, czyli usunac poprzednia liczbe to zeruje komorke, jezeli podmienia inna liczba to tablica Z zapamietuje ze zmienil, ma to znaczenie przy kolorze wypisywania tej komorki
   	  	  A[indi][indj]=L;
	  }
   }
}

void wczytanieDlakomputera(int As[N][N])
{
     int i;
     kolor(white);
     for (i=1;i<N; i++) //pobranie wszystkich 9 linii liczb do planszy
     {
     	printf("  ");
     	scanf("%d %d %d %d %d %d %d %d %d",
	       &As[i][1], &As[i][2], &As[i][3], &As[i][4], &As[i][5], &As[i][6], &As[i][7], &As[i][8], &As[i][9]);
	 }
}


int rozwiazujeKomputer(int T[N][N])
{
	int Tas[N3][N82]; //tablica przechowujaca indeksy pustych pol, czyli edytowalnych
    int i, j, min,L,LL,nr,
	ile=0; //liczba komoek do wypelnienia
	int ok=1;

	if(poprawnaPlansza(T)) //jezeli plansza jest poprawna to dopiero wtedy probuje ja wypelnic
	{
		for(i=1;i<N;i++)
        for(j=1;j<N;j++)
        {
           if (T[i][j]==0)
		   {
		     ile++; Tas[1][ile]=i;
			 Tas[2][ile]=j;
		   } //zliczam i wstawiam do Tas indeksy pol do wstawienia wtedy poruszajac sie na lewo lub prawo mam aktualne indeksy do wstawienia
        }
        if (ile>0) //jezeli jest do wypelnienia przynajmniej jedno pole
        {
          nr=1; //ustawiam czytnik Tas na pierwsza pozycje
          while (nr>0 && nr<=ile) //dopoki nr jest w zakresie Tas
          {
              if (wstawliczbe(Tas[1][nr], Tas[2][nr], T)) nr++; else nr--;
			  //jezeli udalo mi sie wstawic liczbe do komorki to przesuwan nr na nastepna pozycje, jezeli nie to przesuwam sie do pozycji poprzedniej
			  //i znow probuje wstawic nastepna liczbe
          }
          ok=(nr>ile); //rozwiazywanie sie zakonczy jezeli nr przekroczy liczbe cyfr do wstawienia do planszy, to znaczy ze wypelnil wszystko
        }
	} else ok=0; //jezeli plansza niepoprawna
	return ok;
}

int losuj(int a, int b)
{
	return a+rand()%(b-a+1);
}

void permutuj(int P[N], int n)
{
	int i, j, k, temp;
	for(i=1;i<N;i++) P[i]=i;
	for(k=1;k<=n;k++)
	{
		i=losuj(1, N-1); //losuje 2 pozycje do zamiany miejscami
		j=losuj(1, N-1);
		if(i!=j) //jezeli sa rozne, to zamieniam miejscami liczby na pozycji i oraz j, wtedy mam permutacje
		{
			temp=P[i];
			P[i]=P[j];
			P[j]=temp;
		}
	}
}

void Generuj(int G[N][N], int Z[N][N])
{
	int P[N];
	int i, j, k, ok, us;

	for(i=1;i<10;i++)
	for(j=1;j<10;j++)
	{
		G[i][j]=0; //zeruje plansze
		Z[i][j]=1; //tablice stanu planszy wypelniam jedynkami, czyli na razie nic nie mozna zmienic, nizej to sie zmieni
	}

	permutuj(P, (N-1)*(N-2)/2); //permutuje ciag 9 liczb
	k=1;
	for(i=1;i<=3;i++) //i przepisuje go do lewego gornego kwadratu
	for(j=1;j<=3;j++)
	{
		G[i][j]=P[k];
		k++;
	}
	permutuj(P, (N-1)*(N-2)/2);
	k=1;
	for(i=4;i<=6;i++) //to samo dla kwadratu centralnego
	for(j=4;j<=6;j++)
	{
		G[i][j]=P[k];
		k++;
	}
	permutuj(P, (N-1)*(N-2)/2);
	k=1;
	for(i=7;i<N;i++) //to samo dla kwadratu prawego dolnego
	for(j=7;j<N;j++)
	{
		G[i][j]=P[k];
		k++;
	}
	ok=rozwiazujeKomputer(G); //reszte rozwiazuje komputer
	us=losuj(N51, N64); //losuje ile liczb usunac z planszy i zastapic je zerami
	while(us)
	{
		do //losuje tak dlugo az znajde cos co da sie usunac
		{ //losuje wspolrzedna w tablicy, gdzie zniknie liczba
			i=losuj(1, N-1);
		    j=losuj(1, N-1);
		}while(G[i][j]==0);
		G[i][j]=0; //usuwam ja w planszy
		Z[i][j]=0; //i zaznaczam w Z, ze mozna ja edytowac
		us--;
	}
}

void kolor(int const c)
{
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hConsole, c);
}

void c()
{
	system("cls");
}

void p()
{
	system("pause");
}

void instrukcja()
{
	c();
	kolor(white);
	printf("W trybie rozwiazywania przez komputer podajemy 9 liczb w kazdej linii oddzielone spacja i zatwierdzamy enterem.\n");
	printf("W trybie rozwiazywania przez uzytkownika komputer losuje plansze.\n");
	printf("Liczby wejsciowe planszy, ktorych nie mozna zmienic wyswietlane sa na zielono.\n");
	printf("Liczby wpisane przez uzytkownika wyswietlane sa na bialo.\n");
	printf("Aby wpisac liczbe do komorki podajemy 3 liczby oddzielone spacja.\n");
	printf("Pierwsze dwie liczby oznaczaja wspolrzedne polozenia trzeciej wpisanej liczby.\n");
	printf("Jezeli wpiszemy trzecia liczbe 0, to poprzednia jest usuwana.\n");
	printf("Przyklad poprawnie wpisanej liczby do planszy 4 5 7\n");
	kolor(green);
	printf("Milej zabawy\n");
	kolor(white);
	p();
}

int main(int argc, char *argv[])
{

    int sud[N][N]; //plansza sudoku
    int zajete[N][N]; //tablica przechowujaca stan planszy,ktore numery sa dane z gory jako wejsciowe i nie mozna ich zmienic oraz ktore wypelnil uzytkownik

    int indeksi,
	    indeksj, //wspolrzedne tablicy do wypelnienia liczba przez uzytkownika
		L,  //wstawiana liczba przez uzytkownika
		ok, //zmienna przechwytujaca poprawnosc wpisanej planszy
		rozw; //zmienna pamietajaca czy jest plansza rozwiazana
    char wybor; //zmienna pamietajaca wybor opcji z menu
    srand(time(NULL));//inicjacja generatora liczb losowych
    do //petla dzialajaca tak dlugo az nie wprowadzimy znaku k, czyli zakonczenia programu
    {
    	c(); //czysc ekran
    	kolor(yellow);
    	printf("  M E N U\n");
    	printf("  i - Instrukcja\n");
    	printf("  r - Sudoku rozwiazuje komputer\n");
    	printf("  u - Sudoku rozwiazuje uzytkownik\n");
    	printf("  k - Koniec programu\n");
    	printf("  >");
    	scanf("%c", &wybor);
    	fflush(stdin); //czyszczenie bufora wejscia z klawiatury, czasami bez tego dzieja sie dziwne rzeczy, np. pomija sie instrukjca scanf
    	wybor=tolower(wybor); //zamiana wczytanego znaku na maly, nie musimu sprawdzac czy wpisano np r czy R
    	switch(wybor) //instrukcja sprawdzajaca co wybrano z menu
    	{
    		case 'i':
    		  instrukcja();
    		break;
    		case 'r':
    		  kolor(white);
    		  printf("Podaj 9 wierszy z liczbami od 0 do 9 oddzielonymi spacjami i zatwierdzaj enterem.\n");
			  printf("Jako puste pole wstaw 0\n\n");
              wczytanieDlakomputera(sud);
			  if(poprawnaPlansza(sud))
			  {
			  	  ok=rozwiazujeKomputer(sud);
			  	  if(ok)
				  {
				  	 kolor(green);
				  	 printf("\n  A oto plansza rozwiazana przez komputer:\n");
				  	 kolor(white);
				  	 wypisz(sud);
				  }	else
			  	  {
			  	  	 kolor(red);
			  	     printf("Brak rozwiazania planszy\n");
			  	     kolor(white);
				  }
			  } else
			  {
			  	  kolor(red);
			  	  printf("Niepoprawna plansza sudoku\n");
			  	  kolor(white);
			  }
			  p();
    		break;
    		case 'u':
    			kolor(white);
    			Generuj(sud, zajete);
    			do //petla dzialajaca tak dlugo az nie wpiszemy 0 0 0 co konczy wpisywanie liczb przez rozwiazujacego czlowieka
    			{
    				c();
    				printf("\n");
    			    printf("  Aby wpisac liczbe do komorki podajesz wspolrzedne komorki oraz wartosc,\n");
    			    printf("  czyli 3 liczby. Wpisanie 3 zer konczy rozwiazywanie\n");
    			    printf("  Sudoku do rozwiazania\n");
    			    printf("\n");
    				wypiszU(sud, zajete);
    				fflush(stdin);
    				printf("  >>> ");
    				scanf("%d %d %d", &indeksi, &indeksj, &L);
    				wstawliczbeU(sud, zajete, indeksi, indeksj, L);
    				rozw=sprawdzRozwiazanie(sud);
    				if(rozw) break; //jezeli uzytkownik wpisal ostatnia liczbe i plansza jest rozwiazana, to petla sie konczy
				}while(indeksi!=0 || indeksj!=0 || L!=0);
    			if(rozw)
				{
					kolor(green);
					printf("Plansza rozwiazana poprawnie.\n");
					kolor(white);
				} else
				{
				   kolor(red);
				   printf("Plansza nierozwiazana.\n");
				   kolor(white);
				}
    			p();
    		break;
		}
    	kolor(white);
	}while(wybor!='k'); //koniec petli sprawdzajacej jaki znak wpisano
    return 0;
}
