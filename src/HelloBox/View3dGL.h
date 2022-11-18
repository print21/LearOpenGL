

#include <QOpenGLWidget>

#include "Matrices.h"

class View3dGL : public QOpenGLWidget
{
    Q_OBJECT;
public:
    explicit View3dGL(QWidget * parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~View3dGL();

public Q_SLOTS:
    void slotModelValueChanged(int posx, int posy, int posz, int rotp, int roty, int rotr);
    void slotViewValueChanged(int posx, int posy, int posz, int rotp, int roty, int rotr);

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

    void setViewport(int x, int y, int w, int h);
    void setOrthoProjection(float left, float right, float bottom, float top, float near, float far);

protected:
    unsigned int shaderProgram;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;

    Matrix4 viewMatrix;
    Matrix4 modelMatrix;
    Matrix4 projectMatrix;
};

