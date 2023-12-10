#include <stdio.h>

#define MAX_DAYS 30  
void inputData(int days[], float pertamax[], float pertalite[], float solar[], float sisaPertamax[], float sisaPertalite[], float sisaSolar[], int day) {
    printf("Input data untuk hari ke-%d:\n", day);
    
    printf("Total tangki pertamax sebelum isi: ");
    scanf("%f", &pertamax[day]);
    
    printf("Total tangki pertamax sesudah isi: ");
    scanf("%f", &sisaPertamax[day]);
    
    printf("Total tangki pertalite sebelum isi: ");
    scanf("%f", &pertalite[day]);
    
    printf("Total tangki pertalite sesudah isi: ");
    scanf("%f", &sisaPertalite[day]);
    
    printf("Total tangki solar sebelum isi: ");
    scanf("%f", &solar[day]);
    
    printf("Total tangki solar sesudah isi: ");
    scanf("%f", &sisaSolar[day]);
    
    days[day] = day;
}

void displayData(int days[], float pertamax[], float pertalite[], float solar[], float sisaPertamax[], float sisaPertalite[], float sisaSolar[], int day) {
    printf("\nData untuk hari ke-%d:\n", day);
    printf("  Jenis Bensin   | Sebelum Isi | Sesudah Isi | Sisa Tangki\n");
    printf(" ----------------|-------------|-------------|-------------\n");
    printf("  Pertamax        | %-11.2f | %-11.2f | %-11.2f\n", pertamax[day], sisaPertamax[day], sisaPertamax[day] - pertamax[day]);
    printf("  Pertalite       | %-11.2f | %-11.2f | %-11.2f\n", pertalite[day], sisaPertalite[day], sisaPertalite[day] - pertalite[day]);
    printf("  Solar           | %-11.2f | %-11.2f | %-11.2f\n", solar[day], sisaSolar[day], sisaSolar[day] - solar[day]);
}

int main() {
    int days[MAX_DAYS];
    float pertamax[MAX_DAYS], pertalite[MAX_DAYS], solar[MAX_DAYS];
    float sisaPertamax[MAX_DAYS], sisaPertalite[MAX_DAYS], sisaSolar[MAX_DAYS];
    int totalDays = 0;
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Input Data Harian\n");
        printf("2. Tampilkan Data\n");
        printf("3. Keluar\n");
        printf("Pilih menu (1-3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (totalDays < MAX_DAYS) {
                    totalDays++;
                    inputData(days, pertamax, pertalite, solar, sisaPertamax, sisaPertalite, sisaSolar, totalDays);
                    printf("Data berhasil disimpan!\n");
                } else {
                    printf("Jumlah hari maksimum sudah tercapai.\n");
                }
                break;
            case 2:
                if (totalDays > 0) {
                    printf("\nTampilkan data untuk hari ke berapa? (1-%d): ", totalDays);
                    scanf("%d", &choice);
                    if (choice >= 1 && choice <= totalDays) {
                        displayData(days, pertamax, pertalite, solar, sisaPertamax, sisaPertalite, sisaSolar, choice);
                    } else {
                        printf("Input tidak valid.\n");
                    }
                } else {
                    printf("Belum ada data yang dimasukkan.\n");
                }
                break;
            case 3:
                printf("Program selesai.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 3);

    return 0;
}

