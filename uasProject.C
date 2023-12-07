#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 10
#define USERNAME_LENGTH 20
#define PASSWORD_LENGTH 30
#define MAX_WEEKS 4
#define MAX_DATA_PER_WEEK 10

struct User {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    int totalBensin;
    int totalUang;
    int weeklyBensin[MAX_WEEKS][MAX_DATA_PER_WEEK];
    int weeksStored;
};

struct User users[MAX_USERS];
int userCount = 0;

// Fungsi
void validateInput(const char *message, char *input, int maxLength);
void userMenu(int userIndex);
void displayUserData(int userIndex);
void displayWeeklyData();
void adminMenu();
int signIn();

// Validasi inputan
void validateInput(const char *message, char *input, int maxLength) {
    printf("%s: ", message);
    fgets(input, maxLength, stdin);
    input[strcspn(input, "\n")] = '\0';
}

// Menu pengguna
void userMenu(int userIndex) {
    int choice;
    do {
        printf("\nMenu Pengguna:\n");
        printf("1. Update Pendapatan\n");
        printf("2. Lihat Data\n");
        printf("3. Kembali\n");

        printf("Pilihan: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1: {
                int week;
                printf("Masukkan minggu yang ingin diupdate: ");
                scanf("%d", &week);
                if (week > MAX_WEEKS || week <= 0) {
                    printf("Data untuk minggu %d belum ada.\n", week);
                    printf("Masukkan pendapatan baru untuk minggu %d: ", week);
                    scanf("%d", &users[userIndex].weeklyBensin[week - 1][0]);
                    printf("Pendapatan untuk minggu %d berhasil diperbarui!\n", week);
                    if (week > users[userIndex].weeksStored) {
                        users[userIndex].weeksStored = week;
                    }
                } else {
                    printf("Data untuk minggu %d sudah ada.\n", week);
                    printf("Pendapatan untuk minggu %d: %d\n", week, users[userIndex].weeklyBensin[week - 1][0]);
                }
                break;
            }
            case 2:
                printf("=== Data Pengguna ===\n");
                displayUserData(userIndex);
                break;
            case 3:
                printf("Kembali ke menu sebelumnya.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
                break;
        }
    } while (choice != 3);
}

// Tampilan untuk pengguna
void displayUserData(int userIndex) {
    printf("Data Pengguna %s:\n", users[userIndex].username);
    for (int i = 0; i < users[userIndex].weeksStored; i++) {
        printf("Minggu %d:\n", i + 1);
        printf("Pendapatan: %d\n", users[userIndex].weeklyBensin[i][0]);
    }
}

// Tampilan untuk mingguan pengguna
void displayWeeklyData() {
    printf("Data Mingguan Pengguna:\n");
    for (int i = 0; i < userCount; i++) {
        printf("Data Pengguna %s:\n", users[i].username);
        printf("Total Pendapatan: %d\n", users[i].totalBensin);
        printf("\n");
    }
}

// Menu admin
void adminMenu() {
    int choice;
    do {
        printf("\nMenu Admin:\n");
        printf("1. Lihat Data Mingguan Pengguna\n");
        printf("2. Update Isi Tangki Bensin\n");
        printf("3. Kembali\n");

        printf("Pilihan: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                printf("=== Data Mingguan Pengguna ===\n");
                displayWeeklyData();
                break;
            case 2:
                printf("Implement adminUpdateBensin()\n");
                break;
            case 3:
                printf("Kembali ke menu sebelumnya.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
                break;
        }
    } while (choice != 3);
}
// Login
int signIn() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];

    validateInput("Masukkan username", username, USERNAME_LENGTH);
    validateInput("Masukkan password", password, PASSWORD_LENGTH);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Welcome admin\n");
        adminMenu();
        printf("Tekan Enter untuk melanjutkan...");
        getchar();
        return 1;
    }

    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Login berhasil!\n\n");
            userMenu(i);
            return i;
        }
    }
    printf("Username atau password salah!\n\n");
    system("cls");
    printf("Tekan Enter untuk melanjutkan...");
    getchar();
    return -1;
}

// Main
int main() {
    strcpy(users[0].username, "user1");
    strcpy(users[0].password, "pass1");
    users[0].totalBensin = 0;
    users[0].totalUang = 0;
    users[0].weeksStored = 0;

    strcpy(users[1].username, "user2");
    strcpy(users[1].password, "pass2");
    users[1].totalBensin = 0;
    users[1].totalUang = 0;
    users[1].weeksStored = 0;

    strcpy(users[2].username, "user3");
    strcpy(users[2].password, "pass3");
    users[2].totalBensin = 0;
    users[2].totalUang = 0;
    users[2].weeksStored = 0;

    userCount = 3;

    int choice;
    int userIndex;

    do {
        printf("Menu:\n");
        printf("1. Sign In\n");
        printf("2. Exit\n");

        printf("Pilihan: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                userIndex = signIn();
                break;
            case 2:
                exit(0);
                break;
            default:
                printf("Mohon pilih angka yang sesuai dengan menu!\n\n");
                break;
        }
    } while (choice != 2);
    system("cls");

    return 0;
}
