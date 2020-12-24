#ifndef UIDRAWER_H
#define UIDRAWER_H

#include <memory>
#include <vector>

namespace gnGame {

	class UIObject;
	using UIObjectPtr = UIObject*;
	using UIList = std::vector<UIObjectPtr>;

	// UI‚ð•`‰æ‚·‚éƒNƒ‰ƒX
	class UIDrawer {
	public:
		static UIDrawer* getIns();

	public:
		~UIDrawer() = default;

		void addUI(UIObjectPtr _uiObject);

		void removeUI(UIObjectPtr _uiObject);

		void OndrawUIList();

		void claerUIList();

		size_t getListSize() {
			return uiList.size();
		}

	private:
		UIDrawer() : uiList() {};
		UIDrawer(const UIDrawer&);
		UIDrawer& operator= (const UIDrawer&);

	private:
		UIList uiList;
	};
}

#endif // !UIDRAWER_H