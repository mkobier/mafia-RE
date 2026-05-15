#include "Physics.h"
#include "../../Core/Memory.h"

constexpr uintptr_t ADDR_CHECK_SPHERE_INTERSECTION = 0x29C60;

namespace Physics
{
    long double __stdcall CheckSphereIntersection(Vector3* position1, Vector3* velocity1, float radius1, Vector3* position2, Vector3* velocity2, float radius2)
    {
        // Position difference vector (P2 - P1)
        float dx = position2->x - position1->x;
        float dz = position2->z - position1->z;
        float dy = position2->y - position1->y;

        // Velocity difference vector (V2 - V1)
        float dvx = velocity2->x - velocity1->x;
        float dvz = velocity2->z - velocity1->z;
        float dvy = velocity2->y - velocity1->y;

        float sumRadiiSq = (radius1 + radius2) * (radius1 + radius2);

        // Squares of differences
        float dySq = dy * dy;
        float dzSq = dz * dz;
        float dxSq = dx * dx;

        // Squared distance between sphere centers
        float distSq = dzSq + dySq + dxSq;

        // Check if spheres are already intersecting
        if (distSq <= sumRadiiSq)
            return 0.0f;

        // Squared relative velocity
        float relVelSq = dvy * dvy + dvz * dvz + dvx * dvx;

        // If relative velocity is zero, spheres will never meet
        if (relVelSq <= 0.0f)
            return -1.0f;

        // Dot product of velocity and position vectors
        float b = 2.0f * (dvx * dx + dvy * dy + dvz * dz);
        float c = distSq - sumRadiiSq;

        // Discriminant: D = b^2 - 4ac
        float discriminant = b * b - 4.0f * relVelSq * c;

        if (discriminant >= 0.0f)
        {
            float sqrtD = sqrtf(discriminant);
            float inv2a = 1.0f / (2.0f * relVelSq);

            // Two possible intersection times
            float t1 = (sqrtD - b) * inv2a;
            float t2 = (-b - sqrtD) * inv2a;

            // Return the smaller time (equivalent to min(t1, t2))
            if (t1 < t2)
                return t1;

            return t2;
        }

        return discriminant;
    }

    void InitHooks(uintptr_t gameBaseAddress)
    {

        Memory::InstallHook(gameBaseAddress + ADDR_CHECK_SPHERE_INTERSECTION, (void*)&CheckSphereIntersection, 5);
    }
}