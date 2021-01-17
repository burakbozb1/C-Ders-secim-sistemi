#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000


struct HOCA {
    int id;
    char adSoyad[100];
    char unvan[100];
    struct HOCA *next;
};

struct DERS{
	char dersKod[100];
	char dersAd[100];
	int dersKredi;
	int dersKontenjan;
	int ogretmenId;
	struct DERS *next;
};

struct OgrDers{
	int ogrNo;
	char dersKod[100];
	int durum;
	char tarih[100];
	struct OgrDers *next;
};

struct OGRENCI{
	int ogrNo;
	char ogrAdSoyad[100];
	int dersSayisi;
	int toplamKredi;
	struct OGRENCI *next;
	struct OgrDers *dersHead;
};



char *getTime();

void dosyaKontrol(char *);
void ogretimUyesiYazdir();
void satirOku(char * );
void derslerYazdir();
void ogrencilerYazdir();
void ogrenciDersYazdir();
void clrBuffer();
struct HOCA* hocaSonaEkle(struct HOCA*,int, char *, char *);
struct HOCA* hocaDugumOlustur(int, char *, char *);
int hocaGuncelle(struct HOCA*,int);
int hocaIdAl(struct HOCA*);
struct HOCA* hocaSil(struct HOCA*,int);
void hocaTxtYaz(struct HOCA*);
struct HOCA* hocaBaslangic(struct HOCA*);
void hocaListedenYazdir(struct HOCA*);
void hocaTemizle(struct HOCA*);


//DersFonksiyonlar�
struct DERS* dersSonaEkle(struct DERS* ,char * , char * , int , int , int );
struct DERS* dersDugumOlustur(char *, char *, int, int, int);
int dersGuncelle(struct DERS* ,char * ,struct HOCA* );
void dersTxtYaz(struct DERS*);
void derslerListedenYazdir(struct DERS*);
struct DERS* dersBaslangic(struct DERS*);
struct DERS* dersSil(struct DERS*,char *);
void dersTemizle(struct DERS*);


//��renci fonksiyonlar�
struct OGRENCI* ogrDugumOlustur(int, char *);
struct OGRENCI* ogrSonaEkle(struct OGRENCI*,int, char *);
int ogrIdOlustur(struct OGRENCI*);
int ogrGuncelle(struct OGRENCI*,int);
void ogrListedenYazdir(struct OGRENCI*);
void ogrTemizle(struct OGRENCI*);
struct OGRENCI* ogrSil(struct OGRENCI*,int);
void ogrTxtYaz(struct OGRENCI*);
struct OGRENCI* ogrBaslangic(struct OGRENCI*);
struct OGRENCI* ogrBaslangicDugumOlustur(int, char * ,int ,int );
struct OGRENCI* ogrBaslangicSonaEkle(struct OGRENCI* ,int , char * ,int ,int );


//Ogrenci men�s� fonksiyonlar�
struct OGRENCI* girisYapanOgrenci(struct OGRENCI* ,int );
void secilebilecekDersler(struct OGRENCI *,struct DERS* );
void ogrDerslerimYazdir(struct OGRENCI *);
struct OgrDers* ogrDersSonaEkle(struct OGRENCI *,struct DERS *,char * ,int , char * );
struct OgrDers* ogrDersDugumOlustur(int ,char * , int , char * );
void ogrDerstxtYazdir(struct OGRENCI*);
void ogrDersBaslangic(struct OGRENCI*);
void ogrDersCikar(struct OGRENCI *,char * ,struct DERS *);
void ogrDersBaslangicSonaEkle(struct OGRENCI *,char * ,int , char * );

//��kt� fonksiyonlar�
struct HOCA * arananHoca(struct HOCA* ,int );

//EK KONTROLLER
struct DERS* kontrolDersSil(int ,struct DERS* );
void kontrolDersBosla(int ,struct DERS* );
void kontrolOgrenciDersSil(int ,struct OGRENCI* ,struct DERS* );
struct OgrDers* hocaSilDersSil(struct OGRENCI *,char * ,struct DERS *);
void ogrKrediDersGuncelle(struct OGRENCI* ,struct DERS* );
void ogrSilinenDersCikar(struct OGRENCI* ,char * ,struct DERS* dersHead);
struct OgrDers* ogrencidenDersiSil(struct OGRENCI *,char * ,struct DERS* );


int main()
{
	
	
	int giris=-1;
	int i=0,j=0;
	int guncelHocaId=-1;
	int hocaSilinecekId=-1;
	char dersArananId[100];
	char dersSilinecekKod[100];
	char yeniOgrAdSoyad[100];
	int ogrGuncelNo;
	int ogrSilArananNo;
	int islemYapanOgrenci;
	char secilenDersKodu[100];
	char cikacakDersKodu[100];
	int hocaDersListeleId;
	int hocaninDersleriId;
	char dersOgrenciDersKod[100];
	char sinifListesiDersKod[100];
	int ogrenciSecilenDerslerNo;
	
	struct HOCA* hocaHead = NULL;
	struct DERS* dersHead = NULL;
	struct OGRENCI* ogrHead = NULL;
	
	hocaHead = hocaBaslangic(hocaHead);
	dersHead = dersBaslangic(dersHead);
	ogrHead = ogrBaslangic(ogrHead);
	ogrDersBaslangic(ogrHead);
	ogrKrediDersGuncelle(ogrHead,dersHead);
	ogrDerstxtYazdir(ogrHead);
	ogrTxtYaz(ogrHead);
	
	//Dosya varm� kontrol. Eger dosya yoksa dosyalar yarat�lacakt�r.
	dosyaKontrol("hocalar.txt");
	dosyaKontrol("dersler.txt");
	dosyaKontrol("ogrenciler.txt");
	dosyaKontrol("ogrenci-ders.txt");
	
	
	
	do
	{
		system("cls");
		printf("\n\n==============================================================================\n\nMENU\n");
		
		printf("Bilgilendirme:\n");
		printf("Admin menusunde hocalar, desrler ve ogrenciler icin eklemeler, listelemeler, guncellemeler yapilmaktadir.\n");
		printf("Bu islemler haricinde odev sonucu olarak istenen ciktilar da admin menusu icerisindedir.\n");
		printf("Ogrenci menusunde, ogrenci numarasi ile giris yapmakta ve ders secim islemlerini gerceklestirmektedir.\n");
		printf("Bellek atamalarini temizlemek icin 0 ile cikis yapiniz.\n\n");
		printf("Secenekler:\n");
		printf("1 - Admin girisi icin\n2 - Ogrenci girisi icin\n0 - Cikis yapmak icin\nSecim:");
		scanf("%d",&giris);
		clrBuffer();
		if(giris==1){
			system("cls");
			int giris2=-1;
			do
			{
				system("cls");
				printf("Admin menusune hos geldiniz.\n");
				printf("EKLEMELER\n1 - Ogretim uyesi islemleri icin\n2 - Ders islemleri icin\n3 - Ogrenci islemleri icin\n");
				printf("\nLISTELEMELER\n4 - Ogretim uyesinin verdigi dersler\n5 - Dersi alan tum ogrenciler\n6 - Ogrencinin aldigi tum dersler\n7 - derskodu_sinifLisesi.txt yazdir\n");
				printf("0 - Ust menuye donmek icin");
				printf("Secim :");
				scanf("%d",&giris2);
				int giris3;
				clrBuffer();
				switch(giris2)
				{
					case 1://Admin ��retim �yesi men�s�ne gider
						giris3=-1;
						do
						{
							system("cls");
							printf("Admin Menusu -> Ogretim Uyesi islemleri\n");
							printf("1 - Ogretim uyelerini listele\n");
							printf("2 - Ogretim uyesi ekle\n");
							printf("3 - Ogretim uyesi guncelle\n");
							printf("4 - Ogretim uyesi sil\n");
							printf("0 - Ust menuye don\n");
							printf("Secim :");
							scanf("%d",&giris3);
							clrBuffer();
							switch(giris3)
							{
								case 1://Admin ��retim �yelerini listeleler
									printf("Hocalar:\n");
									
									hocaListedenYazdir(hocaHead);
									
									printf("Devam etmek icin enter tusuna basiniz.\n");
									getch();
									break;
								case 2://Admin Yeni ��retim �yesi ekler.
									printf("Yeni ogretim uyesi eklenecek.\n");
									
									struct HOCA yeniHoca;
									printf("Yeni hocanin adini ve soyadini girin:");
									gets(yeniHoca.adSoyad);
									printf("Yeni hocanin unvanini girin:");
									gets(yeniHoca.unvan);
									yeniHoca.id = hocaIdAl(hocaHead);
									hocaHead=hocaSonaEkle(hocaHead,yeniHoca.id,yeniHoca.adSoyad,yeniHoca.unvan);
									hocaTxtYaz(hocaHead);
									
									printf("Devam etmek icin enter tusuna basiniz.\n");		
									getch();
									break;
								case 3://��retim �yesini g�ncelle
									printf("Ogretim uyesi guncelleniyor...\n");
									
									printf("Hocalar:\n");
									hocaListedenYazdir(hocaHead);
									printf("Guncellemek istediginiz hocanin idsini girin:");
									scanf("%d",&guncelHocaId);
									int hocaGuncelDurum = hocaGuncelle(hocaHead ,guncelHocaId);
									if(hocaGuncelDurum==1)
									{
										printf("Kayit guncellendi.\n");
										hocaTxtYaz(hocaHead);
									}
									else if(hocaGuncelDurum==-1)
									{
										printf("Kayit guncellenemedi.\n");
									}
									
									printf("Devam etmek icin enter tusuna basiniz.\n");
									getch();
									break;
								case 4://��retim �yesini sil
									printf("Ogretim uyesi siliniyor...\n");
									
									clrBuffer();
									int dersSilK=0;
									int dersSilOnay=0;
									
									printf("Hocalar:\n");
									hocaListedenYazdir(hocaHead);
									printf("Hoca idsini girin:");
									scanf("%d",&hocaSilinecekId);
									hocaHead = hocaSil(hocaHead,hocaSilinecekId);
									hocaTxtYaz(hocaHead);
									do
									{
										printf("Hocanin verdigi dersler silinsinmi? (1-Evet | 0-Hayir)\n");
										printf("Evet secilirse hocanin vermis oldugu dersler ve bu dersi secen ogrencilerin ders secimleri silinecektir.\n");
										printf("Hayir secilirse bosta kalan dersler icin yeni hoca atanmasi istenecektir.Secim:");
										scanf("%d",&dersSilK);
										if(dersSilK==1)
										{
											kontrolOgrenciDersSil(hocaSilinecekId,ogrHead,dersHead);
											dersHead=kontrolDersSil(hocaSilinecekId,dersHead);
											dersTxtYaz(dersHead);
											ogrDerstxtYazdir(ogrHead);
											ogrTxtYaz(ogrHead);
											printf("Hocanin verdigi dersler silindi.\n");
											printf("Hocanin verdigi dersler, ogrencilerin sectigi derslerden silindi.\n");
											dersSilOnay=1;
											
										}
										else if(dersSilK==0)
										{
											kontrolDersBosla(hocaSilinecekId,dersHead);
											struct DERS* hocasizDersler = dersHead;
											while(hocasizDersler != NULL)
											{
												if(hocasizDersler->ogretmenId==-1)
												{
													hocaListedenYazdir(hocaHead);
													printf("%s isimli derse yeni hoca atayiniz. Yeni hoca idsi:",hocasizDersler->dersAd);
													scanf("%d",&hocasizDersler->ogretmenId);
													printf("%s isimli dersin yeni hocasini %d idli hoca olarak atanmistir.\n",hocasizDersler->dersAd,hocasizDersler->ogretmenId);
												}
												hocasizDersler=hocasizDersler->next;
											}
											dersTxtYaz(dersHead);
											dersSilOnay=1;
										}
										else
										{
											dersSilOnay=0;
											printf("Gecersiz secim. Lutfen evet icin 1, hayir icin 0 giriniz.\n");
										}
									}while(dersSilOnay!=1);
									
									printf("Devam etmek icin enter tusuna basiniz.\n");
									getch();
									break;
								default :
									if(giris3==0)
									{
										//�st men�ye y�nel
									}
									else
									{
										printf("Gecersiz secim. Lutfen tekrar secim yapiniz.");
										giris3=-1;
									}
											
							}
										
						}while(giris3!=0);
						
						break;
					case 2://Admin ders men�s�ne gider
						giris3=-1;
						do
						{
							system("cls");
							printf("Admin Menusu -> Ders islemleri\n");
							printf("1 - Dersleri listele\n");
							printf("2 - Ders ekle\n");
							printf("3 - Ders guncelle\n");
							printf("4 - Ders sil\n");
							printf("0 - Ust menuye don\n");
							printf("Secim :");
							scanf("%d",&giris3);
							clrBuffer();
							switch(giris3)
							{
								case 1:
									printf("Dersler listeleniyor...\n");
									
									derslerListedenYazdir(dersHead);
									
									printf("Devam etmek icin enter tusuna basiniz.\n");
									getch();
									break;
								case 2:
									printf("Dersler ekleniyor...\n");
									
									struct DERS yeniDers;
									printf("Ders kodunu giriniz:");
									gets(yeniDers.dersKod);
									printf("Ders adini giriniz:");
									gets(yeniDers.dersAd);
									printf("Dersin kredisini giriniz:");
									scanf("%d",&yeniDers.dersKredi);
									printf("Dersin kontenjanini giriniz:");
									scanf("%d",&yeniDers.dersKontenjan);
									hocaListedenYazdir(hocaHead);
									printf("\nDersi verecek ogretmenin id sini giriniz:\n");
									scanf("%d",&yeniDers.ogretmenId);
									yeniDers.next=NULL;
									dersHead = dersSonaEkle(dersHead,yeniDers.dersKod,yeniDers.dersAd,yeniDers.dersKredi,yeniDers.dersKontenjan,yeniDers.ogretmenId);
									dersTxtYaz(dersHead);
									
									printf("Devam etmek icin enter tusuna basiniz.\n");
									getch();
									break;
								case 3:
									printf("Dersler guncelleniyor...\n");
									
									printf("Dersler:\n");
									derslerListedenYazdir(dersHead);
									printf("Guncellenecek dersin kodunu girin:");
									gets(dersArananId);
									int dersGuncelDurum = dersGuncelle(dersHead,dersArananId,hocaHead);
									if(dersGuncelDurum==1)
									{
										printf("Ders guncellendi...\n");
										dersTxtYaz(dersHead);
									}
									else if(dersGuncelDurum==-1)
									{
										printf("Ders guncelleNEMEdi.\n");
									}
									else
									{
										printf("Beklenmeyen durum olustu...\n");
									}
									
									printf("Devam etmek icin enter tusuna basiniz.\n");
									getch();
									break;
								case 4:
									printf("Dersler siliniyor...\n");
									
									printf("Dersler:\n");
									derslerListedenYazdir(dersHead);
									printf("Silinen ders ogrencilerin secimleri arasindan da silinecektir.\nSilinecek ders kodunu girin:");
									gets(dersSilinecekKod);
									
									ogrSilinenDersCikar(ogrHead,dersSilinecekKod,dersHead);
									dersHead = dersSil(dersHead,dersSilinecekKod);
									dersTxtYaz(dersHead);
									ogrDerstxtYazdir(ogrHead);
									
									printf("Devam etmek icin enter tusuna basiniz.\n");
									getch();
									break;
								default :
									if(giris3==0)
									{
										//�st men�ye y�nel
									}
									else
									{
										printf("Gecersiz secim. Lutfen tekrar secim yapiniz.");
										giris3=-1;
									}
											
							}
										
						}while(giris3!=0);
						
						
						break;
					case 3://Admin ��renci men�s�ne gider
						giris3=-1;
						do
						{
							system("cls");
							printf("Admin Menusu -> Ogrenci islemleri\n");
							printf("1 - Ogrencileri listele\n");
							printf("2 - Ogrencileri ekle\n");
							printf("3 - Ogrencileri guncelle\n");
							printf("4 - Ogrencileri sil\n");
							printf("5 - ogrenciDers.txt dosyasini yazdir\n");
							printf("0 - Ust menuye don\n");
							printf("Secim :");
							scanf("%d",&giris3);
							clrBuffer();
							switch(giris3)
							{
								case 1:
									printf("Ogrenciler listeleniyor...\n");
									
									ogrListedenYazdir(ogrHead);
									
									printf("Devam etmek icin enter tusuna basiniz.\n");
									getch();
									break;
								case 2:
									printf("Ogrenci ekleniyor...\n");
									
									printf("Ogrencinin adini ve soyadini girin:");
									gets(yeniOgrAdSoyad);
									ogrHead = ogrSonaEkle(ogrHead,ogrIdOlustur(ogrHead),yeniOgrAdSoyad);
									ogrTxtYaz(ogrHead);
									
									printf("Devam etmek icin enter tusuna basiniz.\n");
									getch();
									break;
								case 3://Admin ��renci g�ncelliyor
									
									printf("Ogrenciler:\n");
									ogrListedenYazdir(ogrHead);
									printf("\nGuncellemek istediginiz ogrencinin numarasini girin:");
									scanf("%d",&ogrGuncelNo);
									int ogrGuncelDurum = ogrGuncelle(ogrHead,ogrGuncelNo);
									if(ogrGuncelDurum==1)
									{
										printf("Guncelleme basarili...\n");
										ogrTxtYaz(ogrHead);
									}
									else if(ogrGuncelDurum==-1)
									{
										printf("Guncelleme basariSIZ.\n");
									}
									else
									{
										printf("Beklenmedik durum olustu.\n");
									}
									
									printf("Devam etmek icin enter tusuna basiniz.\n");
									getch();
									break;
								case 4://Admin ��renci siliyor
									
									printf("Ogrenciler:\n");
									ogrListedenYazdir(ogrHead);
									printf("\nSilmek istediginiz ogrencinin numarasini girin:");
									scanf("%d",&ogrSilArananNo);
									ogrHead = ogrSil(ogrHead,ogrSilArananNo);
									ogrDerstxtYazdir(ogrHead);
									ogrTxtYaz(ogrHead);
									
									printf("Devam etmek icin enter tusuna basiniz.\n");
									getch();
									break;
								case 5://Admin ogrenci-ders.txt isimli dosyadaki verileri yazd�r�yor.
									printf("Ogrenci-ders.txt listesi yazdiriliyor...\n");
									
									ogrenciDersYazdir();
									
									printf("Devam etmek icin enter tusuna basiniz.\n");
									getch();
									break;
								default :
									if(giris3==0)
									{
										//�st men�ye y�nel
									}
									else
									{
										printf("Gecersiz secim. Lutfen tekrar secim yapiniz.");
										giris3=-1;
									}
											
							}
										
						}while(giris3!=0);
						
						
						break;
					case 4://Admin ��retim �yesinin verdi�i dersleri listeler
						
						printf("Hocalar:\n");
						hocaListedenYazdir(hocaHead);
						printf("\nHocanin verdigi dersleri gormek icin hocanin id sini giriniz:");
						scanf("%d",&hocaDersListeleId);
						struct HOCA* hoca = arananHoca(hocaHead,hocaDersListeleId);
						if(hoca!=NULL)
						{
							printf("%s hocanin verdigi dersler:\n",hoca->adSoyad);
							struct DERS* tmpDersler = dersHead;
							while(tmpDersler != NULL)
							{
								if(tmpDersler->ogretmenId==hoca->id)
								{
									printf("==============================================\n");
									printf("Ders Kodu:%s\n",tmpDersler->dersKod);
									printf("Ders Adi:%s\n",tmpDersler->dersAd);
									printf("Ders Kredisi:%d\n",tmpDersler->dersKredi);
									printf("Ders Kontenjani:%d\n",tmpDersler->dersKontenjan);
									printf("==============================================\n");	
								}
								tmpDersler=tmpDersler->next;
							}
						}
						
						printf("Devam etmek icin enter tusuna basiniz.\n");
						getch();
						break;
					case 5://Admin belli dersi alan t�m ��rencileri listeler
					
						printf("Dersler:\n");
						derslerListedenYazdir(dersHead);
						printf("\nKodu girilen dersi alan ogrenciler listelenecektir.\n");
						printf("Ders kodunu giriniz:");
						gets(dersOgrenciDersKod);
						printf("%s kodlu dersi alan ogrenciler:\n",dersOgrenciDersKod);
						struct OGRENCI *ogrenciTmp = ogrHead;
						while(ogrenciTmp != NULL)
						{
							struct OgrDers *tmpOgrDers = ogrenciTmp->dersHead;
							int dersK = 0;
							while(tmpOgrDers != NULL && dersK==0)
							{
								if(strcmp(tmpOgrDers->dersKod,dersOgrenciDersKod)==0 && tmpOgrDers->durum == 1)
								{
									dersK=1;
								}
								tmpOgrDers = tmpOgrDers->next;
							}
							if(dersK==1)
							{
								printf("%d\t%s\n",ogrenciTmp->ogrNo,ogrenciTmp->ogrAdSoyad);
							}
							
							ogrenciTmp = ogrenciTmp->next;
						}
						
						printf("Devam etmek icin enter tusuna basiniz.\n");
						getch();
						break;
					case 6://Admin belli ��rencinin ald��� t�m dersleri listeler
						printf("Ogrenciler:\n");
						ogrListedenYazdir(ogrHead);
						printf("\nOgrenci numarasini girin:");
						scanf("%d",&ogrenciSecilenDerslerNo);
						struct OGRENCI *tmpOgrenci = ogrHead;
						int ogrKontrol = 0;
						while(tmpOgrenci != NULL && ogrKontrol == 0)
						{
							if(tmpOgrenci->ogrNo==ogrenciSecilenDerslerNo)
							{
								ogrKontrol=1;
							}
							else
							{
								tmpOgrenci = tmpOgrenci->next;
							}
						}
						if(ogrKontrol==1)
						{
							ogrDerslerimYazdir(tmpOgrenci);
						}
						else
						{
							printf("Numarasini girdiginiz ogrenci bulunamdi.\n");
						}
						
						printf("Devam etmek icin enter tusuna basiniz.\n");
						getch();
						break;
					case 7://derskodu_siniflisesi.txt dosyasi yazd�r�l�r.
						
						printf("Hocalar:\n");
						hocaListedenYazdir(hocaHead);
						printf("\nHocanin verdigi dersleri gormek icin hocanin id sini giriniz:");
						scanf("%d",&hocaninDersleriId);
						struct HOCA *hocaGecici = arananHoca(hocaHead,hocaninDersleriId);
						if(hocaGecici!=NULL)
						{
							printf("%s hocanin verdigi dersler:\n",hocaGecici->adSoyad);
							struct DERS* tmpDersler2 = dersHead;
							while(tmpDersler2 != NULL)
							{
								if(tmpDersler2->ogretmenId==hocaGecici->id)
								{
									printf("==============================================\n");
									printf("Ders Kodu:%s\n",tmpDersler2->dersKod);
									printf("Ders Adi:%s\n",tmpDersler2->dersAd);
									printf("Ders Kredisi:%d\n",tmpDersler2->dersKredi);
									printf("Ders Kodu:%d\n",tmpDersler2->dersKontenjan);
									printf("==============================================\n");	
								}
								tmpDersler2=tmpDersler2->next;
							}
						}
						clrBuffer();
						printf("Sinif listesi olusturmak icin %s hocanin verdigi dersler arasindan ders kodu giriniz:",hocaGecici->adSoyad);
						gets(sinifListesiDersKod);
						
						char dosyaAdi[100];
						strcpy(dosyaAdi,sinifListesiDersKod);
						strcat(dosyaAdi,"_sinifListesi.txt");
						FILE *dosyaYaz;
						dosyaYaz = fopen(dosyaAdi,"a");
						printf("Sinif listesi:\n");
						struct OGRENCI *ogrenciGecici = ogrHead;
						while(ogrenciGecici != NULL)
						{
							struct OgrDers *tmpOgrDersGecici = ogrenciGecici->dersHead;
							int dersK = 0;
							while(tmpOgrDersGecici != NULL && dersK==0)
							{
								if(strcmp(tmpOgrDersGecici->dersKod,sinifListesiDersKod)==0 && tmpOgrDersGecici->durum == 1)
								{
									dersK=1;
								}
								tmpOgrDersGecici = tmpOgrDersGecici->next;
							}
							if(dersK==1)
							{
								fprintf(dosyaYaz,"%d\t%s\n",ogrenciGecici->ogrNo,ogrenciGecici->ogrAdSoyad);
							}
							
							ogrenciGecici = ogrenciGecici->next;
						}
						fclose(dosyaYaz);
						printf("%s isimli dosya yazdirildi. %s kodlu dersin sinif listesi hazir.\n",dosyaAdi,sinifListesiDersKod);
						
						printf("Devam etmek icin enter tusuna basiniz.\n");
						getch();
						break;
					default :
						printf("Defaulta dustu\n");
						if(giris2==0)
						{
							//�st men�ye y�nel
						}
						else
						{
							printf("Gecersiz secim. Lutfen tekrar secim yapiniz.");
							giris2=-1;
						}
				}
			}while(giris2!=0);
			
			giris=-1;
		}
		else if(giris==2)
		{
			system("cls");
			int giris2=-1;
			struct OGRENCI* ogrenci=NULL;
			int ogrNoSayac=0;
			do
			{
				system("cls");
				if(ogrNoSayac!=0)
				{
					if(ogrenci==NULL)
					{
						printf("\n***Girdiginiz ogrenci numarasi yanlis. Lutfen dogru bir numara girin.\n");
					}
				}
				
				ogrListedenYazdir(ogrHead);
				printf("(!!!Dogru numara girene kadar tekrar edecektir. Cikmak icin herhangi bir ogrencinin numarasini girin)\nOgrenci numaranizi girin:");
				scanf("%d",&islemYapanOgrenci);
				ogrenci = girisYapanOgrenci(ogrHead,islemYapanOgrenci);
				
				ogrNoSayac++;
			}while(ogrenci == NULL);
			
			system("cls");
			
			do
			{
				printf("%s - Ogrenci menusune hos geldiniz.\n",ogrenci->ogrAdSoyad);
				printf("Maksimum alabileceginiz kredi 20 dir.\n");
				printf("Secmis oldugunuz ders sayisi: %d\n",ogrenci->dersSayisi);
				printf("Toplam aldiginiz kredi:%d\n",ogrenci->toplamKredi);
				if(ogrenci->toplamKredi<=20)
				{
					int kalanKredi = 20-(ogrenci->toplamKredi);
					printf("%d krediye kadar ders secebilirsiniz.\n",kalanKredi);
				}
				else
				{
					printf("Kredi limitine ulastiginiz icin ders secimi yapamazsiniz. Ders secmek icin once ders cikarip ardindan ekleme yapiniz.\n");
				}
				
				printf("1 - Ders listesi icin\n2 - Ders eklemek icin\n3 - Ders Cikarmak icin\n4 - Sectiginiz dersleri listelemek icin\n");
				printf("0 - Ust menuye donmek icin");
				printf("Secim :");
				scanf("%d",&giris2);
				clrBuffer();
				switch(giris2)
				{
					case 1://��renci ders listesini g�r�r
						printf("Ders Listesi\n");
						
						derslerListedenYazdir(dersHead);
						
						printf("Devam etmek icin enter tusuna basiniz.\n");
						getch();
						break;
					case 2://��renci ders ekler
						printf("Secebileceginiz dersler asagidadir.\n");
						secilebilecekDersler(ogrenci,dersHead);
						printf("Lutfen secmek istediginiz dersin kodunu girin:");
						gets(secilenDersKodu);
						ogrenci->dersHead = ogrDersSonaEkle(ogrenci,dersHead,secilenDersKodu,1,getTime());
						ogrDerstxtYazdir(ogrHead);
						ogrTxtYaz(ogrHead);
						
						printf("Devam etmek icin enter tusuna basiniz.\n");
						getch();
						break;
					case 3://��renci ders ��kar�r
						printf("Secmis oldugunuz dersler:\n");
						ogrDerslerimYazdir(ogrenci);
						printf("Cikarmak istediginiz dersin kodunu girin:");
						gets(cikacakDersKodu);
						ogrDersCikar(ogrenci,cikacakDersKodu,dersHead);
						//ogrKrediDersGuncelle(ogrHead,dersHead);
						ogrDerstxtYazdir(ogrHead);
						ogrTxtYaz(ogrHead);
						
						printf("Devam etmek icin enter tusuna basiniz.\n");
						getch();
						break;
						
					case 4://��renci se�ti�i dersleri yazd�r�r
						ogrDerslerimYazdir(ogrenci);
						
						printf("Devam etmek icin enter tusuna basiniz.\n");
						getch();
						break;
						
					default :
						if(giris2==0)
						{
							//�st men�ye y�nel
						}
						else
						{
							printf("Gecersiz secim. Lutfen tekrar secim yapiniz.");
							giris2=-1;
						}
				}
			}while(giris2!=0);
			
			giris=-1;
		}
	}while(giris!=0);
	
	
	//Verileri temizle
	
	hocaTemizle(hocaHead);
	dersTemizle(dersHead);
	ogrTemizle(ogrHead);
	
	printf("Bellek temizlendi...\n");
	return 0;
}

void dosyaKontrol(char * dosyaAdi){//Program ba�lad��� anda ismi girilen dosyan�n var olup olmad��� kontrol eden fonksiyondur. E�er dosya yoksa olu�turulur.
	/*
	inputlar:
		char* kontrol edilecek dosyan�n ad�
	return:
		void
	*/
	if( access( dosyaAdi, F_OK ) == 0 ) {
    	printf("%s isimli dosya mevcut\n",dosyaAdi);
	} else {
	    printf("Dosya mevcut degil\n");
	    FILE* file_ptr = fopen(dosyaAdi, "w");
    	fclose(file_ptr);
    	printf("Dosya olusturuldu\n");
	}
}

void hocaListedenYazdir(struct HOCA* start){//Hocalar�n bulundu�u linkli listeyi konsol ekran�na yazd�rmak i�in kullan�lan fonksiyondur.
	/*
	inputlar:
		HOCA* hoca linkli listesinin ba�lang�� adresi
	return:
		void
	*/
	struct HOCA* tmp = start;
	while(tmp != NULL)
	{
		printf("%d\t%s %s\n",tmp->id,tmp->unvan,tmp->adSoyad);
		tmp=tmp->next;
	}
}

void ogretimUyesiYazdir(){//hocalar.txt dosyasindan okunan veriler satir satir ekrana yazdirilir.
	satirOku("hocalar.txt");
}

void derslerYazdir(){//dersler.txt dosyasindan okunan veriler satir satir ekrana yazdirilir.
	satirOku("dersler.txt");
}

void ogrencilerYazdir(){//ogrenciler.txt dosyasindan okunan veriler satir satir ekrana yazdirilir.
	satirOku("ogrenciler.txt");
}

void ogrenciDersYazdir(){//ogrenci-ders.txt dosyasindan okunan veriler satir satir ekrana yazdirilir.
	satirOku("ogrenci-ders.txt");
}

int hocaIdAl(struct HOCA* start){
	/*
	inputlar:
		hocalar�n tutuldu�u linli listenin ba�lang�� de�eri
	retrun:
		yeni eklenecek hoca i�in benzersiz id de�eri
	*/
	if(start==NULL)
	{
		return 1;//Hoca eklenmemi�se 1 d�nd�r�lecek.
	}
	else//Hoca eklendiyse en son id 1 artt�rl�p d�nd�r�lecek.
	{
		
		struct HOCA* tmp=start;
		int retId=-1;
		while(tmp != NULL)
		{
			retId=tmp->id;
			tmp=tmp->next;
		}
		retId++;
		return retId;
	}
	
}

void satirOku(char * dosyaAdi){//Txt dosyas�ndan sat�r sat�r de�er okumak i�in kullan�lan fonksiyondur.
	/*
	inputlar:
		okunacak dosyanin ad� al�n�r
	return:
		void
	*/
	FILE *fp = fopen(dosyaAdi, "r");
	if(fp == NULL) {
        perror("Aradiginiz dosya yok. Lutfen once inputlari ekleyiniz. Ardindan menuden 5. secenek ile dosyaya yazdiriniz.\n");
    }
    else
    {
	    char satir[1000];
	    while(fgets(satir, sizeof(satir), fp) != NULL) {
			fputs(satir, stdout);
		}
		fclose(fp);
	}
}

void clrBuffer(){//Buffer bellekte bulunan enter, bo�luk vs karakterleri temizlemek i�in kullan�l�r
	fseek(stdin,0,SEEK_END);
}

struct HOCA* hocaDugumOlustur(int id, char * adSoyad, char * unvan){//Yeni bir hoca eklemek i�in d���m olu�turmaya yarayan fonksiyondur
	/*
	inputlar:
		int eklenecek hocan�n idsi
		char* eklenecek hocan�n ad� ve soyad�
		char* eklenecek hocan�n �nvan�
	return:
		HOCA* olu�turulan yeni d���m�n adresi
	*/
    struct HOCA* yeniDugum = (struct HOCA*) malloc(sizeof(struct HOCA));
    yeniDugum->next = NULL;
    yeniDugum->id = id;
    strcpy(yeniDugum->adSoyad,adSoyad);
    strcpy(yeniDugum->unvan,unvan);
    return yeniDugum;
}


struct HOCA* hocaSonaEkle(struct HOCA* start,int id, char * adSoyad, char * unvan){//Yeni hoca eklemek i�in linkli listenin sonuna yeni bir d���m eklenir.
	/*
	inputlar:
		HOCA* hoca linkli listesinin ba�lang�� de�eri
		int yeni hocan�n id si
		char * yeni hocan�n ad� ve soyad�
		char * hocan�n �nvan�
	return:
		HOCA* linkli listenin ba�lang�� de�eri
	*/
    struct HOCA* sonaEklenecek = hocaDugumOlustur(id,adSoyad,unvan);
 
    if (start == NULL)//Listemizin i�erisinde hi� eleman yoksa ilk eleman�m�z� ekliyoruz
    {
        start = sonaEklenecek;
    }
 
    else//E�er liste i�erisinde eleman varsa
    {	
	    struct HOCA* tmp = start;
	    while(tmp->next != NULL)
	    {
	    	tmp=tmp->next;
		}
		tmp->next=sonaEklenecek;
    }
    
    printf("%s isimli hoca eklendi...\n",adSoyad);
    return start;
}


int hocaGuncelle(struct HOCA* start,int arananId){//Mevcut bir hocan�n ad�n� soyad�n� ve �nvan�n� g�ncellemek i�in kullan�l�r.
	/*
	inputlar:
		HOCA* hocalar linkli listesinin ba�lang�� de�eri
		int g�ncellenecek olan hocan�n id si
	return
		int 1=g�ncelleme ba�ar�l� , -1=g�ncelleme ba�ar�s�z
	*/
	struct HOCA* tmp = start;
	int kontrol=0;
	char yeniAdSoyad[100];
	char yeniUnvan[100];
	
	while(tmp != NULL && kontrol ==0 )
	{
		if(tmp->id==arananId)
		{
			clrBuffer();
			kontrol=1;
			printf("Guncel bilgiler...\nDegistirmek istemiyorsaniz eski halini girin.");
			printf("Yeni ad ve soyad girin:");
			gets(yeniAdSoyad);
			printf("Yeni unvan girin:");
			gets(yeniUnvan);
			strcpy(tmp->adSoyad,yeniAdSoyad);
			strcpy(tmp->unvan,yeniUnvan);
			return 1;
		}
		
		tmp=tmp->next;
	}
	return -1;
}

void hocaTemizle(struct HOCA* start){//Program kapat�l�rken bellekte hocalara ayr�lan alan�n i�letim sistemine b�rak�lmas� i�in kullan�l�r.
	/*
	inputlar:
		HOCA* hocalar linkli listesinin ba�lang�� adresi
	return:
		void
	*/
	struct HOCA* tmp;
	while(start != NULL)
	{
		tmp = start;
		start = start->next;
		free(tmp);
	}
	printf("Hocalar temizlendi.\n");
}

void hocaTxtYaz(struct HOCA* start){//Hocalar� txt dosyas�na kaydetmek i�in kullan�lan fonksiyondur.
	/*
	inputlar:
		HOCA* hocalar linkli listesinin ba�lang�� adresi
	return:
		void
	*/
	int i=0;
	struct HOCA* tmp = start;
	FILE *dosya_yaz;
	dosya_yaz = fopen("hocalar.txt","w");
	while(tmp != NULL)
	{
		fprintf(dosya_yaz,"%d\t%s\t%s\n",tmp->id,tmp->adSoyad,tmp->unvan);
		tmp=tmp->next;
	}
	fclose(dosya_yaz);
	
}


struct HOCA* hocaSil(struct HOCA* start,int hocaId){//Id si girilen hocay� silmek i�in kullan�l�r
	/*
	inputlar:
		HOCA* hocalar linkli listesinin ba�lang�� adresi
		int aranan hocan�n id si
	return:
		HOCA* hocalar linkli listesinin ba�lang�� de�eri
	*/
	int kayitKontrol=0;
	struct HOCA* head = start;
	if(head->id==hocaId)
	{
		struct HOCA* tmp=start->next;
		head=tmp;
		free(start);
		//Headi de�i�tir
		kayitKontrol=1;
		printf("Kayit silindi. Head degisti.\n");
	}
	else
	{
		struct HOCA* tmp = start;
		while(tmp != NULL && kayitKontrol==0)
		{
			struct HOCA* tmp2 = tmp->next;
			if(tmp2->id==hocaId)
			{
				tmp->next=tmp2->next;
				free(tmp2);
				kayitKontrol=1;
				printf("Kayit silindi.\n");
			}
			tmp=tmp->next;
		}
	}
	if(kayitKontrol==0)
	{
		printf("Kayit bulunamadi.\n");
	}
	
	return head;
}

struct HOCA* hocaBaslangic(struct HOCA* start){//Program ba�lat�ld��� anda txt dosyas�nda kay�tl� olan hocalar i�in yeni linkli liste olu�turuluyor ve tekrar tekrar veri girilmesi engelleniyor
	/*
	inputlar:
		HOCA* hocalar linkli listesinin ba�lang�� adresi
	return:
		HOCA* hocalar linkli listesinin ba�lang�� adresi
	*/
	struct HOCA* head = start;
	int sayac=0;
	struct HOCA yeniHoca;
	FILE *fp = fopen("hocalar.txt", "r");
	if(fp == NULL) {
        perror("hocalar.txt isimli dosya bulunamadi. Lutfen yeni hocalari kaydedin.\n");
    }
    else
    {
	    char satir[1000];
	    while(fgets(satir, sizeof(satir), fp) != NULL) {
	    	int len=strlen(satir);
	    	satir[len-1]='\0';
	    	int sayac=0;
			char delim[] = "\t";
			char *ptr = strtok(satir, delim);
			while(ptr != NULL)
			{
				if(sayac==0)
				{
					yeniHoca.id=atoi(ptr);
				}
				else if(sayac==1)
				{
					strcpy(yeniHoca.adSoyad,ptr);
				}
				else if(sayac==2)
				{
					strcpy(yeniHoca.unvan,ptr);
				}
				ptr = strtok(NULL, delim);
				sayac++;
			}
			
			head = hocaSonaEkle(head,yeniHoca.id,yeniHoca.adSoyad,yeniHoca.unvan);
		}
		fclose(fp);
		
	}
	return head;
}


//DERSLER B�L�M�


struct DERS* dersDugumOlustur(char * dersKod, char * dersAd, int dersKredi, int dersKontenjan, int ogretmenId){//Eklenecek ders i�in yeni bir d���m olu�turulmas�n� sa�layan fonksiyondur.
	/*
	inputlar:
		char* eklenecek olan dersin ders kodu
		char* eklenecek olan dersin ad�
		int eklenecek olan dersin kredisi
		int eklenecek olan dersin kontenjan�
		int dersi verecek olan hocan�n idsi
	return:
		DERS* olu�turulan d���m�n adresi
	*/
    struct DERS* yeniDugum = (struct DERS*) malloc(sizeof(struct DERS));
    yeniDugum->next = NULL;
    strcpy(yeniDugum->dersKod,dersKod);
    strcpy(yeniDugum->dersAd,dersAd);
    yeniDugum->dersKredi=dersKredi;
    yeniDugum->dersKontenjan=dersKontenjan;
    yeniDugum->ogretmenId=ogretmenId;
    
    
    return yeniDugum;
}

struct DERS* dersSonaEkle(struct DERS* start,char * dersKod, char * dersAd, int dersKredi, int dersKontenjan, int ogremenId){//DERS linkli listesinin sonuna yeni bir ders eklenmesi
    /*
	inputlar:
		DERS* dersler linkli listesinin ba�lang�� de�eri
		char* eklenecek olan dersin kodu
		char* eklenecek olan dersin ad�
		int eklenecek olan dersin kredisi
		int eklenecek dersin kontenjan�
		int eklenecek dersi veren hocan�n idsi
	return:
		DERS* dersler linkli listesinin ba�lang�� adresi
	*/
	struct DERS* sonaEklenecek = dersDugumOlustur(dersKod,dersAd,dersKredi,dersKontenjan,ogremenId);    
    if (start == NULL)
    {
        start = sonaEklenecek;
    }
 
    else
    {	
	    struct DERS* tmp = start;
	    while(tmp->next != NULL)
	    {
	    	tmp=tmp->next;
		}
		tmp->next=sonaEklenecek;
    }
    
    printf("%s isimli ders eklendi...\n",dersAd);
    return start;
}

void derslerListedenYazdir(struct DERS* start){//Dersler linkli listenin konsol ekran�na yazd�r�lmas� i�in kullan�lan fonksiyondur.
	/*
	inputlar:
		DERS* dersler linkli listesinin ba�lang�� adresi
	return:
		void
	*/
	struct DERS* tmp = start;
	while(tmp != NULL)
	{
		printf("=========================================\n");
		printf("Ders Kodu:%s\n",tmp->dersKod);
		printf("Ders Adi:%s\n",tmp->dersAd);
		printf("Ders Kredisi:%d\n",tmp->dersKredi);
		printf("Ders Kontenjani:%d\n",tmp->dersKontenjan);
		printf("Ders Yurutucusu Id:%d\n",tmp->ogretmenId);
		printf("=========================================\n");
		tmp=tmp->next;
	}
}

int dersGuncelle(struct DERS* start,char * arananId,struct HOCA* hocaHead){//Ders kodu girilen dersin verilerini g�ncellemek i�in kullan�lan fonksiyondur.
	/*
	inputlar:
		DERS* dersler linkli listesinin ba�lang�� adresi
		char* aranan dersin ders kodu
		HOCA* hocalar linkli listesinin ba�lang�� de�eri
	return:
		int 1=g�ncelleme ba�ar�l�,-1=g�ncelleme ba�ar�s�z
	*/
	struct DERS* tmp = start;
	int kontrol=0;
	char yenidersAdi[100];
	
	while(tmp != NULL && kontrol ==0 )
	{
		if(strcmp(tmp->dersKod,arananId)==0)
		{
			clrBuffer();
			kontrol=1;
			printf("Guncel bilgiler...\nDegistirmek istemiyorsaniz eski halini girin.");
			printf("Yeni ders adini girin(Eskisi:%s):",tmp->dersAd);
			gets(yenidersAdi);
			strcpy(tmp->dersAd,yenidersAdi);
			printf("Yeni ders kredisini girin(Eskisi:%d):",tmp->dersKredi);
			scanf("%d",&tmp->dersKredi);
			printf("Yeni ders kontenjanini girin(Eskisi:%d):",tmp->dersKontenjan);
			scanf("%d",&tmp->dersKontenjan);
			hocaListedenYazdir(hocaHead);
			printf("\nYeni ders yurutucusunun id sini girin(Eskisi:%d):",tmp->ogretmenId);
			scanf("%d",&tmp->ogretmenId);
			return 1;
		}
		
		tmp=tmp->next;
	}
	return -1;
}

void dersTxtYaz(struct DERS* start){//Dersler linkli listesindeki derslerin dersler.txt dosyas�na yaz�lmas� i�in kullan�lan fonksiyondur.
	/*
	inputlar:
		DERS* dersler linkli listesinin ba�lang�� de�eri
	return:
		void
	*/
	struct DERS* tmp = start;
	FILE *dosya_yaz;
	dosya_yaz = fopen("dersler.txt","w");
	while(tmp != NULL)
	{
		fprintf(dosya_yaz,"%s\t%s\t%d\t%d\t%d\n",tmp->dersKod,tmp->dersAd,tmp->dersKredi,tmp->dersKontenjan,tmp->ogretmenId);
		tmp=tmp->next;
	}
	fclose(dosya_yaz);
}

struct DERS* dersBaslangic(struct DERS* start){//Program ba�lat�ld��� anda dersler.txt dosyas�ndan linkli listesinin doldurulmas� i�in kullan�lan fonksiyondur.
	/*
	inputlar:
		DERS* dersler linkli listesinin ba�lang�� de�eri
	return:
		DERS* dersler linkli listesinin ba�lang�� de�eri
	*/
	struct DERS* head = start;
	int sayac=0;
	struct DERS yeniDers;
	FILE *fp = fopen("dersler.txt", "r");
	if(fp == NULL) {
        perror("Aradiginiz dosya yok. Lutfen once inputlari ekleyiniz. Ardindan menuden 5. secenek ile dosyaya yazdiriniz.\n");
    }
    else
    {
	    char satir[1000];
	    while(fgets(satir, sizeof(satir), fp) != NULL) {
	    	int len=strlen(satir);
	    	satir[len-1]='\0';
	    	int sayac=0;
			char delim[] = "\t";
			char *ptr = strtok(satir, delim);
			while(ptr != NULL)
			{
				if(sayac==0)
				{
					printf("Ders Kod : %s",ptr);
					strcpy(yeniDers.dersKod,ptr);
				}
				else if(sayac==1)
				{
					printf("Ders Ad: %s",ptr);
					strcpy(yeniDers.dersAd,ptr);
				}
				else if(sayac==2)
				{
					yeniDers.dersKredi=atoi(ptr);
				}
				else if(sayac==3)
				{
					yeniDers.dersKontenjan=atoi(ptr);
				}
				else if(sayac==4)
				{
					yeniDers.ogretmenId=atoi(ptr);
				}
				//printf("-%s-", ptr);
				ptr = strtok(NULL, delim);
				sayac++;
			}
			
			//head = hocaSonaEkle(head,yeniHoca.id,yeniHoca.adSoyad,yeniHoca.unvan);
			head = dersSonaEkle(head,yeniDers.dersKod,yeniDers.dersAd,yeniDers.dersKredi,yeniDers.dersKontenjan,yeniDers.ogretmenId);
		}
		fclose(fp);
		
	}
	return head;
}

struct DERS* dersSil(struct DERS* start,char * dersKod){//Listeden ders silmek i�in kullan�l�r.
	/*
	inputlar:
		DERS* dersler linkli listesinin ba�lang�� de�eri
		char* silinecek olan dersin kodu
	return:
		DERS* dersler linkli listesinin ba�lang�� de�eri
	*/
	int kayitKontrol=0;
	struct DERS* head = start;
	if(strcmp(head->dersKod,dersKod)==0)
	{
		//Head de�i�tirilmeli
		struct DERS* tmp=start->next;
		head=tmp;
		free(start);
		kayitKontrol=1;
		printf("Kayit silindi.\n");
	}
	else
	{
		struct DERS* tmp = start;
		while(tmp != NULL && kayitKontrol==0)
		{
			struct DERS* tmp2 = tmp->next;
			if(strcmp(tmp2->dersKod,dersKod)==0)
			{
				tmp->next=tmp2->next;
				free(tmp2);
				kayitKontrol=1;
				printf("Kayit silindi.\n");
			}
			tmp=tmp->next;
		}
	}
	if(kayitKontrol==0)
	{
		printf("Kayit bulunamadi.\n");
	}
	
	return head;
}

struct DERS* dersGetir(struct DERS* start,char * dersKod){
	
	int kayitKontrol=0;
	struct DERS* head = start;
	while(head != NULL)
	{
		if(strcmp(head->dersKod,dersKod)==0)
		{
			return head;
		}
		else
		{
			head = head->next;	
		}
	}
	
	return head;
}

void dersTemizle(struct DERS* start){//Program kapat�l�rken bellekte me�gul edilen alan�n tekrar i�letim sistemine b�rak�lmas� i�in kullan�lan fonksiyon
	/*
	inputlar:
		DERS* dersler linkli listesinin ba�lang�� de�eri
	return:
		void
	*/
	struct DERS* tmp;
	while(start != NULL)
	{
		tmp = start;
		start = start->next;
		free(tmp);
	}
	printf("Dersler temizlendi.\n");
}


//��renci Fonksiyonlar�


struct OGRENCI* ogrDugumOlustur(int ogrNo, char * ogrAdSoyad){//Linkli listeye yeni bir ��renci eklenebilmesi i�in bellekte yer ayr�l�yor.
	/*
	inputlar:
		int eklenecek ��rencinin numaras�
		char* eklenecek ��rencinin ad� ve soyad�
	return:
		OGRENCI* olu�turulan d���m�n adresi
	*/
    struct OGRENCI* yeniDugum = (struct OGRENCI*) malloc(sizeof(struct OGRENCI));
    
	yeniDugum->ogrNo=ogrNo;
    strcpy(yeniDugum->ogrAdSoyad,ogrAdSoyad);
    yeniDugum->dersSayisi=0;
    yeniDugum->toplamKredi=0;
    yeniDugum->dersHead=NULL;
    yeniDugum->next = NULL;
    
    
    return yeniDugum;
}


struct OGRENCI* ogrSonaEkle(struct OGRENCI* start,int ogrNo, char * ogrAdSoyad){//Linkli listenin sonuna yeni bir ��renci eklemek i�in kullan�lan fonksiyondur.
	/*
	inputlar:
		OGRENCI* ��renciler linkli listesinin ba�lang�� de�eri
		int ��renci numaras�
		int ��rencinin ad� ve soyad�
	return:
		OGRENCI* ��renciler linkli listesinin ba�lang�� de�eri
	*/
    struct OGRENCI* sonaEklenecek = ogrDugumOlustur(ogrNo,ogrAdSoyad);
    if (start == NULL)
    {
        start = sonaEklenecek;
    }
    else
    {	
	    struct OGRENCI* tmp = start;
	    while(tmp->next != NULL)
	    {
	    	tmp=tmp->next;
		}
		tmp->next=sonaEklenecek;
    }
    printf("%d nolu ve %s isimli ogrenci eklendi...\n",ogrNo,ogrAdSoyad);
    return start;
}

int ogrIdOlustur(struct OGRENCI* start){//Yeni olu�turulacak ��renci i�in ��renci numaras�n�n tahsis edilmesi
	/*
	inputlar:
		OGRENCI* ��renciler linkli listesinin ba�lang�� de�eri
	return:
		int olu�turulan ��renci idsi
	*/
	int yeniId=0;
	struct OGRENCI* tmp = start;
	if(tmp==0)
	{
		yeniId = 2111001;//�lk ��renci i�in haz�rlanm�� baz de�er
	}
	else
	{
		while(tmp->next != NULL)
		{
			tmp=tmp->next;
		}
		yeniId=(tmp->ogrNo)+1;
	}
	return yeniId;
}

void ogrListedenYazdir(struct OGRENCI* start){//��renciler linkli listesinin konsola yazd�r�lmas� i�in kullan�l�r.
	/*
	inputlar:
		OGRENCI* ��renciler linkli listesinin ba�lang�� de�eri
	return:
		void
	*/
	struct OGRENCI* tmp = start;
	while(tmp != NULL)
	{
		printf("=========================================\n");
		printf("Ogrenci No:%d\n",tmp->ogrNo);
		printf("Ogrenci Ad Soyad:%s\n",tmp->ogrAdSoyad);
		printf("Ogrencinin aldigi ders sayisi:%d\n",tmp->dersSayisi);
		printf("Ogrencinin aldigi toplam kredi:%d\n",tmp->toplamKredi);
		printf("=========================================\n");
		tmp=tmp->next;
	}
}

void ogrTemizle(struct OGRENCI* start){//Program kapat�l�rken ��renciler linkli listesine tahsis edilmi� alan�n tekrar i�letim sistemine b�rak�lmas� i�in kullan�l�r.
	/*
	inputlar:
		OGRENCI* ��renciler linkli listesinin ba�lang�� de�eri
	return:
		void
	*/
	struct OGRENCI* tmp;
	while(start != NULL)
	{
		tmp = start;
		start = start->next;
		free(tmp);
	}
	printf("Ogrenciler temizlendi.\n");
}

int ogrGuncelle(struct OGRENCI* start,int arananNo){//�d si girilen ��rencinin ad�n� ve soyad�n� g�ncellemek i�in kullan�lan fonksiyondur. Geri kalan de�erler yap�lan i�lemler �er�evesinde otomatik olarak g�ncellenmektedir.
	/*
	inputlar:
		OGRENCI* ��renciler linkli listesinin ba�lang�� de�eri
		int aranan ��rencinin idsi
	return:
		int 1=g�ncelleme ba�ar�l� ise, -1=g�ncelleme ba�ar�s�z ise
	*/
	struct OGRENCI* tmp = start;
	int kontrol=0;
	char yeniOgrAdi[100];
	
	while(tmp != NULL && kontrol ==0 )
	{
		if(tmp->ogrNo == arananNo)
		{
			clrBuffer();
			kontrol=1;
			printf("Guncel bilgiler...\nDegistirmek istemiyorsaniz eski halini girin.");
			printf("Ogrencinin yeni adini girin(Eskisi:%s):",tmp->ogrAdSoyad);
			gets(yeniOgrAdi);
			strcpy(tmp->ogrAdSoyad,yeniOgrAdi);
			printf("NOT: Ogrencinin sadece adi ve soyadi guncellenmektedir. No bilgisi otomatik atanmaktadir.\nAldigi toplam ders kredisi ve ders sayisi sistem tarafindan otomatik guncellenmektedir.\n");
			return 1;
		}
		
		tmp=tmp->next;
	}
	return -1;
}

struct OGRENCI* ogrSil(struct OGRENCI* start,int ogrNo){//�d si girilen ��renciyi silmek i�in kullan�l�r
	/*
	inputlar:
		OGRENCI* ��renciler linkli listesinin ba�lang�� de�eri
		int silinecek ��rencinin idsi
	return:
		OGRENCI* ��renci linkli listesinin ba�lang�� de�eri
	*/
	int kayitKontrol=0;
	struct OGRENCI* head = start;
	if(head->ogrNo==ogrNo)
	{
		struct OGRENCI* tmp=start->next;
		head=tmp;
		tmp->dersHead=NULL;
		
		free(start);
		//Headi de�i�tir
		kayitKontrol=1;
		printf("Kayit silindi. Head degisti.\n");
	}
	else
	{
		struct OGRENCI* tmp = start;
		while(tmp != NULL && kayitKontrol==0)
		{
			struct OGRENCI* tmp2 = tmp->next;
			if(tmp2->ogrNo==ogrNo)
			{
				tmp->next=tmp2->next;
				tmp2->dersHead=NULL;
				free(tmp2);
				kayitKontrol=1;
				printf("Kayit silindi.\n");
			}
			tmp=tmp->next;
		}
	}
	if(kayitKontrol==0)
	{
		printf("Kayit bulunamadi.\n");
	}
	
	return head;
}



void ogrTxtYaz(struct OGRENCI* start){//Linkli listedeki ��rencilerin ogrenciler.txt isimli dosyaya yaz�lmas�n� sa�layan fonksiyondur.
	/*
	inputlar:
		OGRENCILER* ��renciler linkli listesinin ba�lang�� adresi
	return:
		void
	*/
	struct OGRENCI* tmp = start;
	FILE *dosya_yaz;
	dosya_yaz = fopen("ogrenciler.txt","w");
	while(tmp != NULL)
	{
		fprintf(dosya_yaz,"%d\t%s\t%d\t%d\n",tmp->ogrNo,tmp->ogrAdSoyad,tmp->dersSayisi,tmp->toplamKredi);
		tmp=tmp->next;
	}
	fclose(dosya_yaz);
}

struct OGRENCI* ogrBaslangic(struct OGRENCI* start){//Program ba�lat�ld��� anda ��renciler i�in linkli liste olu�turulur ve ogrenciler.txt dosyas�ndaki de�erler bu linkli listeye eklenir.
	/*
	inputlar:
		OGRENCI* ��renciler linkli listesinin ba�lang�� de�eri
	return:
		OGRENCI* ��renciler linkli listesinin ba�lang�� de�eri
	*/
	struct OGRENCI* head = start;
	int sayac=0;
	struct OGRENCI yeniOgrenci;
	FILE *fp = fopen("ogrenciler.txt", "r");
	if(fp == NULL) {
        perror("Aradiginiz dosya yok. Lutfen once inputlari ekleyiniz. Ardindan menuden 5. secenek ile dosyaya yazdiriniz.\n");
    }
    else
    {
	    char satir[1000];
	    while(fgets(satir, sizeof(satir), fp) != NULL) {
	    	int len=strlen(satir);
	    	satir[len-1]='\0';
	    	int sayac=0;
			char delim[] = "\t";
			char *ptr = strtok(satir, delim);
			printf("Satir verisi:%s\n",satir);
			while(ptr != NULL)
			{
				if(sayac==0)
				{
					yeniOgrenci.ogrNo=atoi(ptr);
					printf("No:%d-",yeniOgrenci.ogrNo);
				}
				else if(sayac==1)
				{
					strcpy(yeniOgrenci.ogrAdSoyad,ptr);
					printf("AdSoyad:%s-",yeniOgrenci.ogrAdSoyad);
				}
				else if(sayac==2)
				{
					//yeniOgrenci.dersSayisi=atoi(ptr);
					yeniOgrenci.dersSayisi=0;
					printf("DersSayisi:%d-",yeniOgrenci.dersSayisi);
				}
				else if(sayac==3)
				{
					//yeniOgrenci.toplamKredi=atoi(ptr);
					yeniOgrenci.toplamKredi=0;
					printf("ToplamKredi:%d\n",yeniOgrenci.toplamKredi);
				}
				//printf("-%s-", ptr);
				ptr = strtok(NULL, delim);
				sayac++;
			}
			
			
			//printf("%d")
			head = ogrBaslangicSonaEkle(head,yeniOgrenci.ogrNo,yeniOgrenci.ogrAdSoyad,yeniOgrenci.dersSayisi,yeniOgrenci.toplamKredi);
		}
		fclose(fp);
		
	}
	return head;
}

struct OGRENCI* ogrBaslangicDugumOlustur(int ogrNo, char * ogrAdSoyad,int dersSayisi,int dersKredi){//Ba�lang��taki ��renci eklemeleri i�in ��renci ba��na yeni bir d���m olu�turan fonksiyondur.
	/*
	inputlar:
		int ��renci no
		int ��renci ad� soyad�
		int ��rencinin se�ti�i ders say�s�
		int ��rencinin se�ti�i derslerin toplam kredi de�eri
	return:
		OGRENCI* olu�turulan ��renci d���m�n�n adresi
	*/
    struct OGRENCI* yeniDugum = (struct OGRENCI*) malloc(sizeof(struct OGRENCI));
	yeniDugum->ogrNo=ogrNo;
    strcpy(yeniDugum->ogrAdSoyad,ogrAdSoyad);
    yeniDugum->dersSayisi=dersSayisi;
    yeniDugum->toplamKredi=dersKredi;
    yeniDugum->dersHead=NULL;
    yeniDugum->next = NULL;
    
    
    return yeniDugum;
}


struct OGRENCI* ogrBaslangicSonaEkle(struct OGRENCI* start,int ogrNo, char * ogrAdSoyad,int dersSayisi,int dersKredi){//��renciler linkli listesinin sonuna ba�lang��ta yeni bir ��renci eklenmesi i�in kullan�lan fonksiyondur
	/*
	inputlar:
		OGRENCI* ��renciler linkli listesinin ba�lang�� de�eri
		int ��renci numaras�
		char* ��renci ad� ve soyad�
		int ��rencinin se�mi� oldu�u ders say�s�
		int ��rencinin se�mi� oldu�u derslerin toplam kredi de�eri
	return:
		OGRENCI* ��renci linkli listesinin ba�lang�� de�eri
	*/	
    struct OGRENCI* sonaEklenecek = ogrBaslangicDugumOlustur(ogrNo,ogrAdSoyad,dersSayisi,dersKredi);
    if (start == NULL)
    {
        start = sonaEklenecek;
        printf("BASA EKLENDI\n");
    }
    else
    {	
	    struct OGRENCI* tmp = start;
	    while(tmp->next != NULL)
	    {
	    	tmp=tmp->next;
		}
		tmp->next=sonaEklenecek;
    }
    printf("**********%d - %s\n",start->ogrNo,start->ogrAdSoyad);
    printf("%d nolu ve %s isimli ogrenci eklendi...\n",ogrNo,ogrAdSoyad);
    return start;
}


struct OGRENCI* girisYapanOgrenci(struct OGRENCI* start,int ogrNo){//��renci ders se�erken sisteme giri� yapmal�d�r. Girdigi numaras�na g�re giri� yapan ��renciyi d�nd�ren fonksiyondur.
	/*
	inputlar:
		OGRENCI* ��renciler linkli listesinin ba�lang�� de�eri
		int giri� yapacak olan ��rencinin numaras�
	return:
		OGRENCI* ��renci bulunduysa giri� yapan ��rencinin adresi, NULL-> ��renci bulunamam��t�r. Bu durumda tekrar giri� yapmas� istenecek
	*/
	struct OGRENCI* tmp = start;
	struct OGRENCI* bulunan=NULL;
	int kontrol=0;
	while(tmp != NULL && kontrol==0)
	{
		if(tmp->ogrNo==ogrNo)
		{
			bulunan = tmp;
		}
		tmp=tmp->next;
	}
	if(bulunan != NULL)
	{
		return bulunan;
	}
	else
	{
		return NULL;
	}
	
}

char *getTime(){//�u an�n tarihini string olarak d�nd�ren fonksiyondur.
	time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return asctime(tm);
}


//Ogrenci men�s� i� se�im fonksiyonlar�


void secilebilecekDersler(struct OGRENCI *ogrenci,struct DERS* dersStart){//��rencinin, �artlar�n izin verdi�i se�ebilece�i dersleri ekrana yazd�ran fonksiyondur.
	/*
	inputlar:
		OGRENCI* ��renci linkli listesinin ba�lang�� de�eri
		DERS* dersler linkli listesinin ba�lang�� de�eri
	return:
		void
	*/
	struct OgrDers *tmpOgr = ogrenci->dersHead;
	struct DERS *tmpDers = dersStart;
	int dersKontrol = 0;
	
	if(tmpOgr != NULL)//Daha �nce ders se�ilmi�tir. Kalan dersler yazd�r�l�r.
	{
		while(tmpDers != NULL)
		{
			tmpOgr = ogrenci->dersHead;
			dersKontrol=0;
			while(tmpOgr != NULL && dersKontrol==0)
			{
				if((strcmp(tmpDers->dersKod,tmpOgr->dersKod)==0) && tmpOgr->durum != 0)
				{
					dersKontrol=1;
				}
				tmpOgr=tmpOgr->next;
			}
			if(dersKontrol!=1)
			{
				printf("====================================================\n");
				printf("Ders Kodu : %s\nDers Ad�:%s\nDers Kredisi:%d\nDers Kontenjani:%d\nDers Yurutucu Id:%d\n",
				tmpDers->dersKod,
				tmpDers->dersAd,
				tmpDers->dersKredi,
				tmpDers->dersKontenjan,
				tmpDers->ogretmenId);
				printf("====================================================\n");
			}
			tmpDers=tmpDers->next;
		}	
	}
	else//Daha �nce ders se�ilmemi�tir. T�m dersler yazd�r�l�r.
	{
		derslerListedenYazdir(dersStart);
	}
	
}

void ogrDerslerimYazdir(struct OGRENCI *gelenOgrenci){//��rencinin se�mi� oldu�u dersleri ekrana yazd�ran fonksiyondur
	/*
	inputlar:
		OGRENCI* sisteme giri� yapan ��renci
	return:
		void
	*/
	struct OgrDers *tmp = gelenOgrenci->dersHead;
	printf("Sectiginiz dersler:\n");
	while(tmp != NULL)
	{
		if(tmp->durum==1)
		{
			printf("Ders Kod:%s - Durum:%d - Tarih:%s\n",tmp->dersKod,tmp->durum,tmp->tarih);
		}
		tmp = tmp->next;
	}
}

struct OgrDers* ogrDersDugumOlustur(int ogrNo,char * dersKod, int durum, char * tarih){//��rencinin se�ti�i ders i�in d���m olu�turulmas�n� sa�layan fonksiyondur.
	/*
	inputlar:
		int ��renci numaras�
		char* dersin kodu
		int dersin durumu(1=ders se�ildi| 0=ders ��kar�ld�)
		char* i�lem yap�lan tarih
	return:
		OGRENCI* olu�turulan d���m�n adresi
	*/
    struct OgrDers* yeniDugum = (struct OgrDers*) malloc(sizeof(struct OgrDers));
    yeniDugum->ogrNo=ogrNo;
    strcpy(yeniDugum->dersKod,dersKod);
    yeniDugum->durum=durum;
    strcpy(yeniDugum->tarih,tarih);
    yeniDugum->next = NULL;
    
    
    return yeniDugum;
}


struct OgrDers* ogrDersSonaEkle(struct OGRENCI *ogrenci,struct DERS *dersHead,char * dersKod,int durum, char * tarih){//��renciye yeni ders eklenmesi i�in kullan�lan fonksiyondur.
	/*
	inputlar:
		OGRENCI* ekleme yap�lacak ��rencinin adresi
		DERS* ders linkli listesinin ba�lang�� adresi
		char* eklenecek dersin kodu
		int eklenecek dersin durumu (1=ders eklendi | 0=ders ��kar�ld�)
		char* i�lem yap�lan tarih
	return:
		OgrDers* ��renci->OgrDers ba�lang�� de�eri
	*/
	char tarih2[100];
	strcpy(tarih2,tarih);
	int tarihLen = strlen(tarih2);
	tarih2[tarihLen-1]='\0';
	int dersKontrol=0;
	int dersDurum = 0;
	struct DERS *tmpDers = dersHead;
	while(tmpDers != NULL && dersKontrol == 0)//Dersi bulmak i�in kullan�l�r
	{
		//printf("tmpDers:%s - dersKod:%s\n",tmpDers->dersKod,dersKod);
		if(strcmp(tmpDers->dersKod,dersKod)==0)
		{
			dersKontrol=1;
		}
		else
		{
			tmpDers=tmpDers->next;
		}
	}
	if(dersKontrol==1)//E�er ders bulunduysa
	{
		struct OgrDers *tmpDersDurum = ogrenci->dersHead;
		while(tmpDersDurum != NULL && dersDurum==0)//��rencide bulunan dersin durumu kontrol edilir
		{
			if(strcmp(dersKod,tmpDersDurum->dersKod)==0)
			{
				dersDurum=1;
			}
			else
			{
				tmpDersDurum=tmpDersDurum->next;	
			}
		}
		if(dersDurum==1)
		{
			//Durumu g�ncelle
			if((tmpDers->dersKredi+ogrenci->toplamKredi)<=20)//Kredi izin veriyor mu
			{
				tmpDersDurum->durum=1;
				ogrenci->dersSayisi++;
				ogrenci->toplamKredi+=tmpDers->dersKredi;
				printf("Dersin durumu aktife cevrildi.\n");
			}
			else
			{
				printf("Gerekli kosullari saglamiyorsunuz.\n");
			}
		}
		else
		{
			//yeni ekleme yap
			if((tmpDers->dersKredi+ogrenci->toplamKredi)<=20)//Ders se�ilebilir
			{
				struct OgrDers *sonaEklenecek = ogrDersDugumOlustur(ogrenci->ogrNo,dersKod,durum,tarih2);
			    //printf("\tFonksiyon i�i Ogrenci->dersHead:%p\n",ogrenci->dersHead);
			    if (ogrenci->dersHead == NULL)
			    {
			        ogrenci->dersHead = sonaEklenecek;
			        ogrenci->dersSayisi++;
					ogrenci->toplamKredi+=tmpDers->dersKredi;
			        printf("Ilk dersiniz eklendi.\n");
			    }
			 
			    else
			    {
			    	struct OgrDers *tmpYeniDers = ogrenci->dersHead;
			    	while(tmpYeniDers->next != NULL)
			    	{
			    		tmpYeniDers = tmpYeniDers->next;
					}
					tmpYeniDers->next=sonaEklenecek;
					ogrenci->dersSayisi++;
					ogrenci->toplamKredi+=tmpDers->dersKredi;
					printf("Yeni dersiniz eklendi.\n");
				    
			    }
			}
			else//Ders se�ilemez
			{
				printf("Dersi secebilmek icin gecerli kosullari saglamiyorsunuz...\n");
			}
		}
	}
	else
	{
		printf("Ders bulunamadi...\n");
	}
	
    return ogrenci->dersHead;
}

void ogrDerstxtYazdir(struct OGRENCI* start){//��rencilere eklenen dersler ogrenci-ders.txt isimli text dosyas�na yazd�r�l�r. Bu ogrenci-ders.txt dosyas� aradaki ili�kileri kontrol etmek i�in kullan�lacakt�r.
	/*
	inputlar:
		OGRENCI* ��renciler linkli listesinin ba�lang�� de�eri
	return:
		void
	*/
	FILE *dosyaYaz;
	dosyaYaz = fopen("ogrenci-ders.txt","w");
	struct OGRENCI *gecerliOgrenci = start;
	while(gecerliOgrenci != NULL)
	{
		struct OgrDers *gecerliDersler = gecerliOgrenci->dersHead;
		if(gecerliDersler != NULL)
		{
			while(gecerliDersler != NULL)
			{
				fprintf(dosyaYaz,"%d\t%s\t%d\t%s\n",gecerliDersler->ogrNo,gecerliDersler->dersKod,gecerliDersler->durum,gecerliDersler->tarih);
				gecerliDersler = gecerliDersler->next;
			}
		}
		gecerliOgrenci = gecerliOgrenci->next;
	}
	fclose(dosyaYaz);
}

void ogrDersBaslangic(struct OGRENCI* start){//Program ba�lat�ld��� anda ��rencilerin se�ti�i derslerin ��renciler i�erisine eklenmesi i�in kullan�lan fonksiyondur.
	/*
	inputlar:
		OGRENCI* ��renciler linkli listesinin ba�lang�� de�eri
	return:
		void
	*/
	struct OGRENCI *tmpOgrenci = start;
	struct OgrDers yeniKayit;
	FILE *fp = fopen("ogrenci-ders.txt", "r");
	if(fp == NULL) {
        perror("Aradiginiz dosya yok. Lutfen once inputlari ekleyiniz. Ardindan menuden 5. secenek ile dosyaya yazdiriniz.\n");
    }
    else
    {
	    char satir[1000];
	    while(fgets(satir, sizeof(satir), fp) != NULL) {
	    	int len=strlen(satir);
	    	satir[len-1]='\0';
	    	int sayac=0;
			char delim[] = "\t";
			char *ptr = strtok(satir, delim);
			while(ptr != NULL)
			{
				if(sayac==0)//OgrNo
				{
					yeniKayit.ogrNo=atoi(ptr);
				}
				else if(sayac==1)//ders kodu
				{
					strcpy(yeniKayit.dersKod,ptr);
				}
				else if(sayac==2)//durum
				{
					yeniKayit.durum=atoi(ptr);
				}
				else if(sayac==3)//tarih
				{
					strcpy(yeniKayit.tarih,ptr);
				}
				ptr = strtok(NULL, delim);
				sayac++;
			}
			
			int kontrol = 0;
			while(tmpOgrenci != NULL && kontrol == 0)
			{
				if(tmpOgrenci->ogrNo==yeniKayit.ogrNo)
				{
					kontrol=1;
				}
				else
				{
					tmpOgrenci=tmpOgrenci->next;
				}
			}
			if(kontrol==1)
			{
				ogrDersBaslangicSonaEkle(tmpOgrenci,yeniKayit.dersKod,yeniKayit.durum,yeniKayit.tarih);
				
			}
			tmpOgrenci=start;
			printf("Eklenecek : No:%d - DersKod:%s - Durum:%d - Tarih:%s\n",yeniKayit.ogrNo,yeniKayit.dersKod,yeniKayit.durum,yeniKayit.tarih);
			//EKle
		}
		fclose(fp);
		
	}
}

void ogrDersBaslangicSonaEkle(struct OGRENCI *ogrenci,char * dersKod,int durum, char * tarih){//Program ba�lad��� anda ��rencilerin se�ti�i dersleri txt dosyas�ndan al�nan verileri linkli listeye ekleyen fonksiyondur.
	/*
	inputlar:
		OGRENCI* ekleme yap�lacak ��rencinin adresi
		char* eklenecek olan dersin kodu
		int eklenecek olan dersin durumu (1=Ders se�ilmi�tir | 0=Ders ��kar�lm��t�r)
		char* i�lemin yap�lm�� oldu�u tarih
	return:
		void
	*/
    struct OgrDers* sonaEklenecek = ogrDersDugumOlustur(ogrenci->ogrNo,dersKod,durum,tarih);
    if (ogrenci->dersHead == NULL)
    {
        ogrenci->dersHead = sonaEklenecek;
    }
    else
    {	
	    struct OgrDers* tmp = ogrenci->dersHead;
	    while(tmp->next != NULL)
	    {
	    	tmp=tmp->next;
		}
		tmp->next= (struct OgrDers*) malloc(sizeof(struct OgrDers));
		tmp->next = sonaEklenecek;
    }
    printf("Ders eklendi.\n");
}

void ogrKrediDersGuncelle(struct OGRENCI* ogrHead,struct DERS* dersHead)
{
	
	struct OGRENCI* tmpOgr = ogrHead;
	//struct DERS* tmpDers = dersHead
	//int toplamKredi = 0;
	//int toplamDersSay = 0;
	//struct OgrDers *tmpDersler = dersHead;
	while(tmpOgr != NULL)
	{
		struct OgrDers *tmpOgrDers = tmpOgr->dersHead;
		while(tmpOgrDers != NULL)
		{
			
			struct DERS* tmpDersler = dersHead;
			int kontrol = 0;
			while(tmpDersler != NULL && kontrol == 0 )
			{
				//printf("********OgrDers: %s - Dersler: %s\n",tmpOgrDers->dersKod,tmpDersler->dersKod);
				if(strcmp(tmpOgrDers->dersKod,tmpDersler->dersKod)==0 && tmpOgrDers->durum == 1)
				{
					//printf("***Eslesen ders bulundu: OgrDers: %s - Dersler: %s\n",tmpOgrDers->dersKod,tmpDersler->dersKod);
					kontrol = 1;
				}
				else
				{
					tmpDersler = tmpDersler->next;
				}
			}
			if(kontrol==1)
			{
				tmpOgr->dersSayisi++;
				tmpOgr->toplamKredi+=tmpDersler->dersKredi;
				//tmpDersler->dersKredi
			}
			
			//printf("*** %s isimli ogrencinin dersi: %s\n",tmpOgr->ogrAdSoyad,tmpOgrDers->dersKod);
			
			tmpOgrDers = tmpOgrDers->next;
		}
		
		/*printf("**Ogrenci No:%d\n",tmpOgr->ogrNo);
		printf("**Ogrenci Ad Soyad:%s\n",tmpOgr->ogrAdSoyad);
		printf("**Ogrenci Ders Sayisi:%d\n",tmpOgr->dersSayisi);
		printf("**Ogrenci No:%d\n",tmpOgr->toplamKredi);
		printf("\n");*/
		
		
		
		
		tmpOgr = tmpOgr->next;
	}
}

void ogrDersCikar(struct OGRENCI *ogrenci,char * dersKod,struct DERS *dersHead){//��rencinin se�mi� oldu�u dersler aras�ndan ders ��karmas�n� sa�layan fonksiyondur.
	/*
	inputlar:
		OGRENCI* dersi ��kar�lacak ��rencinin adresi
		char* ��kar�lacak dersin kodu
		DERS* dersler linkli listesinin ba�lang�� adresi
	return:
		void
	*/
	struct OgrDers *tmpDersler = ogrenci->dersHead;
	struct DERS *dersBilgi = dersHead;
	int dersBilgiDurum = 0;
	while(dersBilgi != NULL && dersBilgiDurum == 0)
	{
		if(strcmp(dersBilgi->dersKod,dersKod)==0)
		{
			dersBilgiDurum = 1;
		}
		else
		{
			dersBilgi = dersBilgi->next;
		}
	}
	if(dersBilgiDurum==1)
	{
		int dersKontrol = 0;
		while(tmpDersler != NULL && dersKontrol == 0)
		{
			if(strcmp(tmpDersler->dersKod,dersKod)==0)
			{
				dersKontrol=1;
			}
			else
			{
				tmpDersler=tmpDersler->next;
			}
		}
		if(dersKontrol==1)
		{
			tmpDersler->durum=0;
			ogrenci->dersSayisi--;
			ogrenci->toplamKredi-=dersBilgi->dersKredi;
			char tarih2[100];
			int tarihLen=0;
			strcpy(tarih2,getTime());
			tarihLen=strlen(tarih2);
			tarih2[tarihLen-1]='\0';
			strcpy(tmpDersler->tarih,tarih2);
			printf("%s kodlu dersin durumu inaktif edildi...\n",tmpDersler->dersKod);
		}
		else
		{
			printf("Ders bulunamadi\n");
		}
	}
	else
	{
		printf("Ders bulunamadi\n");
	}
}


//�IKTILAR

struct HOCA * arananHoca(struct HOCA* head,int arananId){//�d si girilen hocan�n adresini d�nd�ren fonksiyondur.
	/*
	inputlar:
		HOCA* hocalar linkli listesinin ba�lang�� de�eri
	return:
		HOCA* Hoca bulunursa bulunan hocan�n adresi | Hoca bulunamazsa NULL
	*/
	struct HOCA *tmp = head;
	int hocaDurum=0;
	while(tmp!= NULL && hocaDurum == 0)
	{
		if(tmp->id == arananId)
		{
			hocaDurum=1;
		}
		else
		{
			tmp = tmp->next;
		}
	}
	
	if(hocaDurum==1)
	{
		return tmp;
	}
	return NULL;
}

//EK KONTROLLER

struct DERS* kontrolDersSil(int hocaId,struct DERS* start){
	
	int sayac=0;
	struct DERS* dersHead = start;
	while(start->next!=NULL)
	{
		if(sayac==0)
		{
			if(start->ogretmenId==hocaId)
			{
				printf("Hoca %s dersi veriyor.\n",start->dersAd);
				//head de�i�
				struct DERS *tmp = start;
				start=start->next;
				free(tmp);
				dersHead = start;
			}
		}
		else
		{
			struct DERS *prev=start;
			struct DERS *curr=start->next;
			if(curr->ogretmenId==hocaId)
			{
				printf("Hoca %s dersi veriyor.\n",curr->dersAd);
				prev->next=curr->next;
				free(curr);
			}
			start = start->next;
		}
		sayac++;
	}
	return dersHead;
	
}
void kontrolDersBosla(int hocaId,struct DERS* start){
	struct DERS* tmp = start;
	while(tmp != NULL)
	{
		if(tmp->ogretmenId==hocaId)
		{
			tmp->ogretmenId=-1;
		}
		tmp=tmp->next;
	}
}

void kontrolOgrenciDersSil(int hocaId,struct OGRENCI* ogrHead,struct DERS* dersHead){
	
	char dersKod[100];
	struct DERS *tmpDers = dersHead;
	while(tmpDers!=NULL)
	{
		if(tmpDers->ogretmenId==hocaId)
		{
			//printf("***DersHocaId:%d - hocaId:%d\n",tmpDers->ogretmenId,hocaId);
			//printf("***%d id li Hoca %s isimli dersi veriyor\n",hocaId,tmpDers->dersAd);
			strcpy(dersKod,tmpDers->dersKod);
			struct OGRENCI *tmpOgrenci = ogrHead;
			while(tmpOgrenci != NULL)
			{
				struct OgrDers *tmpOgrDers = tmpOgrenci->dersHead;
				while(tmpOgrDers != NULL)
				{
					if(strcmp(dersKod,tmpOgrDers->dersKod)==0)
					{
						//printf("DersKod:%s - tmpOgrDersKod:%s",dersKod,tmpOgrDers->dersKod);
						//bu dersi ��rencinin se�ti�i derslerden sil
						tmpOgrenci->dersHead=hocaSilDersSil(tmpOgrenci,dersKod,dersHead);
					}
					tmpOgrDers=tmpOgrDers->next;
				}
				tmpOgrenci=tmpOgrenci->next;
			}
		}
		tmpDers = tmpDers->next;
	}
}

struct OgrDers* hocaSilDersSil(struct OGRENCI *gelenOgr,char * dersKod,struct DERS* dersHead){
	if(strcmp(gelenOgr->dersHead->dersKod,dersKod)==0)
	{
		struct OgrDers *tmp = gelenOgr->dersHead->next;
		struct OgrDers *silinecek = gelenOgr->dersHead;
		
		
		
		gelenOgr->dersHead=tmp;
		
		
		if(silinecek->durum==1)
		{
			struct DERS *cikan = dersGetir(dersHead,dersKod);
			int eksilenKredi = cikan->dersKredi;
			gelenOgr->toplamKredi-=eksilenKredi;
			gelenOgr->dersSayisi--;
		}
		
		free(silinecek);
		return gelenOgr->dersHead;
	}
	else
	{
		//ara kay�t sil
		struct OgrDers *tmp = gelenOgr->dersHead;
		struct OgrDers *tmp2 = gelenOgr->dersHead->next;
		int kontrol = 0;
		while(tmp2 != NULL && kontrol == 0)
		{
			if(strcmp(tmp2->dersKod,dersKod)==0)
			{
				tmp->next=tmp2->next;
				if(tmp2->durum==1)
				{
					gelenOgr->dersSayisi--;
					struct DERS *cikan = dersGetir(dersHead,dersKod);
					int eksilenKredi = cikan->dersKredi;
					gelenOgr->toplamKredi-=eksilenKredi;
				}
				
				
				free(tmp2);
				kontrol = 1;
			}
			else
			{
				tmp=tmp->next;
				tmp2 = tmp2->next;
			}
		}
	}
	return gelenOgr->dersHead;
}

void ogrSilinenDersCikar(struct OGRENCI* ogrHead,char * dersKod,struct DERS* dersHead)
{
	struct OGRENCI *tmpOgrenci = ogrHead;
	while(tmpOgrenci != NULL)
	{
		struct OgrDers *tmpOgrDers = tmpOgrenci->dersHead;
		while(tmpOgrDers != NULL)
		{
			if(strcmp(dersKod,tmpOgrDers->dersKod)==0)
			{
				tmpOgrenci->dersHead=ogrencidenDersiSil(tmpOgrenci,dersKod,dersHead);
			}
			tmpOgrDers=tmpOgrDers->next;
		}
		tmpOgrenci=tmpOgrenci->next;
	}
}


struct OgrDers* ogrencidenDersiSil(struct OGRENCI *gelenOgr,char * dersKod,struct DERS* dersHead){
	if(strcmp(gelenOgr->dersHead->dersKod,dersKod)==0)
	{
		struct OgrDers *tmp = gelenOgr->dersHead->next;
		struct OgrDers *silinecek = gelenOgr->dersHead;
		
		
		gelenOgr->dersHead=tmp;
		
		if(silinecek->durum==1)
		{
			struct DERS *cikan = dersGetir(dersHead,dersKod);
			int eksilenKredi = cikan->dersKredi;
			gelenOgr->toplamKredi-=eksilenKredi;
			gelenOgr->dersSayisi--;
		}
		free(silinecek);
		return gelenOgr->dersHead;
	}
	else
	{
		//ara kay�t sil
		struct OgrDers *tmp = gelenOgr->dersHead;
		struct OgrDers *tmp2 = gelenOgr->dersHead->next;
		int kontrol = 0;
		while(tmp2 != NULL && kontrol == 0)
		{
			if(strcmp(tmp2->dersKod,dersKod)==0)
			{
				tmp->next=tmp2->next;
				if(tmp2->durum==1)
				{
					gelenOgr->dersSayisi--;
					struct DERS *cikan = dersGetir(dersHead,dersKod);
					int eksilenKredi = cikan->dersKredi;
					gelenOgr->toplamKredi-=eksilenKredi;
				}
				
				free(tmp2);
				kontrol = 1;
			}
			else
			{
				tmp=tmp->next;
				tmp2 = tmp2->next;
			}
		}
	}
	return gelenOgr->dersHead;
}

