/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
// Original file Copyright Crytek GMBH or its affiliates, used under license.

#ifndef CRYINCLUDE_CRYSCRIPTSYSTEM_SCRIPTBINDINGS_SCRIPTBIND_PHYSICS_H
#define CRYINCLUDE_CRYSCRIPTSYSTEM_SCRIPTBINDINGS_SCRIPTBIND_PHYSICS_H
#pragma once

#if ENABLE_CRY_PHYSICS
#include <IScriptSystem.h>

struct ISystem;
struct I3DEngine;
struct IPhysicalWorld;

/*!
*   <description>This class implements script-functions for Physics and decals.</description>
*   <remarks>After initialization of the script-object it will be globally accessible through scripts using the namespace "Physics".</remarks>
*   <example>Physics.CreateDecal(pos, normal, scale, lifetime, decal.texture, decal.object, rotation)</example>
*   <remarks>These function will never be called from C-Code. They're script-exclusive.</remarks>
*/
class CScriptBind_Physics
    : public CScriptableBase
{
public:
    CScriptBind_Physics(IScriptSystem* pScriptSystem, ISystem* pSystem);
    virtual ~CScriptBind_Physics();
    virtual void GetMemoryUsage(ICrySizer* pSizer) const
    {
        pSizer->AddObject(this, sizeof(*this));
    }

    //! <code>Physics.SimulateExplosion( explosionParams )</code>
    //! <description>
    //!     Simulate physical explosion.
    //!     Does not apply any game related explosion damages, this function only apply physical forces.
    //!     The parameters are passed as a table containing the elements described below.
    //! </description>
    //!     <param name="pos">Explosion epicenter position.</param>
    //!     <param name="radius">Explosion radius.</param>
    //!     <param name="direction">Explosion impulse direction.</param>
    //!     <param name="impulse_pos">Explosion impulse position (Can be different from explosion epicenter).</param>
    //!     <param name="impulse_presure">Explosion impulse presur at radius distance from epicenter.</param>
    //!     <param name="rmin">Explosion minimal radius, at this radius full pressure is applied.</param>
    //!     <param name="rmax">Explosion maximal radius, at this radius impulse pressure will be reaching zero.</param>
    //!     <param name="hole_size">Size of the explosion hole to create in breakable objects.</param>
    int SimulateExplosion(IFunctionHandler* pH, SmartScriptTable explosionParams);

    //! <code>Physics.RegisterExplosionShape( sGeometryFile, fSize, nMaterialId, fProbability, sSplintersFile, fSplintersOffset, sSplintersCloudEffect )</code>
    //! <description>
    //!     Register a new explosion shape from the static geometry.
    //!     Does not apply any game related explosion damages, this function only apply physical forces.
    //! </description>
    //!     <param name="sGeometryFile">Static geometry file name (CGF).</param>
    //!     <param name="fSize">Scale for the static geometry.</param>
    //!     <param name="nMaterialId">ID of the breakable material to apply this shape on.</param>
    //!     <param name="fProbability">Preference ratio of using this shape then other registered shape.</param>
    //!     <param name="sSplintersFile">additional non-physicalized splinters cgf to place on cut surfaces.</param>
    //!     <param name="fSplintersOffset">the lower splinters piece wrt to the upper one.</param>
    //!     <param name="sSplintersCloudEffect">particle effect when the splinters constraint breaks.</param>
    int RegisterExplosionShape(IFunctionHandler* pH, const char* sGeometryFile, float fSize, int nIdMaterial, float fProbability,
        const char* sSplintersFile, float fSplintersOffset, const char* sSplintersCloudEffect);

    //! <code>Physics.RegisterExplosionCrack( sGeometryFile, int nMaterialId )</code>
    //! <description>Register a new crack for breakable object.</description>
    //!     <param name="sGeometryFile">Static geometry file name fro the crack (CGF).</param>
    //!     <param name="nMaterialId">ID of the breakable material to apply this crack on.</param>
    int RegisterExplosionCrack(IFunctionHandler* pH, const char* sGeometryFile, int nIdMaterial);

    //bool ReadPhysicsTable(IScriptTable *pITable, PhysicsParams &sParamOut) {};

    //! <code>Physics.RayWorldIntersection( vPos, vDir, nMaxHits, iEntTypes [, skipEntityId1 [, skipEntityId2]] )</code>
    //! <description>Check if ray segment from src to dst intersect anything.</description>
    //!     <param name="vPos">Ray origin point.</param>
    //!     <param name="vDir">Ray direction.</param>
    //!     <param name="nMaxHits">Max number of hits to return, sorted in nearest to farest order.</param>
    //!     <param name="iEntTypes">Physical Entity types bitmask, ray will only intersect with entities specified by this mask (ent_all,...).</param>
    //!     <param name="skipEntityId1">(optional) Entity id to skip when checking for intersection.</param>
    //!     <param name="skipEntityId2">(optional) Entity id to skip when checking for intersection.</param>
    int RayWorldIntersection(IFunctionHandler* pH);

    //! <code>Physics.RayTraceCheck( src, dst, skipEntityId1, skipEntityId2 )</code>
    //! <description>Check if ray segment from src to dst intersect anything.</description>
    //!     <param name="src">Ray segment origin point.</param>
    //!     <param name="dst">Ray segment end point.</param>
    //!     <param name="skipEntityId1">Entity id to skip when checking for intersection.</param>
    //!     <param name="skipEntityId2">Entity id to skip when checking for intersection.</param>
    int RayTraceCheck(IFunctionHandler* pH, Vec3 src, Vec3 dst, ScriptHandle skipEntityId1, ScriptHandle skipEntityId2);

    //! <code>Physics.SamplePhysEnvironment( pt, r [, objtypes] )</code>
    //! <description>Find physical entities touched by a sphere.</description>
    //!     <param name="pt">center of sphere.</param>
    //!     <param name="r">radius of sphere.</param>
    //!     <param name="objtypes">(optional) physics entity types.</param>
    int SamplePhysEnvironment(IFunctionHandler* pH);

private:
    ISystem* m_pSystem;
    I3DEngine* m_p3DEngine;
    IPhysicalWorld* m_pPhysicalWorld;
};
#endif // ENABLE_CRY_PHYSICS

#endif // CRYINCLUDE_CRYSCRIPTSYSTEM_SCRIPTBINDINGS_SCRIPTBIND_PHYSICS_H

