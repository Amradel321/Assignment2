//Characters for timon and pumbaa and the end game 

//eslam Khalil 202200486
// Amr Adel 202200382
#include <GLUT/glut.h>
#include <cmath>
#include <vector>
using namespace std;
#include <iostream>




// Global variable to track game state
bool gameOver = false;
bool playerWon = false;

// Function to draw a circle
void drawCircle(float x, float y, float radius, int segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * 3.14159f * i / segments;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

// Function to draw an ellipse
void drawEllipse(float x, float y, float radiusX, float radiusY, int segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * 3.14159f * i / segments;
        glVertex2f(x + cos(angle) * radiusX, y + sin(angle) * radiusY);
    }
    glEnd();
}

// Function to draw Timon
void drawTimon() {
    glColor3f(0.9f, 0.7f, 0.5f); // Light brown color
    glRectf(-0.7f, -0.6f, -0.5f, 0.1f); // Rectangle for the body

    glColor3f(0.9f, 0.8f, 0.6f); // Head inside the body
    // drawCircle(-0.6f, -0.1f, 0.15f, 50); // Circle for the head (moved to be inside the body)
    
    glColor3f(1.0f, 1.0f, 1.0f); // Eyes
    drawCircle(-0.65f, -0.05f, 0.03f, 20); // Left eye
    drawCircle(-0.55f, -0.05f, 0.03f, 20);  // Right eye

    glColor3f(0.0f, 0.0f, 0.0f); // Pupils
    drawCircle(-0.65f, -0.05f, 0.015f, 20); // Left pupil
    drawCircle(-0.55f, -0.05f, 0.015f, 20);  // Right pupil

    glColor3f(0.5f, 0.2f, 0.2f); // Nose
    drawCircle(-0.6f, -0.15f, 0.02f, 20); // Small circle for nose

    glColor3f(0.9f, 0.7f, 0.5f); // Match body color for arms
    drawEllipse(-0.75f, -0.2f, 0.05f, 0.15f, 30); // Left arm
    drawEllipse(-0.45f, -0.2f, 0.05f, 0.15f, 30);  // Right arm

    glColor3f(0.5f, 0.3f, 0.2f); // Darker brown for hands
    drawCircle(-0.75f, -0.35f, 0.03f, 20); // Left hand
    drawCircle(-0.45f, -0.35f, 0.03f, 20);  // Right hand

    glColor3f(0.9f, 0.7f, 0.5f); // Legs
    glRectf(-0.68f, -0.6f, -0.63f, -0.8f); // Left leg
    glRectf(-0.57f, -0.6f, -0.52f, -0.8f);  // Right leg
}

// Function to draw Pumbaa
void drawPumbaa() {
    glColor3f(0.8f, 0.4f, 0.2f); // Brown body color
    drawEllipse(0.2f, -0.1f, 0.3f, 0.2f, 50); // Body ellipse

    glColor3f(0.8f, 0.4f, 0.2f); // Head color
    drawEllipse(0.2f, 0.125f, 0.175f, 0.125f, 50); // Head ellipse

    glColor3f(1.0f, 0.7f, 0.6f); // Snout color
    drawEllipse(0.2f, 0.175f, 0.1f, 0.06f, 50); // Snout

    glColor3f(0.0f, 0.0f, 0.0f); // Nostrils
    drawCircle(0.175f, 0.185f, 0.015f, 20); // Left nostril
    drawCircle(0.225f, 0.185f, 0.015f, 20); // Right nostril

    glColor3f(1.0f, 1.0f, 1.0f); // White tusks
    glBegin(GL_TRIANGLES); // Left tusk
    glVertex2f(0.125f, 0.15f);
    glVertex2f(0.14f, 0.2f);
    glVertex2f(0.15f, 0.15f);
    glEnd();

    glBegin(GL_TRIANGLES); // Right tusk
    glVertex2f(0.275f, 0.15f);
    glVertex2f(0.26f, 0.2f);
    glVertex2f(0.25f, 0.15f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); // White eyes
    drawCircle(0.175f, 0.225f, 0.025f, 20); // Left eye
    drawCircle(0.225f, 0.225f, 0.025f, 20); // Right eye

    glColor3f(0.0f, 0.0f, 0.0f); // Black pupils
    drawCircle(0.175f, 0.225f, 0.01f, 20); // Left pupil
    drawCircle(0.225f, 0.225f, 0.01f, 20); // Right pupil

    glColor3f(0.8f, 0.4f, 0.2f); // Legs
    drawEllipse(0.15f, -0.25f, 0.04f, 0.1f, 50); // Left front leg
    drawEllipse(0.25f, -0.25f, 0.04f, 0.1f, 50); // Right front leg
    drawEllipse(0.15f, -0.35f, 0.04f, 0.1f, 50); // Left back leg
    drawEllipse(0.25f, -0.35f, 0.04f, 0.1f, 50); // Right back leg

    glBegin(GL_LINES); // Tail
    glColor3f(0.8f, 0.4f, 0.2f);
    glVertex2f(0.325f, -0.1f);
    glVertex2f(0.35f, 0.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Black tuft at tail
    drawCircle(0.35f, 0.0f, 0.015f, 20); // Tuft
}

// Function to display the end game screen
void displayEndGame() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for text

    if (playerWon) {
        // Display "You Win" message
        glRasterPos2f(-0.2f, 0.0f);
        const char* message = "You Win!";
        for (int i = 0; message[i] != '\0'; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);
        }
    } else {
        // Display "You Lose" message
        glRasterPos2f(-0.2f, 0.0f);
        const char* message = "You Lose!";
        for (int i = 0; message[i] != '\0'; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);
        }
    }

    glFlush();
}

// Function to update game state (you can call this function whenever a character dies)
void updateGameState(bool win) {
    gameOver = true;
    playerWon = win;
}

// Display function
void display() {
    if (gameOver) {
        displayEndGame();
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    // Draw Pumbaa
    drawPumbaa();
    // Draw Timon
    drawTimon();

    glFlush();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pumbaa - Accurate Design");

    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Light blue background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
