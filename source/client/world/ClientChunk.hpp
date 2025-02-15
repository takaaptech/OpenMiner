/*
 * =====================================================================================
 *
 *  OpenMiner
 *
 *  Copyright (C) 2018-2020 Unarelith, Quentin Bazin <openminer@unarelith.net>
 *  Copyright (C) 2019-2020 the OpenMiner contributors (see CONTRIBUTORS.md)
 *
 *  This file is part of OpenMiner.
 *
 *  OpenMiner is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  OpenMiner is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with OpenMiner; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * =====================================================================================
 */
#ifndef CLIENTCHUNK_HPP_
#define CLIENTCHUNK_HPP_

#include <gk/gl/Drawable.hpp>

#include "Chunk.hpp"
#include "ChunkMeshLayer.hpp"
#include "Config.hpp"
#include "Dimension.hpp"

class ClientWorld;
class TextureAtlas;

class ClientChunk : public Chunk {
	public:
		ClientChunk(s32 x, s32 y, s32 z, const Dimension &dimension, ClientWorld &world);

		void update() final;
		void process() final;

		void onBlockPlaced(int x, int y, int z, const Block &block) override;

		const Dimension &dimension() const { return m_dimension; }

		bool isReadyForMeshing() const { return m_isReadyForMeshing; }
		void setReadyForMeshing(bool isReadyForMeshing) { m_isReadyForMeshing = isReadyForMeshing; }

		bool isTooFar() const { return m_isTooFar; }
		void setTooFar(bool isTooFar) { m_isTooFar = isTooFar; }

		bool hasBeenDrawn() const { return m_hasBeenDrawn; }
		void setHasBeenDrawn(bool hasBeenDrawn) { m_hasBeenDrawn = hasBeenDrawn; }

		bool areAllNeighboursTooFar() const;

		const gk::VertexBuffer &getVertexBuffer(u8 layer) { return m_vbo[layer]; }

		std::size_t getVerticesCount(u8 layer) const { return m_verticesCount[layer]; }
		void setVerticesCount(u8 layer, std::size_t count) { m_verticesCount[layer] = count; }

		const gk::VertexBuffer &getVBO(u8 layer) const { return m_vbo[layer]; }

		int debugTimesReceived = 0; // Only used by Minimap

		static u32 chunkUpdatesPerSec;
		static u32 chunkUpdateCounter;
		static u64 chunkUpdateTime;

	private:
		ClientWorld &m_world;

		const Dimension &m_dimension;

		std::array<gk::VertexBuffer, ChunkMeshLayer::Count> m_vbo{};
		std::array<std::size_t, ChunkMeshLayer::Count> m_verticesCount{};

		bool m_isReadyForMeshing = false;
		bool m_isTooFar = false;
		bool m_hasBeenDrawn = false;
};

#endif // CLIENTCHUNK_HPP_
