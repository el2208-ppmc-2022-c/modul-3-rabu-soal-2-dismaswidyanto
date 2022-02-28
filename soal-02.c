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
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            *(*(matrix+i)+j) = i+j+1;
        }
    }
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

/** @brief fungsi digunakan untuk menurunkan n permen pada kolom tertentu
 * @param dim dimensi dari matriks persegi
 * @param matrix matriks persegi
 * @param column kolom yang permennya akan diturunkan
 * @param start_row baris dimulainya permen dihapus 
 * @param step_down jumlah baris permen diturunkan
**/
void down_n(int dim, int matrix[dim][dim], int column, int start_row, int step_down){
    // Fungsi 
    for(int i=start_row;i>=0;i--){
        if(i>step_down-1){
            *(*(matrix+i)+column) = *(*(matrix+i-step_down)+column);
        }
        else{
            *(*(matrix+i)+column) = 0;
        }
    }
};

/** @brief Fungsi akan mengubah susunan matriks apabila pengguna memakai magic chocolate bomb
 * @param dim dimensi dari matriks persegi
 * @param matrix matriks persegi
 * @param idx_row indeks baris bom
 * @param idx_colum indeks kolom bom
**/
void mi_bomb(int dim, int matrix[dim][dim], int idx_row, int idx_column){
    int erase_row, start_row;
    // Seleksi jumlah baris yang akan dihapus berdasarkan letak pusat bom
    if(idx_row-1<0){
        erase_row = 2;
        start_row = idx_row+1;
    }
    else if(idx_row+1>=dim){
        erase_row = 2;
        start_row = idx_row;
    }
    else{
        erase_row = 3;
        start_row = idx_row+1;
    }
    // Seleksi jumlah kolom yang dihapus berdasakan letak pusat bom
    if((idx_column-1)<0){
        // printf("No column on left\n"); Print untuk debugging
        for(int i=0;i<2;i++){
            down_n(dim,matrix,idx_column+i,start_row,erase_row);
        }
    }
    else if((idx_column+1) >= dim){
        // printf("No column on right\n"); Print untuk debugging
        for(int i=-1;i<1;i++){
            down_n(dim,matrix,idx_column+i,start_row,erase_row);
        }
    }
    else{
        for(int i=-1;i<2;i++){
            down_n(dim,matrix,idx_column+i,start_row,erase_row);
        }
    }
}

/** @brief Fungsi akan mengubah susunan matriks apabila pengguna memakai Double Shot Syrup
 * @param dim dimensi dari matriks persegi
 * @param matrix matriks persegi
 * @param idx_row indeks baris sirup
 * @param idx_colum indeks kolom sirup
**/
void mi_syrup(int dim, int matrix[dim][dim], int idx_row, int idx_column){
    down_n(dim,matrix,idx_column,dim-1,dim);
    for(int i=0;i<dim;i++){
        down_n(dim,matrix,i,idx_row,1);      
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
    for(int i=0;i<mi_total;i++){
        // printf("row = %d, column = %d\n",mi_idx[i][0],mi_idx[i][1]);
        if(*(mi_type+i)=='b'){
            mi_bomb(dim,matrix,*(*(mi_idx+i)+0),*(*(mi_idx+i)+1));
        }
        else if(*(mi_type+i)=='s'){
            mi_syrup(dim,matrix,*(*(mi_idx+i)+0),*(*(mi_idx+i)+1));
        }
        // printf("Kondisi permen saat ke %d:\n",i); // Untuk debugging
        // print_matrix(dim,matrix); // Untuk debugging
    }
}

int main(){
    // Deklarasi variabel
    char file_name[MAX_STRING];
    char each_line[MAX_STRING];
    char temp[MAX_STRING];
    char *token;
    int count = 0;
    int n_mi_matrix;

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
    // printf("Magic Item = %d\n",n_mi_matrix);

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
                // printf("%c ",mi_type[count]); Print untuk debugging
            }
            else{
                // Kasus untuk indeks magic item
                mi_matrix[count][column-1] = atoi(token);
                // printf("%d ",mi_matrix[count][column-1]); Print untuk debugging
            }
            column += 1;
            token = strtok(NULL,",");
        }
        count+=1;
        // printf("\n"); Print untuk debugging
    }

    // Definisikan Matriks utama
    int candy_matrix[DIM][DIM];
    fill_matrix(DIM,candy_matrix);
    printf("Kondisi Permen Awal:\n");
    print_matrix(DIM,candy_matrix);
    mi_use(DIM,candy_matrix,n_mi_matrix,mi_type,mi_matrix);
    printf("Kondisi Permen Akhir:\n");
    print_matrix(DIM,candy_matrix);
    fclose(file_mi);
    return 0;
}
