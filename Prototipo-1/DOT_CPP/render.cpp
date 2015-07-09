#include "render.h"
#include <iostream>
using namespace std;

#define N 40.0 // Number of vertices on the boundary of the disc.

static int hits; // Number of entries in hit buffer.
static unsigned int buffer[1024]; // Hit buffer.


unsigned int  findClosestHit(int hits, unsigned int buffer[])
{
   unsigned int *ptr, minZ;
   unsigned int  closestName = 0;
   minZ= 0xffffffff; // 2^32 - 1
   ptr = buffer;
   for (int i = 0; i < hits; i++){
      ptr++;
      if (*ptr < minZ){

         minZ = *ptr;
         ptr += 2;
         closestName = *ptr;
         //cout << "AQUI EU ESTOU HITANO O ITEM: " << closestName << endl;
         ptr++;

      }else {
        ptr += 3;
      }
    }

    return closestName;
}

unsigned int Render::render(vector <Object *> objects,  vector <float > proj,  int x, int y, bool render_mode, vector <float > r, float s)

{

    int viewport[4]; // Viewport data.

    glGetIntegerv(GL_VIEWPORT, viewport); // Get viewport data.

    glSelectBuffer(1024, buffer); // Specify buffer to write hit records in selection mode
    (void) glRenderMode(GL_SELECT); // Enter selection mode.

    // Save the viewing volume defined in the resize routine.
    glMatrixMode(GL_PROJECTION);
        glPushMatrix();

        // Define a viewing volume corresponding to selecting in 3 x 3 region around the cursor.
        glLoadIdentity();
        gluPickMatrix((float)x, (float) (viewport[3] - y) , 20.0, 20.0, viewport);
        gluPerspective( proj[0], proj[1], proj[2], proj[3] );
        glTranslatef(1, 0, 0);
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity( );

        glInitNames();
        glPushName(0);

        //charmar a renderObjects aqui
        renderObjects(objects, render_mode, true, r, s);

        hits = glRenderMode(GL_RENDER); // Return to rendering mode, returning number of hits.

        // Restore viewing volume of the resize routine and return to modelview mode.
        glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    // Determine closest of the hit objects (if any).
    return findClosestHit(hits, buffer);
}

void Render::renderObjects(vector <Object *> objects, bool render_mode, bool is_selecting, vector <float > r, float s)
{
    //cout << "Tamanho dos vertices do cubo: " << objects[0]->getVertex().size() << " Size world: " << objects.size() << endl;

   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   gluLookAt(0, 100, 200, 0, 0, 0, 0, 1, 0);

   //Rotacao de todo o cenario
    GLfloat matrix[16];
    glm::quat quat  (glm::vec3((r[0]*PI/BASE)/4, 0*PI/BASE, 0*PI/BASE));
    glm::quat quat2 (glm::vec3(0*PI/BASE, (r[1]*PI/BASE)/4, 0*PI/BASE));
    glm::quat quaternion = quat * quat2;
    glm::mat4 mat  = glm::toMat4(quaternion);
    int count = 0;
    for (int k = 0; k < 4; ++k){
        for (int j = 0; j < 4; ++j){
            matrix[count] = mat[k][j];
            //cout << matrix[count] << ", ";
            count++;
        }
        cout << endl;
    }
    glMultMatrixf(matrix);
    //glPushMatrix();
    //glPushMatrix();

    //Escala para dar Zoom.
    glScalef(s, s, s);

    //if (!is_selecting){
        //glRotatef(r[0]/2, 1.0, .0, 0.0);
        //glRotatef(r[1]/2, 0.0, 1.0, 0.0);
    //}

    for (int i = 0; i <  (int) objects.size() ; ++i) {

        vector <float > t = objects[i]->getTranslation();
        glm::vec4  res = mat * glm::vec4(t[0],t[1],t[2], 1.0f);
        t[0]=res[0];
        t[1]=res[1];
        t[2]=res[2];
        objects[i]->setGlobalTranslation(t);
        //glLoadName(i+1); // register object.
        objects[i]->setRenderMode(render_mode);

        objects[i]->draw(i, is_selecting);
        //cout << "Modo de renderizacao: " << objects[i]->getRenderMode() << endl;
    }
    //glPopName();
    glPopMatrix();
}


/** Inits the OpenGL viewport for drawing in 3D. */
void Render::viewport3D(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y, const float *obsP)

{

	glClearColor(0.3, 0.3, 0.3, 1 ); // Black Background

    glViewport(topleft_x, topleft_y, bottomrigth_x, bottomrigth_y);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    float ratio_w_h = (float)(bottomrigth_x-topleft_x)/(float)(bottomrigth_y-topleft_y);

    gluPerspective(45.0 /*view angle*/, ratio_w_h, 0.1 /*clip close*/, 400 /*clip far*/);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //enable z buffer
    glEnable( GL_DEPTH_TEST );
    //set the value in z-buffer as 1.0
    glClearDepth( 1.0 );
    //gluLookAt(obsP[0],obsP[1],obsP[2],obsP[3],obsP[4],obsP[5],obsP[6],obsP[7], obsP[8]);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //status_projection = true;

}


vector <float > Render::worldPoint(int x, int y)
{
    double modelview[16], projection[16];
    int viewport[4];
    float z;
    double objx, objy, objz;

    /*Read the projection, modelview and viewport matrices
    using the glGet functions.*/
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetIntegerv( GL_VIEWPORT, viewport );

    //Read the window z value from the z-buffer
    glReadPixels( x, viewport[3]-y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z );
    z = 1 - 0.0002;
    //Use the gluUnProject to get the world co-ordinates of
    //the point the user clicked and save in objx, objy, objz.
    gluUnProject( x, viewport[3]-y, z, modelview, projection, viewport, &objx, &objy, &objz );
    float v[] = {(float)objx, (float)objy, (float)objz};
    vector<float > p;
    //p.insert(p.end(), v, v+3);
    p.push_back(objx);
    p.push_back(objy);
    p.push_back(objz);
    cout << "\n\n\nPonto Mouse world " << "X: " << objx << "Y: " << objy << "Z: " << objz << endl;
    return p;
}