// Trunnion BC kinematics stepper pulse time generation
//
// Copyright (C) 2024- Flummoxed <gahlerbj@gmail.com>
// based on work by @_geek_gear_ <gear2nd.droid@gmail.com>
//
// This file may be distributed under the terms of the GNU GPLv3 license.

#include <math.h> // sqrt
#include <stdlib.h> // malloc
#include <string.h> // memset
#include "compiler.h" // __visible
#include "itersolve.h" // struct stepper_kinematics
#include "trapq.h" // move_get_coord

static double
turntable_stepper_plus_calc_position(struct stepper_kinematics *sk, struct move *m
                                  , double move_time)
{
    struct coord c = move_get_coord(m, move_time);
    return c.x + c.z;
}

static double
turntable_stepper_minus_calc_position(struct stepper_kinematics *sk, struct move *m
                                   , double move_time)
{
    struct coord c = move_get_coord(m, move_time);
    return c.x - c.z;
}

static double
turntable_stepper_y_calc_position(struct stepper_kinematics *sk, struct move *m
                             , double move_time)
{
    return move_get_coord(m, move_time).y;
}

static double
turntable_stepper_c_calc_position(struct stepper_kinematics *sk, struct move *m
                             , double move_time)
{
    return move_get_coord(m, move_time).c;
}

struct stepper_kinematics * __visible
turntable_stepper_alloc(char type)
{
    struct stepper_kinematics *sk = malloc(sizeof(*sk));
    memset(sk, 0, sizeof(*sk));
    if (type == 'x')
        sk->calc_position_cb = turntable_stepper_plus_calc_position;
    else if (type == 'z')
        sk->calc_position_cb = turntable_stepper_minus_calc_position;
    else if (type == 'y')
        sk->calc_position_cb = turntable_stepper_y_calc_position;
    else if (type == 'c')
        sk->calc_position_cb = turntable_stepper_c_calc_position;
    sk->active_flags = AF_X | AF_Y | AF_Z | AF_C;
    return sk;
}
