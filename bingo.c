#include<stdio.h>
#include<time.h>

// �L�X�C�������P�W�h
void print_rules(void);

// �L�X��J���Ǫ���l
void print_initial_cells(void);

// �N��l���Ȫ�l�Ƭ�-1
void initial_cells(int cells[]);

// �񺡪��a����l�]�H���Φۤv��J�^
void fill_player_cells(int cells[]);

// �H����J�Ʀr
void random_fill_cells(int cells[]);

// ���տ�J�Ʀr�O�_�ŦX�d��έ���
int  error(int cells[], int enter_number);

// �L�X�ثe��l���Ʀr�γQ�������a��
void print_now(int cells[]);

// �L�X�ثe�q��������
void print_computer_cells(int computer_cells[]);

// �u�����Ű}�C��l��
void initial_level_array(int level_array[]);

// ���V�������Ʀr�Ҧb��l
void assign_cells_p(int cells[], int *cells_p[]);

// ���a��J�n�������Ʀr
int  player_enter_number(int player_cells[], int *player_cells_p[]);

// ���ܪ��a��J���Ʀr�������u������
void filter_level_array(int level_array[], int computer_index);

// ��X���a��J���Ʀr�������q����l
int  find_computer_index(int computer_cells[], int p_choose_number);

// �N��ܪ��Ʀr�]����
void clear_number(int *cells_p[], int enter_num);

// �q���۰ʿ�ܭn�������Ʀr
int  choose_computer_number(int computer_cells[], int level_array[]);

// ��X�Ĥ@���u�����ų̰�����l
int  find_max(int level_array[]);

// �N��ܫ᪺�Ƭ����s�u�u������+1
void level_array_add(int level_array[], int choose_cell);

// �p��ثe�������X���u
int  determine_line_vertical(int cells[]);

// �p��ثe����X���u
int  determine_line_horizontal(int cells[]);

// �p��ثe��e�����X���u
int  determine_line_cross(int cells[]);

// �p��ثe�`�@���X���u
int  determine_line_total(int cells[]);

// �L�X�ثe���a��q���U���X���u�A�öǦ^�C���O�_����
int  print_lines(int player_cells[], int computer_cells[]);

// �L�X�C�����G�A�C�������C
void print_over_information(int result); 

int main(void) {
    int  p_cells[25],        //���a�b��l�̨̧Ƕ�g���Ʀr
        *p_cells_p[25],      //���V���a�Ʀr�Ҧb����l
         c_cells[25],        //�q���b��l�̨̧Ƕ񺡪��Ʀr
        *c_cells_p[25],      //���V�q���Ʀr�Ҧb����l
         l_array[25],        //�q���s��︹�u�����Ū��}�C
         over,                     //�C���O�_�����G0���|�������A>0������
         p_choose_number,          //���a��ܪ����X
         p_choose_c_cells_index,   //���a��ܪ����X������q������l
         c_choose_number;          //�q����ܪ����X
    char pause;                    //�Ȱ�����
    print_rules();                 //�L�X�C�������P�W�h
    print_initial_cells();         //�L�X��J���Ǫ���l
    initial_cells(p_cells);        //�N��l���Ȫ�l�Ƭ�0
    srand(time(NULL));             //�üƺؤl
    fill_player_cells(p_cells);    //�񺡪��a����l�]�H���Φۤv��J�^
    srand(time(NULL));             //�üƺؤl
    random_fill_cells(c_cells);    //�񺡹q������l�]�H���^
    initial_level_array(l_array);  //�u�����Ű}�C��l��
    assign_cells_p(p_cells, p_cells_p);  //�Np_cells_p���V�������Ʀr�Ҧb��l
    assign_cells_p(c_cells, c_cells_p);  //�Nc_cells_p���V�������Ʀr�Ҧb��l
    do {
        // ���a�����Ʀr
        p_choose_number = player_enter_number(p_cells, p_cells_p);
        // �D�X���a�������Ʀr�������q����l
        p_choose_c_cells_index = find_computer_index(c_cells, p_choose_number);
        // ��q�������a�������Ʀr�]����
        clear_number(c_cells_p, p_choose_number);
        // ����p_choose_c_cells_index��0
        filter_level_array(l_array, p_choose_c_cells_index);
        // ���ܪ��a�������Ʀr�������u������
        level_array_add(l_array, p_choose_c_cells_index);

        system("cls");

        // �L�X���a�������Ʀr
        printf("�@�z�����F%d\n", p_choose_number + 1);
        // �L�X�ثe���a�P�q���U���X���s�u
        over = print_lines(p_cells, c_cells);
        // �L�X�ثe�q��������
        print_computer_cells(c_cells);
        // �L�X�ثe���a����l
        print_now(p_cells);

        if (over > 0)
           break;

        // �q���۰ʿ�ܼƦr
        c_choose_number = c_cells[choose_computer_number(c_cells, l_array)] - 25;
        //�۰ʱN���a���q���ҿ�ܤ��Ʀr�]����
        clear_number(p_cells_p, c_choose_number);

        // �L�X�q����������l
        printf("�q�������F%d\n", c_choose_number + 1);
        // �L�X�ثe���a�P�q���U���X���s�u
        over = print_lines(p_cells, c_cells);
        // �L�X�ثe�q��������
        print_computer_cells(c_cells);
        // �L�X�ثe���a����l
        print_now(p_cells);
    } while (over == 0 );

    print_over_information(over);

    return(0);
}

// �L�X�C�������P�W�h
void print_rules(void) {
     printf("-----* ���G�C�� *-----\n");
     printf("1. �Ы��ӤU�C��l���ǿ�J�z�n���Ʀr\n");
     printf("   �i�@����J�@�ơA�C�ӼƦr���Ϊťչj�}\n");
     printf("   ��J���@�ӼƦr�δX�ӼƦr���Enter�A�N�|�L�X�̷s���A\n");
     printf("   �]���O�C�������M��l����l�|�M�š^\n");
     printf("2. �Ʀr�d��1~25�A�Y�O���@�ӼƦr���b�d��\n");
     printf("   �{���|�бz�A���s��J�A�Y�᭱�w����J�Ʀr�h�|���e���@��C\n");
     printf("3. ��J������A�{���|���ܱz����J�n�������Ʀr\n");
     printf("   �п�J�z�n�������Ʀr���Enter\n");
     printf("   �{���|���K�N�q�����︹�������C\n"); 
     printf("4. �C���p�P�@�뻫�G�C���A���������s�u�̬�Ĺ�C\n"); 
     printf("5. �����즹�����A�Чּ֦a���C���a:)\n\n");
}

// �L�X��J���Ǫ���l
void print_initial_cells(void) {
     int i;
     printf("\n�z�ССССССССТ{\n");
     for (i = 1; i <= 25; i++) {
         if (i % 5 == 1)
            printf("�U"); 
         printf("%2d�U", i); 
         if (i % 5 == 0 && i != 25)
            printf("\n�u�СϡСϡСϡСϡТt\n");
     }
     printf("\n�|�ССССССССТ}\n");
}

// �N��l���Ȫ�l�Ƭ�-1
void initial_cells(int cells[]) {
     int i;
     for (i = 0; i < 25; i++)
         cells[i] = -1;
}

// �񺡪��a����l�]�H���Φۤv��J�^
void fill_player_cells(int cells[]) {
     int sum = 0, enter_num;
     do {
         printf("�п�J�n��J���Ʀr�]�ο�J0�ѹq���H����J�Ʀr�^ >> ");
         scanf("%d", &enter_num);
         if (enter_num == 0) {
            random_fill_cells(cells);
            print_now(cells);
            sum = 25;
         } else if (!error(cells, enter_num)) {
                   enter_num--;
                   cells[sum] = enter_num;
                   sum++;
                   print_now(cells);
         }
     } while (sum < 25);
}

// �H����J�Ʀr
void random_fill_cells(int cells[]) {
     int i, a, b, temp;
     for (i = 0; i < 25; i++) {
         cells[i] = i;
     }
     for (i = 0; i < 25; i++) {
         a = rand() % 25;
         b = rand() % 25;
         temp = cells[a];
         cells[a] = cells[b];
         cells[b] = temp;
     }
}

// ���տ�J�Ʀr�O�_�ŦX�d��έ���
int  error(int cells[], int enter_number) {
     int err = 0, i;
     for (i = 0; i < 25 && !err; i++)
         if (enter_number == cells[i]) {
            err = 1;
            printf("%d���п�J�A�п�J��L��\n", enter_number);
         }
     if (enter_number < 1 || enter_number > 25) {
        err = 1;
        printf("%d�W�X�d��A�п�J��L��\n", enter_number);
     }
     return(err);
}

// �L�X�ثe��l���Ʀr�γQ�������a��
void print_now(int cells[]) {
     int i;
     printf("\n�СССССССССС�\n");
     for (i = 0; i < 25; i++) {
         if (i % 5 == 0)
            printf("�U"); 
         if (cells[i] >= 25)
            printf("���U"); 
         else
             printf("%2d�U", cells[i] + 1); 
         if (i % 5 == 4 && i != 25 - 1)
            printf("\n�ССϡСϡСϡСϡС�\n");
     }
     printf("\n�СССССССССС�\n");
}

// �L�X�ثe�q��������
void print_computer_cells(int computer_cells[]) {
     int i;
     printf("\n�СССССССССС�\n");
     for (i = 0; i < 25; i++) {
         if (i % 5 == 0)
            printf("�U"); 
         if (computer_cells[i] >= 25)
            printf("���U"); 
         else
             printf("���U"); 
         if (i % 5 == 4 && i != 25 - 1)
            printf("\n�ССϡСϡСϡСϡС�\n");
     }
     printf("\n�СССССССССС�\n");
}

// �u�����Ű}�C��l��
void initial_level_array(int level_array[]) {
     int i;
     for (i = 0; i < 25; i++) {
	 if (i % 4 == 0 || i % 6 == 0)
	    level_array[i] = 3;
         else
             level_array[i] = 2;
     }
     level_array[12]++;
     
}

// ���V�������Ʀr�Ҧb��l
void assign_cells_p(int cells[], int *cells_p[]) {
     int i;
     for (i = 0; i < 25; i++)
         cells_p[cells[i]] = &cells[i];
}

// ���a��J�n�������Ʀr
int  player_enter_number(int player_cells[], int *player_cells_p[]) {
     int clear_n;
     printf("�п�J�n�������Ʀr >> ");
     scanf("%d", &clear_n);
     clear_n--;
     if (clear_n > 24 || clear_n < 0 || *player_cells_p[clear_n] >= 25) {
        printf("�W�X�d��άO�w�����A�Э��s��J�C\n");
     } else {
          clear_number(player_cells_p, clear_n);
          return(clear_n);
     }
}

// ���ܪ��a��J���Ʀr�������u������
void filter_level_array(int level_array[], int computer_index) {
     level_array[computer_index] = 0;
}

// ��X���a��J���Ʀr�������q����l
int  find_computer_index(int computer_cells[], int p_choose_number) {
     int i;
     for (i = 0; i < 25; i++) {
         if (computer_cells[i] == p_choose_number)
            break;
     }
     return(i);
}

// �N��ܪ��Ʀr�]����
void clear_number(int *cells_p[], int enter_num) {
     *cells_p[enter_num] += 25;
}

// �q���۰ʿ�ܭn��������l
int  choose_computer_number(int computer_cells[], int level_array[]) {
     int max_index;
     max_index = find_max(level_array);
     computer_cells[max_index] += 25;
     level_array[max_index] = 0;
     level_array_add(level_array, max_index);
     return(max_index);
}

// ��X�Ĥ@���u�����ų̰�����l
int  find_max(int level_array[]) {
     int max_value = level_array[0], i, first_max_index = -1;
     for (i = 0; i < 25; i++)
         if (level_array[i] > max_value)
            max_value = level_array[i];

     for (i = 0; i < 25; i++) {
         if (level_array[i] == max_value) {
            first_max_index = i;
            break;
         }
     }
     return(first_max_index);
}

// �N��ܫ᪺�Ƭ����s�u�u������+1
void level_array_add(int level_array[], int choose_cell) {
     int difference, i;
     difference = choose_cell % 5;

     // ��+1
     for (i = choose_cell - difference; i < choose_cell; i++)
	 if (level_array[i] != 0)
	    level_array[i]++;
     for (i = choose_cell + 1; i < choose_cell + 5 - difference; i++)
         if (level_array[i] != 0)
            level_array[i]++;

     // ��+1
     for (i = choose_cell % 5; i < choose_cell; i += 5)
         if (level_array[i] != 0)
	    level_array[i]++;
     for (i = choose_cell + 5; i < 25; i += 5)
         if (level_array[i] != 0)
	    level_array[i]++;

     // ��e+1
     if (choose_cell % 6 == 0)
        for (i = 0; i < 25; i += 6)
            if (level_array[i] != 0)
               level_array[i]++;
     else if (choose_cell % 4 == 0)
             for (i = 4; i <= 20; i += 4)
                 if (level_array[i] != 0)
                    level_array[i]++;

     if (choose_cell == 12) {
        level_array[4]++;
        level_array[8]++;
        level_array[16]++;
        level_array[20]++;
     }
}

// �p��ثe�������X���u
int  determine_line_vertical(int cells[]) {
     int connect, sum = 0, i, j;
     for (i = 0; i < 5; i++) {
         connect = 1;
         for (j = 0; j < 5; j++) {
             if (cells[i + j * 5] < 25)
                connect = 0;
         }
         if (connect == 1)
            sum++;
     }
     return(sum);
}

// �p��ثe����X���u
int  determine_line_horizontal(int cells[]) {
     int connect, sum = 0, i, j;
     for (i = 0; i < 5; i++) {
         connect = 1;
         for (j = 0; j < 5; j++)
             if (cells[i * 5 + j] < 25)
                connect = 0;
         if (connect == 1)
            sum++;
     }
     return(sum);
}

// �p��ثe��e�����X���u
int  determine_line_cross(int cells[]) {
     int connect, sum = 0, i;
     connect = 1;
     for ( i = 0; i < 25; i += 6) 
         if (cells[i] < 25)
            connect = 0;
     if (connect == 1)
        sum++;

     connect = 1;
     for ( i = 4; i <= 20; i += 4)
         if (cells[i] < 25)
            connect = 0;
     if (connect == 1)
        sum++;
     return(sum);
}

// �p��ثe�`�@���X���u
int  determine_line_total(int cells[]) {
     return (determine_line_vertical(cells) +
             determine_line_horizontal(cells) +
             determine_line_cross(cells));
}

// �L�X�ثe���a��q���U���X���u�A�öǦ^�C���O�_����
int  print_lines(int player_cells[], int computer_cells[]) {
     int player_lines, computer_lines;
     player_lines = determine_line_total(player_cells);
     computer_lines = determine_line_total(computer_cells);
     printf("�@�z�ثe�� %d ���s�u\n", player_lines);
     printf("�q���ثe�� %d ���s�u\n", computer_lines);

     if (computer_lines >= 5 || player_lines >= 5)
        printf("���̲׳ӭt >> �]�z�^%d : �]�q���^%d\n", player_lines, computer_lines);

     if (player_lines >= 5 && computer_lines < 5)
        return(1);	  // ���aĹ
     else if (computer_lines >= 5 && player_lines < 5)
             return(2);   // �q��Ĺ
     else if (player_lines == 5 && computer_lines == 5)
             return(3);   // ����
     else
         return(0);       // �C���|������
}

void print_over_information(int result) {
     if (result == 1)
        printf("\n���ߧA�IĹ�F�I�C�������A���±z������I\n");
     else if (result == 2)
             printf("\nOops!���n�N��q��Ĺ�F�A�Ф��n���L�I�C�������A���±z������I\n");
     else
         printf("\n����C�I�C�������A���±z������I\n");
     system("pause");
}
