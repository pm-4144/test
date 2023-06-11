//
//  main.cpp
//  reversi
//
//  Created by Pino Marianne on 2023/06/06.
//

#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

#include <cmath>
#include <string>

#include "reversi.hpp"

using std::cout;
using std::endl;

#if 0
#define INVERT_COLOR
#endif

namespace {
int WINDOW_WIDTH  = 800;  // window's width
int WINDOW_HEIGHT = 600;  // window's height

constexpr size_t cell_width   = 70;
constexpr size_t cell_height  = 70;
constexpr size_t cell_voffset = 20;  // vertical offset
constexpr size_t cell_hoffset = 20;  // horizonal offset
//constexpr double M_PI = 3.14159265358979;

constexpr size_t piece_radius = 30;

bool is_your_turn{};
bool is_paused{};
bool is_over{};
const std::string str_color[2] =
#ifndef INVERT_COLOR
    {"black", "white"};  // standard color
#else
    {"white", "black"};  // invert color
#endif

auto cell_color_1 = []{
#ifndef INVERT_COLOR
    glColor3d(.2, .6, .2);  // standard color
#else
    glColor3d(.8, .4, .8);  // invert color
#endif
};

auto cell_color_2 = []{
#ifndef INVERT_COLOR
    glColor3d(.1, .4, .1);  // standard color
#else
    glColor3d(.9, .6, .9);  // invert color
#endif
};

auto menu_color = []{
#ifndef INVERT_COLOR
    glColor4d(1., 1., .0, .4);  // standard color
#else
    glColor4d(.0, .0, 1., .4);  // invert color
#endif
};

auto theme_color = []{
#ifndef INVERT_COLOR
    glClearColor(.0, .0, .0, 1.0);  // standard color
#else
    glClearColor(1., 1., 1., 1.0);  // invert color
#endif
};

auto chr_color = []{
#ifndef INVERT_COLOR
    glColor3d(1., 1., 1.);  // standard color
#else
    glColor3d(.0, .0, .0);  // invert color
#endif
};

}

namespace {
    field fld = {};
}



void init();
void display();
void renderCircle(float r, int x, int y);
void putPiece_v(int x, int y);
void putPiece(int x, int y);
void pause();
void onclick(int button, int state, int x, int y);
void reshape(int width, int height);
void updateDisplay();
void result();
void animate();
void pauseMenu();
void displayTurn();



void init() {
    theme_color();
    fld.init();
    is_your_turn = bool{};
    is_paused = bool{};
    is_over = bool{};
}

void display() {
    // ウィンドウ表示内容のクリア
    glClear(GL_COLOR_BUFFER_BIT);

    updateDisplay();
}

void updateDisplay()
{
    pauseMenu();
    displayTurn();
    
    // field
    for (auto i = 0; i < 8; ++i) {
        for (auto j = 0; j < 8; ++j) {
            if (!((i+j)%2)) {
                cell_color_1();
            } else {
                cell_color_2();
            }
            glRectd(cell_hoffset+cell_width*i, cell_voffset+cell_height*j, cell_hoffset+cell_width*(i+1), cell_voffset+cell_height*(j+1));
        }
    }
    
    // piece
    for (auto i = 0; i < 8; ++i) {
        for (auto j = 0; j < 8; ++j) {
            if (auto color = fld[8*i+j]; color) {
                glColor3d(color, color, color);
                putPiece_v(i, j);
            } else if (!is_paused && fld(8*i+j)(is_your_turn)) {
                glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                glEnable(GL_BLEND);
                menu_color();
                putPiece_v(i, j);
                glDisable(GL_BLEND);
            }
        }
    }
    
    result();
    
    glutSwapBuffers();
    //glFlush();
}


void renderCircle(float r, int x, int y) {
    glBegin(GL_POLYGON); // ポリゴンの描画
    // 円を描画
    constexpr auto n = 200;
    for (auto i = 0; i < n; i++) {
        auto rate = static_cast<double>(i)/n;
        auto dx = r * cos(2.0 * M_PI * rate);
        auto dy = r * sin(2.0 * M_PI * rate);
        glVertex3f(x+dx, y+dy, .0);
    }
    glEnd();
    glFlush();
    
}

void putPiece_v(int x, int y) {
    x *= cell_width; x+= cell_width/2; x += cell_hoffset;
    y *= cell_height; y += cell_height/2; y += cell_voffset;
    
    renderCircle(piece_radius, x, y);
}

void putPiece(int x, int y) {
    if (is_over) return;
    
    bool able_to_put{};
    for (auto i = 0; i < 64; ++i)
        if (fld(i)(is_your_turn)) {
            able_to_put = true;
            break;
        }
    if (!able_to_put) {
        is_your_turn = !is_your_turn;
        updateDisplay();
        return;
    }
    
    if (x < 0) return;
    if (x > cell_width*8) return;
    if (y < 0) return;
    if (y > cell_height*8) return;
    
    x /= cell_width; y /= cell_height;
    auto n = 8*x+y;
    if (fld[n] || !fld(n)(is_your_turn)) return;
    
    fld.putPieceAt(is_your_turn, x, y);
    ++fld;
    
    //fld[n] = is_your_turn ? 1 : -1;
    cout << "(" << x << "," << y << ") : ";
    cout << str_color[fld[n] > 0] << endl;
    is_your_turn = !is_your_turn;
    
    updateDisplay();
    //glFlush();
}



void result()
{
    static std::string winner{};
    if (!is_over) {
        for (auto i = 0; i < 64; ++i)
            if (fld(i).black || fld(i).white)
                return;
        auto b = 0, w = 0;
        for (auto i = 0; i < 64; ++i) {
            switch (fld[i]) {
                case 1:
                    ++b; break;
                case -1:
                    ++w; break;
            }
        }
        
        is_over = true;
        if (w > b) {
            cout << "Player 1 (" << str_color[0] << ") win! " << w << " : " << b << endl;
            winner = "Winner : "; winner += str_color[0];
        } else if (b > w) {
            cout << "Player 2 (" << str_color[1] << ") win! " << b << " : " << w << endl;
            winner = "Winner : "; winner += str_color[1];
        } else {
            cout << "Draw." << endl;
            winner = "-- Draw --";
        }
    }
    
    chr_color();
    glRasterPos3i(600, 450, 0);
    for (const auto& i : winner) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, i);
    
    //glFlush();
    //glutSwapBuffers();
}

void onclick(int button, int state, int x, int y) {
    if (state == GLUT_UP) return;
    
    y = WINDOW_HEIGHT - y;
    

    // pause
    if (600<x && x<700 && 200<y && y<225) {
        if (is_over || is_paused) return;
        cout << "Pause.\n";
        is_paused = true;
        return;
    }
    
    // resume
    if (600<x && x<700 && 150<y && y<175) {
        if (is_over || !is_paused) return;
        cout << "Resume.\n";
        is_paused = false;
        return;
    }
    
    // restart
    if (600<x && x<700 && 100<y && y<125) {
        cout << "Restart.\n";
        init();
        //updateDisplay();
        return;
    }
    
    // quit
    if (600<x && x<650 && 50<y && y<75) {
        cout << "Quit.\n";
        exit(1);
    }

    
    
    x -= cell_hoffset;
    y -= cell_voffset;
    

    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (is_paused) break;
            putPiece(x, y); break;
        case GLUT_RIGHT_BUTTON:
            pause(); break;
    }
    
}


void reshape(int width, int height) {
    // OpenGLウィンドウの描画範囲を設定
    // 下記は描画範囲が[0, width] x [0, height]となるように設定している
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (double)width, 0.0, (double)height);
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
}

void animate()
{
    glutPostRedisplay();
}

void pause()
{
    if (is_over) exit(1);
    cout << (is_paused ? "Resume." : "Pause.") << endl;
    is_paused = !is_paused;
}

void displayTurn()
{
    std::string str_turn{str_color[is_your_turn]};
    str_turn += "'s turn";

    cell_color_2();
    glRectd(600,533,656,589);
    
    glColor3d(is_your_turn, is_your_turn, is_your_turn);
    renderCircle(25, 627, 560);
    
    chr_color();
    glRasterPos3i(660, 550, 0);
    for (const auto& i : str_turn) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, i);
}

void pauseMenu()
{
    std::string
        str_pause   = "Pause",
        str_restart = "Restarat",
        str_quit    = "Quit",
        str_resume  = "Resume";
    
    menu_color();
    glRasterPos3i(600, 200, 0);
    for (const auto& i : str_pause) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, i);
    glRasterPos3i(600, 150, 0);
    for (const auto& i : str_resume) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, i);
    glRasterPos3i(600, 100, 0);
    for (const auto& i : str_restart) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, i);
    glRasterPos3i(600,  50, 0);
    for (const auto& i : str_quit) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, i);
    

    glFlush();
}

int main(int argc, char **argv) {
    // GLUTの初期化
    glutInit(&argc, argv);
    // ダブルバッファの確保
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    // ウィンドウのサイズを設定
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // ウィンドウの作成 (引数はウィンドウのタイトル)
    glutCreateWindow("Reversi");
    // 描画に使う関数の登録
    glutDisplayFunc(display);
    
    glutMouseFunc(onclick);
    // ウィンドウのサイズ変更時に呼ばれる関数の登録
    glutReshapeFunc(reshape);
    
    glutIdleFunc(animate);
    // OpenGLの初期化処理  (これはコールバック関数ではないので直接呼び出す)
    init();
    // 描画ループの開始
    glutMainLoop();
}
