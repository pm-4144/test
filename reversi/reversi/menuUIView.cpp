//
//  menuUIView.cpp
//  reversi
//
//  Created by Pino Marianne on 2023/06/08.
//


#include "menuUIView.hpp"
#include "common.h"

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

#include <iostream>
#include <cmath>
#include <string>

namespace {
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
}

void displayTurn()
{
    std::string
        str_white = "White turn",
        str_black = "Black turn";

    glColor3d(.9, .6, .9);
    glRectd(600,532,656,588);
    
    glColor3d(is_your_turn, is_your_turn, is_your_turn);
    renderCircle(25, 628, 560);
    
    glColor3d(0, 0, 0);
    glRasterPos3i(660, 550, 0);
    for (const auto& i : (is_your_turn ? str_black : str_white)) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, i);
}

void pauseMenu()
{
    std::string
        str_pause   = "Pause",
        str_restart = "Restarat",
        str_quit    = "Quit",
        str_resume  = "Resume";
    
    glColor3d(.0, .0, 1.);
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



