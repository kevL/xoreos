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

/** @file
 *  The context handling the gameplay in Neverwinter Nights 2.
 */

#include <cassert>

#include "src/common/error.h"
#include "src/common/configman.h"
#include "src/common/filepath.h"
#include "src/common/filelist.h"

#include "src/events/events.h"

#include "src/engines/nwn2/game.h"
#include "src/engines/nwn2/nwn2.h"
#include "src/engines/nwn2/console.h"
#include "src/engines/nwn2/campaign.h"
#include "src/engines/nwn2/module.h"
#include "src/engines/nwn2/area.h"

namespace Engines {

namespace NWN2 {

Game::Game(NWN2Engine &engine, ::Engines::Console &console) :
	_engine(&engine), _campaign(0), _console(&console) {

}

Game::~Game() {
	delete _campaign;
}

Campaign &Game::getCampaign() {
	assert(_campaign);

	return *_campaign;
}

Module &Game::getModule() {
	assert(_campaign && _campaign->getModule());

	return *_campaign->getModule();
}

void Game::run() {
	_campaign = new Campaign(*_console);

	while (!EventMan.quitRequested()) {
		runCampaign();
	}

	delete _campaign;
	_campaign = 0;
}

void Game::runCampaign() {
	_campaign->load("neverwinter nights 2 campaign");

	_campaign->run();

	_campaign->clear();
}

void Game::playMusic(const Common::UString &music) {
	if (!_campaign || !_campaign->getModule() || !_campaign->getModule()->isRunning())
		return;

	Area *area = _campaign->getModule()->getCurrentArea();
	if (!area)
		return;

	area->playAmbientMusic(music);
}

void Game::stopMusic() {
	if (!_campaign || !_campaign->getModule() || !_campaign->getModule()->isRunning())
		return;

	Area *area = _campaign->getModule()->getCurrentArea();
	if (!area)
		return;

	area->stopAmbientMusic();
}

void Game::getCampaigns(std::vector<Common::UString> &campaigns) {
	campaigns.clear();

	const Common::UString directory = ConfigMan.getString("NWN2_campaignDir");

	const Common::FileList camFiles(directory, -1);

	for (Common::FileList::const_iterator c = camFiles.begin(); c != camFiles.end(); ++c) {
		if (!Common::FilePath::getFile(*c).equalsIgnoreCase("campaign.cam"))
			continue;

		const Common::UString cam = Common::FilePath::relativize(directory, Common::FilePath::getDirectory(*c));
		if (cam.empty() || (cam == "."))
			continue;

		campaigns.push_back(cam);
	}
}

void Game::getModules(std::vector<Common::UString> &modules) {
	modules.clear();

	const Common::UString directory = ConfigMan.getString("NWN2_moduleDir");

	const Common::FileList modFiles(directory);

	for (Common::FileList::const_iterator m = modFiles.begin(); m != modFiles.end(); ++m) {
		if (!Common::FilePath::getExtension(*m).equalsIgnoreCase(".mod"))
			continue;

		modules.push_back(Common::FilePath::getStem(*m));
	}
}

} // End of namespace NWN2

} // End of namespace Engines