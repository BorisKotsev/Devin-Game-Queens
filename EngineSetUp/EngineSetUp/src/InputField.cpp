#include "InputField.h"

#include "World.h"
extern World world;

InputField::InputField()
{
}

InputField::~InputField()
{
}

void InputField::init(string configFile, string folder)
{
	m_writer = world.m_presenter.getWriter();

	configFile = CONFIG_FOLDER + UI_FOLDER + folder + configFile;
	
	string tmp;
	string backgroundPath, foregroundPath;

	int opacityPerFrame;

	fstream stream;
	stream.open(configFile);

	stream >> tmp >> backgroundPath;
	stream >> tmp >> foregroundPath;
	stream >> tmp >> m_rect.x >> m_rect.y >> m_rect.w >> m_rect.h;
	stream >> tmp >> m_textUI.rect.x >> m_textUI.rect.y >> m_textUI.rect.h;

	stream >> tmp >> opacityPerFrame;

	stream.close();

	setOpacityPerFrame(opacityPerFrame);

	backgroundPath = UI_FOLDER + backgroundPath;
	foregroundPath = UI_FOLDER + foregroundPath;

	m_background.texture = loadTexture(backgroundPath);
	m_foreground.texture = loadTexture(foregroundPath);

	m_background.rect = m_rect;
	m_foreground.rect = m_rect;
}

void InputField::destroy()
{
}

string InputField::getValue()
{
	return m_value;
}

void InputField::readInput()
{
	m_readInput = true;
}

void InputField::stopInput()
{
	m_readInput = false;
}

void InputField::update()
{		
	if (m_readInput)
	{
		setText(world.m_inputManager.getTextInput());
	}

	if (m_readInput || m_value.size() > 0)
	{
		decreaseOpacity();
	}
	else
	{
		increaseOpacity();
	}

	if (m_value.length() > 0)
	{
		pair<int2, SDL_Texture*> value = m_writer->getText(m_value, FONT::ADVENT_PRO, COLOR::LIGHT, 30);
		
		// Destroy the old texture before getting the new one
		if (m_textUI.texture != nullptr)
		{
			SDL_DestroyTexture(m_textUI.texture);
		}

		m_textUI.texture = value.second;
		m_textUI.rect.w = value.first.x;
		m_textUI.rect.h = value.first.y;
	}
}

void InputField::draw()
{
	drawObject(m_background);

	if (m_value.length() > 0)
	{
		drawObject(m_textUI);
	}
}

void InputField::setWriter(Writer* writer)
{
	m_writer = writer;
}

void InputField::setText(string text)
{
	if (text == "")
	{
		text = "0";
	}
	if (m_value != text)
	{
		auto res = m_writer->getText(text, FONT::ADVENT_PRO, COLOR::LIGHT, 30);
		m_textUI.rect.x = m_rect.x + (m_rect.w - res.first.x) / 2;
		m_textUI.rect.y = m_rect.y + (m_rect.h - res.first.y) / 2;
		m_textUI.rect.w = res.first.x;
		m_textUI.rect.h = res.first.y;
		m_textUI.texture = res.second;

		m_value = text;

		if (m_hideText)
		{
			m_displayText = "";

			for (int i = 0; i < m_value.length(); i++)
			{
				m_displayText += "*";
			}
		}
		else
		{
			m_displayText = m_value;
		}
	}
}

void InputField::hide(bool hide)
{
	m_hideText = hide;
}

SDL_Rect InputField::getRect()
{
	return m_rect;
}

bool InputField::readsInput()
{
	return m_readInput;
}