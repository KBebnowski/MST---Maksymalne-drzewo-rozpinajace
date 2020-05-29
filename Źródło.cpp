#include <iostream>
#include <fstream>
#include <string>


class Kruskal {

private:
	short* tabelaKolorow;
	std::string* tabelaWierzcholkow;
	short** tabelaWzorow;
	std::fstream plikDoOdczytu;
	std::fstream plikDoZapisu;
	std::string nazwaOdczyt;	//nazwa pliku do odczytu
	std::string nazwaZapis;		//nazwa pliku do zapisu
	int Nv;						//ilosc krawedzi grafu
	int Ne;						//liczba krawedzi w grafie


public:
	Kruskal() {
		std::ifstream readFile;
		nazwaOdczyt = "dane";
		nazwaZapis = "";
		Nv = 0;
		Ne = 0;
	}

	void createTest() {
		std::cout << "Stworz plik do zapisu (podaj nazwe): ";
		std::cin >> nazwaZapis;

		plikDoOdczytu.open(nazwaOdczyt, std::ios::in);
		plikDoZapisu.open(nazwaZapis, std::ios::out | std::ios::app);

		if (plikDoOdczytu.good() == true) {

			tworzenieTablicyKolorow_i_Wierzcholkow();

			tworzenieTablicyWzorow();

			sortowanieTablicyWzorow();

			tworzenieMST();
		}
	}

	void tworzenieTablicyKolorow_i_Wierzcholkow() {

		plikDoOdczytu >> Nv;

		tabelaKolorow = new short[Nv];
		tabelaWierzcholkow = new std::string[Nv];

		for (int i = 0; i < Nv; i++) {
			plikDoOdczytu >> tabelaKolorow[i];
			plikDoOdczytu >> tabelaWierzcholkow[i];
		}
	}

	void tworzenieTablicyWzorow() {

		plikDoOdczytu >> Ne;

		tabelaWzorow = new short* [Ne];
		for (int i = 0; i < Ne; ++i) {
			tabelaWzorow[i] = new short[3];
		}

		for (int i = 0; i < Ne; i++) {
			for (int j = 0; j < 3; j++) {
				plikDoOdczytu >> tabelaWzorow[i][j];
			}
		}
	}

	void sortowanieTablicyWzorow() {

		for (int i = 0; i < Ne; i++)
		{
			for (int j = 0; j < Ne; j++)
			{
				if (j + 1 < Ne) {
					if (tabelaWzorow[j][2] > tabelaWzorow[j + 1][2]) {
						std::swap(tabelaWzorow[j][2], tabelaWzorow[j + 1][2]);
						std::swap(tabelaWzorow[j][1], tabelaWzorow[j + 1][1]);
						std::swap(tabelaWzorow[j][0], tabelaWzorow[j + 1][0]);
					}
				}
			}
		}
	}

	void tworzenieMST() {

		short kontener1 = tabelaWzorow[0][0];
		short glownyKlucz = kontener1;
		short kontener2 = 0;
		short wartosc = 0;
		short sprawdzenie = 0;

		short licznik = 0;
		short i = 0;
		while (licznik<Nv) {

			kontener1 = tabelaWzorow[i][0];
			kontener2 = tabelaWzorow[i][1];
			wartosc = tabelaWzorow[i][2];
		
			//odejmujemy oba kontenery poniewaz wczesniej jak tworzylismy tablice kolorow to przypisywalismy wartosc 1 do miejsca 0 w tabeli itd..
			kontener1--;						
			kontener2--;

			if (tabelaKolorow[kontener1] != tabelaKolorow[kontener2]) {
			
				plikDoZapisu << tabelaWierzcholkow[kontener1] << " " << tabelaWierzcholkow[kontener2] << " " << wartosc << std::endl;

				if (tabelaKolorow[kontener2] == glownyKlucz) {
					sprawdzenie = tabelaKolorow[kontener1];

					for (int i = 0; i < Nv; i++) {
						if (tabelaKolorow[i] == sprawdzenie) {
							tabelaKolorow[i] = tabelaKolorow[kontener2];;
						}
						if (tabelaKolorow[i] == glownyKlucz) {
							licznik++;
						}
						else {
							licznik = 0;
						}
					}
				}

				else {
					sprawdzenie = tabelaKolorow[kontener2];

					for (int i = 0; i < Nv; i++) {
						if (tabelaKolorow[i] == sprawdzenie) {
							tabelaKolorow[i] = tabelaKolorow[kontener1];;
						}
						if (tabelaKolorow[i] == glownyKlucz) {
							licznik++;
						}
						else {
							licznik = 0;
						}
					}
				}
			}
			i++;
		
		}

	}

	~Kruskal()
	{
		plikDoOdczytu.close();
		plikDoZapisu.close();
		delete[] tabelaKolorow;
		delete[] tabelaWierzcholkow;
		for (int z = 0; z < 3; z++) {
			delete[] tabelaWzorow[z];
		}
		delete[] tabelaWzorow;
	}

};

int main() {

	Kruskal kruskal;
	kruskal.createTest();

	return 0;
}