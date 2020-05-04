/**
 * server/src/enum/worldevent.hpp
 *
 * This file is part of the traintastic source code.
 *
 * Copyright (C) 2019-2020 Reinder Feenstra
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

#ifndef TRAINTASTIC_SERVER_ENUM_WORLDEVENT_HPP
#define TRAINTASTIC_SERVER_ENUM_WORLDEVENT_HPP

#include <enum/worldevent.hpp>
#ifndef DISABLE_LUA_SCRIPTING
  #include "../lua/enumvalues.hpp"
#endif

#ifndef DISABLE_LUA_SCRIPTING
LUA_ENUM_VALUES(WorldEvent, 7,
{
  {WorldEvent::Stop, "STOP"},
  {WorldEvent::Run, "RUN"},
  {WorldEvent::EditDisabled, "EDIT_DISABLED"},
  {WorldEvent::EditEnabled, "EDIT_ENABLED"},
  {WorldEvent::TrackPowerOff, "TRACK_POWER_OFF"},
  {WorldEvent::TrackPowerOn, "TRACK_POWER_ON"},
  {WorldEvent::EmergencyStop, "EMERGENCY_STOP"},
})
#endif

#endif