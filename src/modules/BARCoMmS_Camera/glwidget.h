#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QOpenGLWidget>
#include "qopenglfunctions.h"
#include "qopenglbuffer.h"
#include "qopenglvertexarrayobject.h"
#include "qopenglshaderprogram.h"
#include "vertex.h"
#include <QOpenGLBuffer>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    /* Initializes GL...
     * Sets up the shaders
     * Binds the VAO and vertex buffer to
     * the widget.
     *
     * Basically does everything.
     */
    void initializeGL();
    /* Paints the widget
     *
     * Called every time the widget gets updated
     * So basically all the time.
     */
    void paintGL();
    /* Resizes the widget to fit the screen.
     * Reloads the texture every time.
     */
    void resizeGL(int width, int height);
    /* Takes a QString of an image's path,
     * converts it into a texture and then
     * binds that texture to the OpenGL widget.
     */
    void loadTextureImg(QString imagePath);
    /* Tears down everything...*/
    void tearDownGL();

    /* Accessor for QString currentImage */
    void setCurrentImage(QString imagePath);

signals:
    /* Signals initially in resizeGL() when
     * imageObject is null
     */
    void GLStartup();
    void imageChanged(QString imagePath);

public slots:
    /* This function takes in values of the positions
     * of sliders. It also takes in a char*. This char*
     * is used to identify which uniform variable
     * in the vertex/fragment shader the slider
     * is trying to access.
     *
     * It then passes that value to
     * the fragment/vertex shader via uniform variables.
     * Tada!
     */
    void changeValue(int value,char* name);

private:
    QImage *imageObject;
    GLuint *tex;
    QPixmap image;
    QString currentImage;

    // OpenGL State Information
    QOpenGLBuffer m_vertex;
    QOpenGLVertexArrayObject m_object;
    QOpenGLShaderProgram *m_program;
    QMatrix4x4 m_projection;
    QMatrix4x4 m_modelView;
    GLuint EBO;

    /* Actually emits the signal
     */
    void emitGLStartup();
};

#endif // GLWIDGET_H
