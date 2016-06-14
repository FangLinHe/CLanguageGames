/*   ** �C���]�p�����G
     1. ��a�p��9*9����l�A�@10���a�p
     2. ��ܼƦr�����@����񪺤K�Ӧa�Ϧ@���X���a�p
        ����ܼƦr�h��ܪ��񪺤K�Ӧa�ϨS�a�p 

     ** �{���]�p�����G
     1. �N��l�ŧi��int cells[9][9]���}�C�A�s���T����
            0  �N��w�����a�ϡA�B����S�a�p 
         1~ 8  �N��w�����a�ϡA�����񦳦a�p�A�Ʀr���a�p�� 
           -1  �N��|���Q��쪺�a�p��
        10~18  �N��w�Q������w���a��
           -2  �N��w�Q��쪺�a�p�ϡA�C������
           
     2. �b�ù��W�L�X��l
     3. �ШϥΪ̿�J�Ĥ@�ӭn���}����m(x, y) 
     2. �Q�ζüƩ�m�a�p�Q���A�b�����ƪ���m�B���O�ϥΪ̿�J����}
     4. �b�w���a�ϭp����T(����X���a�p)
     5. �N��Q����쪺�w���a�ϭȥ[10(�N��w���) 
     6. �M���ù�
     7. ���cells�}�C���A��>10����T�]>10�N��w�g����^
     8. �ШϥΪ̿�J���U�ӭn���}����m(x2, y2)
     9. �p��(x2, y2)���� (�w��-> cells[x2][y2] += 10�F�a�p-> cells[x2][y2] = -2�A�C������)
    10. �p�Gcells[x2, y2]���Ȭ�10�A�h���}���񪺮�l
    10. �Y�������h����step 6 ~ 9�A����Ĺ(������>10 or ==-1 )�N���X 
    11. �߰ݬO�_�A���@���A�Y�A���@���h����2~10 
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void assign_initial(int cells[][11]);                                           //�N��l����T��l�Ƭ�0
void print_blanks(void);                                                        //�L�X�C����l����l 
void open_cell(int *op_x, int *op_y);                                           //�ШϥΪ̿�J�n���}����m
void put_mine(int cells[][11], int op_x, int op_y);                             //��m�a�p
void calculate_num_of_cells(int cells[][11]);                                   //�p��D�a�p�Ϫ��񦳴X���a�p 
void assign_inf_after_open(int cells[][11], int op_x, int op_y);                //���ܨϥΪ̥��}����m����T
void open_surrounding(int cells[][11], int p_x, int op_y);                      //���}���񪺰ϰ�]���l����L�a�p�ɡ^ 
void check_no_mine(int cells[][11], int op_x, int op_y);                        //�ˬd���񪺰ϰ즳�S���a�p 
int  check_over(int cells[][11], int op_x, int op_y);                           //�ˬd�C���O�_����(���Ĺ)
void print_cells(int cells[][11], int op_x, int op_y, int over);                //�L�X�ثe�����p
void print_condition_playing(int cells[][11]);                                  //�L�X�|�����������p
void print_condition_over(int cells[][11], int over);                           //�L�X�C�����������p(�C�Ӯ�l����T) 
char play_again(void);                                                          //�߰ݬO�_�A���@��

int main(void) {
    int  cells[11][11],
         open_x, open_y,
         over;
    char again;

    do {
       system("cls");
       assign_initial(cells);                                                   //�N��l����T��l�Ƭ�0
       print_blanks();                                                          //�L�X�C����l����l 
       open_cell(&open_x, &open_y);                                             //�ШϥΪ̿�J�n���}����m
       put_mine(cells, open_x, open_y);                                         //��m�a�p
       calculate_num_of_cells(cells);                                           //�p��D�a�p�Ϫ��񦳴X�u�a�p
       assign_inf_after_open(cells, open_x, open_y);                            //���ܨϥΪ̥��}����m����T
       check_no_mine(cells, open_x, open_y);                                    //�ˬd���񪺰ϰ즳�S���a�p�A�ñN�L�a�p���ϰ쥴�}
       over = check_over(cells, open_x, open_y);                                //�ˬd�C���O�_����(���Ĺ)
       print_cells(cells, open_x, open_y, over);                                //�L�X�ثe�����p
       while (over == 0) {
             open_cell(&open_x, &open_y);
             assign_inf_after_open(cells, open_x, open_y);                      //�ШϥΪ̿�J�n���}����m
             check_no_mine(cells, open_x, open_y);                              //�ˬd���񪺰ϰ즳�S���a�p�A�ñN�L�a�p���ϰ쥴�}
             over = check_over(cells, open_x, open_y);                          //�ˬd�C���O�_����(���Ĺ)
             print_cells(cells, open_x, open_y, over);                          //�L�X�ثe�����p
       }
       again = play_again();                                                    //�߰ݬO�_�A���@��
    } while (again == 'Y' || again == 'y');

    return(0);
}

void assign_initial(int cells[][11]) {                                          //�N��l����T��l�Ƭ�0 
     int i, j;
     for (i = 0; i < 11; i++)
         for (j = 0; j < 11; j++)
             cells[i][j] = 0;
}

void print_blanks(void) {                                                       //�L�X�C����l����l 
     int i, j;
     printf("              �C�������G\n");
     printf("---------------------------------------\n");
     printf("�� �n�}�ҳ̥��W������п�J1 1\n");
     printf("   ���U�@��h���䪺��+1(��J�G2 1)\n");
     printf("   ���k�@��h�k�䪺��+1(��J�G1 2)\n");
     printf("   ��l�H�������A�q1 1 ~ 9 9\n");
     printf("   ��J�榡���G�Ʀr�Ů�Ʀr�A�p�G8 2\n\n");
     printf("�� �i�@����J�h��y�СA\n");
     printf("   �y�ж��u�ݥH�D�Ʀr�Ÿ��j�}�N�i�H�F�I\n");
     printf("   ���z�C���r�֡I:)\n");
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
                 printf("�f");
         }
         printf("\n");
     }
}

void open_cell(int *op_x, int *op_y) {                                          //�ШϥΪ̿�J�n���}����m
     int x, y;
     printf("\n��J�z�n�}�Ҫ��y�� >> ");
     scanf("%d%d", op_x, op_y);
}

void put_mine(int cells[][11], int op_x, int op_y) {                            //��m�a�p
     srand(time(NULL));          //  �üƺؤl 
     int  n = 0,
          rand_num,
          cell_x,
          cell_y;

     do {
         rand_num = rand() % 81;     // ( rand() % (�̤j��-�̤p��+1)) + �̤p��
         cell_x = (rand_num % 9) + 1;
         cell_y = ((rand_num - cell_x) / 9) + 1;
         if (cells[cell_x][cell_y] != -1 && !(cell_x == op_x && cell_y == op_y)) {
             cells[cell_x][cell_y] = -1;
             n++;
         }
     } while (n < 10);
}

void calculate_num_of_cells(int cells[][11]) {                                  //�p��D�a�p�Ϫ��񦳴X�u�a�p 
     int i, j, u, v;
     for (i = 1; i <= 9; i++)
         for (j = 1; j <= 9; j++)
             if (cells[i][j] == 0)
                for (u = i - 1; u <= i + 1; u++)
                    for (v = j - 1; v <= j + 1; v++)
                        if (cells[u][v] == -1)
                           cells[i][j]++;
}

void assign_inf_after_open(int cells[][11], int op_x, int op_y) {               //���ܨϥΪ̥��}����m����T 
     if (cells[op_x][op_y] == -1)
        cells[op_x][op_y] = -2;
     if (cells[op_x][op_y] >= 0 && cells[op_x][op_y] <= 8)
        cells[op_x][op_y] += 10;
}

void open_surrounding(int cells[][11], int op_x, int op_y) {                    //���}���񪺰ϰ�]���l����L�a�p�ɡ^ 
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

void check_no_mine(int cells[][11], int op_x, int op_y) {                       //�ˬd���񪺰ϰ즳�S���a�p
     if (cells[op_x][op_y] == 10)        //����S�a�p 
        open_surrounding(cells, op_x, op_y);
}

void print_condition_playing(int cells[][11]) {                                 //�L�X�|�����������p
     int i, j;
     printf("      ");
     for (i = 1; i <= 9; i++)
         printf("%2d", i);
     printf("\n    �z�ССССССССТ{\n");
     for (i = 1; i <= 9; i++) {
             for (j = 0; j <= 9; j++) { 
                 if (j == 0)
                    printf("%4d�U", i); 
                 else if (cells[i][j] < 10)
                      printf("�f");
                 else if (cells[i][j] == 10)
                      printf(" 0");
                 else if (cells[i][j] > 10 && cells[i][j] <= 18)
                      printf(" %d", cells[i][j] - 10);
                 if (j == 9)
                    printf("�U%d", i); 
         }
         printf("\n");
     }
     printf("    �|�ССССССССТ}\n");
     printf("      ");
     for (i = 1; i <= 9; i++)
         printf("%2d", i);
     printf("\n");
}
     
     
void print_condition_over(int cells[][11], int over) {                          //�L�X�C�����������p(�C�Ӯ�l����T) 
     int i, j;
     printf("  �z�ССССССССТ{\n");
     for (i = 1; i <= 9; i++) {
         for (j = 0; j <= 10; j++) {
             if (j  == 0)
                printf("  �U");
             else if (j == 10)
                  printf("�U"); 
             else if(cells[i][j] % 10 == 0)
                  printf("�D");
             else if (cells[i][j] == -1)
                  printf(" *");
             else if (cells[i][j] == -2)
                  printf("��");
             else
                 printf("%2d", cells[i][j] % 10);
         }
         printf("\n");
     }
     printf("  �|�ССССССССТ}\n");
     if (over == 1)
        printf("�D���D���ߧA���Ĺ�F�I\n\n");
     else
         printf("���ģ��z�F�K�K \n\n");
     printf("�Ʀr�N��P��K��a�p�`�ƶq\n");
     printf("*�N��a�p\n");
     printf("�D�N��P��S�a�p\n");
     printf("��N���z�����a�p�C\n");
     printf("�P�±z���������\n");
}
     
void print_cells(int cells[][11], int op_x, int op_y, int over) {               //�L�X�ثe�����p
     system("cls");
     printf("\n");
     int i, j;
     if (over == 0) {
        print_condition_playing(cells);
     } else
           print_condition_over(cells, over);
}

int  check_over(int cells[][11], int op_x, int op_y) {                          //�ˬd�C���O�_����(���Ĺ)
    //result == 0 ->�|�������Aresult == 1 ->Ĺ�Aresult == -1 ->��
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

char play_again(void) {                                                         //�߰ݬO�_�A���@��
     char again;
     printf("\n�٭n�A���@���ܡH");
     do {
        printf("\n�n�A���@�����ܽп�JY�A\n");
        printf("�ο�JN�����{���C >>");
        scanf(" %c", &again);
     } while (again != 'Y' && again != 'y' && again != 'N' && again != 'n');
     return(again);
}
