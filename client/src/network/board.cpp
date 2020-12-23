/**
 * client/src/network/board.cpp
 *
 * This file is part of the traintastic source code.
 *
 * Copyright (C) 2020 Reinder Feenstra
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

#include "board.hpp"
#include "connection.hpp"
#include "callmethod.hpp"

Board::Board(const QSharedPointer<Connection>& connection, Handle handle, const QString& classId) :
  Object(connection, handle, classId),
  m_getTileDataRequestId{Connection::invalidRequestId}
{
}

Board::~Board()
{
  if(m_getTileDataRequestId != Connection::invalidRequestId)
    if(auto c = connection())
      c->cancelRequest(m_getTileDataRequestId);
}

void Board::getTileData()
{
  m_getTileDataRequestId = m_connection->getTileData(*this);
}

int Board::addTile(int16_t x, int16_t y, TileRotate rotate, const QString& id, bool replace, std::function<void(const bool&, Message::ErrorCode)> callback)
{
  return callMethod(*m_connection, *getMethod("add_tile"), std::move(callback), x, y, rotate, id, replace);
}

int Board::deleteTile(int16_t x, int16_t y, std::function<void(const bool&, Message::ErrorCode)> callback)
{
  return callMethod(*m_connection, *getMethod("delete_tile"), std::move(callback), x, y);
}

void Board::getTileDataResponse(const Message& response)
{
  m_getTileDataRequestId = Connection::invalidRequestId;

  while(!response.endOfMessage())
  {
    TileLocation l = response.read<TileLocation>();
    if(static_cast<const TileData*>(response.current())->isLong())
      m_tileData.emplace(l, response.read<TileDataLong>());
    else
      m_tileData.emplace(l, response.read<TileData>());
  }

  emit tileDataChanged();
}

void Board::processMessage(const Message& message)
{
  switch(message.command())
  {
    case Message::Command::BoardTileDataChanged:
    {
      TileLocation l = message.read<TileLocation>();
      const TileData* data = static_cast<const TileData*>(message.current());
      if(!data->operator bool()) // no tile
      {
        auto it = m_tileData.find(l);
        if(it != m_tileData.end())
          m_tileData.erase(it);
      }
      else if(data->isLong())
        m_tileData[l] = message.read<TileDataLong>();
      else
        m_tileData[l] = message.read<TileData>();
      emit tileDataChanged();
      break;
    }
    default:
      Q_ASSERT(false);
      break;
  }
}