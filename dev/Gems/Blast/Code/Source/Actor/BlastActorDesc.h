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
#pragma once

#include <AzCore/std/containers/vector.h>
#include <AzFramework/Physics/RigidBody.h>

namespace Nv::Blast
{
    class TkActor;
} // namespace Nv::Blast

namespace Blast
{
    class BlastFamily;

    //! Data required to create a BlastActor.
    struct BlastActorDesc
    {
        BlastFamily* m_family;
        Nv::Blast::TkActor* m_tkActor;
        Physics::MaterialId m_physicsMaterialId;
        AZ::Vector3 m_parentLinearVelocity = AZ::Vector3::CreateZero();
        AZ::Vector3 m_parentCenterOfMass = AZ::Vector3::CreateZero();
        Physics::RigidBodyConfiguration m_bodyConfiguration; //! Either rigid dynamic or rigid static
        AZStd::vector<uint32_t> m_chunkIndices; //! Chunks that are going to simulate this actor.
        AZStd::shared_ptr<AZ::Entity> m_entity; //! Entity that the actor should use to simulate rigid body
        bool m_isStatic = false; //! Denotes whether actor should be simulated by a static or dynamic rigid body.
        bool m_isLeafChunk = false; //! Denotes whether this actor represented by a single leaf chunk.
    };
} // namespace Blast
