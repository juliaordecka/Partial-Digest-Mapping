#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <ostream>

using namespace std;


int Licznikznakow(string nazwa)
{
	fstream file;
	file.open(nazwa, ios::in);

	if (!file.good())
	{
		printf("\nnie mozna otworzyc pliku");
		exit(0);
	}

	if (file.peek() == EOF)
	{
		printf("\nplik jest pusty");
		file.close();
		exit(0);
	}

	int wyraz;
	int licznikwyrazow = 0;
	while (!file.eof())
	{
		while (file >> wyraz)
		{
			licznikwyrazow++;
		}
	}
	file.close();

	return licznikwyrazow;
}

void Wczytaj(int tabinstancja[], string nazwa)
{

	fstream file;

	file.open(nazwa, ios::in);
	int a = 0;
	int wyraz;
	while (!file.eof())
	{
		while (file >> wyraz)
		{
			tabinstancja[a] = wyraz;
			a++;
		}
	}

	file.close();

}

void Isnumeric(string nazwa)
{
	fstream file;
	file.open(nazwa, ios::in);
	char slowo;

	while (!file.eof())
	{
		while (file >> slowo)
		{
			if (!isdigit(slowo))
			{
				cout << "nieprawidlowy plik zawierajacy inne znaki niz numeryczne\n";
				file.close();
				exit(0);
			}
		}
	}

	file.close();
}

void Sortujwejscie(int tabinstancja[], int licznikwyrazow)
{
	sort(tabinstancja, tabinstancja + licznikwyrazow);
	cout << "\nPosortowana tablica: ";
	for (int i = 0; i < licznikwyrazow; i++)
	{
		cout << tabinstancja[i] << " ";
	}

}

int Liczbaciec(int A) 
{
	//k*k+3*k+2-2A=0 
	int a = 1;
	int b = 3;
	int c = 2 - (2 * A);

	double delta = b * b - (4 * a * c);

	double k1 = (-b - (sqrt(delta))) / (2 * a);
	double k2 = (-b + (sqrt(delta))) / (2 * a);

	if (k1 > 0 && (k1 - floor(k1)) == 0)
	{
		return k1;
	}
	else if (k2 > 0 && (k2 - floor(k2)) == 0)
	{
		return k2;
	}
	else
	{
		printf("\nNieprawidlowa liczba elementow instancji, nie przeklada sie (nie mozna okreslic) na liczbe ciec.");
		return 0;
	}
}

int Szukaj(int mapa[], int liczbaelementowmapy, int** kopiatabinstancja, int makswartwtabinst, int nrelementumapy)
{
	int liczba1, liczba2;
	int suma;
	int potencjalny = 0;

	int zredukowana_makswartwtabinstancja = makswartwtabinst - (kopiatabinstancja[makswartwtabinst + 1][nrelementumapy - 1]);

	if ((zredukowana_makswartwtabinstancja < kopiatabinstancja[0][nrelementumapy] + 1) && nrelementumapy > 2)
	{
		for (int k = 0; k <= makswartwtabinst + 1; k++)
		{
			kopiatabinstancja[k][nrelementumapy] = 0;
		}
		nrelementumapy = nrelementumapy - 1;
		for (int k = 1; k <= makswartwtabinst + 1; k++)
		{
			kopiatabinstancja[k][nrelementumapy] = 0;
		}
		return Szukaj(mapa, liczbaelementowmapy, kopiatabinstancja, makswartwtabinst, nrelementumapy); 
	}
	
	for (int i = kopiatabinstancja[0][nrelementumapy] + 1; i <= zredukowana_makswartwtabinstancja; i++)
	{
		if (kopiatabinstancja[i][0] > 0)
		{
			liczba1 = kopiatabinstancja[i][0];
			for (int k = nrelementumapy - 1; k >= 1; k--)
			{
				liczba1 = liczba1 - kopiatabinstancja[i][k]; 
				
			}

			if (liczba1 > 0)
			{
				potencjalny = 1; 
				kopiatabinstancja[i][nrelementumapy] = 1;
				suma = i; 
				for (int j = nrelementumapy - 1; j >= 1; j--)
				{
					suma = suma + mapa[j];
					if (suma > makswartwtabinst)
					{
						potencjalny = -1;
						for (int k = 0; k <= makswartwtabinst + 1; k++)
						{
							kopiatabinstancja[k][nrelementumapy] = 0;
						}
						break;
					}

					liczba2 = kopiatabinstancja[suma][0];
					for (int k = nrelementumapy - 1; k >= 1; k--)
					{
						liczba2 = liczba2 - kopiatabinstancja[suma][k];
					}
					if (liczba2 < 1)
					{
						potencjalny = 0;
						for (int k = 0; k <= makswartwtabinst + 1; k++)
						{
							kopiatabinstancja[k][nrelementumapy] = 0;
						}
						break;
					}
					else
					{
						kopiatabinstancja[suma][nrelementumapy] = 1;
						
					}
				}

				if (potencjalny == 0 && i >= zredukowana_makswartwtabinstancja)
				{
					for (int k = 0; k <= makswartwtabinst + 1; k++)
					{
						kopiatabinstancja[k][nrelementumapy] = 0;
					}
					nrelementumapy = nrelementumapy - 1;
					for (int k = 1; k <= makswartwtabinst + 1; k++)
					{
						kopiatabinstancja[k][nrelementumapy] = 0;
					}
					
					if (nrelementumapy > 1)
					{
						return Szukaj(mapa, liczbaelementowmapy, kopiatabinstancja, makswartwtabinst, nrelementumapy);
					}
					else
					{
						return -1;
					}
				}
				if (potencjalny == 1)
				{
					kopiatabinstancja[0][nrelementumapy] = i;
					kopiatabinstancja[makswartwtabinst + 1][nrelementumapy] = kopiatabinstancja[makswartwtabinst + 1][nrelementumapy - 1] + i; 
					mapa[nrelementumapy] = i;
					nrelementumapy = nrelementumapy + 1;
			
					if (nrelementumapy <= liczbaelementowmapy)
					{
						return Szukaj(mapa, liczbaelementowmapy, kopiatabinstancja, makswartwtabinst, nrelementumapy);
					}
					else
					{
						return 0;
					}
				}
				if (potencjalny == -1 && nrelementumapy > 2)
				{
					nrelementumapy = nrelementumapy - 1;
					for (int k = 1; k <= makswartwtabinst + 1; k++) 
					{
						kopiatabinstancja[k][nrelementumapy] = 0;
					}
				
					if (nrelementumapy > 1)
					{
						return Szukaj(mapa, liczbaelementowmapy, kopiatabinstancja, makswartwtabinst, nrelementumapy);
					}
					else 
					{
						return -1;
					}
				}
			}
			else if (i >= zredukowana_makswartwtabinstancja && nrelementumapy > 2) 
			{
				for (int k = 0; k <= makswartwtabinst + 1; k++)//
				{
					kopiatabinstancja[k][nrelementumapy] = 0;
				}
				nrelementumapy = nrelementumapy - 1;
				for (int k = 1; k <= makswartwtabinst + 1; k++)// 
				{
					kopiatabinstancja[k][nrelementumapy] = 0;
				}
				
				if (nrelementumapy > 1)
				{
					return Szukaj(mapa, liczbaelementowmapy, kopiatabinstancja, makswartwtabinst, nrelementumapy);
				}
				else 
				{
					return -1;
				}
			}
		}
		else if (i >= zredukowana_makswartwtabinstancja && nrelementumapy > 2)
		{
			for (int k = 0; k <= makswartwtabinst + 1; k++)
			{
				kopiatabinstancja[k][nrelementumapy] = 0;
			}
			nrelementumapy = nrelementumapy - 1;
			for (int k = 1; k <= makswartwtabinst + 1; k++)
			{
				kopiatabinstancja[k][nrelementumapy] = 0;
			}
			if (nrelementumapy > 1)
			{
				return Szukaj(mapa, liczbaelementowmapy, kopiatabinstancja, makswartwtabinst, nrelementumapy);
			}
			else
			{
				return -1;
			}
		}
	}
	cout << "\nNie udalo sie, ostatni sprawdzany nr elementu mapy przed wykryciem bledu: " << nrelementumapy << "\n";
	return -1; 
}


int main()
{
	string nazwa;
	printf("Wpisz sciezke do pliku ktory chcesz otworzyc: ");
	cin >> nazwa;

	Isnumeric(nazwa);
	int licznikwyrazow;
	licznikwyrazow = Licznikznakow(nazwa);
	cout << "licznik wyrazow: " << licznikwyrazow << "\n";

	int* tabinstancja = new int[licznikwyrazow];
	Wczytaj(tabinstancja, nazwa);
	
	for (int i = 0; i < licznikwyrazow; i++)
		cout << tabinstancja[i] << " ";
	Sortujwejscie(tabinstancja, licznikwyrazow);

	int liczbaciec = Liczbaciec(licznikwyrazow);
	if (liczbaciec == 0)
	{
		return 0;
	}
	cout << "\nLiczba ciec dla licznosci multizbioru " << licznikwyrazow << " wynosi " << liczbaciec << "\n";

	int liczbaelementowmapy = liczbaciec + 1; 
	int* mapa = new int[liczbaelementowmapy];

	int pierwszy = tabinstancja[licznikwyrazow - 1] - tabinstancja[licznikwyrazow - 2];
	int istnieje = 0;

	for (int i = 0; i < licznikwyrazow; i++) 
	{
		if (pierwszy == tabinstancja[i])
		{
			istnieje = 1;
			break;
		}
	}
	if (istnieje == 0)
	{
		cout << "Pierwszy element mapy nie istnieje w Instancji, nie mozna wyznaczyc mapy.";
		return 0;
	}
	
	cout << "pierwszy element mapy: " << tabinstancja[licznikwyrazow - 1] - tabinstancja[licznikwyrazow - 2] << "\n";

	int makswartwtabinst = tabinstancja[licznikwyrazow - 1];

	int** kopiatabinstancja = new int* [makswartwtabinst + 2]; 
	for (int i = 0; i <= makswartwtabinst + 1; i++)
	{
		kopiatabinstancja[i] = new int[liczbaelementowmapy + 1]();
	}
	
	for (int i = 0; i <= makswartwtabinst + 1; i++) 
	{
		for (int j = 0; j <= liczbaelementowmapy; j++)
		{
			kopiatabinstancja[i][j] = 0;
		}
	}

	for (int i = 0; i < licznikwyrazow; i++) 
	{
		kopiatabinstancja[tabinstancja[i]][0] = kopiatabinstancja[tabinstancja[i]][0] + 1;
	}


	if (kopiatabinstancja[pierwszy][0] > 0)
	{
		kopiatabinstancja[pierwszy][1] = 1; 
		kopiatabinstancja[makswartwtabinst + 1][1] = pierwszy; 
		mapa[1] = pierwszy; 
	}
	
	int nrelementumapy = 2;
	int wynik;

	chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();


	wynik = Szukaj(mapa, liczbaelementowmapy, kopiatabinstancja, makswartwtabinst, nrelementumapy);
	if (wynik == -1)
	{
		cout << "Blad obliczen, wyniki niewiarygodne.";
		
	}
	chrono::high_resolution_clock::time_point stop = chrono::high_resolution_clock::now();

	chrono::duration<double> czas_trwania;
	czas_trwania = chrono::duration_cast<chrono::duration<double>>(stop - start);
	cout << "\nCzas trwania wyliczenia mapy: " << czas_trwania.count() << " sekund\n";

	cout << "\nMapa: ";
	for (int i = 1; i < liczbaelementowmapy + 1; i++)
	{
		cout << mapa[i] << ", ";
	}

	for (int i = 0; i <= makswartwtabinst; i++)
	{
		delete[] kopiatabinstancja[i];
	}
	delete[] kopiatabinstancja;

	return 0;
}