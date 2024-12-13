#include <glut.h>
#include <cmath>
#include <vector>


// Global variables
bool gameOver = false;
bool playerWon = false;
void displayEndGame();

// Function to draw a tree
void drawTree(float x, float y) {
    glColor3f(0.55f, 0.27f, 0.07f); // Brown color
    glBegin(GL_QUADS);
    glVertex2f(x - 0.05f, y);
    glVertex2f(x + 0.05f, y);
    glVertex2f(x + 0.05f, y + 0.3f);
    glVertex2f(x - 0.05f, y + 0.3f);
    glEnd();

    glColor3f(0.0f, 0.8f, 0.0f); // Green color
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y + 0.5f);
    glVertex2f(x - 0.2f, y + 0.3f);
    glVertex2f(x + 0.2f, y + 0.3f);
    glEnd();
}

// Function to draw a circle
void drawCircle(float x, float y, float radius, int segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * 3.14 * i / segments;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

// Function to draw an ellipse
void drawEllipse(float x, float y, float radiusX, float radiusY, int segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * 3.14 * i / segments;
        glVertex2f(x + cos(angle) * radiusX, y + sin(angle) * radiusY);
    }
    glEnd();
}

// Function to draw Timon
void drawTimon() {
    glColor3f(0.9f, 0.7f, 0.5f); // Light brown color
    glRectf(-0.7f, -0.6f, -0.5f, 0.1f);

    glColor3f(1.0f, 1.0f, 1.0f); // Eyes
    drawCircle(-0.65f, -0.05f, 0.03f, 20);
    drawCircle(-0.55f, -0.05f, 0.03f, 20);

    glColor3f(0.0f, 0.0f, 0.0f); // Pupils
    drawCircle(-0.65f, -0.05f, 0.015f, 20);
    drawCircle(-0.55f, -0.05f, 0.015f, 20);

    glColor3f(0.5f, 0.2f, 0.2f); // Nose
    drawCircle(-0.6f, -0.15f, 0.02f, 20);

    glColor3f(0.9f, 0.7f, 0.5f); // Arms
    drawEllipse(-0.75f, -0.2f, 0.05f, 0.15f, 30);
    drawEllipse(-0.45f, -0.2f, 0.05f, 0.15f, 30);

    glColor3f(0.9f, 0.7f, 0.5f); // Legs
    glRectf(-0.68f, -0.6f, -0.63f, -0.8f);
    glRectf(-0.57f, -0.6f, -0.52f, -0.8f);
}

// Function to draw Pumbaa
void drawPumbaa() {
    glColor3f(0.8f, 0.4f, 0.2f); // Brown body color
    drawEllipse(0.2f, -0.1f, 0.3f, 0.2f, 50);

    glColor3f(1.0f, 0.7f, 0.6f); // Snout color
    drawEllipse(0.2f, 0.175f, 0.1f, 0.06f, 50);

    glColor3f(0.0f, 0.0f, 0.0f); // Nostrils
    drawCircle(0.175f, 0.185f, 0.015f, 20);
    drawCircle(0.225f, 0.185f, 0.015f, 20);

    glColor3f(1.0f, 1.0f, 1.0f); // Eyes
    drawCircle(0.175f, 0.225f, 0.025f, 20);
    drawCircle(0.225f, 0.225f, 0.025f, 20);

    glColor3f(0.8f, 0.4f, 0.2f); // Legs
    drawEllipse(0.15f, -0.25f, 0.04f, 0.1f, 50);
    drawEllipse(0.25f, -0.25f, 0.04f, 0.1f, 50);
}

// Function to display the main scene
void display() {
    if (gameOver) {
        displayEndGame();
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glClearColor(0.5f, 0.8f, 0.92f, 1.0f);
    glColor3f(0.2f, 0.6f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.5f);
    glVertex2f(1.0f, -0.5f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    for (float x = -0.9f; x <= 0.9f; x += 0.4f) {
        drawTree(x, -0.5f);
    }

    drawTimon();
    drawPumbaa();

    glFlush();
}

// Function to display the end game screen
void displayEndGame() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);

    const char* message = playerWon ? "You Win!" : "You Lose!";
    glRasterPos2f(-0.2f, 0.0f);
    for (int i = 0; message[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);
    }

    glFlush();
}

void handleKeyboard(unsigned char key, int x, int y) {
    if (key == 'r' || key == 'R') {
        gameOver = false;
        playerWon = false;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Timon and Pumbaa Game");
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyboard);
    glutMainLoop();
    return 0;
}
