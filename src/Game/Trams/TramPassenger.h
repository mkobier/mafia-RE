#pragma once
#include <cstdint>
#include "../Math/Vector3.h"

struct I3DFrameModel;
struct AnimFlagContainer;
struct CollisionTreeData;

struct Matrix4x4
{
    float m[16];
};

class TramPassenger
{
public:

    int passenger_flag;          
    I3DFrameModel* frame_model;        
    AnimFlagContainer* anim_container;
    int should_keep_sitting;
    int animation_number;
    int new_animation_number;
    unsigned int wagon_index;
    int seat_index;
    int field_20;
    Vector3 target_position;
    Vector3 look_target;
    int fear_timer;
    int max_fear_time;
    int old_passenger_flag;
    int old_animation_number;
    Matrix4x4 inverse_global_matrix;
    int field_8C;
    CollisionTreeData* collision_data;

    TramPassenger* CreateEmpty();

    static void InitHooks(uintptr_t gameBaseAddress);

private:

    static constexpr uintptr_t ADDR_CREATE_EMPTY = 0x832E0;
};

static_assert(sizeof(TramPassenger) == 0x94, "Size of TramPassenger class is incorrect!");