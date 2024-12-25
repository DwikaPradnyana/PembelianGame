#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Struktur Data untuk Linked List
struct game {
    int id;
    char nama[100];
    char genre[100];
    int harga;
    struct game *left, *right;
};

// Struktur Data untuk Queue
struct pembeli {
    char namaPembeli[100];
    char namaGame[100];
    struct pembeli* next;
};

struct Qnode {
    struct pembeli *front, *rear;
};

// Struktur Data untuk Stack
struct stackNode {
    char nama[100];
    char game[100];
    struct stackNode* next;
};

// Struktur Data untuk Tree (BST)
struct game* createGameNode(int id, char nama[], char genre[], int harga) {
    struct game* newNode = (struct game*)malloc(sizeof(struct game));
    newNode->id = id;
    strcpy(newNode->nama, nama);
    strcpy(newNode->genre, genre);
    newNode->harga = harga;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct game* tambahGame(struct game* root, int id, char nama[], char genre[], int harga) {
    if (root == NULL) {
        return createGameNode(id, nama, genre, harga);
    }

    if (strcmp(nama, root->nama) < 0)
        root->left = tambahGame(root->left, id, nama, genre, harga);
    else if (strcmp(nama, root->nama) > 0)
        root->right = tambahGame(root->right, id, nama, genre, harga);

    return root;
}

void tampilkanGame(struct game* root) {
    if (root != NULL) {
        tampilkanGame(root->left);
        if (strlen(root->nama) > 0) {
            printf("\t\t ============================================\n");
            printf("\t\t | ID     : %-31d|\n", root->id);
            printf("\t\t | Nama   : %-31s|\n", root->nama);
            printf("\t\t | Genre  : %-31s|\n", root->genre);
            printf("\t\t | Harga  : Rp.%-30d|\n", root->harga);
            printf("\t\t ============================================\n");
        }
        tampilkanGame(root->right);
    }
}


struct game* minValueNode(struct game* node) {
    struct game* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct game* hapusGame(struct game* root, char nama[]) {
    if (root == NULL)
        return root;

    if (strcmp(nama, root->nama) < 0)
        root->left = hapusGame(root->left, nama);
    else if (strcmp(nama, root->nama) > 0)
        root->right = hapusGame(root->right, nama);
    else {
        if (root->left == NULL) {
            struct game* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct game* temp = root->left;
            free(root);
            return temp;
        }

        struct game* temp = minValueNode(root->right);
        root->id = temp->id;
        strcpy(root->nama, temp->nama);
        strcpy(root->genre, temp->genre);
        root->harga = temp->harga;
        root->right = hapusGame(root->right, temp->nama);
    }
    return root;
}

struct game* cariGame(struct game* root, char nama[]) {
    if (root == NULL || strcmp(nama, root->nama) == 0)
        return root;

    if (strcmp(nama, root->nama) < 0)
        return cariGame(root->left, nama);

    return cariGame(root->right, nama);
}

// Fungsi untuk Queue
struct Qnode* createQueue() {
    struct Qnode* antrian = (struct Qnode*)malloc(sizeof(struct Qnode));
    antrian->front = antrian->rear = NULL;
    return antrian;
}

struct pembeli* pembeliBaru(char namaPembeli[], char namaGame[]) {
    struct pembeli* temp = (struct pembeli*)malloc(sizeof(struct pembeli));
    strcpy(temp->namaPembeli, namaPembeli);
    strcpy(temp->namaGame, namaGame);
    temp->next = NULL;
    return temp;
}

void enqueue(struct Qnode* antrian, char namaPembeli[], char namaGame[]) {
    struct pembeli* temp = pembeliBaru(namaPembeli, namaGame);
    if (antrian->rear == NULL) {
        antrian->front = antrian->rear = temp;
        return;
    }
    antrian->rear->next = temp;
    antrian->rear = temp;
}

void dequeue(struct Qnode* antrian) {
    if (antrian->front == NULL)
        return;
    struct pembeli* temp = antrian->front;
    antrian->front = antrian->front->next;
    if (antrian->front == NULL)
        antrian->rear = NULL;
    free(temp);
    printf("\t\t ===============================================\n");
    printf("\t\t |          Pembeli Berhasil dequeue !!!       |\n");
    printf("\t\t ===============================================\n");

}

// Fungsi untuk menghapus antrian pembeli berdasarkan nama
void cancleorder(struct Qnode** antrian, char target[]) {
    struct pembeli* temp = (*antrian)->front;
    struct pembeli* prev = NULL;

    // Jika antrian kosong
    if (temp == NULL) {
        printf("\t\t ======================================\n");
        printf("\t\t |  Antrian kosong!                   |\n");
        printf("\t\t ======================================\n");
        return;
    }

    // Jika nama pembeli berada di front
    if (strcmp(temp->namaPembeli, target) == 0) {
        (*antrian)->front = temp->next;
        printf("\t\t ======================================\n");
        printf("\t\t |  Nama pembeli %s berhasil dihapus. |\n", target);
        printf("\t\t ======================================\n");
        free(temp);
        return;
    }

    // Traverse list untuk mencari pembeli
    while (temp != NULL && strcmp(temp->namaPembeli, target) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // Jika pembeli tidak ditemukan
    if (temp == NULL) {
        printf("\t\t ======================================\n");
        printf("\t\t |  Nama pembeli %s tidak ditemukan.  |\n", target);
        printf("\t\t ======================================\n");
        return;
    }

    // Menghapus pembeli
    prev->next = temp->next;
    printf("\t\t ======================================\n");
    printf("\t\t |  Nama pembeli %s berhasil dihapus. |\n", target);
    printf("\t\t ======================================\n");
    free(temp);
}

void printTableHeader() {
    printf("+-----+------------------------+------------------------+--------------+\n");
    printf("| ID  | Nama                   | Genre                  | Harga        |\n");
    printf("+-----+------------------------+------------------------+--------------+\n");
}

void printTableFooter() {
    printf("+-----+------------------------+------------------------+--------------+\n");
}

void printTableRow(struct game* game) {
    printf("| %-3d | %-22s | %-22s | Rp.%-9d |\n", game->id, game->nama, game->genre, game->harga);
}

void tampilkanAntrian(struct Qnode* antrian) {
    struct pembeli* temp = antrian->front;
    if (temp == NULL) {
        printf("\t\t ===============================================\n");
        printf("\t\t |                Antrian Kosong !!!           |\n");
        printf("\t\t ===============================================\n");
        return;
    }

    printf("\t\t ===============================================\n");
    printf("\t\t |              ANTRIAN PEMBELIAN              |\n");
    printf("\t\t ===============================================\n");

    int counter = 1;
    while (temp != NULL) {
        printf("\t\t | Nomor Antrian: %-28d|\n", counter);
        printf("\t\t | Nama Pembeli : %-28s|\n", temp->namaPembeli);
        printf("\t\t | Nama Game    : %-28s|\n", temp->namaGame);
        printf("\t\t ============================================\n");
        temp = temp->next;
        counter++;
    }
}


// Fungsi untuk Stack
struct stackNode* createStack(char nama[], char game[]) {
    struct stackNode* newNode = (struct stackNode*)malloc(sizeof(struct stackNode));
    strcpy(newNode->nama, nama);
    strcpy(newNode->game, game);
    newNode->next = NULL;
    return newNode;
}

void push(struct stackNode** top, char nama[], char game[]) {
    struct stackNode* newNode = createStack(nama, game);
    newNode->next = *top;
    *top = newNode;
}

void printStack(struct stackNode* top) {
    printf("\t\t ============================================\n");
    printf("\t\t |          DAFTAR GAME YANG DIHAPUS         |\n");
    printf("\t\t ============================================\n");
    
    if (top == NULL) {
        printf("\t\t ============================================\n");
        printf("\t\t |  Tidak ada game yang dihapus.            |\n");
        printf("\t\t ============================================\n");
    } else {
        while (top != NULL) {
            printf("\t\t | Genre Game : %-31s|\n", top->game);
            printf("\t\t | Nama Game  : %-31s|\n", top->nama);
            printf("\t\t ============================================\n");
            top = top->next;
        }
    }
}



// Fungsi untuk Sorting Game
void sortGames(struct game* games[], int n, int (*compare)(struct game*, struct game*)) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (compare(games[j], games[j+1]) > 0) {
                struct game* temp = games[j];
                games[j] = games[j+1];
                games[j+1] = temp;
            }
        }
    }
}

int compareByName(struct game* a, struct game* b) {
    return strcmp(a->nama, b->nama);
}

int compareByGenre(struct game* a, struct game* b) {
    return strcmp(a->genre, b->genre);
}

int compareByPrice(struct game* a, struct game* b) {
    return a->harga - b->harga;
}

void fillGameArray(struct game* root, struct game* games[], int* index) {
    if (root != NULL) {
        fillGameArray(root->left, games, index);
        games[(*index)++] = root;
        fillGameArray(root->right, games, index);
    }
}

void tampilkanGameSorted(struct game* root, int (*compare)(struct game*, struct game*)) {
    int n = 0;
    struct game* games[100];  // Assuming max 100 games
    fillGameArray(root, games, &n);
    sortGames(games, n, compare);
    printTableHeader();
    for (int i = 0; i < n; i++) {
        printTableRow(games[i]);
    }
    printTableFooter();
}

int main() {
    struct Qnode* listPembeli = createQueue();
    struct game* listGame = NULL;
    struct stackNode* gameDihapus = NULL;
    int id = 5;
    
    char namaPembeli[100];
    char namaGame[100];
    // Menambahkan game langsung di dalam kode
    listGame = tambahGame(listGame, 1, "Game A", "Action", 50000);
    listGame = tambahGame(listGame, 2, "Game B", "Adventure", 70000);
    listGame = tambahGame(listGame, 3, "Game C", "Simulation", 65000);
    listGame = tambahGame(listGame, 4, "Game D", "RPG", 55000);
    listGame = tambahGame(listGame, 5, "Game E", "Strategy", 90000);

    int pilihan;
    do {
        system("cls");
        printf("\t\t ===============================================\n");
        printf("\t\t |                MENU PROGRAM                  |\n");
        printf("\t\t ===============================================\n");
        printf("\t\t |  1. Tambah Game                             |\n");
        printf("\t\t |  2. Tampilkan Daftar Game                   |\n");
        printf("\t\t |  3. Tambahkan Pembeli                       |\n");
        printf("\t\t |  4. Tampilkan Antrian Pembeli               |\n");
        printf("\t\t |  5. Hapus Game                              |\n");
        printf("\t\t |  6. Cari Game                               |\n");
        printf("\t\t |  7. Tampilkan Game yang Dihapus             |\n");
        printf("\t\t |  8. Sorting game                            |\n");
        printf("\t\t |  9. Exit                                    |\n");
        printf("\t\t |=============================================|\n");
        printf("\t\t | Masukkan pilihan:                           |\n");
        printf("\t\t ==============================================\n");

        printf("\033[14;40H");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: {
                system("cls");
                id++;
                char nama[100];
                char genre[100];
                int harga;
                printf("\t\t ========== TAMBAH GAME ==========\n");
                printf("\t\t Masukkan Nama Game: ");
                fflush(stdin); scanf(" %[^\n]s", nama);
                printf("\t\t Masukkan Genre Game: ");
                fflush(stdin); scanf(" %[^\n]s", genre);
                printf("\t\t Masukkan Harga Game: ");
                fflush(stdin); scanf("%d", &harga);
                printf("\t\t =================================\n");

                listGame = tambahGame(listGame, id, nama, genre, harga);
                printf("\t\t =================================\n");
                printf("\t\t Game berhasil ditambahkan!\n");
                printf("\t\t =================================\n");
                getch();
                break;
            }
            case 2: {
                system("cls");
                printf("\t\t ========== DAFTAR GAME ==========\n");
                tampilkanGame(listGame);
                getch();
                break;
            }
            case 3: {
                system("cls");
                printf("\t\t ========== DAFTAR GAME ==========\n");
                tampilkanGame(listGame);
                printf("\t\t ===============================================\n");
                printf("\t\t |                 TAMBAH PEMBELI               |\n");
                printf("\t\t ===============================================\n");
                printf("\t\t  Masukkan Nama Pembeli: ");
                scanf(" %[^\n]s", namaPembeli);
                fflush(stdin);
                printf("\t\t  Masukkan Nama Game: ");
                scanf(" %[^\n]s", namaGame);
                fflush(stdin);
                printf("\t\t ===============================================\n");
                printf("\t\t | Pembeli berhasil ditambahkan!               |\n");
                printf("\t\t ===============================================\n");

                // Add to queue
                enqueue(listPembeli, namaPembeli, namaGame);
                getch();
                break;
            }
            case 4: {
            system("cls");
            printf("\t\t ===============================================\n");
            printf("\t\t |            LIHAT ANTRIAN PEMBELI            |\n");
            printf("\t\t ===============================================\n");
            printf("\t\t |  1. Tampilkan Antrian                       |\n");
            printf("\t\t |  2. Dequeue Antrian Pembeli                 |\n");
            printf("\t\t |  3. Hapus Antrian Dengan Nama Pembeli       |\n");
            printf("\t\t |=============================================|\n");
            printf("\t\t | Masukkan pilihan:                           |\n");
            printf("\t\t ===============================================\n");

                int choice;
                printf("\033[8;40H");
                scanf("%d", &choice);
                
                switch (choice) {
                    case 1:
                        tampilkanAntrian(listPembeli);
                        printf("\t");
                        system("pause");
                        break;
                    case 2: 
                        dequeue(listPembeli); // Hapus dari queue
                        system("pause");
                        break;
                    case 3: 
                        printf("\t\t ========= CARI Nama Pembeli ===========\n");
                        printf("\t\t Masukkan Nama Pembeli yang ingin dicari: ");
                        fflush(stdin); scanf(" %[^\n]s", namaPembeli);
                        cancleorder(&listPembeli, namaPembeli); // Hapus dengan Nama Pembeli
                        system("pause");
                        break;
                }
                break;
            }
            case 5: {
                system("cls");
                char namaGame[100];
                printf("\t\t ============= HAPUS GAME ===========\n");
                printf("\t\t Masukkan Nama Game yang ingin dihapus: ");
                fflush(stdin); scanf(" %[^\n]s", namaGame);

                struct game* gameDicari = cariGame(listGame, namaGame);
                if (gameDicari != NULL) {
                    push(&gameDihapus, gameDicari->nama, gameDicari->genre);
                    listGame = hapusGame(listGame, namaGame);
                    printf("\t\t Game berhasil dihapus!\n");
                } else {
                    printf("\t\t Game tidak ditemukan!\n");
                }
                getch();
                break;
            }
            case 6: {
                system("cls");
                char namaGame[100];
                printf("\t\t ============ CARI GAME =============\n");
                printf("\t\t Masukkan Nama Game yang ingin dicari: ");
                fflush(stdin); scanf(" %[^\n]s", namaGame);

                struct game* gameDicari = cariGame(listGame, namaGame);
                if (gameDicari != NULL) {
                    printf("\t\t Game ditemukan!\n");
                    printf("\t\t ID: %d\n", gameDicari->id);
                    printf("\t\t Nama: %s\n", gameDicari->nama);
                    printf("\t\t Genre: %s\n", gameDicari->genre);
                    printf("\t\t Harga: Rp.%d\n", gameDicari->harga);
                } else {
                    printf("\t\t Game tidak ditemukan!\n");
                }
                getch();
                break;
            }
            case 7: {
                system("cls");
                printStack(gameDihapus);
                getch();
                break;
            }
            case 8: {
                system("cls");
                printf("\t\t ==========================================\n");
                printf("\t\t |             SORTIR GAME                 |\n");
                printf("\t\t ==========================================\n");
                printf("\t\t |  1. Berdasarkan Nama                    |\n");
                printf("\t\t |  2. Berdasarkan Genre                   |\n");
                printf("\t\t |  3. Berdasarkan Harga                   |\n");
                printf("\t\t ==========================================\n");
                printf("\t\t | Masukkan pilihan:                       |\n");
                printf("\t\t ==========================================\n");

                int sortChoice;
                printf("\033[8;40H");
                scanf("%d", &sortChoice);
                switch (sortChoice) {
                    case 1:
                        tampilkanGameSorted(listGame, compareByName);
                        break;
                    case 2:
                        tampilkanGameSorted(listGame, compareByGenre);
                        break;
                    case 3:
                        tampilkanGameSorted(listGame, compareByPrice);
                        break;
                    default:
                        printf("\t\t Pilihan tidak valid!\n");
                }
                getch();
                break;
            }

            case 9: {
                system("cls");
                printf("\t\t ===========================================\n");
                printf("\t\t Terima kasih telah menggunakan program ini!\n");
                printf("\t\t ===========================================\n");
                break;
            }
            default:
                printf("\t\t Pilihan tidak valid! Silakan coba lagi.\n");
                getch();
                break;
        }
    } while (pilihan != 9);

    return 0;
}
