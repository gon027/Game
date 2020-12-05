#include "../include/UIDrawer.h"
#include "../include/UIObject.h"

namespace gnGame {

	UIDrawer* UIDrawer::getIns()
	{
		static UIDrawer Instance;
		return &Instance;
	}

	void UIDrawer::addUI(UIObjectPtr& _uiObject)
	{
		uiList.emplace_back(_uiObject);
	}

	void UIDrawer::removeUI(UIObjectPtr& _uiObject)
	{
		// å„Ç≈çlÇ¶ÇÈ
	}

	void UIDrawer::onUpdateUIList()
	{
		for (auto& uiObj : uiList) {
			if (!uiObj) {
				continue;
			}


		}
	}

	void UIDrawer::claerUIList()
	{
	}
}