#pragma once
// Created with ReClass.NET 1.2 by KN4CK3R

class Player
{
public:
	char pad_0000[24]; //0x0000
	float health; //0x0018
	float armour; //0x001C
	char pad_0020[32]; //0x0020
}; //Size: 0x0040