
#include<stdlib.h>
#include <math.h>
#include <time.h>
#include<strings.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#ifndef M_PI
#endif
#define TORSO_HEIGHT 5.0
#define TORSO_RADIUS 1.3
#define HEAD_HEIGHT 1.7
#define HEAD_RADIUS 1.3
#define UPPER_ARM_HEIGHT 3.0
#define LOWER_ARM_HEIGHT 2.0
#define UPPER_ARM_RADIUS 0.65
#define LOWER_ARM_RADIUS 0.5
#define LOWER_LEG_HEIGHT 3.0
#define UPPER_LEG_HEIGHT 3.0
#define UPPER_LEG_RADIUS 0.65
#define LOWER_LEG_RADIUS 0.5
#define SHOULDER_RADIUS 0.85
#define JOINT_RADIUS 0.85
int stackIncompCount = 0;
int writingCount = 0;
int stackCompCount = 0;
char s[50]="",s1[50]="",s2[50]="",s3[50]="";
/*
 *Adjust the time(seconds)
 *according to the time taken by the 1st two windows.
 */
int previousWindowTime = 24;
int light_flag = 0;
typedef float point[3];
GLfloat seconds;
float rot_z = 0.0,abc1 = 0.0,abc2 = 0.0;
GLuint texture[4]; //the array for our texture
static GLfloat theta[13] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,
180.0,0.0,180.0,0.0,0.0,0.0}; /* initial joint angles */
GLfloat theta_min[11];
GLfloat theta_max[11];
GLfloat theta_freq[11];
GLfloat knees_y, knees_z;
GLfloat mat_x, mat_y, mat_z;
GLfloat mat_specular[]={0.0, 0.0, 1.0, 1.0};
GLfloat mat_diffuse[]={0.0, 0.0, 1.0, 1.0};
GLfloat mat_ambient[]={0.0, 0.0, 1.0, 1.0};
GLfloat mat_shininess={100.0};
static GLint angle = 3;
int flag_dance = 0;
float sec = 0.5;
GLUquadricObj *t, *gl, *h, *lua, *lla, *rua, *rla, *lll, *rll, *rul, *lul;
GLUquadricObj *rs, *ls, *rleg, *lleg, *elbow;
GLUquadricObj *disk,*tbl;
double size=1.0;
int i;
char ch[4] = "";

void torso()
{
glPushMatrix();
glRotatef(-90.0, 1.0, 0.0, 0.0);                                    //rotate by90 to get to og position
gluCylinder(t,TORSO_RADIUS, TORSO_RADIUS*1.5, TORSO_HEIGHT,10,10);  //(*obj, base, top, height, slices, stacks)
glPopMatrix();
}
void head()
{
glPushMatrix();
glTranslatef(0.0, 0.5*HEAD_HEIGHT,0.0);                             //get to og position
glScalef(HEAD_RADIUS, HEAD_HEIGHT, HEAD_RADIUS);                    //make bigger to adjust to glas_bot size
gluSphere(h,1.0,10,10);                             
glPopMatrix();
}
void glass_bot()
{
glPushMatrix();
glTranslatef(0.0, 0.5*HEAD_HEIGHT,0.075);                           //get to og position on head
glRotatef(-90.0, 1.0, 0.0, 0.0);                                  //rotate to fit horizontally on head
gluCylinder(gl,HEAD_RADIUS, HEAD_RADIUS, HEAD_HEIGHT/2,10,10);
glPopMatrix();
}
void shoulder_joints()
{
glPushMatrix();
glScalef(SHOULDER_RADIUS, SHOULDER_RADIUS, SHOULDER_RADIUS);                //make smaller to become perfect size
gluSphere(h,1.0,10,10);
glPopMatrix();
}
void elbow_joints()
{
glPushMatrix();
glScalef(SHOULDER_RADIUS/1.2, SHOULDER_RADIUS/1.2, SHOULDER_RADIUS/1.2);    //make smaller to become perfect size
gluSphere(h,1.0,10,10);
glPopMatrix();
}
void palms()
{
glPushMatrix();
glScalef(SHOULDER_RADIUS/1.3, SHOULDER_RADIUS/1.3, SHOULDER_RADIUS/1.3);   //make smaller to become perfect size
gluSphere(h,1.0,10,10);
glPopMatrix();
}
void leg_joints()
{
glPushMatrix();
glScalef(JOINT_RADIUS, JOINT_RADIUS, JOINT_RADIUS);                         //make smaller to become perfect size
gluSphere(h,1.0,10,10);
glPopMatrix();
}
void knee_joints()
{
glPushMatrix();
glScalef(JOINT_RADIUS, JOINT_RADIUS, JOINT_RADIUS);                         //make smaller to become perfect size
gluSphere(h,1.0,10,10);
glPopMatrix();
}
void torso_disk()
{
glPushMatrix();
glScalef(1.5*TORSO_RADIUS, 0.1, 1.5*TORSO_RADIUS);
gluSphere(h,1.0,10,10);
glPopMatrix();
}
void left_upper_arm()
{
glPushMatrix();
gluCylinder(lua,UPPER_ARM_RADIUS*1.2, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
glPopMatrix();
}
void left_lower_arm()
{
glPushMatrix();
gluCylinder(lla,LOWER_ARM_RADIUS*1.1, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
glPopMatrix();
}
void right_upper_arm()
{
glPushMatrix();
glRotatef(-90.0, 1.0, 0.0, 0.0);                                                    //rotate by 90 to get to og position
gluCylinder(rua,UPPER_ARM_RADIUS*1.2, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
glPopMatrix();
}
void right_lower_arm()
{
glPushMatrix();
glRotatef(-90.0, 1.0, 0.0, 0.0);                                                    //rotate by 90 to get to og position
gluCylinder(rla,LOWER_ARM_RADIUS*1.1, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
glPopMatrix();
}
void left_upper_leg()
{
glPushMatrix();
glRotatef(-120.0, 1.0, 0.0, 0.0);                                                   //rotate by 90 to get to og position
gluCylinder(lul,UPPER_LEG_RADIUS*1.2, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
glPopMatrix();
}
void left_lower_leg()
{
glPushMatrix();
glTranslatef(0.0,-0.25,-UPPER_LEG_HEIGHT/2);                                        //get to og position
glRotatef(-70.0, 1.0, 0.0, 0.0);                                                    //rotate by 90 to get to og position
gluCylinder(lll,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS*1.5, LOWER_LEG_HEIGHT,10,10);
glPopMatrix();
}
void right_upper_leg()
{
glPushMatrix();
glRotatef(-120.0, 1.0, 0.0, 0.0);                                                   //rotate by 90 to get to og position
gluCylinder(rul,UPPER_LEG_RADIUS*1.2, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
glPopMatrix();
}
void right_lower_leg()
{
glPushMatrix();
glTranslatef(0.0,-0.25,-UPPER_LEG_HEIGHT/2);                                        //get to og position
glRotatef(-70.0, 1.0, 0.0, 0.0);                                                    //rotate by 90 to get to og position
gluCylinder(rll,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS*1.5, LOWER_LEG_HEIGHT,10,10);
glPopMatrix();
}
void table()
{
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    
    glVertex3f(-10.0f, 1.5f, 10.0f);                //table front
    glVertex3f(-10.0f, 0.5f, 10.0f);
    glVertex3f(7.0f, 0.5f, 10.0f);
    glVertex3f(7.0f, 1.5f, 10.0f);
    
    glVertex3f(7.0f, 1.5f, 10.0f);                 //table rhs
    glVertex3f(8.5f, 2.0f, 3.0f);
    glVertex3f(8.5f, 1.0f, 3.0f);
    glVertex3f(7.0f, 0.5f, 10.0f);

    glVertex3f(-10.0f, 1.5f, 10.0f);                //table top
    glVertex3f(-8.5f, 2.0f, 3.0f);
    glVertex3f(8.5f, 2.0f, 3.0f);
    glVertex3f(7.0f, 1.5f, 10.0f);
    
    glEnd();
    glFlush();
}

void stackIncomplete()
{
    if(stackIncompCount>0){
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);

        glVertex3f(-9.5f, 1.9+(0.3*(stackIncompCount-1)), 10.0f);                //front
        glVertex3f(-9.5f, 1.5f, 10.0f);
        glVertex3f(-6.5f, 1.5f, 10.0f);
        glVertex3f(-6.5f, 1.9+(0.3*(stackIncompCount-1)), 10.0f);

        glVertex3f(-6.5f, 1.9+(0.3*(stackIncompCount-1)), 10.0f);                 //rhs
        glVertex3f(-5.0f, 1.95+(0.3*(stackIncompCount-1)), 3.0f);
        glVertex3f(-5.0f, 1.55f, 3.0f);
        glVertex3f(-6.5f, 1.5f, 10.0f);

        glVertex3f(-9.5f, 1.9+(0.3*(stackIncompCount-1)), 10.0f);                //top
        glVertex3f(-8.0f, 1.95+(0.3*(stackIncompCount-1)), 3.0f);
        glVertex3f(-5.0f, 1.75+(0.3*(stackIncompCount-1)), 3.0f);
        glVertex3f(-6.5f, 1.7+(0.3*(stackIncompCount-1)), 10.0f);

        glEnd();
        glFlush();
    }
}

void writing()
{
    if(writingCount==1)
    {
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);

        glVertex3f(-1.0f, 1.9f, 10.0f);                //top
        glVertex3f(-3.0f, 2.0f, 10.0f);
        glVertex3f(-1.5f, 2.1f, 10.0f);
        glVertex3f(0.5f, 2.0f, 10.0f);

        glVertex3f(-3.0f, 1.55f, 6.5f);                 //lhs
        glVertex3f(-3.0f, 2.0f, 6.5f);
        glVertex3f(-1.0f, 1.9f, 10.0f);
        glVertex3f(-1.0f, 1.5f, 10.0f);

        glVertex3f(-1.0f, 1.55f, 10.0f);                //rhs
        glVertex3f(-1.0f, 2.0f, 10.0f);
        glVertex3f(1.5f, 1.9f, 6.5f);
        glVertex3f(1.5f, 1.5f, 6.5f);

        glEnd();
        glFlush();
    }
}

void stackComplete()
{
    if(stackCompCount>0){
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);

        glVertex3f(3.5f, 1.9+(0.1*(stackCompCount-1)), 10.0f);                //front
        glVertex3f(3.5f, 1.5f, 10.0f);
        glVertex3f(6.5f, 1.5f, 10.0f);
        glVertex3f(6.5f, 1.9+(0.1*(stackCompCount-1)), 10.0f);

        glVertex3f(6.5f, 1.9+(0.1*(stackCompCount-1)), 10.0f);                 //rhs
        glVertex3f(8.0f, 1.95+(0.1*(stackCompCount-1)), 3.0f);
        glVertex3f(8.0f, 1.55f, 3.0f);
        glVertex3f(6.5f, 1.5f, 10.0f);

        glVertex3f(3.5f, 1.9+(0.1*(stackCompCount-1)), 10.0f);                //top
        glVertex3f(5.0f, 1.95+(0.1*(stackCompCount-1)), 3.0f);
        glVertex3f(8.0f, 1.95+(0.1*(stackCompCount-1)), 3.0f);
        glVertex3f(6.5f, 1.9+(0.1*(stackCompCount-1)), 10.0f);

        glEnd();
        glFlush();
    }
}

void Write(char *string,float x,float y)
{
    glRasterPos3f(x,y,0); 
            
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
    
    glFlush();
}

void display(void)
{
GLfloat rot_x=0.0, rot_y=0.0;
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glLoadIdentity();

    glEnable(GL_LIGHT3);
    if(flag_dance<11)
    {
        Write(s,-12,9);
        Write(s1,-10,8);
        Write(s2,-10,7);
    }
    if(flag_dance>=11)
            Write("Moral:",-0.5,7);
    if(flag_dance>=12)
        Write("Engineers aren't Robots",-2.5,5);
    if(flag_dance>=13)
        Write("Because...",-1,3);
    if(flag_dance>=14)
        Write("Because...",-1,1);
    if(flag_dance>=15)
        Write("Because...",-1,-1);
    if(flag_dance>=16)
        Write("Robots can't do what Engineers do..!!",-4,-3);
    
    glDisable(GL_LIGHT3);
    
    glEnable(GL_LIGHT4);
    if(flag_dance==5)
    {
        Write("Z",1,5);
        Write("z",1.5,5.5);
        Write("z",2,6);
    }
    glDisable(GL_LIGHT4);
    
    glEnable(GL_LIGHT5);
        Write(s3,-3,8);
    glDisable(GL_LIGHT5);
        
    glEnable(GL_LIGHT1);
    glScalef(sec, sec, sec);
    glFlush();    
    
    if(flag_dance<5)
    {       
        glPushMatrix();
        glRotatef(theta[12],1,0,0);
        torso();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0, TORSO_HEIGHT+0.5*HEAD_HEIGHT, 0.0);   //setting location of head
        glTranslatef(0.0, -0.5*HEAD_HEIGHT, 0.0);               //put head slight inside torso
        head();
        glass_bot();
        glPopMatrix();

        if(flag_dance<4)
        {
            rot_x = 1;
            rot_y = 0;
        }
        else if(flag_dance==4)
        {
            rot_x = 1;
            rot_y = 0;
            rot_z = 0;
        }
        
        //right arm

        glPushMatrix();
            glTranslatef(-(TORSO_RADIUS+UPPER_ARM_RADIUS), 0.9*TORSO_HEIGHT, 0.0);    //get to og location
            glRotatef(theta[3], rot_x, rot_y, rot_z);                                  

        left_upper_arm();
        glTranslatef(0.0, 0.0, UPPER_ARM_HEIGHT);                               //get to og location
        elbow_joints();
        if(flag_dance==4)
        {
            glRotatef(theta[4], 1, 0, 1);                   
            glRotatef(abc1,0,1,0);
        }    
        else if(flag_dance<4)
            glRotatef(theta[4], rot_x, rot_y, rot_z);                       
        left_lower_arm();
        glTranslatef(0.0, 0.0,LOWER_ARM_HEIGHT);                                //set to og location
        palms(); //left hand
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0, TORSO_HEIGHT, 0.0);                                   //get to og location (below head)
            glPushMatrix();
            torso_disk();  
            glPopMatrix();
        glPopMatrix();
        //shoulder_joints
        glPushMatrix();
        glTranslatef(1.5*TORSO_RADIUS, 0.9*TORSO_HEIGHT, 0.0);                //get to og location
        shoulder_joints();
        glTranslatef(-3.0*TORSO_RADIUS, 0.0, 0.0);                              //get to og location
        shoulder_joints();
        glPopMatrix();
        //leg_joints
        glPushMatrix();
        glTranslatef(1.1*TORSO_RADIUS, 0.0, 0.0);                               //get to og location (left upper leg ball)
        leg_joints();
        glTranslatef(-2.2*TORSO_RADIUS, 0.0, 0.0);                              //right leg upper ball (display)
        shoulder_joints();
        glPopMatrix();
        //left arm
        glPushMatrix();
        glTranslatef(TORSO_RADIUS+UPPER_ARM_RADIUS, 0.9*TORSO_HEIGHT, 0.0);     //display right arm full
        if(flag_dance==0||flag_dance==1||flag_dance==3)
        {
            glRotatef(theta[5], rot_x, rot_y, 0.0);                                  
        }
        else if(flag_dance==2)
        {
            glRotatef(theta[5], rot_x, rot_y, 1.0);                                  
        }
        else if(flag_dance==4)
        {
            glRotatef(theta[5], rot_x, rot_y, rot_z);
        }
        right_upper_arm();
        glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);                               //display elbow joins and right lower arm
        elbow_joints();
        if(flag_dance==0||flag_dance==1)
        {
            glRotatef(theta[6], 1.0, 0.0, 0.0);                                  
        }
        if(flag_dance==4)
        {
            glRotatef(theta[6], 0, 0, 1);                          
            glRotatef(abc2,0,1,0);
        }
        right_lower_arm();
        glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);                               //display right hand palm ball
        palms(); //left hand
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-(TORSO_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);             //left leg upper ball to og location
        glRotatef(theta[7], 1.0, 0.0, 0.0);                                  
        left_upper_leg();                                                      
        glTranslatef(0.0, UPPER_LEG_HEIGHT, -1.5);                              //display left knee+lower leg in position
        knee_joints();
        glTranslatef(0.0, 0.0, 1.5);                                                //display left lower leg in position
        glRotatef(theta[8], 1.0, 0.0, 0.0);                                    
        left_lower_leg();
        glPopMatrix();
        glPushMatrix();
        glTranslatef((TORSO_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);              //display right leg in position   
        glRotatef(theta[9], 1.0, 0.0, 0.0);                                     
        right_upper_leg();
        glTranslatef(0.0, UPPER_LEG_HEIGHT, -1.5);                              //display right knee+lower leg in position
        knee_joints();
        glTranslatef(0.0, 0.0, 1.5);                                            //display right lower leg in position
        glRotatef(theta[10], 1.0, 0.0, 0.0);                                   
        right_lower_leg();
        glPopMatrix();
        //glDisable(GL_LIGHT1);
    }
    else if(flag_dance==5)
    {
        glPushMatrix();
            glRotatef(theta[12],1,0,0);
            torso();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, TORSO_HEIGHT+0.5*HEAD_HEIGHT, 0.0);   //setting location of head
            glTranslatef(0.0, -0.5*HEAD_HEIGHT, 0.0);               //put head slight inside torso
            glRotatef(theta[1],1,0,0);
            glTranslatef(0,0.5,7);
            head();
            glass_bot();
        glPopMatrix();

        rot_x = 1;
        rot_y = 0;
        rot_z = 1;
        
        //left arm
        glPushMatrix();
            glPushMatrix();
                glTranslatef(-(TORSO_RADIUS+UPPER_ARM_RADIUS), 0.9*TORSO_HEIGHT, 0.0);    //get to og location
                glTranslatef(0,-1.8,6);
                glScalef(0.8,2,1);
                glRotatef(theta[3], rot_x, rot_y, rot_z);              
                left_upper_arm();
            glPopMatrix();
            glTranslatef(-1.75,2,6);
            glTranslatef(0.0, 0.0, UPPER_ARM_HEIGHT);                               //get to og location
            elbow_joints();
            glRotatef(theta[4], 1, 0, 1);                
            glRotatef(abc1,0,1,0);
            left_lower_arm();
            glTranslatef(0.0, 0.0,LOWER_ARM_HEIGHT);                                //set to og location
            palms(); //left hand
        glPopMatrix();
        
        //torso disk
        glPushMatrix();
            glTranslatef(0.0, TORSO_HEIGHT, 0.0);                                   //get to og location (below head)
            glPushMatrix();
                glTranslatef(0,-1.5,6);
                glRotatef(theta[13],1,0,0);   
                torso_disk();  
            glPopMatrix();
        glPopMatrix();
        
        //shoulder_joints
        glPushMatrix();
            glTranslatef(1.5*TORSO_RADIUS, 0.9*TORSO_HEIGHT, 0.0);                //get to og location
            glTranslatef(0,-1,5);
            shoulder_joints();                                                   //right shoulder
            glTranslatef(-3.0*TORSO_RADIUS, 0.0, 0.0);                              //get to og location
            shoulder_joints();                                                   //left shoulder
        glPopMatrix();
        
        //leg_joints
        glPushMatrix();
            glTranslatef(1.1*TORSO_RADIUS, 0.0, 0.0);                               //get to og location (left upper leg ball)
            leg_joints();
            glTranslatef(-2.2*TORSO_RADIUS, 0.0, 0.0);                              //right leg upper ball (display)
            shoulder_joints();
        glPopMatrix();
        
        //right arm
        glPushMatrix();
            glPushMatrix();
                glTranslatef(TORSO_RADIUS+UPPER_ARM_RADIUS, 0.9*TORSO_HEIGHT, 0.0);     //display right arm full
                glTranslatef(-0.5,-2,5.75);
                glScalef(0.95,0.5,1);
                glRotatef(theta[5], rot_x, rot_y, rot_z);
                right_upper_arm();
            glPopMatrix();
            glTranslatef(1.5,-0.75,8);
            glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);                               //display elbow joins and right lower arm
            elbow_joints();
            glRotatef(theta[6], 0, 0, 1);                                  
            glRotatef(abc2,0,1,0);
            right_lower_arm();
            glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);                               //display right hand palm ball
            palms(); //left hand
        glPopMatrix();
        
        //left leg
        glPushMatrix();
            glTranslatef(-(TORSO_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);             //left leg upper ball to og location
            glRotatef(theta[7], 1.0, 0.0, 0.0);                                
            left_upper_leg();                                                      
            glTranslatef(0.0, UPPER_LEG_HEIGHT, -1.5);                              //display left knee+lower leg in position
            knee_joints();
            glTranslatef(0.0, 0.0, 1.5);                                                //display left lower leg in position
            glRotatef(theta[8], 1.0, 0.0, 0.0);                                 
            left_lower_leg();
        glPopMatrix();
        
        //right leg
        glPushMatrix();
            glTranslatef((TORSO_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);              //display right leg in position   
            glRotatef(theta[9], 1.0, 0.0, 0.0);                                   
            right_upper_leg();
            glTranslatef(0.0, UPPER_LEG_HEIGHT, -1.5);                              //display right knee+lower leg in position
            knee_joints();
            glTranslatef(0.0, 0.0, 1.5);                                            //display right lower leg in position
            glRotatef(theta[10], 1.0, 0.0, 0.0);                             
            right_lower_leg();
        glPopMatrix();
    }
    else if(flag_dance<=8)
    {
        glRotatef(theta[0], 0.0, 1.0, 0.0);        \
        torso();

        glPushMatrix();
        glTranslatef(0.0, TORSO_HEIGHT+0.5*HEAD_HEIGHT, 0.0);   //setting location of head
        glRotatef(theta[1], 1.0, 0.0, 0.0);               
        glRotatef(theta[2], 0.0, 1.0, 0.0);       
        glTranslatef(0.0, -0.5*HEAD_HEIGHT, 0.0);               //put head slight inside torso
        head();
        glass_bot();
        glPopMatrix();
        //right arm
        if(flag_dance==7)
        {
        rot_x=1.0;
        rot_y=0.0;
        }
        if(flag_dance==8)
        {
        rot_x=0.0;
        rot_y=1.0;
        }
        glPushMatrix();
        glTranslatef(-(TORSO_RADIUS+UPPER_ARM_RADIUS), 0.9*TORSO_HEIGHT, 0.0);    //get to og location
        glRotatef(theta[3], rot_x, rot_y, 0.0);                     
        left_upper_arm();
        glTranslatef(0.0, 0.0, UPPER_ARM_HEIGHT);                               //get to og location
        elbow_joints();                                                             
        glRotatef(theta[4], 1.0, 0.0, 0.0);                            
        left_lower_arm();
        glTranslatef(0.0, 0.0,LOWER_ARM_HEIGHT);                                //set to og location
        palms(); //left hand
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0, TORSO_HEIGHT, 0.0);                                   //get to og location (below head)
        torso_disk();   
        glPopMatrix();
        //shoulder_joints
        glPushMatrix();
        glTranslatef(1.5*TORSO_RADIUS, 0.9*TORSO_HEIGHT, 0.0);                //get to og location
        shoulder_joints();
        glTranslatef(-3.0*TORSO_RADIUS, 0.0, 0.0);                              //get to og location
        shoulder_joints();
        glPopMatrix();
        //leg_joints
        glPushMatrix();
        glTranslatef(1.1*TORSO_RADIUS, 0.0, 0.0);                               //get to og location (left upper leg ball)
        leg_joints();
        glTranslatef(-2.2*TORSO_RADIUS, 0.0, 0.0);                              //right leg upper ball (display)
        shoulder_joints();
        glPopMatrix();
        //left arm
        glPushMatrix();
        glTranslatef(TORSO_RADIUS+UPPER_ARM_RADIUS, 0.9*TORSO_HEIGHT, 0.0);     //display right arm full
        glRotatef(theta[5], 1.0, 0.0, 0.0);                            
        right_upper_arm();
        glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);                               //display elbow joins and right lower arm
        elbow_joints();
        glRotatef(theta[6], 1.0, 0.0, 0.0);                            
        glColor3f(1.0,1.0,1.0);
        right_lower_arm();
        glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);                               //display right hand palm ball
        palms(); //left hand
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-(TORSO_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);             //left leg upper ball to og location
        glRotatef(theta[7], 1.0, 0.0, 0.0);                            
        left_upper_leg();                                                      
        glTranslatef(0.0, UPPER_LEG_HEIGHT, -1.5);                              //display left knee+lower leg in position
        knee_joints();
        glTranslatef(0.0, 0.0, 1.5);                                                //display left lower leg in position
        glRotatef(theta[8], 1.0, 0.0, 0.0);                                  
        left_lower_leg();
        glPopMatrix();
        glPushMatrix();
        glTranslatef((TORSO_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);              //display right leg in position   
        glRotatef(theta[9], 1.0, 0.0, 0.0);                                  
        right_upper_leg();
        glTranslatef(0.0, UPPER_LEG_HEIGHT, -1.5);                              //display right knee+lower leg in position
        knee_joints();
        glTranslatef(0.0, 0.0, 1.5);                                            //display right lower leg in position
        glRotatef(theta[10], 1.0, 0.0, 0.0);                           
        right_lower_leg();
        glPopMatrix();
    }
    else if(flag_dance==9)
    {
        glPushMatrix();
        glRotatef(theta[12],1,0,0);
        torso();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0, TORSO_HEIGHT+0.5*HEAD_HEIGHT, 0.0);   //setting location of head
        glTranslatef(0.0, -0.5*HEAD_HEIGHT, 0.0);               //put head slight inside torso
        head();
        glass_bot();
        glPopMatrix();

        rot_x = 1;
        rot_y = 0;
        rot_z = 0;
        
        //right arm

        glPushMatrix();
            glTranslatef(-(TORSO_RADIUS+UPPER_ARM_RADIUS), 0.9*TORSO_HEIGHT, 0.0);    //get to og location
            glRotatef(theta[3], rot_x, rot_y, rot_z);               

        left_upper_arm();
        glTranslatef(0.0, 0.0, UPPER_ARM_HEIGHT);                               //get to og location
        elbow_joints();
       
        glRotatef(45,-1,0,0);
        glRotatef(theta[4], 0, 1, 0);                 
        glRotatef(abc1,0,0,1);  
       
        left_lower_arm();
        glTranslatef(0.0, 0.0,LOWER_ARM_HEIGHT);                                //set to og location
        palms(); //left hand
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0, TORSO_HEIGHT, 0.0);                                   //get to og location (below head)
            glPushMatrix();
            torso_disk();  
            glPopMatrix();
        glPopMatrix();
        //shoulder_joints
        glPushMatrix();
        glTranslatef(1.5*TORSO_RADIUS, 0.9*TORSO_HEIGHT, 0.0);                //get to og location
        shoulder_joints();
        glTranslatef(-3.0*TORSO_RADIUS, 0.0, 0.0);                              //get to og location
        shoulder_joints();
        glPopMatrix();
        //leg_joints
        glPushMatrix();
        glTranslatef(1.1*TORSO_RADIUS, 0.0, 0.0);                               //get to og location (left upper leg ball)
        leg_joints();
        glTranslatef(-2.2*TORSO_RADIUS, 0.0, 0.0);                              //right leg upper ball (display)
        shoulder_joints();
        glPopMatrix();
        //left arm
        glPushMatrix();
        glTranslatef(TORSO_RADIUS+UPPER_ARM_RADIUS, 0.9*TORSO_HEIGHT, 0.0);     //display right arm full
        glRotatef(theta[5], rot_x, rot_y, rot_z);
        right_upper_arm();
        glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);                               //display elbow joins and right lower arm
        elbow_joints();
            glRotatef(theta[6], 0, 0, 1);              
            glRotatef(abc2,0,1,0);
        right_lower_arm();
        glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);                               //display right hand palm ball
        palms(); //left hand
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-(TORSO_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);             //left leg upper ball to og location
        glRotatef(theta[7], 1.0, 0.0, 0.0);                               
        left_upper_leg();                                                      
        glTranslatef(0.0, UPPER_LEG_HEIGHT, -1.5);                              //display left knee+lower leg in position
        knee_joints();
        glTranslatef(0.0, 0.0, 1.5);                                                //display left lower leg in position
        glRotatef(theta[8], 1.0, 0.0, 0.0);                                  
        left_lower_leg();
        glPopMatrix();
        glPushMatrix();
        glTranslatef((TORSO_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);              //display right leg in position   
        glRotatef(theta[9], 1.0, 0.0, 0.0);                                  
        right_upper_leg();
        glTranslatef(0.0, UPPER_LEG_HEIGHT, -1.5);                              //display right knee+lower leg in position
        knee_joints();
        glTranslatef(0.0, 0.0, 1.5);                                            //display right lower leg in position
        glRotatef(theta[10], 1.0, 0.0, 0.0);                                   
        right_lower_leg();
        glPopMatrix();
        
    }
    
    else if(flag_dance==10)
    {
        glRotatef(theta[0], 0.0, 1.0, 0.0);                     //rotating torso
        torso();

        glPushMatrix();
        glTranslatef(0.0, TORSO_HEIGHT+0.5*HEAD_HEIGHT-2.5, 5.0);   //setting location of head
        glRotatef(theta[1], 1.0, 0.0, 1.0);      
        glRotatef(theta[2], 0.0, 1.0, 1.0);      
        glTranslatef(0.0, -0.5*HEAD_HEIGHT, 0.0);               //put head slight inside torso
        head();
        glass_bot();
        glPopMatrix();
        //right arm
        if(flag_dance==7)
        {
        rot_x=1.0;
        rot_y=0.0;
        }
        if(flag_dance==8)
        {
        rot_x=0.0;
        rot_y=1.0;
        }
        glPushMatrix();
        glTranslatef(-(TORSO_RADIUS+UPPER_ARM_RADIUS), 0.9*TORSO_HEIGHT, 0.0);    //get to og location
        glRotatef(theta[3], rot_x, rot_y, 0.0);                  
        left_upper_arm();
        glTranslatef(0.0, 0.0, UPPER_ARM_HEIGHT);                               //get to og location
        elbow_joints();                                                             
        glRotatef(theta[4], 1.0, 0.0, 0.0);                   
        left_lower_arm();
        glTranslatef(0.0, 0.0,LOWER_ARM_HEIGHT);                                //set to og location
        palms(); //left hand
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0, TORSO_HEIGHT, 0.0);                                   //get to og location (below head)
        torso_disk();   
        glPopMatrix();
        //shoulder_joints
        glPushMatrix();
        glTranslatef(1.5*TORSO_RADIUS, 0.9*TORSO_HEIGHT, 0.0);                //get to og location
        shoulder_joints();
        glTranslatef(-3.0*TORSO_RADIUS, 0.0, 0.0);                              //get to og location
        shoulder_joints();
        glPopMatrix();
        //leg_joints
        glPushMatrix();
        glTranslatef(1.1*TORSO_RADIUS, 0.0, 0.0);                               //get to og location (left upper leg ball)
        leg_joints();
        glTranslatef(-2.2*TORSO_RADIUS, 0.0, 0.0);                              //right leg upper ball (display)
        shoulder_joints();
        glPopMatrix();
        //left arm
        glPushMatrix();
        glTranslatef(TORSO_RADIUS+UPPER_ARM_RADIUS, 0.9*TORSO_HEIGHT, 0.0);     //display right arm full
        glRotatef(theta[5], 1.0, 0.0, 0.0);                              
        right_upper_arm();
        glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);                               //display elbow joins and right lower arm
        elbow_joints();
        glRotatef(theta[6], 1.0, 0.0, 0.0);                    
        glColor3f(1.0,1.0,1.0);
        right_lower_arm();
        glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);                               //display right hand palm ball
        palms(); //left hand
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-(TORSO_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);             //left leg upper ball to og location
        glRotatef(theta[7], 1.0, 0.0, 0.0);                          
        left_upper_leg();                                                      
        glTranslatef(0.0, UPPER_LEG_HEIGHT, -1.5);                              //display left knee+lower leg in position
        knee_joints();
        glTranslatef(0.0, 0.0, 1.5);                                                //display left lower leg in position
        glRotatef(theta[8], 1.0, 0.0, 0.0);                          
        left_lower_leg();
        glPopMatrix();
        glPushMatrix();
        glTranslatef((TORSO_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);              //display right leg in position   
        glRotatef(theta[9], 1.0, 0.0, 0.0);                              
        right_upper_leg();
        glTranslatef(0.0, UPPER_LEG_HEIGHT, -1.5);                              //display right knee+lower leg in position
        knee_joints();
        glTranslatef(0.0, 0.0, 1.5);                                            //display right lower leg in position
        glRotatef(theta[10], 1.0, 0.0, 0.0);                              
        right_lower_leg();
        glPopMatrix();
    }
    
    glDisable(GL_LIGHT1);

    if((flag_dance>=3&&flag_dance<6)||(flag_dance>=9&&flag_dance<11))
    {
        glEnable(GL_LIGHT2);
            table();
        glDisable(GL_LIGHT2);
        
        glEnable(GL_LIGHT0);
            stackIncomplete();
            writing();
            stackComplete();
        glDisable(GL_LIGHT0);
     
        if(flag_dance>8||stackCompCount>0)
        {
            glEnable(GL_LIGHT3);        
            Write("Incomplete",-9,-1);
            Write("Assignments",-9,-2);
            Write("Completed",4,-1);
            Write("Assignments",4,-2);
            glDisable(GL_LIGHT3);
        }
    }
    
glFlush();
glutSwapBuffers();
}

float getAngle(float freq, float min, float max, float t){
return (max - min)*sin(freq*M_PI*t) + 0.5*(min + max);
}
static void idle(void){
    GLfloat seconds = glutGet(GLUT_ELAPSED_TIME)/1000.0;
    
    if(seconds<=(5+previousWindowTime))                                              //walk ahead
    {
        sec+=0.0001;
        theta[3] = getAngle(theta_freq[3], theta_min[3],theta_max[3], seconds);
        theta[5] = getAngle(theta_freq[5], theta_min[5],theta_max[5], seconds);
        theta[7] = getAngle(theta_freq[7], theta_min[7],theta_max[7], seconds);
        theta[9] = getAngle(theta_freq[9], theta_min[9],theta_max[9], seconds);
        
        theta[1] = getAngle(theta_freq[1], theta_min[1],theta_max[1], seconds);
        theta[4] = getAngle(theta_freq[4], theta_min[4],theta_max[4], seconds);
        theta[6] = getAngle(theta_freq[6], theta_min[6],theta_max[6], seconds);
        theta[0] = getAngle(theta_freq[0], theta_min[0],theta_max[0], seconds);
    }    
    else if(seconds<=(6+previousWindowTime))                                     //right hand up
    {
        strcpy(s,"Hello Everyone!!");
        strcpy(s1,"You don't have to worry in SEM 4");
        strcpy(s2,"I'll help you do your assignments..");
        
        flag_dance = 1;
        theta[5] = getAngle(0.60,35,90,seconds); 
    }
    else if(seconds<=(10+previousWindowTime))                                    //hi
    {
        flag_dance = 2;
        theta[5] = getAngle(4,-4,-12,seconds);
    }
    else if(seconds<=(11+previousWindowTime))                                    //right hand down
    {
        strcpy(s,"College begins!!");
        strcpy(s1,"");
        strcpy(s2,"");
        
        flag_dance = 3;
        theta[5] = getAngle(0.60,35,135,seconds); 
    }
    else if(seconds<=(12+previousWindowTime))                                    //sleeping
    {
        flag_dance = 4;
        theta[3] = getAngle(0.5, 50, 0, seconds);        //hand to the side
        theta[4] = getAngle(0.5,0,10, seconds);
        abc1 = getAngle(0.5,0,120,seconds);
        theta[5] = getAngle(0.5, 140, 90, seconds);        //hand to the side
        theta[6] = getAngle(0.5,80,70, seconds);
        abc2 = getAngle(0.5,-100,0,seconds);
    }
    else if(seconds<=(18+previousWindowTime))
    {
        strcpy(s,"JANUARY:");
        strcpy(s1,"No Assignments!!");
        strcpy(s2,"Let's Just Sleep..");
        
        flag_dance = 5;
        if(seconds<=(13+previousWindowTime))
        {
            theta[12] = getAngle(0.5, 0, 30, seconds);      //torso
            theta[13] = getAngle(0.1,0,135,seconds);        //torso disk
            theta[1] = getAngle(0.5, 0, 10, seconds);        //head and glass bot

            theta[3] = getAngle(0,0,45,seconds);
            theta[5] = getAngle(0,-45,0,seconds);
        }
    }
    else if(seconds<=(19+previousWindowTime))                                    //stand straight
    {
        strcpy(s,"FEBRUARY:");
        strcpy(s1,"It's time for Euphoria!!");
        strcpy(s2,"Class Dance Practice...");
        
        flag_dance = 3;
        theta[12] = getAngle(0.60,1,0,seconds);
        theta[5] = getAngle(0.60,35,135,seconds); 
    }
      else if(seconds<=(28+previousWindowTime))                                  //dance
    {         
        flag_dance = 6;
          
        if(seconds >= (21+previousWindowTime)) flag_dance = 7;
        if(seconds >= (23+previousWindowTime)) flag_dance = 8;
        if(seconds>=(21+previousWindowTime) && seconds<=(23+previousWindowTime))
        {
            theta[3] = getAngle(3, 0, -90, seconds);
            theta[5] = getAngle(3, 0, 90, seconds);
            theta[7] = getAngle(3, 160, 200, seconds);
            theta[9] = getAngle(3, 200, 160, seconds);
        }
        theta[1] = getAngle(3, -5, 15, seconds);
        theta[4] = getAngle(2, -10, -35, seconds);
        theta[6] = getAngle(2, -10, -35, seconds);
        theta[0] = getAngle(0.5, -30, 30, seconds);
    }
    else if(seconds<=(29+previousWindowTime))                                        //writing position
    {
        strcpy(s,"MARCH:");
        strcpy(s1,"Assignments Begin..");
        strcpy(s2,"Now I can help you!!");
        
        flag_dance = 4;
        theta[3] = getAngle(0.5,35,40,seconds);
        theta[4] = getAngle(0.5,0,-90, seconds);
        abc1 = getAngle(0.5,0,20,seconds);
        theta[5] = getAngle(0.5,35,100,seconds);
        theta[6] = getAngle(0.5,20,60,seconds);
    }
    else if(seconds<=(41+previousWindowTime))                                        //writing slow
    {
        if(seconds<=(32+previousWindowTime)||(seconds>=(34+previousWindowTime)&&seconds<=(36)+previousWindowTime)||(seconds>=(38+previousWindowTime)&&seconds<=(40+previousWindowTime)))
        {
            flag_dance = 9;
            theta[4] = getAngle(3,20,60,seconds);
            abc1 = getAngle(0.5,0,20,seconds);
            writingCount = 1;
            
            if(seconds<=(32+previousWindowTime))
                strcpy(s3,"TCS: Module Test 1-3");
            else if(seconds>=(34+previousWindowTime)&&seconds<=(36+previousWindowTime))
                strcpy(s3,"AOA: Assignment - 1");
            else if(seconds>=(38+previousWindowTime)&&seconds<=(40+previousWindowTime))
                strcpy(s3,"CG: Module Test - 1");
        }
        else
        {
            strcpy(s3,"");
            
            flag_dance = 4;
            writingCount = 0;
            if(seconds>(40+previousWindowTime))
                stackCompCount = 3;
            else if(seconds>(36+previousWindowTime))
                stackCompCount = 2;
            else if(seconds>(32+previousWindowTime))
                stackCompCount = 1;
            glFlush();
        }
    }
    else if(seconds<=(62+previousWindowTime))                                        //writing fast
    {
        strcpy(s,"APRIL:");
        strcpy(s1,"More Assignments..");
        strcpy(s2,"Time for Term Work Submission!!");
        
        flag_dance = 9;
        theta[4] = getAngle(3,20,60,seconds);
        abc1 = getAngle(0.5,0,20,seconds);
        writingCount = 1;      
        
        if(seconds<=(43+previousWindowTime))                                                     //Incomplete stack and new assignments
            strcpy(s3,"COA: Module Test - 1");
        else if(seconds<=(44+previousWindowTime))
        {
            stackIncompCount = 1;
            strcpy(s3,"DBMS: Mini Project - Proposal");
        }
        else if(seconds<=(45+previousWindowTime))
        {   
            stackIncompCount = 2;
            strcpy(s3,"CG: Module Test 2");
        }
        else if(seconds<=(46+previousWindowTime))
        {
            strcpy(s3,"AM: Tutorial 2 (Home Assignment)");
        }
        else if(seconds<=(47+previousWindowTime))
        {
            stackIncompCount = 3;
            strcpy(s3,"AOA: Write Ups 1-8");
        }
        else if(seconds<=(48+previousWindowTime))
        {
            stackIncompCount = 4;
            strcpy(s3,"COA: Module Test - 2");
        }
        else if(seconds<=(49+previousWindowTime))
        {    
            strcpy(s3,"DBMS: Mini Project - ER Diagram");
        }
        else if(seconds<=(50+previousWindowTime))
        {
            stackIncompCount = 5;
            strcpy(s3,"AM: Tutorial 5 (Home Assignment)");
        }
        else if(seconds<=(51+previousWindowTime))
        {    
            stackIncompCount = 6;
            strcpy(s3,"AOA: Assignment - 2");
        }
        else if(seconds<=(52+previousWindowTime))
        {
            strcpy(s3,"CG: Module Test - 3");
        }
        else if(seconds<=(53+previousWindowTime))
        {
            stackIncompCount = 7;
            strcpy(s3,"AOA: Write Ups 9-11");
        }
        else if(seconds<=(54+previousWindowTime))
        {
            stackIncompCount = 8;
            strcpy(s3,"DBMS: Write Ups 3-9");
        }
        else if(seconds<=(55+previousWindowTime))
        {
            strcpy(s3,"AM: Tutorial 6 (Home Assignment)");
        }
        else if(seconds<=(56+previousWindowTime))
        {
            stackIncompCount = 9;
            strcpy(s3,"CG: Module Test - 4");
        }
        else if(seconds<=(57+previousWindowTime))
        {    
            stackIncompCount = 10;
            strcpy(s3,"AOA: Write Ups 12-15");
        }
        else if(seconds<=(58+previousWindowTime))
        {
            strcpy(s3,"COA: Write Ups 1-9");
        }
        else if(seconds<=(59+previousWindowTime))
        {    
            stackIncompCount = 11;
            strcpy(s3,"DBMS: Write Ups 10-12");
        }
        else if(seconds<=(60+previousWindowTime))
        {    
            stackIncompCount = 12;
            strcpy(s3,"CG: Practical Printouts");
        }
        else if(seconds<=(62+previousWindowTime))
        {
            writingCount = 0;
            flag_dance = 4;
            strcpy(s3,"Mission Failed....!!!!!!!!!!!");
        }
            
        
        if(seconds>(58+previousWindowTime))                                                          //complete stack
            stackCompCount = 5;
        else if(seconds>(54+previousWindowTime))
            stackCompCount = 4;
        else if(seconds>(52+previousWindowTime))
            stackCompCount = 3;
        else if(seconds>(49+previousWindowTime))
            stackCompCount = 2;
        else if(seconds>(46+previousWindowTime))
            stackCompCount = 1;
        else
            stackCompCount = 0;
        
        glFlush();
    }
    else if(seconds<=(66+previousWindowTime))
    {
        flag_dance = 10;
        
        strcpy(s,"");
        strcpy(s1,"");
        strcpy(s2,"");

        strcpy(s3,"CG and DBMS ke Mini Projects to abhi baaki hai!!");
        if(seconds<(63+previousWindowTime))
        {theta[1] = getAngle(0.5, -180, 5, seconds);
        theta[2] = getAngle(0.5, 45, -45, seconds);}
    }
    else if(seconds<=(73+previousWindowTime))
    {
        stackIncompCount = 0;
        stackCompCount = 0;
        strcpy(s3,"");
        
        if(seconds<=(67+previousWindowTime))
            flag_dance = 11;
        else if(seconds<=(68+previousWindowTime))
            flag_dance = 12;
        else if(seconds<=(69+previousWindowTime))
            flag_dance = 13;
        else if(seconds<=(70+previousWindowTime))
            flag_dance = 14;
        else if(seconds<=(71+previousWindowTime))
            flag_dance = 15;
        else if(seconds<=(72+previousWindowTime))
            flag_dance = 16;
    }
    
    srand(time(NULL));
    mat_x = rand()%2;
    mat_y = rand()%2;
    mat_z = rand()%2;
 
    mat_diffuse[0] = mat_x;
    mat_diffuse[1] = mat_y;
    mat_diffuse[2] = mat_z;
    glutPostRedisplay();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
    glOrtho(-10.0, 10.0, -10.0 * (GLfloat) h / (GLfloat) w,
    10.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
    glOrtho(-10.0 * (GLfloat) w / (GLfloat) h,
    10.0 * (GLfloat) w / (GLfloat) h, -10.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void myinit()
{
    //light 1
    GLfloat light_ambient1[]={1.0, 1.0, 1.0, 1.0};                          //GL_LIGHT0 (white - assignment sheets)
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient1);
    //light 2
    GLfloat light_ambient2[]={1.0, 1.0, 1.0, 1.0};                          //GL_LIGHT1 (robot colour)
    GLfloat light_diffuse2[]={1.0, 3.0, 3.0, 1.0};
    GLfloat light_specular2[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_position2[]={10.0, 1.0, 10.0, 0.0};
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular2);
    //light 3
    GLfloat light_ambient3[]={1.0, 1.0, 1.0, 1.0};                          //GL_LIGHT2 (red - table)
    GLfloat light_diffuse3[]={5.0, 0.0, 0.0, 1.0};
    GLfloat light_specular3[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_position3[]={10.0, 1.0, 10.0, 0.0};
    glLightfv(GL_LIGHT2, GL_POSITION, light_position3);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient3);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse3);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular3);
    //light 4
    GLfloat light_ambient4[]={0.0, 10.0, 0.0, 1.0};                          //GL_LIGHT3 (green - text)
    glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient4);
    //light 5
    GLfloat light_ambient5[]={0.0, 0.0, 10.0, 1.0};                          //GL_LIGHT4 (blue - Zzz)
    glLightfv(GL_LIGHT4, GL_AMBIENT, light_ambient5);         
    //light 6
    GLfloat light_ambient6[]={5.0, 10.0, 0.0, 1.0};                          //GL_LIGHT5 (Blue - assignments)
    glLightfv(GL_LIGHT5, GL_AMBIENT, light_ambient6);       
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    /*    Setting the min, max and frequency for body parts*/
    for(i=0;i<11;i++)
    {
    theta_min[i] = 0.0;
    theta_max[i] = 0.0;
    theta_freq[i] = 0.0;
    }
    theta_min[3] = 135; theta_min[5] = 135;
    theta_freq[1] = 3.0;
    theta_max[1] = 15.0; theta_min[1] = -5.0;
    theta_freq[3] = 2.0; theta_freq[5] = 2.0;
    theta_max[3] = 90.0; theta_max[5] = 180.0;
    theta_freq[4] = 2; theta_freq[6] = 2;
    theta_max[4] = -35.0; theta_max[6] = -35.0;
    theta_min[4] = -10.0; theta_min[6] = -10.0;
    theta_freq[7] = 2.0; theta_freq[9] = 2.0;
    theta_max[7] = 200.0; theta_max[9] = 160.0;
    theta_min[7] = 160.0; theta_min[9] = 200.0;
    theta_min[0] = -30; theta_freq[0] = 0.5;
    theta_max[0] = 30;
    /* allocate quadrics with filled drawing style */
    h=gluNewQuadric();
    gluQuadricDrawStyle(h, GLU_FILL);
    gluQuadricNormals(h, GLU_SMOOTH);
    t=gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_FILL);
    gluQuadricNormals(t, GLU_SMOOTH);
    gl=gluNewQuadric();
    gluQuadricDrawStyle(gl, GLU_FILL);
    gluQuadricNormals(gl, GLU_SMOOTH);
    lua=gluNewQuadric();
    gluQuadricDrawStyle(lua, GLU_FILL);
    gluQuadricNormals(lua, GLU_SMOOTH);
    lla=gluNewQuadric();
    gluQuadricDrawStyle(lla, GLU_FILL);
    gluQuadricNormals(lla, GLU_SMOOTH);
    rua=gluNewQuadric();
    gluQuadricDrawStyle(rua, GLU_FILL);
    gluQuadricNormals(rua, GLU_SMOOTH);
    rla=gluNewQuadric();
    gluQuadricDrawStyle(rla, GLU_FILL);
    gluQuadricNormals(rla, GLU_SMOOTH);
    lul=gluNewQuadric();
    gluQuadricDrawStyle(lul, GLU_FILL);
    gluQuadricNormals(lul, GLU_SMOOTH);
    lll=gluNewQuadric();
    gluQuadricDrawStyle(lll, GLU_FILL);
    gluQuadricNormals(lll, GLU_SMOOTH);
    rul=gluNewQuadric();
    gluQuadricDrawStyle(rul, GLU_FILL);
    gluQuadricNormals(rul, GLU_SMOOTH);
    rll=gluNewQuadric();
    gluQuadricDrawStyle(rll, GLU_FILL);
    gluQuadricNormals(rll, GLU_SMOOTH);
    tbl =gluNewQuadric();
    gluQuadricDrawStyle(tbl, GLU_FILL);
    gluQuadricNormals(tbl, GLU_SMOOTH);
}

void Write2D(char *string,float x,float y)
{
    glRasterPos2f(x,y); 
            
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
    
    glFlush();
}

void dda(float x1,float y1,float x2,float y2)//Line 
{
    float dx,dy,steps,i,xinc,yinc;
    dx=x2-x1;
    dy=y2-y1;
    if(abs(dx)>=abs(dy))
        steps=abs(dx);
    else
        steps=abs(dy);
    
    xinc=dx/steps;
    yinc=dy/steps;
    glBegin(GL_POINTS);
    glVertex2f(x1,y1);
    for(i=0;i<=steps;i++)
    {
        x1=x1+xinc;
        y1=y1+yinc;
        glVertex2f(x1,y1);
    }
 glEnd();
        glFlush();
}
void delay(int i)                                //Delay
{
    int c,d;
    for ( c = 1 ; c <= 30000 ; c++ )
        for ( d = 1 ; d <= 300*i ; d++ )
            {}           
    glEnd();
    glFlush();
}
void circle(float x1,float y1,float r)
{
 glBegin(GL_POINTS);
 float x=0,y=r;
 float pk;
 pk=(5/4)-r;
 glVertex2f(x,y);
 while(x<y)
 {
  if(pk<=0)
  {
   pk=pk+2*x+3;
   x=x+1;
  }
  else
  {
   pk=pk+2*x-2*y+5;
   x=x+1;
   y=y-1;
  }
  glVertex2f(x+x1,y+y1);          //1
  glVertex2f(y+x1,x+y1);          //2
                glVertex2f(y+x1,-x+y1);         //3
  glVertex2f(x+x1,-y+y1);         //4  
  glVertex2f(-x+x1,-y+y1);        //5
  glVertex2f(-y+x1,-x+y1);        //6
                glVertex2f(-y+x1,x+y1);         //7
  glVertex2f(-x+x1,y+y1);         //8
  

 }
 glEnd();
        glFlush();
}
void halfcircle(float x1,float y1,float r,int a,int b,int c,int d,int e,int f,int g,int h)
{
 glBegin(GL_POINTS);
        int i;
 float x=0,y=r;
 float pk;
 pk=(5/4)-r;
 glVertex2f(x,y);
 while(x<y)
 {
  if(pk<=0)
  {
   pk=pk+2*x+3;
   x=x+1;
  }
  else
  {
   pk=pk+2*x-2*y+5;
   x=x+1;
   y=y-1;
  }
  if(a==1)
                    glVertex2f(x+x1,y+y1);          //1
                if(b==1)
                    glVertex2f(y+x1,x+y1);          //2
                if(c==1)
                    glVertex2f(y+x1,-x+y1);         //3
  if(d==1)
                    glVertex2f(x+x1,-y+y1);         //4  
  if(e==1)
                    glVertex2f(-x+x1,-y+y1);        //5
  if(f==1)
                    glVertex2f(-y+x1,-x+y1);        //6
                if(g==1)
                    glVertex2f(-y+x1,x+y1);         //7
  if(h==1)
                    glVertex2f(-x+x1,y+y1);         //8
  
 }
 glEnd();
        glFlush();
}
const float DEG2RAD = 3.14159/180.0;
void drawEllipse(float xradius, float yradius)
{
 glBegin(GL_LINE_LOOP);
 for(int i=0; i < 360; i++)
 {
   //convert degrees into radians
  float degInRad = i*DEG2RAD;
  glVertex2f(cos(degInRad)*xradius,sin(degInRad)*yradius);
 } 
 glEnd();
}
void setupEnv()
{
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(0.0, 400.0, 0.0, 400.0, 1.0, -1.0);
 glMatrixMode(GL_MODELVIEW);
 glClearColor(0.0, 0.0, 0.0, 0.0);
 glColor3f(1.0, 1.0, 1.0);
}

void TillCG()
{
    int i=0,j=0,k=0,a=0;
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f,0.0f,0.0f);                  //Red   
    for(i=0;i<20;i++)                          //Shoes
    {          
        dda(105,25+i,134,25+i);         //left
        dda(155,25+i,184,25+i);         //right            
        delay(1);
    }   
    for(i=0;i<80;i++)                          //Legs
    {   glColor3f(1.0f,0.0f,1.0f);
        dda(115,45+i,134,45+i);         //left
        dda(155,45+i,174,45+i);         //right             
        delay(1);
    }
        
    for(i=0;i<10;i++)                          //Body 1
    {   glColor3f(1.0f,1.0f,0.0f);       
        dda(105,125+i,184,125+i);
        delay(1);
    }
    for(i=0;i<80;i++)                          //Body 2
    {   glColor3f(0.0f,1.0f,0.0f);       
        dda(105,135+i,114,135+i);       //left
        dda(175,135+i,184,135+i);       //right
        delay(1);
    }
    for(i=0;i<10;i++)                          //Body 3
    {   glColor3f(0.0f,0.0f,1.0f);      
        dda(105,215+i,184,215+i);
        delay(1);
    }
                                                                               
    for(i=0;i<10;i++)                          //Neck
    {          
        dda(135,225+i,154,225+i);
        delay(1);
    }
    
    glColor3f(1,1,0);
    
    for(i=0;i<40;i++)                           //Head 1
    {          
        dda(144-i,235,145+i,235);
        delay(1);
    }
    for(i=0;i<40;i++)                           //Head 2
    {          
        dda(105,235,105,235+i);         //left
        dda(185,235,185,235+i);         //right
        delay(1);
    }
    for(i=0;i<40;i++)                           //Head 3
    {          
        dda(105,275,105+i,275);         //left
        dda(185,275,185-i,275);         //right
        delay(1);
    }
    
    for(i=0;i<=5;i++)                           //Eyes
    {
        glColor3f(1.0f,1.0f,1.0f);              //White           
        circle(125,265,5+i);            //left
        circle(165,265,5+i);            //right
        delay(1);delay(1);
    }
    glColor3f(1.0f,0.0f,0.0f);                  //Red
    halfcircle(145,250,10,0,0,0,1,1,0,0,0);     //Smile
    
    for(i=0;i<10;i++)                           //Hands 1
    {
        dda(104-i,225,104-i,205);       //left
        dda(186+i,225,186+i,205);       //right
        delay(1);
    }
    for(i=0;i<50;i++)                           //Hands 2
    {   glColor3f(0.0f,0.0f,1.0f);
        dda(94-i,220,94-i,210);         //left
        dda(196+i,220,196+i,210);       //right
        delay(1);
    }
    for(i=0;i<10;i++)                           //Hands 3(Fingers)
    {   glColor3f(1.0f,0.0f,1.0f);
        dda(44-i,224,44-i,204);         //left
        dda(246+i,224,246+i,204);       //right
        delay(1);
    }
    
    for(i=0;i<10;i++)                           //Ears
    {
        halfcircle(105,255,i,0,0,0,0,1,1,1,1);//left
        halfcircle(185,255,i,1,1,1,1,0,0,0,0);//right
        delay(1);
    }
    
    glColor3f(1,0,0);
    
    for(a=0;a<3;a++)
    {
    for(i=0;i<10;i++)                           //HeartBeat 1                           
    {
       dda(116,175,116+i,175);
       delay(1);
    }
   
    for(i=0,j=0;i<10;i++,j+=3)                  //HeartBeat 2
    {
        dda(126,175,126+i,175+j);
        glColor3f(0.0f,0.0f,0.0f);              //Black
        dda(116,175,116+i,175);
        glColor3f(1.0f,0.0f,0.0f);              //Red
        delay(1);
    }
    for(i=0,j=0;i<10;i++,j+=3)                  //HeartBeat 3
    {
        dda(136,205,136+i,205-j);
        glColor3f(0.0f,0.0f,0.0f);              //Black
        dda(126,175,126+i,175+j);
        glColor3f(1.0f,0.0f,0.0f);              //Red
        delay(1);
    }    
    for(i=0,j=0;i<10;i++,j+=3)                  //HeartBeat 4
    {
        dda(146,175,146+i,175-j);
        glColor3f(0.0f,0.0f,0.0f);              //Black
        dda(136,205,136+i,205-j);
        glColor3f(1.0f,0.0f,0.0f);              //Red
        delay(1);
    }
    for(i=0,j=0;i<10;i++,j+=3)                  //HeartBeat 5
    {
        dda(156,145,156+i,145+j);
        glColor3f(0.0f,0.0f,0.0f);              //Black
        dda(146,175,146+i,175-j);
        glColor3f(1.0f,0.0f,0.0f);              //Red
        delay(1);
    }
    for(i=0,j=0,k=0;i<10 || k<9;k++,i++,j+=3)   //HeartBeat 6
    {   if(k<9)
            dda(165,175,165+k,175);
        glColor3f(0.0f,0.0f,0.0f);              //Black
        dda(156,145,156+i,145+j);
        glColor3f(1.0f,0.0f,0.0f);              //Red
        delay(1);
    }for(i=0;i<9;i++)                           //HeartBeat 7
    {       
        glColor3f(0.0f,0.0f,0.0f);              //Black
        dda(165,175,165+i,175);
        glColor3f(1.0f,0.0f,0.0f);              //Red
        delay(1);
    }
    }
    
    for(i=0;i<5;i++)                           //CG 1
    {
        dda(135+i,180,135+i,210);       //C
        dda(135+i,140,135+i,170);       //G
        delay(1);
    }
    for(i=0;i<10;i++)                           //CG 2
    {
        dda(140+i,205,140+i,210);       //C
        dda(140+i,180,140+i,185);
        dda(140+i,165,140+i,170);       //G
        dda(140+i,140,140+i,145);
        if(i>5)
            dda(140+i,152.5,140+i,157.5);
        delay(1);
    }
    for(i=0;i<5;i++)                            //CG 3
    {
        dda(150+i,205,150+i,210);       //C
        dda(150+i,180,150+i,185);
        dda(150+i,165,150+i,170);       //G
        dda(150+i,140,150+i,157.5);
        delay(1);
    }
    
    delay(20);
    
    glColor3f(0,1,0);
    dda(49,5,49,20);                            //Loading bar
    dda(249,5,249,20);
    dda(49,5,249,5);
    dda(49,20,249,20);
    glFlush();
    
    for(i=0;i<200;i++)                          //Loading 
    {
        glColor3f(0,1,0);
        dda(49+i,5,49+i,20);
        glColor3f(1,1,1);
        Write2D("loading...",111.5,7);
        delay(1);
        glFlush();
    }
    
    delay(20);                                  //Thinking 1
    glTranslatef(149,290,0);
    drawEllipse(10,5);
    glFlush();
    
    
}
void WrittenStuff()
{
    glColor3f(1,0,0);
    delay(25);
    Write2D("7668 MELITA SALDANHA",-100,215);
    glFlush();
    
    glColor3f(0,1,0);
    delay(25);
    Write2D("7670 SHRIYA SHET",-100,185);
    glFlush();
    
    glColor3f(0,0,1);
    delay(25);
    Write2D("7674 ASHLEY TUSCANO",-100,155);
    glFlush();
    delay(50);
}
void disp2()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glTranslatef(149,20,0);                         // 1
    delay(50);
    drawEllipse(20,10);   
    glFlush();
    
    glTranslatef(0,40,0);                           // 2
    delay(50);
    drawEllipse(40,20);   
    glFlush();
    
    glTranslatef(0,139,0);                          // 3
    delay(50);
    drawEllipse(150,100);   
    glFlush();
    
    glTranslatef(0,-199,0);                         // Making the origin proper
    
    WrittenStuff();
}
void disp1()
{
    TillCG();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitWindowPosition(970,300);
    glutInitWindowSize(300,300);
    glutCreateWindow("<<Mercury>>");      
    gluOrtho2D(0,300,0,300);
    glutDisplayFunc(disp1);

    glutInitWindowPosition(970,0);
    glutInitWindowSize(300,300);
    glutCreateWindow("<<Shriya>>");      
    gluOrtho2D(0,300,0,300);
    glutDisplayFunc(disp2);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(900, 900);
    glutCreateWindow("<<Melita>>");
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}