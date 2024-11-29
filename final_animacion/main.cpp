#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;
float camaraX = 10;
float camaraY = 30;
float camaraZ =70;

float angulo = 2.5;
float radio = 30;
float centroY = 10;
void iniciarVentana(int ancho, int alto)
{
    glViewport(0,0,ancho, alto);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0, (float)ancho/(float)alto,1,200);
}
void inicializarLuces()
{
    // Ajustar la luz ambiental para que sea más oscura
    GLfloat luz_ambiente[] = { 0.1, 0.1, 0.1, 1 };  // Reducir la luz ambiental
    GLfloat luz_difusa[] = { 0.3, 0.3, 0.3, 1 };    // Reducir la luz difusa
    GLfloat luz_especular[] = { 0.3, 0.3, 0.3, 1 };  // Mantener la luz especular igual
    float posicionLuz0[] = { 0, 70, 60, 1 };          // Posición de la luz

    glEnable(GL_LIGHTING);         // Habilitar iluminación
    glEnable(GL_LIGHT0);           // Habilitar la luz 0
    glEnable(GL_DEPTH_TEST);       // Habilitar el test de profundidad
    glEnable(GL_COLOR_MATERIAL);   // Habilitar material de color

    // Configurar la luz
    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);  // Luz ambiental más oscura
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);    // Luz difusa más oscura
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular); // Luz especular sin cambios
    glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz0);  // Posición de la luz
}



void ruedaDeCarro(float posX, float posY, float posZ) {
    glPushMatrix();

    // Mover la rueda a la posición deseada
    glTranslated(posX, posY, posZ);

    // Rotar la rueda 90 grados sobre el eje Y
    glRotated(90, 0.0, 1.0, 0.0);

        // Escalar la rueda (ajustable)
    glScaled(1, 1.0, 1.5); // Escalar: modificar para ajustar radio y grosor

    // Dibujar el cuerpo de la rueda (cilindro)
    glColor3ub(40, 40, 40); // Color gris oscuro para el cuerpo
    GLUquadric* cuerpo = gluNewQuadric();
    gluCylinder(cuerpo, 7.0, 7.0, 4.0, 50, 10); // Cilindro con radio 7 y altura 4

    // Dibujar el borde inferior (disco)
    glPushMatrix();
    glColor3ub(20, 20, 20); // Color negro para los bordes
    gluDisk(cuerpo, 0, 7.0, 50, 1); // Disco inferior
    glPopMatrix();

    // Dibujar el borde superior (disco)
    glPushMatrix();
    glTranslated(0.0, 0.0, 4.0); // Mover al extremo superior del cilindro
    gluDisk(cuerpo, 0, 7.0, 50, 1); // Disco superior
    glPopMatrix();

    // Liberar memoria
    gluDeleteQuadric(cuerpo);

    glPopMatrix();
}




void platilloVolador(float posX, float posY, float posZ) {
    glPushMatrix();

    // Mover el platillo volador utilizando los parámetros posX, posY y posZ
    glTranslated(posX, posY, posZ);  // Mover el platillo

    // Parte superior del platillo (cúpula grande y alargada)
    glPushMatrix();
    glColor4f(0.0, 1.0, 1.0, 0.5);  // Color cian translúcido para la cúpula
    glEnable(GL_BLEND);             // Habilitar transparencia
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTranslated(0, 10, 0);         // Mover hacia arriba para alinear con el cuerpo
    glScaled(5, 5, 5);              // Escalar para hacerla más alta y ancha
    glutSolidSphere(5, 50, 50);     // Esfera base para la cúpula
    glDisable(GL_BLEND);            // Deshabilitar transparencia
    glPopMatrix();

    // Parte inferior del platillo (cuerpo)
    glPushMatrix();
    glColor3ub(80, 80, 80);         // Color gris oscuro
    glScaled(10, 3, 9);             // Escalar para dar forma alargada
    int slices = 50;                // Suavidad de la esfera
    int stacks = 25;                // Número de divisiones verticales

    for (int i = 0; i <= stacks; ++i) {
        float theta1 = (i * M_PI) / stacks;        // Ángulo inicial
        float theta2 = ((i + 1) * M_PI) / stacks;  // Ángulo siguiente

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float phi = (j * 2 * M_PI) / slices; // Ángulo alrededor del eje Y

            // Primer vértice
            float x1 = 5.0 * sin(theta1) * cos(phi);
            float y1 = 5.0 * cos(theta1);
            float z1 = 5.0 * sin(theta1) * sin(phi);

            // Segundo vértice
            float x2 = 5.0 * sin(theta2) * cos(phi);
            float y2 = 5.0 * cos(theta2);
            float z2 = 5.0 * sin(theta2) * sin(phi);

            // Dibujar los vértices si están en la mitad superior
            if (y1 >= 0.0f) glVertex3f(x1, y1, z1);
            if (y2 >= 0.0f) glVertex3f(x2, y2, z2);
        }
        glEnd();
    }
    glPopMatrix();

    // Agregar la tapa en la parte inferior
    glPushMatrix();
    glTranslated(0, 1.5, 0);            // Ajustar posición para que encaje con la parte inferior
    glRotated(90, 1.0, 0.0, 0.0);      // Rotar 90 grados en el eje X para alinear correctamente
    glColor3ub(50, 50, 50);             // Color gris oscuro



    GLUquadric* quadric = gluNewQuadric();
    gluDisk(quadric, 0, 47, 50, 1);     // Reducir el radio del disco a 30 para hacerlo menos ancho
    gluDeleteQuadric(quadric);

    glPopMatrix();

}





void piso()
{
    glPushMatrix();
    glColor3ub(79, 255, 8 );
    glTranslated(0,-1,0);
    glScaled(300,1,200);
    glutSolidCube(1);
    glPopMatrix();
}

void dibujarEjes()
{
    glPushMatrix();
    glLineWidth(2);
    glBegin(GL_LINES);
//Eje X
    glColor3ub(255,0,0);
    glVertex3d(0,0,0);
    glVertex3d(50,0,0);
//Eje Y
    glColor3ub(0,255,0);
    glVertex3d(0,0,0);
    glVertex3d(0,50,0);
//Eje Z
    glColor3ub(0,0,255);
    glVertex3d(0,0,0);
    glVertex3d(0,0,50);
    glEnd();
    glPopMatrix();
}

void pies(float posX){
    glPushMatrix();
        glTranslated(posX,0,1.5);
        glScaled(1.2,1,3);
        glutSolidSphere(1.5,50,50);
    glPopMatrix();
}

void tobillo(float posX){
    glPushMatrix();
        glTranslated(posX,0,0);
        glRotated(-90,1,0,0);
        glScaled(0.2,0.2,1.5);
        gluCylinder(gluNewQuadric(),4,4,4,50,50);
    glPopMatrix();
}

void pierna(float posX){
    glPushMatrix();
        glTranslated(posX,2.2,0);
        glRotated(-90,1,0,0);
        glScaled(0.5,0.3,4.5);
        gluCylinder(gluNewQuadric(),4,4,4,50,50);
    glPopMatrix();
}

void cuerpo(){
    glPushMatrix();
        glTranslated(0,20,0);
        glScaled(1.3,4.5,1);
        glRotated(-90,1,0,0);
        gluCylinder(gluNewQuadric(),4,4,4,50,50);
    glPopMatrix();
}

void hombros(float posX,float posY,float rotX){
    glPushMatrix();
        glTranslated(posX,posY,0);
        glRotated(90,0,1,0);
        glRotated(rotX,1,0,0);
        gluCylinder(gluNewQuadric(),1.5,1.5,6,50,50);
    glPopMatrix();

}


void brazo(float posX,float posY, float rotX ){
    glPushMatrix();
        glTranslated(posX,posY,0);
        glRotated(90,0,1,0);
        glRotated(rotX,1,0,0);
        gluCylinder(gluNewQuadric(),1.2,1.2,10,50,50);
    glPopMatrix();

}

void mano(float posX,float posY){
    glPushMatrix();
        glTranslated(posX,posY,0);
        glScaled(0.8,1.1,0.65);
        glutSolidSphere(2,50,50);
    glPopMatrix();
}

void cuerpoLinea(){
    glPushMatrix();
        glTranslated(0,6.8,6.6);
        glRotated(-16,1,0,0);
        glScaled(0.5,7,1);
        glutSolidCube(1);
    glPopMatrix();
}
void cuello(){
    glPushMatrix();
        glTranslated(0,10,0);
        glRotated(-90,1,0,0);
        glScaled(0.6,0.6,0.6);
        glutSolidTorus(1,10,50,50);
    glPopMatrix();
}


void cabeza(){
    glPushMatrix();
        glTranslated(0,16,0);
        glutSolidSphere(7.7,50,50);
    glPopMatrix();
}

void pelo(){
    glPushMatrix();
        glTranslated(0,19,-3);
        glutSolidSphere(8.5,50,50);
    glPopMatrix();
}

void nariz(){
    glPushMatrix();
        glTranslated(0,15,8);
        glutSolidSphere(1,50,50);
    glPopMatrix();
}

void boca() {
glPushMatrix();
    glTranslated(0, 13, 7.5);  // Posición de la boca, más abajo de la nariz
    glColor3ub(0, 0, 0);  // Color negro para la boca
    glBegin(GL_LINE_STRIP);  // Usamos líneas para dibujar el arco de la boca
        // Generar un arco de sonrisa usando vértices
        glVertex3f(-2.5, 0, 0);    // Parte izquierda de la boca
        glVertex3f(-2, -0.8, 0);   // Curvatura inferior izquierda
        glVertex3f(-1, -1.2, 0);   // Centro de la curva (parte más baja)
        glVertex3f(1, -1.2, 0);    // Centro de la curva (parte más baja)
        glVertex3f(2, -0.8, 0);    // Curvatura inferior derecha
        glVertex3f(2.5, 0, 0);     // Parte derecha de la boca
    glEnd();
glPopMatrix();


}

void ojos() {
    // Ojo izquierdo
    glPushMatrix();
        glTranslated(-3, 17, 7);  // Posición del ojo izquierdo
        glColor3ub(255, 255, 255);  // Color blanco
        glutSolidSphere(2, 50, 50);  // Ojo blanco (más grande)

        glColor3ub(0, 0, 0);  // Color de la pupila
        glTranslated(0, 0, 1.2);  // Posición de la pupila
        glutSolidSphere(1, 50, 50);  // Pupila (más grande)
    glPopMatrix();

    // Ojo derecho
    glPushMatrix();
        glTranslated(3, 17, 7);  // Posición del ojo derecho
        glColor3ub(255, 255, 255);  // Color blanco
        glutSolidSphere(2, 50, 50);  // Ojo blanco (más grande)

        glColor3ub(0, 0, 0);  // Color de la pupila
        glTranslated(0, 0, 1.2);  // Posición de la pupila
        glutSolidSphere(1, 50, 50);  // Pupila (más grande)
    glPopMatrix();
}

void cabeza_completa(double posX, double posY, double posZ){
    glPushMatrix();

    // Trasladar todo el conjunto a la posición proporcionada
    glTranslated(posX, posY, posZ);
    glColor3ub(255,204,153); //piel
    cabeza();
    glColor3ub(76,51,25);
    pelo();
    glColor3ub(255,204,153); //piel
    nariz();
    boca();
    ojos();

    glColor3ub(255,204,153); //piel
    nariz();
    glPopMatrix();
}

void morty(){



    glColor3ub(255,204,153);
    mano(6.6,23);
    mano(-6.6,23);

    glColor3ub(255, 255, 0);  // (amarillo)
    hombros(3,38,50);
    hombros(-3,38,130);

    glColor3ub(255,204,153); //piel
    brazo(6.5,34,90);
    brazo(-6.5,34,90);

    glColor3ub(255, 255, 0);  // (amarillo)
    cuerpo();


    glColor3ub(0, 0, 255);  // Color de las piernas (azul)
    pierna(3);
    pierna(-3);

    glColor3ub(223, 223, 223);  // Color de los zapatos (blancos)
    tobillo(3);
    tobillo(-3);

    glColor3ub(223, 223, 223);  // Color de los zapatos (blancos)
    pies(3);
    pies(-3);

    cabeza_completa(0,28,1);


}


void dibujarCasa(double posX, double posY, double posZ, double ancho, double alto, double profundidad) {
    glPushMatrix();

    // Trasladar toda la casa a la posición deseada
    glTranslated(posX, posY, posZ);

    // Dibujar el garage (base de la casa)
    glPushMatrix();
        glScaled(ancho, alto, profundidad); // Escalar para ajustar tamaño
        glColor3ub(254, 176, 30 );         // Color gris para la pared
        glutSolidCube(1.0);                // Cubo escalado como base
    glPopMatrix();

        // Dibujar la puerta (base de la casa)
    glPushMatrix();
        glScaled(45, 40, 65); // Escalar para ajustar tamaño
        glColor3ub(249, 242, 111  );         // Color gris para la pared
        glutSolidCube(1.0);                // Cubo escalado como base
    glPopMatrix();


            // Dibujar pared (base de la casa)
        glPushMatrix();
        glColor3ub(255, 0, 0);
            glTranslated(-60, 20.0, -100);
            glScaled(50, 60, 1.0);
             // Escalar para ajustar tamaño
                    // Color gris para la pared
            glutSolidCube(1.0);                // Cubo escalado como base
        glPopMatrix();




    // Dibujar el techo (triángulo)
    glPushMatrix();
        glTranslated(0.0, 30, 30); // Mover el techo encima de la pared
        glScaled(ancho, alto, 1.0);             // Escalar el triángulo para que sea proporcional
        glColor3ub(255, 0, 0);                 // Color rojo para el techo
        glBegin(GL_TRIANGLES);
            glVertex3f(-0.5f, 0.0f, 0.0f); // Vértice izquierdo del triángulo
            glVertex3f(0.5f, 0.0f, 0.0f);  // Vértice derecho del triángulo
            glVertex3f(0.0f, 0.5f, 0.0f);  // Vértice superior del triángulo
        glEnd();
    glPopMatrix();

    glPopMatrix();
}

void mostrarValoresCamara()
{
    cout << "gluLookAt(" << camaraX << ", " << camaraY << ", " << camaraZ << ", 0, " << centroY << ", 0, 0, 1, 0);" << endl;
}


void configurarCamara()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10, 15.5, 70, 0, 10, 0, 0, 1, 0);
    mostrarValoresCamara();
}

void dibujar()
{
    inicializarLuces();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    // Usamos gluLookAt para posicionar la cámara y hacerla mirar al centro
    //gluLookAt(camaraX, camaraY, camaraZ, 0, 0, 0, 0, 1, 0);
    configurarCamara();

    //gluLookAt(camaraX, camaraY, camaraZ,0,0,0,0,1,0);
    gluLookAt(radio * cos(angulo), camaraY, radio * sin(angulo),0,centroY,0,0,1,0);

    //piso();
    dibujarEjes();


   //morty();
    // Llamar a la función para dibujar el platillo volador
    // Aquí puedes moverlo a cualquier posición ajustando los valores
    platilloVolador(0, 25, 0);  // Mueve el platillo a la izquierda
    //ruedaDeCarro(0.0f, 4.0f, 0.0f);


    // Dibujar una casa en la posición (0, 0, -5) con dimensiones 3x4x2
   //dibujarCasa(-40, 20.0, -100, 80, 60, 64);

       ruedaDeCarro(-28.0f, -2.0f, 14.0f);
       ruedaDeCarro(28.0f, -2.0, 14.0f);
       ruedaDeCarro(28.0f, 4.0f, -28.0f);
       ruedaDeCarro(-28.0f, 4.0f, -28.0f);


    glutSwapBuffers();
}



void teclado_especial(int tecla, int x, int y)
{
    cout<<tecla<<endl;
    switch(tecla)
    {
    case 101:
        camaraY += 0.5;
        break;
    case 103:
        camaraY -= 0.5;
        break;
    case 100:
        angulo += 0.05;
        break;
    case 102:
        angulo -= 0.05;
        break;
    case 105:
        radio += 1;
        break;
    case 104:
        radio -= 1;
        break;
    }
}

void manejarTeclasNormales(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '+':
        radio -= 1.0; // Acercar la cámara
        if (radio < 1.0) radio = 1.0;
        camaraX = radio * cos(angulo);
        camaraZ = radio * sin(angulo);
        break;
    case '-':
        radio += 1.0; // Alejar la cámara
        camaraX = radio * cos(angulo);
        camaraZ = radio * sin(angulo);
        break;
    }
    glutPostRedisplay();
}



void timer(int t)
{
    glutPostRedisplay();
    glutTimerFunc(20,timer,0);
}
int main(int argc, char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1400,900);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Ventana de dibujo");
    glutReshapeFunc(iniciarVentana);
    glutDisplayFunc(dibujar);
    glutSpecialFunc(teclado_especial);
        glutKeyboardFunc(manejarTeclasNormales);
    glutTimerFunc(0,timer,0);
    glutMainLoop();
    return 0;
}
