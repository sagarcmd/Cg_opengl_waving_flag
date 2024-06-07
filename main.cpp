#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

// Define initial positions and other constants
float flagWave = 0.0f;

// Define colors
GLfloat green[] = { 0.0, 0.5, 0.0 };
GLfloat red[] = { 0.75, 0.0, 0.0 };
GLfloat grey[] = { 0.5, 0.5, 0.5 };

// Function to draw a rectangle
void drawRectangle(float x, float y, float width, float height, GLfloat color[3]) {
    glColor3fv(color);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

// Function to draw a circle
void drawCircle(float cx, float cy, float radius, int segments, GLfloat color[3]) {
    glColor3fv(color);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Function to draw the flag of Bangladesh with a waving effect
void drawFlag() {
    float waveAmplitude = 0.02f;
    float waveFrequency = 10.0f;
    glColor3fv(green);
    glBegin(GL_QUADS);
    for (int i = 0; i < 100; i++) {
        float x = 0.0f + i * 0.004f;
        float y = waveAmplitude * sin(waveFrequency * x + flagWave);
        glVertex2f(x, y);
        glVertex2f(x + 0.004f, y);
        glVertex2f(x + 0.004f, y + 0.2f);
        glVertex2f(x, y + 0.2f);
    }
    glEnd();
    drawCircle(0.2f, 0.1f, 0.05f, 50, red);
}

// Function to draw the flag pole
void drawPole() {
    drawRectangle(-0.01f, -0.5f, 0.02f, 1.0f, grey);
}

// Function to draw the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the flag pole
    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, 0.0f);
    drawPole();
    glPopMatrix();

    // Draw the flag
    glPushMatrix();
    glTranslatef(-0.5f, 0.3f, 0.0f);
    drawFlag();
    glPopMatrix();

    glFlush();
}

// Timer function for animation
void timer(int) {
    flagWave += 0.1f;
    if (flagWave > 2 * M_PI) {
        flagWave -= 2 * M_PI;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);  // 60 FPS
}

// Initialize OpenGL settings
void init() {
    glClearColor(0.5, 0.8, 0.9, 1.0); // Background color
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Waving Bangladeshi Flag with Pole");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
