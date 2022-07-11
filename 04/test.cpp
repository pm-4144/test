// バンダイナムコスタジオ インターン選考問題

/*
座席管理クラスを作成してください。
*/

// includeは必要に応じて追加/削除していただいて大丈夫です。
#include <iostream>
#include <list>
#include <algorithm>
#include <random>
#include <fstream>

// 最初から用意されているクラス名やメソッド名は変更しないでください
// メソッドやメンバ変数等は自由に追加していただいて大丈夫ですが、このファイルのみで完結させる必要があります。
class SEAT
{
public:
    int seat[10];       //0 as 空席, positive integer as 使用中
    int seat_ast[10];   //連番の空き数を格納し、その最初のカウンター番号を引数に持つarray
    int seat_til[5];    //seat_astを逆引き、つまりn人入れる先頭カウンター番号を格納

    // コンストラクタです
    SEAT()
    {
        // TODO
        // 実装してください
        for (int i = 0; i < 10; i++)
            seat[i] = 0;
    }

    // デストラクタです
    ~SEAT()
    {
        // 必要に応じて実装してください
    }

    // お客様の来店時に呼ばれるメソッドです
    // nはお客様の人数です。現在5名様以上の来店はご遠慮いただいておりますので、n には1～4の値が来ます。
    // 戻り値には、人数分連続して空いている、一番若いカウンター番号を返してください。
    // 人数分連続した席の確保が出来なければ-1を返してください。
    // (例)
    // 0123456789 <- カウンター番号
    // ....oo.... <- . 空き / o 使用中
    // の時に allocate(4) が呼ばれた場合 0を返してください。 6は一番若いという条件を満たしていません。
    // (例)
    // 0123456789 <- カウンター番号
    // o..oooo.o. <- . 空き / o 使用中
    // の時に allocate(4) が呼ばれた場合 -1を返してください
    int allocate(int n)
    {
        // TODO
        // 実装してください
        if (n > 4 || n <= 0) return -1;   //五人以上お断り

        int max = 10;   //空席の最大数
        for (int i = 0; i < 10; i++){
            if (seat[i] > 0) max--; // 空席の数をカウント
        }
        if (n > max) return -1; //空席の数よりもグループの人数が多い時

        // seat_ast[10]   連番の空き数を格納し、その最初のカウンター番号を引数に持つarray
        for (int i = 0; i < 10; i++) seat_ast[i] = 0;   //initialization

        for (int i = 0; i < 10; i++){   //set the array
            int sum = 0;
            for (int j = i; j < 10; j++){
                if (seat[j] > 0) break;
                sum++;
            }
            seat_ast[i] = sum;
        }
//	for (int i = 0; i < 10;) std::cout << seat_ast[i];std::cout<<std::endl;


        // seat_til[5]    //seat_astを逆引き、つまりn人入れる先頭カウンター番号を格納
        for (int i = 0; i < 5; i++) seat_til[i] = -1;    //initialization
        for (int i = 1; i < 5; i++){
            for (int j = 0; j < 10; j++){
                if (seat_ast[j] >= i){
                    seat_til[i] = j;
                    break;
                }
            }
        }

        if (seat_til[n] < 0) return -1; //連番の席がないのでお断りお断り

        for (int i = 0; i < n; i++){    //空席を埋める
            seat[seat_til[n] + i] = n - i;
        }

        return seat_til[n];
    }

    // お客様が帰られる時に呼ばれるメソッドです
    // nはallocate時に返ってきたカウンター番号です。
    // allocate時の人数分お帰りになられます。バラバラに帰られることはありません。
    // 席の確保ができなかった時にも呼ばれることがあるので -1 が入力されても問題の無いように実装してください。
    // (例)
    // 全席空席の状態で allocate(4) を行い 0 が返ってきた時に
    // 0123456789 <- カウンター番号
    // oooo...... <- . 空き / o 使用中
    // free(0)を行うと
    // 0123456789 <- カウンター番号
    // .......... <- . 空き / o 使用中
    // 全席空席にもどしてください
    void free(int n)
    {
        // TODO
        // 実装してください
        if (n < 0 || n > 9 ) return;
	if (n > 0 && seat[n-1] > seat[n]) return;
        int tmp = seat[n];
        for (int i = 0; i < tmp; i++){
            seat[n + i] = 0;

        }
    }
};

#define MIN 1
#define MAX 10

int main(){

using std::cout;
using std::endl;

std::random_device rd;
std::default_random_engine engine(rd());
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist1(1, 10);
std::uniform_int_distribution<int> dist2(1, 6);
std::uniform_int_distribution<int> dist3(0, 9);
//	for(int i=0;i<10;i++)
//	cout << distr(rd) << endl;



SEAT test;
cout << "一組ずつ来て帰る" << endl;
for(int j=0;j<30;j++){
int a, b; a  = test.allocate((b = dist1(rd)));
cout << j <<", " << b << " : ";
for(int i=0;i<10;i++)cout << test.seat[i];cout << " -> ";

test.free(a);
for(int i=0;i<10;i++)cout << test.seat[i]; //cout << " ( ";
/*
for(int i=0;i<10;i++)cout << test.seat_ast[i];cout << ", ";
for(int i=0;i<5;i++)cout << test.seat_til[i];cout << ")";
*/
cout << endl;
}
cout << endl;

cout << "5組ずつきて、来た順に帰る" << endl;
for (int k = 0; k < 10; k++){
int c[10], d;
for(int j=0;j<5;j++){
c[j]=test.allocate((d = dist2(rd)));
cout << "in(" << d << ") ";
for(int i=0;i<10;i++)cout << test.seat[i];cout << " -> ";
}
cout<<endl;

for(int j=0;j<5;j++){
test.free(c[j]);
cout << "out   ";
for(int i=0;i<10;i++)cout << test.seat[i];cout << " -> ";
}
cout<<endl;cout<<endl;
}


cout << "random" << endl;
for(int j=0;j<30;j++){
int a, b; test.allocate((b = dist2(rd)));
cout << j <<", " << b << " : ";
for(int i=0;i<10;i++)cout << test.seat[i];cout << " -> ";

test.free((b = dist3(rd))); cout << b << ", ";
test.free((b = dist3(rd))); cout << b << ", ";
test.free((b = dist3(rd))); cout << b << ", ";
for(int i=0;i<10;i++)cout << test.seat[i]; //cout << " ( ";
/*
for(int i=0;i<10;i++)cout << test.seat_ast[i];cout << ", ";
for(int i=0;i<5;i++)cout << test.seat_til[i];cout << ")";
*/
cout << endl;
}
cout << endl;


return 0;
}







