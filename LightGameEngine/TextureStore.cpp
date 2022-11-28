/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#include "TextureStore.h"

CubeTexture* TextureStore::Skybox;
CubeTexture* TextureStore::Ak;
CubeTexture* TextureStore::HumanBody;
CubeTexture* TextureStore::MetalCube;
CubeTexture* TextureStore::UpperArmCube;
CubeTexture* TextureStore::SkinCube;
CubeTexture* TextureStore::ReadPointScope;
CubeTexture* TextureStore::WoodBox;

Texture* TextureStore::Terrain;
Texture* TextureStore::Head;
Texture* TextureStore::Metal;
Texture* TextureStore::AkMag;
Texture* TextureStore::Cloth;
Texture* TextureStore::Skin;
Texture* TextureStore::AkOrtho;

void TextureStore::Init()
{
	Skybox = new CubeTexture(L"Assets/skybox.jpg");

	Texture* ak_side = Texture::LoadTexture(L"Assets/ak_side.png");
	Texture* ak_top = Texture::LoadTexture(L"Assets/ak_top.png");
	Ak = new CubeTexture(ak_side, ak_side, ak_side, ak_side, ak_top, ak_top);

	Texture* humanBodyFront = Texture::LoadTexture(L"Assets/body_front.jpg");
	Texture* humanBodySide = Texture::LoadTexture(L"Assets/body_side.jpg");
	HumanBody = new CubeTexture(humanBodyFront, humanBodyFront, humanBodySide, humanBodySide, NULL, NULL);

	Terrain = Texture::LoadTexture(L"Assets/terrain.jpg");
	Head = Texture::LoadTexture(L"Assets/head.jpg");
	Metal = Texture::LoadTexture(L"Assets/metal.jpg");
	MetalCube = new CubeTexture(Metal, Metal, Metal, Metal, Metal, Metal);
	AkMag = Texture::LoadTexture(L"Assets/ak_mag.png");
	Cloth = Texture::LoadTexture(L"Assets/cloth.jpg");
	Skin = Texture::LoadTexture(L"Assets/skin.jpg");

	SkinCube = new CubeTexture(Skin, Skin, Skin, Skin, Skin, Skin);

	Texture* upperArm = Texture::LoadTexture(L"Assets/upper_arm.png");
	UpperArmCube = new CubeTexture(upperArm, upperArm, upperArm, upperArm, Cloth, Skin);

	AkOrtho = Texture::LoadTexture(L"Assets/ak_ortho.png");

	Texture* redPointScope = Texture::LoadTexture(L"Assets/red_point.png");
	Texture* redPointScopeBack = Texture::LoadTexture(L"Assets/red_point_back.png");
	ReadPointScope = new CubeTexture(redPointScope, redPointScopeBack, Metal, Metal, Metal, Metal);

	Texture* box = Texture::LoadTexture(L"Assets/box.jpg");
	WoodBox = new CubeTexture(box, box, box, box, box, box);
}
