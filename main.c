#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_AUTOR 10
#define MAX_LIBRA_PER_AUTOR 5
#define MAX_LIBRA 20

struct libri {
    int id;
    int faqe;
    char isbn[13];
    char titulli[20];
} librat[MAX_LIBRA];

struct autori {
    int id;
    char emri[20];
    char mbiemri[20];
    struct libri librat[MAX_LIBRA_PER_AUTOR];
    int nr_librave;
} autoret[MAX_AUTOR];

int nr_librave = 0;
int nr_autoreve = 0;

int nr_librave_isbn_shkronje(struct libri librat[]) {
    int i;
    int counter = 0;
    for (i = 0; i < nr_librave; i++) {
        if (isalpha(librat[i].isbn[0]) && islower(librat[i].isbn[0])) {
            counter++;
        }
    }
    return counter;
}

int gjej_liber_titull(char titull[]) {
    int i;
    for (i = 0; i < nr_librave; i++) {
        if (strcmp(librat[i].titulli, titull) == 0) {
            return i;
        }
    }
    return -1;
}

int gjej_liber_isbn(char isbn[]) {
    int i;
    for (i = 0; i < nr_librave; i++) {
        if (strcmp(librat[i].isbn, isbn) == 0) {
            return i;
        }
    }
    return -1;
}

void shtoAutor() {
    if (nr_autoreve == MAX_AUTOR) {
        printf("Nuk mund te shtoni me teper autore.\n");
        return;
    }

    printf("Vendosni emrin e autorit: ");
    scanf("%s", autoret[nr_autoreve].emri);
    printf("Vendosni mbiemrin e autorit: ");
    scanf("%s", autoret[nr_autoreve].mbiemri);

    autoret[nr_autoreve].nr_librave = 0;
    nr_autoreve++;
}

void regjistroLibrin() {
    if (nr_librave == MAX_LIBRA) {
        printf("Nuk mund te shtoni me teper libra.\n");
        return;
    }

    char titull[20];
    printf("Vendosni titullin: ");
    scanf("%s", titull);

    int poz = gjej_liber_titull(titull);
    if (poz != -1) {
        if (autoret[nr_autoreve - 1].nr_librave < MAX_LIBRA_PER_AUTOR) {
            autoret[nr_autoreve - 1].librat[autoret[nr_autoreve - 1].nr_librave] = librat[poz];
            autoret[nr_autoreve - 1].nr_librave++;
        } else {
            printf("Eshte arritur numri maksimal te librave qe mund te regjistroje autori.\n");
        }
    } else {
        printf("Libri me kete titull nuk gjendet.\n");
    }
}

void listoLibratAutorit() {
    char emri[20], mbiemri[20];
    printf("Vendosni emrin dhe mbiemrin e autorit: ");
    scanf("%s %s", emri, mbiemri);

    int i, j;
    for (i = 0; i < nr_autoreve; i++) {
        if (strcmp(autoret[i].emri, emri) == 0 && strcmp(autoret[i].mbiemri, mbiemri) == 0) {
            printf("Librat e autorit %s %s:\n", emri, mbiemri);
            for (j = 0; j < autoret[i].nr_librave; j++) {
                printf("%s\n", autoret[i].librat[j].titulli);
            }
            return;
        }
    }
    printf("Autori nuk gjendet ne sistem.\n");
}

void printMenu() {
    printf("\nMENU:\n");
    printf("1. Shtoni autorin\n");
    printf("2. Regjistroni nje liber per autorin e fundit qe keni shtuar\n");
    printf("3. Listoni librat\n");
    printf("4. Dalje\n");
}

int main() {
    int choice;
    do {
        printMenu();
        printf("\nPerzgjidhni nje opsion: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                shtoAutor();
                break;
            case 2:
                regjistroLibrin();
                break;
            case 3:
                listoLibratAutorit();
                break;
            case 4:
                printf("Dalja nga programi...\n");
                break;
            default:
                printf("Opsioni i zgjedhur nuk ekziston.\n");
        }
    } while (choice != 4);

    return 0;
}
