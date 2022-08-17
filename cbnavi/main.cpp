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
    string menu_ = "<메뉴를 선택해주세요>  ";
    string menu_id = "1. 길찾기 2. 운동, 산책 추천 경로, 3. 대중 교통 이용 지점 확인 -1. 프로그램 종료";
    string s_end = "다음 작업을 실행하려면 아무 키나 눌러주세요";
    string l_end = "라이트 모드로 변경합니다";
    string d_end = "다크 모드로 변경합니다";
    string a_start= "출발지를 입력해주세요>> ";
    string a_end= "도착지를 입력해주세요>> ";       
    string str,sstt;

    int nn=4; // mode set 1:길찾기, 2:추천 경로, 3:교통 정보, 4:라이트 모드, 5:다크 모드
    bool back_color = true; // true일 시 라이트 모드, false일 시 다크 모드

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
        gotoxy(79, 4); cout << "N12 : 도서관";
        gotoxy(79, 5); cout << "E2 : 개신문화관";
        gotoxy(79, 6); cout << "E3 : 제1학생회관(신학)";
        gotoxy(79, 7); cout << "E3-1 : NH관";
        gotoxy(79, 8); cout << "E4-2 : 대운동장";
        gotoxy(79, 9); cout << "E7-4 : 충북대학교 병원";
        gotoxy(79, 10); cout << "SN : 솔못";
        gotoxy(79, 11); cout << "N17 : 개성재, S17 : 양성재, E8-11 : 양진재";
        gotoxy(79, 12); cout << "S14 : 제2학생회관(동아리방)";
        gotoxy(79, 13); cout << "S9 : 박물관";
        gotoxy(79, 14); cout << "S8 : 야외공연장";
        if (back_color) {
            SetTextColor(WHITE, BLACK);
        }
        else {
            SetTextColor(BLACK, WHITE);
        }

        /* Light, Dark mode */
        gotoxy(140, 4); cout << "┌───────────────────────┐" << " ";
        gotoxy(140, 5); cout << "│       Light Mode      │" << " ";
        gotoxy(140, 6); cout << "└───────────────────────┘"<<" ";

        gotoxy(175, 4); cout << "┌───────────────────────┐" << " ";
        gotoxy(175, 5); cout << "│        Dark Mode      │" << " ";
        gotoxy(175, 6); cout << "└───────────────────────┘" << " ";

        /* component info */        
        gotoxy(140, 9); cout << "  " << menu_;
        gotoxy(140, 11); cout << "┌───────────────────────┐" << "          " << "┌───────────────────────┐" << "          " << "┌───────────────────────┐" << "          " << "┌───────────────────────┐ ";
        gotoxy(140, 12); cout << "│                       │" << "          " << "│                       │" << "          " << "│                       │"<< "          " <<"│                       │ ";
        gotoxy(140, 13); cout << "│         길찾기        │" << "          " << "│        추천경로       │" << "          " << "│        대중교통       │" << "          " << "│     프로그램 종료     │ ";
        gotoxy(140, 14); cout << "│                       │" << "          " << "│                       │" << "          " << "│                       │" << "          " << "│                       │ ";
        gotoxy(140, 15); cout << "└───────────────────────┘" << "          " << "└───────────────────────┘" << "          " << "└───────────────────────┘" << "          " << "└───────────────────────┘ ";
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
                        gotoxy(140, 11); cout << "┌───────────────────────┐ ";
                        gotoxy(140, 12); cout << "│                       │ ";
                        gotoxy(140, 13); cout << "│         길찾기        │ ";
                        gotoxy(140, 14); cout << "│                       │ ";
                        gotoxy(140, 15); cout << "└───────────────────────┘ ";
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
                        gotoxy(175, 11); cout << "┌───────────────────────┐ ";
                        gotoxy(175, 12); cout << "│                       │ ";
                        gotoxy(175, 13); cout << "│        추천경로       │ ";
                        gotoxy(175, 14); cout << "│                       │ ";
                        gotoxy(175, 15); cout << "└───────────────────────┘ ";
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
                        gotoxy(210, 11); cout << "┌───────────────────────┐ ";
                        gotoxy(210, 12); cout << "│                       │ ";
                        gotoxy(210, 13); cout << "│        대중교통       │ ";
                        gotoxy(210, 14); cout << "│                       │ ";
                        gotoxy(210, 15); cout << "└───────────────────────┘ ";
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
                        gotoxy(245, 11); cout << "┌───────────────────────┐ ";
                        gotoxy(245, 12); cout << "│                       │ ";
                        gotoxy(245, 13); cout << "│     프로그램 종료     │ ";
                        gotoxy(245, 14); cout << "│                       │ ";
                        gotoxy(245, 15); cout << "└───────────────────────┘ ";
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
            gotoxy(140, 17); cout << "프로그램을 종료합니다.";
            break;
        }
        
        /* 길찾기 console */

        else if (nn == 1) {
            gotoxy(140, 17);  cout << "출발지를 눌러주세요>> ";
            gotoxy(162, 17); cout << "검색 모드로 출발지를 찾으시려면 눌러주세요";
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
                            gotoxy(162, 18); cout << "검색어 (키워드) >> ";
                            gotoxy(182, 18); cin >> str;
                            s = m.matching(str);
                            break;
                        }
                        rib(5,16,5,18) {
                            gotoxy(162, 17); cout << "법학전문대학원, 형설관, 국제교류본부                                                                    " << endl;
                            s=1; break;
                        }                        
                        rib(8, 16, 22, 30) {
                            gotoxy(162, 17); cout << "S21 (농업과학기술센터)                                                                    " << endl;
                            s = 2; break;
                        }
                        rib(19, 26, 21, 25) {
                            gotoxy(162, 17); cout << "N10 (대학 본부,국제교류본부)                                                                    " << endl;
                            s = 3; break;
                        }
                        rib(3, 9, 33, 36) {
                            gotoxy(162, 17); cout << "S19 (승리관, 종양 연구소)                                                                    " << endl;
                            s = 4; break;
                        }
                        rib(12, 16, 33, 36) {
                            gotoxy(162, 17); cout << "S20 (첨단바이오 연구센터)                                                                    " << endl;
                            s = 5; break;
                        }
                        rib(15, 21, 40, 47) {
                            gotoxy(162, 17); cout << "S17 (양성재)                                                                    " << endl;
                            s = 6; break;
                        }
                        rib(29, 34, 33, 36) {
                            gotoxy(162, 17); cout << "S14 (동아리방)                                                                    " << endl;
                            s = 7; break;
                        }
                        rib(30, 37, 40, 45) {
                            gotoxy(162, 17); cout << "S8 (공연장, 공터)                                                                    " << endl;
                            s = 8; break;
                        }
                        rib(41, 44, 35, 38) {
                            gotoxy(162, 17); cout << "S9 (박물관)                                                                    " << endl;
                            s = 9; break;
                        }
                        rib(40, 43, 44, 46) {
                            gotoxy(162, 17); cout << "S3 (본부관리동 창고)                                                                    " << endl;
                            s = 10; break;
                        }
                        rib(39, 44, 48, 51) {
                            gotoxy(162, 17); cout << "S4-1 (전자정보 3관)                                                                    " << endl;
                            s = 11; break;
                        }
                        rib(39, 44, 56, 59) {
                            gotoxy(162, 17); cout << "S4-2 (나이팅게일관)                                                                    " << endl;
                            s = 12; break;
                        }
                        rib(46, 49, 44, 46) {
                            gotoxy(162, 17); cout << "S2 (전산정보원)                                                                    " << endl;
                            s = 13; break;
                        }
                        rib(32, 42, 23, 26) {
                            gotoxy(162, 17); cout << "N11 (공동실험실습관)                                                                    " << endl;
                            s = 14; break;
                        }
                        rib(45, 49, 21, 26) {
                            gotoxy(162, 17); cout << "솔못                                                                    " << endl;
                            s = 15; break;
                        }
                        rib(44, 50, 17, 19) {
                            gotoxy(162, 17); cout << "N13 (경영학관)                                                                    " << endl;
                            s = 16; break;
                        }
                        rib(35, 41, 11, 17) {
                            gotoxy(162, 17); cout << "N14 (인문사회관)                                                                    " << endl;
                            s = 17; break;
                        }
                        rib(44, 49, 11, 15) {
                            gotoxy(162, 17); cout << "N16-2 (미술관)                                                                    " << endl;
                            s = 18; break;
                        }
                        rib(36, 41, 2, 5) {
                            gotoxy(162, 17); cout << "N17 (개성재)                                                                    " << endl;
                            s = 19; break;
                        }
                        rib(46, 52, 2, 5) {
                            gotoxy(162, 17); cout << "N18 (법학관)                                                                    " << endl;
                            s = 20; break;
                        }
                        rib(51, 57, 48, 51) {
                            gotoxy(162, 17); cout << "S1-5 (자연과학대학 5호관)                                                                    " << endl;
                            s = 21; break;
                        }
                        rib(53, 59, 44, 46) {
                            gotoxy(162, 17); cout << "S1-4 (자연과학대학 4호관)                                                                    " << endl;
                            s = 22; break;
                        }
                        rib(48, 57, 28, 30) {
                            gotoxy(162, 17); cout << "S1-1 (자연과학대학 1호관)                                                                    " << endl;
                            s = 23; break;
                        }
                        rib(54, 59, 32, 34) {
                            gotoxy(162, 17); cout << "S1-2 (자연과학대학 2호관)                                                                    " << endl;
                            s = 24; break;
                        }
                        rib(58, 59, 35, 40) {
                            gotoxy(162, 17); cout << "S1-7 (과학기술도서관)                                                                    " << endl;
                            s = 25; break;
                        }
                        rib(54, 59, 41, 43) {
                            gotoxy(162, 17); cout << "S1-3 (자연과학대학 3호관)                                                                    " << endl;
                            s = 26; break;
                        }
                        rib(52, 59, 21, 26) {
                            gotoxy(162, 17); cout << "N12 (중앙 도서관)                                                                    " << endl;
                            s = 27; break;
                        }
                        rib(55, 61, 17, 19) {
                            gotoxy(162, 17); cout << "N15 (사회과학대학 본관)                                                                    " << endl;
                            s = 28; break;
                        }
                        rib(66, 71, 13, 19) {
                            gotoxy(162, 17); cout << "E2 (개신문화관, 충북대 서점)                                                                    " << endl;
                            s = 29; break;
                        }
                        rib(55, 61, 8, 11) {
                            gotoxy(162, 17); cout << "N16-1 (인문대학 본관)                                                                    " << endl;
                            s = 30; break;
                        }
                        rib(69, 74, 8, 11) {
                            gotoxy(162, 17); cout << "E1 (사범대학)                                                                    " << endl;
                            s = 31; break;
                        }
                        rib(65, 66, 1, 5) {
                            gotoxy(162, 17); cout << "N21 (은하수식당)                                                                    " << endl;
                            s = 32; break;
                        }
                        rib(69, 74, 1, 6) {
                            gotoxy(162, 17); cout << "N20 (생활과학관)                                                                    " << endl;
                            s = 33; break;
                        }
                        rib(56, 61, 2, 6) {
                            gotoxy(162, 17); cout << "N19 (제2본관)                                                                    " << endl;
                            s = 34; break;
                        }
                        rib(63, 66, 21, 26) {
                            gotoxy(162, 17); cout << "E3 (제1학생회관, 신학)                                                                    " << endl;
                            s = 35; break;
                        }
                        rib(69, 72, 21, 26) {
                            gotoxy(162, 17); cout << "E3-1 (NH관, 헬스장)                                                                    " << endl;
                            s = 36; break;
                        }
                        rib(62, 69, 28, 30) {
                            gotoxy(162, 17); cout << "E8-1 (공과대학 1호관)                                                                    " << endl;
                            s = 37; break;
                        }
                        rib(62, 73, 36, 38) {
                            gotoxy(162, 17); cout << "E8-2 (공대 합동강의동)                                                                    " << endl;
                            s = 38; break;
                        }
                        rib(63, 72, 45, 47) {
                            gotoxy(162, 17); cout << "E8-7 (전자정보 1관)                                                                    " << endl;
                            s = 39; break;
                        }
                        rib(64, 68, 51, 53) {
                            gotoxy(162, 17); cout << "E9 (학연산공동기술연구원)                                                                    " << endl;
                            s = 40; break;
                        }
                        rib(71, 73, 30, 35) {
                            gotoxy(162, 17); cout << "E8-3 (공과대학 2호관)                                                                    " << endl;
                            s = 41; break;
                        }
                        rib(76, 80, 33, 37) {
                            gotoxy(162, 17); cout << "E8-4 (제1공장동)                                                                    " << endl;
                            s = 42; break;
                        }
                        rib(76, 80, 40, 44) {
                            gotoxy(162, 17); cout << "E8-5 (제2공장동)                                                                    " << endl;
                            s = 43; break;
                        }
                        rib(83, 84, 40, 46) {
                            gotoxy(162, 17); cout << "E8-8 (공과대학 4호관)                                                                    " << endl;
                            s = 44; break;
                        }
                        rib(76, 80, 46, 48) {
                            gotoxy(162, 17); cout << "E8-6 (공과대학 3호관)                                                                    " << endl;
                            s = 45; break;
                        }
                        rib(78, 80, 48, 51) {
                            gotoxy(162, 17); cout << "E8-6 (공과대학 3호관)                                                                    " << endl;
                            s = 45; break;
                        }
                        rib(70, 73, 49, 53) {
                            gotoxy(162, 17); cout << "E10 (전자정보 2관)                                                                    " << endl;
                            s = 46; break;
                        }
                        rib(76, 81, 53, 55) {
                            gotoxy(162, 17); cout << "E8-10 (공과대학 5호관)                                                                    " << endl;
                            s = 47; break;
                        }
                        rib(78, 88, 17, 26) {
                            gotoxy(162, 17); cout << "E4-1 (소운동장)                                                                    " << endl;
                            s = 48; break;
                        }
                        rib(88, 94, 50, 53) {
                            gotoxy(162, 17); cout << "E8-11 (양진재)                                                                    " << endl;
                            s = 49; break;
                        }
                        rib(92, 94, 46, 50) {
                            gotoxy(162, 17); cout << "E8-11 (양진재)                                                                    " << endl;
                            s = 49; break;
                        }
                        rib(89, 93, 28, 30) {
                            gotoxy(162, 17); cout << "E7-3 (의과대학 2호관)                                                                    " << endl;
                            s = 50; break;
                        }
                        rib(92, 117, 17, 26) {
                            gotoxy(162, 17); cout << "E4-2 (대운동장)                                                                    " << endl;
                            s = 51; break;
                        }
                        rib(98, 103, 28, 30) {
                            gotoxy(162, 17); cout << "E7-1 (의과대학 1호관)                                                                    " << endl;
                            s = 52; break;
                        }
                        rib(98, 103, 32, 37) {
                            gotoxy(162, 17); cout << "E7-2                                                                    " << endl;
                            s = 53; break;
                        }
                        rib(107, 128, 28, 40) {
                            gotoxy(162, 17); cout << "E7-4 (충북대학교 병원)                                                                    " << endl;
                            s = 54; break;
                        }
                    }
                }
            }
            gotoxy(140, 19); cout << "도착지를 눌러주세요>> ";
            gotoxy(162, 19); cout << "(검색 모드로 도착지를 찾으시려면 눌러주세요)";
            while (true)
            {
                if (be_input())
                {
                    if (get_input(&key, &pos) != 0)
                    {
                        MOUSE_EVENT;
                        x = pos.X; y = pos.Y;
                        rib(162, 204, 19, 19) {
                            gotoxy(162, 20); cout << "검색어 (키워드) >> ";
                            gotoxy(182, 20); cin >> str;
                            e = m.matching(str);
                            break;
                        }
                        rib(5, 16, 5, 18) {
                            gotoxy(162, 19); cout << "법학전문대학원, 형설관, 국제교류본부                                                                    " << endl;
                            e = 1; break;
                        }
                        rib(8, 16, 22, 30) {
                            gotoxy(162, 19); cout << "S21 (농업과학기술센터)                                                                    " << endl;
                            e = 2; break;
                        }
                        rib(19, 26, 21, 25) {
                            gotoxy(162, 19); cout << "N10 (대학 본부,국제교류본부)                                                                    " << endl;
                            e = 3; break;
                        }
                        rib(3, 9, 33, 36) {
                            gotoxy(162, 19); cout << "S19 (승리관, 종양 연구소)                                                                    " << endl;
                            e = 4; break;
                        }
                        rib(12, 16, 33, 36) {
                            gotoxy(162, 19); cout << "S20 (첨단바이오 연구센터)                                                                    " << endl;
                            e = 5; break;
                        }
                        rib(15, 21, 40, 47) {
                            gotoxy(162, 19); cout << "S17 (양성재)                                                                    " << endl;
                            e = 6; break;
                        }
                        rib(29, 34, 33, 36) {
                            gotoxy(162, 19); cout << "S14 (동아리방)                                                                    " << endl;
                            e = 7; break;
                        }
                        rib(30, 37, 40, 45) {
                            gotoxy(162, 19); cout << "S8 (공연장, 공터)                                                                    " << endl;
                            e = 8; break;
                        }
                        rib(41, 44, 35, 38) {
                            gotoxy(162, 19); cout << "S9 (박물관)                                                                    " << endl;
                            e = 9; break;
                        }
                        rib(40, 43, 44, 46) {
                            gotoxy(162, 19); cout << "S3 (본부관리동 창고)                                                                    " << endl;
                            e = 10; break;
                        }
                        rib(39, 44, 48, 51) {
                            gotoxy(162, 19); cout << "S4-1 (전자정보 3관)                                                                    " << endl;
                            e = 11; break;
                        }
                        rib(39, 44, 56, 59) {
                            gotoxy(162, 19); cout << "S4-2 (나이팅게일관)                                                                    " << endl;
                            e = 12; break;
                        }
                        rib(46, 49, 44, 46) {
                            gotoxy(162, 19); cout << "S2 (전산정보원)                                                                    " << endl;
                            e = 13; break;
                        }
                        rib(32, 42, 23, 26) {
                            gotoxy(162, 19); cout << "N11 (공동실험실습관)                                                                    " << endl;
                            e = 14; break;
                        }
                        rib(45, 49, 21, 26) {
                            gotoxy(162, 19); cout << "솔못                                                                    " << endl;
                            e = 15; break;
                        }
                        rib(44, 50, 17, 19) {
                            gotoxy(162, 19); cout << "N13 (경영학관)                                                                    " << endl;
                            e = 16; break;
                        }
                        rib(35, 41, 11, 17) {
                            gotoxy(162, 19); cout << "N14 (인문사회관)                                                                    " << endl;
                            e = 17; break;
                        }
                        rib(44, 49, 11, 15) {
                            gotoxy(162, 19); cout << "N16-2 (미술관)                                                                    " << endl;
                            e = 18; break;
                        }
                        rib(36, 41, 2, 5) {
                            gotoxy(162, 19); cout << "N17 (개성재)                                                                    " << endl;
                            e = 19; break;
                        }
                        rib(46, 52, 2, 5) {
                            gotoxy(162, 19); cout << "N18 (법학관)                                                                    " << endl;
                            e = 20; break;
                        }
                        rib(51, 57, 48, 51) {
                            gotoxy(162, 19); cout << "S1-5 (자연과학대학 5호관)                                                                    " << endl;
                            e = 21; break;
                        }
                        rib(53, 59, 44, 46) {
                            gotoxy(162, 19); cout << "S1-4 (자연과학대학 4호관)                                                                    " << endl;
                            e = 22; break;
                        }
                        rib(48, 57, 28, 30) {
                            gotoxy(162, 19); cout << "S1-1 (자연과학대학 1호관)                                                                    " << endl;
                            e = 23; break;
                        }
                        rib(54, 59, 32, 34) {
                            gotoxy(162, 19); cout << "S1-2 (자연과학대학 2호관)                                                                    " << endl;
                            e = 24; break;
                        }
                        rib(58, 59, 35, 40) {
                            gotoxy(162, 19); cout << "S1-7 (과학기술도서관)                                                                    " << endl;
                            e = 25; break;
                        }
                        rib(54, 59, 41, 43) {
                            gotoxy(162, 19); cout << "S1-3 (자연과학대학 3호관)                                                                    " << endl;
                            e = 26; break;
                        }
                        rib(52, 59, 21, 26) {
                            gotoxy(162, 19); cout << "N12 (중앙 도서관)                                                                    " << endl;
                            e = 27; break;
                        }
                        rib(55, 61, 17, 19) {
                            gotoxy(162, 19); cout << "N15 (사회과학대학 본관)                                                                    " << endl;
                            e = 28; break;
                        }
                        rib(66, 71, 13, 19) {
                            gotoxy(162, 19); cout << "E2 (개신문화관, 충북대 서점)                                                                    " << endl;
                            e = 29; break;
                        }
                        rib(55, 61, 8, 11) {
                            gotoxy(162, 19); cout << "N16-1 (인문대학 본관)                                                                    " << endl;
                            e = 30; break;
                        }
                        rib(69, 74, 8, 11) {
                            gotoxy(162, 19); cout << "E1 (사범대학)                                                                    " << endl;
                            e = 31; break;
                        }
                        rib(65, 66, 1, 5) {
                            gotoxy(162, 19); cout << "N21 (은하수식당)                                                                    " << endl;
                            e = 32; break;
                        }
                        rib(69, 74, 1, 6) {
                            gotoxy(162, 19); cout << "N20 (생활과학관)                                                                    " << endl;
                            e = 33; break;
                        }
                        rib(56, 61, 2, 6) {
                            gotoxy(162, 19); cout << "N19 (제2본관)                                                                    " << endl;
                            e = 34; break;
                        }
                        rib(63, 66, 21, 26) {
                            gotoxy(162, 19); cout << "E3 (제1학생회관, 신학)                                                                    " << endl;
                            e = 35; break;
                        }
                        rib(69, 72, 21, 26) {
                            gotoxy(162, 19); cout << "E3-1 (NH관, 헬스장)                                                                    " << endl;
                            e = 36; break;
                        }
                        rib(62, 69, 28, 30) {
                            gotoxy(162, 19); cout << "E8-1 (공과대학 1호관)                                                                    " << endl;
                            e = 37; break;
                        }
                        rib(62, 73, 36, 38) {
                            gotoxy(162, 19); cout << "E8-2 (공대 합동강의동)                                                                    " << endl;
                            e = 38; break;
                        }
                        rib(63, 72, 45, 47) {
                            gotoxy(162, 19); cout << "E8-7 (전자정보 1관)                                                                    " << endl;
                            e = 39; break;
                        }
                        rib(64, 68, 51, 53) {
                            gotoxy(162, 19); cout << "E9 (학연산공동기술연구원)                                                                    " << endl;
                            e = 40; break;
                        }
                        rib(71, 73, 30, 35) {
                            gotoxy(162, 19); cout << "E8-3 (공과대학 2호관)                                                                    " << endl;
                            e = 41; break;
                        }
                        rib(76, 80, 33, 37) {
                            gotoxy(162, 19); cout << "E8-4 (제1공장동)                                                                    " << endl;
                            e = 42; break;
                        }
                        rib(76, 80, 40, 44) {
                            gotoxy(162, 19); cout << "E8-5 (제2공장동)                                                                    " << endl;
                            e = 43; break;
                        }
                        rib(83, 84, 40, 46) {
                            gotoxy(162, 19); cout << "E8-8 (공과대학 4호관)                                                                    " << endl;
                            e = 44; break;
                        }
                        rib(76, 80, 46, 48) {
                            gotoxy(162, 19); cout << "E8-6 (공과대학 3호관)                                                                    " << endl;
                            e = 45; break;
                        }
                        rib(78, 80, 48, 51) {
                            gotoxy(162, 19); cout << "E8-6 (공과대학 3호관)                                                                    " << endl;
                            e = 45; break;
                        }
                        rib(70, 73, 49, 53) {
                            gotoxy(162, 19); cout << "E10 (전자정보 2관)                                                                    " << endl;
                            e = 46; break;
                        }
                        rib(76, 81, 53, 55) {
                            gotoxy(162, 19); cout << "E8-10 (공과대학 5호관)                                                                    " << endl;
                            e = 47; break;
                        }
                        rib(78, 88, 17, 26) {
                            gotoxy(162, 19); cout << "E4-1 (소운동장)                                                                    " << endl;
                            e = 48; break;
                        }
                        rib(88, 94, 50, 53) {
                            gotoxy(162, 19); cout << "E8-11 (양진재)                                                                    " << endl;
                            e = 49; break;
                        }
                        rib(92, 94, 46, 50) {
                            gotoxy(162, 19); cout << "E8-11 (양진재)                                                                    " << endl;
                            e = 49; break;
                        }
                        rib(89, 93, 28, 30) {
                            gotoxy(162, 19); cout << "E7-3 (의과대학 2호관)                                                                    " << endl;
                            e = 50; break;
                        }
                        rib(92, 117, 17, 26) {
                            gotoxy(162, 19); cout << "E4-2 (대운동장)                                                                    " << endl;
                            e = 51; break;
                        }
                        rib(98, 103, 28, 30) {
                            gotoxy(162, 19); cout << "E7-1 (의과대학 1호관)                                                                    " << endl;
                            e = 52; break;
                        }
                        rib(98, 103, 32, 37) {
                            gotoxy(162, 19); cout << "E7-2                                                                    " << endl;
                            e = 53; break;
                        }
                        rib(107, 128, 28, 40) {
                            gotoxy(162, 19); cout << "E7-4 (충북대학교 병원)                                                                    " << endl;
                            e = 54; break;
                        }
                    }
                }
            }
            gotoxy(140, 21);// cout << "<경로 안내>  ";
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

        /* case : 추천 경로 */ 

        
        else if(nn==2){
            gotoxy(140, 17); cout << "추천 경로 :: 원하는 경로를 눌러주세요";
            gotoxy(143, 19); cout << "  < 봄 커플 데이트 코스 >";
            gotoxy(143, 21); cout << "  < 빡센 조깅 코스 >";
            gotoxy(143, 23); cout << "  < 어두운 산책로 >";
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
                            gotoxy(143, 19); cout << "  < 봄 커플 데이트 코스 >" << "   " << "꽃이 피고, 꽃이 지는 길";
                            gotoxy(140, 27); cout << "즐거운 데이트하시길 바랍니다! ";
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
                            gotoxy(143, 21); cout << "  < 빡센 조깅 코스 >" << "   " << "걷는 기준 50분 전후 소요";
                            gotoxy(140, 27); cout << "안전한 운동되시길 바랍니다! ";
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
                            gotoxy(143, 23); cout << "  < 어두운 산책로 >" << "   " << "걷는 기준 30분 전후 소요" ;
                            gotoxy(140, 27); cout << "조용히 걷고 싶은 길";
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
            gotoxy(144, 17);  cout << "1682 충북대학교 병원 방면 정류장";
            gotoxy(144, 19);  cout << "710번 버스 ";

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
            gotoxy(144, 23);  cout << "1678 충북대학교 입구 방면 정류장";
            gotoxy(144, 25);  cout << "710번 버스 ";
            gotoxy(144, 26);  cout << "학교 통학버스";
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