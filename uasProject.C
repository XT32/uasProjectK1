#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_USERS 4
#define USERNAME_LENGTH 20
#define PASSWORD_LENGTH 20
#define PERTALITE 1
#define PERTAMAX 2
#define SOLAR 3
#define HARGA_PERTALITE 10000
#define HARGA_PERTAMAX 15000
#define HARGA_SOLAR 7000
struct Akun 
{
  char username[USERNAME_LENGTH];
  char password[PASSWORD_LENGTH];
  char role[10];
  int jenisUser;      // Untuk menyimpan jenis user pada menu user
  int chosenFuelType; // 1 for Pertalite, 2 for Pertamax, 3 for Solar
  float stokBensin;    // Added field to store fuel stock
};

struct Akun users[MAX_USERS];
int userCount = 0; // Inisialisasi jumlah pengguna

float mingguanPendapatan[4] = {0.0};
float literPertalite[28] = {0.0};
float literPertamax[28] = {0.0}; // Tambahkan array untuk Pertamax
float literSolar[28] = {0.0};    // Tambahkan array untuk Solar
float stokPertalite[4] = {0.0};  // Tambahkan array untuk stok Pertalite
float stokPertamax[4] = {0.0};   // Tambahkan array untuk stok Pertamax
float stokSolar[4] = {0.0};      // Tambahkan array untuk stok Solar

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

int findUserIndex(const char *username) {
  for (int i = 0; i < MAX_USERS; ++i) {
    if (strcmp(users[i].username, username) == 0) {
      return i;
    }
  }
  return -1; // User not found
}

void displayBensin(struct Akun *user, float *literBensin, float hargaBensin, const char *jenisBensin, float *stokBensin);
void dataBensin(struct Akun *user, float *literBensin, float hargaBensin, float *stokBensin, const char *jenisBensin);
void refillSingleFuelType(float *literBensin, int userIndex);

void refillFuelStockUser(struct Akun *user) {
    refillFuelStock(user);
}

void refillFuelStock(struct Akun *user) {
  switch (user->chosenFuelType) {
    case PERTALITE:
      refillSingleFuelType(stokPertalite, user - users);
      break;
    case PERTAMAX:
      refillSingleFuelType(stokPertamax, user - users);
      break;
    case SOLAR:
      refillSingleFuelType(stokSolar, user - users);
      break;
    default:
      printf("Jenis bensin tidak valid.\n");
  }
}

void refillSingleFuelType(float *stokBensin, int userIndex) {
    printf("Masukkan jumlah liter bensin yang akan diisi ulang: ");
    float refillAmount;
    scanf("%f", &refillAmount);

    // Update stokBensin array for all weeks
    for (int i = 0; i < 4; ++i) {
        stokBensin[i] += refillAmount;
    }

    printf("Stok bensin berhasil diisi ulang untuk user %d.\n", userIndex);
}

int findEmptyUserSlot() {
  for (int i = 0; i < MAX_USERS; ++i) {
    if (strlen(users[i].username) == 0) {
      return i;
    }
  }
  return -1; // No empty slot found
}

int signIn() {
  char username[USERNAME_LENGTH];
  char password[PASSWORD_LENGTH];

  printf("=== Sign In ===\n");
  printf("Username: ");
  scanf("%s", username);
  printf("Password: ");
  scanf("%s", password);

  for (int i = 0; i < userCount; ++i) {
    if (strcmp(users[i].username, username) == 0 &&
        strcmp(users[i].password, password) == 0) {
      if (strcmp(users[i].role, "admin") == 0) {
        printf("Login berhasil sebagai Admin: %s.\n", username);
        return i; // Mengembalikan indeks pengguna yang berhasil login
      } else {
        printf("Login berhasil sebagai User: %s.\n", username);
        users[i].jenisUser = 1; // Set to 1 when the user signs in
        return i; // Mengembalikan indeks pengguna yang berhasil login
      }
    }
  }

  printf("Sign in gagal. Username atau password salah.\n");
  return -1; // Mengembalikan -1 jika login gagal
}

int handleSignInFailure(struct Akun users[], int userCount) {
  char username[USERNAME_LENGTH];
  char password[PASSWORD_LENGTH];

  printf("Sign in gagal. Username atau password salah.\n");
  int choice;
  printf("1. Kembali ke menu utama\n");
  printf("Pilih opsi (1): ");
  scanf("%d", &choice);

  if (choice != 1) {
    printf("Pilihan tidak valid.\n");
    return -1; // Kembalikan -1 jika pilihan tidak valid
  }

  printf("Masukkan username: ");
  scanf("%s", username);
  printf("Masukkan password: ");
  scanf("%s", password);

  for (int i = 0; i < userCount; ++i) {
    if (strcmp(users[i].username, username) == 0 &&
        strcmp(users[i].password, password) == 0) {
      printf("Login berhasil sebagai %s.\n", username);
      return i; // Kembalikan indeks pengguna yang berhasil login
    }
  }

  printf("Username atau password salah.\n");
  return -1; // Kembalikan -1 jika login gagal
}
void dataBensin(struct Akun *user, float *literBensin, float hargaBensin, float *stokBensin, const char *jenisBensin){
  int continueInput = 1;
  int hari;
  float harianPendapatan[28] = {0.0}; // 4 minggu x 7 hari
  float totalLiterTerjual = 0.0;

  while (1) {
    int minggu;
    float pendapatanMingguan = 0.0;

    printf("===== Pilih Ingin Memasukkan Penghasilan Minggu Ke Berapa:  =====\n");
    printf("1. Minggu Pertama\n");
    printf("2. Minggu Kedua\n");
    printf("3. Minggu Ketiga\n");
    printf("4. Minggu Keempat\n");
    printf("0. Kembali Ke Menu User\n");
    scanf("%d", &minggu);

    if (minggu == 0) {
      clearScreen();
      break; // Kembali ke menu bensin
    }

    if (minggu < 1 || minggu > 4) {
      printf("Minggu tidak valid. Silakan pilih lagi.\n");
      continue; // Ketika tidak memasukkan minggu yang valid
    }

    printf("\n===== Minggu %d =====\n", minggu);
    clearScreen();

    for (hari = 0; hari < 7; ++hari) {
      printf("\n===== Hari %d =====\n", hari + 1);

      continueInput = 1;

      while (continueInput) {
        float uangBensin;
        printf("Masukkan jumlah uang penjualan Bensin: ");
        scanf("%f", &uangBensin);

        int dataIndex = hari + (minggu - 1) * 7;
        float literTerjual = uangBensin / hargaBensin;

        if (literTerjual > stokBensin[minggu - 1]) {
          printf("Maaf, stok bensin tidak mencukupi untuk jumlah yang dimasukkan.\n");
            sleep(2);
            clearScreen();
          return -1;
        }

        literBensin[dataIndex] += literTerjual;
        harianPendapatan[dataIndex] += uangBensin;
        pendapatanMingguan += uangBensin;
        totalLiterTerjual += literBensin[dataIndex];

        // Display remaining fuel stock
        stokBensin[minggu - 1] -= literTerjual;
        printf("Hari ke - %d\n", hari + 1);
        printf("Jumlah %s yang Terjual: %.2f liter\n", jenisBensin, literBensin[dataIndex]);
        printf("Sisa Stok Bensin: %.2f liter\n", stokBensin[minggu - 1]);
        printf("Jumlah Penjualan Harian: Rp %.2f\n",  literBensin[dataIndex] * hargaBensin);

        printf("Pilih tindakan:\n");
        printf("1. Lanjut\n");
        printf("2. Ganti hari\n");
        printf("0. Kembali ke menu minggu\n");
        scanf("%d", &continueInput);

        if (continueInput == 0 || continueInput == 2) {
          clearScreen();
          break; // Kembali ke menu minggu atau ganti hari
        }
      }

      if (continueInput == 0) {
        break; // Keluar dari dalam menu pemasukkan harian lalu kembali ke menu
               // memilih minggu
      }
    }

    mingguanPendapatan[minggu - 1] += pendapatanMingguan;

    printf("\nTerima kasih, telah melaporkan data Bensin untuk Minggu %d.\n",
           minggu);
    sleep(2);
    clearScreen();
  }
}

void displayBensin(struct Akun *user, float *literBensin, float hargaBensin, const char *jenisBensin, float *stokBensin) {
  printf("Menampilkan Seluruh Data %s untuk User: %s\n", jenisBensin, user->username);

  for (int minggu = 0; minggu < 4; ++minggu) {
    printf("\n===== Minggu %d =====\n", minggu + 1);

    // Inisialisasi total pendapatan mingguan
    float totalPendapatanMingguan = 0.0;
    float totalLiterTerjual = 0.0;
    float sisaStokBensin = 0.0;
    int dataExist = 0; // Flag untuk menandakan apakah ada data penjualan

    for (int hari = 0; hari < 7; ++hari) {
      int dataIndex = hari + minggu * 7;

      // Hanya tampilkan data yang telah diisi oleh pengguna
      if (literBensin[dataIndex] > 0) {
        totalLiterTerjual += literBensin[dataIndex];
        sisaStokBensin = literBensin[dataIndex];
        totalPendapatanMingguan += literBensin[dataIndex] * hargaBensin;

        printf("Hari ke-%d - Jumlah Liter %s yang Terjual: %.2f liter, Jumlah Penjualan Harian: Rp %.2f\n",
               hari + 1, jenisBensin, literBensin[dataIndex], literBensin[dataIndex] * hargaBensin);

        // Tampilkan jumlah liter yang terjual tepat di atas sisa stok bensin
        printf("Sisa Stok Bensin: %.2f liter\n" , *stokBensin);

        dataExist = 1; // Set flag bahwa ada data penjualan
      }
    }

    // Tampilkan pesan jika tidak ada data penjualan untuk minggu tertentu
    if (!dataExist) {
      printf("Tidak ada data penjualan untuk minggu ke-%d.\n", minggu + 1);
    } else {
      printf("Total Liter Terjual minggu ke-%d: %.2f liter\n", minggu + 1, totalLiterTerjual);
      printf("Total Pendapatan minggu ke-%d: Rp %.2f\n", minggu + 1, totalPendapatanMingguan);
    }
  }
}
void viewUserList() {
    printf("=== Daftar Pengguna ===\n");
    for (int i = 1; i < userCount; ++i) {
        printf("%d. %s", i, users[i].username);

        // Check if the user is signed in
        if (users[i].jenisUser == 1) {
            printf(" (Sudah Sign In)");
        } else {
            printf(" (Belum Sign In)");
        }

        // Display the type of fuel the user is managing
        if (users[i].chosenFuelType == PERTALITE) {
            printf(" - Mengelola Pertalite");
        } else if (users[i].chosenFuelType == PERTAMAX) {
            printf(" - Mengelola Pertamax");
        } else if (users[i].chosenFuelType == SOLAR) {
            printf(" - Mengelola Solar");
        }

        printf("\n");
    }
    printf("=======================\n");
}

void viewAllData(struct Akun adminUser) {
  int userChoice;
  printf("=== Melihat Seluruh Data ===\n");
  printf("1. Data User 1\n");
  printf("2. Data User 2\n");
  printf("3. Data User 3\n");
  printf("0. Kembali ke Menu Admin\n");
  printf("Pilih user (1-3): ");
  scanf("%d", &userChoice);

  switch (userChoice) {
  case 1:
    clearScreen();
    displayBensin(&adminUser, literPertalite, HARGA_PERTALITE, "Pertalite", stokPertalite);
    break;
  case 2:
    clearScreen();
    displayBensin(&adminUser, literPertamax, HARGA_PERTAMAX, "Pertamax", stokPertamax);
    break;
  case 3:
    clearScreen();
    displayBensin(&adminUser, literSolar, HARGA_SOLAR, "Solar", stokSolar);
    break;
  case 0:
    printf("Kembali ke Menu Admin.\n");
    break;
  default:
    printf("Pilihan user tidak valid.\n");
  }
}
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
