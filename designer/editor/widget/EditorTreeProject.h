#pragma once
#include "../extern_ctrl/treectrl/treeitem_uistyle.h"
#include "../extern_ctrl/treectrl/treeview.h"

class DirChunk : virtual public TreeItem<DirData>
{
public:
	std::string OnGetIUIStyleName() const {
		return "DirChunkUI";
	}
};

class DirChunkUI : public ITreeItemUIStyle
{
public:
	typedef std::function<void(const std::wstring& path)> SelectedCallback;
public:
	DirChunkUI() {
		ui::GlobalManager::FillBoxWithCache(this, L"layout/item_tree_dir.xml");
	}
	virtual ~DirChunkUI() = default;
public:
	int GetHeight() {
		return 20;
	}
	virtual void OnFill() override;
public:
	void SetSelectedCallback(SelectedCallback callback) {
		_selected_callback = callback;
	}
private:
	bool OnDoubleClick(ui::EventArgs* args);
private:
	SelectedCallback _selected_callback;
};

class EditorTreeProject : public ui::Box
{
public:
	EditorTreeProject();
	~EditorTreeProject();
public:
	void LoadData();
public:
	std::wstring GetSelectedPath() {
		return _selected_path;
	}
private:
	void InitFolder(tinyxml2::XMLElement* element);
private:
	ui::Box* _box_tree_project;
	TreeComponent* _tree;
private:
	std::wstring _selected_path = L"";
};