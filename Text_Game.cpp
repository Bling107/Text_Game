#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <vector>

#pragma comment(lib, "user32")
using namespace std;

string slot[9];    


int Max_Hpcal;
int pre_Hpcal;
int Max_Mpcal;
int pre_Mpcal;

namespace Item {

    /**
    * Item클래스
    * setName 아이템이름
    * set_func 기능정하기
    * use_Item 아이템 사용
    */
  class Item_class {

    public:

        /**
        * 아이템 이름 set
        * @param setItem_name 아이템이름 넣기
        */
        void setName(string setItem_name) {

            Item_name = setItem_name;

        }

        /**
        * 아이템의 기능
        * @param isinc 증간지 감소인지 증가는 true 감소는 false
        * @param forcal 연산할 수
        * @param amount 증가,감소량
        */
        void set_func(bool set_inc, int set_cal, int set_amount) {

            set_inc = Item_class::isinc;
            set_cal = Item_class::forcal;
            set_amount = Item_class::amount;

        }

        void use_item() {

            Item_func(Item_class::isinc, Item_class::forcal, Item_class::amount);

        }


        /*아이템 이름 리턴*/
        string getItemName() {

            return Item_name;

        }

    private:

        string Item_name;
        bool isinc = true;
        int forcal = 0;
        int amount = 0;

        int Item_func(bool _isinc, int _forcal, int _amount) {

            if (isinc == true)
                return forcal + amount;
            else
                return forcal - amount;

        }

   };


        Item_class apple;
        
}

void Item_set() {

    Item::apple.setName("apple");
    
}

//색상
enum {
    BLACK,
    DARK_BLUE,
    DARK_GREEN,
    DARK_SKYBLUE,
    DARK_RED,
    DARK_VOILET,
    DAKR_YELLOW,
    GRAY,
    DARK_GRAY,
    BLUE,
    GREEN,
    SKYBLUE,
    RED,
    VIOLET,
    YELLOW,
    WHITE,
};

// 콘솔 텍스트 색상 변경해주는 함수
void setColor(unsigned short text) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

//커서 좌표를 변경해주는 함수
void gotoxy(int x, int y)
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}


void print_slot(string for_add, int slot_num) {

    int x_first = 80;
    int x_sec = 80;
    int x_third = 80;


    slot[slot_num - 1] = for_add;

    //슬롯 생성
    for (int i = 0; i < 9; i++) {

        if (i >= 0 && i < 3) {
            gotoxy(x_first + 1, 4);
            cout << "          ";
            gotoxy(x_first, 4);
            gotoxy(x_first + int(slot[i].size() - slot[i].size() / 2), 4);
            cout << slot[i];
            x_first += 13;

        }
        else if (i >= 3 && i < 6) {
            
            gotoxy(x_sec + 1, 10);
            cout << "          ";
            gotoxy(x_sec, 10);
            gotoxy(x_sec + int(slot[i].size() - slot[i].size() / 2), 10);
            cout << slot[i];
            x_sec += 13;

        }
        else if (i >= 6 && i < 9) {

            gotoxy(x_sec + 1, 16);
            cout << "          ";
            gotoxy(x_third, 16);
            gotoxy(x_third + int(slot[i].size() - slot[i].size() / 2), 16);
            cout << slot[i];
             x_third += 13;
        }
        
       
        
    }

}

void Title() {

    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

    gotoxy(85, 20);
    cout << "Made by  반짝" << endl;
    Sleep(1000);
    gotoxy(77, 25);
    cout << "전체화면 플레이를 권장합니다." << endl;

    gotoxy(10, 10);

}



/** 
*HP출력하는 함수
* @param Max_Hp 최대체력
* @param pre_Hp 현재 체력
*/
void set_HP(int Max_Hp, int pre_Hp) {

    Max_Hpcal = Max_Hp;
    pre_Hpcal = pre_Hp;

    setColor(RED);
    gotoxy(121, 3);
    cout << "          ";
    gotoxy(121, 3);
    cout << "HP:" << pre_Hp << "/" << Max_Hp << endl;
    setColor(WHITE);
}

/**
* 데미지 계산
* @param deal 넣을 데미지
*/
void getDamage(int deal) {

    pre_Hpcal -= deal;
    set_HP(Max_Hpcal, pre_Hpcal);

}


/**
*Mp출력하는 함수
* @param Max_Mp 최대마나
* @param pre_Mp 현재 마나
*/
void set_MP(int Max_Mp, int pre_Mp) {

    Max_Mpcal = Max_Mp;
    pre_Mpcal = pre_Mp;

    setColor(BLUE);
    gotoxy(121, 4);
    cout << "          ";
    gotoxy(121, 4);
    cout << "MP:" << pre_Mp << "/" << Max_Mp << endl;
    setColor(WHITE);
}
/**
* Mp 사용
* @param amount 사용량
*/
void UseMp(int amount) {

    pre_Mpcal -= amount;
    set_HP(Max_Mpcal, pre_Mpcal);

}

void Encounter() {

    string situ;
    int situ_line = 0;

    fstream situation("Encounters/Start%n.txt", 30);

    if (situation.is_open()) {

        while (getline(situation, situ)) {

            gotoxy(0,situ_line);
            cout << situ << endl;
            situ_line++;

        }
        
        situation.close();
    }
    else {

        cout << "open failed" << endl;

    }

}

void Game_Screen() {

    system("cls");

    int a, b, c, d;
    a = 0;
    b = 0;
    c = 0;
    d = 0;

    fstream inv("Ui/inventory.txt");
    fstream stats("Ui/Status.txt");
    fstream line("Ui/side_bar.txt");
    fstream under_line("Ui/under_bar.txt");

    string inven;
    string status;
    string outline;
    string under_bar;
    

    //인벤토리 생성
    if (inv.is_open()) {

        while (getline(inv, inven)) {
            gotoxy(80, a);
            cout << inven << endl;
            a++;
        }
        inv.close();
    }
    else {
        cout << "안열림" << endl;
    }
    //스테이터스 생성
    if (stats.is_open()) {

        while (getline(stats, status)) {
            gotoxy(120, b+1);
            cout << status << endl;
            b++;
        }
        set_HP(100,100);
        set_MP(200, 200);
        stats.close();
    }
    else {
        cout << "안열림" << endl;
    }
    //옆,아래 경계선 생성
    if (line.is_open()) {

        while (getline(line, outline)) {
            gotoxy(79, c);
            cout << outline << endl;
            c++;
        }
        line.close();
    }
    else {
        cout << "안열림" << endl;
    }


    if (under_line.is_open()) {

        while (getline(under_line, under_bar)) {
            gotoxy(0,d + 26);
            cout << under_bar << endl;
            d++;
        }
        under_line.close();
    }
    else {
        cout << "안열림" << endl;
    }

    Encounter();
    
    print_slot(Item::apple.getItemName(), 1);

     gotoxy(0, 27);
 }


void Small_Encounter() {



}

void Main() {

    char c = 0;

    gotoxy(85, 20);
    cout << "낭만 판타지" << endl;
    Sleep(1000);
    gotoxy(77, 25);
    cout << "시작하려면 ENTER를 눌러주세요" << endl;

    c = _getch();

      if (c == 13) {

            Game_Screen();

      }

    }
    

int main() {

    SetConsoleOutputCP(20949);

    Item_set();

    Title();
    Sleep(1500);
    system("cls");
    Main();
    
    gotoxy(0, 27);

    system("pause");
}