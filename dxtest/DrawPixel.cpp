#include "DxLib.h"
#include<math.h>

typedef struct {
    int x, y, img, muki, walking_flag;
}ch_t;

char Key[256];
ch_t ch;



void DrawSquare(int x1, int y1, int x2, int y2, int thickness) {
    int White = GetColor(255, 255, 255);
    // 上辺
    for (int i = 0; i < thickness; ++i) {
        DrawLine(x1, y1 + i, x2, y1 + i, White);
    }
    // 下辺
    for (int i = 0; i < thickness; ++i) {
        DrawLine(x1, y2 - i, x2, y2 - i, White);
    }
    // 左辺
    for (int i = 0; i < thickness; ++i) {
        DrawLine(x1 + i, y1, x1 + i, y2, White);
    }
    // 右辺
    for (int i = 0; i < thickness; ++i) {
        DrawLine(x2 - i, y1, x2 - i, y2, White);
    }
}

int DrawHeart(int x,int y) {
	int Handle00 = LoadGraph("image/heart.png"); //画像を読み込む
	DrawRotaGraph(x, y, 0.05, 0.0, Handle00, TRUE); //画像の描画
	return 0;
}




int CharaWalk(int s1x, int s1y, int s2x, int s2y) {
    ch.walking_flag = 1; //歩くフラグを立てる
    if (Key[KEY_INPUT_UP] == 1 && ch.y > s1y) {  //上ボタンが押され、上の枠線を越えないように
        ch.muki = 0;         //上向きフラグを立てる
    }
    else if (Key[KEY_INPUT_LEFT] == 1 && ch.x > s1x) {  //左ボタンが押され、左の枠線を越えないように
        ch.muki = 1;         //左向きフラグを立てる
    }
    else if (Key[KEY_INPUT_DOWN] == 1 && ch.y < s2y) {  //下ボタンが押され、下の枠線を越えないように
        ch.muki = 2;         //下向きフラグを立てる
    }
    else if (Key[KEY_INPUT_RIGHT] == 1 && ch.x < s2x) {  //右ボタンが押され、右の枠線を越えないように
        ch.muki = 3;         //右向きフラグを立てる
    }
    else {
        ch.walking_flag = 0; //歩かないフラグを立てる
    }

    if (ch.walking_flag == 1) { //歩くフラグが立っていたら
        if (ch.muki == 0)        //上向きならch.y座標を減らす
            ch.y--;
        else if (ch.muki == 1)        //左向きならch.x座標を減らす
            ch.x--;
        else if (ch.muki == 2)        //下向きならch.y座標を増やす
            ch.y++;
        else if (ch.muki == 3)        //右向きならch.x座標を増やす
            ch.x++;
    }
    DrawHeart(ch.x, ch.y); //ハートを描画
    return 0;
}

// 重力操作の攻撃
int BlueCharaWalk(int s1x, int s1y, int s2x, int s2y,int g) {
    // 重力計算するなら使う以下3行
    //int ymax = s1y+9; //最高到達点
    //int time1=0, time2=0;
    //double t;
    ch.walking_flag = 1; //歩くフラグを立てる
    int jumpflag = 0;
    if (Key[KEY_INPUT_UP] == 1 && ch.y > s1y) {  //上ボタンが押され、上の枠線を越えないように
        // jumpflag = 1;
        // time1=GetNowCount();
        ch.muki = 0;         //上向きフラグを立てる
    }
    else if (Key[KEY_INPUT_LEFT] == 1 && ch.x > s1x) {  //左ボタンが押され、左の枠線を越えないように
        ch.muki = 1;         //左向きフラグを立てる
    }
    else if (Key[KEY_INPUT_DOWN] == 1 && ch.y < s2y) {  //下ボタンが押され、下の枠線を越えないように
        ch.muki = 2;         //下向きフラグを立てる
    }
    else if (Key[KEY_INPUT_RIGHT] == 1 && ch.x < s2x) {  //右ボタンが押され、右の枠線を越えないように
        ch.muki = 3;         //右向きフラグを立てる
    }else if(ch.y < s2y){
		ch.muki = 4;
	}
    else {
        ch.walking_flag = 0; //歩かないフラグを立てる
    }

    if (ch.walking_flag == 1) { //歩くフラグが立っていたら
        if (ch.muki == 0) {        //上向きならch.y座標を減らす
            //time2 = GetNowCount();
            //t = (double)(time2 - time1) / 1000;
            //ch.y = (int)((sqrt(2.000 * g * ymax) * t - 0.500 * g * t * t))+300;//y座標を計算
            ch.y--;
        }
        else if (ch.muki == 1)        //左向きならch.x座標を減らす
            ch.x--;
        else if (ch.muki == 2)        //下向きならch.y座標を増やす
            ch.y++;
        else if (ch.muki == 3)        //右向きならch.x座標を増やす
            ch.x++;
        else if (ch.muki == 4) {
            
            ch.y-=g;
		}
    }

    DrawHeart(ch.x, ch.y); //ハートを描画
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    ch.x = 300;
    ch.y = 300;
    ch.walking_flag = 0;


    SetGraphMode(630, 480, 32); //画面サイズ設定Undertale用
    if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1; //ウィンドウ化と初期化処理


    SetDrawScreen(DX_SCREEN_BACK);                                                 //描画先を裏画面に設定

    while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
        //↑ﾒｯｾｰｼﾞ処理        ↑画面をｸﾘｱ         ↑ｷｰﾎﾞｰﾄﾞ入力状態取得       ↑ESCが押されると終了
        int s1x = 250, s1y = 200, s2x = 400, s2y = 350,thick=5; //四角形の座標
        DrawSquare(s1x, s1y, s2x, s2y, thick); //四角形を描画
        // CharaWalk(s1x+thick+4,s1y+thick+4,s2x-thick-4,s2y-thick-4); //キャラクターを歩かせる
        BlueCharaWalk(s1x+thick+4,s1y+thick+4,s2x-thick-4,s2y-thick-4,-9.8); //キャラクターを歩かせる
        // Charajump(s1x+thick+4,s1y+thick+4,s2x-thick-4,s2y-thick-4); //キャラクターをジャンプさせる
        ScreenFlip();//裏画面を表画面に反映

    }

    DxLib_End();
    return 0;
}
