/**
 * server/src/hardware/protocol/ecos/object/locomotive.cpp
 *
 * This file is part of the traintastic source code.
 *
 * Copyright (C) 2021 Reinder Feenstra
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "locomotive.hpp"
#include <cassert>
#include "../messages.hpp"

namespace ECoS {

const std::initializer_list<std::string_view> Locomotive::options = {Option::addr, Option::protocol, Option::state, Option::speedStep};

Locomotive::Locomotive(Kernel& kernel, uint16_t id)
  : Object(kernel, id)
{
  requestView();
}

bool Locomotive::receiveReply(const Reply& reply)
{
  assert(reply.objectId == m_id);

  return Object::receiveReply(reply);
}

bool Locomotive::receiveEvent(const Event& event)
{
  assert(event.objectId == m_id);

  return Object::receiveEvent(event);
}

}
