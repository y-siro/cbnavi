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
    string menu_ = "<詭景蒂 摹鷗п輿撮蹂>  ";
    string menu_id = "1. 望瓊晦 2. 遴翕, 骯疇 蹺繭 唳煎, 3. 渠醞 掖鱔 檜辨 雖薄 �挫� -1. Щ煎斜極 謙猿";
    string s_end = "棻擠 濛機擊 褒чж溥賊 嬴鼠 酈釭 揚楝輿撮蹂";
    string l_end = "塭檜お 賅萄煎 滲唳м棲棻";
    string d_end = "棻觼 賅萄煎 滲唳м棲棻";
    string a_start= "轎嫦雖蒂 殮溘п輿撮蹂>> ";
    string a_end= "紫雜雖蒂 殮溘п輿撮蹂>> ";       
    string str,sstt;

    int nn=4; // mode set 1:望瓊晦, 2:蹺繭 唳煎, 3:掖鱔 薑爾, 4:塭檜お 賅萄, 5:棻觼 賅萄
    bool back_color = true; // true橾 衛 塭檜お 賅萄, false橾 衛 棻觼 賅萄

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
        gotoxy(79, 4); cout << "N12 : 紫憮婦";
        gotoxy(79, 5); cout << "E2 : 偃褐僥�降�";
        gotoxy(79, 6); cout << "E3 : 薯1з儅�萼�(褐з)";
        gotoxy(79, 7); cout << "E3-1 : NH婦";
        gotoxy(79, 8); cout << "E4-2 : 渠遴翕濰";
        gotoxy(79, 9); cout << "E7-4 : 醱磁渠з掖 煽錳";
        gotoxy(79, 10); cout << "SN : 樂跤";
        gotoxy(79, 11); cout << "N17 : 偃撩營, S17 : 曄撩營, E8-11 : 曄霞營";
        gotoxy(79, 12); cout << "S14 : 薯2з儅�萼�(翕嬴葬寞)";
        gotoxy(79, 13); cout << "S9 : 夢僭婦";
        gotoxy(79, 14); cout << "S8 : 撿諼奢翱濰";
        if (back_color) {
            SetTextColor(WHITE, BLACK);
        }
        else {
            SetTextColor(BLACK, WHITE);
        }

        /* Light, Dark mode */
        gotoxy(140, 4); cout << "忙式式式式式式式式式式式式式式式式式式式式式式式忖" << " ";
        gotoxy(140, 5); cout << "弛       Light Mode      弛" << " ";
        gotoxy(140, 6); cout << "戌式式式式式式式式式式式式式式式式式式式式式式式戎"<<" ";

        gotoxy(175, 4); cout << "忙式式式式式式式式式式式式式式式式式式式式式式式忖" << " ";
        gotoxy(175, 5); cout << "弛        Dark Mode      弛" << " ";
        gotoxy(175, 6); cout << "戌式式式式式式式式式式式式式式式式式式式式式式式戎" << " ";

        /* component info */        
        gotoxy(140, 9); cout << "  " << menu_;
        gotoxy(140, 11); cout << "忙式式式式式式式式式式式式式式式式式式式式式式式忖" << "          " << "忙式式式式式式式式式式式式式式式式式式式式式式式忖" << "          " << "忙式式式式式式式式式式式式式式式式式式式式式式式忖" << "          " << "忙式式式式式式式式式式式式式式式式式式式式式式式忖 ";
        gotoxy(140, 12); cout << "弛                       弛" << "          " << "弛                       弛" << "          " << "弛                       弛"<< "          " <<"弛                       弛 ";
        gotoxy(140, 13); cout << "弛         望瓊晦        弛" << "          " << "弛        蹺繭唳煎       弛" << "          " << "弛        渠醞掖鱔       弛" << "          " << "弛     Щ煎斜極 謙猿     弛 ";
        gotoxy(140, 14); cout << "弛                       弛" << "          " << "弛                       弛" << "          " << "弛                       弛" << "          " << "弛                       弛 ";
        gotoxy(140, 15); cout << "戌式式式式式式式式式式式式式式式式式式式式式式式戎" << "          " << "戌式式式式式式式式式式式式式式式式式式式式式式式戎" << "          " << "戌式式式式式式式式式式式式式式式式式式式式式式式戎" << "          " << "戌式式式式式式式式式式式式式式式式式式式式式式式戎 ";
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
                        gotoxy(140, 11); cout << "忙式式式式式式式式式式式式式式式式式式式式式式式忖 ";
                        gotoxy(140, 12); cout << "弛                       弛 ";
                        gotoxy(140, 13); cout << "弛         望瓊晦        弛 ";
                        gotoxy(140, 14); cout << "弛                       弛 ";
                        gotoxy(140, 15); cout << "戌式式式式式式式式式式式式式式式式式式式式式式式戎 ";
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
                        gotoxy(175, 11); cout << "忙式式式式式式式式式式式式式式式式式式式式式式式忖 ";
                        gotoxy(175, 12); cout << "弛                       弛 ";
                        gotoxy(175, 13); cout << "弛        蹺繭唳煎       弛 ";
                        gotoxy(175, 14); cout << "弛                       弛 ";
                        gotoxy(175, 15); cout << "戌式式式式式式式式式式式式式式式式式式式式式式式戎 ";
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
                        gotoxy(210, 11); cout << "忙式式式式式式式式式式式式式式式式式式式式式式式忖 ";
                        gotoxy(210, 12); cout << "弛                       弛 ";
                        gotoxy(210, 13); cout << "弛        渠醞掖鱔       弛 ";
                        gotoxy(210, 14); cout << "弛                       弛 ";
                        gotoxy(210, 15); cout << "戌式式式式式式式式式式式式式式式式式式式式式式式戎 ";
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
                        gotoxy(245, 11); cout << "忙式式式式式式式式式式式式式式式式式式式式式式式忖 ";
                        gotoxy(245, 12); cout << "弛                       弛 ";
                        gotoxy(245, 13); cout << "弛     Щ煎斜極 謙猿     弛 ";
                        gotoxy(245, 14); cout << "弛                       弛 ";
                        gotoxy(245, 15); cout << "戌式式式式式式式式式式式式式式式式式式式式式式式戎 ";
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
            gotoxy(140, 17); cout << "Щ煎斜極擊 謙猿м棲棻.";
            break;
        }
        
        /* 望瓊晦 console */

        else if (nn == 1) {
            gotoxy(140, 17);  cout << "轎嫦雖蒂 揚楝輿撮蹂>> ";
            gotoxy(162, 17); cout << "匐儀 賅萄煎 轎嫦雖蒂 瓊戲衛溥賊 揚楝輿撮蹂";
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
                            gotoxy(162, 18); cout << "匐儀橫 (酈錶萄) >> ";
                            gotoxy(182, 18); cin >> str;
                            s = m.matching(str);
                            break;
                        }
                        rib(5,16,5,18) {
                            gotoxy(162, 17); cout << "徹з瞪僥渠з錳, ⑽撲婦, 措薯掖盟獄睡                                                                    " << endl;
                            s=1; break;
                        }                        
                        rib(8, 16, 22, 30) {
                            gotoxy(162, 17); cout << "S21 (堯機婁з晦獎撫攪)                                                                    " << endl;
                            s = 2; break;
                        }
                        rib(19, 26, 21, 25) {
                            gotoxy(162, 17); cout << "N10 (渠з 獄睡,措薯掖盟獄睡)                                                                    " << endl;
                            s = 3; break;
                        }
                        rib(3, 9, 33, 36) {
                            gotoxy(162, 17); cout << "S19 (蝓葬婦, 謙曄 翱掘模)                                                                    " << endl;
                            s = 4; break;
                        }
                        rib(12, 16, 33, 36) {
                            gotoxy(162, 17); cout << "S20 (繩欽夥檜螃 翱掘撫攪)                                                                    " << endl;
                            s = 5; break;
                        }
                        rib(15, 21, 40, 47) {
                            gotoxy(162, 17); cout << "S17 (曄撩營)                                                                    " << endl;
                            s = 6; break;
                        }
                        rib(29, 34, 33, 36) {
                            gotoxy(162, 17); cout << "S14 (翕嬴葬寞)                                                                    " << endl;
                            s = 7; break;
                        }
                        rib(30, 37, 40, 45) {
                            gotoxy(162, 17); cout << "S8 (奢翱濰, 奢攪)                                                                    " << endl;
                            s = 8; break;
                        }
                        rib(41, 44, 35, 38) {
                            gotoxy(162, 17); cout << "S9 (夢僭婦)                                                                    " << endl;
                            s = 9; break;
                        }
                        rib(40, 43, 44, 46) {
                            gotoxy(162, 17); cout << "S3 (獄睡婦葬翕 璽堅)                                                                    " << endl;
                            s = 10; break;
                        }
                        rib(39, 44, 48, 51) {
                            gotoxy(162, 17); cout << "S4-1 (瞪濠薑爾 3婦)                                                                    " << endl;
                            s = 11; break;
                        }
                        rib(39, 44, 56, 59) {
                            gotoxy(162, 17); cout << "S4-2 (釭檜た啪橾婦)                                                                    " << endl;
                            s = 12; break;
                        }
                        rib(46, 49, 44, 46) {
                            gotoxy(162, 17); cout << "S2 (瞪骯薑爾錳)                                                                    " << endl;
                            s = 13; break;
                        }
                        rib(32, 42, 23, 26) {
                            gotoxy(162, 17); cout << "N11 (奢翕褒я褒蝗婦)                                                                    " << endl;
                            s = 14; break;
                        }
                        rib(45, 49, 21, 26) {
                            gotoxy(162, 17); cout << "樂跤                                                                    " << endl;
                            s = 15; break;
                        }
                        rib(44, 50, 17, 19) {
                            gotoxy(162, 17); cout << "N13 (唳艙з婦)                                                                    " << endl;
                            s = 16; break;
                        }
                        rib(35, 41, 11, 17) {
                            gotoxy(162, 17); cout << "N14 (檣僥餌�萼�)                                                                    " << endl;
                            s = 17; break;
                        }
                        rib(44, 49, 11, 15) {
                            gotoxy(162, 17); cout << "N16-2 (嘐獎婦)                                                                    " << endl;
                            s = 18; break;
                        }
                        rib(36, 41, 2, 5) {
                            gotoxy(162, 17); cout << "N17 (偃撩營)                                                                    " << endl;
                            s = 19; break;
                        }
                        rib(46, 52, 2, 5) {
                            gotoxy(162, 17); cout << "N18 (徹з婦)                                                                    " << endl;
                            s = 20; break;
                        }
                        rib(51, 57, 48, 51) {
                            gotoxy(162, 17); cout << "S1-5 (濠翱婁з渠з 5�ㄟ�)                                                                    " << endl;
                            s = 21; break;
                        }
                        rib(53, 59, 44, 46) {
                            gotoxy(162, 17); cout << "S1-4 (濠翱婁з渠з 4�ㄟ�)                                                                    " << endl;
                            s = 22; break;
                        }
                        rib(48, 57, 28, 30) {
                            gotoxy(162, 17); cout << "S1-1 (濠翱婁з渠з 1�ㄟ�)                                                                    " << endl;
                            s = 23; break;
                        }
                        rib(54, 59, 32, 34) {
                            gotoxy(162, 17); cout << "S1-2 (濠翱婁з渠з 2�ㄟ�)                                                                    " << endl;
                            s = 24; break;
                        }
                        rib(58, 59, 35, 40) {
                            gotoxy(162, 17); cout << "S1-7 (婁з晦獎紫憮婦)                                                                    " << endl;
                            s = 25; break;
                        }
                        rib(54, 59, 41, 43) {
                            gotoxy(162, 17); cout << "S1-3 (濠翱婁з渠з 3�ㄟ�)                                                                    " << endl;
                            s = 26; break;
                        }
                        rib(52, 59, 21, 26) {
                            gotoxy(162, 17); cout << "N12 (醞懈 紫憮婦)                                                                    " << endl;
                            s = 27; break;
                        }
                        rib(55, 61, 17, 19) {
                            gotoxy(162, 17); cout << "N15 (餌�萼�з渠з 獄婦)                                                                    " << endl;
                            s = 28; break;
                        }
                        rib(66, 71, 13, 19) {
                            gotoxy(162, 17); cout << "E2 (偃褐僥�降�, 醱磁渠 憮薄)                                                                    " << endl;
                            s = 29; break;
                        }
                        rib(55, 61, 8, 11) {
                            gotoxy(162, 17); cout << "N16-1 (檣僥渠з 獄婦)                                                                    " << endl;
                            s = 30; break;
                        }
                        rib(69, 74, 8, 11) {
                            gotoxy(162, 17); cout << "E1 (餌彰渠з)                                                                    " << endl;
                            s = 31; break;
                        }
                        rib(65, 66, 1, 5) {
                            gotoxy(162, 17); cout << "N21 (擎ж熱衝渡)                                                                    " << endl;
                            s = 32; break;
                        }
                        rib(69, 74, 1, 6) {
                            gotoxy(162, 17); cout << "N20 (儅�偽�з婦)                                                                    " << endl;
                            s = 33; break;
                        }
                        rib(56, 61, 2, 6) {
                            gotoxy(162, 17); cout << "N19 (薯2獄婦)                                                                    " << endl;
                            s = 34; break;
                        }
                        rib(63, 66, 21, 26) {
                            gotoxy(162, 17); cout << "E3 (薯1з儅�萼�, 褐з)                                                                    " << endl;
                            s = 35; break;
                        }
                        rib(69, 72, 21, 26) {
                            gotoxy(162, 17); cout << "E3-1 (NH婦, ⑦蝶濰)                                                                    " << endl;
                            s = 36; break;
                        }
                        rib(62, 69, 28, 30) {
                            gotoxy(162, 17); cout << "E8-1 (奢婁渠з 1�ㄟ�)                                                                    " << endl;
                            s = 37; break;
                        }
                        rib(62, 73, 36, 38) {
                            gotoxy(162, 17); cout << "E8-2 (奢渠 м翕鬼曖翕)                                                                    " << endl;
                            s = 38; break;
                        }
                        rib(63, 72, 45, 47) {
                            gotoxy(162, 17); cout << "E8-7 (瞪濠薑爾 1婦)                                                                    " << endl;
                            s = 39; break;
                        }
                        rib(64, 68, 51, 53) {
                            gotoxy(162, 17); cout << "E9 (з翱骯奢翕晦獎翱掘錳)                                                                    " << endl;
                            s = 40; break;
                        }
                        rib(71, 73, 30, 35) {
                            gotoxy(162, 17); cout << "E8-3 (奢婁渠з 2�ㄟ�)                                                                    " << endl;
                            s = 41; break;
                        }
                        rib(76, 80, 33, 37) {
                            gotoxy(162, 17); cout << "E8-4 (薯1奢濰翕)                                                                    " << endl;
                            s = 42; break;
                        }
                        rib(76, 80, 40, 44) {
                            gotoxy(162, 17); cout << "E8-5 (薯2奢濰翕)                                                                    " << endl;
                            s = 43; break;
                        }
                        rib(83, 84, 40, 46) {
                            gotoxy(162, 17); cout << "E8-8 (奢婁渠з 4�ㄟ�)                                                                    " << endl;
                            s = 44; break;
                        }
                        rib(76, 80, 46, 48) {
                            gotoxy(162, 17); cout << "E8-6 (奢婁渠з 3�ㄟ�)                                                                    " << endl;
                            s = 45; break;
                        }
                        rib(78, 80, 48, 51) {
                            gotoxy(162, 17); cout << "E8-6 (奢婁渠з 3�ㄟ�)                                                                    " << endl;
                            s = 45; break;
                        }
                        rib(70, 73, 49, 53) {
                            gotoxy(162, 17); cout << "E10 (瞪濠薑爾 2婦)                                                                    " << endl;
                            s = 46; break;
                        }
                        rib(76, 81, 53, 55) {
                            gotoxy(162, 17); cout << "E8-10 (奢婁渠з 5�ㄟ�)                                                                    " << endl;
                            s = 47; break;
                        }
                        rib(78, 88, 17, 26) {
                            gotoxy(162, 17); cout << "E4-1 (模遴翕濰)                                                                    " << endl;
                            s = 48; break;
                        }
                        rib(88, 94, 50, 53) {
                            gotoxy(162, 17); cout << "E8-11 (曄霞營)                                                                    " << endl;
                            s = 49; break;
                        }
                        rib(92, 94, 46, 50) {
                            gotoxy(162, 17); cout << "E8-11 (曄霞營)                                                                    " << endl;
                            s = 49; break;
                        }
                        rib(89, 93, 28, 30) {
                            gotoxy(162, 17); cout << "E7-3 (曖婁渠з 2�ㄟ�)                                                                    " << endl;
                            s = 50; break;
                        }
                        rib(92, 117, 17, 26) {
                            gotoxy(162, 17); cout << "E4-2 (渠遴翕濰)                                                                    " << endl;
                            s = 51; break;
                        }
                        rib(98, 103, 28, 30) {
                            gotoxy(162, 17); cout << "E7-1 (曖婁渠з 1�ㄟ�)                                                                    " << endl;
                            s = 52; break;
                        }
                        rib(98, 103, 32, 37) {
                            gotoxy(162, 17); cout << "E7-2                                                                    " << endl;
                            s = 53; break;
                        }
                        rib(107, 128, 28, 40) {
                            gotoxy(162, 17); cout << "E7-4 (醱磁渠з掖 煽錳)                                                                    " << endl;
                            s = 54; break;
                        }
                    }
                }
            }
            gotoxy(140, 19); cout << "紫雜雖蒂 揚楝輿撮蹂>> ";
            gotoxy(162, 19); cout << "(匐儀 賅萄煎 紫雜雖蒂 瓊戲衛溥賊 揚楝輿撮蹂)";
            while (true)
            {
                if (be_input())
                {
                    if (get_input(&key, &pos) != 0)
                    {
                        MOUSE_EVENT;
                        x = pos.X; y = pos.Y;
                        rib(162, 204, 19, 19) {
                            gotoxy(162, 20); cout << "匐儀橫 (酈錶萄) >> ";
                            gotoxy(182, 20); cin >> str;
                            e = m.matching(str);
                            break;
                        }
                        rib(5, 16, 5, 18) {
                            gotoxy(162, 19); cout << "徹з瞪僥渠з錳, ⑽撲婦, 措薯掖盟獄睡                                                                    " << endl;
                            e = 1; break;
                        }
                        rib(8, 16, 22, 30) {
                            gotoxy(162, 19); cout << "S21 (堯機婁з晦獎撫攪)                                                                    " << endl;
                            e = 2; break;
                        }
                        rib(19, 26, 21, 25) {
                            gotoxy(162, 19); cout << "N10 (渠з 獄睡,措薯掖盟獄睡)                                                                    " << endl;
                            e = 3; break;
                        }
                        rib(3, 9, 33, 36) {
                            gotoxy(162, 19); cout << "S19 (蝓葬婦, 謙曄 翱掘模)                                                                    " << endl;
                            e = 4; break;
                        }
                        rib(12, 16, 33, 36) {
                            gotoxy(162, 19); cout << "S20 (繩欽夥檜螃 翱掘撫攪)                                                                    " << endl;
                            e = 5; break;
                        }
                        rib(15, 21, 40, 47) {
                            gotoxy(162, 19); cout << "S17 (曄撩營)                                                                    " << endl;
                            e = 6; break;
                        }
                        rib(29, 34, 33, 36) {
                            gotoxy(162, 19); cout << "S14 (翕嬴葬寞)                                                                    " << endl;
                            e = 7; break;
                        }
                        rib(30, 37, 40, 45) {
                            gotoxy(162, 19); cout << "S8 (奢翱濰, 奢攪)                                                                    " << endl;
                            e = 8; break;
                        }
                        rib(41, 44, 35, 38) {
                            gotoxy(162, 19); cout << "S9 (夢僭婦)                                                                    " << endl;
                            e = 9; break;
                        }
                        rib(40, 43, 44, 46) {
                            gotoxy(162, 19); cout << "S3 (獄睡婦葬翕 璽堅)                                                                    " << endl;
                            e = 10; break;
                        }
                        rib(39, 44, 48, 51) {
                            gotoxy(162, 19); cout << "S4-1 (瞪濠薑爾 3婦)                                                                    " << endl;
                            e = 11; break;
                        }
                        rib(39, 44, 56, 59) {
                            gotoxy(162, 19); cout << "S4-2 (釭檜た啪橾婦)                                                                    " << endl;
                            e = 12; break;
                        }
                        rib(46, 49, 44, 46) {
                            gotoxy(162, 19); cout << "S2 (瞪骯薑爾錳)                                                                    " << endl;
                            e = 13; break;
                        }
                        rib(32, 42, 23, 26) {
                            gotoxy(162, 19); cout << "N11 (奢翕褒я褒蝗婦)                                                                    " << endl;
                            e = 14; break;
                        }
                        rib(45, 49, 21, 26) {
                            gotoxy(162, 19); cout << "樂跤                                                                    " << endl;
                            e = 15; break;
                        }
                        rib(44, 50, 17, 19) {
                            gotoxy(162, 19); cout << "N13 (唳艙з婦)                                                                    " << endl;
                            e = 16; break;
                        }
                        rib(35, 41, 11, 17) {
                            gotoxy(162, 19); cout << "N14 (檣僥餌�萼�)                                                                    " << endl;
                            e = 17; break;
                        }
                        rib(44, 49, 11, 15) {
                            gotoxy(162, 19); cout << "N16-2 (嘐獎婦)                                                                    " << endl;
                            e = 18; break;
                        }
                        rib(36, 41, 2, 5) {
                            gotoxy(162, 19); cout << "N17 (偃撩營)                                                                    " << endl;
                            e = 19; break;
                        }
                        rib(46, 52, 2, 5) {
                            gotoxy(162, 19); cout << "N18 (徹з婦)                                                                    " << endl;
                            e = 20; break;
                        }
                        rib(51, 57, 48, 51) {
                            gotoxy(162, 19); cout << "S1-5 (濠翱婁з渠з 5�ㄟ�)                                                                    " << endl;
                            e = 21; break;
                        }
                        rib(53, 59, 44, 46) {
                            gotoxy(162, 19); cout << "S1-4 (濠翱婁з渠з 4�ㄟ�)                                                                    " << endl;
                            e = 22; break;
                        }
                        rib(48, 57, 28, 30) {
                            gotoxy(162, 19); cout << "S1-1 (濠翱婁з渠з 1�ㄟ�)                                                                    " << endl;
                            e = 23; break;
                        }
                        rib(54, 59, 32, 34) {
                            gotoxy(162, 19); cout << "S1-2 (濠翱婁з渠з 2�ㄟ�)                                                                    " << endl;
                            e = 24; break;
                        }
                        rib(58, 59, 35, 40) {
                            gotoxy(162, 19); cout << "S1-7 (婁з晦獎紫憮婦)                                                                    " << endl;
                            e = 25; break;
                        }
                        rib(54, 59, 41, 43) {
                            gotoxy(162, 19); cout << "S1-3 (濠翱婁з渠з 3�ㄟ�)                                                                    " << endl;
                            e = 26; break;
                        }
                        rib(52, 59, 21, 26) {
                            gotoxy(162, 19); cout << "N12 (醞懈 紫憮婦)                                                                    " << endl;
                            e = 27; break;
                        }
                        rib(55, 61, 17, 19) {
                            gotoxy(162, 19); cout << "N15 (餌�萼�з渠з 獄婦)                                                                    " << endl;
                            e = 28; break;
                        }
                        rib(66, 71, 13, 19) {
                            gotoxy(162, 19); cout << "E2 (偃褐僥�降�, 醱磁渠 憮薄)                                                                    " << endl;
                            e = 29; break;
                        }
                        rib(55, 61, 8, 11) {
                            gotoxy(162, 19); cout << "N16-1 (檣僥渠з 獄婦)                                                                    " << endl;
                            e = 30; break;
                        }
                        rib(69, 74, 8, 11) {
                            gotoxy(162, 19); cout << "E1 (餌彰渠з)                                                                    " << endl;
                            e = 31; break;
                        }
                        rib(65, 66, 1, 5) {
                            gotoxy(162, 19); cout << "N21 (擎ж熱衝渡)                                                                    " << endl;
                            e = 32; break;
                        }
                        rib(69, 74, 1, 6) {
                            gotoxy(162, 19); cout << "N20 (儅�偽�з婦)                                                                    " << endl;
                            e = 33; break;
                        }
                        rib(56, 61, 2, 6) {
                            gotoxy(162, 19); cout << "N19 (薯2獄婦)                                                                    " << endl;
                            e = 34; break;
                        }
                        rib(63, 66, 21, 26) {
                            gotoxy(162, 19); cout << "E3 (薯1з儅�萼�, 褐з)                                                                    " << endl;
                            e = 35; break;
                        }
                        rib(69, 72, 21, 26) {
                            gotoxy(162, 19); cout << "E3-1 (NH婦, ⑦蝶濰)                                                                    " << endl;
                            e = 36; break;
                        }
                        rib(62, 69, 28, 30) {
                            gotoxy(162, 19); cout << "E8-1 (奢婁渠з 1�ㄟ�)                                                                    " << endl;
                            e = 37; break;
                        }
                        rib(62, 73, 36, 38) {
                            gotoxy(162, 19); cout << "E8-2 (奢渠 м翕鬼曖翕)                                                                    " << endl;
                            e = 38; break;
                        }
                        rib(63, 72, 45, 47) {
                            gotoxy(162, 19); cout << "E8-7 (瞪濠薑爾 1婦)                                                                    " << endl;
                            e = 39; break;
                        }
                        rib(64, 68, 51, 53) {
                            gotoxy(162, 19); cout << "E9 (з翱骯奢翕晦獎翱掘錳)                                                                    " << endl;
                            e = 40; break;
                        }
                        rib(71, 73, 30, 35) {
                            gotoxy(162, 19); cout << "E8-3 (奢婁渠з 2�ㄟ�)                                                                    " << endl;
                            e = 41; break;
                        }
                        rib(76, 80, 33, 37) {
                            gotoxy(162, 19); cout << "E8-4 (薯1奢濰翕)                                                                    " << endl;
                            e = 42; break;
                        }
                        rib(76, 80, 40, 44) {
                            gotoxy(162, 19); cout << "E8-5 (薯2奢濰翕)                                                                    " << endl;
                            e = 43; break;
                        }
                        rib(83, 84, 40, 46) {
                            gotoxy(162, 19); cout << "E8-8 (奢婁渠з 4�ㄟ�)                                                                    " << endl;
                            e = 44; break;
                        }
                        rib(76, 80, 46, 48) {
                            gotoxy(162, 19); cout << "E8-6 (奢婁渠з 3�ㄟ�)                                                                    " << endl;
                            e = 45; break;
                        }
                        rib(78, 80, 48, 51) {
                            gotoxy(162, 19); cout << "E8-6 (奢婁渠з 3�ㄟ�)                                                                    " << endl;
                            e = 45; break;
                        }
                        rib(70, 73, 49, 53) {
                            gotoxy(162, 19); cout << "E10 (瞪濠薑爾 2婦)                                                                    " << endl;
                            e = 46; break;
                        }
                        rib(76, 81, 53, 55) {
                            gotoxy(162, 19); cout << "E8-10 (奢婁渠з 5�ㄟ�)                                                                    " << endl;
                            e = 47; break;
                        }
                        rib(78, 88, 17, 26) {
                            gotoxy(162, 19); cout << "E4-1 (模遴翕濰)                                                                    " << endl;
                            e = 48; break;
                        }
                        rib(88, 94, 50, 53) {
                            gotoxy(162, 19); cout << "E8-11 (曄霞營)                                                                    " << endl;
                            e = 49; break;
                        }
                        rib(92, 94, 46, 50) {
                            gotoxy(162, 19); cout << "E8-11 (曄霞營)                                                                    " << endl;
                            e = 49; break;
                        }
                        rib(89, 93, 28, 30) {
                            gotoxy(162, 19); cout << "E7-3 (曖婁渠з 2�ㄟ�)                                                                    " << endl;
                            e = 50; break;
                        }
                        rib(92, 117, 17, 26) {
                            gotoxy(162, 19); cout << "E4-2 (渠遴翕濰)                                                                    " << endl;
                            e = 51; break;
                        }
                        rib(98, 103, 28, 30) {
                            gotoxy(162, 19); cout << "E7-1 (曖婁渠з 1�ㄟ�)                                                                    " << endl;
                            e = 52; break;
                        }
                        rib(98, 103, 32, 37) {
                            gotoxy(162, 19); cout << "E7-2                                                                    " << endl;
                            e = 53; break;
                        }
                        rib(107, 128, 28, 40) {
                            gotoxy(162, 19); cout << "E7-4 (醱磁渠з掖 煽錳)                                                                    " << endl;
                            e = 54; break;
                        }
                    }
                }
            }
            gotoxy(140, 21);// cout << "<唳煎 寰頂>  ";
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

        /* case : 蹺繭 唳煎 */ 

        
        else if(nn==2){
            gotoxy(140, 17); cout << "蹺繭 唳煎 :: 錳ж朝 唳煎蒂 揚楝輿撮蹂";
            gotoxy(143, 19); cout << "  < 瑤 醴Ы 等檜お 囀蝶 >";
            gotoxy(143, 21); cout << "  < 緇撫 褻梵 囀蝶 >";
            gotoxy(143, 23); cout << "  < 橫舒遴 骯疇煎 >";
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
                            gotoxy(143, 19); cout << "  < 瑤 醴Ы 等檜お 囀蝶 >" << "   " << "粒檜 Я堅, 粒檜 雖朝 望";
                            gotoxy(140, 27); cout << "闌剪遴 等檜おж衛望 夥奧棲棻! ";
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
                            gotoxy(143, 21); cout << "  < 緇撫 褻梵 囀蝶 >" << "   " << "務朝 晦遽 50碟 瞪�� 模蹂";
                            gotoxy(140, 27); cout << "寰瞪и 遴翕腎衛望 夥奧棲棻! ";
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
                            gotoxy(143, 23); cout << "  < 橫舒遴 骯疇煎 >" << "   " << "務朝 晦遽 30碟 瞪�� 模蹂" ;
                            gotoxy(140, 27); cout << "褻辨�� 務堅 談擎 望";
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
            gotoxy(144, 17);  cout << "1682 醱磁渠з掖 煽錳 寞賊 薑盟濰";
            gotoxy(144, 19);  cout << "710廓 幗蝶 ";

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
            gotoxy(144, 23);  cout << "1678 醱磁渠з掖 殮掘 寞賊 薑盟濰";
            gotoxy(144, 25);  cout << "710廓 幗蝶 ";
            gotoxy(144, 26);  cout << "з掖 鱔з幗蝶";
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