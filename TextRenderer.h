/*
-----------------------------------------------------------------------------
Filename:    TextRenderer.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/

http://www.ogre3d.org/tikiwiki/Simple+Text+Output&structure=Cookbook
-----------------------------------------------------------------------------
*/
#ifndef __TextRenderer_h_
#define __TextRenderer_h_

#include <Ogre.h>
#include <OgreSingleton.h>


class TextRenderer : public Ogre::Singleton<TextRenderer>
{
private:
	Ogre::OverlayManager*    _overlayMgr;
	Ogre::Overlay*           _overlay;
	Ogre::OverlayContainer*  _panel;

public:
    TextRenderer();
	~TextRenderer();

	void addPanel(const std::string& a_sPanelID);
	void showPanel(const std::string& a_sPanelID);
	void hidePanel(const std::string& a_sPanelID);


    void addTextBox(const std::string& a_sPanelID,
                    const std::string& ID,
                    const std::string& text,
                    Ogre::Real x, Ogre::Real y,
                    Ogre::Real width, Ogre::Real height,
                    const Ogre::ColourValue& color,
                    const std::string& size,
                    const std::string& font,
                    const std::string& alignement);


	void addTextBox(
		const std::string& ID,
		const std::string& text,
		Ogre::Real x, Ogre::Real y,
		Ogre::Real width, Ogre::Real height,
		const Ogre::ColourValue& color = Ogre::ColourValue(1.0, 1.0, 1.0, 1.0),
		const std::string& size = "16",
		const std::string& font = "MyFont",
		const std::string& alignement = "left");

	void removeTextBox(const std::string& ID);

	void setText(const std::string& ID, const std::string& Text);
};


#endif // #ifndef __TextRenderer_h_
