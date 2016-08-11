#ifndef VERTEX_H
#define VERTEX_H

/* This class is designed to make passing vertices
 * to the vertex shader much easier to accomplish.
 *
 * It uses QVector3Ds of position and color and a
 * QVector2D of texture position.
 *
 * These values are then passed to the vertex shader
 * in initializeGL().
 *
 * All the other stuff just makes the code look nicer...
 */

#include <QVector3D>

class Vertex
{
public:
    // Constructors
    Q_DECL_CONSTEXPR Vertex();
    Q_DECL_CONSTEXPR explicit Vertex(const QVector3D &position);
    Q_DECL_CONSTEXPR Vertex(const QVector3D &position, const QVector3D &color);    
    Q_DECL_CONSTEXPR Vertex(const QVector3D &position, const QVector3D &color, const QVector2D &texture);
    Q_DECL_CONSTEXPR Vertex(const QVector3D &position, const QVector2D &texture);

    // Accessors
    Q_DECL_CONSTEXPR const QVector3D& position() const;
    Q_DECL_CONSTEXPR const QVector3D& color() const;
    Q_DECL_CONSTEXPR const QVector2D& texture() const;
    void setPosition(const QVector3D& position);
    void setColor(const QVector3D& color);
    void setTexture(const QVector2D& texture);

    // OpenGL Helpers
    static const int PositionTupleSize = 3;
    static const int ColorTupleSize = 3;
    static const int textureTupleSize = 3;
    static Q_DECL_CONSTEXPR int positionOffset();
    static Q_DECL_CONSTEXPR int colorOffset();
    static Q_DECL_CONSTEXPR int textureOffset();
    static Q_DECL_CONSTEXPR int stride();

private:
    QVector3D m_position;
    QVector3D m_color;
    QVector2D m_texture;
};

Q_DECLARE_TYPEINFO(Vertex, Q_MOVABLE_TYPE);

// Constructors
Q_DECL_CONSTEXPR inline Vertex::Vertex() {}
Q_DECL_CONSTEXPR inline Vertex::Vertex(const QVector3D &position) : m_position(position) {}
Q_DECL_CONSTEXPR inline Vertex::Vertex(const QVector3D &position, const QVector3D &color) :m_position(position), m_color(color) {}
Q_DECL_CONSTEXPR inline Vertex::Vertex(const QVector3D &position, const QVector3D &color, const QVector2D &texture) :m_position(position), m_color(color),m_texture(texture) {}
Q_DECL_CONSTEXPR inline Vertex::Vertex(const QVector3D &position, const QVector2D &texture) :m_position(position), m_texture(texture) {}

// Accessors
Q_DECL_CONSTEXPR inline const QVector3D& Vertex::position() const   { return m_position; }
Q_DECL_CONSTEXPR inline const QVector3D& Vertex::color()    const   { return m_color; }
Q_DECL_CONSTEXPR inline const QVector2D& Vertex::texture()  const   { return m_texture; }
void inline Vertex::setPosition(const QVector3D& position)          { m_position = position; }
void inline Vertex::setColor(const QVector3D& color)                { m_color = color; }
void inline Vertex::setTexture(const QVector2D& texture)            { m_color = texture; }

// OpenGL Helpers
Q_DECL_CONSTEXPR inline int Vertex::positionOffset()    { return offsetof(Vertex, m_position); }
Q_DECL_CONSTEXPR inline int Vertex::colorOffset()       { return offsetof(Vertex, m_color); }
Q_DECL_CONSTEXPR inline int Vertex::textureOffset()     { return offsetof(Vertex, m_texture); }
Q_DECL_CONSTEXPR inline int Vertex::stride()            {return sizeof(Vertex); }

#endif // VERTEX_H
