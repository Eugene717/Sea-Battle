#include "GameDataPacket.h"

sf::Packet& operator <<(sf::Packet& packet, const GameDataPacket& m)
{
    return packet << m.m_shootPos.x << m.m_shootPos.y;
}

sf::Packet& operator >>(sf::Packet& packet, GameDataPacket& m)
{
    return packet >> m.m_shootPos.x >> m.m_shootPos.y;
}
