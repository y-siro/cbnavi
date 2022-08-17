#include "map.h"
using namespace std;

HANDLE CIN = 0; // console input
HANDLE COUT = 0; // console output
enum Color { BLUE = 9, YELLOWGREEN, SKY, RED, PINK, YELLOW, WHITE, BLACK, INDIGO, ORANGE }; // console color set
int s, e; // point start, end

/* mouse set */
int be_input()
{
    INPUT_RECORD input_record;
    DWORD input_count;
    PeekConsoleInput(CIN, &input_record, 1, &input_count);
    return input_count;
}

int get_input(WORD* vkey, COORD* pos)
{
    INPUT_RECORD input_record;
    DWORD input_count;
    ReadConsoleInput(CIN, &input_record, 1, &input_count);
    switch (input_record.EventType) {
    case MOUSE_EVENT:
        if (pos && (input_record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)) {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(COUT, &csbi);
            *pos = input_record.Event.MouseEvent.dwMousePosition;
            pos->X -= csbi.srWindow.Left;
            pos->Y -= csbi.srWindow.Top;
            return MOUSE_EVENT;
        }
        break;
    }
    return 0;
}
/* mouse set end */

void SetTextColor(int background, int text) // func color set
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (background << 4) | text);
}

void gotoxy(int x, int y) // func coordinate set
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setConsoleView() { // set console col, row size
    system("mode con:cols=350 lines=100");
    system("title cbnu Navi");
}

int main(void) {
	fast;

    setConsoleView(); // set console col, row size 
    //SetTextColor(WHITE, BLUE); // set console background, let color
    DWORD mode; WORD key; COORD pos; 
    
    int event; // mouse event
    int x; // mouse x set
    int y; // mouse y set
    

    /* set mouse click */
    CIN = GetStdHandle(STD_INPUT_HANDLE);
    COUT = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(CIN, &mode);
    SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);  

    pathfind m;
    string menu_ = "<�޴��� �������ּ���>  ";
    string menu_id = "1. ��ã�� 2. �, ��å ��õ ���, 3. ���� ���� �̿� ���� Ȯ�� -1. ���α׷� ����";
    string s_end = "���� �۾��� �����Ϸ��� �ƹ� Ű�� �����ּ���";
    string l_end = "����Ʈ ���� �����մϴ�";
    string d_end = "��ũ ���� �����մϴ�";
    string a_start= "������� �Է����ּ���>> ";
    string a_end= "�������� �Է����ּ���>> ";       
    string str,sstt;

    int nn=4; // mode set 1:��ã��, 2:��õ ���, 3:���� ����, 4:����Ʈ ���, 5:��ũ ���
    bool back_color = true; // true�� �� ����Ʈ ���, false�� �� ��ũ ���

    while (true) {   
        if (back_color) {
            SetTextColor(WHITE, BLACK);
        }
        else {
            SetTextColor(BLACK, WHITE);
        }
        system("cls");
        
        m.setLoadmap();
        m.setcomponent();
        m.showMap();
        
        /* component info */
        if (back_color) {
            SetTextColor(WHITE, BLUE);
        }
        else {
            SetTextColor(BLACK, BLUE);
        }
        gotoxy(79, 4); cout << "N12 : ������";
        gotoxy(79, 5); cout << "E2 : ���Ź�ȭ��";
        gotoxy(79, 6); cout << "E3 : ��1�л�ȸ��(����)";
        gotoxy(79, 7); cout << "E3-1 : NH��";
        gotoxy(79, 8); cout << "E4-2 : ����";
        gotoxy(79, 9); cout << "E7-4 : ��ϴ��б� ����";
        gotoxy(79, 10); cout << "SN : �ָ�";
        gotoxy(79, 11); cout << "N17 : ������, S17 : �缺��, E8-11 : ������";
        gotoxy(79, 12); cout << "S14 : ��2�л�ȸ��(���Ƹ���)";
        gotoxy(79, 13); cout << "S9 : �ڹ���";
        gotoxy(79, 14); cout << "S8 : �߿ܰ�����";
        if (back_color) {
            SetTextColor(WHITE, BLACK);
        }
        else {
            SetTextColor(BLACK, WHITE);
        }

        /* Light, Dark mode */
        gotoxy(140, 4); cout << "��������������������������������������������������" << " ";
        gotoxy(140, 5); cout << "��       Light Mode      ��" << " ";
        gotoxy(140, 6); cout << "��������������������������������������������������"<<" ";

        gotoxy(175, 4); cout << "��������������������������������������������������" << " ";
        gotoxy(175, 5); cout << "��        Dark Mode      ��" << " ";
        gotoxy(175, 6); cout << "��������������������������������������������������" << " ";

        /* component info */        
        gotoxy(140, 9); cout << "  " << menu_;
        gotoxy(140, 11); cout << "��������������������������������������������������" << "          " << "��������������������������������������������������" << "          " << "��������������������������������������������������" << "          " << "�������������������������������������������������� ";
        gotoxy(140, 12); cout << "��                       ��" << "          " << "��                       ��" << "          " << "��                       ��"<< "          " <<"��                       �� ";
        gotoxy(140, 13); cout << "��         ��ã��        ��" << "          " << "��        ��õ���       ��" << "          " << "��        ���߱���       ��" << "          " << "��     ���α׷� ����     �� ";
        gotoxy(140, 14); cout << "��                       ��" << "          " << "��                       ��" << "          " << "��                       ��" << "          " << "��                       �� ";
        gotoxy(140, 15); cout << "��������������������������������������������������" << "          " << "��������������������������������������������������" << "          " << "��������������������������������������������������" << "          " << "�������������������������������������������������� ";
        gotoxy(140, 17);
        GetConsoleMode(CIN, &mode);
        SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);
        while (true)
        {
            if (be_input())
            {
                if (get_input(&key, &pos) != 0)
                {
                    MOUSE_EVENT;
                    x = pos.X; y = pos.Y;
                    
                    rib(141, 164, 11, 15) {
                        nn = 1;
                        if (back_color) {
                            SetTextColor(WHITE, RED);
                        }
                        else {
                            SetTextColor(BLACK, RED);
                        }
                        gotoxy(140, 11); cout << "�������������������������������������������������� ";
                        gotoxy(140, 12); cout << "��                       �� ";
                        gotoxy(140, 13); cout << "��         ��ã��        �� ";
                        gotoxy(140, 14); cout << "��                       �� ";
                        gotoxy(140, 15); cout << "�������������������������������������������������� ";
                        break;
                    }
                    rib(176, 199, 11, 15) {
                        nn = 2;
                        if (back_color) {
                            SetTextColor(WHITE, RED);
                        }
                        else {
                            SetTextColor(BLACK, RED);
                        }
                        gotoxy(175, 11); cout << "�������������������������������������������������� ";
                        gotoxy(175, 12); cout << "��                       �� ";
                        gotoxy(175, 13); cout << "��        ��õ���       �� ";
                        gotoxy(175, 14); cout << "��                       �� ";
                        gotoxy(175, 15); cout << "�������������������������������������������������� ";
                        break;
                    }
                    rib(211, 234, 11, 15) {
                        nn = 3;
                        if (back_color) {
                            SetTextColor(WHITE, RED);
                        }
                        else {
                            SetTextColor(BLACK, RED);
                        }
                        gotoxy(210, 11); cout << "�������������������������������������������������� ";
                        gotoxy(210, 12); cout << "��                       �� ";
                        gotoxy(210, 13); cout << "��        ���߱���       �� ";
                        gotoxy(210, 14); cout << "��                       �� ";
                        gotoxy(210, 15); cout << "�������������������������������������������������� ";
                        break;
                    }
                    rib(246, 269, 11, 15) {
                        nn = -1;
                        if (back_color) {
                            SetTextColor(WHITE, RED);
                        }
                        else {
                            SetTextColor(BLACK, RED);
                        }
                        gotoxy(245, 11); cout << "�������������������������������������������������� ";
                        gotoxy(245, 12); cout << "��                       �� ";
                        gotoxy(245, 13); cout << "��     ���α׷� ����     �� ";
                        gotoxy(245, 14); cout << "��                       �� ";
                        gotoxy(245, 15); cout << "�������������������������������������������������� ";
                        break;
                    }
                    if ((x >= 141 && x <= 164 && y >= 4 && y <= 6) and nn != 4) {
                        nn = 4;
                        SetTextColor(WHITE, BLACK);
                        break;
                        
                    }
                    if ((x >= 176 && x <= 199 && y >= 4 && y <= 6) and nn !=5 ) {
                        nn = 5;
                        SetTextColor(BLACK, WHITE);
                        break;
                        
                    }
                }
            }
        }

        if (back_color) {
            SetTextColor(WHITE, BLACK);
        }
        else {
            SetTextColor(BLACK, WHITE);
        }
        
        /* exit btn */

        if (nn == -1) {
            gotoxy(140, 17); cout << "���α׷��� �����մϴ�.";
            break;
        }
        
        /* ��ã�� console */

        else if (nn == 1) {
            gotoxy(140, 17);  cout << "������� �����ּ���>> ";
            gotoxy(162, 17); cout << "�˻� ���� ������� ã���÷��� �����ּ���";
            GetConsoleMode(CIN, &mode);
            SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);
            while (true)
            {
                if (be_input())
                {
                    if (get_input(&key, &pos) != 0)
                    {
                        MOUSE_EVENT;
                        x = pos.X; y = pos.Y;
                        rib(162, 204, 17, 17) {
                            gotoxy(162, 18); cout << "�˻��� (Ű����) >> ";
                            gotoxy(182, 18); cin >> str;
                            s = m.matching(str);
                            break;
                        }
                        rib(5,16,5,18) {
                            gotoxy(162, 17); cout << "�����������п�, ������, ������������                                                                    " << endl;
                            s=1; break;
                        }                        
                        rib(8, 16, 22, 30) {
                            gotoxy(162, 17); cout << "S21 (������б������)                                                                    " << endl;
                            s = 2; break;
                        }
                        rib(19, 26, 21, 25) {
                            gotoxy(162, 17); cout << "N10 (���� ����,������������)                                                                    " << endl;
                            s = 3; break;
                        }
                        rib(3, 9, 33, 36) {
                            gotoxy(162, 17); cout << "S19 (�¸���, ���� ������)                                                                    " << endl;
                            s = 4; break;
                        }
                        rib(12, 16, 33, 36) {
                            gotoxy(162, 17); cout << "S20 (÷�ܹ��̿� ��������)                                                                    " << endl;
                            s = 5; break;
                        }
                        rib(15, 21, 40, 47) {
                            gotoxy(162, 17); cout << "S17 (�缺��)                                                                    " << endl;
                            s = 6; break;
                        }
                        rib(29, 34, 33, 36) {
                            gotoxy(162, 17); cout << "S14 (���Ƹ���)                                                                    " << endl;
                            s = 7; break;
                        }
                        rib(30, 37, 40, 45) {
                            gotoxy(162, 17); cout << "S8 (������, ����)                                                                    " << endl;
                            s = 8; break;
                        }
                        rib(41, 44, 35, 38) {
                            gotoxy(162, 17); cout << "S9 (�ڹ���)                                                                    " << endl;
                            s = 9; break;
                        }
                        rib(40, 43, 44, 46) {
                            gotoxy(162, 17); cout << "S3 (���ΰ����� â��)                                                                    " << endl;
                            s = 10; break;
                        }
                        rib(39, 44, 48, 51) {
                            gotoxy(162, 17); cout << "S4-1 (�������� 3��)                                                                    " << endl;
                            s = 11; break;
                        }
                        rib(39, 44, 56, 59) {
                            gotoxy(162, 17); cout << "S4-2 (�����ð��ϰ�)                                                                    " << endl;
                            s = 12; break;
                        }
                        rib(46, 49, 44, 46) {
                            gotoxy(162, 17); cout << "S2 (����������)                                                                    " << endl;
                            s = 13; break;
                        }
                        rib(32, 42, 23, 26) {
                            gotoxy(162, 17); cout << "N11 (��������ǽ���)                                                                    " << endl;
                            s = 14; break;
                        }
                        rib(45, 49, 21, 26) {
                            gotoxy(162, 17); cout << "�ָ�                                                                    " << endl;
                            s = 15; break;
                        }
                        rib(44, 50, 17, 19) {
                            gotoxy(162, 17); cout << "N13 (�濵�а�)                                                                    " << endl;
                            s = 16; break;
                        }
                        rib(35, 41, 11, 17) {
                            gotoxy(162, 17); cout << "N14 (�ι���ȸ��)                                                                    " << endl;
                            s = 17; break;
                        }
                        rib(44, 49, 11, 15) {
                            gotoxy(162, 17); cout << "N16-2 (�̼���)                                                                    " << endl;
                            s = 18; break;
                        }
                        rib(36, 41, 2, 5) {
                            gotoxy(162, 17); cout << "N17 (������)                                                                    " << endl;
                            s = 19; break;
                        }
                        rib(46, 52, 2, 5) {
                            gotoxy(162, 17); cout << "N18 (���а�)                                                                    " << endl;
                            s = 20; break;
                        }
                        rib(51, 57, 48, 51) {
                            gotoxy(162, 17); cout << "S1-5 (�ڿ����д��� 5ȣ��)                                                                    " << endl;
                            s = 21; break;
                        }
                        rib(53, 59, 44, 46) {
                            gotoxy(162, 17); cout << "S1-4 (�ڿ����д��� 4ȣ��)                                                                    " << endl;
                            s = 22; break;
                        }
                        rib(48, 57, 28, 30) {
                            gotoxy(162, 17); cout << "S1-1 (�ڿ����д��� 1ȣ��)                                                                    " << endl;
                            s = 23; break;
                        }
                        rib(54, 59, 32, 34) {
                            gotoxy(162, 17); cout << "S1-2 (�ڿ����д��� 2ȣ��)                                                                    " << endl;
                            s = 24; break;
                        }
                        rib(58, 59, 35, 40) {
                            gotoxy(162, 17); cout << "S1-7 (���б��������)                                                                    " << endl;
                            s = 25; break;
                        }
                        rib(54, 59, 41, 43) {
                            gotoxy(162, 17); cout << "S1-3 (�ڿ����д��� 3ȣ��)                                                                    " << endl;
                            s = 26; break;
                        }
                        rib(52, 59, 21, 26) {
                            gotoxy(162, 17); cout << "N12 (�߾� ������)                                                                    " << endl;
                            s = 27; break;
                        }
                        rib(55, 61, 17, 19) {
                            gotoxy(162, 17); cout << "N15 (��ȸ���д��� ����)                                                                    " << endl;
                            s = 28; break;
                        }
                        rib(66, 71, 13, 19) {
                            gotoxy(162, 17); cout << "E2 (���Ź�ȭ��, ��ϴ� ����)                                                                    " << endl;
                            s = 29; break;
                        }
                        rib(55, 61, 8, 11) {
                            gotoxy(162, 17); cout << "N16-1 (�ι����� ����)                                                                    " << endl;
                            s = 30; break;
                        }
                        rib(69, 74, 8, 11) {
                            gotoxy(162, 17); cout << "E1 (�������)                                                                    " << endl;
                            s = 31; break;
                        }
                        rib(65, 66, 1, 5) {
                            gotoxy(162, 17); cout << "N21 (���ϼ��Ĵ�)                                                                    " << endl;
                            s = 32; break;
                        }
                        rib(69, 74, 1, 6) {
                            gotoxy(162, 17); cout << "N20 (��Ȱ���а�)                                                                    " << endl;
                            s = 33; break;
                        }
                        rib(56, 61, 2, 6) {
                            gotoxy(162, 17); cout << "N19 (��2����)                                                                    " << endl;
                            s = 34; break;
                        }
                        rib(63, 66, 21, 26) {
                            gotoxy(162, 17); cout << "E3 (��1�л�ȸ��, ����)                                                                    " << endl;
                            s = 35; break;
                        }
                        rib(69, 72, 21, 26) {
                            gotoxy(162, 17); cout << "E3-1 (NH��, �ｺ��)                                                                    " << endl;
                            s = 36; break;
                        }
                        rib(62, 69, 28, 30) {
                            gotoxy(162, 17); cout << "E8-1 (�������� 1ȣ��)                                                                    " << endl;
                            s = 37; break;
                        }
                        rib(62, 73, 36, 38) {
                            gotoxy(162, 17); cout << "E8-2 (���� �յ����ǵ�)                                                                    " << endl;
                            s = 38; break;
                        }
                        rib(63, 72, 45, 47) {
                            gotoxy(162, 17); cout << "E8-7 (�������� 1��)                                                                    " << endl;
                            s = 39; break;
                        }
                        rib(64, 68, 51, 53) {
                            gotoxy(162, 17); cout << "E9 (�п���������������)                                                                    " << endl;
                            s = 40; break;
                        }
                        rib(71, 73, 30, 35) {
                            gotoxy(162, 17); cout << "E8-3 (�������� 2ȣ��)                                                                    " << endl;
                            s = 41; break;
                        }
                        rib(76, 80, 33, 37) {
                            gotoxy(162, 17); cout << "E8-4 (��1���嵿)                                                                    " << endl;
                            s = 42; break;
                        }
                        rib(76, 80, 40, 44) {
                            gotoxy(162, 17); cout << "E8-5 (��2���嵿)                                                                    " << endl;
                            s = 43; break;
                        }
                        rib(83, 84, 40, 46) {
                            gotoxy(162, 17); cout << "E8-8 (�������� 4ȣ��)                                                                    " << endl;
                            s = 44; break;
                        }
                        rib(76, 80, 46, 48) {
                            gotoxy(162, 17); cout << "E8-6 (�������� 3ȣ��)                                                                    " << endl;
                            s = 45; break;
                        }
                        rib(78, 80, 48, 51) {
                            gotoxy(162, 17); cout << "E8-6 (�������� 3ȣ��)                                                                    " << endl;
                            s = 45; break;
                        }
                        rib(70, 73, 49, 53) {
                            gotoxy(162, 17); cout << "E10 (�������� 2��)                                                                    " << endl;
                            s = 46; break;
                        }
                        rib(76, 81, 53, 55) {
                            gotoxy(162, 17); cout << "E8-10 (�������� 5ȣ��)                                                                    " << endl;
                            s = 47; break;
                        }
                        rib(78, 88, 17, 26) {
                            gotoxy(162, 17); cout << "E4-1 (�ҿ��)                                                                    " << endl;
                            s = 48; break;
                        }
                        rib(88, 94, 50, 53) {
                            gotoxy(162, 17); cout << "E8-11 (������)                                                                    " << endl;
                            s = 49; break;
                        }
                        rib(92, 94, 46, 50) {
                            gotoxy(162, 17); cout << "E8-11 (������)                                                                    " << endl;
                            s = 49; break;
                        }
                        rib(89, 93, 28, 30) {
                            gotoxy(162, 17); cout << "E7-3 (�ǰ����� 2ȣ��)                                                                    " << endl;
                            s = 50; break;
                        }
                        rib(92, 117, 17, 26) {
                            gotoxy(162, 17); cout << "E4-2 (����)                                                                    " << endl;
                            s = 51; break;
                        }
                        rib(98, 103, 28, 30) {
                            gotoxy(162, 17); cout << "E7-1 (�ǰ����� 1ȣ��)                                                                    " << endl;
                            s = 52; break;
                        }
                        rib(98, 103, 32, 37) {
                            gotoxy(162, 17); cout << "E7-2                                                                    " << endl;
                            s = 53; break;
                        }
                        rib(107, 128, 28, 40) {
                            gotoxy(162, 17); cout << "E7-4 (��ϴ��б� ����)                                                                    " << endl;
                            s = 54; break;
                        }
                    }
                }
            }
            gotoxy(140, 19); cout << "�������� �����ּ���>> ";
            gotoxy(162, 19); cout << "(�˻� ���� �������� ã���÷��� �����ּ���)";
            while (true)
            {
                if (be_input())
                {
                    if (get_input(&key, &pos) != 0)
                    {
                        MOUSE_EVENT;
                        x = pos.X; y = pos.Y;
                        rib(162, 204, 19, 19) {
                            gotoxy(162, 20); cout << "�˻��� (Ű����) >> ";
                            gotoxy(182, 20); cin >> str;
                            e = m.matching(str);
                            break;
                        }
                        rib(5, 16, 5, 18) {
                            gotoxy(162, 19); cout << "�����������п�, ������, ������������                                                                    " << endl;
                            e = 1; break;
                        }
                        rib(8, 16, 22, 30) {
                            gotoxy(162, 19); cout << "S21 (������б������)                                                                    " << endl;
                            e = 2; break;
                        }
                        rib(19, 26, 21, 25) {
                            gotoxy(162, 19); cout << "N10 (���� ����,������������)                                                                    " << endl;
                            e = 3; break;
                        }
                        rib(3, 9, 33, 36) {
                            gotoxy(162, 19); cout << "S19 (�¸���, ���� ������)                                                                    " << endl;
                            e = 4; break;
                        }
                        rib(12, 16, 33, 36) {
                            gotoxy(162, 19); cout << "S20 (÷�ܹ��̿� ��������)                                                                    " << endl;
                            e = 5; break;
                        }
                        rib(15, 21, 40, 47) {
                            gotoxy(162, 19); cout << "S17 (�缺��)                                                                    " << endl;
                            e = 6; break;
                        }
                        rib(29, 34, 33, 36) {
                            gotoxy(162, 19); cout << "S14 (���Ƹ���)                                                                    " << endl;
                            e = 7; break;
                        }
                        rib(30, 37, 40, 45) {
                            gotoxy(162, 19); cout << "S8 (������, ����)                                                                    " << endl;
                            e = 8; break;
                        }
                        rib(41, 44, 35, 38) {
                            gotoxy(162, 19); cout << "S9 (�ڹ���)                                                                    " << endl;
                            e = 9; break;
                        }
                        rib(40, 43, 44, 46) {
                            gotoxy(162, 19); cout << "S3 (���ΰ����� â��)                                                                    " << endl;
                            e = 10; break;
                        }
                        rib(39, 44, 48, 51) {
                            gotoxy(162, 19); cout << "S4-1 (�������� 3��)                                                                    " << endl;
                            e = 11; break;
                        }
                        rib(39, 44, 56, 59) {
                            gotoxy(162, 19); cout << "S4-2 (�����ð��ϰ�)                                                                    " << endl;
                            e = 12; break;
                        }
                        rib(46, 49, 44, 46) {
                            gotoxy(162, 19); cout << "S2 (����������)                                                                    " << endl;
                            e = 13; break;
                        }
                        rib(32, 42, 23, 26) {
                            gotoxy(162, 19); cout << "N11 (��������ǽ���)                                                                    " << endl;
                            e = 14; break;
                        }
                        rib(45, 49, 21, 26) {
                            gotoxy(162, 19); cout << "�ָ�                                                                    " << endl;
                            e = 15; break;
                        }
                        rib(44, 50, 17, 19) {
                            gotoxy(162, 19); cout << "N13 (�濵�а�)                                                                    " << endl;
                            e = 16; break;
                        }
                        rib(35, 41, 11, 17) {
                            gotoxy(162, 19); cout << "N14 (�ι���ȸ��)                                                                    " << endl;
                            e = 17; break;
                        }
                        rib(44, 49, 11, 15) {
                            gotoxy(162, 19); cout << "N16-2 (�̼���)                                                                    " << endl;
                            e = 18; break;
                        }
                        rib(36, 41, 2, 5) {
                            gotoxy(162, 19); cout << "N17 (������)                                                                    " << endl;
                            e = 19; break;
                        }
                        rib(46, 52, 2, 5) {
                            gotoxy(162, 19); cout << "N18 (���а�)                                                                    " << endl;
                            e = 20; break;
                        }
                        rib(51, 57, 48, 51) {
                            gotoxy(162, 19); cout << "S1-5 (�ڿ����д��� 5ȣ��)                                                                    " << endl;
                            e = 21; break;
                        }
                        rib(53, 59, 44, 46) {
                            gotoxy(162, 19); cout << "S1-4 (�ڿ����д��� 4ȣ��)                                                                    " << endl;
                            e = 22; break;
                        }
                        rib(48, 57, 28, 30) {
                            gotoxy(162, 19); cout << "S1-1 (�ڿ����д��� 1ȣ��)                                                                    " << endl;
                            e = 23; break;
                        }
                        rib(54, 59, 32, 34) {
                            gotoxy(162, 19); cout << "S1-2 (�ڿ����д��� 2ȣ��)                                                                    " << endl;
                            e = 24; break;
                        }
                        rib(58, 59, 35, 40) {
                            gotoxy(162, 19); cout << "S1-7 (���б��������)                                                                    " << endl;
                            e = 25; break;
                        }
                        rib(54, 59, 41, 43) {
                            gotoxy(162, 19); cout << "S1-3 (�ڿ����д��� 3ȣ��)                                                                    " << endl;
                            e = 26; break;
                        }
                        rib(52, 59, 21, 26) {
                            gotoxy(162, 19); cout << "N12 (�߾� ������)                                                                    " << endl;
                            e = 27; break;
                        }
                        rib(55, 61, 17, 19) {
                            gotoxy(162, 19); cout << "N15 (��ȸ���д��� ����)                                                                    " << endl;
                            e = 28; break;
                        }
                        rib(66, 71, 13, 19) {
                            gotoxy(162, 19); cout << "E2 (���Ź�ȭ��, ��ϴ� ����)                                                                    " << endl;
                            e = 29; break;
                        }
                        rib(55, 61, 8, 11) {
                            gotoxy(162, 19); cout << "N16-1 (�ι����� ����)                                                                    " << endl;
                            e = 30; break;
                        }
                        rib(69, 74, 8, 11) {
                            gotoxy(162, 19); cout << "E1 (�������)                                                                    " << endl;
                            e = 31; break;
                        }
                        rib(65, 66, 1, 5) {
                            gotoxy(162, 19); cout << "N21 (���ϼ��Ĵ�)                                                                    " << endl;
                            e = 32; break;
                        }
                        rib(69, 74, 1, 6) {
                            gotoxy(162, 19); cout << "N20 (��Ȱ���а�)                                                                    " << endl;
                            e = 33; break;
                        }
                        rib(56, 61, 2, 6) {
                            gotoxy(162, 19); cout << "N19 (��2����)                                                                    " << endl;
                            e = 34; break;
                        }
                        rib(63, 66, 21, 26) {
                            gotoxy(162, 19); cout << "E3 (��1�л�ȸ��, ����)                                                                    " << endl;
                            e = 35; break;
                        }
                        rib(69, 72, 21, 26) {
                            gotoxy(162, 19); cout << "E3-1 (NH��, �ｺ��)                                                                    " << endl;
                            e = 36; break;
                        }
                        rib(62, 69, 28, 30) {
                            gotoxy(162, 19); cout << "E8-1 (�������� 1ȣ��)                                                                    " << endl;
                            e = 37; break;
                        }
                        rib(62, 73, 36, 38) {
                            gotoxy(162, 19); cout << "E8-2 (���� �յ����ǵ�)                                                                    " << endl;
                            e = 38; break;
                        }
                        rib(63, 72, 45, 47) {
                            gotoxy(162, 19); cout << "E8-7 (�������� 1��)                                                                    " << endl;
                            e = 39; break;
                        }
                        rib(64, 68, 51, 53) {
                            gotoxy(162, 19); cout << "E9 (�п���������������)                                                                    " << endl;
                            e = 40; break;
                        }
                        rib(71, 73, 30, 35) {
                            gotoxy(162, 19); cout << "E8-3 (�������� 2ȣ��)                                                                    " << endl;
                            e = 41; break;
                        }
                        rib(76, 80, 33, 37) {
                            gotoxy(162, 19); cout << "E8-4 (��1���嵿)                                                                    " << endl;
                            e = 42; break;
                        }
                        rib(76, 80, 40, 44) {
                            gotoxy(162, 19); cout << "E8-5 (��2���嵿)                                                                    " << endl;
                            e = 43; break;
                        }
                        rib(83, 84, 40, 46) {
                            gotoxy(162, 19); cout << "E8-8 (�������� 4ȣ��)                                                                    " << endl;
                            e = 44; break;
                        }
                        rib(76, 80, 46, 48) {
                            gotoxy(162, 19); cout << "E8-6 (�������� 3ȣ��)                                                                    " << endl;
                            e = 45; break;
                        }
                        rib(78, 80, 48, 51) {
                            gotoxy(162, 19); cout << "E8-6 (�������� 3ȣ��)                                                                    " << endl;
                            e = 45; break;
                        }
                        rib(70, 73, 49, 53) {
                            gotoxy(162, 19); cout << "E10 (�������� 2��)                                                                    " << endl;
                            e = 46; break;
                        }
                        rib(76, 81, 53, 55) {
                            gotoxy(162, 19); cout << "E8-10 (�������� 5ȣ��)                                                                    " << endl;
                            e = 47; break;
                        }
                        rib(78, 88, 17, 26) {
                            gotoxy(162, 19); cout << "E4-1 (�ҿ��)                                                                    " << endl;
                            e = 48; break;
                        }
                        rib(88, 94, 50, 53) {
                            gotoxy(162, 19); cout << "E8-11 (������)                                                                    " << endl;
                            e = 49; break;
                        }
                        rib(92, 94, 46, 50) {
                            gotoxy(162, 19); cout << "E8-11 (������)                                                                    " << endl;
                            e = 49; break;
                        }
                        rib(89, 93, 28, 30) {
                            gotoxy(162, 19); cout << "E7-3 (�ǰ����� 2ȣ��)                                                                    " << endl;
                            e = 50; break;
                        }
                        rib(92, 117, 17, 26) {
                            gotoxy(162, 19); cout << "E4-2 (����)                                                                    " << endl;
                            e = 51; break;
                        }
                        rib(98, 103, 28, 30) {
                            gotoxy(162, 19); cout << "E7-1 (�ǰ����� 1ȣ��)                                                                    " << endl;
                            e = 52; break;
                        }
                        rib(98, 103, 32, 37) {
                            gotoxy(162, 19); cout << "E7-2                                                                    " << endl;
                            e = 53; break;
                        }
                        rib(107, 128, 28, 40) {
                            gotoxy(162, 19); cout << "E7-4 (��ϴ��б� ����)                                                                    " << endl;
                            e = 54; break;
                        }
                    }
                }
            }
            gotoxy(140, 21);// cout << "<��� �ȳ�>  ";
            m.search(s,e);
            for (int i = 0; i < 70; ++i) {
                for (int j = 0; j < 130; ++j) {
                    if (m.map[i][j] == 2) {
                        gotoxy(j, i); 
                        if (back_color) {
                            SetTextColor(WHITE, RED);
                        }
                        else {
                            SetTextColor(BLACK, RED);
                        }
                        cout << "#";
                    }
                }
            }


            if (back_color) {
                SetTextColor(WHITE, BLUE);
            }
            else {
                SetTextColor(BLACK, BLUE);
            }
            gotoxy(140, 23); cout << s_end;
            gotoxy(140, 25); sstt = _getch();
        }

        /* case : ��õ ��� */ 

        
        else if(nn==2){
            gotoxy(140, 17); cout << "��õ ��� :: ���ϴ� ��θ� �����ּ���";
            gotoxy(143, 19); cout << "  < �� Ŀ�� ����Ʈ �ڽ� >";
            gotoxy(143, 21); cout << "  < ���� ���� �ڽ� >";
            gotoxy(143, 23); cout << "  < ��ο� ��å�� >";
            GetConsoleMode(CIN, &mode);
            SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);
            while (true)
            {
                if (be_input())
                {
                    if (get_input(&key, &pos) != 0)
                    {
                        MOUSE_EVENT;
                        x = pos.X; y = pos.Y;
                        rib(143, 167, 19, 19) {
                            if (back_color) {
                                SetTextColor(WHITE, PINK);
                            }
                            else {
                                SetTextColor(BLACK, PINK);
                            }
                            gotoxy(143, 19); cout << "  < �� Ŀ�� ����Ʈ �ڽ� >" << "   " << "���� �ǰ�, ���� ���� ��";
                            gotoxy(140, 27); cout << "��ſ� ����Ʈ�Ͻñ� �ٶ��ϴ�! ";
                            for (int i = 42; i <= 64; ++i) {
                                gotoxy(i, 20); cout << "#";
                            }
                            for (int i = 6; i <= 19; ++i) {
                                gotoxy(42, i); cout << "#";
                            }
                            for (int i = 6; i <= 19; ++i) {
                                gotoxy(64, i); cout << "#";
                            }
                            gotoxy(43,6); cout << "#";
                            gotoxy(44,6); cout << "#";
                            gotoxy(53,6); cout << "#";
                            gotoxy(54,6); cout << "#";
                            gotoxy(62,6); cout << "#";
                            gotoxy(63,6); cout << "#";
                            break;
                        }
                        rib(143, 165, 21, 21) {
                            if (back_color) {
                                SetTextColor(WHITE, SKY);
                            }
                            else {
                                SetTextColor(BLACK, SKY);
                            }
                            gotoxy(143, 21); cout << "  < ���� ���� �ڽ� >" << "   " << "�ȴ� ���� 50�� ���� �ҿ�";
                            gotoxy(140, 27); cout << "������ ��ǽñ� �ٶ��ϴ�! ";
                            for (int i = 17; i <= 42; ++i) {
                                gotoxy(i, 20); cout << "#";
                            }
                            for (int i = 21; i <= 39; ++i) {
                                gotoxy(17, i); cout << "#";
                            }
                            for (int i = 18; i <= 38; ++i) {
                                gotoxy(i,39); cout << "#";
                            }
                            for (int i = 40; i <= 47; ++i) {
                                gotoxy(38,i); cout << "#";
                            }
                            for (int i = 39; i <= 60; ++i) {
                                gotoxy(i, 47); cout << "#";
                            }
                            for (int i = 48; i <= 58; ++i) {
                                gotoxy(60,i); cout << "#";
                            }
                            for (int i = 61; i <= 74; ++i) {
                                gotoxy(i,58); cout << "#";
                            }
                            for (int i = 27; i <= 57; ++i) {
                                gotoxy(74,i); cout << "#";
                            }
                            for (int i = 20; i <= 27; ++i) {
                                gotoxy(73, i); cout << "#";
                            }
                            for (int i = 64; i <= 72; ++i) {
                                gotoxy(i,20); cout << "#";
                            }
                            for (int i = 6; i <= 19; ++i) {
                                gotoxy(42, i); cout << "#";
                            }
                            for (int i = 6; i <= 19; ++i) {
                                gotoxy(64, i); cout << "#";
                            }
                            gotoxy(43, 6); cout << "#";
                            gotoxy(44, 6); cout << "#";
                            gotoxy(53, 6); cout << "#";
                            gotoxy(54, 6); cout << "#";
                            gotoxy(62, 6); cout << "#";
                            gotoxy(63, 6); cout << "#";
                            break;
                        }
                        rib(143, 177, 23, 23) {
                            if (back_color) {
                                SetTextColor(WHITE, BLUE);
                            }
                            else {
                                SetTextColor(BLACK, BLUE);
                            }
                            gotoxy(143, 23); cout << "  < ��ο� ��å�� >" << "   " << "�ȴ� ���� 30�� ���� �ҿ�" ;
                            gotoxy(140, 27); cout << "������ �Ȱ� ���� ��";
                            for (int i = 27; i <= 58; ++i) {
                                gotoxy(74,i); cout << "#";
                            }
                            for (int i = 60; i <= 73; ++i) {
                                gotoxy(i,58); cout << "#";
                            }
                            for (int i = 56; i <= 57; ++i) {
                                gotoxy(60,i); cout << "#";
                            }
                            for (int i = 45; i <= 59; ++i) {
                                gotoxy(i, 56); cout << "#";
                            }
                            for (int i = 47; i <= 55; ++i) {
                                gotoxy(45, i); cout << "#";
                            }
                            for (int i = 38; i <= 44; ++i) {
                                gotoxy(i,47); cout << "#";
                            }
                            for (int i = 39; i <= 46; ++i) {
                                gotoxy(38, i); cout << "#";
                            }
                            for (int i = 27; i <= 38; ++i) {
                                gotoxy(39, i); cout << "#";
                            }
                            for (int i = 40; i <= 43; ++i) {
                                gotoxy(i,27); cout << "#";
                            }
                            for (int i = 23; i <= 26; ++i) {
                                gotoxy(43, i); cout << "#";
                            }
                            break;
                        }
                    }
                }
            }
            if (back_color) {
                SetTextColor(WHITE, BLUE);
            }
            else {
                SetTextColor(BLACK, BLUE);
            }

            gotoxy(140, 31); cout << s_end;
            gotoxy(140, 33); sstt = _getch();
        }
        
        else if (nn == 3) { 
            if (back_color) {
                SetTextColor(WHITE, BLUE);
            }
            else {
                SetTextColor(BLACK, BLUE);
            }
            gotoxy(41, 27); cout << "#";
            if (back_color) {
                SetTextColor(WHITE, RED);
            }
            else {
                SetTextColor(BLACK, RED);
            }
            gotoxy(69, 27); cout << "#";
            if (back_color) {
                SetTextColor(WHITE, BLUE);
            }
            else {
                SetTextColor(BLACK, BLUE);
            }
            gotoxy(140, 17);  cout << "#";        
            if (back_color) {
                SetTextColor(WHITE, BLACK);
            }
            else {
                SetTextColor(BLACK, WHITE);
            }
            gotoxy(144, 17);  cout << "1682 ��ϴ��б� ���� ��� ������";
            gotoxy(144, 19);  cout << "710�� ���� ";

            if (back_color) {
                SetTextColor(WHITE, RED);
            }
            else {
                SetTextColor(BLACK, RED);
            }
            gotoxy(140, 23);  cout << "#";
            if (back_color) {
                SetTextColor(WHITE, BLACK);
            }
            else {
                SetTextColor(BLACK, WHITE);
            }
            gotoxy(144, 23);  cout << "1678 ��ϴ��б� �Ա� ��� ������";
            gotoxy(144, 25);  cout << "710�� ���� ";
            gotoxy(144, 26);  cout << "�б� ���й���";
            gotoxy(140, 31); cout << s_end;
            gotoxy(140, 33); sstt = _getch();
        }

        else if (nn == 4) {
            back_color = true;
            gotoxy(140, 31); cout << l_end;
            gotoxy(140, 33); sstt = _getch();
            
        }
        else if (nn == 5) {
            back_color = false;
            gotoxy(140, 31); cout << d_end;
            gotoxy(140, 33); sstt = _getch();

        }
        else {
            cout << "error code" << endl;
            break;
        }
    }    
	return 0;    
}