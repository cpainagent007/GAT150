#include "GameData.h"

namespace Cpain {

	std::vector<vec2> playerPoints{
		{ 3, 0 },
		{ -4, -3 },
		{ -2, 0 },
		{ -4, 3 },
		{ 3, 0 }
	};
	std::vector<vec2> enemyPoints{
	   { 8, -2 },
	   { 2, -2 },
	   { 0, 0 },
	   { 2, 2 },
	   { 8, 2 },
	   { 2, 3 },
	   { -7, 3 },
	   { -3, 0 },
	   { -7, -3 },
	   { 2, -3 },
	   { 8, -2 },
	   { 2, -3 },
	   { 0, -3 },
	   { 0, -6 },
	   { -3, 0 },
	   { 0, 6 },
	   { 0, 3 }
	};
	std::vector<vec2> bulletPoints{
		{ 1, 0 },
		{ -1, -1 },
		{ 0, 0 },
		{ -1, 1 },
		{ 1, 0 },
	};
	std::vector<vec2> bombPoints{
		{ 0, -2 },
		{ -2, -1 },
		{ -2, 1 },
		{ 0, 2 },
		{ 2, 1 },
		{ 2, -1 },
		{ 0, -2 },
		{ -1, -3 },
		{ -2, -2 },
	};
}