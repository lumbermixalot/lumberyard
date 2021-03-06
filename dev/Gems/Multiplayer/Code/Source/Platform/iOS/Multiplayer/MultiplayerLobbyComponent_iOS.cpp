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

#include "Multiplayer_precompiled.h"
#include <AzCore/Component/EntityId.h>
#include <Multiplayer/MultiplayerLobbyServiceWrapper/MultiplayerLobbyServiceWrapper.h>

namespace Multiplayer
{
    class MultiplayerLobbyServiceWrapper;
}

namespace GridMate
{
    struct CarrierDesc;
}

namespace Platform
{
    bool ListServers(const AZStd::string& actionName, const AZ::EntityId& entityId, Multiplayer::MultiplayerLobbyServiceWrapper*& multiplayerLobbyServiceWrapper)
    {
        AZ_UNUSED(actionName);
        AZ_UNUSED(entityId);
        AZ_UNUSED(multiplayerLobbyServiceWrapper);
        return false;
    }

    void InitCarrierDesc(GridMate::CarrierDesc& carrierDesc)
    {
        // Force the IP Version regardless of what was configured
        carrierDesc.m_familyType = GridMate::Driver::BSD_AF_INET6;
    }
}
