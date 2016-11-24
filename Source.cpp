//=============================================//
// Copyright - Emil Pirinen 2016 (16i260a)     //
// Ohjelmointikielet, perusteet - harjoitustyö //
//=============================================//

#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

// Prototyypit (oikeassa järjestyksessä)
void arvo_lottorivi(short oikea_rivi[], short oikea_lisrivi[]);
void kysy_lottorivi(short taul[], short rivi_size);
void oikean_lottorivin_arvonta();
void yhden_rivin_lotto();
void yhden_rivin_lotto_arvotulla_tuloksella();
void useamman_rivin_lotto_arvotulla_tuloksella();
void yhden_rivin_jokeri();
void kysy_jokeririvi(short taul[], short rivi_size);
void laske_pisteet(short& pts, short& pts_l, short oikea[], short oikea_l[], short user[]);
void tulosta_pisteet(short pts, short pts_l);
void tulostaValikko(char& valinta);
void bubble_sort(short a[], int n);
void clearInput();

// Globaalit vakiomuuttujat
const short LOTTONUMEROT = 39;
const short LOTTORIVI_KOKO = 7;
const short LISANUMEROT_KOKO = 2;
const short MAX_RIVIT = 10;
const short JOKERI_KOKO = 7;

// MAIN - Pääohjelma
int main() {

	// Muuttujat
	char valikonValinta;
	bool keep_going = true; // Jatketaanko ohjelman ajoa vai ei
	// Muuta
	srand(unsigned int(time(NULL))); // Siemenluku rand():ia varten

	do { // Valikkorakenne
		tulostaValikko(valikonValinta);
		//
		if (valikonValinta == '1') {
			oikean_lottorivin_arvonta();
		}
		else if (valikonValinta == '2') {
			yhden_rivin_lotto();
		}
		else if (valikonValinta == '3') {
			yhden_rivin_lotto_arvotulla_tuloksella();
		}
		else if (valikonValinta == '4') {
			useamman_rivin_lotto_arvotulla_tuloksella();
		}
		else if (valikonValinta == '5') {
			yhden_rivin_jokeri();
		}
		else {
			keep_going = false; // suljetaan ohjelma
		}
	} while (keep_going); // end of do-while

	return 0;
}

void arvo_lottorivi(short oikea_rivi[], short oikea_lisrivi[]) {
	// Arvotaan lottorivi
	short lottonumerot[LOTTONUMEROT];
	// alustetaan taulukkoon lottonumerot 1-39
	for (int i = 0; i < LOTTONUMEROT; i++) {
		lottonumerot[i] = i + 1;
	}
	random_shuffle(&lottonumerot[0], &lottonumerot[LOTTONUMEROT]); // arvotaan numeroiden järjestys

	for (int i = 0; i < LOTTORIVI_KOKO; i++) { // otetaan ensimmäiset 7 alkiota ja tallennetaan ne lottorivin taulukkoon
		oikea_rivi[i] = lottonumerot[i];
	}
	bubble_sort(oikea_rivi, LOTTORIVI_KOKO); // järjestetään alkiot nousevaan järjestykseen

	oikea_lisrivi[0] = lottonumerot[20]; // 1. lisänumero = 20. alkio
	oikea_lisrivi[1] = lottonumerot[30]; // 2. lisänumero = 30. alkio
	bubble_sort(oikea_lisrivi, LISANUMEROT_KOKO); // järjestetään alkiot nousevaan järjestykseen
}
//
void kysy_lottorivi(short taul[], short rivi_size) {
	for (int i = 0; i < rivi_size; i++) {
		do {
			int x = 0;
			bool ex = false;
			cout << "Anna " << i + 1 << ". numero: ";
			cin >> taul[i];
			clearInput();
			if (taul[i] < 1 || taul[i] > LOTTONUMEROT) {
				cout << "Virhe! ";
			}
			while (x < i) {
				if (taul[i] == taul[x]) {
					taul[i] = -1;
					cout << "Numero loytyy jo! ";
				}
				x++;
			}
		} while (taul[i] < 1 || taul[i] > LOTTONUMEROT);
	}
}
//
void oikean_lottorivin_arvonta() {
	// Oikean lottorivin arvonta
	short oikea_lottorivi[LOTTORIVI_KOKO];
	short oikea_lottorivi_lisanumerot[LISANUMEROT_KOKO];
	// Arvotaan oikea lottorivi
	arvo_lottorivi(oikea_lottorivi, oikea_lottorivi_lisanumerot);
	// Tulostus
	cout << endl << "Lottonumerot: ";
	for (int i = 0; i < LOTTORIVI_KOKO; i++) {
		cout << oikea_lottorivi[i] << " ";
	}
	cout << endl << " Lisanumerot: ";
	cout << oikea_lottorivi_lisanumerot[0] << " " << oikea_lottorivi_lisanumerot[1] << endl << endl;
}
//
void yhden_rivin_lotto() {
	// Yhden rivin lotto
	short tulos = 0;
	short tulos_lis = 0;
	short oikea_rivi[LOTTORIVI_KOKO];
	short oikea_lisrivi[LISANUMEROT_KOKO];
	short user_rivi[LOTTORIVI_KOKO];
	// Arvottu lottorivi
	cout << endl << "Anna arvottu lottorivi:" << endl;
	kysy_lottorivi(oikea_rivi, LOTTORIVI_KOKO);
	bubble_sort(oikea_rivi, LOTTORIVI_KOKO);
	// Lisänumerot
	cout << endl << "Anna arvotut lisanumerot:" << endl;
	for (int i = 0; i < LISANUMEROT_KOKO; i++) {
		do {
			int x = 0;
			int y = 0;
			bool ex = false;
			cout << "Anna " << i + 1 << ". numero: ";
			cin >> oikea_lisrivi[i];
			clearInput();
			if (oikea_lisrivi[i] < 1 || oikea_lisrivi[i] > LOTTONUMEROT) {
				cout << "Virhe! ";
			}
			while (x < i) {
				if (oikea_lisrivi[i] == oikea_lisrivi[x]) {
					oikea_lisrivi[i] = -1;
					cout << "Numero loytyy jo! ";
				}
				x++;
			}
			while (y < LOTTORIVI_KOKO) {
				if (oikea_lisrivi[i] == oikea_rivi[y]) {
					oikea_lisrivi[i] = -1;
					cout << "Numero loytyy jo! ";
				}
				y++;
			}
		} while (oikea_lisrivi[i] < 1 || oikea_lisrivi[i] > LOTTONUMEROT);
	}
	bubble_sort(oikea_lisrivi, LISANUMEROT_KOKO);
	// Oma rivi
	cout << endl << "Anna oma rivi:" << endl;
	kysy_lottorivi(user_rivi, LOTTORIVI_KOKO);
	bubble_sort(user_rivi, LOTTORIVI_KOKO);
	// Pisteiden laskenta
	laske_pisteet(tulos, tulos_lis, oikea_rivi, oikea_lisrivi, user_rivi);
	// Tulostukset
	cout << endl << "Oikea lottorivi: ";
	for (int i = 0; i < LOTTORIVI_KOKO; i++) {
		if (i == LOTTORIVI_KOKO - 1) {
			cout << oikea_rivi[i];
		}
		else {
			cout << oikea_rivi[i] << " ";
		}
	}
	cout << ", lisanumerot: ";
	for (int i = 0; i < LISANUMEROT_KOKO; i++) {
		cout << oikea_lisrivi[i] << " ";
	}
	cout << endl << "Sinun lottorivi: ";
	for (int i = 0; i < LOTTORIVI_KOKO; i++) {
		cout << user_rivi[i] << " ";
	}
	cout << endl;
	// Pisteet
	tulosta_pisteet(tulos, tulos_lis);
}
//
void yhden_rivin_lotto_arvotulla_tuloksella() {
	// Yhden rivin lotto arvotulla tuloksella
	short tulos = 0;
	short tulos_lis = 0;
	short oikea_rivi[LOTTORIVI_KOKO];
	short oikea_lisrivi[LISANUMEROT_KOKO];
	short user_rivi[LOTTORIVI_KOKO];
	// Arvotaan oikea lottorivi
	arvo_lottorivi(oikea_rivi, oikea_lisrivi);
	cout << endl << "Lottorivi arvottu lisanumeroineen." << endl;
	// Anna oma rivi
	cout << endl << "Anna oma rivi: " << endl;
	kysy_lottorivi(user_rivi, LOTTORIVI_KOKO);
	bubble_sort(user_rivi, LOTTORIVI_KOKO);
	// Tulos
	cout << endl << "Tulos:" << endl;
	cout << "Sinun lottorivisi: ";
	for (int i = 0; i < LOTTORIVI_KOKO; i++) {
		cout << user_rivi[i] << " ";
	}
	cout << endl << "Arvottu lottorivi: ";
	for (int i = 0; i < LOTTORIVI_KOKO; i++) {
		if (i == LOTTORIVI_KOKO - 1) {
			cout << oikea_rivi[i];
		}
		else {
			cout << oikea_rivi[i] << " ";
		}
	}
	cout << ", lisanumerot: ";
	for (int i = 0; i < LISANUMEROT_KOKO; i++) {
		cout << oikea_lisrivi[i] << " ";
	}
	// Pisteiden laskenta
	laske_pisteet(tulos, tulos_lis, oikea_rivi, oikea_lisrivi, user_rivi);
	cout << endl;
	// Pisteet / voittoluokka
	tulosta_pisteet(tulos, tulos_lis);
}
//
void useamman_rivin_lotto_arvotulla_tuloksella() {
	// Useamman rivin lotto arvotulla tuloksella
	short rivi = 0;
	short tulos = 0;
	short tulos_lis = 0;
	short oikea_rivi[LOTTORIVI_KOKO];
	short oikea_lisrivi[LISANUMEROT_KOKO];
	short user_temp[LOTTORIVI_KOKO];
	short user_rivi[MAX_RIVIT][LOTTORIVI_KOKO];
	bool uusi_rivi = true;
	// Arvotaan oikea lottorivi
	arvo_lottorivi(oikea_rivi, oikea_lisrivi);
	cout << endl << "Lottorivi arvottu lisanumeroineen." << endl;
	// Käyttäjän syöttämät arvot
	while (rivi < MAX_RIVIT && uusi_rivi) {
		cout << endl << "Anna oma " << rivi+1 << ". rivi: " << endl;
		kysy_lottorivi(user_temp, LOTTORIVI_KOKO);
		bubble_sort(user_temp, LOTTORIVI_KOKO);
		for (int i = 0; i < LOTTORIVI_KOKO; i++) {
			user_rivi[rivi][i] = user_temp[i];
		}
		int c;
		if (rivi < MAX_RIVIT - 1) {
			cout << endl << "0 = ei, jokin muu = kylla" << endl;
			cout << "Uusi rivi? ";
			cin >> c;
			clearInput();
			if (c == 0) {
				uusi_rivi = false;
			}
		}
		rivi++;
	} // end of while
	// Tulokset
	cout << endl << "Tulos:" << endl;
	cout << "Arvottu lottorivi: ";
	for (int i = 0; i < LOTTORIVI_KOKO; i++) {
		if (i == LOTTORIVI_KOKO - 1) {
			cout << oikea_rivi[i];
		}
		else {
			cout << oikea_rivi[i] << " ";
		}
	}
	cout << ", lisanumerot: ";
	for (int i = 0; i < LISANUMEROT_KOKO; i++) {
		cout << oikea_lisrivi[i] << " ";
	}
	//
	cout << endl << endl;
	// Yhteenveto
	for (int i = 0; i < rivi; i++) {
		// Pisteiden laskenta
		tulos = 0;
		tulos_lis = 0;
		for (int z = 0; z < LOTTORIVI_KOKO; z++) {
			int x = 0;
			int y = 0;
			while (x < LOTTORIVI_KOKO) {
				if (oikea_rivi[z] == user_rivi[i][x]) {
					tulos++;
				}
				x++;
			}
			while (y < LISANUMEROT_KOKO) { // Tarkistetaan löytyykö numero lisänumeroista
				if (oikea_lisrivi[y] == user_rivi[i][z]) {
					tulos_lis++;
				}
				y++;
			}
		}
		cout << i+1 << ". kayttajan rivi: ";
		for (int x = 0; x < LOTTORIVI_KOKO; x++) {
			cout << user_rivi[i][x] << " ";
		}
		tulosta_pisteet(tulos, tulos_lis);
	}
}
//
void yhden_rivin_jokeri() {
	// Yhden rivin jokeri
	short pisteet = 0;
	short oikea_jokeri[JOKERI_KOKO];
	short user_jokeri[JOKERI_KOKO];
	// Arvotaan jokeririvi
	for (int i = 0; i < JOKERI_KOKO; i++) {
		oikea_jokeri[i] = rand() % 10;
	}
	// Ilmoitus
	cout << endl << "Jokeririvi arvottu." << endl << endl;
	// Kysytään käyttäjän riviä
	cout << "Anna oma jokeririvi:" << endl;
	kysy_jokeririvi(user_jokeri, JOKERI_KOKO);
	// Tulokset ja tulostukset
	cout << endl << "Tulos:" << endl;
	cout << "Sinun jokeririvi: \t";
	for (int i = 0; i < JOKERI_KOKO; i++) {
		cout << user_jokeri[i] << " ";
		if (user_jokeri[i] == oikea_jokeri[i]) {
			pisteet++;
		}
	}
	cout << endl << "Arvottu jokeririvi: \t";
	for (int i = 0; i < JOKERI_KOKO; i++) {
		cout << oikea_jokeri[i] << " ";
	}
	// Lopputulos
	cout << endl << endl << pisteet << " oikein.";
	if (pisteet < 2) {
		cout << " Ei voittoa." << endl << endl;
	}
	else {
		cout << " Voitit!" << endl << endl;
	}
}
//
void kysy_jokeririvi(short taul[], short rivi_size) {
	for (int i = 0; i < rivi_size; i++) {
		do {
			cout << "Anna " << i + 1 << ". numero: ";
			cin >> taul[i];
			clearInput();
			if (taul[i] < 0 || taul[i] > 9) {
				cout << "Virhe! ";
			}
		} while (taul[i] < 0 || taul[i] > 9);
	}
}
//
void laske_pisteet(short& pts, short& pts_l, short oikea[], short oikea_l[], short user[]) {
	// Laske pisteet
	for (int i = 0; i < LOTTORIVI_KOKO; i++) {
		int x = 0;
		int y = 0;
		while (x < LOTTORIVI_KOKO) {
			if (oikea[i] == user[x]) {
				pts++;
			}
			x++;
		}
		while (y < LISANUMEROT_KOKO) { // Tarkistetaan löytyykö numero lisänumeroista
			if (oikea_l[y] == user[i]) {
				pts_l++;
			}
			y++;
		}
	}
}
//
void tulosta_pisteet(short pts, short pts_l) {
	// Tulosta pisteet / voittoluokka
	if (pts < 4) {
		cout << endl << "Ei voittoa (" << pts << " + " << pts_l << " oikein)" << endl << endl;
	}
	else if (pts == 6 && pts_l == 1) {
		cout << endl << pts << " + " << pts_l << " oikein" << endl << endl;
	}
	else {
		cout << endl << pts << " oikein" << endl << endl;
	}
}
//
void tulostaValikko(char& valinta) {
	// Tulostetaan valikko
	cout << "Lottopelisimulaattori" << endl;
	cout << "=====================" << endl << endl;
	cout << "Toiminnot:" << endl;
	cout << "1) Oikean lottorivin arvonta" << endl;
	cout << "2) Yhden rivin lotto" << endl;
	cout << "3) Yhden rivin lotto arvotulla tuloksella" << endl;
	cout << "4) Useamman rivin lotto arvotulla tuloksella" << endl;
	cout << "5) Yhden rivin jokeri" << endl;
	cout << "l/L) Lopeta" << endl << endl;
	cout << "Valintasi: ";

	do { // virheellisen syötteen tarkistus
		cin >> valinta;
		clearInput();
		if (valinta != '1' && valinta != '2' && valinta != '3' && valinta != '4' && valinta != '5' && valinta != 'l' && valinta != 'L') {
			cout << "Virhe! Valintasi: ";
		}
	} while (valinta != '1' && valinta != '2' && valinta != '3' && valinta != '4' && valinta != '5' && valinta != 'l' && valinta != 'L');
}
//
void bubble_sort(short a[], int n) {
	// Kuplalajittelualgoritmin ohjelmakoodi (valmiiksi annettu)
	int	j, k;
	int	exchange_made = 1;
	int  temp;

	k = 0;

	while ((k < n - 1) && exchange_made) {
		// If no exchange had been done in the previous round =>
		// all elements are in proper order

		exchange_made = 0;
		++k;

		for (j = 0; j < n - k; ++j) {
			if (a[j] > a[j + 1]) {

				// Exchange must be made 
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				exchange_made = 1;
			}
		}
	}
}
//
void clearInput() {
	// Tarkastetaan syöte ja käsitellään sen sisältö oikeanlaiseksi (poistetaan muuttujaan kuulumaton sisältö)
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}