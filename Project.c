#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_KELIME_UZUNLUGU 7
#define MAX_TAHMINLER 100

// Kullanýlabilecek harfler ve kelimeler listesi
const char D[] = {'k', 'a', 'm', 'n', 'e', 'r', 'i'};
const int D_UZUNLUK = sizeof(D) / sizeof(D[0]);
const char kelimeler[][MAX_KELIME_UZUNLUGU] = {
    "anemik", "kameri", "marine", "minare", "makine", "anemi", "mekan", "krema",
    "kerim", "inmek", "imkan", "imren", "imran", "erkan", "ekran", "mera",
    "krem", "mine", "mira", "name", "ekim", "erik", "kim", "nem", "nam",
    "ani", "kin", "kir"
};
const int KELIME_SAYISI = sizeof(kelimeler) / sizeof(kelimeler[0]);

// Harfin kullanýlabilir olup olmadýðýný kontrol eder
bool harf_kullanilabilir(char harf, int harf_sayaci[]) {
	int i;
    for ( i = 0; i < D_UZUNLUK; i++) {
        if (D[i] == harf) {
            if (harf_sayaci[i] > 0) {
                harf_sayaci[i]--;
                return true;
            }
            break;
        }
    }
    return false;
}

// Kelimenin dizi içinde olup olmadýðýný kontrol eder
bool kelime_var_mi(const char* tahmin) {
	int i;
    for ( i = 0; i < KELIME_SAYISI; i++) {
        if (strcmp(kelimeler[i], tahmin) == 0) {
            return true;
        }
    }
    return false;
}

int main() {
	int i;
    char tahmin[MAX_KELIME_UZUNLUGU];
    int toplam_puan = 0;
    char kullanilan_kelime_listesi[MAX_TAHMINLER][MAX_KELIME_UZUNLUGU] = {0};
    int kullanilan_kelime_sayisi = 0;

    printf("Kullanabileceginiz karakterler: ");
    for (i = 0; i < D_UZUNLUK; i++) {
        printf("%c ", D[i]);
    }
    printf("\n");

    while (1) {
        printf("Tahmininizi giriniz: ");
        scanf("%s", tahmin);

        if (strcmp(tahmin, "0") == 0) {
            break;
        }

        int tahmin_uzunluk = strlen(tahmin);
        if (tahmin_uzunluk < 2) {
            printf("Gecersiz uzunlukta kelime, en az iki harfli olmalidir!\n");
            continue;
        }

        int harf_sayaci[D_UZUNLUK];
        for (i = 0; i < D_UZUNLUK; i++) harf_sayaci[i] = 1;

        bool gecerli_harfler = true;
        for (i = 0; i < tahmin_uzunluk; i++) {
            if (!harf_kullanilabilir(tahmin[i], harf_sayaci)) {
                gecerli_harfler = false;
                break;
            }
        }

        if (!gecerli_harfler) {
            printf("Hatali harf kullanimi, Puaniniz: -%d\n", tahmin_uzunluk);
            toplam_puan -= tahmin_uzunluk;
            continue;
        }

        // Ayný kelime daha önce kullanýlmýþ mý kontrolü
        bool tekrar_tahmin = false;
        for (i = 0; i < kullanilan_kelime_sayisi; i++) {
            if (strcmp(kullanilan_kelime_listesi[i], tahmin) == 0) {
                tekrar_tahmin = true;
                break;
            }
        }

        if (tekrar_tahmin) {
            printf("Kelime zaten tahmin edildi, Puaniniz: -%d\n", tahmin_uzunluk);
            toplam_puan -= tahmin_uzunluk;
            continue;
        }

        // Tahmini kaydet
        strcpy(kullanilan_kelime_listesi[kullanilan_kelime_sayisi++], tahmin);

        if (kelime_var_mi(tahmin)) {
            printf("Puaniniz: %d\n", tahmin_uzunluk);
            toplam_puan += tahmin_uzunluk;
        } else {
            printf("Gecersiz kelime, Puaniniz: -%d\n", tahmin_uzunluk);
            toplam_puan -= tahmin_uzunluk;
        }
    }

    printf("Oyun bitmistir. Tebrikler! Toplam puaniniz: %d\n", toplam_puan);

    return 0;
}

