/*
 * =====================================================================================
 *
 *       Filename:  ServerBlock.hpp
 *
 *    Description:
 *
 *        Created:  25/01/2019 00:20:34
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SERVERBLOCK_HPP_
#define SERVERBLOCK_HPP_

#include "Block.hpp"

class Client;
class Server;
class ServerPlayer;

class ServerBlock : public Block {
	public:
		ServerBlock(u32 id, const TilesDef &tiles, const std::string &name, const std::string &label)
			: Block(id, tiles, name, label) {}

		void onTick(const glm::ivec3 &, std::unordered_map<u16, ServerPlayer> &, Chunk &, World &, Server &) const;
		bool onBlockActivated(const glm::ivec3 &pos, Player &player, World &world, Client &client) const;
		void onBlockPlaced(const glm::ivec3 &pos, World &world) const;

		bool canUpdate() const { return m_onTick.valid(); }

		void setOnBlockActivated(const sol::function &function) { m_onBlockActivated = function; m_canBeActivated = m_onBlockActivated.valid(); }
		void setOnTick(const sol::function &function) { m_onTick = function; m_canUpdate = m_onTick.valid(); }
		void setOnBlockPlaced(const sol::function &function) { m_onBlockPlaced = function; }

	private:
		sol::unsafe_function m_onBlockActivated;
		sol::unsafe_function m_onTick;
		sol::unsafe_function m_onBlockPlaced;
		mutable bool m_onTickEnabled = true;
};

#endif // SERVERBLOCK_HPP_
