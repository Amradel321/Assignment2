
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

float SpongpopSpeed = 0.05f;  // Speed of pop
float PatrickSpeed = 0.05f;  // Speed of baset 2

float spongeBobX = -0.5f, spongeBobY = 0.0f;
float patrickX = 0.3f, patrickY = -0.1f;
float characterSpeed = 0.05f;

// Function to draw a circle
void drawCircle(float x, float y, float radius, int segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * 3.14159f * i / segments;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

// Function to draw a rectangle
void drawRectangle(float x1, float y1, float x2, float y2) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

// Function to draw SpongeBob
void drawSpongeBob() {
    // Body
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    drawRectangle(spongeBobX - 0.1f, spongeBobY - 0.4f, spongeBobX + 0.1f, spongeBobY + 0.2f);

    // Pants
    glColor3f(0.4f, 0.2f, 0.0f); // Brown
    drawRectangle(spongeBobX - 0.1f, spongeBobY - 0.4f, spongeBobX + 0.1f, spongeBobY - 0.2f);

    // Legs
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow for legs
    drawRectangle(spongeBobX - 0.08f, spongeBobY - 0.6f, spongeBobX - 0.04f, spongeBobY - 0.4f); // Left leg
    drawRectangle(spongeBobX + 0.04f, spongeBobY - 0.6f, spongeBobX + 0.08f, spongeBobY - 0.4f); // Right leg

    // Shoes
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    drawRectangle(spongeBobX - 0.08f, spongeBobY - 0.65f, spongeBobX - 0.04f, spongeBobY - 0.6f); // Left shoe
    drawRectangle(spongeBobX + 0.04f, spongeBobY - 0.65f, spongeBobX + 0.08f, spongeBobY - 0.6f); // Right shoe

    // Eyes
    glColor3f(1.0f, 1.0f, 1.0f); // White
    drawCircle(spongeBobX - 0.05f, spongeBobY + 0.1f, 0.05f, 30); // Left eye
    drawCircle(spongeBobX + 0.05f, spongeBobY + 0.1f, 0.05f, 30); // Right eye

    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    drawCircle(spongeBobX - 0.05f, spongeBobY + 0.1f, 0.025f, 30); // Left pupil
    drawCircle(spongeBobX + 0.05f, spongeBobY + 0.1f, 0.025f, 30); // Right pupil

    // Mouth
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glBegin(GL_LINE_STRIP);
    glVertex2f(spongeBobX - 0.07f, spongeBobY - 0.05f);
    glVertex2f(spongeBobX - 0.05f, spongeBobY - 0.1f);
    glVertex2f(spongeBobX + 0.05f, spongeBobY - 0.1f);
    glVertex2f(spongeBobX + 0.07f, spongeBobY - 0.05f);
    glEnd();
}

// Function to draw Patrick Star
void drawPatrick() {
    // Body
    glColor3f(1.0f, 0.5f, 0.5f); // Pink
    drawCircle(patrickX, patrickY, 0.3f, 50);

    // Shorts
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    drawRectangle(patrickX - 0.15f, patrickY - 0.3f, patrickX + 0.15f, patrickY);

    // Legs
    glColor3f(1.0f, 0.5f, 0.5f); // Pink
    drawRectangle(patrickX - 0.1f, patrickY - 0.5f, patrickX - 0.05f, patrickY - 0.3f); // Left leg
    drawRectangle(patrickX + 0.05f, patrickY - 0.5f, patrickX + 0.1f, patrickY - 0.3f); // Right leg

    // Feet
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    drawCircle(patrickX - 0.075f, patrickY - 0.55f, 0.05f, 20); // Left foot
    drawCircle(patrickX + 0.075f, patrickY - 0.55f, 0.05f, 20); // Right foot

    // Eyes
    glColor3f(1.0f, 1.0f, 1.0f); // White
    drawCircle(patrickX - 0.05f, patrickY + 0.2f, 0.05f, 30); // Left eye
    drawCircle(patrickX + 0.05f, patrickY + 0.2f, 0.05f, 30); // Right eye

    glColor3f(0.0f, 0.0f, 0.0f); // Black pupils
    drawCircle(patrickX - 0.05f, patrickY + 0.2f, 0.025f, 30); // Left pupil
    drawCircle(patrickX + 0.05f, patrickY + 0.2f, 0.025f, 30); // Right pupil

    // Mouth
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glBegin(GL_LINE_STRIP);
    glVertex2f(patrickX - 0.1f, patrickY - 0.1f);
    glVertex2f(patrickX, patrickY - 0.15f);
    glVertex2f(patrickX + 0.1f, patrickY - 0.1f);
    glEnd();
}

// Function to move SpongeBob
void moveSpongeBob(int key) {
    if (key == GLUT_KEY_UP) spongeBobY += characterSpeed;
    else if (key == GLUT_KEY_DOWN) spongeBobY -= characterSpeed;
    else if (key == GLUT_KEY_LEFT) spongeBobX -= characterSpeed;
    else if (key == GLUT_KEY_RIGHT) spongeBobX += characterSpeed;
}

// Function to move Patrick
void movePatrick(unsigned char key, int x, int y) {
    if (key == 'w') patrickY += characterSpeed;
    else if (key == 's') patrickY -= characterSpeed;
    else if (key == 'a') patrickX -= characterSpeed;
    else if (key == 'd') patrickX += characterSpeed;
}

// Function to handle key release
void keyRelease(unsigned char key, int x, int y) {
    // Speed control for Zombie 1 and Zombie 2
    if (key == '+') {
        SpongpopSpeed += 0.01f;
        PatrickSpeed += 0.01f;
    }
    if (key == '-') {
        SpongpopSpeed = max(0.01f, SpongpopSpeed - 0.01f);
        PatrickSpeed = max(0.01f, PatrickSpeed - 0.01f);
    }
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

    // Draw SpongeBob
    drawSpongeBob();
    // Draw Patrick
    drawPatrick();

    glFlush();
}

// Special key input function
void specialKeys(int key, int x, int y) {
    moveSpongeBob(key);
    glutPostRedisplay();
}

// Normal key input function
void normalKeys(unsigned char key, int x, int y) {
    movePatrick(key, x, y);
    glutPostRedisplay();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("SpongeBob and Patrick Game");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(normalKeys);
    glutKeyboardUpFunc(keyRelease);

    glutMainLoop();
    return 0;
}

