#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

//void truc();
void draw();
void reshape(int, int);
void keyboard(unsigned char key, int x, int y);
void rotateHouse();
void idle() {
    glutPostRedisplay();
}
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    //thiết lập ánh sáng

    
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(350, 50);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Modern House");
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    //glutIdleFunc(rotateHouse); // Hàm xoay liên tục
    glutKeyboardFunc(keyboard);
    init();
    
    //glutDisplayFunc(draw);
    glutIdleFunc(idle);
    
    glutMainLoop();
    return 0;
}

float angle = 0.0;
void drawBody();
void drawBody2(float yOffset);
void fillColorBody();
void drawRoof();
//void fillColorRoof();
void drawDoor();
void drawWindow();
//void VNflag();
void drawGrass();
void drawPath();
void hon_da();
void drawSwing();
float xPos = 0.0f, zPos = 0.0f; // Vị trí của ngôi nhà
bool continuousRotate = false;
float zoom = -12.0;
// Góc xoay và giá trị dịch chuyển
float yOffset = 0.0f;
bool isMovingUp = false;  // Biến kiểm soát trạng thái bắt đầu/dừng
bool isMovingDown = false;
void update();
void draw() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
   
    glTranslatef(0.0, 0.0, zoom);
    //glRotatef(90.0, 0.0, 3.0, 0.0); // Xoay 30 độ quanh trục Y
    gluLookAt(3.0, 3.0, 3.0,  // Vị trí camera
        0.0, 0.0, 0.0,  // Điểm nhìn
        0.0, 1.0, 0.0); // Vector lên
    
    // 
    //Xoay ngôi nhà
    glPushMatrix(); // Lưu trạng thái hiện tại

    glTranslatef(xPos, 0.0, -zPos);
    //glTranslatef(-1.0, 0.0, -5.0);
    glRotatef(-80.0, 0.0, 1.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0); // Xoay quanh trục Y


    //Vẽ thân ngôi nhà (hình hộp chữ nhật)
    drawBody();
    //Tô màu cho thân ngôi nhà
    fillColorBody();
    //
    glPushMatrix();
    glTranslatef(0.0f, yOffset, 0.0f);  // Dịch chuyển theo trục y
    
    //Vẽ mái nhà
    drawRoof();
    //vẽ ban công
    drawBody2(yOffset);

    //ban công, mái nhà di chuyển lên xuống
    if (isMovingUp || isMovingDown) {
        update();
    }
    
    //
    glPopMatrix();

    //Vẽ cửa chính
    drawDoor();
    
    
   
    if (continuousRotate) {
        rotateHouse(); // Gọi hàm xoay ngôi nhà
    }


    glPopMatrix(); // Khôi phục trạng thái ma trận

    drawGrass();
    // Vẽ một số cây
    
    glutSwapBuffers();
    glFlush();

    //rotateHouse(); // Gọi hàm xoay ngôi nhà
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Tính tỷ lệ khung hình mới
    float aspectRatio = (float)w / (float)h;

    // Áp dụng tỷ lệ khung hình vào hàm gluPerspective
    gluPerspective(60, aspectRatio, 2.0, 50.0);
    /*gluPerspective(60, 1, 2.0, 50.0);*///60:1 aspect ratio z-near=2  z-far=50.0
    //gluPerspective(60.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}


void drawBody() {
    //Mặt trước (vẽ viền màu đen)
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0); // Màu đen cho mặt trước
    glVertex3f(-3.0, 4.0, 5.0);
    glVertex3f(3.0, 4.0, 5.0);
    glVertex3f(3.0, 0.0, 5.0);
    glVertex3f(-3.0, 0.0, 5.0);
    glEnd();

    // Mặt sau (vẽ viền màu đen)
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0); // Màu đen cho mặt sau
    glVertex3f(-3.0, 0.0, 0.0);
    glVertex3f(3.0, 0.0, 0.0);
    glVertex3f(3.0, 4.0, 0.0);
    glVertex3f(-3.0, 4.0, 0.0);
    glEnd();

    // Mặt bên phải (vẽ viền màu đen)
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0); // Màu đen cho mặt bên phải
    glVertex3f(3.0, 0.0, 5.0);
    glVertex3f(3.0, 0.0, 0.0);
    glVertex3f(3.0, 4.0, 0.0);
    glVertex3f(3.0, 4.0, 5.0);
    glEnd();

    // Mặt bên trái (vẽ viền màu xanh)
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0); // Màu xanh cho mặt bên trái
    glVertex3f(-3.0, 0.0, 0.0);
    glVertex3f(-3.0, 4.0, 0.0);
    glVertex3f(-3.0, 4.0, 5.0);
    glVertex3f(-3.0, 0.0, 5.0);
    glEnd();

    

    // Mặt dưới (vẽ viền màu đen)
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0); // Màu đen cho mặt dưới
    glVertex3f(-3.0, 0.0, 0.0);
    glVertex3f(-3.0, 0.0, 5.0);
    glVertex3f(3.0, 0.0, 5.0);
    glVertex3f(3.0, 0.0, 0.0);
    glEnd();
    

    // Mặt trên (vẽ viền màu đen)
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0); // Màu đen cho mặt trên
    glVertex3f(-3.0, 4.0, 0.0);
    glVertex3f(3.0, 4.0, 0.0);
    glVertex3f(3.0, 4.0, 5.0);
    glVertex3f(-3.0, 4.0, 5.0);
    glEnd();
    
}

//ban công bên trên
void drawBody2(float yOffset) {
    float n = yOffset - 3.0;
    //Mặt trước (vẽ viền màu đen)
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5); // Màu đen cho mặt trước
    glVertex3f(-2.9, 4.0+n, 4.9);
    glVertex3f(2.9, 4.0+n, 4.9);
    glVertex3f(2.9, 0.0, 4.9);
    glVertex3f(-2.9, 0.0, 4.9);
    glEnd();

    // Mặt sau (vẽ viền màu đen)
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5); // Màu xám cho mặt sau
    glVertex3f(-2.9, 0.0, 0.1);
    glVertex3f(2.9, 0.0, 0.1);
    glVertex3f(2.9, 4.0+n, 0.1);
    glVertex3f(-2.9, 4.0+n, 0.1);
    glEnd();

    // Mặt bên phải (vẽ viền màu đen)
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5); // Màu xám cho mặt bên phải
    glVertex3f(2.9, 0.0, 4.9);
    glVertex3f(2.9, 0.0, 0.1);
    glVertex3f(2.9, 4.0+n, 0.1);
    glVertex3f(2.9, 4.0+n, 4.9);
    glEnd();

    // Mặt bên trái (vẽ viền màu xanh)
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5); // Màu xám cho mặt bên trái
    glVertex3f(-2.9, 0.0, 0.0);
    glVertex3f(-2.9, 4.0+n, 0.0);
    glVertex3f(-2.9, 4.0+n, 4.9);
    glVertex3f(-2.9, 0.0, 4.9);
    glEnd();

}


void fillColorBody() {
    /////
    //Mặt trước (đổ màu)
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.392, 0.545); //xanh than
    glVertex3f(-3.0, 4.0, 5.0);
    glVertex3f(3.0, 4.0, 5.0);
    glVertex3f(3.0, 0.0, 5.0);
    glVertex3f(-3.0, 0.0, 5.0);
    glEnd();

    // Mặt sau (đổ màu)
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.392, 0.545);
    glVertex3f(-3.0, 0.0, 0.0);
    glVertex3f(3.0, 0.0, 0.0);
    glVertex3f(3.0, 4.0, 0.0);
    glVertex3f(-3.0, 4.0, 0.0);
    glEnd();

    // Mặt bên phải (đổ màu)
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.392, 0.545);
    glVertex3f(3.0, 0.0, 5.0);
    glVertex3f(3.0, 0.0, 0.0);
    glVertex3f(3.0, 4.0, 0.0);
    glVertex3f(3.0, 4.0, 5.0);
    glEnd();

    

    // Mặt bên trái (đổ màu)
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.392, 0.545);
    glVertex3f(-3.0, 0.0, 0.0);
    glVertex3f(-3.0, 4.0, 0.0);
    glVertex3f(-3.0, 4.0, 5.0);
    glVertex3f(-3.0, 0.0, 5.0);
    glEnd();

    

    // Mặt dưới (đổ màu)
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(-3.0, 0.0, 0.0);
    glVertex3f(-3.0, 0.0, 5.0);
    glVertex3f(3.0, 0.0, 5.0);
    glVertex3f(3.0, 0.0, 0.0);
    glEnd();

    
    // Mặt trên (đổ màu)
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0); 
    glVertex3f(-3.0, 4.0, 0.0);
    glVertex3f(3.0, 4.0, 0.0);
    glVertex3f(3.0, 4.0, 5.0);
    glVertex3f(-3.0, 4.0, 5.0);
    glEnd();

    drawWindow();
}

void fillColorRoof(float yOffset);
void drawRoof() {
    //VẼ MÁI NHÀ
    //Vẽ mái nhà-bên phải (tam giác)
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(3.0, 4.0, 5.0);
    glVertex3f(3.0, 4.0, 0.0);
    glVertex3f(1.5, 6.0, 2.5);
    glEnd();

    
    //Vẽ mái nhà-bên trái (tam giác)
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-3.0, 4.0, 0.0);
    glVertex3f(-3.0, 4.0, 5.0);
    glVertex3f(-1.5, 6.0, 2.5);
    glEnd();

    

    //Vẽ mái nhà-mặt trước (tứ giác)
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-3.0, 4.0, 5.0);
    glVertex3f(3.0, 4.0, 5.0);
    glVertex3f(1.5, 6.0, 2.5);
    glVertex3f(-1.5, 6.0, 2.5);
    glEnd();


    //Vẽ mái nhà-mặt sau  (tứ giác)
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-3.0, 4.0, 0.0);
    glVertex3f(3.0, 4.0, 0.0);
    glVertex3f(1.5, 6.0, 2.5);
    glVertex3f(-1.5, 6.0, 2.5);
    glEnd();

    //fillColorRoof();
    fillColorRoof(yOffset);

   
}


//test
void fillColorRoof(float yOffset) {
    float heightAdjustment = yOffset * 0.1f; // Điều chỉnh chiều cao
    float stretchFactor = yOffset; // Kéo dài chiều ngang

    // Vẽ mái nhà-bên phải (đổ màu)
    glBegin(GL_TRIANGLES);
    glColor3f(0.8, 0.25, 0.25);
    glVertex3f(3.0, 4.0, 5.0);
    glVertex3f(3.0, 4.0, 0.0);
    glVertex3f(1.5, 6.0, 2.5);
    glEnd();

    // Vẽ mái nhà-bên trái (đổ màu)
    glBegin(GL_TRIANGLES);
    glColor3f(0.8, 0.25, 0.25);
    glVertex3f(-3.0, 4.0, 0.0);
    glVertex3f(-3.0, 4.0, 5.0);
    glVertex3f(-1.5, 6.0, 2.5);
    glEnd();

    // Vẽ mái nhà-mặt trước (đổ màu)
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-3.0, 4.0 + heightAdjustment, 5.0 + yOffset); // Nâng lên, dãn ra theo trục z
    glVertex3f(3.0, 4.0 + heightAdjustment, 5.0+ yOffset); // Nâng lên, dãn ra theo trục z
    glVertex3f(1.5, 6.0, 2.5); // Kéo dài
    glVertex3f(-1.5, 6.0, 2.5); // Kéo dài
    glEnd();

    // Vẽ mái nhà-mặt sau (đổ màu)
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.4, 0.0);
    glVertex3f(-3.0, 4.0 + heightAdjustment, 0.0-yOffset); // Nâng lên, dãn ra theo trục z
    glVertex3f(3.0, 4.0 + heightAdjustment, 0.0- yOffset); // Nâng lên, dãn ra theo trục z
    glVertex3f(1.5 , 6.0, 2.5); 
    glVertex3f(-1.5, 6.0, 2.5); 
    glEnd();
}



bool isDoorOpen = false; // Trạng thái của cửa (mở/đóng)


void drawDoor() {
    // Vẽ lỗ hổng (mặt tường màu trắng khi cửa mở)
    glPushMatrix();
    glTranslatef(0.001, 0.0, 0.0);

    // Vẽ viền đen cho lỗ hổng
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0); // Màu đen cho viền
    glVertex3f(3.0, 0.0, 3.0); // Cạnh cố định
    glVertex3f(3.0, 0.0, 2.0);
    glVertex3f(3.0, 2.0, 2.0);
    glVertex3f(3.0, 2.0, 3.0); // Cạnh cố định
    glEnd();

    // Vẽ lỗ hổng (mặt tường) màu trắng khi cửa mở
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0); // Màu trắng cho lỗ hổng
    glVertex3f(3.0, 0.0, 3.0); // Cạnh cố định
    glVertex3f(3.0, 0.0, 2.0);
    glVertex3f(3.0, 2.0, 2.0);
    glVertex3f(3.0, 2.0, 3.0); // Cạnh cố định
    glEnd();
    glPopMatrix();

    // Vẽ cửa (màu vàng) sẽ xoay theo trạng thái mở/đóng
    glPushMatrix();

    // Nếu cửa mở, xoay cửa 90 độ quanh cạnh cố định (trục Y)
    if (isDoorOpen) {
        glTranslatef(3.0, 0.0, 3.0); // Dịch chuyển đến cạnh cố định
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); // Xoay cửa 90 độ quanh trục Y
        glTranslatef(-3.0, 0.0, -3.0); // Dịch ngược lại để giữ đúng vị trí
    }

    // Vẽ viền đen của cửa
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0); // Màu đen cho viền cửa
    glVertex3f(3.01, 0.0, 3.0); // Cạnh cố định
    glVertex3f(3.01, 0.0, 2.0);
    glVertex3f(3.01, 2.0, 2.0);
    glVertex3f(3.01, 2.0, 3.0); // Cạnh cố định
    glEnd();

    // Vẽ mặt cửa màu nâu khi đóng
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.3, 0.0); // Màu nâu cho mặt cửa
    glVertex3f(3.01, 0.0, 3.0); // Cạnh cố định
    glVertex3f(3.01, 0.0, 2.0);
    glVertex3f(3.01, 2.0, 2.0);
    glVertex3f(3.01, 2.0, 3.0); // Cạnh cố định
    glEnd();
    
    glPopMatrix();
    
}



// Hàm cập nhật để thay đổi góc xoay và dịch chuyển đồng thời
void update() {
    // Kiểm tra xem chuyển động có được kích hoạt hay không
    if (isMovingUp) {

        // Tăng dịch chuyển (dịch chuyển lên đến một giới hạn nhất định)
        if (yOffset < 2.0f) {
            yOffset += 0.001f;
        }

        // Dừng lại khi đã dịch chuyển lên
        if (yOffset >= 2.0f) { 
            isMovingUp = false;  
            
        }
    }

    // Chuyển động xuống
    if (isMovingDown) {
        if (yOffset > 0.0f) {
            yOffset -= 0.001f;  // Dịch chuyển từ từ xuống
        }

        // Khi dịch chuyển hoàn tất, dừng lại và đặt lại giá trị ban đầu
        if (yOffset <= 0.0f) {
            isMovingDown = false;
            yOffset = 0.0f;
           
        }

        glutPostRedisplay();
    }

    // Cập nhật lại khung hình
    glutPostRedisplay();
    
}


void drawWindow() {
    //Cửa sổ ở mặt trước (đổ màu)
    glPushMatrix(); // Lưu trạng thái hiện tại của ma trận

    // Di chuyển đến vị trí cửa sổ
    glTranslatef(0.0, 2.0, 5.01); // Vị trí cửa sổ, z cao hơn một chút so với mặt trước

    //Vẽ viền đen (xy)
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0); // Màu đen cho viền
    glVertex3f(-0.6, 0.5, 0.0); // Đỉnh trái trên
    glVertex3f(0.6, 0.5, 0.0);  // Đỉnh phải trên
    glVertex3f(0.6, -0.5, 0.0);  // Đỉnh phải dưới
    glVertex3f(-0.6, -0.5, 0.0); // Đỉnh trái dưới
    glEnd();

    // Vẽ cửa sổ
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-0.6f, 0.5f, 0.0f); // Đỉnh trái trên
    glVertex3f(0.6f, 0.5f, 0.0f);  // Đỉnh phải trên
    glVertex3f(0.6f, -0.5f, 0.0f);  // Đỉnh phải dưới
    glVertex3f(-0.6f, -0.5f, 0.0f); // Đỉnh trái dưới
    glEnd();

    glPopMatrix(); // Khôi phục trạng thái ma trận

    glPushMatrix();
    glTranslatef(0.0, 2.0, -0.1);
    //Vẽ cửa sổ ở mặt sau (đổ màu)

    //Vẽ viền đen
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0); // Màu đen cho viền
    glVertex3f(-0.6, 0.5, 0.0); // Đỉnh trái trên
    glVertex3f(0.6, 0.5, 0.0);  // Đỉnh phải trên
    glVertex3f(0.6, -0.5, 0.0);  // Đỉnh phải dưới
    glVertex3f(-0.6, -0.5, 0.0); // Đỉnh trái dưới
    glEnd();

     //Vẽ cửa sổ (đổ màu)
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-0.6f, 0.5f, 0.0f); // Đỉnh trái trên
    glVertex3f(0.6f, 0.5f, 0.0f);  // Đỉnh phải trên
    glVertex3f(0.6f, -0.5f, 0.0f);  // Đỉnh phải dưới
    glVertex3f(-0.6f, -0.5f, 0.0f); // Đỉnh trái dưới
    glEnd();

    glPopMatrix();
}

void drawGrass() {
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.5f, 0.0f); // Màu xanh cho thảm cỏ
    glVertex3f(-10.0f, 0.0f, -10.0f); // Góc dưới trái
    glVertex3f(10.0f, 0.0f, -10.0f); // Góc dưới phải
    glVertex3f(10.0f, 0.0f, 10.0f); // Góc trên phải
    glVertex3f(-10.0f, 0.0f, 10.0f); // Góc trên trái
    glEnd();

}



//hàm điều khiển phím
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 't': // Nhấn 't' để phóng to
        zoom += 3.0;
        break;
    case 'n': // Nhấn 'n' để thu nhỏ
        zoom -= 3.0;
        break;
    case 'l': // Nhấn 'l' để xoay trái
        angle -= 10.0;
        break;
    case 'r': // Nhấn 'r' để xoay phải
        angle += 10.0;
        break;
    case 'o': // Nhấn phím 'o' để mở cửa
        isDoorOpen = true; // Mở cửa
       
        break;
    case 'c': // Nhấn phím 'c' để đóng cửa
        isDoorOpen = false; // Đóng cửa
       
        break;
    case 'b':  // Di chuyển lùi
        zPos += 0.5f;
        break;
    case 'f':  // Di chuyển tiến
        zPos -= 0.5f;
        break;
    case 'q':  // Di chuyển sang trái
        xPos -= 0.5f;
        break;
    case 'p':  // Di chuyển sang phải
        xPos += 0.5f;
        break;
    case 'x':  // xoay nhà liên tục
        continuousRotate = !continuousRotate;
        break;
    case 'hx':  // Hủy xoay nhà liên tục
        continuousRotate = false;
        break;
    case 's':  // bắt đầu
        isMovingUp = true;
        isMovingDown = false;
        break;
    case 'e':  //kết thúc
        isMovingUp = false;
        isMovingDown = true;
        break;
    
    case 27: // Nhấn ESC để thoát
        exit(0);
        break;
    }
    glutPostRedisplay(); // Cập nhật lại màn hình
}

void rotateHouse() {
    glutPostRedisplay(); // Yêu cầu vẽ lại cảnh
    angle += 0.015; // Tăng góc xoay mỗi lần gọi hàm
    if (angle > 360.0) {
        angle -= 360.0; // Đảm bảo góc không vượt quá 360 độ
    }
    
}