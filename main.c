#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <locale.h>


int map[80][23]={0};  //haritanın sınırlarnı belirleyen bir array oluşturuldu
int kuyrukSutun[500];  //yılanın kuyruğu için belirlenen  x ve y koordinatlar
int kuyrukSatir[500];


void gotoxy(short x, short y) {       //istenilen koordinatlara gitmeyi sağlar
	HANDLE hConsoleOutput;
	COORD Cursor_Pos = {x-1, y-1};

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}

void alan(int x1,int y1,int x2,int y2,int stabildeger)   // oyunun çerçevesinin sınırlarını belirleyen fonksiyon
{
    int i;
    for(i=x1; i<=x2; i++)
    {
        map[i][y1] = stabildeger;
        map[i][y2] = stabildeger;
    }
    for(i=y1; i<=y2; i++)
    {
        map[x1][i] = stabildeger;
        map[x2][i] = stabildeger;
    }
}
void EkranaYaz() //sınırları belirlenen çerçevenin şeklini ekrana bastırıan fonksiyon
{

    int x,y;
    for(x=0; x<80; x++)
    {
        for(y=0; y<23; y++){
            gotoxy(x+1,y+1);
        if(map[x][y]==2){
            printf("%c",175);
        }
        }
    }
}

int k,l,engelx,engely;   // k ve l yem için, engelx ve engely engel için belirlenen koordinat değişkenleridir
int randomAtama()       //ekrandan random yem ve engel oluşturan fonksiyondur
{
    srand(time(NULL));
    k=4+rand()%65;
    l=4+rand()%15;
    engelx=4+rand()%65;
    engely=4+rand()%15;
}

void main()
{
    system("color B"); //oyunun rengi belirlendi
    gotoxy(30,10);
    printf("\t___Yilan Oyununa Hosgeldiniz___\n\n\n");
    printf("\tOyunumuzun amaci belirtilen hedeflerin yenerek kurallara uygun sekilde oyunu bitirmeye calismaktir.\n");
    printf("\tKurallar:\n\t-Duvarlarin disina cikilamaz.\n\t-Yilan kendine veya 'X' engeline carparsa yanar\n ");
    Sleep(8000); //oyun açıklamasının ekrandaki konumu ve ekranda kalma süresi belirlendi
    system("cls");//konsolu temizlemek için
    gotoxy(40,10);
    printf("BOL SANS :))");
    Sleep(1000);
    system("cls");
    tekrar:
    setlocale(LC_ALL,"Turkish");
    randomAtama(); // oluşturulan fonksiyonlar ana fonksiyonda çağırıldı
    alan(0,0,79,22,2);
    EkranaYaz();

    int sx=39,sy=13;
    int dy=0,dx=0;
    int a=0;
    int durum=1;
    unsigned char tus;




    do{
        if(kbhit()) //bir tuşa basılıp basılmadığını belirler
        {
            tus=getch(); // basılan tuşu hafızada tutar
            if(tus==224)  // tuş takımında girilen tuşa göre x veya y konumunun eksilip artmasını sağlar.
            {
                tus=getch();
                switch(tus)
                {
                    case 72:dy=-1; dx=0;
                        break;
                    case 80:dy=1; dx=0;
                        break;
                    case 77: dx=1; dy=0;
                        break;
                    case 75: dx=-1; dy=0;

                }
            }
        }
        sx=sx+dx;
        sy=sy+dy;

        if(((sx>78)||(sx<2)||(sy>22)||(sy<2))){  //yılan çerçeveye çarptığında oyunu bitirip ekreanı temizleyen koşul
            gotoxy(1,1);
            system("cls");
            gotoxy(30,10);
            printf("\t___YANDINIZ_");
            gotoxy(30,12);
            printf("\tTEKRAR DENEYIN :(");
            gotoxy(0,0);
            durum=0;
            Sleep(1000);
            printf("\a");
            system("cls");
            break;
            }

        kuyrukSutun[0]=sx; // Yılanın kuyruğu için bu değişkenleri tanımladık.
        kuyrukSatir[0]=sy;

        int i,cevap;
        for(i=1;i<=a;i++)  //a değeri yılanın büyüyen kuyruğu ve oyunun puanı için kullanılan değerdir
        {
            if((sx==kuyrukSutun[i] && sy==kuyrukSatir[i])) // yılan kendi kuyruğuna değidiğinde oyuu bitirip ekranı temizleyen koşul
            {
                system("cls");
                gotoxy(30,10);printf("\t___YANDINIZ_");
                durum=0;
                gotoxy(30,12);
                printf("\tTEKRAR DENEYIN :(");
                getch();
                system("cls");

            }
        }


        gotoxy(sx,sy);printf("*"); // yılan için kullanılacak sembolün konumu

        for(i=0;i<=a;i++)// yemi yedikçe yılanın kuyruğunu uzatır
        {
            gotoxy(kuyrukSutun[i],kuyrukSatir[i]);
            printf("*");
        }



        if((sx==engelx) && (sy==engely))  //yılan engele çarparsa oyuu bitirir
        {
            system("cls");
            gotoxy(30,10);
            printf("\t___YANDINIZZZZ_\n");
            gotoxy(30,12);
            printf("\tTEKRAR DENEYINIZ  :(");
            printf("\a");
            durum=0;
            Sleep(3000);
            system("cls");

        }
         if(sx==k && sy==l)  // yılan yemi yedikçe kuyruk değeri ve puan 1 artar belirlenen puana gelindiğinde oyunu bitirir
        {
            randomAtama();
            a++;
            gotoxy(2,2);printf("Puan: %d",a);
            /*
            if(a==10){
                printf("--KAZANDINIZ--\n");
                Sleep(1000);
                system("cls");
                durum=0;
            }*/
        }
        gotoxy(engelx,engely);printf("X");// yılan yemi yedikten sonra yemin ve engelin yerine boşluk değer atar
        gotoxy(k,l);printf("o");
        Sleep(90);
        gotoxy(sx,sy);printf(" ");
        gotoxy(k,l);printf(" ");
        gotoxy(engelx,engely);printf(" ");

       for(i=0;i<=a;i++)//yılanın kuyruğunun sadece yemi yediği zaöman artmasını sağlar
        {
            gotoxy(kuyrukSutun[i],kuyrukSatir[i]);printf(" ");
        }

        for(i=a;i>0;i--)//yılanın yönünün kullanıcının bastığı tuşa göre değişmesini sağlar
        {
            kuyrukSutun[i]=kuyrukSutun[i-1];
            kuyrukSatir[i]=kuyrukSatir[i-1];

        }

    }
    while(durum==1);  /*döngü durum 1 olduğu sürece döngüyü devam ettirir.
    main fonksiyonun içinde kullandığımız durum=0 döngüyü bitirir*/
    int cevap;
    if(durum==0){ //kullanıcının oyun bittikten sonra oyuna devam edip etmemek istediğine göre konsolu kapatır ya da oyunu baştan başlatır
        gotoxy(30,10);
        printf("Tekrar oynamak icin 1'e  oyundan cikmak icin 2'ye basin.. ");
        scanf("%d",&cevap);system("cls");

        if(cevap==1){
            goto tekrar;
            system("cls");
        }
        else if(cevap==2){
            durum=0;
            system("cls");
        }

    }


void game_over(){ //kullanıcı oyunu kapatmayı seçtiğinde oyun sonu bilgilendirmesi yapıp konsolu kapatır
    setlocale(LC_ALL,"Turkish");
	system("cls");
	gotoxy(1,5);
	printf("\t____________OYUN BITTI_____________ \n ");
	gotoxy(1,7);
	printf("_____________PUANINIZ :%d __________________\n\n\n\n",a);
	getch();
	return 0;
}
    game_over();

}
