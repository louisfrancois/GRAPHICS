/*  Louis BOUDDHOU
 *  Final Project
 *
 *  Used class exemple 8, 9, 13 and 15 to help
 *
 * 
 *  Key bindings:
 *  m          Modes (orthogonal, perspective, first person navigation)
 *  n          Interrupt light movement
 *  l          Toggle lighting
 *  +/-        Changes field of view for perspective
 *  </>        Move light when stopped
 *  x          Toggle axes on and off
 *  ESC        Exit
 *  0          Reset view angle
 *
 * In orthogonal and perspective modes:
 *   arrows     Change view angle 
 *   
 * In first person navigation
 *   arrows     Change view angle on static plane
 *   w/s        Change height
 *  
 */


#include "CSCIx229.h"

int tmode=0;      //  Texture Mode
int mode=0;       //  Display mode
int axes=0;       //  Display axes
int proj_mode=0;       //  Projection mode
int move=1;       //  Move lighting
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=10.0;   //  Size of world
int new_angle = 0;
int light=1;      //  Lighting
double moveX = 0.0;
double moveZ = 0.0;
double y_pos = 0.0;

// Light values
int one       =   1;  // Unit value
int distance  =   5;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shinyvec[1];    // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light

// wall textures
unsigned int walls;
unsigned int glass_window;
unsigned int grey_brick_wall;
unsigned int plaque_wall;
unsigned int ground;
unsigned int red_wall;
unsigned int old_brick;
unsigned int dice[6];
unsigned int concrete_wall;
unsigned int building_wall;
unsigned int building_windows;
unsigned int modern_building;
unsigned int cloud_window;
unsigned int old_facade;

// roof textures
unsigned int roof_wood_texture;
unsigned int tiles;
unsigned int grey_roof;
unsigned int metal_grey;
unsigned int building_top;

// ground textures
unsigned int stone_ground;
unsigned int roadway_lines;
unsigned int pavement_coffee;
unsigned int simple_pavement;

// grid
int key_x = 15;
int key_z = 3;



static void building1(float x, float z);
static void building2(float x, float z);
static void building3(float x, float z);
static void building4(float x, float z);
static void building5(float x, float z);
static void building6(float x, float z);
static void building7(float x, float z);
static void building8(float x, float z);
static void building9(float x, float z);
static void building10(float x, float z);
static void building11(float x, float z);
static void building12(float x, float z);
static void building13(float x, float z);
static void building14(float x, float z);
static void building15(float x, float z);
static void building16(float x, float z);
static void building17(float x, float z);
static void building18(float x, float z);
static void building19(float x, float z);
static void building20(float x, float z);
static void building21(float x, float z);
static void building22(float x, float z);
static void building23(float x, float z);
static void building24(float x, float z);
static void building25(float x, float z);
static void building26(float x, float z);
static void building27(float x, float z);
static void building28(float x, float z);
static void building29(float x, float z);
static void building30(float x, float z);
static void Vertex(double th,double ph);


// /*
//  *  Draw a cube
//  *     at (x,y,z)
//  *     dimentions (dx,dy,dz)
//  *     rotated th about the y axis
//  */
// static void cube(double x,double y,double z,
//                  double dx,double dy,double dz,
//                  double th)
// {
//    //  Set specular color to white
//    float white[] = {1,1,1,1};
//    float Emission[]  = {0.0,0.0,0.01*emission,1.0};
//    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
//    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
//    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
//    //  Save transformation
//    glPushMatrix();
//    //  Offset, scale and rotate
//    glTranslated(x,y,z);
//    glRotated(th,0,1,0);
//    glScaled(dx,dy,dz);
//    //  Enable textures
//    glEnable(GL_TEXTURE_2D);
//    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,tmode?GL_REPLACE:GL_MODULATE);
//    glColor3f(1,1,1);
//    //  Front
//    glBindTexture(GL_TEXTURE_2D,dice[1]);
//    glBegin(GL_QUADS);
//    glNormal3f( 0, 0, 1);
//    glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
//    glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
//    glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
//    glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
//    glEnd();
//    //  Back
//    glBindTexture(GL_TEXTURE_2D,dice[2]);
//    glBegin(GL_QUADS);
//    glNormal3f( 0, 0,-1);
//    glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
//    glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
//    glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
//    glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
//    glEnd();
//    //  Right
//    glBindTexture(GL_TEXTURE_2D,dice[3]);
//    glBegin(GL_QUADS);
//    glNormal3f(+1, 0, 0);
//    glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
//    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
//    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
//    glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
//    glEnd();

//    //  Left
//    glBindTexture(GL_TEXTURE_2D,dice[4]);
//    glBegin(GL_QUADS);
//    glNormal3f(-1, 0, 0);
//    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
//    glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
//    glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
//    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
//    glEnd();
//    //  Top
//    glBindTexture(GL_TEXTURE_2D,dice[5]);
//    glBegin(GL_QUADS);
//    glNormal3f( 0,+1, 0);
//    glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
//    glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
//    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
//    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
//    glEnd();
//    //  Bottom
//    glBindTexture(GL_TEXTURE_2D,dice[0]);
//    glBegin(GL_QUADS);
//    glNormal3f( 0,-1, 0);
//    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
//    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
//    glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
//    glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
//    glEnd();
//    //  Undo transformations and textures
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
// }


static void cubex(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th,
                  int front_texture,
                  int back_texture,
                  int right_texture,
                  int left_texture,
                  int top_texture,
                  int bottom_texture,
                  double rep,
                  double myR, double myG, double myB)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,tmode?GL_REPLACE:GL_MODULATE);
   glColor3f(myR,myG,myB);
   //  Front
   glBindTexture(GL_TEXTURE_2D,front_texture);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0  ,0); glVertex3f(-1,-1, 1);
   glTexCoord2f(rep,0); glVertex3f(+1,-1, 1);
   glTexCoord2f(rep,rep); glVertex3f(+1,+1, 1);
   glTexCoord2f(0  ,rep); glVertex3f(-1,+1, 1);
   glEnd();
   //  Back
   glBindTexture(GL_TEXTURE_2D, back_texture);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0,-1);
   glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(rep,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(rep,rep); glVertex3f(-1,+1,-1);
   glTexCoord2f(0,rep); glVertex3f(+1,+1,-1);
   glEnd();
   //  Right
   glBindTexture(GL_TEXTURE_2D, right_texture);
   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0  ,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(rep,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(rep,rep); glVertex3f(+1,+1,-1);
   glTexCoord2f(0  ,rep); glVertex3f(+1,+1,+1);
   glEnd();

   //  Left
   glBindTexture(GL_TEXTURE_2D, left_texture);
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0  ,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(rep,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(rep,rep); glVertex3f(-1,+1,+1);
   glTexCoord2f(0  ,rep); glVertex3f(-1,+1,-1);
   glEnd();
   //  Top
   glBindTexture(GL_TEXTURE_2D, top_texture);
   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0  ,0); glVertex3f(-1,+1,+1);
   glTexCoord2f(rep,0); glVertex3f(+1,+1,+1);
   glTexCoord2f(rep,rep); glVertex3f(+1,+1,-1);
   glTexCoord2f(0  ,rep); glVertex3f(-1,+1,-1);
   glEnd();
   //  Bottom
   glBindTexture(GL_TEXTURE_2D, bottom_texture);
   glBegin(GL_QUADS);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(0  ,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(rep,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(rep,rep); glVertex3f(+1,-1,+1);
   glTexCoord2f(0  ,rep); glVertex3f(-1,-1,+1);
   glEnd();
   //  Undo transformations and textures
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}


static void cubey(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th,
                  int front_texture,
                  int back_texture,
                  int right_texture,
                  int left_texture,
                  int top_texture,
                  int bottom_texture,
                  double rep,
                  double myR, double myG, double myB)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,tmode?GL_REPLACE:GL_MODULATE);
   glColor3f(myR,myG,myB);
   //  Front
   glBindTexture(GL_TEXTURE_2D,front_texture);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0  ,0); glVertex3f(-1,-1, 1);
   glTexCoord2f(rep,0); glVertex3f(+1,-1, 1);
   glTexCoord2f(rep,rep); glVertex3f(+1,+1, 1);
   glTexCoord2f(0  ,rep); glVertex3f(-1,+1, 1);
   glEnd();
   //  Back
   glBindTexture(GL_TEXTURE_2D, back_texture);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0,-1);
   glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(rep,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(rep,rep); glVertex3f(-1,+1,-1);
   glTexCoord2f(0,rep); glVertex3f(+1,+1,-1);
   glEnd();
   //  Right
   glBindTexture(GL_TEXTURE_2D, right_texture);
   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0  ,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(rep,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(rep,rep); glVertex3f(+1,+1,-1);
   glTexCoord2f(0  ,rep); glVertex3f(+1,+1,+1);
   glEnd();

   //  Left
   glBindTexture(GL_TEXTURE_2D, left_texture);
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0  ,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(rep,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(rep,rep); glVertex3f(-1,+1,+1);
   glTexCoord2f(0  ,rep); glVertex3f(-1,+1,-1);
   glEnd();
   //  Top
   glBindTexture(GL_TEXTURE_2D, top_texture);
   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0  ,0); glVertex3f(-1,+1,+1);
   glTexCoord2f(0,rep); glVertex3f(+1,+1,+1);
   glTexCoord2f(rep,rep); glVertex3f(+1,+1,-1);
   glTexCoord2f(rep,0); glVertex3f(-1,+1,-1);
   glEnd();
   //  Bottom
   glBindTexture(GL_TEXTURE_2D, bottom_texture);
   glBegin(GL_QUADS);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(0  ,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(rep,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(rep,rep); glVertex3f(+1,-1,+1);
   glTexCoord2f(0  ,rep); glVertex3f(-1,-1,+1);
   glEnd();
   //  Undo transformations and textures
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void cylinder(double x,double y,double z,double r, double h, int cylinder_texture, double rep)
{
   const int d=5;
   int th;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(r,1,r);


      glColor3f(1, 1 , 1);
      glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,cylinder_texture);

   glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   glBegin(GL_QUAD_STRIP);
   for (th=0;th<=360;th+=d)
   {
      double x = Sin(th);
      double z = Cos(th);
      glNormal3d(x, 0, z);
      glTexCoord2f(th/360.0f,0);
      glVertex3d(x, 0, z);
      glTexCoord2f(th/360.0f, rep);
      glVertex3d(x, h, z);
   }
   glEnd();
   glDisable(GL_TEXTURE_2D);

   //  Undo transformations
   glPopMatrix();
}



static void sphere2(double x,double y,double z,
                     double r,
                     double scale_x,
                     double scale_y,
                     double scale_z)
{
   const int d=5;
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(scale_x,scale_y,scale_z);
   glScaled(r,r,r);
   //  White sphere
   glColor3f(1,1,1);
   glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

   //  Latitude bands
   for (ph=-90;ph<90;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=d)
      {
         Vertex(th,ph);
         Vertex(th,ph+d);
      }
      glEnd();
   }

   //  Undo transformations
   glPopMatrix();
}


static void tire(double x,double y,double z, double r, double h, int cylinder_texture){
   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(90,0,0,1);
   {
      sphere2(0,0,0,r,1,0.00000001,1);
      cylinder(0,0,0, r, h, cylinder_texture, 1);
      sphere2(0,h,0,r,1,0.00000001,1);
   }
   glRotated(-90,0,0,1);
   glPopMatrix();
}

/*
   Draw a car
*/
static void car(double x,double y,double z, double angle)   
{
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glScaled(0.3,0.3,0.3);
   glRotated(angle,0,1,0);

   cubex(0.0,0.26,-0.05 , 0.15,0.07,0.20 , 0 , glass_window , glass_window , glass_window , glass_window , ground , ground, 0.1 , 1,1,1);
   cubex(0.0,0.12,0.0 , 0.15,0.07,0.35 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);
   tire(0.17,0.06,0.17,0.06,0.04,tiles);
   tire(0.17,0.06,-0.17,0.06,0.04,tiles);
   tire(-0.13,0.06,0.17,0.06,0.04,tiles);
   tire(-0.13,0.06,-0.17,0.06,0.04,tiles);


   glPopMatrix();
   glDisable(GL_TEXTURE_2D);

}  



/*
   Draw a house1
*/
static void house(double x,double y,double z,
                  double dx,double dy,double dz,
                  double r, 
                  int front_wall_texture,
                  int back_wall_texture,
                  int right_wall_texture,
                  int left_wall_texture,
                  int bottom_wall_texture,
                  int front_roof_texture,
                  int back_roof_texture,
                  int right_roof_texture,
                  int left_roof_texture,
                  double rep)   
{
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glScaled(dx,dy,dz);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,tmode?GL_REPLACE:GL_MODULATE);
   glColor3f(1,1,1);

   //  Cube
   //  Create Base
      // Beige Front
      glColor3f(245/255.0, 241/255.0, 222/255.0);
      glBindTexture(GL_TEXTURE_2D, front_wall_texture);
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, 1);
      glTexCoord2f(0  ,0); glVertex3f(-1,-1, 1);
      glTexCoord2f(rep,0); glVertex3f(+1,-1, 1);
      glTexCoord2f(rep,rep); glVertex3f(+1,+1, 1);
      glTexCoord2f(0  ,rep); glVertex3f(-1,+1, 1);
      glEnd();
      // Beige Back
      glColor3f(245/255.0, 241/255.0, 222/255.0);
      glBindTexture(GL_TEXTURE_2D, back_wall_texture);
      glBegin(GL_QUADS);
      glNormal3f( 0, 0,-1);
      glTexCoord2f(0  ,0); glVertex3f(+1,-1,-1);
      glTexCoord2f(rep,0); glVertex3f(-1,-1,-1);
      glTexCoord2f(rep,rep); glVertex3f(-1,+1,-1);
      glTexCoord2f(0  ,rep); glVertex3f(+1,+1,-1);
      glEnd();
      // FFE5CC Right
      glColor3f(255/255.0, 229/255.0, 204/255.0);
      glBindTexture(GL_TEXTURE_2D, right_wall_texture);
      glBegin(GL_QUADS);
      glNormal3f(+1, 0, 0);
      glTexCoord2f(0  ,0); glVertex3f(+1,-1,+1);
      glTexCoord2f(rep,0); glVertex3f(+1,-1,-1);
      glTexCoord2f(rep,rep); glVertex3f(+1,+1,-1);
      glTexCoord2f(0  ,rep); glVertex3f(+1,+1,+1);
      glEnd();
      // FFE5CC Left
      glColor3f(255/255.0, 229/255.0, 204/255.0);
      glBindTexture(GL_TEXTURE_2D, left_wall_texture);
      glBegin(GL_QUADS);
      glNormal3f(-1, 0, 0);
      glTexCoord2f(0  ,0); glVertex3f(-1,-1,-1);
      glTexCoord2f(rep,0); glVertex3f(-1,-1,+1);
      glTexCoord2f(rep,rep); glVertex3f(-1,+1,+1);
      glTexCoord2f(0  ,rep); glVertex3f(-1,+1,-1);
      glEnd();
      // Magenta Bottom
      glColor3f(1.0, 0.0, 1.0);
      glBindTexture(GL_TEXTURE_2D, bottom_wall_texture);
      glBegin(GL_QUADS);
      glNormal3f( 0,-1, 0);
      glTexCoord2f(0  ,0); glVertex3f(-1,-1,-1);
      glTexCoord2f(rep,0); glVertex3f(+1,-1,-1);
      glTexCoord2f(rep,rep); glVertex3f(+1,-1,+1);
      glTexCoord2f(0  ,rep); glVertex3f(-1,-1,+1);
      glEnd();

   //glEnd();

   // glBindTexture(GL_TEXTURE_2D,tiles);
   // Building Rooftop
   
      // grey front roof
      glColor3f(1,1,1);
      glBindTexture(GL_TEXTURE_2D, front_roof_texture);
      glBegin(GL_TRIANGLES);
      glNormal3f(0,1,2.3);
      glTexCoord2f(0,0); glVertex3f(1,1,1);
      glTexCoord2f((rep + rep/2),0); glVertex3f(-1,1,1);
      glTexCoord2f(rep,rep); glVertex3f(0,2.3,0);
      glEnd();

      // dimgrey right roof
      glColor3f(1,1,1);
      glBindTexture(GL_TEXTURE_2D, right_roof_texture);
      glBegin(GL_TRIANGLES);
      glNormal3f(2.3,1,0);
      glTexCoord2f(0,0); glVertex3f(1,1,-1);
      glTexCoord2f((rep + rep/2),0); glVertex3f(1,1,1);
      glTexCoord2f(rep,rep); glVertex3f(0,2.3,0);
      glEnd();

      // grey back roof
      glColor3f(1,1,1);
      glBindTexture(GL_TEXTURE_2D, back_roof_texture);
      glBegin(GL_TRIANGLES);
      glNormal3f(0,1,-2.3);
      glTexCoord2f(0,0); glVertex3f(1,1,-1);
      glTexCoord2f((rep + rep/2),0); glVertex3f(-1,1,-1);
      glTexCoord2f(rep,rep); glVertex3f(0,2.3,0);
      glEnd();

      // dimgrey left roof
      glColor3f(1,1,1);
      glBindTexture(GL_TEXTURE_2D, left_roof_texture);
      glBegin(GL_TRIANGLES);
      glNormal3f(-2.3,1,0);
      glTexCoord2f(0,0); glVertex3f(-1,1,1);
      glTexCoord2f((rep + rep/2),0); glVertex3f(-1,1,-1);
      glTexCoord2f(rep,rep); glVertex3f(0,2.3,0);  
      glEnd();    

   // Building door and windows
   // glBegin(GL_QUADS);
   //    // 944C009 Front door
   //    glColor3f(153/255.0, 76/255.0, 0.0);
   //    glNormal3f(0,1,2.3);
   //    glVertex3f(0.8,-1,1.01);
   //    glVertex3f(0.8,0.5,1.01);
   //    glVertex3f(0.2,0.5,1.01);
   //    glVertex3f(0.2,-1,1.01);

   //    // 944C009 Right window
   //    glColor3f(0.0, 191/255.0, 1.0);
   //    glNormal3f(+1, 0, 0);
   //    glVertex3f(1.01,0.5,0.8);
   //    glVertex3f(1.01,0.5,-0.8);
   //    glVertex3f(1.01,-0.1,-0.8);
   //    glVertex3f(1.01,-0.1,0.8);
   
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);

}  

/*
   Draw a house2
*/
static void house2(double x,double y,double z,
                  double dx,double dy,double dz,
                  double r, 
                  int front_texture2,
                  int back_texture2,
                  int left_texture2,
                  int right_texture2,
                  int bottom_texture2,
                  double rep)   
{
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glScaled(dx,dy,dz);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,tmode?GL_REPLACE:GL_MODULATE);
   glColor3f(1,1,1);

   //  Cube
   //  Create Base
      // Beige Front
      glColor3f(245/255.0, 241/255.0, 222/255.0);
      glBindTexture(GL_TEXTURE_2D, front_texture2);
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, 1);
      glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
      glTexCoord2f(rep,0); glVertex3f(+1,-1, 1);
      glTexCoord2f(rep,rep); glVertex3f(+1,+1, 1);
      glTexCoord2f(0,rep); glVertex3f(-1,+1, 1);
      glEnd();
      // Beige Back
      glColor3f(245/255.0, 241/255.0, 222/255.0);
      glBindTexture(GL_TEXTURE_2D, back_texture2);
      glBegin(GL_QUADS);
      glNormal3f( 0, 0,-1);
      glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
      glTexCoord2f(rep,0); glVertex3f(-1,-1,-1);
      glTexCoord2f(rep,rep); glVertex3f(-1,+1,-1);
      glTexCoord2f(0,rep); glVertex3f(+1,+1,-1);
      glEnd();
      // FFE5CC Right
      glColor3f(255/255.0, 229/255.0, 204/255.0);
      glBindTexture(GL_TEXTURE_2D, right_texture2);
      glBegin(GL_QUADS);
      glNormal3f(+1, 0, 0);
      glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
      glTexCoord2f(rep,0); glVertex3f(+1,-1,-1);
      glTexCoord2f(rep,rep); glVertex3f(+1,+1,-1);
      glTexCoord2f(0,rep); glVertex3f(+1,+1,+1);
      glEnd();
      // FFE5CC Left
      glColor3f(255/255.0, 229/255.0, 204/255.0);
      glBindTexture(GL_TEXTURE_2D, left_texture2);
      glBegin(GL_QUADS);
      glNormal3f(-1, 0, 0);
      glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
      glTexCoord2f(rep,0); glVertex3f(-1,-1,+1);
      glTexCoord2f(rep,rep); glVertex3f(-1,+1,+1);
      glTexCoord2f(0,rep); glVertex3f(-1,+1,-1);
      glEnd();
      // Magenta Bottom
      glColor3f(1.0, 0.0, 1.0);
      glBindTexture(GL_TEXTURE_2D, bottom_texture2);
      glBegin(GL_QUADS);
      glNormal3f( 0,-1, 0);
      glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
      glTexCoord2f(rep,0); glVertex3f(+1,-1,-1);
      glTexCoord2f(rep,rep); glVertex3f(+1,-1,+1);
      glTexCoord2f(0,rep); glVertex3f(-1,-1,+1);
      glEnd();

   //glEnd();

   glBindTexture(GL_TEXTURE_2D,tiles);
   // Building Rooftop
    

   // Building door and windows
   // glBegin(GL_QUADS);
   //    // 944C009 Front door
   //    glColor3f(153/255.0, 76/255.0, 0.0);
   //    glNormal3f(0,1,2.3);
   //    glVertex3f(0.8,-1,1.01);
   //    glVertex3f(0.8,0.5,1.01);
   //    glVertex3f(0.2,0.5,1.01);
   //    glVertex3f(0.2,-1,1.01);

   //    // 944C009 Right window
   //    glColor3f(0.0, 191/255.0, 1.0);
   //    glNormal3f(+1, 0, 0);
   //    glVertex3f(1.01,0.5,0.8);
   //    glVertex3f(1.01,0.5,-0.8);
   //    glVertex3f(1.01,-0.1,-0.8);
   //    glVertex3f(1.01,-0.1,0.8);
   glEnd();
   
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);

}  


/*
 *  Draw vertex in polar coordinates
 */
static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

static void sphere(double x,double y,double z,
                     double r,
                     double scale_x,
                     double scale_y,
                     double scale_z)
{
   const int d=5;
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(scale_x,scale_y,scale_z);
   //  White sphere
   glColor3f(1,1,1);
   glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

   //  Latitude bands
   for (ph=-90;ph<90;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=d)
      {
         Vertex(th,ph);
         Vertex(th,ph+d);
      }
      glEnd();
   }

   //  Undo transformations
   glPopMatrix();
}


void drawAll(){
    /*
            FENCE WALLS ON X
         */
         // x = -8
         cubex(-8.0,0.05,0.0 , 0.01,0.05,10 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);

         // x = -6
         cubex(-6.0,0.05,0.0 , 0.01,0.05,10 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);

         // x = -4
         cubex(-4.0,0.05,0.0 , 0.01,0.05,10 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);

         // x = -2
         cubex(-2.0,0.05,0.0 , 0.01,0.05,10 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);

         /*
         // x = 0
         cubex(0.0,0.2,0.0 , 0.01,0.2,10 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);
         */

         // x = 2
         cubex(2.0,0.05,0.0 , 0.01,0.05,10 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);

         // x = 4
         cubex(4.0,0.05,0.0 , 0.01,0.05,10 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);

         // x = 6
         cubex(6.0,0.05,0.0 , 0.01,0.05,10 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);

         // x = 8
         cubex(8.0,0.05,0.0 , 0.01,0.05,10 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);

         /*
            FENCE WALLS ON z
         */
         // x = -4
         cubex(0.0,0.2,-4.0 , 10,0.05,0.005 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);

         // x = -2
         cubex(0.0,0.0025,-2.0 , 10,0.0025,0.005 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);

         // x = -1
         cubex(0.0,0.0025,-1.0 , 10,0.0025,0.005 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);

         // z = 1
         cubex(0.0,0.0025,+1.0 , 10,0.0025,0.005 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);

         // x = 2
         cubex(0.0,0.0025,+2.0 , 10,0.0025,0.005 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);

         // x = 4
         cubex(0.0,0.0025,+4.0 , 10,0.0025,0.005 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);

         // x = 5
         cubex(0.0,0.0025,+5.0 , 10,0.0025,0.005 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);

         // x = 7
         cubex(0.0,0.0025,+7.0 , 10,0.0025,0.005 , 0 , ground , ground , ground , ground , ground , ground, 1 , 1,1,1);

         
         /* ********************************* STREET 1  ******************************************/ 

         /*********** ON Z ***********/

         // road 1 on z
         cubex(0.0,0.0,-1.5 , 6.0,0.0,0.5 , 0 , ground , ground , ground , ground , ground , ground, 4 , 0.5,0.5,0.5);

         // road 2 on z
         cubex(0.0,0.0,1.5 , 6.0,0.0,0.5 , 0 , ground , ground , ground , ground , ground , ground, 4 , 0.5,0.5,0.5);

         // road 2 on z
         cubex(0.0,0.0,4.5 , 6.0,0.0,0.5 , 0 , ground , ground , ground , ground , ground , ground, 4 , 0.5,0.5,0.5);

         /*********** ON X ***********/
         // road 1 on x
         cubey(-4.8,0.002,-1.5 , 0.5,0.002,6.0 , 0 , ground , ground , ground , ground , ground , ground, 4 , 0.5,0.5,0.5);

         // road 1 on x
         cubey(6.2,0.002,-1.5 , 0.5,0.002,6.0 , 0 , ground , ground , ground , ground , ground , ground, 4 , 0.5,0.5,0.5);

         // walk way 1
         cubex(0.95,0.002,0.0 , 0.2,0.002,1.0 , 0 , ground , ground , ground , ground , stone_ground , ground, 6 , 0.5,0.5,0.5);

         // walk way 2
         cubex(0.95,0.002,3.0 , 0.2,0.002,1.0 , 0 , ground , ground , ground , ground , stone_ground , ground, 6 , 0.5,0.5,0.5);

         /* ********************************* PAVEMENT 1  ******************************************/ 

         // pavement 1
         cubex(0.0,-0.1,0.0 , 7.0,0.1,1.0 , 0 , ground , ground , ground , ground , simple_pavement , ground, 20 , 1,1,1);

         // pavement 2
         cubex(0.0,-0.1,3.0 , 7.0,0.1,1.0 , 0 , ground , ground , ground , ground , simple_pavement , ground, 20 , 1,1,1);


         /* ********************************* ROW 1 OF BUILDINGS **********************************/

         

         building1(1.5, 0.0);
         building2(2.2, 0.0);
         building3(2.9 , 0.0);
         

         // High glass office building
         building4(3.2,-0.6);

         // High glass and metal apartment building 
         building5(4.0, 0.4);
         building6(4.6, 0.25);
         // window panel
         cubex(4.9,1.2,0.4 , 0.002,1.2,0.1 , 0 , glass_window , glass_window , glass_window , glass_window , glass_window , glass_window, 3 , 1,1,1);


         // Medium apartment building
         building7(4.5,-0.5);
         
         /*
         // High glass office building 
         building8(-0.3,0.0);
         building9(-0.3,0.0);
         */
         
         // Apartments house
         building10(-1.8, 0.5);
         
         // Appartments house
         building11(-1.9,-0.5);
         
         // Very high shopping mall
         building12(-3.3,0.0);
         building13(-3.3,0.0);
         building14(-3.3,0.0);
         building15(-3.3,0.0);

         // High round glass office building
         building27(5.05,3.0);
         building28(5.05,3.0);
         building29(5.05,3.0);
         building30(5.05,3.0);


         /* ********************************* ROW 2 OF BUILDINGS **********************************/ 

         // High Office building
         building16(0,2.5);
         building16(2,2.5);
         
         // High Office building
         building17(-0.2,3.4);
         
         // Tripler library buildings
         // High skinny library building
         building18(-1.4,3.0);
         
         // High skinny library building
         building19(-2.2,2.5);
         
         // High skinny library building
         building20(-2.2,3.4);
         
         // Medium old school building
         building21(-3.55,3.0);
         
         // High bulky apartment building
         building22(3.2,3.0);
         building23(3.0,2.5);
         
         // Highest office building
         building24(2.3,3.3);
         
         // High glass office building
         building25(1.7,3.2);
         
         // Very high long office building
         building26(4.05,3.0);
         



         /*
            **************************** GROUND PLANE (TEXTURE NOT WORKING) *******************************************
         */
         // cubex(0.3,0.01,0.3 , 20.0,0.01,20.0 , 0 , ground , ground , ground , ground , ground , ground , 5);

         // house(3.6,0.3,0.0 , 0.3,0.3,0.3 , 0, 0);

         // house(4.3,0.3,0.0 , 0.3,0.3,0.3 , 0, 0);


         // The the sun
         sphere(1.0,10.0,1.0,0.3 , 0.3,0.3,0.3);
}
/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   const double len=20;  //  Length of axes
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (proj_mode == 1)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else if(proj_mode == 2)
   {
      double Ex = 0 + moveX;
      double Ez = +2*dim + moveZ;
      double Cx = Ex-Sin(new_angle);
      double Cz = Ez-Cos(new_angle);
      gluLookAt(Ex,y_pos,Ez , Cx,y_pos,Cz , 0,1,0);
   }
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }

   //  Flat or smooth shading
   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   //  Light switch
   if (light)
   {
        //  Translate intensity to color vectors
        float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
        float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
        float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
        //  Light position
        float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
        //  Draw light position as sphere (still no lighting here)
        glColor3f(1,1,1);
        sphere(Position[0],Position[1],Position[2],0.1 , 0.1,0.1,0.1);
        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
        //  glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        //  Enable light 0
        glEnable(GL_LIGHT0);
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
        glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
     glDisable(GL_LIGHTING);

   drawAll();

  car(0, 0, 0, 0);
        
   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   glPopMatrix();
   //  Display parameters
   glWindowPos2i(5,5);
   if (proj_mode == 2) Print("Angle=%d,%d  Dim=%.1f FOV=%d Proection= First Person View",th,ph,dim,fov);
   else Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s",th,ph,dim,fov,mode?"Perpective":"Orthogonal");

   //  Render the scene and make it visible
   glFlush();
   glutSwapBuffers();
}


/************************************************************** BUILDINGS FACTORY  *************************************************************/

static void building1(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // first frame
   house(0.0,0.3,0.0 , 0.3,0.3,0.3 , 0 , walls , walls , walls , walls , walls , tiles , tiles , tiles , tiles, 3);
   glPopMatrix();
}

static void building2(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // second frame
   house(0.0,0.3,0.0 , 0.7,0.3,0.7 , 0 , walls , walls , walls , walls , walls , tiles , tiles , tiles , tiles, 3);
   glPopMatrix();
}

static void building3(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // third frame
   house(0.0,0.3,0.0 , 0.5,0.3,0.5 , 0 , walls , walls , walls , walls , walls , tiles , tiles , tiles , tiles, 3);     
   glPopMatrix();
}

static void building4(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   house2(0,1.1,0 , 0.3,1.1,0.15 , 0 , glass_window , glass_window , glass_window , glass_window , glass_window , 3);
   // flat roof
   cubex(0,2.21,0 , 0.305,0.01,0.155 , 0 , metal_grey , metal_grey , metal_grey , metal_grey , metal_grey , metal_grey, 3 , 1,1,1);     
   glPopMatrix();
}

static void building5(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // first glass frame first level
   house2(0,1.2,0 , 0.3,1.2,0.3 , 0 ,  glass_window, grey_brick_wall , glass_window , grey_brick_wall, grey_brick_wall, 6);
   // flat roof
   cubex(0,2.43,0 , 0.305,0.03,0.305 , 0 , metal_grey , metal_grey , metal_grey , metal_grey , metal_grey , metal_grey, 3 , 1,1,1);     

   glPopMatrix();
}

static void building6(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // second brick frame 
   house2(0,1.2,0 , 0.3,1.2,0.3 , 0 , concrete_wall,  concrete_wall ,     concrete_wall ,  concrete_wall,    concrete_wall, 6);
   // flat roof
   cubex(0,2.43,0 , 0.305,0.03,0.305 , 0 , metal_grey , metal_grey , metal_grey , metal_grey , metal_grey , metal_grey, 3 , 1,1,1);    
   glPopMatrix();
}

static void building7(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   house2(0,0.8,0 , 0.9,0.8,0.3 , 0, building_wall , building_wall , building_wall , building_wall , building_wall , 2);
   // roof
   cubex(0,1.61,0 , 0.905,0.01,0.305 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall, 3 , 1,1,1);     
   glPopMatrix();
}

static void building8(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // frame
   house2(0,0.5,0 , 1.0,0.5,0.8 , 0, glass_window, glass_window , glass_window , glass_window, glass_window, 3);
   // roof
   cubex(0,1.05,0 , 1.005,0.05,0.805 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , metal_grey , ground, 3 , 1,1,1);     
   glPopMatrix();
}

static void building9(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // frame
   house2(0,1.1,0 , 0.80,1.0,0.60 , 0, glass_window, glass_window , glass_window , glass_window, glass_window, 3);
   // roof
   cubex(0,2.2,0 , 0.805,0.1,0.605 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , metal_grey , ground, 3 , 1,1,1);     
   glPopMatrix();
}

static void building10(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   house(0,0.3,0 , 0.3,0.3,0.4 , 0, glass_window , red_wall , red_wall , red_wall , red_wall , grey_roof , grey_roof , grey_roof , grey_roof, 3);    
   glPopMatrix();
}

static void building11(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   house2(0,0.4,0 , 0.5,0.4,0.4 , 0, red_wall , red_wall , red_wall , red_wall , red_wall , 3);
   // flat roof
   cubex(0,0.81,0 , 0.51,0.01,0.41 , 0 , metal_grey , metal_grey , metal_grey , metal_grey , metal_grey , metal_grey, 3 , 1,1,1);    
   glPopMatrix();
}

static void building12(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // first frame
   house2(0,0.4,0 , 0.8,0.4,0.6 , 0, building_wall , building_wall , building_wall , building_wall , building_wall , 2);
   // flat roof
   cubex(0,0.81,0 , 0.805,0.01,0.605 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall, 3 , 1,1,1);    
   glPopMatrix();
}

static void building13(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // second frame
   house2(0,1.22,0 , 0.75,0.4,0.55 , 0, building_wall , building_wall , building_wall , building_wall , building_wall , 2);
   // second roof
   cubex(0,1.63,0 , 0.755,0.01,0.610 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall, 3 , 1,1,1);   
   glPopMatrix();
}

static void building14(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // third frame
   house2(0,2.04,0 , 0.60,0.4,0.40 , 0, building_wall , building_wall , building_wall , building_wall , building_wall , 2);
   // third roof
   cubex(0,2.45,0 , 0.605,0.01,0.405 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall, 3 , 1,1,1); 
   glPopMatrix();
}

static void building15(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // fourth frame
   house2(0,2.84,0 , 0.45,0.4,0.25 , 0, building_wall , building_wall , building_wall , building_wall , building_wall , 2);
   // fourth roof
   cubex(0,3.25,0 , 0.455,0.01,0.255 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall, 3 , 1,1,1);     
   glPopMatrix();
}

static void building16(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   house2(0.0,1.3,0, 0.6,1.3,0.4 , 0, building_wall , building_wall , building_wall , building_wall , building_wall , 2);
   cubex(0.0,2.61,0, 0.605,0.01,0.405 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall, 3 , 1,1,1);
   glPopMatrix();
}

static void building17(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   house2(0,1.1,0 , 0.8,1.1,0.5 , 0, building_wall , building_wall , building_wall , building_wall , building_wall , 2);
   //  roof
   cubex(0,2.21,0 , 0.805,0.01,0.505 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall, 3 , 1,1,1);     
   glPopMatrix();
}

static void building18(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   house2(0,1.2,0 , 0.25,1.2,0.5 , 0, building_windows , building_windows , building_windows , building_windows , building_windows , 3.2);
   // roof
   cubex(0,2.41,0 , 0.255,0.01,0.505 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall, 3 , 1,1,1);     
   glPopMatrix();
}

static void building19(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   house2(0,1.0,0 , 0.6,1.0,0.2 , 0, building_windows , building_windows , building_windows , building_windows , building_windows , 2.8);
   // roof
   cubex(0,2.01,0 , 0.605,0.01,0.205 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall, 3 , 1,1,1);    
   glPopMatrix();
}

static void building20(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   house2(0,1.0,0 , 0.6,1.0,0.2 , 0, building_windows , building_windows , building_windows , building_windows , building_windows , 2.8);
   // roof
   cubex(0,2.01,0 , 0.605,0.01,0.205 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall, 3 , 1,1,1);  
   glPopMatrix();
}

static void building21(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   house2(0,1.5,0 , 0.65,1.5,0.8 , 0, modern_building , modern_building , modern_building , modern_building , modern_building , 5);
   // roof
   cubex(0,3.01,0 , 0.655,0.01,0.805 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall, 3 , 1,1,1);   
   glPopMatrix();
}

static void building22(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // first frame
   house(0,0.3,0 , 0.4,0.3,0.75 , 0 , old_facade , old_facade , old_facade , old_facade , old_facade , tiles , tiles , tiles , tiles, 1.5);
   glPopMatrix();
}

static void building23(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // second frame
   house2(0,0.9,0 , 0.3,0.9,0.3 , 0 , old_facade , old_facade , old_facade , old_facade , old_facade , 2);
   // roof
   cubex(0,1.81,0 , 0.305,0.01,0.305 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall, 3 , 1,1,1);    
   glPopMatrix();
}

static void building24(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   house2(0,2.0,0 , 0.4,2.0,0.4 , 0, cloud_window , cloud_window , cloud_window , cloud_window , cloud_window , 8);
   // roof
   cubex(0,4.01,0 , 0.405,0.01,0.405 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall, 3 , 1,1,1); 
   glPopMatrix();
}

static void building25(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   house2(0,1.0,0 , 0.35,1.0,0.35 , 0, glass_window , glass_window , glass_window , glass_window , glass_window , 8);
   // roof
   cubex(0,2.01,0 , 0.355,0.01,0.355 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall, 3 , 1,1,1);   
   glPopMatrix();
}

static void building26(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   house2(0,1.5,0 , 0.35,1.5,0.8 , 0, modern_building , modern_building , modern_building , modern_building , modern_building , 8);
   // roof
   cubex(0,3.01,0 , 0.355,0.01,0.805 , 0 , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall , concrete_wall, 3 , 1,1,1); 
   glPopMatrix();
}

static void building27(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // first frame
   cylinder(0,0,0 , 0.5,  1.0 , modern_building, 2.7);
   // first roof
   sphere(0,1.0,0 , 0.5  ,  0.5,0.5,0.5);
   glPopMatrix();
}

static void building28(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // second frame
   cylinder(0,1.05,0 , 0.45, 0.8 , modern_building, 2.6);
   // second roof
   sphere(0,1.85,0 , 0.45 , 0.45,0.30,0.45);
   glPopMatrix();
}

static void building29(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // third frame
   cylinder(0,1.90,0 , 0.35, 0.9 , modern_building, 2.7);
   // third roof
   sphere(0,2.80,0 , 0.35 , 0.35,0.20,0.35);
   glPopMatrix();
}

static void building30(float x, float z){

   glPushMatrix();
   glTranslated(x,0,z);
   // fourth frame
   cylinder(0,2.85,0 , 0.25, 0.9 , modern_building, 2.2);
   // fourth roof
   sphere(0,3.70,0 , 0.35 , 0.35,0.05,0.35);
   glPopMatrix();
}


/**************************************************************************************************************************************************/

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   if(move){
      //  Elapsed time in seconds
      double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
      zh = fmod(90*t,360.0);
      //  Tell GLUT it is necessary to redisplay the scene
      glutPostRedisplay();
   }
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (proj_mode == 0 || proj_mode == 1)
   {
      if (key == GLUT_KEY_RIGHT)
         th += 5;
      //  Left arrow key - decrease angle by 5 degrees
      else if (key == GLUT_KEY_LEFT)
         th -= 5;
      //  Up arrow key - increase elevation by 5 degrees
      else if (key == GLUT_KEY_UP)
         ph += 5;
      //  Down arrow key - decrease elevation by 5 degrees
      else if (key == GLUT_KEY_DOWN)
         ph -= 5;
      //  PageUp key - increase dim
      else if (key == GLUT_KEY_PAGE_UP)
         dim += 0.1;
      //  PageDown key - decrease dim
      else if (key == GLUT_KEY_PAGE_DOWN && dim>1)
         dim -= 0.1;
      //  Keep angles to +/-360 degrees
      th %= 360;
      ph %= 360;
   }
   else 
   {
      if (key == GLUT_KEY_RIGHT)
         new_angle -= 5;
      //  Left arrow key - decrease angle by 5 degrees
      else if (key == GLUT_KEY_LEFT)
         new_angle += 5;
      //  Up arrow key - increase elevation by 5 degrees
      else if (key == GLUT_KEY_UP) 
      {
         moveX -= 0.5*Sin(new_angle);
         moveZ -= 0.5*Cos(new_angle);
      }     
      //  Down arrow key - decrease elevation by 5 degrees
      else if (key == GLUT_KEY_DOWN)
      {
         moveX += 0.5*Sin(new_angle);
         moveZ += 0.5*Cos(new_angle);
      }
      //  PageUp key - increase dim
      else if (key == GLUT_KEY_PAGE_UP)
         dim += 0.1;
      //  PageDown key - decrease dim
      else if (key == GLUT_KEY_PAGE_DOWN && dim>1)
         dim -= 0.1;
      //  Keep angles to +/-360 degrees
      new_angle %= 360;
   }

   
   
   //  Update projection
   Project(proj_mode?fov:0,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angles
   else if (ch == 'w' || ch == 'W')
      y_pos += 0.1;

   else if (ch == 's' || ch == 'S')
      y_pos -= 0.1;

   else if (ch == '0')
      new_angle = moveX = moveZ = y_pos = th = ph = 0;
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Switch display mode
   else if (ch == 'm' || ch == 'M')
      // mode = 1-mode;
      proj_mode = (proj_mode+1)%3;
   //  Toggle light movement
   else if (ch == 'n' || ch == 'N')
      move = 1-move;
   //  Move light
   else if (ch == '<')
      zh += 1;
   else if (ch == '>')
      zh -= 1;
   //  Change field of view angle
   else if (ch == '-' && fov>1)
      fov--;
   else if (ch == '+' && fov<179)
      fov++;
   //  Reproject
   Project(proj_mode?fov:0,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);


   //  Set projection
   Project(proj_mode?fov:0,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(1300,800);
   glutCreateWindow("Textures and Lighting");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load textures
   walls = LoadTexBMP("textures/wall_bricks.bmp");
   tiles = LoadTexBMP("textures/tile_roof.bmp");
   ground = LoadTexBMP("textures/road_texture.bmp");
   glass_window = LoadTexBMP("textures/glass_window.bmp");
   red_wall = LoadTexBMP("textures/red_wall.bmp");
   metal_grey = LoadTexBMP("textures/metal_grey.bmp");
   plaque_wall = LoadTexBMP("textures/plaque_wall.bmp");
   roof_wood_texture = LoadTexBMP("textures/roof_wood_texture.bmp");
   grey_brick_wall = LoadTexBMP("textures/grey_brick_wall.bmp");
   grey_roof = LoadTexBMP("textures/grey_roof.bmp");
   stone_ground = LoadTexBMP("textures/stone_ground.bmp");
   old_brick = LoadTexBMP("textures/old_brick.bmp");
   pavement_coffee = LoadTexBMP("textures/pavement_coffee.bmp");
   simple_pavement = LoadTexBMP("textures/simple_pavement.bmp");
   concrete_wall = LoadTexBMP("textures/concrete_wall.bmp");
   building_wall = LoadTexBMP("textures/building_wall.bmp");
   building_windows = LoadTexBMP("textures/building_windows.bmp");
   modern_building = LoadTexBMP("textures/modern_building.bmp");
   cloud_window = LoadTexBMP("textures/cloud_window.bmp");
   old_facade = LoadTexBMP("textures/old_facade.bmp"); 
   building_top = LoadTexBMP("textures/old_facade.bmp"); 

   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
