#include "PacmanE.hpp"


PacmanE::PacmanE(Texture *tex) : BatchEntity {4, {64.f, 64.f}} {
	sTextures.push_back(SubTexture {tex, {456.f, 0.f}, {16.f, 16.f}});
}


