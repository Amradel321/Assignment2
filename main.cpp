#include <glut.h>
#include <cstdio>


// Initial positions of characters
float timonX = 0.3f, timonY = -0.7f;
float bombaX = 0.5f, bombaY = -0.7f;
float enemyX = -0.5f, enemyY = -0.7f;

// Variables to track lives
int timonLives = 3;
int bombaLives = 3;
int enemyLives = 3;
// Collision detection function
bool checkCollision(float objX, float objY, float projX, float projY, float size) {
    return projX >= objX - size && projX <= objX + size &&
        projY >= objY - size && projY <= objY + size;
}

// Maximum number of projectiles that can be active at once
const int MAX_PROJECTILES = 10;
struct Projectile {
    float x, y, directionX, directionY;
    bool isActive;
};

// Arrays to hold projectiles for Timon, Bomba, and Enemy
Projectile timonProjectiles[MAX_PROJECTILES];
Projectile bombaProjectiles[MAX_PROJECTILES];
Projectile enemyProjectiles[MAX_PROJECTILES];

// Draw trees for the forest
void drawTree(float x, float y) {
    glColor3f(0.4f, 0.2f, 0.0f); // Brown color for tree trunk
    glBegin(GL_QUADS);
    glVertex2f(x - 0.05f, y);
    glVertex2f(x + 0.05f, y);
    glVertex2f(x + 0.05f, y + 0.2f);
    glVertex2f(x - 0.05f, y + 0.2f);
    glEnd();

    glColor3f(0.0f, 0.6f, 0.0f); // Green color for tree leaves
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.15f, y + 0.2f);
    glVertex2f(x + 0.15f, y + 0.2f);
    glVertex2f(x, y + 0.4f);
    glEnd();
}

// Draw the forest background with trees
void drawForest() {
    glColor3f(0.2f, 0.6f, 0.2f); // Green for grass
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.8f);
    glVertex2f(-1.0f, -0.8f);
    glEnd();

    drawTree(-0.8f, -0.7f);
    drawTree(-0.5f, -0.6f);
    drawTree(0.2f, -0.5f);
    drawTree(0.6f, -0.6f);
    drawTree(0.9f, -0.7f);
}

// Draw Timon character
void drawTimon() {
    glColor3f(1.0f, 0.0f, 0.0f); // Red for body
    glBegin(GL_QUADS);
    glVertex2f(timonX - 0.1f, timonY + 0.25f);
    glVertex2f(timonX + 0.1f, timonY + 0.25f);
    glVertex2f(timonX + 0.1f, timonY + 0.35f);
    glVertex2f(timonX - 0.1f, timonY + 0.35f);
    glEnd();

    glColor3f(0.8f, 0.0f, 0.0f); // Dark red for arms
    glBegin(GL_QUADS);
    glVertex2f(timonX - 0.05f, timonY + 0.05f);
    glVertex2f(timonX + 0.05f, timonY + 0.05f);
    glVertex2f(timonX + 0.05f, timonY + 0.25f);
    glVertex2f(timonX - 0.05f, timonY + 0.25f);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f); // Brown for legs
    glBegin(GL_LINES);
    glVertex2f(timonX - 0.1f, timonY + 0.15f);
    glVertex2f(timonX - 0.2f, timonY + 0.05f);
    glVertex2f(timonX + 0.1f, timonY + 0.15f);
    glVertex2f(timonX + 0.2f, timonY + 0.05f);
    glEnd();
}

// Draw Bomba character
void drawBomba() {
    glColor3f(0.0f, 0.0f, 1.0f); // Blue for body
    glBegin(GL_QUADS);
    glVertex2f(bombaX - 0.1f, bombaY + 0.25f);
    glVertex2f(bombaX + 0.1f, bombaY + 0.25f);
    glVertex2f(bombaX + 0.1f, bombaY + 0.35f);
    glVertex2f(bombaX - 0.1f, bombaY + 0.35f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.8f); // Dark blue for arms
    glBegin(GL_QUADS);
    glVertex2f(bombaX - 0.05f, bombaY + 0.05f);
    glVertex2f(bombaX + 0.05f, bombaY + 0.05f);
    glVertex2f(bombaX + 0.05f, bombaY + 0.25f);
    glVertex2f(bombaX - 0.05f, bombaY + 0.25f);
    glEnd();
}

// Draw Enemy character
void drawEnemy() {
    glColor3f(0.0f, 1.0f, 0.0f); // Green for body
    glBegin(GL_QUADS);
    glVertex2f(enemyX - 0.1f, enemyY + 0.25f);
    glVertex2f(enemyX + 0.1f, enemyY + 0.25f);
    glVertex2f(enemyX + 0.1f, enemyY + 0.35f);
    glVertex2f(enemyX - 0.1f, enemyY + 0.35f);
    glEnd();

    glColor3f(0.0f, 0.6f, 0.0f); // Dark green for arms
    glBegin(GL_QUADS);
    glVertex2f(enemyX - 0.05f, enemyY + 0.05f);
    glVertex2f(enemyX + 0.05f, enemyY + 0.05f);
    glVertex2f(enemyX + 0.05f, enemyY + 0.25f);
    glVertex2f(enemyX - 0.05f, enemyY + 0.25f);
    glEnd();
}

// Handle special key press for Timon
void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) timonX -= 0.05f;
    if (key == GLUT_KEY_RIGHT) timonX += 0.05f;
    if (key == GLUT_KEY_UP) timonY += 0.05f;
    if (key == GLUT_KEY_DOWN) timonY -= 0.05f;

    glutPostRedisplay();
}

// Handle regular key press for Bomba, Timon, and Enemy
void regularKeys(unsigned char key, int x, int y) {
    // Bomba (WASD keys)
    if (key == 'a' || key == 'A') bombaX -= 0.05f;
    if (key == 'd' || key == 'D') bombaX += 0.05f;
    if (key == 'w' || key == 'W') bombaY += 0.05f;
    if (key == 's' || key == 'S') bombaY -= 0.05f;

    // Enemy (QERT keys)
    if (key == 'q' || key == 'Q') enemyX -= 0.05f;
    if (key == 'e' || key == 'E') enemyX += 0.05f;
    if (key == 'r' || key == 'R') enemyY += 0.05f;
    if (key == 't' || key == 'T') enemyY -= 0.05f;


    // Fire projectiles for enemy
    if (key == 'f' || key == 'F') {
        for (int i = 0; i < MAX_PROJECTILES; i++) {
            if (!enemyProjectiles[i].isActive) {
                // Fire projectile to the right, starting from the enemy's position
                enemyProjectiles[i] = { enemyX, enemyY, 0.05f, 0.0f, true }; // Right direction, no vertical movement
                break;
            }
        }
    }


    // Timon (Spacebar to fire)
    if (key == ' ') {
        for (int i = 0; i < MAX_PROJECTILES; i++) {
            if (!timonProjectiles[i].isActive) {
                // Fire projectile from Timon towards the enemy
                timonProjectiles[i].x = timonX;
                timonProjectiles[i].y = timonY + 0.1f;

                // Calculate direction
                float deltaX = enemyX - timonX;
                float deltaY = enemyY - timonY;
                timonProjectiles[i].directionX = deltaX * 0.01f; // Scaling for speed
                timonProjectiles[i].directionY = deltaY * 0.01f;

                timonProjectiles[i].isActive = true;
                break;
            }
        }
    }

    // Bomba (Enter to fire)
    if (key == 13) {  // Enter key
        for (int i = 0; i < MAX_PROJECTILES; i++) {
            if (!bombaProjectiles[i].isActive) {
                // Fire projectile from Bomba towards the enemy
                bombaProjectiles[i].x = bombaX;
                bombaProjectiles[i].y = bombaY + 0.1f;

                // Calculate direction
                float deltaX = enemyX - bombaX;
                float deltaY = enemyY - bombaY;
                bombaProjectiles[i].directionX = deltaX * 0.01f; // Scaling for speed
                bombaProjectiles[i].directionY = deltaY * 0.01f;

                bombaProjectiles[i].isActive = true;
                break;
            }
        }
    }

    glutPostRedisplay();
}
// Update projectiles and check collisions
void updateProjectiles() {
    // Timon projectiles update
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (timonProjectiles[i].isActive) {
            timonProjectiles[i].x += timonProjectiles[i].directionX;
            timonProjectiles[i].y += timonProjectiles[i].directionY;

            // Check collision with enemy
            if (checkCollision(enemyX, enemyY, timonProjectiles[i].x, timonProjectiles[i].y, 0.1f)) {
                timonProjectiles[i].isActive = false;
                enemyLives--;
                if (enemyLives <= 0) {
                    enemyX = -0.5f; // Reset position or handle death logic
                    enemyLives = 3; // Reset lives for simplicity
                }
            }

            // Deactivate projectile if out of bounds
            if (timonProjectiles[i].x > 1.0f || timonProjectiles[i].x < -1.0f ||
                timonProjectiles[i].y > 1.0f || timonProjectiles[i].y < -1.0f) {
                timonProjectiles[i].isActive = false;
            }
        }
    }


    // Bomba projectiles update
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (bombaProjectiles[i].isActive) {
            bombaProjectiles[i].x += bombaProjectiles[i].directionX;
            bombaProjectiles[i].y += bombaProjectiles[i].directionY;

            // Check collision with enemy
            if (checkCollision(enemyX, enemyY, bombaProjectiles[i].x, bombaProjectiles[i].y, 0.1f)) {
                bombaProjectiles[i].isActive = false;
                enemyLives--;
                if (enemyLives <= 0) {
                    enemyX = -0.5f; // Reset position or handle death logic
                    enemyLives = 3; // Reset lives for simplicity
                }
            }

            // Deactivate projectile if out of bounds
            if (bombaProjectiles[i].x > 1.0f || bombaProjectiles[i].x < -1.0f ||
                bombaProjectiles[i].y > 1.0f || bombaProjectiles[i].y < -1.0f) {
                bombaProjectiles[i].isActive = false;
            }
        }
    }


    // Enemy projectiles update
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (enemyProjectiles[i].isActive) {
            enemyProjectiles[i].x += enemyProjectiles[i].directionX;
            enemyProjectiles[i].y += enemyProjectiles[i].directionY;

            // Check collision with Timon
            if (checkCollision(timonX, timonY, enemyProjectiles[i].x, enemyProjectiles[i].y, 0.1f)) {
                enemyProjectiles[i].isActive = false;
                timonLives--;
                if (timonLives <= 0) {
                    timonX = 0.3f; // Reset position or handle death logic
                    timonLives = 3; // Reset lives for simplicity
                }
            }

            // Check collision with Bomba
            if (checkCollision(bombaX, bombaY, enemyProjectiles[i].x, enemyProjectiles[i].y, 0.1f)) {
                enemyProjectiles[i].isActive = false;
                bombaLives--;
                if (bombaLives <= 0) {
                    bombaX = 0.5f; // Reset position or handle death logic
                    bombaLives = 3; // Reset lives for simplicity
                }
            }

            // Deactivate projectile if out of bounds
            if (enemyProjectiles[i].x > 1.0f || enemyProjectiles[i].x < -1.0f ||
                enemyProjectiles[i].y > 1.0f || enemyProjectiles[i].y < -1.0f) {
                enemyProjectiles[i].isActive = false;
            }
        }
    }
}

// Draw projectiles
void drawProjectiles() {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (timonProjectiles[i].isActive) {
            glColor3f(1.0f, 0.0f, 0.0f); // Red for Timon projectiles
            glBegin(GL_QUADS);
            glVertex2f(timonProjectiles[i].x - 0.02f, timonProjectiles[i].y - 0.02f);
            glVertex2f(timonProjectiles[i].x + 0.02f, timonProjectiles[i].y - 0.02f);
            glVertex2f(timonProjectiles[i].x + 0.02f, timonProjectiles[i].y + 0.02f);
            glVertex2f(timonProjectiles[i].x - 0.02f, timonProjectiles[i].y + 0.02f);
            glEnd();
        }

        if (bombaProjectiles[i].isActive) {
            glColor3f(0.0f, 0.0f, 1.0f); // Blue for Bomba projectiles
            glBegin(GL_QUADS);
            glVertex2f(bombaProjectiles[i].x - 0.02f, bombaProjectiles[i].y - 0.02f);
            glVertex2f(bombaProjectiles[i].x + 0.02f, bombaProjectiles[i].y - 0.02f);
            glVertex2f(bombaProjectiles[i].x + 0.02f, bombaProjectiles[i].y + 0.02f);
            glVertex2f(bombaProjectiles[i].x - 0.02f, bombaProjectiles[i].y + 0.02f);
            glEnd();
        }

        if (enemyProjectiles[i].isActive) {
            glColor3f(1.0f, 1.0f, 0.0f); // Yellow for enemy projectiles
            glBegin(GL_QUADS);
            glVertex2f(enemyProjectiles[i].x - 0.02f, enemyProjectiles[i].y - 0.02f);
            glVertex2f(enemyProjectiles[i].x + 0.02f, enemyProjectiles[i].y - 0.02f);
            glVertex2f(enemyProjectiles[i].x + 0.02f, enemyProjectiles[i].y + 0.02f);
            glVertex2f(enemyProjectiles[i].x - 0.02f, enemyProjectiles[i].y + 0.02f);
            glEnd();
        }
    }
}
// Display function to show lives
void displayLives() {
    char buffer[50];
    glColor3f(1.0f, 1.0f, 1.0f); // White color for text

    // Display Timon lives
    sprintf_s(buffer, "Timon Lives: %d", timonLives);
    glRasterPos2f(-0.9f, 0.9f);
    for (char* c = buffer; *c != '\0'; c++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    // Display Bomba lives
    sprintf_s(buffer, "Bomba Lives: %d", bombaLives);
    glRasterPos2f(-0.9f, 0.8f);
    for (char* c = buffer; *c != '\0'; c++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    // Display Enemy lives
    sprintf_s(buffer, "Enemy Lives: %d", enemyLives);
    glRasterPos2f(-0.9f, 0.7f);
    for (char* c = buffer; *c != '\0'; c++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw the forest and characters
    drawForest();
    drawTimon();
    drawBomba();
    drawEnemy();
    drawProjectiles();
    // Display lives
    displayLives();

    glutSwapBuffers();
}

// Idle function
void idle() {
    updateProjectiles();
    glutPostRedisplay();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Timon and Bomba Firing Projectiles");

    glClearColor(0.0f, 0.5f, 1.0f, 1.0f); // Sky blue background
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Orthographic projection

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(regularKeys);

    glutMainLoop();
    return 0;
}
