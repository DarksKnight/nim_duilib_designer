#pragma once
#include "../internal/Global.h"

class EditorControlsList : public ui::VBox
{
public:
	typedef std::function<void(int id)> SelectCallback;
public:
	EditorControlsList();
	~EditorControlsList();
public:
	void LoadData(std::vector<DrawControl> controls);
public:
	void SetSelectCallback(SelectCallback callback) {
		_select_callback = callback;
	}
private:
	bool OnButtonDown(ui::EventArgs* args);
	bool OnButtonUp(ui::EventArgs* args);
private:
	SelectCallback _select_callback;
};

