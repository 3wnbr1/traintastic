/**
 * server/src/hardware/input/inputs.hpp
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

#ifndef TRAINTASTIC_SERVER_HARDWARE_INPUT_INPUTS_HPP
#define TRAINTASTIC_SERVER_HARDWARE_INPUT_INPUTS_HPP

#include "input.hpp"
#include "../../utils/makearray.hpp"

#include "loconetinput.hpp"

struct Inputs
{
  static constexpr std::string_view classIdPrefix = "input.";

  static constexpr auto classList = makeArray(
    LocoNetInput::classId
  );

  static std::shared_ptr<Input> create(const std::weak_ptr<World>& world, std::string_view classId, std::string_view id);
};

#endif