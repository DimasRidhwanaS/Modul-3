/** EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
 *   Modul               : 3 - Pointers and Function
 *   Hari dan Tanggal    : Jumat, 24 Februari 2023
 *   Nama (NIM)          : Dimas Ridhwana Shalsareza (13221076)
 *   Nama File           : main.c
 *   Deskripsi           : Membuka file.txt berisi status karakter, memasukkan nomor atribut, 
 *                         menampilkan status akhir karakter Setelah penambahan atribut
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// BUKA FILE
char spek[3];
char str_baris[10000];
char nama_file[10000];
char nama[10000];

// Partisi Comma
const char s[2] = ",";
const char s2[2] = "\n";
char *token;
char *token2;
int loop = 0;

// Assign stat
int count=0;
int status[6]  = {0,0,0,0,0,0};
int temp_plus[6] = {0,0,0,0,0,0};              // <HP,ATK,Crit Rate,Crit Damage,ER,EM>
int temp_percent[6] = {0,0,0,0,0,0};           // <HP,ATK,Crit Rate,Crit Damage,ER,EM>

void tambah_senjata(char senjata){ // Lengkapi parameter
    /** @brief Fungsi digunakan untuk mengubah nilai status karakter berdasarkan pilihan senjata
     * 
    **/

    if (senjata == 1){              // <HP,ATK,CritRate% ,CritDamage%, ER%, EM>
        temp_plus[1] += 400;
        temp_plus[2] += 28;
    } else if (senjata == 2){
        temp_plus[1] += 600;
        temp_plus[3] += 66;
    }else if (senjata == 3){
        temp_plus[1] += 550;
        temp_plus[3] += 88;      
    }else if (senjata == 4){
        temp_plus[1] += 600;
        temp_plus[4] += 55;      
    }else if (senjata == 5){
        temp_plus[1] += 540;
        temp_plus[5] += 265;        
    }
}

void tambah_artifak(int artifak){ // Lengkapi parameter
    /** @brief Fungsi digunakan untuk mengubah nilai status karakter berdasarkan pilihan artifak karakter
     * 
    */
   // Lengkapi fungsi // <HP,ATK,Crit Rate,Crit Damage,ER,EM>
    if (artifak == 1){              // <HP,ATK,CritRate% ,CritDamage%, ER%, EM>
        temp_percent[0] += 20;
        temp_percent[1] += 20;
    } else if (artifak == 2){
        temp_plus[4] += 20;
        temp_plus[5] += 80;
    }else if (artifak == 3){
        temp_plus[2] += 12;
        temp_plus[3] += 24;        
    }else if (artifak == 4){
        temp_percent[1] += 15;
        temp_plus[5] += 80;      
    }else if (artifak == 5){
        temp_percent[1] += 20;
        temp_plus[2] += 10;        
    }
}

void assign_stat(){
    //LOOPING UNTUK PARTISI KOMA
    token = strtok(str_baris, s);
    // printf("STATUS          : ");         //----DEBUG

    while( token != NULL ) {
        // printf("--------------------\n");    //----DEBUG

        status[loop] = atoi(token);
        // printf("%d,",status[loop]);     //----DEBUG
        // printf("\n");   //----DEBUG
        token = strtok(NULL, s);
        loop++;
    }
}

void new_stat(){
    // printf("NEW STAT        : ");
    for (int i=0; i<6; i++){
        status[i] += temp_plus[i]; // Jumlah dengan senjata
        int addition = 100 + temp_percent[i];
        int temp_stat = status[i]*addition/100;
        status[i] = temp_stat;
        temp_stat = 0;
    }
}

int main(){
    // Input nama file
    printf("Gensin Impek - Berpetualang di Dunia Fantasi\n");
    printf("Masukkan nama file yang berisi status karakter: ");
    scanf("%s", nama_file);                   

    FILE *file = fopen(nama_file, "r");
    // Validasi File 
    if (file == NULL){
        printf("File tidak dapat dibuka. Program Berakhir.");
        
    } else{
        // Input nomor senjata dan set artifak
        printf("Masukkan nomor senjata, set artifak 1, dan set artifak 2: ");
        for (int i=0; i<sizeof(spek);i++){
            scanf("%d",&spek[i]);
            // printf("spek %d : %d\n", i, spek[i]);               //----DEBUG
        } 
        count = 0;
        char * test;
        test = fgets(str_baris, 10000, file);
        token2 = strtok(str_baris, s2);
        printf("Status akhir karakter %s ", token2);

        while(fgets(str_baris, sizeof(str_baris), file) !=NULL){
            count++;
            if (count == 0){
                for (int i = 0; i<strlen(str_baris);i++){
                    nama[i] = str_baris[i];
                    // printf("%s", nama[i]);                      //----DEBUG
                } 
            }else if (count==1){
                assign_stat();
                tambah_senjata(spek[0]);
                tambah_artifak(spek[1]);
                tambah_artifak(spek[2]);
                new_stat();
            }       
        }
        printf("setelah menggunakan senjata dan artifak adalah:\n");
        printf("HP: %d\n", status[0]);
        printf("ATK: %d\n", status[1]);
        printf("Crit Rate: %d%c\n", status[2],37);
        printf("Crit Damage: %d%c\n", status[3],37);
        printf("ER: %d%c\n", status[4],37);
        printf("EM: %d\n", status[5]);
    }
   return(0);
}
