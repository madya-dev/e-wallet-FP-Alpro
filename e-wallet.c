#include <stdio.h>
#include <string.h>

// global variable
int loginStatus = 0;
long saldo = 100000;
long *c_saldo = &saldo;
long nominalTopUp[7] = {5000, 10000, 20000, 25000, 50000, 75000, 100000};

// akun
char telp[12];
char password[9];
char name[20] = "Madya Santosa ";

int loginHandler(){
    printf("Masukan Nomor Telepon : ");
    scanf("%s", &telp);
    if(strcasecmp(telp, "085157349882") == 0){
        printf("Masukan Kata Sandi : ");
        scanf("%s", &password);
        if(strcasecmp(password, "alpro2021") == 0){
            loginStatus = 1;
            return 1;
        }else{
            printf("Kata sandi yang anda masukan salah!\n");
            return 0;
        }
    }else{
        printf("Nomor telepon yang anda masukan salah!\n");
        return 0;
    }
}
void logoutHandler(){
    loginStatus = 0;
    printf("Berhasil keluar dari akun");
}
int transfer(nominal){
    printf("Proses transfer...\n");
    if (nominal <= saldo)
    {
        *c_saldo -= nominal;
        return 1;

    }else{
        return 0;
    }
}
void topup(level){
    *c_saldo += nominalTopUp[level-1];
    printf("Proses Top up saldo berhasil \n");
}
void cekSaldo(){
    printf("Saldo anda saat ini sebesar Rp%ld.\n", saldo);
}
int main(){
    int pilihan;
    char telptujuan[12];
    long nominalTrf, nominalTU;
    if(loginStatus == 0){
        printf("===== SELAMAT DATANG =====");
    }else{
        printf("===== SELAMAT DATANG %s=====", strupr(name));
    }
    printf("\nPilihan : \n");
    if(loginStatus == 0){
        printf("1. Masuk Akun\n");
    }else{
        printf("1. Keluar\n");
    }
    printf("2. Cek Saldo\n3. Top up\n4. Transfer\n");
    printf("masukan pilihan anda : ");
    scanf("%d", &pilihan);  
    switch (pilihan)
    {
    case 1:
        if (loginStatus == 0)
        {
            loginHandler();
            main();
        }else{
            logoutHandler();
        }
        break;
    case 2:
        if (loginStatus == 1)
        {
            cekSaldo();
            main();
        }else{
            loginHandler();
            main();
        }
        break;
    case 3:
        if (loginStatus == 1)
        {
            printf("Daftar nominal Top Up : \n");
            for (int i = 1; i <= 7; i++)
            {
                printf("%d. Rp%ld \n", i, nominalTopUp[i-1]);
            }
            
            printf("Pilihan nominal Top Up : ");
            scanf("%ld", &nominalTU);
            if(nominalTU > 0 && nominalTU < 8){
                topup(nominalTU);
            }else{
                printf("Pilihan anda tidak ada di menu.\n");
            }
            cekSaldo();
            main();
        }else{
            loginHandler();
            main();
        }
        break;
    case 4:
        if (loginStatus == 1)
        {
          printf("Masukan nomor tujuan : ");
          scanf("%s", &telptujuan);
          printf("Masukan nominal transfer (Rp) : ");
          scanf("%ld", &nominalTrf);
          if(transfer(nominalTrf) == 1){
              printf("Status transfer tujuan %s sejumlah Rp%ld berhasil.\n", telptujuan, nominalTrf);
              cekSaldo();
          }else{
              printf("Status transfer tujuan %s sejumlah Rp%ld gagal.\n", telptujuan, nominalTrf);
              cekSaldo();
          }
          main();
        }else{
          loginHandler();
          main();
        }
        break;
    default:
        printf("pilihan yang anda masukan tidak ada, silakan coba lagi!\n");
        main();
    }
    return 0;
}