#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


/*      +
        +
        +
        +
++++++++++++++++++
        +
        +
        +
        +    
  - Aby bonusový úkol1 fungoval, musí se oddělat z poznámek všechny funkce končící _b1 a označit do poznámek jejich sousední funkce z normálního zadání
  + se musí odpoznámkovat cyklus na tvoření překážek

  - Aby fungovala animce, musí se oddělat funkce animace() v mainu z poznámek
*/

int zelva_row[3];
int zelva_col[3];
int zelva_smer[3];
int pocet_zelv = 1;

void inicializace_pole (char *pole, int rows, int cols){
    for (int i = 0; i < rows * cols; i++)
    {
        pole[i] = '.';
    }
    
}

void tvorba_pole (char *pole, int rows, int cols){
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%c", pole[i * cols + j]);
        }
        printf("\n");
    }
}

void otoceni_zelv_doprava(){
    for (int i = 0; i < pocet_zelv; i++)
    {
        zelva_smer[i] = (zelva_smer[i] + 1) % 4;
    }
    
}

void otoceni_zelv_doleva(){
    for (int i = 0; i < pocet_zelv; i++)
    {
        zelva_smer[i] = (zelva_smer[i] + 3) % 4;
    }
    
}

void presun_zelv(int rows, int cols){
    for (int i = 0; i < pocet_zelv; i++)
    {
        if (zelva_smer[i] == 0){
            zelva_col[i] = (zelva_col[i] + 1) % cols;
        }
        if (zelva_smer[i] == 1){
            zelva_row[i] = (zelva_row[i] + 1) % rows;
        }
        if (zelva_smer[i] == 2){
            zelva_col[i] = (zelva_col[i] - 1 + cols) % cols;
        }
        if (zelva_smer[i] == 3){
            zelva_row[i] = (zelva_row[i] - 1 + rows) % rows;
        }
    }
    
}

void vykreslovani(char *pole, int rows, int cols){
    for (int i = 0; i < pocet_zelv; i++)
    {
        int r = zelva_row[i];
        int c = zelva_col[i];
        int index = r * cols + c;

        if(pole[index] == '.'){
            pole[index] = 'o';
        }
        else
        {
            pole[index] = '.';
        }
        
    }
    
}

void pridani_zelvy(){
    if(pocet_zelv < 3){
        zelva_row[pocet_zelv] = 0;
        zelva_col[pocet_zelv] = 0;
        zelva_smer[pocet_zelv] = 0;
        pocet_zelv++;
    }
}


// VOIDY PRO BONUSOVÝ ÚKOL 1

void presun_zelv_b1(int rows, int cols, char *pole){
    for (int i = 0; i < pocet_zelv; i++)
    {
        int bonus1_r = zelva_row[i];
        int bonus1_c = zelva_col[i];
        if (zelva_smer[i] == 0){
            bonus1_c = (bonus1_c + 1) % cols;
        }
        if (zelva_smer[i] == 1){
            bonus1_r = (bonus1_r + 1) % rows;
        }
        if (zelva_smer[i] == 2){
            bonus1_c = (bonus1_c - 1 + cols) % cols;
        }
        if (zelva_smer[i] == 3){
            bonus1_r = (bonus1_r - 1 + rows) % rows;
        }
        int novy_index = bonus1_r * cols + bonus1_c;

        if (pole[novy_index] != '#')
        {
            zelva_row[i] = bonus1_r;
            zelva_col[i] = bonus1_c;
        }
        
    }    
}

void inicializace_pole_b1 (char *pole, int rows, int cols){
    for (int i = 0; i < rows * cols; i++)
    {
        pole[i] = ' ';
    }
    
}

int S = 2;
int vygeneruj_cislo(int max){
    S = (S * 17 + 43) % 97;
    return S % max;
}

void vykreslovani_prekazek(char *pole, int rows, int cols){
    int r = vygeneruj_cislo(rows);
    int c = vygeneruj_cislo(cols);
    int index = r * cols + c;

    if(pole[index] == ' ' || pole[index] == 'o'){
        pole[index] = '#';
    }    
}

void vykreslovani_b1(char *pole, int rows, int cols){
    for (int i = 0; i < pocet_zelv; i++)
    {
        int r = zelva_row[i];
        int c = zelva_col[i];
        int index = r * cols + c;

        if(pole[index] == ' '){
            pole[index] = 'o';
        }
        else
        {
            pole[index] = ' ';
        }
        
    }
    
}

// VOIDY PRO ANIMACI 
void flush() {
  fflush(stdout);
}

void animate_ms(int ms) {
  usleep(1000 * ms);
}

void clear_screen(){
    printf("\x1b[2J");
    flush();
}

void move_to (int row, int col){
  printf("\x1b[%d;%dH", row, col);
  flush();
}

void animace () {
    int rows = 7;
    int cols = 7;
    int kroky = 6;
    char *pole = malloc(rows * cols * sizeof(char));
    
    for (int i = 0; i < rows * cols; i++) //inicializace 
    {
        pole[i] = ' ';
    }
    
    clear_screen();

    for (int i = 0; i < rows; i++) //vykrelseni prazdneho pole
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%c", pole[i * cols + j]);
        }
    }
    for (int x = 1; x <= rows; x++ ){ //animace
        for (int i = 1; i <= kroky; i++)
        {
            presun_zelv(rows, cols);

            for (int j = 0; j < pocet_zelv; j++)
            {
                int r = zelva_row[j];
                int c = zelva_col[j];
                int index = r * cols + c;

                move_to(x, c);
                animate_ms(100);
                printf("z");
                flush();

                move_to(x,c);
                animate_ms(100);
                printf("o");
                flush();
                
                pole[index] = 'o';
            }
            animate_ms(200);
        }
    }
    move_to(rows + 1, 0);
    free(pole);
}

int main (){
    int rows = 0;
    int cols = 0;
    scanf("%d%d", &rows, &cols);
    char *pole = malloc(rows * cols * sizeof(char));

    inicializace_pole(pole, rows, cols);
    //inicializace_pole_b1(pole, rows, cols); //bonusový úkol 1 - překážky
    
    /*for (int i = 0; i < (rows * cols / 10); i++)
    {
        vykreslovani_prekazek(pole, rows, cols);
    }*/

    zelva_row[0] = 0;
    zelva_col[0] = 0;
    zelva_smer[0] = 0;

    char vstup;
    while (scanf (" %c", &vstup) == 1){
        if (vstup == 'x'){
            break;
        }
        if (vstup == 'r'){
            otoceni_zelv_doprava();
        }
        if (vstup == 'l'){
            otoceni_zelv_doleva();
        }
        if (vstup == 'm'){
            presun_zelv(rows, cols);
            //presun_zelv_b1(rows, cols, pole);
        }
        if (vstup == 'o'){
            //vykreslovani_b1(pole, rows, cols);
            vykreslovani(pole, rows, cols);
        }
        if (vstup == 'f'){
            pridani_zelvy();
        }
    }
    tvorba_pole(pole, rows, cols);

    //animace();  //animace
    
    free(pole);
    return 0;
}
