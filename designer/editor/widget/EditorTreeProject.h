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
	bool OnMenuOpenDir(ui::EventArgs* args, bool isDir, const std::wstring & path);
	bool OnMenuDel(ui::EventArgs* args, bool isDir, const std::wstring& path);
	bool OnMenuNewDir(ui::EventArgs* args, const std::wstring& folder);
	bool OnMenuAddDir(ui::EventArgs* args, const std::wstring & folder);
	bool OnMenuScan(ui::EventArgs* args, const std::wstring & folder);
private:
	void OnNewDir(const std::wstring& name, const std::wstring & folder);
	void OnAddDir(BOOL ret, std::wstring selectPath, const std::wstring & folder);
private:
	void InitFolder(tinyxml2::XMLElement* element);
	void DeleteDirectory(const std::wstring& folder);
private:
	ui::Box* _box_tree_project;
	TreeComponent* _tree;
};