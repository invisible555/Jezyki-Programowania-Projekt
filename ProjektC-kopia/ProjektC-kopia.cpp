#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <cstdio>

#define eqheight 10
#define eqwidth 80

#define MAP "mapka.txt"

#pragma warning(disable : 4996)  
using namespace std;

char** mapa;
int itemid = 1;
int wiersze = 0;
int kolumny = 0;
int enemycount = 0;



/*
mapa swiata
klasy postaci
postacie,bohater
przedmioty
zadania
przeciwnicy
encounters
przeszkody terenowe
ekwipunek
interfejs uzytkownika
system rozwoju
*/

enum atak
{
    zwyklyatak = 1,
	poteznyatak
	
    

};
enum obrona
{
    zwyklaobrona=5,
    unik
};
struct przedmiot
{
    char nazwa[30];
    int id;
    char klasa[20];
    int width;
    int height;
    int cena;
    int obrazenia;
    int szybkosc_ataku;
    int wartosc_pancerza;
    int posx;
    int posy;
    przedmiot* parent = NULL;

   

};
struct bohater
{
    int atak;
    int obrona ;
    int mana;  // energia do rzucania zaklec
    int hp; //punkty zdrowia
    int stamina; // punkty wytrzymalosci
	int exp; //punkty doświadczenia
	int lvl; //poziom
    przedmiot* weaponslot[2];
    char name[100]; // nazwa
    int posx;
    int posy;
    void (*move)(bohater*, bohater*);
    struct bohater* next;
    struct bohater* prev;
    struct bohater* head=NULL;
    struct bohater* tail;

};


bohater* lista(bohater* enemy, int n);




void enemymove1(bohater* wojownik, bohater* enemy)
{
    int x = rand() % 3 - 1;
    int y = rand() % 3 - 1;
    if (enemy->posx < 1 && x < 0 || enemy->posx > kolumny - 2 && x > 0)
    {
        enemy->posx += -x;
    }
    else
    {
        enemy->posx += x;
    }
    if (enemy->posy > wiersze - 2 && y > 0 || enemy->posy < 1 && y < 0)
    {
        enemy->posx += -y;
    }
    else
    {
        enemy->posy += y;
    }



}
void enemymove2(bohater* wojownik, bohater* enemy)
{
    if (pow(wojownik->posx - enemy->posx, 2) + pow(wojownik->posy - enemy->posy, 2) <= 3)
    {
        if (wojownik->posx < enemy->posx && wojownik->posy < enemy->posy)
        {
            enemy->posx--;
            enemy->posy--;
        }
        else if (wojownik->posx > enemy->posx && wojownik->posy > enemy->posy)
        {
            enemy->posx++;
            enemy->posy++;
        }
    }
    else
    {
        int x = rand() % 3 - 1;
        int y = rand() % 3 - 1;
        if (enemy->posx < 1 && x < 0 || enemy->posx > kolumny - 2 && x > 0)
        {
            enemy->posx += -x;
        }
        else
        {
            enemy->posx += x;
        }
        if (enemy->posy > wiersze - 2 && y > 0 || enemy->posy < 1 && y < 0)
        {
            enemy->posx += -y;
        }
        else
        {
            enemy->posy += y;
        }
    }
}

bohater* bohater_spawn(int mana, int hp, int stamina, int speed, int atak, char nazwa, int obrona=5)
{
    //bohater losowy_wojownik;
    bohater* losowy_wojownik = (bohater*)malloc(sizeof(bohater));
    losowy_wojownik->mana = mana;
    losowy_wojownik->hp = hp;
    losowy_wojownik->stamina = stamina;
    losowy_wojownik->obrona = obrona;
    losowy_wojownik->atak = atak;
    strcpy_s(losowy_wojownik->name, "Wojownik");
   // losowy_wojownik->name = (char)nazwa;
    return losowy_wojownik;
}
void referencje_bohater(bohater& wojownik)
{
    wojownik.atak = 5;
	wojownik.obrona = 5;
	wojownik.mana = 5;
	wojownik.hp = 100;
	wojownik.stamina = 100;
	wojownik.exp = 0;
	wojownik.lvl = 1;
	
	
}


przedmiot* item_create(int id,int width,int height,int cena,int obrazenia,int szybkosc_ataku,int wartosc_pancerza)
{
    przedmiot* item = (przedmiot*)malloc(sizeof(przedmiot));
    item->id = id;
    item->width = width;
    item->height = height;
    item->cena = cena;
    item->obrazenia = obrazenia;
    item->szybkosc_ataku = szybkosc_ataku;
    item->wartosc_pancerza = wartosc_pancerza;
    item->parent = item;
    strcpy_s(item->nazwa, "Miecz");
    return item;

}
bool checksize(int Equipment[eqheight][eqwidth], int posy, int posx, int y, int x)
{
    int licznik = 0;
    for (int a = posy; a < posy + y; a++)
    {
        for (int b = posx; b < posx + x; b++)
        {
            if (Equipment[a][b] == NULL)
            {
                licznik++;
            }
        }
    }
    if (licznik = x * y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void inventory_storage(przedmiot* item1, przedmiot* Eq[eqheight][eqwidth], int Equipment[eqheight][eqwidth], przedmiot* Eq_order[100])
{
    /*  if (Eq[0][0].parent = 0)
      {
          Eq[0][0] = *item1;
          Eq[0][0].parent = &Eq[0][0];
          item1->height;
          item1->width;
          item1->posx;
          item1->posy;
          for (int i = 0; i < item1->height; i++)
          {
              Eq[i][0].parent = &Eq[0][0];
          }



      }
  */
    int x = item1->height;
    int y = item1->width;
    for (int posy = 0; posy < eqheight; posy++)
    {
        for (int posx = 0; posx < eqwidth; posx++)
        {
            if (Eq[posy][posx] == NULL)
            {
                if (checksize(Equipment, posy, posx, y, x))
                {
                    for (int j = posy; j < posy + x; j++)
                    {
                        for (int i = posx; i < posx + y; i++)
                        {
                            Equipment[j][i] = itemid;
                            Eq[j][i] = item1;
                            Eq[j][i]->parent = Eq[j][i];
                            Eq_order[Equipment[j][i]] = item1;

                        }
                    }
                    itemid++;
                    posx = eqwidth;
                    posy = eqheight;

                }



            }

        }

    }



}

void map(bohater* wojownik,bohater* enemy)
{
    enemy->head = NULL;
    char filename[] = { "mapka.txt" };
    struct stat sb;
    if (stat(filename, &sb) == -1)
    {
        cout << "error stat" << endl;
        exit(EXIT_FAILURE);
    }

    FILE* in_file;
    fopen_s(&in_file, filename, "r");
    std::fstream plik3;
    string tekst;
    plik3.open(filename, std::ios::in);
    char* file_contents = (char*)malloc(sb.st_size);
    if (in_file != NULL)
    {

        
        fscanf_s(in_file, "%[^\n]", file_contents, sb.st_size);
        if (file_contents != NULL)
        {
            kolumny = strlen(file_contents);
        }
        fclose(in_file);


        
        if (plik3.is_open())
        {
            while (getline(plik3, tekst))
            {
                wiersze++;
            }
        }
       

        
        


    }
    plik3.close();
    mapa = (char**)malloc(wiersze * sizeof(char*));
    std::fstream plik;
    plik.open(MAP, std::ios::in);
   
		
    


    for (int i = 0; i < wiersze; i++)
    {
        mapa[i] = (char*)malloc(kolumny * sizeof(char));
    }
    
    for (int y = 0; y < wiersze; y++)
    {
        for (int x = 0; x < kolumny; x++)
        {

            plik >> mapa[y][x];
            
            if (mapa[y][x] == 'W')
            {
                wojownik->posx = x;
                wojownik->posy = y;
            }
            else if (mapa[y][x] == 'E')
            {
                
                /*enemy[k] = bohater_spawn(30, 10, 10, 10, 5, (char)"enemy");
               
               
                enemy[k]->move = &enemy1;
                enemy[k]->posx = x;
                enemy[k]->posy = y;
                */
                if (enemycount==0)
                {
                    enemy->head = NULL;
                }
                  enemy = lista(enemy, 1);
                  
                  enemy->tail->posx = x;
				  enemy->tail->posy = y;
                  enemycount++;
            }

        }
        cout << endl;
    }
    
    plik.close();
  //  return enemy;
    
}

void enemyspawn(bohater** enemy) // nie używane
{
    for (int i = 0; i < enemycount; i++)
    {
        enemy[i] = bohater_spawn(30, 10, 10, 10, 5, (char)"enemy");
        if (i % 2 == 0)
        {
            enemy[i]->move = &enemymove1;
        }
        else
        {
            enemy[i]->move = &enemymove2;
        }

        enemy[i]->posx = rand() % (wiersze - 1);
        enemy[i]->posy = rand() % (kolumny - 1);

        if (i > 0 && i < enemycount - 1)
        {
            enemy[i - 1]->next = enemy[i];
        }
    }

}

bohater* lista(bohater* enemy, int n)
{
    bohater* tymczasowy;
    if (enemy->head == NULL)
    {
        //enemy = bohater_spawn(30, 10, 10, 10, 5, (char)"enemy");
        enemy->atak = 10;
        enemy->obrona = 5;
		enemy->hp = 100;
        enemy->mana = 10;
        enemy->stamina = 10;
        enemy->head = enemy;
        enemy->prev = NULL;
        enemy->tail = enemy;
		enemy->move = &enemymove1;
        for (int i = 1; i < n; i++)
        {
            tymczasowy = enemy->tail;
            tymczasowy->next = bohater_spawn(30, 10, 10, 10, 5, (char)"enemy");
            if (rand() % 2 == 0)
            {
				tymczasowy->next->move = &enemymove1;
			}
			else
			{
				tymczasowy->next->move = &enemymove2;
            }
            enemy->tail = tymczasowy->next;
            
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        { 
            tymczasowy = enemy->tail;
            tymczasowy->next = bohater_spawn(30, 10, 10, 10, 5, (char)"enemy");
			if (rand() % 2 == 0)
            {
				tymczasowy->next->move = &enemymove1;
			}
			else
			{
				tymczasowy->next->move = &enemymove2;
            }
            enemy->tail = tymczasowy->next;
			enemy->tail->prev = tymczasowy;
            enemy->tail->next = NULL;
        }
    }
    return enemy;
}
bohater* enemyspawn2(bohater* enemy1) // nie używane
{
    bohater* tymczasowy;
    bohater* tymczasowy2;
    enemy1 = bohater_spawn(30, 10, 10, 10, 5, (char)"enemy");
    enemy1->posx = rand() % (wiersze - 1);
    enemy1->posy = rand() % (kolumny - 1);
    enemy1->next = bohater_spawn(30, 10, 10, 10, 5, (char)"enemy");
    enemy1->move = &enemymove1;
    tymczasowy = enemy1->next;
    tymczasowy->prev = enemy1;
    for (int i = 0; i < enemycount - 1; i++)
    {
        if (i % 2 == 0)
        {
            tymczasowy->move = &enemymove1;
        }
        else
        {
            tymczasowy->move = &enemymove2;
        }
        tymczasowy->posx = rand() % (wiersze - 1);
        tymczasowy->posy = rand() % (kolumny - 1);
        tymczasowy->next = bohater_spawn(30, 10, 10, 10, 5, (char)"enemy");
        tymczasowy2 = tymczasowy;
        
        tymczasowy = tymczasowy->next;
        if (i < enemycount - 1)
        {
            tymczasowy->prev = tymczasowy2;
            if (i == enemycount - 2)
            {
                tymczasowy->move = &enemymove1;
                tymczasowy->next = NULL;
            }

        }     
    }

    return enemy1;
}
void show_map(bohater* wojownik, bohater* enemy,bohater* bohaterowie[3])
{
    bohater* tymczasowy;
    for (int y = 0; y < wiersze; y++)
    {
        for (int x = 0; x < kolumny; x++)
        {
            tymczasowy = enemy;
            bool istrue = false; //jeśli jest true, wyświetli się wróg oraz nie nadpisze go innym znakiem
            while(tymczasowy !=NULL)
            {
                if (tymczasowy->posx == x && tymczasowy->posy == y)
                {
                    cout << "E";
                    
                    istrue = true;
                }
                if (tymczasowy != enemy->tail)
                {
                    tymczasowy = tymczasowy->next;
                }
                else
                {
                    break;
                }
            }
            if (istrue == false)
            {
                for(int i = 0; i < 3; i++)
				{
					if (bohaterowie[i]->posx == x && bohaterowie[i]->posy == y)
					{
						cout << "W";
                        istrue = true;
					}
				}
                if (x == wojownik->posx && y == wojownik->posy)
                {
                    cout << "W";

                }
                else
                {
                    if (istrue == false)
                    {
                        cout << '#';
                    }
                }
            }
            
        }
        cout << endl;
    }
    cout << endl;
}
/* {

    for (int y = 0; y < kolumny; y++)
    {
        for (int x = 0; x <wiersze; x++)
        {
            if (y == playerposy && x == playerposx)
            {
                printf("@");
            }

            else
            {
                printf("%c",mapa[0][0]);
            }
        }
        cout << endl;
    }
    cout << endl;
}*/

void zwolnijmape(char** mapa)
{
    for (int i = 0; i < wiersze; i++)
    {
        free(mapa[i]);
    }
    free(mapa);
}

void zwolnijprzeciwnikow(bohater* enemy)
{
    if (enemycount == 1)
    {
        free(enemy);
    }
    else
    {
        while (enemy->prev != NULL )
        {
            enemy = enemy->prev;
            free(enemy->next);

        }

        free(enemy);
    }
}

void poruszanie(int x, bohater* bohater)
{

    switch (x)
    {
    case  72:
        if (bohater->posy != 0)
        {
            bohater->posy--;
        }


        break;
    case 75:
        if (bohater->posx != 0)
        {
            bohater->posx--;
        }

        break;
    case 80:
        if (bohater->posy != wiersze - 1)
        {
            bohater->posy++;
        }

        break;
    case 77:
        if (bohater->posx != kolumny - 1)
        {
            bohater->posx++;
        }

        break;

    }
}


bool walka(bohater* wojownik, bohater* enemy)
{
    while (enemy->hp > 0 && wojownik->hp > 0)
    {
        if (wojownik->stamina > 0)
        {
            enemy->hp -= (wojownik->atak + wojownik->weaponslot[0]->obrazenia)* wojownik->weaponslot[0]->szybkosc_ataku;
            wojownik->stamina -= 5;
        }
        else
        {
            enemy->hp -= (wojownik->atak + wojownik->weaponslot[1]->obrazenia)*wojownik->weaponslot[1]->szybkosc_ataku;
        }
        if (enemy->stamina > 0)
        {
            wojownik->hp -= enemy->atak*2;
			enemy->stamina -= 5;
        }
        else
        {
			wojownik->hp -= enemy->atak ;
        }
    }
    return wojownik->hp > enemy->hp ? true : false;

}//nie uzywane
struct kolejka
{
    int wartoscataku;
    struct kolejka* next = NULL;
};
void dodajdokolejki(kolejka* ataki, bohater* wojownik, int x, int y)
{
    if (ataki->wartoscataku <= 0 || ataki->wartoscataku > 10000 || ataki->wartoscataku ==NULL)
    {
        if (x == 1 && y != 3)
        {
            ataki->wartoscataku = wojownik->atak * atak(zwyklyatak);
        }
        else if (x == 1 && y == 3)
        {
            ataki->wartoscataku = wojownik->atak * obrona(zwyklaobrona);
        }
        else if (x == 2 && y != 4)
        {
            ataki->wartoscataku = wojownik->atak * atak(poteznyatak) - obrona(zwyklaobrona);
        }
        else if (x == 2 && y == 4)
        {
            ataki->wartoscataku = wojownik->atak / obrona(unik);
        }
        else
        {
            ataki->wartoscataku = wojownik->atak;
			
        }
    }
    else
    {
        while (ataki->next != NULL)
        {
            ataki = ataki->next;
        }


        kolejka* nowy = (kolejka*)malloc(sizeof(kolejka));

        if (x == 1 && y != 3)
        {
            nowy->wartoscataku = wojownik->atak * atak(zwyklyatak);
        }
        else if (x == 1 && y == 3)
        {
            nowy->wartoscataku = wojownik->atak * obrona(zwyklaobrona);
        }
        else if (x == 2 && y != 4)
        {
            nowy->wartoscataku = wojownik->atak * atak(poteznyatak) - obrona(zwyklaobrona);
        }
        else if (x == 2 && y == 4)
        {
            nowy->wartoscataku = wojownik->atak / obrona(unik);
        }
        else
        {
            ataki->wartoscataku = wojownik->atak;

        }
        nowy->next = NULL;
        ataki->next = nowy;

    }




}
void wstaw(kolejka* ataki, bohater* wojownik, int x, int y)
{
    kolejka* nowy = (kolejka*)malloc(sizeof(kolejka));

}
kolejka* usun(kolejka* ataki)
{
 
  
        kolejka* tymczasowy = ataki;
        ataki = ataki->next;
        free(tymczasowy);
        return ataki;
}

bool walka2(bohater* wojownik, bohater* enemy)
{
    
  //  kolejka* head = ataki;
    int x = 0;
    int y = 0; //typ ataku przeciwnika
	while (enemy->hp > 0 && wojownik->hp > 0)
	{
        kolejka* ataki = (kolejka*)malloc(sizeof(kolejka));
        ataki->next = NULL;
       // ataki = head;
        cout << "Wybierz 3 ataki" << endl;
		cout << "1. Zwykły atak" << endl;
		cout << "2. Potężny atak" << endl;
		cout << "3. Obrona" << endl;
		cout<< "4. Unik" << endl;
        for (int p = 0; p < 3; p++)
        {
            scanf("%d", &x);
            y = rand() % 2 + 1;
            
            dodajdokolejki(ataki, wojownik, x, y); //atak gracza
            dodajdokolejki(ataki, enemy, y, x); //atak przeciwnika
			


        }
        while (ataki != NULL && enemy->hp > 0 && wojownik->hp >0)
        {
            enemy->hp -= ataki->wartoscataku * wojownik->weaponslot[0]->szybkosc_ataku - (ataki->wartoscataku % enemy->obrona) - wojownik->weaponslot[1]->wartosc_pancerza;
            ataki = usun(ataki);
		    wojownik->hp -= ataki->wartoscataku - ataki->wartoscataku % wojownik->obrona;
            ataki = usun(ataki);
			
        }
        while (ataki != NULL)
        {
			ataki = usun(ataki);
			
			
        }
        
	}
	return wojownik->hp > enemy->hp ? true : false;

}

bohater* usunprzeciwnika(bohater* enemy,bohater* pierwszyelementlisty)
{
	bohater* tymczasowy;
    if (enemy->next == NULL)
    {
        enemycount--;
        enemy->prev->next = NULL;
        //enemy->head->tail = enemy->prev;
        pierwszyelementlisty->tail = enemy->prev;
        tymczasowy = enemy->prev;
        free(enemy);
    }
    else if (enemy->prev == NULL)
    {
        enemycount--;
        enemy->next->head = enemy->next;
        enemy->next->prev = NULL;
		tymczasowy= enemy->next;//usuwam pierwszy element listy, muszę przypisać go do zmiennej
        pierwszyelementlisty = enemy->next; 
        free(enemy);
        
    }
	else
	{
        enemycount--;
		enemy->prev->next = enemy->next;
		enemy->next->prev = enemy->prev;
        tymczasowy = enemy->next;
		free(enemy);
	}
    return tymczasowy;
}

void zapis(bohater* wojownik, bohater* enemy)
{
    FILE* plikzapis;
    plikzapis = fopen("zapis.txt", "w");
    bohater* tymczasowy;
    for (int y = 0; y < wiersze; y++)
    {
        for (int x = 0; x < kolumny; x++)
        {
            tymczasowy = enemy;
            bool istrue = false; //jeśli jest true, wyświetli się wróg oraz nie nadpisze go innym znakiem
            while (tymczasowy != NULL)
            {
                if (tymczasowy->posx == x && tymczasowy->posy == y)
                {
                    fprintf(plikzapis, "%c", 'E');

                    istrue = true;
                }
                if (tymczasowy != enemy->tail)
                {
                    tymczasowy = tymczasowy->next;
                }
                else
                {
                    break;
                }
            }
            if (istrue == false)
            {
                if (x == wojownik->posx && y == wojownik->posy)
                {
                    fprintf(plikzapis, "%c", 'W');
                   

                }
                else
                {
                    fprintf(plikzapis, "%c", '#');
                    
                }
            }
        }
        fprintf(plikzapis, "\n");
    }

    fclose(plikzapis);
}
void zapiszekwipunek(przedmiot* Eq_order[100])
{
    FILE* plik = fopen("ekwipunek.txt", "w");
    
		if (Eq_order != NULL )
		{
            for (int i = 1; i < itemid; i++)
            {
                    fprintf(plik, "%s    %d     %d      %d     %d     %d      %d      %d\n", Eq_order[i]->nazwa, Eq_order[i]->cena, Eq_order[i]->height, Eq_order[i]->width, Eq_order[i]->id, Eq_order[i]->obrazenia, Eq_order[i]->szybkosc_ataku, Eq_order[i]->wartosc_pancerza);
            }
		}
    
}
void wczytajekwipunek(przedmiot* Eq[eqheight][eqwidth],int Ekwipunek[eqheight][eqwidth], przedmiot* Eq_order[100])
{
	FILE* plik = fopen("ekwipunek.txt", "r");
	char nazwa[20];
	int cena, height, width, id, obrazenia, szybkosc_ataku, wartosc_pancerza;
    if (plik)
    {
        while (!feof(plik))
        {
            if(fscanf(plik, "%s %d %d %d %d %d %d %d", nazwa, &cena, &height, &width, &id, &obrazenia, &szybkosc_ataku, &wartosc_pancerza)!=-1)
            {
                przedmiot* nowy = item_create(cena, height, width, id, obrazenia, szybkosc_ataku, wartosc_pancerza);
                inventory_storage(nowy, Eq, Ekwipunek, Eq_order);
            }
        }
    }
}
bohater* bohater_spawn2(int mana, int hp, int stamina, int speed, int atak, char nazwa, int obrona = 5)
{
    //bohater losowy_wojownik;
    bohater* losowy_wojownik = (bohater*)malloc(sizeof(bohater));
    losowy_wojownik->mana = mana;
    losowy_wojownik->hp = hp;
    losowy_wojownik->stamina = stamina;
    losowy_wojownik->obrona = obrona;
    losowy_wojownik->atak = atak;
    losowy_wojownik->posx = rand() % kolumny;
	losowy_wojownik->posy = rand() % wiersze;
    strcpy_s(losowy_wojownik->name, "Wojownik");
    // losowy_wojownik->name = (char)nazwa;
    return losowy_wojownik;
}
void zwolnikekwipunek( przedmiot* Eq[eqheight][eqwidth],int Ekwipunek[eqheight][eqwidth], przedmiot* Eq_order[100])
{
	free( Eq_order);
	

}

int main()
{

    srand(time(NULL));
    setlocale(LC_ALL, "pl-PL");
    bohater* nowy;
    bohater referencje;
    referencje_bohater(referencje);
    nowy = bohater_spawn(30, 1000, 10, 10, 10, (char)"bohater");
    przedmiot* item1 = item_create(1,1,3,100,20,1,0);
    przedmiot* Eq[eqheight][eqwidth] = {};
    int Equipment[eqheight][eqwidth] = {};
    przedmiot* Eq_order[100];
    inventory_storage(item1, Eq, Equipment, Eq_order);
    bohater* enemy1 = (bohater*)malloc (sizeof(bohater));
    //enemy1->head = enemy1;
   // enemy1->tail = enemy1;
     map(nowy,enemy1);
     bohater* enemy2[3];
     for (int i = 0; i < 3; i++)
     {
		enemy2[i]= bohater_spawn2( 30, 1000, 10, 10, 10, (char)"bohater");
     }
    wczytajekwipunek(Eq, Equipment, Eq_order);
   
    int weaponnumber = 1;
    show_map(nowy, enemy1,enemy2);
    int x = 0;
    bohater* head;
  
    int weaponchoose=1;
    while (x != 27)
    {
        head = enemy1;
        system("cls");
        show_map(nowy, enemy1,enemy2);
        x = _getch();
        x = _getch();
        if (x != 27)
        {
            poruszanie(x, nowy);


            for (int i = 0; i < enemycount; i++)
            {
                head->move(nowy, head);

                if (head->posx == nowy->posx && head->posy == nowy->posy)
                {
                    system("cls");

                    cout << "Wybierz 2 przedmioty" << endl; //armor , bron oraz potion(lub cos innego)
                    int iterator = 1;

                    while (iterator < itemid)
                    {
                        cout << iterator << ". " << Eq_order[iterator]->nazwa << "     atk:" << Eq_order[iterator]->obrazenia << "       szybkosc ataku: " << Eq_order[iterator]->szybkosc_ataku << endl;
                        iterator++;
                    }

                    for (int p = 0; p < 2; p++)
                    {
                        scanf("%d", &weaponchoose);
                        nowy->weaponslot[p] = Eq_order[weaponchoose];
                        cout << "Wybrane: " << Eq_order[weaponchoose]->nazwa<< "     atk:"<< Eq_order[weaponchoose]->obrazenia<<"       szybkosc ataku: "<<Eq_order[weaponchoose]->szybkosc_ataku << endl;

                    }
                    system("cls");
                    if (walka2(nowy, head))
                    {
                        if (rand() % 2 == 1) // losowanie nowego przedmiotu
                        {
                            item1 = item_create(itemid, rand() % 3 + 1, rand() % 3 + 1, rand() % 51 + 50, rand() % 11+10, rand() % 3+1, 0);
                            inventory_storage(item1, Eq, Equipment, Eq_order);
                        }
                        else if (rand() % 100 == 2)
                        {
							item1 = item_create(itemid, rand() % 3 + 1, rand() % 3 + 1, rand() % 51 + 50, rand() % 11 + 10, rand() % 3 + 1, 0);
							inventory_storage(item1, Eq, Equipment, Eq_order);
                        }
                        if (enemycount == 1)
                        {
                            free(head);
                            enemycount--;
                        }
						
                        else
                        {
                            head = usunprzeciwnika(head, enemy1);
                            if (head->prev == NULL)
                            {
                                enemy1 = head;
                            }
                        }
                        cout << "Wygrałeś" << endl;
                    }
                    else
                    {
                        cout << "Przegrałeś" << endl;
                        x = 27;
                    }
                    printf("HP = %i\n", nowy->hp);
                    getchar();
                    
                }
                if (enemycount == 0)
                {
                    x = 27;
                    cout << "Wygrałeś grę" << endl;
                    i = enemycount;

                }
                else if (head->next != NULL)
                {
                    head = head->next;

                }

            }
            if (x == 'e')
            {
                
                int iterator = 1;
                while (iterator < itemid)
                {
                    cout << iterator << ". " << Eq_order[iterator]->nazwa << "     atk:" << Eq_order[weaponchoose]->obrazenia << "       szybkosc ataku: " << Eq_order[weaponchoose]->szybkosc_ataku << endl;
                    iterator++;
                }
                getchar();
            }
            
        }
        if (enemycount > 0)
        {
            zapis(nowy, enemy1);
        }
		
       
    }
    
    zapiszekwipunek(Eq_order);
    if (enemycount > 0)
    {
        zapis(nowy, enemy1);
        zwolnijprzeciwnikow(enemy1);
    }
    zwolnijmape(mapa);
    return 0;
}
