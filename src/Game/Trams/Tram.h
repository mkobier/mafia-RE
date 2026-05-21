#pragma once
#include <cstdint>
#include "TramPassenger.h"

struct I3DFrame;
struct I3DFrameSound;
struct I3DFrameModel;
struct CollisionTreeData;
struct ActionData;

struct TramWindowList
{
    char pad[0x14];
};

struct SeatBuffer
{
    char pad[8];
};

struct PassengerData
{
    char pad[0x10];
};

struct Matrix4
{
    Vector3 row0;
    float element0_3;
    Vector3 row1;
    float element1_3;
    Vector3 row2;
    float element2_3;
    Vector3 pos;
    float element3_3;

};

struct I3DFrameModel
{
    void** vftable;                             // 0x00
    int hasSavedData;                           // 0x04
    int gap8;                                   // 0x08
    char* userProperties;                       // 0x0C
    Matrix4x4 globalMatrix;                     // 0x10
    Matrix4x4 localMatrix;                      // 0x50
    Vector3 scale;                              // 0x90
    int rotation[4];                            // 0x9C
    int stateFlags;                             // 0xAC
    char field_B0[80];                          // 0xB0
    char* objectName;                           // 0x100
    char* shortObjectName;                      // 0x104
    int(__stdcall* callbackFunction)(int, int, int, int); // 0x108
    I3DFrameModel* mainModelFrame;              // 0x10C
    int frameType;                              // 0x110
    float averageScale;                         // 0x114
    int field_118;                              // 0x118
    int childCount;                             // 0x11C
    I3DFrameModel* parentFrame;                 // 0x120
    I3DFrameModel* subordinateFrame;            // 0x124
    I3DFrameModel* previousSiblingFrame;        // 0x128
    I3DFrameModel* nextSiblingFrame;            // 0x12C
    int field_130;                              // 0x130
    I3DFrameModel* child1;                      // 0x134
    I3DFrameModel* child2;                      // 0x138
    int pedestrianViewRelated;                  // 0x13C
};

class Tram
{
public:
    char baseObject[0x68];                  //0x0
    I3DFrameModel* frameModel;              //0x68
    int is_duplicated;                      //0x6C
    int unknown0;                           // 0x70
    int field_74;                           // 0x74
    int field_78;                           // 0x78
    int emptyBit;                           // 0x7C
    int* destinationPoints;                 // 0x80
    int* destinationPointsEnd;              // 0x84
    int destinationPointsCapacity;          // 0x88
    int field_8C;                           // 0x8C
    Vector3 tramPosition;                   // 0x90
    Vector3 rearPosition;                   // 0x9C
    int field_A8;                           // 0xA8
    int* nearestRoutePoint;                 // 0xAC
    int* lastRoutePoint;                    // 0xB0
    int field_B4;                           // 0xB4
    float* carOscillationArray;             // 0xB8
    Vector3* carCenter;                     // 0xBC
    Vector3** vectors3Base;                 // 0xC0
    I3DFrameModel** modelsBase;             // 0xC4
    int field_C8;                           // 0xC8
    int field_CC;                           // 0xCC
    float currentSpeed;                     // 0xD0
    float actualSpeed;                      // 0xD4
    int stopOrMoveTimer;                    // 0xD8
    int selectionFlag;                      // 0xDC
    int unknown1;                           // 0xE0
    int routeState;                         // 0xE4
    CollisionTreeData* tramCollisions;      // 0xE8
    int railColl[6];                        // 0xEC
    int someArray2;                         // 0x104
    int array2End;                          // 0x108
    int field_10C;                          // 0x10C
    Matrix4 scaleMatrix2;                   // 0x110
    int field_150[5];                       // 0x150
    I3DFrame* collisionDummyFrame;          // 0x164
    Matrix4 scaleMatrix;                    // 0x168
    int wagonCount;                         // 0x1A8
    float wagonSpacing;                     // 0x1AC
    float metadata2;                        // 0x1B0
    float maxSpeed;                         // 0x1B4
    float metadata5;                        // 0x1B8
    float metadata6;                        // 0x1BC
    float field_1C0;                        // 0x1C0
    float lookAheadDistance;                // 0x1C4
    int field_1C8;                          // 0x1C8
    int field_1CC;                          // 0x1CC
    int field_1D0;                          // 0x1D0
    int field_1D4;                          // 0x1D4
    char isMetro;                           // 0x1D8
    char notConstructed;                    // 0x1D9
    char checked3;                          // 0x1DA
    char checked4;                          // 0x1DB
    int unknown2;                           // 0x1DC
    int vehicleEntryData;                   // 0x1E0
    Vector3* vectorArray;                   // 0x1E4
    int doorList[19];                       // 0x1E8
    TramWindowList windows;                 // 0x234
    SeatBuffer seatBuffer;                  // 0x248
    PassengerData passengerData;            // 0x250
    int field_260;                          // 0x260
    int field_264;                          // 0x264
    int field_268;                          // 0x268
    int field_26C;                          // 0x26C
    ActionData* exitActions;                // 0x270
    ActionData* enterActions;               // 0x274
    int field_278;                          // 0x278
    int field_27C;                          // 0x27C
    int field_280;                          // 0x280
    int field_284;                          // 0x284
    int passengerActiveCount;               // 0x288
    I3DFrameSound* driveSound;              // 0x28C
    I3DFrameSound* startSound;              // 0x290
    I3DFrameSound* turnSqueak;              // 0x294
    int field_298;                          // 0x298
    int field_29C;                          // 0x29C
    int startSoundId;                       // 0x2A0
    int field_2A4;                          // 0x2A4
    int somePassengerFlag;                  // 0x2A8
    int field_2AC;                          // 0x2AC
    TramPassenger conductor;                // 0x2B0
    int field_344[10];                      // 0x344
    int field_36C;                          // 0x36C

    void UpdateOscillation(int deltaTimeMs, int carId, Vector3* carCenter, Vector3* directionVector, Vector3 frontPosition, Vector3 rearPosition);
    void IncreaseActivePassengers();
    void DecreaseActivePassengers();
 
    static void InitHooks(uintptr_t gameBaseAddress);

private:
    static constexpr uintptr_t ADDR_UPDATE_OSCILLATION = 0x87D30;
    static constexpr uintptr_t ADDR_INCREASE_ACTIVE_PASSENGERS = 0x97980;
    static constexpr uintptr_t ADDR_DECREASE_ACTIVE_PASSENGERS = 0x97990;
};

static_assert(sizeof(Tram) == 0x370, "Size of Tram class is incorrect!");