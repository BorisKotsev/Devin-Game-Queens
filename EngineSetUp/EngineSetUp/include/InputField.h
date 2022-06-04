#pragma once

#include "IFade.h"

#include "Writer.h"

class InputField : public IFade
{
public:
	InputField();
	virtual ~InputField();
	
	void init(string configFile, string folder);
	void destroy();

	string getValue();

	void readInput();
	void stopInput();

	void update();
	void draw();

	// setters
	void setWriter(Writer* writer);
	void setText(string text);
	void hide(bool hide);

	bool readsInput();
	
	SDL_Rect getRect();
private:
	string m_value;
	// The text that we display (if we want to hide it)
	// than we present '*'
	string m_displayText;

	SDL_Renderer* m_renderer;

	bool m_readInput;
	bool m_hideText;

	SDL_Rect m_rect;

	Drawable m_textUI;

	Writer* m_writer;
};