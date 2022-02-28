/*EL2208 Praktikum Pemecahan Masalah dengan C 2021/2022
*Modul            : 3 - Pointers and Functions
*Percobaan        : -
*Hari dan Tanggal : Rabu, 2 Maret 2022
*Nama (NIM)       : -
*Asisten (NIM)    : -
*Nama File        : soal-02.c
*Deskripsi        : -
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 255
#define DIM 5

/** @brief fungsi digunakan untuk menginisiasi matriks awal
 * @param dim dimensi dari matriks persegi
 * @param matrix matriks persegi yang akan diinisiasi 
**/
void fill_matrix(int dim,int matrix[dim][dim]){
    // Isi inisialisasi fungsi
    ...
}

/** @brief fungsi digunakan untuk menampilkan matriks persegi ke terminal
 * @param dim dimensi dari matriks persegi
 * @param matrix matriks persegi yang akan ditampilkan ke layar
**/
void print_matrix(int dim, int matrix[dim][dim]){
    // Fungsi digunakan untuk menampilkan matriks ke layar
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            printf("%d ",*(*(matrix+i)+j));
        }
        printf("\n");
    }
}

/** @brief fungsi digunakan untuk menggunakan magic item yang ada di file eksternal
 * @param dim dimensi dari matriks persegi
 * @param matrix matriks persegi
 * @param mi_total banyak magic item
 * @param mi_type matriks jenis magic item yang digunakan
 * @param mi_idx matriks lokasi magic item yang digunakan
**/
void mi_use(int dim,int matrix[dim][dim],int mi_total,char mi_type[mi_total],int mi_idx[mi_total][2]){
	//Isi kode anda
}

// Silahkan tambahkan fungsi lain apabila diperlukan. Pastikan untuk menggunakan konsep pointer juga

int main(){
    // Deklarasi variabel
    char file_name[MAX_STRING];
    char each_line[MAX_STRING];
    char temp[MAX_STRING];
    char *token;
    int count = 0;
    int n_mi_matrix; // Menyatakan jumlah magic item

    // Input nama file
    printf("Masukkan nama file: ");
    scanf("%s", file_name);

    // Buka File Eksternal
    FILE* file_mi = fopen(file_name, "r") ;
    // printf("Nama File: %s\n",file_name); // Untuk Debugging

    // Validasi File 
    if(file_mi == NULL){
        printf("File tidak dapat dibuka. Program Berakhir.\n");
        fclose(file_mi);
        return 0;
    }

    // Baca banyak magic item
    fgets(each_line,MAX_STRING,file_mi);
    strcpy(temp,each_line);
    n_mi_matrix = atoi(temp);

    // Deklarasi matriks jenis dan indeks magic item
    // mi_matrix berisi letak (indeks baris dan kolom) dari magic item yang bersangkutan.
    // Indeks 0 menyatakan letak magic item ke 1, indeks 1 letak magic item kedua, dst
    int mi_matrix[n_mi_matrix][2];
    // mi_type berisi jenis (b untuk magic chocolate bomb dan s untuk double shot syrup) dari magic item yang bersangkutan
    // Indeks 0 menyatakan jenis magic item ke 1, indeks 1 jenis magic item kedua, dst
    char mi_type[n_mi_matrix];

    // Baca magic item yang akan dipakai dari file eksternal
    while(fgets(each_line,MAX_STRING,file_mi)){
        strcpy(temp,each_line);
        int column = 0;
        token = strtok(temp,",");
        while(token!=NULL){
            if(column == 0){
                // Kasus untuk jenis magic item (char)
                mi_type[count] = token[0];
            }
            else{
                // Kasus untuk indeks magic item
                mi_matrix[count][column-1] = atoi(token);
            }
            column += 1;
            token = strtok(NULL,",");
        }
        count+=1;
    }

    // Isi Program Utama
	fill_matrix(DIM,candy_matrix);
    printf("Kondisi Permen Awal:\n");
    print_matrix(...);
	mi_use(DIM,candy_matrix,n_mi_matrix,mi_type,mi_matrix);
    printf("Kondisi Permen Akhir:\n");
    print_matrix(...);
	
    fclose(file_mi);
    return 0;
}