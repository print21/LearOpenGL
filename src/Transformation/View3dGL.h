

#include <QOpenGLWidget>

#include "Matrices.h"

class View3dGL : public QOpenGLWidget
{
    Q_OBJECT;
public:
    explicit View3dGL(QWidget * parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~View3dGL();

    void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);

    void setMousePosition(int x, int y) { mouseX = x; mouseY = y; };
    void setDrawMode(int mode);
    void setWindowSize(int width, int height);
    void setViewMatrix(float x, float y, float z, float pitch, float heading, float roll);
    void setModelMatrix(float x, float y, float z, float rx, float ry, float rz);

    void setCameraX(float x) { cameraPosition[0] = x; updateViewMatrix(); }
    void setCameraY(float y) { cameraPosition[1] = y; updateViewMatrix(); }
    void setCameraZ(float z) { cameraPosition[2] = z; updateViewMatrix(); }
    void setCameraAngleX(float p) { cameraAngle[0] = p; updateViewMatrix(); }
    void setCameraAngleY(float h) { cameraAngle[1] = h; updateViewMatrix(); }
    void setCameraAngleZ(float r) { cameraAngle[2] = r; updateViewMatrix(); }
    float getCameraX() { return cameraPosition[0]; }
    float getCameraY() { return cameraPosition[1]; }
    float getCameraZ() { return cameraPosition[2]; }
    float getCameraAngleX() { return cameraAngle[0]; }
    float getCameraAngleY() { return cameraAngle[1]; }
    float getCameraAngleZ() { return cameraAngle[2]; }

    void setModelX(float x) { modelPosition[0] = x; updateModelMatrix(); }
    void setModelY(float y) { modelPosition[1] = y; updateModelMatrix(); }
    void setModelZ(float z) { modelPosition[2] = z; updateModelMatrix(); }
    void setModelAngleX(float a) { modelAngle[0] = a; updateModelMatrix(); }
    void setModelAngleY(float a) { modelAngle[1] = a; updateModelMatrix(); }
    void setModelAngleZ(float a) { modelAngle[2] = a; updateModelMatrix(); }
    float getModelX() { return modelPosition[0]; }
    float getModelY() { return modelPosition[1]; }
    float getModelZ() { return modelPosition[2]; }
    float getModelAngleX() { return modelAngle[0]; }
    float getModelAngleY() { return modelAngle[1]; }
    float getModelAngleZ() { return modelAngle[2]; }

    // return 16 elements of  target matrix
    const float * getViewMatrixElements() { return matrixView.get(); }
    const float * getModelMatrixElements() { return matrixModel.get(); }
    const float * getModelViewMatrixElements() { return matrixModelView.get(); }
    const float * getProjectionMatrixElements() { return matrixProjection.get(); }

    void rotateCamera(int x, int y);
    void zoomCamera(int dist);
    void zoomCameraDelta(float delta);  // for mousewheel

    bool isShaderSupported() { return glslSupported; }

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

    void drawScene();
    // member functions
    void initLights();                              // add a white light ti scene
    void setViewport(int x, int y, int width, int height);
    void setViewportSub(int left, int bottom, int width, int height, float nearPlane, float farPlane);
    void drawGrid(float size, float step);          // draw a grid on XZ plane
    void drawAxis(float size);                      // draw 3 axis
    void drawSub1();                                // draw upper window
    void drawSub2();                                // draw bottom window
    void drawFrustum(float fovy, float aspect, float near, float far);
    Matrix4 setFrustum(float l, float r, float b, float t, float n, float f);
    Matrix4 setFrustum(float fovy, float ratio, float n, float f);
    Matrix4 setOrthoFrustum(float l, float r, float b, float t, float n = -1, float f = 1);
    void updateModelMatrix();
    void updateViewMatrix();
    bool createShaderPrograms();

    QString getShaderStatus(GLuint shader);
    QString getProgramStatus(GLuint program);

protected:
    // members
    int windowWidth;
    int windowHeight;
    int povWidth;           // width for point of view screen (left)
    bool windowSizeChanged;
    bool drawModeChanged;
    int drawMode;
    int mouseX;
    int mouseY;
    float cameraPosition[3];
    float cameraAngle[3];
    float modelPosition[3];
    float modelAngle[3];

    // these are for 3rd person view
    float cameraAngleX;
    float cameraAngleY;
    float cameraDistance;
    float bgColor[4];

    // 4x4 transform matrices
    Matrix4 matrixView;
    Matrix4 matrixModel;
    Matrix4 matrixModelView;
    Matrix4 matrixProjection;

    // glsl extension
    bool glslSupported;
    bool glslReady;
    GLuint progId1;             // shader program with color
    GLuint progId2;             // shader program with color + lighting
};

