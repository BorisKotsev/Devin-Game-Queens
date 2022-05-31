#include "Writer.h"

Writer::Writer()
{

}

Writer::Writer(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

Writer::~Writer()
{

}

/*
* @return returns a pair, containing the with and height of the surface
*			also the texture itself
*/

pair<int2, SDL_Texture*> Writer::getText(string text, FONT fontName, COLOR colorName, int fontSize)
{
	TTF_Font* font;
	switch (fontName)
	{
	case FONT::ARCADE_CLASSIC:
		font = m_arcadeClassic.at(fontSize);
		break;
	case FONT::ADVENT_PRO:
		font = m_adventPro.at(fontSize);
		break;
	default:
		font = nullptr;
	}

	if (font == nullptr)
	{
		errorFontNotFound(to_string(int(fontName)));
	}

	const char* t = text.c_str();

	SDL_Surface* surface = TTF_RenderText_Blended(font, t, m_colors.at(colorName));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);

	int2 size;
	size.x = surface->w;
	size.y = surface->h;

	pair<int2, SDL_Texture*> returnData
		= pair<int2, SDL_Texture*>(size, texture);

	SDL_FreeSurface(surface);

	return returnData;
}

void Writer::init(string configFile)
{
	///In this function we create the main color values
	configFile = CONFIG_FOLDER + configFile;

	string tmp;

	m_arcadeClassicLocation = FONT_FOLDER + "ArcadeClassic.ttf";
	m_adventProLocation = FONT_FOLDER + "AdventPro-Bold.ttf";

	TTF_Font* m_font;

	for (int i = 11; i <= 72; i++)
	{
		m_font = TTF_OpenFont(m_arcadeClassicLocation.c_str(), i);
		m_arcadeClassic.insert(pair<int, TTF_Font*>(i, m_font));
		m_font = TTF_OpenFont(m_adventProLocation.c_str(), i);
		m_adventPro.insert(pair<int, TTF_Font*>(i, m_font));
	}

	SDL_Color color;

	color.a = Uint8(255);
	color.r = Uint8(255);
	color.g = Uint8(255);
	color.b = Uint8(255);

	m_colors.insert(pair<COLOR, SDL_Color>(COLOR::LIGHT, color));

	color.r = Uint8(0);
	color.g = Uint8(0);
	color.b = Uint8(0);

	m_colors.insert(pair<COLOR, SDL_Color>(COLOR::DARK, color));
}