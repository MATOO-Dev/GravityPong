#pragma once

const static int windowHeight = 1000;
const static int windowWidth = 1900;
const static int gravityRadius = 200;

enum class EGameState		//defines what state the game is in
{
	Menu,
	Active,
	Paused,
	Settings
};

enum class ETheme		//defines the current theme
{
	Light,
	Dark
};