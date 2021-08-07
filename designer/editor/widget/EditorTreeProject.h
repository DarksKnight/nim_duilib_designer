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
	std::wstring GetPath() {
		return _path;
	}
	bool IsDir() {
		return _is_dir;
	}
public:
	virtual void OnFill() override;
private:
	bool OnDoubleClick(ui::EventArgs* args);
private:
	std::wstring _path = L"";
	bool _is_dir = false;
};

class EditorTreeProject : public ui::Box
{
public:
	EditorTreeProject();
	~EditorTreeProject();
public:
	void LoadData();
private:
	bool OnItemMenu(ui::EventArgs* args);
private:
	void InitFolder(tinyxml2::XMLElement* element);
private:
	ui::Box* _box_tree_project;
	TreeComponent* _tree;
};