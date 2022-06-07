#pragma once
#include <SFML/Network.hpp>

struct GameDataPacket
{
	sf::Vector2i m_shootPos;
};

sf::Packet& operator <<(sf::Packet& packet, const GameDataPacket& m);
sf::Packet& operator >>(sf::Packet& packet, GameDataPacket& m);
