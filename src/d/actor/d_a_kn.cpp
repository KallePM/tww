/**
 * d_a_kn.cpp
 * NPC - Crab
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_kn.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/res/res_kn.h"

/* Unused but listed in the debug map

class daKN_HIO_c : public JORReflexible {
public:
        daKN_HIO_c() {}
        virtual ~daKN_HIO_c() {}

    void genMessage(JORMContext*);
};


daKN_HIO_c l_HIO;

static void daKN_ToFore(kn_class* i_this) {}
static void daKN_ToBack(kn_class* i_this) {}
*/

static const GXColor unused = {0xFF, 0, 0, 0x40};
#if VERSION == VERSION_DEMO
static const GXColor unused_demo[] = {
    {0xFF, 0, 0, 0xFF},
    {0, 0xFF, 0, 0xFF},
    {0, 0, 0xFF, 0xFF},
};
#endif

/* 00000078-00000120       .text daKN_Draw__FP8kn_class */
static BOOL daKN_Draw(kn_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;

    if (i_this->field_0x2CC < 0.0f) {
        return TRUE;
#if VERSION == DEMO
    } else if (i_this->field_0x2B4 == 1) {
        s16 angle_y = actor->current.angle.y;
        mDoMtx_YrotS(*calc_mtx, angle_y);
        cXyz vec1;
        cXyz vec2;
        vec1.x = 0.0f;
        vec1.y = 0.0f;
        vec1.z = 100.0f;
        MtxPosition(&vec1, &vec2);
        vec2 += actor->current.pos;
        vec1 = actor->current.pos;
        vec1.y += 50.0f;
        vec2.y += 50.0f;

        return TRUE;
#endif
    } else {
        J3DModel*  model = i_this->mpMorf->mpModel;
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
        g_env_light.setLightTevColorType(model, &actor->tevStr);
        i_this->mpMorf->updateDL();
        dSnap_RegistFig(DSNAP_TYPE_UNK56, actor, 1.0f, 1.0f, 1.0f);
    }
    return TRUE;
}

/* 00000120-00000248       .text anm_init__FP8kn_classifUcfi */
static void anm_init(kn_class* i_this, int anmResIdx, float morf, unsigned char loopMode, float playSpeed, int sndResIdx) {
    /* Nonmatching */
    if (sndResIdx >= 0) {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("KN", anmResIdx), loopMode, morf, playSpeed, 0.0f, -1.0f, dComIfG_getObjectRes("KN", sndResIdx));
    } else {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("KN", anmResIdx), loopMode, morf, playSpeed, 0.0f, -1.0f, NULL);
    }
}

/* 00000248-00000368       .text smoke_set__FP8kn_class */
static void smoke_set(kn_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;

    f32 scale = 1.0f + REG8_F(10);
    i_this->field_0x314.end();
    JPABaseEmitter* emitter = dComIfGp_particle_setToon(dPa_name::ID_COMMON_2027, &i_this->field_0x300, &actor->shape_angle, NULL, 0xb9, &i_this->field_0x314, fopAcM_GetRoomNo(actor));
    i_this->field_0x334 = emitter;
    if (i_this->field_0x334) {
        i_this->field_0x334->setMaxFrame(25);
        i_this->field_0x334->setAwayFromCenterSpeed(0.0f);
        i_this->field_0x334->setAwayFromAxisSpeed(5.0f);
        i_this->field_0x334->setRate(3.0f);
        i_this->field_0x334->setDirectionalSpeed(2.0f);
        i_this->field_0x334->setGlobalScale(JGeometry::TVec3<f32>(scale, scale, scale));
#if VERSION == DEMO
        s16 var1 = 25;
        i_this->field_0x334->setLifeTime(var1);
#else
        i_this->field_0x334->setLifeTime(25);
#endif
    }
}

/* 00000368-00000440       .text shibuki_set__FP8kn_class */
static void shibuki_set(kn_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;

    f32 scale = 0.55f + REG8_F(11);

    JPABaseEmitter* emitter = dComIfGp_particle_set(dPa_name::ID_COMMON_0023, &actor->current.pos, NULL, NULL, 0xff, NULL, -1);

    if (emitter) {
        emitter->setRate(1.5f);
        emitter->setSpread(1.0f);
        emitter->setDirectionalSpeed(4.0f);
        emitter->setMaxFrame(25);
        emitter->setGlobalScale(JGeometry::TVec3<f32>(scale, scale, scale));
    }
}

/* 00000440-00000CE8       .text kn_move__FP8kn_class */
static void kn_move(kn_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;

    f32 fVar8;
    f32 fVar1;
    f32 temp1 = 3.0f;
    f32 dist2 = 200.0f;
    f32 dist3 = 300.0f;
    f32 dist4 = 500.0f;
    fVar8 = i_this->field_0x2EC.x - actor->current.pos.x;
    fVar1 = i_this->field_0x2EC.z - actor->current.pos.z;

    switch (i_this->field_0x2BD) {
#if VERSION == DEMO
        case 0:
            anm_init(i_this, KN_BCK_WALK, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->field_0x2CC = -25.0f;
            actor->current.angle.z = -0x2000;
            ++i_this->field_0x2BD;
            break;
        case 1:
            cLib_addCalc0(&i_this->field_0x2CC, 0.3f, 1.0f);
            if (i_this->field_0x2CC > -10.0f) {
                cLib_addCalcAngleS2(&actor->current.angle.z, 0, 2, 0x200);
            }
            actor->shape_angle.z = actor->current.angle.z;
            if (abs(actor->shape_angle.z) < 256) {
                actor->current.angle.z = 0;
                actor->shape_angle.z = 0;
                i_this->field_0x2BD = 12;
            }
            break;
#endif
        case DEMO_SELECT(10, 0):
            if (cM_rnd() < 0.5f) {
                anm_init(i_this, KN_BCK_WAIT01, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            } else {
                anm_init(i_this, KN_BCK_WAIT02, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            }

            i_this->field_0x2D2 = 2048;
            fVar8 = cM_rndF(2.0f);
            i_this->field_0x2CA = fVar8 + 1.0f;
            ++i_this->field_0x2BD;
        case DEMO_SELECT(11, 1):
            cLib_addCalc0(&actor->speedF, 1.0f, 2.0f);
            if (i_this->mpMorf->checkFrame(43.0f)) {
                --i_this->field_0x2CA;
                if (i_this->field_0x2CA <= 0) {
                    i_this->field_0x2BD = DEMO_SELECT(12, 2);
                }
            }
            if (i_this->field_0x2C2[2] == 0 && fopAcM_searchPlayerDistance(actor) < dist3) {
                i_this->field_0x2BD = DEMO_SELECT(18, 8);
            }
            break;
        case DEMO_SELECT(12, 2):
            anm_init(i_this, KN_BCK_WALK, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);;
            i_this->field_0x2D0 = actor->current.angle.y + cM_rndFX(10752.0f);

            i_this->field_0x2E8 = temp1;
            if (cM_rnd() < 0.5f) {
                i_this->field_0x2E8 = -temp1;
            }
            if (i_this->field_0x2C2[2] != 0) {
                i_this->field_0x2D0 = cM_atan2s(fVar8, fVar1);
                i_this->field_0x2E8 = temp1;
            }

            {
                s16 var1 = 40;
                s16 var2 = 20;
                i_this->field_0x2C2[0] = cM_rndF(var1) + var2;
            }
            // i_this->field_0x2C2[0] = cM_rndF(40.0f) + 20.0f;

            i_this->field_0x2E4 = i_this->field_0x2E8;
            i_this->field_0x2D2 = 2048;
            i_this->field_0x2BE = false;
            ++i_this->field_0x2BD;
        case DEMO_SELECT(13, 3):
            if (fopAcM_searchPlayerDistance(actor) < dist3) {
                i_this->field_0x2BD = DEMO_SELECT(18, 8);
            } else if (i_this->field_0x2C2[2] == 0) {
                if (i_this->field_0x2BE) {
                    shibuki_set(i_this);
                    i_this->field_0x2BF = false;
                    i_this->field_0x2BD = DEMO_SELECT(15, 5);
                } else {
                    if (std::sqrtf(SQUARE(fVar8) + SQUARE(fVar1)) > dist2) {
                        i_this->field_0x2C2[1] = 20;
                        i_this->field_0x2E4 = i_this->field_0x2E8 * -1.0f;
                        i_this->field_0x2BD = DEMO_SELECT(14, 4);
                    } else if (i_this->field_0x2C2[0] == 0) {
                        i_this->field_0x2BD = DEMO_SELECT(10, 0);
                    }
                }
            }
            break;
        case DEMO_SELECT(14, 4):
            if (i_this->field_0x2C2[1] == 0) {
                if (std::sqrtf(SQUARE(fVar8) + SQUARE(fVar1)) > dist2) {
                    i_this->field_0x2D0 = cM_atan2s(fVar8, fVar1);
                    i_this->field_0x2E4 = std::fabsf(i_this->field_0x2E8);
                    i_this->field_0x2C2[1] = 8;
                } else {
                    i_this->field_0x2BD = DEMO_SELECT(10, 0);
                }
            }
            break;
        case DEMO_SELECT(15, 5):
            actor->speedF = 0.0f;
            i_this->field_0x2E4 = 0.0f;
            i_this->field_0x2C0 = false;
            i_this->field_0x2C2[0] = 20;
            anm_init(i_this, KN_BCK_PATA, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            ++i_this->field_0x2BD;
        case DEMO_SELECT(16, 6):
            if (i_this->field_0x2C2[0] == 0) {
                f32 fVar9 = -7.0f;
                if (actor->scale.x > 1.5f) {
                    fVar9 = -11.0f;
                }
                if (!i_this->field_0x2C0) {
                    if(std::fabsf(i_this->field_0x2CC - fVar9) <= 1.0f) {
                        if (i_this->field_0x2BF) {
                            i_this->field_0x314.end();
                        }
                        i_this->field_0x2CC = fVar9;
                        i_this->field_0x2C0 = true;
                        fVar9 = cM_rndF(30.0f);
                        i_this->field_0x2C2[3] = (fVar9 + 30.0f);
                    } else {
                        cLib_addCalc2(&i_this->field_0x2CC, fVar9, 0.1f, 1.0f);
                    }
                }
                if (i_this->field_0x2C0 && i_this->field_0x2C2[3] == 0 && fopAcM_searchPlayerDistance(actor) > dist4) {
                    if (i_this->field_0x2BF) {
                        i_this->field_0x300 = actor->current.pos;
                        i_this->field_0x300.y += 20.0f;
                        smoke_set(i_this);
                    } else {
                        shibuki_set(i_this);
                    }
                    anm_init(i_this, KN_BCK_PATA, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                    i_this->field_0x2BD = DEMO_SELECT(17, 7);
                }
            }
            break;
        case DEMO_SELECT(17, 7):
            cLib_addCalc0(&i_this->field_0x2CC, 0.10000000149011612, 1.0f);
            if (i_this->field_0x2CC < 0.2f) {
                if (i_this->field_0x2BF) {
                    i_this->field_0x314.end();
                }
                i_this->field_0x2CC = 0.0f;
                i_this->field_0x2C2[2] = 40;
                i_this->field_0x2BD = DEMO_SELECT(12, 2);
            }
            break;
        case DEMO_SELECT(18, 8):
            anm_init(i_this, KN_BCK_WALK, 5.0f, J3DFrameCtrl::EMode_LOOP, 2.0f, -1);
            i_this->field_0x2E8 = 40.0f;
            i_this->field_0x2C2[0] = 0;
            i_this->field_0x2C2[1] = 0;
            i_this->field_0x2C2[2] = 0;
            i_this->field_0x2D2 = 256;
            i_this->field_0x2E4 = i_this->field_0x2E8;
            i_this->field_0x2BE = false;
            i_this->field_0x2E4 = i_this->field_0x2E8;

            {
                s16 sVar5 = fopAcM_searchPlayerAngleY(actor) + 0x8000;
                s16 sVar4 = cLib_distanceAngleS(sVar5, actor->current.angle.y);

                if (sVar4 < 0x4000) {
                    i_this->field_0x2D0 = sVar5;
                } else {
                    i_this->field_0x2D0 = actor->current.angle.y;
                    sVar4 = cLib_distanceAngleS(sVar5, actor->current.angle.y) + 0x8000;
                    sVar5 = cLib_distanceAngleS(sVar5, actor->current.angle.y);
                    if (sVar5 > sVar4) {
                        i_this->field_0x2E4 = i_this->field_0x2E8 * -1.0f;
                    }
                }
            }
            ++i_this->field_0x2BD;
        case DEMO_SELECT(19, 9):
            if (i_this->field_0x338.ChkWallHit() || std::sqrtf(SQUARE(fVar8) + SQUARE(fVar1)) > dist2) {
#if VERSION != DEMO
                actor->speedF = 0.0f;
                i_this->field_0x2E4 = 0.0f;
                actor->speed.setall(0.0f);
#endif
                i_this->field_0x300.set(actor->current.pos);
                i_this->field_0x2BF = true;
                smoke_set(i_this);
                i_this->field_0x2BD = DEMO_SELECT(15, 5);
            } else if (i_this->field_0x2BE) {
                i_this->field_0x2BF = false;
                shibuki_set(i_this);
                i_this->field_0x2BD = DEMO_SELECT(15, 5);
            }
    }
    if (i_this->field_0x2BD >= DEMO_SELECT(13, 3)) {
        if (i_this->field_0x2BD < DEMO_SELECT(18, 8)) {
            i_this->field_0x2E0 = 1.0f;
            if ((s16)cLib_distanceAngleS(actor->current.angle.y, i_this->field_0x2D0) > 256) {
                i_this->field_0x2E0 = 2.0f;
            }
            cLib_addCalc2(&i_this->field_0x2DC, i_this->field_0x2E0, 0.5f, 1.0f);
            i_this->mpMorf->setPlaySpeed(i_this->field_0x2DC);
        }
        cLib_addCalcAngleS2(&actor->current.angle.y, i_this->field_0x2D0, 1, i_this->field_0x2D2);
        cLib_addCalc2(&actor->speedF, i_this->field_0x2E4, 0.3f, 1.0f);
    }
    actor->shape_angle.y = actor->current.angle.y + 0x4000;
}

#ifdef VERSION_DEMO
static void oya_kn_move(kn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    f32 fVar2 = 300.0f;
    f32 fVar1 = 500.0f;
    if ((fopAcM_searchPlayerDistance(actor) > fVar1) || (fopAcM_searchPlayerDistance(actor) < fVar2)) {
        return;
    }
    if (i_this->field_0x2C2[0] == 0) {
        fopAcM_prm_class* params = fopAcM_CreateAppend();
        params->base.position.set(actor->current.pos);
        params->base.angle = actor->current.angle;
        if (cM_rnd() < 0.5f) {
            params->base.angle.y += 0x8000;
        }
        params->base.parameters = 2;
        params->room_no = fopAcM_GetRoomNo(actor);
        fpcSCtRq_Request(fpcLy_CurrentLayer(), 0xCA, NULL, NULL, params);
        i_this->field_0x2C2[0] = 10;
        --i_this->field_0x2D4;
        if (i_this->field_0x2D4 <= 0) {
            fopAcM_delete(actor);
        }
    }
}
#endif

/* 00000CE8-00000D64       .text BG_check__FP8kn_class */
static void BG_check(kn_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;

    actor->current.pos.y -= i_this->field_0x2CC;
    actor->old.pos.y -= i_this->field_0x2CC;
    i_this->field_0x378.CrrPos(*dComIfG_Bgsp());
    actor->current.pos.y += i_this->field_0x2CC;
    actor->old.pos.y += i_this->field_0x2CC;
}

/* 00000D64-00000F80       .text daKN_Execute__FP8kn_class */
static BOOL daKN_Execute(kn_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;

    for (s32 i = 0; i < ARRAY_SSIZE(i_this->field_0x2C2); i++) {
        if(i_this->field_0x2C2[i] != 0) {
            --i_this->field_0x2C2[i];
        }
    }

#if VERSION == DEMO
    switch (i_this->field_0x2BC) {
        case 0:
            kn_move(i_this);
            break;
        case 1:
            oya_kn_move(i_this);
            break;
    }
    if (i_this->field_0x2B4 == 1) {
        return TRUE;
    }
#else
    kn_move(i_this);
#endif

    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    cMtx_XrotM(*calc_mtx, actor->current.angle.x);

    cXyz vec1;
    cXyz vec2;
    vec1.x = 0.0f;
    vec1.y = 0.0f;
    vec1.z = actor->speedF;
    MtxPosition(&vec1, &vec2);
    // i_this->speed.set(vec2.x, i_this->speed.y + i_this->gravity, vec2.z);
    actor->speed.x = vec2.x;
    actor->speed.z = vec2.z;

#if VERSION == DEMO
    if (actor->speed.y > -80.0f) {
        actor->speed.y -= 3.0f;
    }
#else
    actor->speed.y += actor->gravity;
    if (actor->speed.y < -20.0f) {
        actor->speed.y = -20.0f;
    }
#endif

    fopAcM_posMove(actor, NULL);
    BG_check(i_this);

    if (i_this->field_0x378.ChkGroundHit()) {
        fopAcM_getGroundAngle(actor, &i_this->field_0x2F8);

#if VERSION == DEMO
        if (i_this->field_0x2BC == 0 && (i_this->field_0x2BD == 13 || i_this->field_0x2BD == 19) &&
#else
        if ((i_this->field_0x2BD == 3 || i_this->field_0x2BD == 9) &&
#endif
            i_this->field_0x378.GetGroundH() != -G_CM3D_F_INF && dComIfG_Bgsp()->GetAttributeCode(i_this->field_0x378.m_gnd) == dBgS_Attr_WATER_e)
        {
            i_this->field_0x2BE = true;
        }
    }

    i_this->mpMorf->play(NULL, 0, 0);
    J3DModel* model = i_this->mpMorf->getModel();
    mDoMtx_stack_c::transS(actor->current.pos);
    mDoMtx_stack_c::XrotM(i_this->field_0x2F8.x);
    mDoMtx_stack_c::ZrotM(i_this->field_0x2F8.z);
    mDoMtx_stack_c::YrotM(actor->shape_angle.y);
    mDoMtx_stack_c::XrotM(actor->shape_angle.x);
    mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
    model->setBaseScale(actor->scale);
    mDoMtx_stack_c::transM(0.0f, i_this->field_0x2CC, 0.0f);
    model->setBaseTRMtx(mDoMtx_stack_c::get());

    return TRUE;
}

/* 00000F80-00000F88       .text daKN_IsDelete__FP8kn_class */
static BOOL daKN_IsDelete(kn_class*) {
    return TRUE;
}

/* 00000F88-00000FD8       .text daKN_Delete__FP8kn_class */
static BOOL daKN_Delete(kn_class* i_this) {
    /* Nonmatching */
    i_this->field_0x314.end();
    dComIfG_resDeleteDemo(&i_this->mPhase, "KN");
    return TRUE;
}

/* 00000FD8-000010E0       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_this) {
    /* Nonmatching */
    kn_class* actor = (kn_class*) i_this;

    actor->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("KN", KN_BDL_KN),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("KN", KN_BCK_PATA),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x11000002
    );

    if (!actor->mpMorf || !actor->mpMorf->getModel()) {
        return FALSE;
    }
    return TRUE;
}

/* 000010E0-000012B0       .text daKN_Create__FP10fopAc_ac_c */
static cPhs_State daKN_Create(fopAc_ac_c* i_this) {
    /* Nonmatching */
    kn_class* a_this = (kn_class*)i_this;

#if VERSION > DEMO
    fopAcM_SetupActor(i_this, kn_class);
#endif
    cPhs_State state = dComIfG_resLoad(&a_this->mPhase, "KN");

    if (state == cPhs_COMPLEATE_e) {
#if VERSION == DEMO
        fopAcM_SetupActor(&a_this->actor, kn_class);
#endif
        a_this->field_0x2B4 = fopAcM_GetParam(i_this);
        a_this->field_0x2B5 = fopAcM_GetParam(i_this) >> 8;
        a_this->field_0x2EC = i_this->current.pos;

#if VERSION == DEMO
        if (a_this->field_0x2B4 == 1) {
            a_this->field_0x2D4 = a_this->field_0x2B5;
            if (a_this->field_0x2B5 == 255 || a_this->field_0x2B5 == 0) {
                a_this->field_0x2D4 = 100;
            }
            a_this->field_0x2BC = 1;
            a_this->field_0x2BD = 20;
            return state;
        }
#endif

        if (!fopAcM_entrySolidHeap(i_this, useHeapInit, 0x2860)){
            return cPhs_ERROR_e;
        }
        fopAcM_SetMtx(i_this, a_this->mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(i_this, -30.0f, -0.0f, -30.0f, 30.0f, 60.0f, 30.0f);
        i_this->gravity = -5.0f;
        i_this->attention_info.flags = 0;
        a_this->field_0x338.SetWall(10.0f, 30.0f);
        a_this->field_0x378.Set(fopAcM_GetPosition_p(i_this), fopAcM_GetOldPosition_p(i_this), i_this, 1, &a_this->field_0x338, fopAcM_GetSpeed_p(i_this));
        i_this->scale.setall(1.5f);
#if VERSION == DEMO
        if (a_this->field_0x2B4 == 2) {
            i_this->current.angle.z = -0x2000;
            a_this->field_0x2CC = -25.0f;
            a_this->field_0x2BC = 0;
            a_this->field_0x2BD = 0;
        } else {
#endif
            if (cM_rnd() < 0.5f) {
                i_this->scale.setall(2.5f);
            }
#if VERSION == DEMO
            a_this->field_0x2BC = 0;
            a_this->field_0x2BD = 10;
        }
#else
        a_this->field_0x2BD = 0;
        daKN_Execute(a_this);
#endif
    }
    return state;
}

static actor_method_class l_daKN_Method = {
    (process_method_func)daKN_Create,
    (process_method_func)daKN_Delete,
    (process_method_func)daKN_Execute,
    (process_method_func)daKN_IsDelete,
    (process_method_func)daKN_Draw,
};

actor_process_profile_definition g_profile_KN = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KN,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kn_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KN,
    /* Actor SubMtd */ &l_daKN_Method,
#if VERSION == DEMO
    /* Status       */ fopAcStts_CULL_e | fopAcStts_NOCULLEXEC_e | fopAcStts_UNK40000_e,
#else
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
#endif
    /* Group        */ fopAc_ENV_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
