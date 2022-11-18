

#pragma once

#include "Vectors.h"
#include "Matrices.h"

class Camera
{
public:
    enum ProjectionType
    {
        PERSPECTIVE,            ///< Perspective projection
        ORTHO                   ///< Orthographic (parallel) projection
    };

public:
    Camera();
    virtual ~Camera();

    void            setViewMatrix(const Matrix4 & mat);
    void            setFromLookAt(const Vector3 & eye, const Vector3 & vrp, const Vector3 & up);
    void            toLookAt(Vector3 * eye, Vector3 * vrp, Vector3 * up) const;

    Vector3           position() const;
    Vector3           direction() const;
    Vector3           up() const;
    Vector3           right() const;

    ProjectionType  projection() const;
    void            setProjectionAsPerspective(double fieldOfViewYDeg, double nearPlane, double farPlane);
    void            setProjectionAsOrtho(double height, double nearPlane, double farPlane);
    void            setProjectionAsUnitOrtho();
    void            setProjectionAsPixelExact2D();

    void            fitView(const BoundingBox & boundingBox, const Vector3 & dir, const Vector3 & up, double relativeDistance = 1.0);
    void            setClipPlanesFromBoundingBoxPerspective(const BoundingBox & boundingBox, double minNearPlaneDistance = 0.01);

    const Matrix4 & viewMatrix() const;
    const Matrix4 & invertedViewMatrix() const;
    const Matrix4 & projectionMatrix() const;

    double          fieldOfViewYDeg() const;
    double          nearPlane() const;
    double          farPlane()const;

    double          aspectRatio() const;
    double          frontPlaneFrustumHeight() const;
    double          frontPlanePixelHeight() const;
    double          distanceWhereObjectProjectsToPixelExtent(double objectExtentWorld, double objectExtentPixels) const;

    void            setViewport(uint x, uint y, uint width, uint height);
    Viewport * viewport();
    const Viewport * viewport() const;

    ref<Ray>        rayFromWinCoord(int winCoordX, int winCoordY) const;
    ref<Plane>      planeFromLineWinCoord(Vec2i winCoordStart, Vec2i winCoordEnd) const;
    bool            unproject(const Vector3 & coord, Vector3 * out) const;
    bool            project(const Vector3 & point, Vector3 * out) const;

    double          computeProjectedBoundingBoxPixelArea(const BoundingBox & box) const;
    double          computeProjectedBoundingSpherePixelArea(const Vector3 & center, double radius) const;
    bool            isProjectedBoundingBoxLessThanThreshold(const BoundingBox & box, double pixelThreshold) const;

    Frustum         frustum() const;

    void            applyOpenGL() const;

private:
    void            updateCachedValues();

    Frustum         computeViewFrustum() const;

    static Matrix4    createFrustumMatrix(double left, double right, double bottom, double top, double zNear, double zFar);
    static Matrix4    createPerspectiveMatrix(double fovy, double aspect_ratio, double znear, double zfar);
    static Matrix4    createOrthoMatrix(double left, double right, double bottom, double top, double near, double far);
    static Matrix4    createLookAtMatrix(Vector3 eye, Vector3 vrp, Vector3 up);

private:
    Matrix4           m_viewMatrix;
    Matrix4           m_cachedInvertedViewMatrix;         // Cached inverted version of the m_viewMatrix
    Matrix4           m_projectionMatrix;
    Matrix4           m_cachedProjectionMultViewMatrix;   // Caching projMat*viewMat, as this is used in many tight loops (eps. computeBoundingBoxPixelSize)
    ProjectionType  m_projectionType;

    double          m_fieldOfViewYDeg;                  // Stored for perspective projection
    double          m_frontPlaneFrustumHeight;          // Height of view frustum in the front plane
    double          m_nearPlane;
    double          m_farPlane;

    ref<Viewport>   m_viewport;
    double          m_cachedFrontPlanePixelHeight;      // Height of a pixel in the front clipping plane given in world coordinates
    Frustum         m_cachedViewFrustum;
};


