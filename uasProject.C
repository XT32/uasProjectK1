#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 10
#define USERNAME_LENGTH 20
#define PASSWORD_LENGTH 30

struct User {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    
    int totalBensin;
    int totalUang;
};

struct User users[MAX_USERS];
int userCount = 0;

void validateInput(const char *message, char *input, int maxLength) {
    printf("%s: ", message);
    fgets(input, maxLength, stdin);
    input[strcspn(input, "\n")] = '\0';
}

void adminPage() {
    printf("Daftar User dan Laporan:\n");
    for (int i = 0; i < userCount; i++) {
        printf("User %d:\n", i + 1);
        printf("Username: %s\n", users[i].username);
        printf("Total Bensin Keluar: %d\n", users[i].totalBensin);
        printf("Total Uang Masuk: %d\n", users[i].totalUang);
    }
}

void signUp() {
    if (userCount < MAX_USERS) {
        struct User newUser;

        validateInput("Masukkan username", newUser.username, USERNAME_LENGTH);
        validateInput("Masukkan password", newUser.password, PASSWORD_LENGTH);

        users[userCount] = newUser;
        userCount++;

        printf("Sign up berhasil!\n\n");
    } else {
        printf("Maksimum user telah tercapai.\n\n");
    }
}

int signIn() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];

    validateInput("Masukkan username", username, USERNAME_LENGTH);
    validateInput("Masukkan password", password, PASSWORD_LENGTH);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Welcome admin\n");
        adminPage();
        printf("Tekan Enter untuk melanjutkan...");
        getchar();
        return 1;
    }

    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Login berhasil!\n\n");
            return i;
        }
    }

    printf("Username atau password salah!\n\n");
    printf("Tekan Enter untuk melanjutkan...");
    getchar();
    return -1;
}

void updateUser(int userIndex) {
    printf("Masukkan total bensin: ");
    scanf("%d", &users[userIndex].totalBensin);

    printf("Masukkan total uang: ");
    scanf("%d", &users[userIndex].totalUang);

    printf("Data berhasil diperbarui!\n\n");
    printf("Tekan Enter untuk melanjutkan...");
    getchar();
}

int main() {
    int choice;
    int userIndex;

    do {
        printf("Menu:\n");
        printf("1. Sign Up\n");
        printf("2. Sign In\n");
        printf("3. Exit\n");

        printf("Pilihan: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                userIndex = signIn();
                if (userIndex != -1 && userIndex != 1) {
                    updateUser(userIndex);
                }
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("Mohon pilih angka yang sesuai dengan menu!\n\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
