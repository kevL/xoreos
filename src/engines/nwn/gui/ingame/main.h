/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * xoreos is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * xoreos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with xoreos. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file engines/nwn/gui/ingame/main.h
 *  The NWN ingame main menu.
 */

#ifndef ENGINES_NWN_GUI_INGAME_MAIN_H
#define ENGINES_NWN_GUI_INGAME_MAIN_H

#include "engines/nwn/gui/gui.h"

namespace Engines {

namespace NWN {

/** The NWN ingame main menu. */
class IngameMainMenu : public GUI {
public:
	IngameMainMenu();
	~IngameMainMenu();

protected:
	void initWidget(Widget &widget);

	void callbackActive(Widget &widget);

private:
	GUI *_game;
	GUI *_video;
	GUI *_sound;
	GUI *_controls;

	GUI *_quitPrompt;
};

} // End of namespace NWN

} // End of namespace Engines

#endif // ENGINES_NWN_GUI_INGAME_MAIN_H
