#include "DxLib.h"
#include<math.h>

typedef struct {
    int x, y, img, muki, walking_flag;
}ch_t;

char Key[256];
ch_t ch;



void DrawSquare(int x1, int y1, int x2, int y2, int thickness) {
    int White = GetColor(255, 255, 255);
    // ���
    for (int i = 0; i < thickness; ++i) {
        DrawLine(x1, y1 + i, x2, y1 + i, White);
    }
    // ����
    for (int i = 0; i < thickness; ++i) {
        DrawLine(x1, y2 - i, x2, y2 - i, White);
    }
    // ����
    for (int i = 0; i < thickness; ++i) {
        DrawLine(x1 + i, y1, x1 + i, y2, White);
    }
    // �E��
    for (int i = 0; i < thickness; ++i) {
        DrawLine(x2 - i, y1, x2 - i, y2, White);
    }
}

int DrawHeart(int x,int y) {
	int Handle00 = LoadGraph("image/heart.png"); //�摜��ǂݍ���
	DrawRotaGraph(x, y, 0.05, 0.0, Handle00, TRUE); //�摜�̕`��
	return 0;
}




int CharaWalk(int s1x, int s1y, int s2x, int s2y) {
    ch.walking_flag = 1; //�����t���O�𗧂Ă�
    if (Key[KEY_INPUT_UP] == 1 && ch.y > s1y) {  //��{�^����������A��̘g�����z���Ȃ��悤��
        ch.muki = 0;         //������t���O�𗧂Ă�
    }
    else if (Key[KEY_INPUT_LEFT] == 1 && ch.x > s1x) {  //���{�^����������A���̘g�����z���Ȃ��悤��
        ch.muki = 1;         //�������t���O�𗧂Ă�
    }
    else if (Key[KEY_INPUT_DOWN] == 1 && ch.y < s2y) {  //���{�^����������A���̘g�����z���Ȃ��悤��
        ch.muki = 2;         //�������t���O�𗧂Ă�
    }
    else if (Key[KEY_INPUT_RIGHT] == 1 && ch.x < s2x) {  //�E�{�^����������A�E�̘g�����z���Ȃ��悤��
        ch.muki = 3;         //�E�����t���O�𗧂Ă�
    }
    else {
        ch.walking_flag = 0; //�����Ȃ��t���O�𗧂Ă�
    }

    if (ch.walking_flag == 1) { //�����t���O�������Ă�����
        if (ch.muki == 0)        //������Ȃ�ch.y���W�����炷
            ch.y--;
        else if (ch.muki == 1)        //�������Ȃ�ch.x���W�����炷
            ch.x--;
        else if (ch.muki == 2)        //�������Ȃ�ch.y���W�𑝂₷
            ch.y++;
        else if (ch.muki == 3)        //�E�����Ȃ�ch.x���W�𑝂₷
            ch.x++;
    }
    DrawHeart(ch.x, ch.y); //�n�[�g��`��
    return 0;
}

// �d�͑���̍U��
int BlueCharaWalk(int s1x, int s1y, int s2x, int s2y,int g) {
    // �d�͌v�Z����Ȃ�g���ȉ�3�s
    //int ymax = s1y+9; //�ō����B�_
    //int time1=0, time2=0;
    //double t;
    ch.walking_flag = 1; //�����t���O�𗧂Ă�
    int jumpflag = 0;
    if (Key[KEY_INPUT_UP] == 1 && ch.y > s1y) {  //��{�^����������A��̘g�����z���Ȃ��悤��
        // jumpflag = 1;
        // time1=GetNowCount();
        ch.muki = 0;         //������t���O�𗧂Ă�
    }
    else if (Key[KEY_INPUT_LEFT] == 1 && ch.x > s1x) {  //���{�^����������A���̘g�����z���Ȃ��悤��
        ch.muki = 1;         //�������t���O�𗧂Ă�
    }
    else if (Key[KEY_INPUT_DOWN] == 1 && ch.y < s2y) {  //���{�^����������A���̘g�����z���Ȃ��悤��
        ch.muki = 2;         //�������t���O�𗧂Ă�
    }
    else if (Key[KEY_INPUT_RIGHT] == 1 && ch.x < s2x) {  //�E�{�^����������A�E�̘g�����z���Ȃ��悤��
        ch.muki = 3;         //�E�����t���O�𗧂Ă�
    }else if(ch.y < s2y){
		ch.muki = 4;
	}
    else {
        ch.walking_flag = 0; //�����Ȃ��t���O�𗧂Ă�
    }

    if (ch.walking_flag == 1) { //�����t���O�������Ă�����
        if (ch.muki == 0) {        //������Ȃ�ch.y���W�����炷
            //time2 = GetNowCount();
            //t = (double)(time2 - time1) / 1000;
            //ch.y = (int)((sqrt(2.000 * g * ymax) * t - 0.500 * g * t * t))+300;//y���W���v�Z
            ch.y--;
        }
        else if (ch.muki == 1)        //�������Ȃ�ch.x���W�����炷
            ch.x--;
        else if (ch.muki == 2)        //�������Ȃ�ch.y���W�𑝂₷
            ch.y++;
        else if (ch.muki == 3)        //�E�����Ȃ�ch.x���W�𑝂₷
            ch.x++;
        else if (ch.muki == 4) {
            
            ch.y-=g;
		}
    }

    DrawHeart(ch.x, ch.y); //�n�[�g��`��
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    ch.x = 300;
    ch.y = 300;
    ch.walking_flag = 0;


    SetGraphMode(630, 480, 32); //��ʃT�C�Y�ݒ�Undertale�p
    if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1; //�E�B���h�E���Ə���������


    SetDrawScreen(DX_SCREEN_BACK);                                                 //�`���𗠉�ʂɐݒ�

    while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
        //��ү���ޏ���        ����ʂ�ر         �����ް�ޓ��͏�Ԏ擾       ��ESC���������ƏI��
        int s1x = 250, s1y = 200, s2x = 400, s2y = 350,thick=5; //�l�p�`�̍��W
        DrawSquare(s1x, s1y, s2x, s2y, thick); //�l�p�`��`��
        // CharaWalk(s1x+thick+4,s1y+thick+4,s2x-thick-4,s2y-thick-4); //�L�����N�^�[���������
        BlueCharaWalk(s1x+thick+4,s1y+thick+4,s2x-thick-4,s2y-thick-4,-9.8); //�L�����N�^�[���������
        // Charajump(s1x+thick+4,s1y+thick+4,s2x-thick-4,s2y-thick-4); //�L�����N�^�[���W�����v������
        ScreenFlip();//����ʂ�\��ʂɔ��f

    }

    DxLib_End();
    return 0;
}
