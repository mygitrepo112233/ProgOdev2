/****************************************************************************
**					SAKARYA ÜNİVERSİTESİ
**			         BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**				    BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**				          PROGRAMLAMAYA GİRİŞİ DERSİ
**
**				ÖDEV NUMARASI…...:2023 guz 2.odev
**				ÖĞRENCİ ADI...............:SERHAT HAR
**				ÖĞRENCİ NUMARASI.:G231210040
**				DERS GRUBU…………:2.OGRETIM B GRUBU
****************************************************************************/

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#pragma warning(disable : 4996)

using namespace std;

void hesap_olusturma();
void hesap_giris();
float ozel_kripto_fiyat_hesap();
float genel_kripto_fiyat_hesap();
void gun_ilerletme();       /*fonksiyonlarin tanitilmasi*/ 
float kar = 0;
int gunsayar = 1;            /*evrensel degiskenler*/
int secilen_hesap;
int secim;
int hesapsayar = 0;
string test = "a";

struct Kripto {
    float genel_kripto_fiyat = 1;     //ilk gun fiyati
    float genel_artis = 1.01;   //her gun
    float genel_dusus = 0.95;   //15 gunde bir

    float ozel_kripto_fiyat = 1;
    float ozel_artis = 1.05;    //her gun
    float ozel_dusus = 0.9;     //ayda rastgele 3 gun
};

struct Kripto kripto;
struct Kripto ozel_kripto;

class Hesap {   /*genel ve ozel hesabi barindiran class*/
public:
    class Genel_hesap {     /*genel hesabin verileri*/
    private:
        string Kullanicino = "a";
        float Bakiye_tl = 0;
        int Bakiye_kripto = 0;
        float Kar = 0;
        float bakiye_sayar = 0;
    public:
        void setKullanicino() {     /*kullanici no icin setter fonksiyonu*/
            int i = 1;
            while (i == 1) {
                string kullanicino;
                cout << "Genel hesap icin 6 haneli kullanici nonuzu giriniz:";
                cin >> kullanicino;
                if (kullanicino.size() == 6) {
                    Kullanicino = kullanicino;
                    cout << Kullanicino << "'nolu genel hesaba giris yapildi\n";
                    i = 0;
                }
                else {
                    cout << "Lutfen sadece 6 haneli bir kullanici no giriniz\n";
                }
            }
        }
        void setBakiye_tl_yatir() {     /*TL yatirmak icin setter fonksiyonu*/
            int i = 1;
            int bakiye;
            while (i == 1) {
                cout << "yuklemek istediginiz bakiyeyi giriniz:";
                cin >> bakiye;
                if (bakiye <= 0) {
                    cout << "0'dan kucuk veya 0'a esit miktarda bakiye yukleyemezsiniz\n";
                }
                else {
                    Bakiye_tl += bakiye;
                    cout << "Yeni bakiyeniz: " << Bakiye_tl << endl;
                    i = 0;
                }
            }
            bakiye_sayar += bakiye;
        }
        void setBakiye_tl_cek() {       /*TL cekmek icin setter fonksiyonu*/
            int i = 1;
            int bakiye;
            while (i == 1) {
                cout << "cekmek istediginiz bakiyeyi giriniz:";         /*negatif olma bakiyeden daha cok para cekme gibi durumlari kontrol eder*/
                cin >> bakiye;
                if (bakiye < 0) {
                    cout << "0'dan kucuk bakiye cekemezsiniz\n";
                }
                else if (bakiye > Bakiye_tl) {
                    cout << "Yetersiz bakiye";
                }
                else {
                    Bakiye_tl -= bakiye;
                    cout << "Yeni bakiyeniz: " << Bakiye_tl << endl;
                    i = 0;
                }
            }
            bakiye_sayar -= bakiye;
        }
        void setBakiye_kripto_al() {        /*kripto para almak ici setter fonksiyonu*/
            int i = 1;
            while (i == 1) {
                int bakiye;
                cout << "Almak istediginiz kripto para miktarini giriniz:";
                cin >> bakiye;
                if (bakiye >= 0 && (bakiye * kripto.genel_kripto_fiyat) <= Bakiye_tl) {
                    Bakiye_kripto += bakiye;
                    Bakiye_tl -= bakiye * kripto.genel_kripto_fiyat;
                    cout << "Yeni kripto bakiyeniz: " << Bakiye_kripto << endl
                        << "Yeni tl bakiyeniz: " << Bakiye_tl << endl;
                    i = 0;
                }
                else if (Bakiye_tl == 0) {
                    cout << "Bakiyeniz 0 alim yapmadan once yukleme yapiniz\n";
                    i = 0;
                }
                else if ((bakiye * kripto.genel_kripto_fiyat) > Bakiye_tl) {
                    cout << "Yetersiz bakiye\n";
                }
                else {
                    cout << "0'dan kucuk veya 0'a esit miktarda kripto alamazsiniz\n";
                }
            }
        }
        void setBakiye_kripto_sat() {       /*kripto para satmak icin setter fonksiyonu*/
            int i = 1;
            while (i == 1) {
                int bakiye;
                cout << "Satmak istediginiz kripto para miktarini giriniz:";
                cin >> bakiye;
                if (bakiye >= 0 && Bakiye_kripto >= bakiye) {
                    Bakiye_kripto -= bakiye;
                    Bakiye_tl += bakiye * kripto.genel_kripto_fiyat;
                    cout << "Yeni kripto bakiyeniz: " << Bakiye_kripto << endl
                        << "Yeni tl bakiyeniz: " << Bakiye_tl << endl;
                    i = 0;
                }
                else if (Bakiye_kripto < bakiye) {
                    cout << "Kripto bakiyeniz yetersiz\n";
                }
                else {
                    cout << "0'dan kucuk veya 0'a esit miktarda kripto alamazsiniz\n";
                }
            }
        }

        string getKullanicino() {       /*kullanici adina erismek icin getter fonksiyonu*/
            return Kullanicino;
        }
        float getBakiye() {     /*bakiyeye erismek icin getter fonksiyonu*/
            return Bakiye_tl;
        }
        float getKar() {        /*kara erismek icin getter fonksiyonu*/
            return Kar;
        }
        float getBakiye_sayar() {
            return bakiye_sayar;
        }
        int getBakiye_kripto() {        /*kripto bakiyesine erismek icin getter fonksiyonu*/
            return Bakiye_kripto;
        }
    };

    class Ozel_hesap {      /*ozel hesap classi*/
    private:
        string Kullanicino = "a";    /*ozel hesabin verileri*/
        float Bakiye_tl = 0;
        int Bakiye_kripto = 0;
        float bakiye_sayar_ozel = 0;
    public:
    public:
        void setKullanicino() {     /*ozel hesap kullanici nosu icin setter fonksiyonu*/
            int i = 1;
            while (i == 1) {
                string kullanicino;
                cout << "Ozel hesap icin 6 haneli kullanici nonuzu giriniz:";
                cin >> kullanicino;
                if (kullanicino.size() == 6) {
                    Kullanicino = kullanicino;
                    cout << Kullanicino << "'nolu ozel hesaba giris yapildi\n";
                    i = 0;
                }
                else {
                    cout << "Lutfen sadece 6 haneli bir kullanici no giriniz\n";
                }
            }
        }
        void setBakiye_tl_yatir() {     /*ozel hesaba TL yatirmak icin setter fonksiyonu*/
            int i = 1;
            int bakiye;
            while (i == 1) {
                cout << "yuklemek istediginiz bakiyeyi giriniz:";
                cin >> bakiye;
                if (bakiye <= 0) {
                    cout << "0'dan kucuk veya 0'a esit miktarda bakiye yukleyemezsiniz\n";
                }
                else {
                    Bakiye_tl += bakiye;
                    cout << "Yeni bakiyeniz: " << Bakiye_tl << endl;
                    i = 0;
                }
            }
            bakiye_sayar_ozel += bakiye;
        }
        void setBakiye_tl_cek() {       /*ozel hesaptan TL cekmek icin setter fonksiyonu*/
            int i = 1;
            int bakiye;
            while (i == 1) {
                cout << "cekmek istediginiz bakiyeyi giriniz:";
                cin >> bakiye;
                if (bakiye < 0) {
                    cout << "0'dan kucuk bakiye cekemezsiniz\n";
                }
                else if (bakiye > Bakiye_tl) {
                    cout << "Yetersiz bakiye\n";
                }
                else {
                    Bakiye_tl -= bakiye;
                    cout << "Yeni bakiyeniz: " << Bakiye_tl << endl;
                    i = 0;
                }
            }
            bakiye_sayar_ozel -= bakiye;
        }
        void setBakiye_kripto_al() {        /*ozel hesaba kripto para almak icin setter fonksiyonu*/
            int i = 1;
            while (i == 1) {
                int bakiye;
                cout << "Almak istediginiz kripto para miktarini giriniz:";
                cin >> bakiye;
                if (bakiye >= 0 && (bakiye * kripto.ozel_kripto_fiyat) <= Bakiye_tl) {
                    Bakiye_kripto += bakiye;
                    Bakiye_tl -= bakiye * kripto.ozel_kripto_fiyat;
                    cout << "Yeni kripto bakiyeniz: " << Bakiye_kripto << endl
                        << "Yeni tl bakiyeniz: " << Bakiye_tl << endl;
                    i = 0;
                }
                else if ((bakiye * kripto.ozel_kripto_fiyat) > Bakiye_tl) {
                    cout << "Yetersiz bakiye\n";
                }
                else if (Bakiye_tl == 0) {
                    cout << "Bakiyeniz 0 alim yapmadan once yukleme yapiniz\n";
                    i = 0;
                }
                else {
                    cout << "0'dan kucuk veya 0'a esit miktarda kripto alamazsiniz\n";
                }
            }
        }
        void setBakiye_kripto_sat() {       /*ozel hesaptan kripto para satmak icin setter fonksiyonu*/
            int i = 1;
            while (i == 1) {
                int bakiye;
                cout << "Satmak istediginiz kripto para miktarini giriniz:";
                cin >> bakiye;
                if (bakiye >= 0 && Bakiye_kripto >= bakiye) {
                    Bakiye_kripto -= bakiye;
                    Bakiye_tl += bakiye * kripto.ozel_kripto_fiyat;
                    cout << "Yeni kripto bakiyeniz: " << Bakiye_kripto << endl
                        << "Yeni tl bakiyeniz: " << Bakiye_tl << endl;
                    i = 0;
                }
                else if (Bakiye_kripto < bakiye) {
                    cout << "Kripto bakiyeniz yetersiz\n";
                }
                else {
                    cout << "0'dan kucuk veya 0'a esit miktarda kripto alamazsiniz\n";
                }
            }
        }

        string getKullanicino() {       /*kullanici adina erismek icin getter fonksiyonu*/
            return Kullanicino;
        }
        float getBakiye_sayar() {
            return bakiye_sayar_ozel;
        }
        float getBakiye_tl() {      /*bakiyeye erismek icin getter fonksiyonu*/
            return Bakiye_tl;
        }
        int getBakiye_kripto() {        /*kripto bakiyesine erismek icin getter fonksiyonu*/
            return Bakiye_kripto;
        }
    };

    int hesap_turu;

    class Genel_hesap genel_hesap;
    class Ozel_hesap ozel_hesap;
};

class Hesap hesap[500];

void ana_menu_genel() {     /*genel hesap icin kullanicinin islemlerini gerceklestirecegi menu*/
    int i = 1;
    int islem;
    cout << "Kripto para genel hesabiniza hosgeldiniz\n";
    while (i == 1) {
        cout << "1) Bakiye sorgulama\n"
            << "2) Para yatirma\n"
            << "3) Para cekme\n"
            << "4) Kripto alma\n"
            << "5) Kripto satma\n"
            << "6) Kari goster\n"
            << "7) Yeni hesap olusturmak icin 7'ye basiniz\n"
            << "8) Hesap degistirmek icin 8'e basiniz\n"
            << "9) Sonraki gune gecmek icin 9'ye basiniz\n"
            << "!) Uygulamadan cikmak icin 0'a basiniz\n"
            << "Yapmak istediginiz islemi seciniz:";
        cin >> islem;

        switch (islem) {        /*sectigimiz isleme gore fonksiyonları cagiran switch case yapisi*/
        case 0:
            i = 0;
            break;
        case 1:
            system("cls");
            cout << hesap[secilen_hesap].genel_hesap.getKullanicino() << "Nolu hesabinizin guncel TL bakiyesi: "
                << hesap[secilen_hesap].genel_hesap.getBakiye() << endl << "Guncel genel kripto para bakiyes:"
                << hesap[secilen_hesap].genel_hesap.getBakiye_kripto() << endl;
            break;
        case 2:
            system("cls");
            hesap[secilen_hesap].genel_hesap.setBakiye_tl_yatir();
            break;
        case 3:
            system("cls");
            hesap[secilen_hesap].genel_hesap.setBakiye_tl_cek();
            break;
        case 4:
            system("cls");
            hesap[secilen_hesap].genel_hesap.setBakiye_kripto_al();
            break;
        case 5:
            system("cls");
            hesap[secilen_hesap].genel_hesap.setBakiye_kripto_sat();
            break;
        case 6:
            system("cls");
            if (hesap[secilen_hesap].genel_hesap.getBakiye_kripto() == 0) {
                kar = hesap[secilen_hesap].genel_hesap.getBakiye() - hesap[secilen_hesap].genel_hesap.getBakiye_sayar();
                cout << "Kariniz: " << kar << endl;
            }
            else {
                kar = (hesap[secilen_hesap].genel_hesap.getBakiye_kripto() * kripto.genel_kripto_fiyat)
                    + hesap[secilen_hesap].genel_hesap.getBakiye() - hesap[secilen_hesap].genel_hesap.getBakiye_sayar();
                cout << "Kariniz" << kar << endl;
            }
            break;
        case 7:
            system("cls");
            i = 0;
            hesap_olusturma();
            break;
        case 8:
            hesap_giris();
            break;
        case 9:
            system("cls");
            gun_ilerletme();
            genel_kripto_fiyat_hesap();
            ozel_kripto_fiyat_hesap();
        }
    }
}

void ana_menu_ozel() {      /*ozel hesap icin kullanicinin islemlerini gerceklestirecegi menu*/
    int i = 1;
    int islem;
    cout << "Kripto para ozel hesabiniza hosgeldiniz\n";
    while (i == 1) {
        cout << "1) Bakiye sorgulama\n"
            << "2) Para yatirma\n"
            << "3) Para cekme\n"
            << "4) Kripto alma\n"
            << "5) Kripto satma\n"
            << "6) Kari goster\n"
            << "7) Yeni hesap olusturmak icin 7'ye basiniz\n"
            << "8) Hesap degistirmek icin 8'e basiniz\n"
            << "9) Sonraki gune gecmek icin 9'ye basiniz\n"
            << "!) Uygulamadan cikmak icin 0'a basiniz\n"
            << "Yapmak istediginiz islemi seciniz:";
        cin >> islem;

        switch (islem) {            /*sectigimiz isleme gore fonksiyonları cagiran switch case yapisi*/
        case 0:
            i = 0;
            break;
        case 1:
            system("cls");
            cout << hesap[secilen_hesap].ozel_hesap.getKullanicino() << "Nolu hesabinizin guncel TL bakiyesi: "
                << hesap[secilen_hesap].ozel_hesap.getBakiye_tl() << endl
                << "Guncel ozel kripto para bakiyesi: "
                << hesap[secilen_hesap].ozel_hesap.getBakiye_kripto();
            break;
        case 2:
            system("cls");
            hesap[secilen_hesap].ozel_hesap.setBakiye_tl_yatir();
            break;
        case 3:
            system("cls");
            hesap[secilen_hesap].ozel_hesap.setBakiye_tl_cek();
            break;
        case 4:
            system("cls");
            hesap[secilen_hesap].ozel_hesap.setBakiye_kripto_al();
            break;
        case 5:
            system("cls");
            hesap[secilen_hesap].ozel_hesap.setBakiye_kripto_sat();
            break;
            system("cls");
        case 6:
            system("cls");
            if (hesap[secilen_hesap].ozel_hesap.getBakiye_kripto() == 0) {
                kar = hesap[secilen_hesap].ozel_hesap.getBakiye_tl() - hesap[secilen_hesap].ozel_hesap.getBakiye_sayar();
                cout << "Kariniz: " << kar << endl;
            }
            else {
                kar = (hesap[secilen_hesap].ozel_hesap.getBakiye_kripto() * kripto.ozel_kripto_fiyat)
                    + hesap[secilen_hesap].ozel_hesap.getBakiye_tl() - hesap[secilen_hesap].ozel_hesap.getBakiye_sayar();
                cout << "Kariniz" << kar << endl;
            }
            break;
        case 7:
            system("cls");
            i = 0;
            hesap_olusturma();
            break;
        case 8:
            hesap_giris();
            break;
        case 9:
            system("cls");
            gun_ilerletme();
            genel_kripto_fiyat_hesap();
            ozel_kripto_fiyat_hesap();
        }
    }
}

int ay;
int yil;
int gun;

void sistem_tarih() {       /*windows sisteminden guncel tarihi ceker ve bunu ay yil gun degiskenlerine atar*/
    time_t tim = time(0);
    tm* sistem = localtime(&tim);
    yil = sistem->tm_year + 1900;
    ay = sistem->tm_mon + 1;
    gun = sistem->tm_mday;

    if (sistem != nullptr) {
        cout << sistem->tm_year + 1900 << "/";
        cout << sistem->tm_mon + 1 << "/";
        cout << sistem->tm_mday << endl;
    }
    else {
        cout << "!!!!!!!windows sisteminden tarihi cekme ile ilgili bir hata olustu!!!!!!!!!";
    }
}

void gun_ilerletme() {      /*tarihin ilerlemesini saglar*/
    gun++;
    gunsayar++;
    if (gun == 30) {
        gun = 1;
        ay++;
    }
    if (ay == 13) {
        ay = 1;
        yil++;
    }
    string tarih = to_string(gun) + "/" + to_string(ay) + "/" + to_string(yil);
    cout << "Tarih: " << tarih << endl;
}

float genel_kripto_fiyat_hesap() {      /*genel hesap icin yukselis ve dususleri ayarlar*/
    if (gunsayar % 15 == 0) {
        kripto.genel_kripto_fiyat *= kripto.genel_dusus;
        cout << "Genel kripto para %5 dustu!!\n";
    }
    else {
        kripto.genel_kripto_fiyat *= kripto.genel_artis;
        cout << "Genel kripto para %1 yukseldi!!\n";
    }
    cout << "Genel kripto para guncel fiyat: " << kripto.genel_kripto_fiyat << endl;
    return kripto.genel_kripto_fiyat;
}

int dusus_ozel[3];

float ozel_kripto_fiyat_hesap() {   /*ozel hesap icin kripto paranin yukselis ve dususlerini ayarlar*/
    if (gun == 1) {
        dusus_ozel[0] = rand() % 30 + 1;
        dusus_ozel[1] = rand() % 30 + 1;
        dusus_ozel[2] = rand() % 30 + 1;
    }
    if (dusus_ozel[0] == gun || dusus_ozel[1] == gun || dusus_ozel[2] == gun) {
        kripto.ozel_kripto_fiyat *= kripto.ozel_dusus;
        cout << "Ozel kripto para %10 dustu!!\n";
    }
    else {
        kripto.ozel_kripto_fiyat *= kripto.ozel_artis;
        cout << "Ozel kripto para %5 yukseldi!!\n";
    }
    cout << "Ozel Kripto para guncel fiyat: " << kripto.ozel_kripto_fiyat << endl;
    return kripto.ozel_kripto_fiyat;
}

void hesap_giris() {
    cout << "Girmek istediginiz hesabinizi seciniz:\n";     /*Olusturulmus olan hesaplara giris yapabilmemizi saglar*/
    for (int i = 0; i < hesapsayar; i++) {
        if (hesap[i].hesap_turu == 1) {
            cout << i + 1 << ") " << "No: " << hesap[i].genel_hesap.getKullanicino() << " (genel)\t"
                << "TL bakiyesi: " << hesap[i].genel_hesap.getBakiye() << " "
                << "Kripto bakiyesi: " << hesap[i].genel_hesap.getBakiye_kripto() << endl;
        }
        else if (hesap[i].hesap_turu == 2) {
            cout << i + 1 << ") " << "No: " << hesap[i].ozel_hesap.getKullanicino() << " (ozel)\t"
                << "TL bakiyesi: " << hesap[i].ozel_hesap.getBakiye_tl() << " "
                << "Kripto bakiyesi: " << hesap[i].ozel_hesap.getBakiye_kripto() << endl;
        }
    }
    cin >> secilen_hesap;
    secilen_hesap -= 1;
    if (hesap[secilen_hesap].hesap_turu == 1) {
        ana_menu_genel();
    }
    else if (hesap[secilen_hesap].hesap_turu == 1) {
        ana_menu_ozel();
    }
}

void hesap_olusturma() {     /*yeni bir genel ya da ozel hesap olusturulmasini saglar*/
    cout << "Kripto para borsasina hosgeldiniz\n"
        << "Genel hesap olusturmak icin 1'e ozel hesap olusturmak icin 2'ye basiniz.\n";
    cin >> secim;

    secilen_hesap = hesapsayar;
    hesap[secilen_hesap].hesap_turu = secim;
    hesapsayar++;
    if (secim == 1) {
        hesap[secilen_hesap].genel_hesap.setKullanicino();
        ana_menu_genel();
    }
    else if (secim == 2) {
        hesap[secilen_hesap].ozel_hesap.setKullanicino();
        ana_menu_ozel();
    }
}

int main() {
    srand(time(NULL));   
    sistem_tarih();
    int kalangun = 30 - gun;
    dusus_ozel[0] = rand() % (kalangun + 1);        /*ilk ayki ozel kripto dususlerinin gunleri rastgele yaratiliyor*/
    dusus_ozel[0] += gun;
    dusus_ozel[1] = rand() % (kalangun + 1);
    dusus_ozel[1] += gun;
    dusus_ozel[2] = rand() % (kalangun + 1);
    dusus_ozel[2] += gun;
    hesap_olusturma();
}
