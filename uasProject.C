#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 10
#define USERNAME_LENGTH 20
#define PASSWORD_LENGTH 30

void menuAdmin(struct Akun adminUser, struct Akun users[]) {
    int adminChoice;
    while (1) {
        printf("=== Admin Menu ===\n");
        printf("1. Mengisi Ulang Stok Bensin\n");
        printf("2. Melihat Seluruh Data\n");
        printf("3. Menampilkan Daftar Pengguna\n");
        printf("4. Kembali ke Menu Utama\n");
        printf("==================\n");
        printf("Pilih opsi (1-4): ");
        scanf("%d", &adminChoice);

        switch (adminChoice) {
            case 1:
                clearScreen();
                viewUserList();
                int userChoice;
                printf("Pilih pengguna (1-%d): ", userCount - 1);
                scanf("%d", &userChoice);
                if (userChoice >= 1 && userChoice < userCount) {
                    refillFuelStockUser(&users[userChoice]);
                } else {
                    printf("Pilihan pengguna tidak valid.\n");
                }
                break;
            case 2:
                clearScreen();
                viewAllData(adminUser);
                break;
            case 3:
                clearScreen();
                viewUserList();
                break;
            case 4:
                printf("Kembali ke Menu Utama.\n");
                return;
            default:
                printf("Opsi tidak valid. Silakan pilih kembali.\n");
        }
    }
}

int main() {
strcpy(users[0].username, "admin");
strcpy(users[0].password, "adminpass");
strcpy(users[0].role, "admin");

strcpy(users[1].username, "user1");
strcpy(users[1].password, "pass1");
users[1].chosenFuelType = PERTALITE;

strcpy(users[2].username, "user2");
strcpy(users[2].password, "pass2");
users[2].chosenFuelType = PERTAMAX;

strcpy(users[3].username, "user3");
strcpy(users[3].password, "pass3");
users[3].chosenFuelType = SOLAR;

  userCount = 4;
  int userIndex;
  int choice;

  do {
    printf("Menu:\n");
    printf("1. Sign In\n");
    printf("2. Exit\n");

    printf("Pilihan: ");
    scanf("%d", &choice);
    while (getchar() != '\n')
      ;

    switch (choice) {
    case 1:
      userIndex = signIn();
      if (userIndex != -1) {
        if (strcmp(users[userIndex].role, "admin") == 0) {
          menuAdmin(users[userIndex], users);
        } else {
          // Menu untuk user biasa
        if (users[userIndex].chosenFuelType == PERTALITE) {
    dataBensin(&users[userIndex], literPertalite, HARGA_PERTALITE, stokPertalite, "Pertalite");
} else if (users[userIndex].chosenFuelType == PERTAMAX) {
    dataBensin(&users[userIndex], literPertamax, HARGA_PERTAMAX, stokPertamax, "Pertamax");
} else if (users[userIndex].chosenFuelType == SOLAR) {
    dataBensin(&users[userIndex], literSolar, HARGA_SOLAR, stokSolar, "Solar");
} else {
    printf("Jenis bensin tidak valid.\n");
}

        }
      }
      break;
    }
  } while (1);

  return 0;
}
