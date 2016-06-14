/*   ** 遊戲設計說明：
     1. 踩地雷有9*9的格子，共10顆地雷
     2. 顯示數字為那一格附近的八個地區共有幾顆地雷
        未顯示數字則表示附近的八個地區沒地雷 

     ** 程式設計說明：
     1. 將格子宣告成int cells[9][9]的陣列，存放資訊之用
            0  代表安全的地區，且附近沒地雷 
         1~ 8  代表安全的地區，但附近有地雷，數字為地雷數 
           -1  代表尚未被踩到的地雷區
        10~18  代表已被選取的安全地區
           -2  代表已被踩到的地雷區，遊戲結束
           
     2. 在螢幕上印出格子
     3. 請使用者輸入第一個要打開的位置(x, y) 
     2. 利用亂數放置地雷十顆，在不重複的位置且不是使用者輸入的位址
     4. 在安全地區計算其資訊(附近幾顆地雷)
     5. 將剛被選取到的安全地區值加10(代表已選取) 
     6. 清除螢幕
     7. 顯示cells陣列中，值>10的資訊（>10代表已經選取）
     8. 請使用者輸入接下來要打開的位置(x2, y2)
     9. 計算(x2, y2)的值 (安全-> cells[x2][y2] += 10；地雷-> cells[x2][y2] = -2，遊戲結束)
    10. 如果cells[x2, y2]的值為10，則打開附近的格子
    10. 若未結束則重複step 6 ~ 9，直到贏(全部都>10 or ==-1 )就跳出 
    11. 詢問是否再玩一次，若再玩一次則重複2~10 
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void assign_initial(int cells[][11]);                                           //將格子內資訊初始化為0
void print_blanks(void);                                                        //印出遊戲初始的格子 
void open_cell(int *op_x, int *op_y);                                           //請使用者輸入要打開的位置
void put_mine(int cells[][11], int op_x, int op_y);                             //放置地雷
void calculate_num_of_cells(int cells[][11]);                                   //計算非地雷區附近有幾顆地雷 
void assign_inf_after_open(int cells[][11], int op_x, int op_y);                //改變使用者打開的位置之資訊
void open_surrounding(int cells[][11], int p_x, int op_y);                      //打開附近的區域（當格子附近無地雷時） 
void check_no_mine(int cells[][11], int op_x, int op_y);                        //檢查附近的區域有沒有地雷 
int  check_over(int cells[][11], int op_x, int op_y);                           //檢查遊戲是否結束(輸或贏)
void print_cells(int cells[][11], int op_x, int op_y, int over);                //印出目前的狀況
void print_condition_playing(int cells[][11]);                                  //印出尚未結束的狀況
void print_condition_over(int cells[][11], int over);                           //印出遊戲結束的狀況(每個格子之資訊) 
char play_again(void);                                                          //詢問是否再玩一次

int main(void) {
    int  cells[11][11],
         open_x, open_y,
         over;
    char again;

    do {
       system("cls");
       assign_initial(cells);                                                   //將格子內資訊初始化為0
       print_blanks();                                                          //印出遊戲初始的格子 
       open_cell(&open_x, &open_y);                                             //請使用者輸入要打開的位置
       put_mine(cells, open_x, open_y);                                         //放置地雷
       calculate_num_of_cells(cells);                                           //計算非地雷區附近有幾彈地雷
       assign_inf_after_open(cells, open_x, open_y);                            //改變使用者打開的位置之資訊
       check_no_mine(cells, open_x, open_y);                                    //檢查附近的區域有沒有地雷，並將無地雷的區域打開
       over = check_over(cells, open_x, open_y);                                //檢查遊戲是否結束(輸或贏)
       print_cells(cells, open_x, open_y, over);                                //印出目前的狀況
       while (over == 0) {
             open_cell(&open_x, &open_y);
             assign_inf_after_open(cells, open_x, open_y);                      //請使用者輸入要打開的位置
             check_no_mine(cells, open_x, open_y);                              //檢查附近的區域有沒有地雷，並將無地雷的區域打開
             over = check_over(cells, open_x, open_y);                          //檢查遊戲是否結束(輸或贏)
             print_cells(cells, open_x, open_y, over);                          //印出目前的狀況
       }
       again = play_again();                                                    //詢問是否再玩一次
    } while (again == 'Y' || again == 'y');

    return(0);
}

void assign_initial(int cells[][11]) {                                          //將格子內資訊初始化為0 
     int i, j;
     for (i = 0; i < 11; i++)
         for (j = 0; j < 11; j++)
             cells[i][j] = 0;
}

void print_blanks(void) {                                                       //印出遊戲初始的格子 
     int i, j;
     printf("              遊戲說明：\n");
     printf("---------------------------------------\n");
     printf("※ 要開啟最左上角那格請輸入1 1\n");
     printf("   往下一格則左邊的值+1(輸入：2 1)\n");
     printf("   往右一格則右邊的值+1(輸入：1 2)\n");
     printf("   其餘以此類推，從1 1 ~ 9 9\n");
     printf("   輸入格式為：數字空格數字，如：8 2\n\n");
     printf("※ 可一次輸入多格座標，\n");
     printf("   座標間只需以非數字符號隔開就可以了！\n");
     printf("   祝您遊戲愉快！:)\n");
     printf("---------------------------------------\n\n");
     printf("    ");
     for (i = 1; i <= 9; i++)
         printf("%2d", i);
     printf("\n");
     for (i = 1; i <= 9; i++) {
         for (j = 0; j <= 9; j++) {
             if (j == 0)
                printf("%4d", i); 
             else
                 printf("口");
         }
         printf("\n");
     }
}

void open_cell(int *op_x, int *op_y) {                                          //請使用者輸入要打開的位置
     int x, y;
     printf("\n輸入您要開啟的座標 >> ");
     scanf("%d%d", op_x, op_y);
}

void put_mine(int cells[][11], int op_x, int op_y) {                            //放置地雷
     srand(time(NULL));          //  亂數種子 
     int  n = 0,
          rand_num,
          cell_x,
          cell_y;

     do {
         rand_num = rand() % 81;     // ( rand() % (最大值-最小值+1)) + 最小值
         cell_x = (rand_num % 9) + 1;
         cell_y = ((rand_num - cell_x) / 9) + 1;
         if (cells[cell_x][cell_y] != -1 && !(cell_x == op_x && cell_y == op_y)) {
             cells[cell_x][cell_y] = -1;
             n++;
         }
     } while (n < 10);
}

void calculate_num_of_cells(int cells[][11]) {                                  //計算非地雷區附近有幾彈地雷 
     int i, j, u, v;
     for (i = 1; i <= 9; i++)
         for (j = 1; j <= 9; j++)
             if (cells[i][j] == 0)
                for (u = i - 1; u <= i + 1; u++)
                    for (v = j - 1; v <= j + 1; v++)
                        if (cells[u][v] == -1)
                           cells[i][j]++;
}

void assign_inf_after_open(int cells[][11], int op_x, int op_y) {               //改變使用者打開的位置之資訊 
     if (cells[op_x][op_y] == -1)
        cells[op_x][op_y] = -2;
     if (cells[op_x][op_y] >= 0 && cells[op_x][op_y] <= 8)
        cells[op_x][op_y] += 10;
}

void open_surrounding(int cells[][11], int op_x, int op_y) {                    //打開附近的區域（當格子附近無地雷時） 
     int i, j;
     for (i = op_x - 1; i <= op_x + 1; i++) {
         for (j = op_y - 1; j <= op_y + 1; j++) {
             if (cells[i][j] >= 0 && cells[i][j] <=8 && i % 10 != 0 && j %10 != 0) {
                cells[i][j] += 10;
                check_no_mine(cells, i, j);
             }
         }
     }
}

void check_no_mine(int cells[][11], int op_x, int op_y) {                       //檢查附近的區域有沒有地雷
     if (cells[op_x][op_y] == 10)        //附近沒地雷 
        open_surrounding(cells, op_x, op_y);
}

void print_condition_playing(int cells[][11]) {                                 //印出尚未結束的狀況
     int i, j;
     printf("      ");
     for (i = 1; i <= 9; i++)
         printf("%2d", i);
     printf("\n    ┌－－－－－－－－－┐\n");
     for (i = 1; i <= 9; i++) {
             for (j = 0; j <= 9; j++) { 
                 if (j == 0)
                    printf("%4d｜", i); 
                 else if (cells[i][j] < 10)
                      printf("口");
                 else if (cells[i][j] == 10)
                      printf(" 0");
                 else if (cells[i][j] > 10 && cells[i][j] <= 18)
                      printf(" %d", cells[i][j] - 10);
                 if (j == 9)
                    printf("｜%d", i); 
         }
         printf("\n");
     }
     printf("    └－－－－－－－－－┘\n");
     printf("      ");
     for (i = 1; i <= 9; i++)
         printf("%2d", i);
     printf("\n");
}
     
     
void print_condition_over(int cells[][11], int over) {                          //印出遊戲結束的狀況(每個格子之資訊) 
     int i, j;
     printf("  ┌－－－－－－－－－┐\n");
     for (i = 1; i <= 9; i++) {
         for (j = 0; j <= 10; j++) {
             if (j  == 0)
                printf("  ｜");
             else if (j == 10)
                  printf("｜"); 
             else if(cells[i][j] % 10 == 0)
                  printf("．");
             else if (cells[i][j] == -1)
                  printf(" *");
             else if (cells[i][j] == -2)
                  printf("⊕");
             else
                 printf("%2d", cells[i][j] % 10);
         }
         printf("\n");
     }
     printf("  └－－－－－－－－－┘\n");
     if (over == 1)
        printf("．ˇ．恭喜你～～贏了！\n\n");
     else
         printf("ˊ＿ˋ爆了…… \n\n");
     printf("數字代表周圍八格地雷總數量\n");
     printf("*代表地雷\n");
     printf("．代表周圍沒地雷\n");
     printf("⊕代表爆掉的地雷。\n");
     printf("感謝您的賞光～～～\n");
}
     
void print_cells(int cells[][11], int op_x, int op_y, int over) {               //印出目前的狀況
     system("cls");
     printf("\n");
     int i, j;
     if (over == 0) {
        print_condition_playing(cells);
     } else
           print_condition_over(cells, over);
}

int  check_over(int cells[][11], int op_x, int op_y) {                          //檢查遊戲是否結束(輸或贏)
    //result == 0 ->尚未結束，result == 1 ->贏，result == -1 ->輸
    int i, j, result = 1;
    if (cells[op_x][op_y] == -2) {
       result = -1;
    } else {
           for (i = 1; i <= 9 && result == 1; i++)
               for (j = 1; j <= 9 && result == 1; j++)
                   if ((cells[i][j] >= 0 && cells[i][j] <= 8))
                      result = 0;
    }
    return(result);
}

char play_again(void) {                                                         //詢問是否再玩一次
     char again;
     printf("\n還要再玩一次嗎？");
     do {
        printf("\n要再玩一次的話請輸入Y，\n");
        printf("或輸入N關閉程式。 >>");
        scanf(" %c", &again);
     } while (again != 'Y' && again != 'y' && again != 'N' && again != 'n');
     return(again);
}
