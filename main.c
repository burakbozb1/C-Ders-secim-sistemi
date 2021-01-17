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


//DersFonksiyonlarý
struct DERS* dersSonaEkle(struct DERS* ,char * , char * , int , int , int );
struct DERS* dersDugumOlustur(char *, char *, int, int, int);
int dersGuncelle(struct DERS* ,char * ,struct HOCA* );
void dersTxtYaz(struct DERS*);
void derslerListedenYazdir(struct DERS*);
struct DERS* dersBaslangic(struct DERS*);
struct DERS* dersSil(struct DERS*,char *);
void dersTemizle(struct DERS*);


//Öðrenci fonksiyonlarý
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


//Ogrenci menüsü fonksiyonlarý
struct OGRENCI* girisYapanOgrenci(struct OGRENCI* ,int );
void secilebilecekDersler(struct OGRENCI *,struct DERS* );
void ogrDerslerimYazdir(struct OGRENCI *);
struct OgrDers* ogrDersSonaEkle(struct OGRENCI *,struct DERS *,char * ,int , char * );
struct OgrDers* ogrDersDugumOlustur(int ,char * , int , char * );
void ogrDerstxtYazdir(struct OGRENCI*);
void ogrDersBaslangic(struct OGRENCI*);
void ogrDersCikar(struct OGRENCI *,char * ,struct DERS *);
void ogrDersBaslangicSonaEkle(struct OGRENCI *,char * ,int , char * );

//Çýktý fonksiyonlarý
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
	
	//Dosya varmý kontrol. Eger dosya yoksa dosyalar yaratýlacaktýr.
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
					case 1://Admin öðretim üyesi menüsüne gider
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
								case 1://Admin öðretim üyelerini listeleler
									printf("Hocalar:\n");
									
									hocaListedenYazdir(hocaHead);
									
									printf("Devam etmek icin enter tusuna basiniz.\n");
									getch();
									break;
								case 2://Admin Yeni öðretim üyesi ekler.
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
								case 3://Öðretim üyesini güncelle
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
								case 4://Öðretim üyesini sil
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
										//Üst menüye yönel
									}
									else
									{
										printf("Gecersiz secim. Lutfen tekrar secim yapiniz.");
										giris3=-1;
									}
											
							}
										
						}while(giris3!=0);
						
						break;
					case 2://Admin ders menüsüne gider
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
										//Üst menüye yönel
									}
									else
									{
										printf("Gecersiz secim. Lutfen tekrar secim yapiniz.");
										giris3=-1;
									}
											
							}
										
						}while(giris3!=0);
						
						
						break;
					case 3://Admin öðrenci menüsüne gider
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
								case 3://Admin öðrenci güncelliyor
									
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
								case 4://Admin Öðrenci siliyor
									
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
								case 5://Admin ogrenci-ders.txt isimli dosyadaki verileri yazdýrýyor.
									printf("Ogrenci-ders.txt listesi yazdiriliyor...\n");
									
									ogrenciDersYazdir();
									
									printf("Devam etmek icin enter tusuna basiniz.\n");
									getch();
									break;
								default :
									if(giris3==0)
									{
										//Üst menüye yönel
									}
									else
									{
										printf("Gecersiz secim. Lutfen tekrar secim yapiniz.");
										giris3=-1;
									}
											
							}
										
						}while(giris3!=0);
						
						
						break;
					case 4://Admin öðretim üyesinin verdiði dersleri listeler
						
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
					case 5://Admin belli dersi alan tüm öðrencileri listeler
					
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
					case 6://Admin belli öðrencinin aldýðý tüm dersleri listeler
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
					case 7://derskodu_siniflisesi.txt dosyasi yazdýrýlýr.
						
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
							//Üst menüye yönel
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
					case 1://Öðrenci ders listesini görür
						printf("Ders Listesi\n");
						
						derslerListedenYazdir(dersHead);
						
						printf("Devam etmek icin enter tusuna basiniz.\n");
						getch();
						break;
					case 2://Öðrenci ders ekler
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
					case 3://Öðrenci ders çýkarýr
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
						
					case 4://Öðrenci seçtiði dersleri yazdýrýr
						ogrDerslerimYazdir(ogrenci);
						
						printf("Devam etmek icin enter tusuna basiniz.\n");
						getch();
						break;
						
					default :
						if(giris2==0)
						{
							//Üst menüye yönel
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

void dosyaKontrol(char * dosyaAdi){//Program baþladýðý anda ismi girilen dosyanýn var olup olmadýðý kontrol eden fonksiyondur. Eðer dosya yoksa oluþturulur.
	/*
	inputlar:
		char* kontrol edilecek dosyanýn adý
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

void hocaListedenYazdir(struct HOCA* start){//Hocalarýn bulunduðu linkli listeyi konsol ekranýna yazdýrmak için kullanýlan fonksiyondur.
	/*
	inputlar:
		HOCA* hoca linkli listesinin baþlangýç adresi
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
		hocalarýn tutulduðu linli listenin baþlangýç deðeri
	retrun:
		yeni eklenecek hoca için benzersiz id deðeri
	*/
	if(start==NULL)
	{
		return 1;//Hoca eklenmemiþse 1 döndürülecek.
	}
	else//Hoca eklendiyse en son id 1 arttýrlýp döndürülecek.
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

void satirOku(char * dosyaAdi){//Txt dosyasýndan satýr satýr deðer okumak için kullanýlan fonksiyondur.
	/*
	inputlar:
		okunacak dosyanin adý alýnýr
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

void clrBuffer(){//Buffer bellekte bulunan enter, boþluk vs karakterleri temizlemek için kullanýlýr
	fseek(stdin,0,SEEK_END);
}

struct HOCA* hocaDugumOlustur(int id, char * adSoyad, char * unvan){//Yeni bir hoca eklemek için düðüm oluþturmaya yarayan fonksiyondur
	/*
	inputlar:
		int eklenecek hocanýn idsi
		char* eklenecek hocanýn adý ve soyadý
		char* eklenecek hocanýn ünvaný
	return:
		HOCA* oluþturulan yeni düðümün adresi
	*/
    struct HOCA* yeniDugum = (struct HOCA*) malloc(sizeof(struct HOCA));
    yeniDugum->next = NULL;
    yeniDugum->id = id;
    strcpy(yeniDugum->adSoyad,adSoyad);
    strcpy(yeniDugum->unvan,unvan);
    return yeniDugum;
}


struct HOCA* hocaSonaEkle(struct HOCA* start,int id, char * adSoyad, char * unvan){//Yeni hoca eklemek için linkli listenin sonuna yeni bir düðüm eklenir.
	/*
	inputlar:
		HOCA* hoca linkli listesinin baþlangýç deðeri
		int yeni hocanýn id si
		char * yeni hocanýn adý ve soyadý
		char * hocanýn ünvaný
	return:
		HOCA* linkli listenin baþlangýç deðeri
	*/
    struct HOCA* sonaEklenecek = hocaDugumOlustur(id,adSoyad,unvan);
 
    if (start == NULL)//Listemizin içerisinde hiç eleman yoksa ilk elemanýmýzý ekliyoruz
    {
        start = sonaEklenecek;
    }
 
    else//Eðer liste içerisinde eleman varsa
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


int hocaGuncelle(struct HOCA* start,int arananId){//Mevcut bir hocanýn adýný soyadýný ve ünvanýný güncellemek için kullanýlýr.
	/*
	inputlar:
		HOCA* hocalar linkli listesinin baþlangýç deðeri
		int güncellenecek olan hocanýn id si
	return
		int 1=güncelleme baþarýlý , -1=güncelleme baþarýsýz
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

void hocaTemizle(struct HOCA* start){//Program kapatýlýrken bellekte hocalara ayrýlan alanýn iþletim sistemine býrakýlmasý için kullanýlýr.
	/*
	inputlar:
		HOCA* hocalar linkli listesinin baþlangýç adresi
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

void hocaTxtYaz(struct HOCA* start){//Hocalarý txt dosyasýna kaydetmek için kullanýlan fonksiyondur.
	/*
	inputlar:
		HOCA* hocalar linkli listesinin baþlangýç adresi
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


struct HOCA* hocaSil(struct HOCA* start,int hocaId){//Id si girilen hocayý silmek için kullanýlýr
	/*
	inputlar:
		HOCA* hocalar linkli listesinin baþlangýç adresi
		int aranan hocanýn id si
	return:
		HOCA* hocalar linkli listesinin baþlangýç deðeri
	*/
	int kayitKontrol=0;
	struct HOCA* head = start;
	if(head->id==hocaId)
	{
		struct HOCA* tmp=start->next;
		head=tmp;
		free(start);
		//Headi deðiþtir
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

struct HOCA* hocaBaslangic(struct HOCA* start){//Program baþlatýldýðý anda txt dosyasýnda kayýtlý olan hocalar için yeni linkli liste oluþturuluyor ve tekrar tekrar veri girilmesi engelleniyor
	/*
	inputlar:
		HOCA* hocalar linkli listesinin baþlangýç adresi
	return:
		HOCA* hocalar linkli listesinin baþlangýç adresi
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


//DERSLER BÖLÜMÜ


struct DERS* dersDugumOlustur(char * dersKod, char * dersAd, int dersKredi, int dersKontenjan, int ogretmenId){//Eklenecek ders için yeni bir düðüm oluþturulmasýný saðlayan fonksiyondur.
	/*
	inputlar:
		char* eklenecek olan dersin ders kodu
		char* eklenecek olan dersin adý
		int eklenecek olan dersin kredisi
		int eklenecek olan dersin kontenjaný
		int dersi verecek olan hocanýn idsi
	return:
		DERS* oluþturulan düðümün adresi
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
		DERS* dersler linkli listesinin baþlangýç deðeri
		char* eklenecek olan dersin kodu
		char* eklenecek olan dersin adý
		int eklenecek olan dersin kredisi
		int eklenecek dersin kontenjaný
		int eklenecek dersi veren hocanýn idsi
	return:
		DERS* dersler linkli listesinin baþlangýç adresi
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

void derslerListedenYazdir(struct DERS* start){//Dersler linkli listenin konsol ekranýna yazdýrýlmasý için kullanýlan fonksiyondur.
	/*
	inputlar:
		DERS* dersler linkli listesinin baþlangýç adresi
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

int dersGuncelle(struct DERS* start,char * arananId,struct HOCA* hocaHead){//Ders kodu girilen dersin verilerini güncellemek için kullanýlan fonksiyondur.
	/*
	inputlar:
		DERS* dersler linkli listesinin baþlangýç adresi
		char* aranan dersin ders kodu
		HOCA* hocalar linkli listesinin baþlangýç deðeri
	return:
		int 1=güncelleme baþarýlý,-1=güncelleme baþarýsýz
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

void dersTxtYaz(struct DERS* start){//Dersler linkli listesindeki derslerin dersler.txt dosyasýna yazýlmasý için kullanýlan fonksiyondur.
	/*
	inputlar:
		DERS* dersler linkli listesinin baþlangýç deðeri
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

struct DERS* dersBaslangic(struct DERS* start){//Program baþlatýldýðý anda dersler.txt dosyasýndan linkli listesinin doldurulmasý için kullanýlan fonksiyondur.
	/*
	inputlar:
		DERS* dersler linkli listesinin baþlangýç deðeri
	return:
		DERS* dersler linkli listesinin baþlangýç deðeri
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

struct DERS* dersSil(struct DERS* start,char * dersKod){//Listeden ders silmek için kullanýlýr.
	/*
	inputlar:
		DERS* dersler linkli listesinin baþlangýç deðeri
		char* silinecek olan dersin kodu
	return:
		DERS* dersler linkli listesinin baþlangýç deðeri
	*/
	int kayitKontrol=0;
	struct DERS* head = start;
	if(strcmp(head->dersKod,dersKod)==0)
	{
		//Head deðiþtirilmeli
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

void dersTemizle(struct DERS* start){//Program kapatýlýrken bellekte meþgul edilen alanýn tekrar iþletim sistemine býrakýlmasý için kullanýlan fonksiyon
	/*
	inputlar:
		DERS* dersler linkli listesinin baþlangýç deðeri
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


//Öðrenci Fonksiyonlarý


struct OGRENCI* ogrDugumOlustur(int ogrNo, char * ogrAdSoyad){//Linkli listeye yeni bir öðrenci eklenebilmesi için bellekte yer ayrýlýyor.
	/*
	inputlar:
		int eklenecek öðrencinin numarasý
		char* eklenecek öðrencinin adý ve soyadý
	return:
		OGRENCI* oluþturulan düðümün adresi
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


struct OGRENCI* ogrSonaEkle(struct OGRENCI* start,int ogrNo, char * ogrAdSoyad){//Linkli listenin sonuna yeni bir öðrenci eklemek için kullanýlan fonksiyondur.
	/*
	inputlar:
		OGRENCI* öðrenciler linkli listesinin baþlangýç deðeri
		int öðrenci numarasý
		int öðrencinin adý ve soyadý
	return:
		OGRENCI* öðrenciler linkli listesinin baþlangýç deðeri
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

int ogrIdOlustur(struct OGRENCI* start){//Yeni oluþturulacak öðrenci için öðrenci numarasýnýn tahsis edilmesi
	/*
	inputlar:
		OGRENCI* öðrenciler linkli listesinin baþlangýç deðeri
	return:
		int oluþturulan öðrenci idsi
	*/
	int yeniId=0;
	struct OGRENCI* tmp = start;
	if(tmp==0)
	{
		yeniId = 2111001;//Ýlk öðrenci için hazýrlanmýþ baz deðer
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

void ogrListedenYazdir(struct OGRENCI* start){//Öðrenciler linkli listesinin konsola yazdýrýlmasý için kullanýlýr.
	/*
	inputlar:
		OGRENCI* öðrenciler linkli listesinin baþlangýç deðeri
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

void ogrTemizle(struct OGRENCI* start){//Program kapatýlýrken öðrenciler linkli listesine tahsis edilmiþ alanýn tekrar iþletim sistemine býrakýlmasý için kullanýlýr.
	/*
	inputlar:
		OGRENCI* öðrenciler linkli listesinin baþlangýç deðeri
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

int ogrGuncelle(struct OGRENCI* start,int arananNo){//Ýd si girilen öðrencinin adýný ve soyadýný güncellemek için kullanýlan fonksiyondur. Geri kalan deðerler yapýlan iþlemler çerçevesinde otomatik olarak güncellenmektedir.
	/*
	inputlar:
		OGRENCI* öðrenciler linkli listesinin baþlangýç deðeri
		int aranan öðrencinin idsi
	return:
		int 1=güncelleme baþarýlý ise, -1=güncelleme baþarýsýz ise
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

struct OGRENCI* ogrSil(struct OGRENCI* start,int ogrNo){//Ýd si girilen öðrenciyi silmek için kullanýlýr
	/*
	inputlar:
		OGRENCI* öðrenciler linkli listesinin baþlangýç deðeri
		int silinecek öðrencinin idsi
	return:
		OGRENCI* öðrenci linkli listesinin baþlangýç deðeri
	*/
	int kayitKontrol=0;
	struct OGRENCI* head = start;
	if(head->ogrNo==ogrNo)
	{
		struct OGRENCI* tmp=start->next;
		head=tmp;
		tmp->dersHead=NULL;
		
		free(start);
		//Headi deðiþtir
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



void ogrTxtYaz(struct OGRENCI* start){//Linkli listedeki öðrencilerin ogrenciler.txt isimli dosyaya yazýlmasýný saðlayan fonksiyondur.
	/*
	inputlar:
		OGRENCILER* öðrenciler linkli listesinin baþlangýç adresi
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

struct OGRENCI* ogrBaslangic(struct OGRENCI* start){//Program baþlatýldýðý anda öðrenciler için linkli liste oluþturulur ve ogrenciler.txt dosyasýndaki deðerler bu linkli listeye eklenir.
	/*
	inputlar:
		OGRENCI* öðrenciler linkli listesinin baþlangýç deðeri
	return:
		OGRENCI* öðrenciler linkli listesinin baþlangýç deðeri
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

struct OGRENCI* ogrBaslangicDugumOlustur(int ogrNo, char * ogrAdSoyad,int dersSayisi,int dersKredi){//Baþlangýçtaki öðrenci eklemeleri için öðrenci baþýna yeni bir düðüm oluþturan fonksiyondur.
	/*
	inputlar:
		int öðrenci no
		int öðrenci adý soyadý
		int öðrencinin seçtiði ders sayýsý
		int öðrencinin seçtiði derslerin toplam kredi deðeri
	return:
		OGRENCI* oluþturulan öðrenci düðümünün adresi
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


struct OGRENCI* ogrBaslangicSonaEkle(struct OGRENCI* start,int ogrNo, char * ogrAdSoyad,int dersSayisi,int dersKredi){//Öðrenciler linkli listesinin sonuna baþlangýçta yeni bir öðrenci eklenmesi için kullanýlan fonksiyondur
	/*
	inputlar:
		OGRENCI* öðrenciler linkli listesinin baþlangýç deðeri
		int öðrenci numarasý
		char* öðrenci adý ve soyadý
		int öðrencinin seçmiþ olduðu ders sayýsý
		int öðrencinin seçmiþ olduðu derslerin toplam kredi deðeri
	return:
		OGRENCI* öðrenci linkli listesinin baþlangýç deðeri
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


struct OGRENCI* girisYapanOgrenci(struct OGRENCI* start,int ogrNo){//Öðrenci ders seçerken sisteme giriþ yapmalýdýr. Girdigi numarasýna göre giriþ yapan öðrenciyi döndüren fonksiyondur.
	/*
	inputlar:
		OGRENCI* öðrenciler linkli listesinin baþlangýç deðeri
		int giriþ yapacak olan öðrencinin numarasý
	return:
		OGRENCI* Öðrenci bulunduysa giriþ yapan öðrencinin adresi, NULL-> Öðrenci bulunamamýþtýr. Bu durumda tekrar giriþ yapmasý istenecek
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

char *getTime(){//Þu anýn tarihini string olarak döndüren fonksiyondur.
	time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return asctime(tm);
}


//Ogrenci menüsü iç seçim fonksiyonlarý


void secilebilecekDersler(struct OGRENCI *ogrenci,struct DERS* dersStart){//Öðrencinin, þartlarýn izin verdiði seçebileceði dersleri ekrana yazdýran fonksiyondur.
	/*
	inputlar:
		OGRENCI* öðrenci linkli listesinin baþlangýç deðeri
		DERS* dersler linkli listesinin baþlangýç deðeri
	return:
		void
	*/
	struct OgrDers *tmpOgr = ogrenci->dersHead;
	struct DERS *tmpDers = dersStart;
	int dersKontrol = 0;
	
	if(tmpOgr != NULL)//Daha önce ders seçilmiþtir. Kalan dersler yazdýrýlýr.
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
				printf("Ders Kodu : %s\nDers Adý:%s\nDers Kredisi:%d\nDers Kontenjani:%d\nDers Yurutucu Id:%d\n",
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
	else//Daha önce ders seçilmemiþtir. Tüm dersler yazdýrýlýr.
	{
		derslerListedenYazdir(dersStart);
	}
	
}

void ogrDerslerimYazdir(struct OGRENCI *gelenOgrenci){//Öðrencinin seçmiþ olduðu dersleri ekrana yazdýran fonksiyondur
	/*
	inputlar:
		OGRENCI* sisteme giriþ yapan öðrenci
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

struct OgrDers* ogrDersDugumOlustur(int ogrNo,char * dersKod, int durum, char * tarih){//Öðrencinin seçtiði ders için düðüm oluþturulmasýný saðlayan fonksiyondur.
	/*
	inputlar:
		int Öðrenci numarasý
		char* dersin kodu
		int dersin durumu(1=ders seçildi| 0=ders çýkarýldý)
		char* iþlem yapýlan tarih
	return:
		OGRENCI* oluþturulan düðümün adresi
	*/
    struct OgrDers* yeniDugum = (struct OgrDers*) malloc(sizeof(struct OgrDers));
    yeniDugum->ogrNo=ogrNo;
    strcpy(yeniDugum->dersKod,dersKod);
    yeniDugum->durum=durum;
    strcpy(yeniDugum->tarih,tarih);
    yeniDugum->next = NULL;
    
    
    return yeniDugum;
}


struct OgrDers* ogrDersSonaEkle(struct OGRENCI *ogrenci,struct DERS *dersHead,char * dersKod,int durum, char * tarih){//Öðrenciye yeni ders eklenmesi için kullanýlan fonksiyondur.
	/*
	inputlar:
		OGRENCI* ekleme yapýlacak öðrencinin adresi
		DERS* ders linkli listesinin baþlangýç adresi
		char* eklenecek dersin kodu
		int eklenecek dersin durumu (1=ders eklendi | 0=ders çýkarýldý)
		char* iþlem yapýlan tarih
	return:
		OgrDers* Öðrenci->OgrDers baþlangýç deðeri
	*/
	char tarih2[100];
	strcpy(tarih2,tarih);
	int tarihLen = strlen(tarih2);
	tarih2[tarihLen-1]='\0';
	int dersKontrol=0;
	int dersDurum = 0;
	struct DERS *tmpDers = dersHead;
	while(tmpDers != NULL && dersKontrol == 0)//Dersi bulmak için kullanýlýr
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
	if(dersKontrol==1)//Eðer ders bulunduysa
	{
		struct OgrDers *tmpDersDurum = ogrenci->dersHead;
		while(tmpDersDurum != NULL && dersDurum==0)//Öðrencide bulunan dersin durumu kontrol edilir
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
			//Durumu güncelle
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
			if((tmpDers->dersKredi+ogrenci->toplamKredi)<=20)//Ders seçilebilir
			{
				struct OgrDers *sonaEklenecek = ogrDersDugumOlustur(ogrenci->ogrNo,dersKod,durum,tarih2);
			    //printf("\tFonksiyon içi Ogrenci->dersHead:%p\n",ogrenci->dersHead);
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
			else//Ders seçilemez
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

void ogrDerstxtYazdir(struct OGRENCI* start){//Öðrencilere eklenen dersler ogrenci-ders.txt isimli text dosyasýna yazdýrýlýr. Bu ogrenci-ders.txt dosyasý aradaki iliþkileri kontrol etmek için kullanýlacaktýr.
	/*
	inputlar:
		OGRENCI* öðrenciler linkli listesinin baþlangýç deðeri
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

void ogrDersBaslangic(struct OGRENCI* start){//Program baþlatýldýðý anda öðrencilerin seçtiði derslerin öðrenciler içerisine eklenmesi için kullanýlan fonksiyondur.
	/*
	inputlar:
		OGRENCI* öðrenciler linkli listesinin baþlangýç deðeri
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

void ogrDersBaslangicSonaEkle(struct OGRENCI *ogrenci,char * dersKod,int durum, char * tarih){//Program baþladýðý anda öðrencilerin seçtiði dersleri txt dosyasýndan alýnan verileri linkli listeye ekleyen fonksiyondur.
	/*
	inputlar:
		OGRENCI* ekleme yapýlacak öðrencinin adresi
		char* eklenecek olan dersin kodu
		int eklenecek olan dersin durumu (1=Ders seçilmiþtir | 0=Ders çýkarýlmýþtýr)
		char* iþlemin yapýlmýþ olduðu tarih
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

void ogrDersCikar(struct OGRENCI *ogrenci,char * dersKod,struct DERS *dersHead){//Öðrencinin seçmiþ olduðu dersler arasýndan ders çýkarmasýný saðlayan fonksiyondur.
	/*
	inputlar:
		OGRENCI* dersi çýkarýlacak öðrencinin adresi
		char* çýkarýlacak dersin kodu
		DERS* dersler linkli listesinin baþlangýç adresi
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


//ÇIKTILAR

struct HOCA * arananHoca(struct HOCA* head,int arananId){//Ýd si girilen hocanýn adresini döndüren fonksiyondur.
	/*
	inputlar:
		HOCA* hocalar linkli listesinin baþlangýç deðeri
	return:
		HOCA* Hoca bulunursa bulunan hocanýn adresi | Hoca bulunamazsa NULL
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
				//head deðiþ
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
						//bu dersi öðrencinin seçtiði derslerden sil
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
		//ara kayýt sil
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
		//ara kayýt sil
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

