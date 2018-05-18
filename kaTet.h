/*****************************************************************************
* Model: kaTet.qm
* File:  ./kaTet.h
*
* This code has been generated by QM tool (see state-machine.com/qm).
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*****************************************************************************/
/*${.::kaTet.h} ............................................................*/
#ifndef kaTet_h
#define kaTet_h
#ifdef __cplusplus
extern "C" {
#endif

#include "qhsm.h"    /* include own framework */
#include "localcharacter.h"

class Dispatcher;


/*${SMs::KaTet} ............................................................*/
typedef struct {
/* protected: */
    QHsm super;

/* public: */
    Dispatcher* dispatcher;
    QStateHandler StartState;
    KaTetLinks* KaTets;
    uint8_t KaTetNear;
} KaTet;

/* protected: */
QState KaTet_initial(KaTet * const me, QEvt const * const e);
QState KaTet_global(KaTet * const me, QEvt const * const e);
QState KaTet_has_katet(KaTet * const me, QEvt const * const e);
QState KaTet_near(KaTet * const me, QEvt const * const e);
QState KaTet_faraway(KaTet * const me, QEvt const * const e);
QState KaTet_alone(KaTet * const me, QEvt const * const e);

#ifdef DESKTOP
QState KaTet_final(KaTet * const me, QEvt const * const e);
#endif /* def DESKTOP */





typedef struct KaTetQEvt {
    QEvt super;
    size_t id;
} KaTetQEvt;


/*${SMs::KaTet_ctor} .......................................................*/
void KaTet_ctor(
    KaTet* me,
    Dispatcher* dispatcher,
    KaTetLinks* KaTets);

#ifdef __cplusplus
}
#endif
#endif /* kaTet_h */
