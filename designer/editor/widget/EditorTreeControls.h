#pragma once
#include "../extern_ctrl/treectrl/treeitem_uistyle.h"
#include "../extern_ctrl/treectrl/treeview.h"

class ControlChunk : virtual public TreeItem<ControlData>
{
public:
	std::string OnGetIUIStyleName() const {
		return "ControlChunkUI";
	}
};

class ControlChunkUI : public ITreeItemUIStyle
{
public:
	ControlChunkUI() {
		ui::GlobalManager::FillBoxWithCache(this, L"layout/item_tree_controls.xml");
	}
	virtual ~ControlChunkUI() = default;
public:
	int GetHeight() {
		return 20;
	}
	virtual void OnFill() override;
};

class EditorTreeControls : public ui::Box
{
public:
	EditorTreeControls();
	~EditorTreeControls();
public:
	void AddNode(const ControlData & ctrlData, DelegateData* targetData, DelegateData* parentData = NULL);
	void RemoveNode(const std::wstring& name);
	void Update();
private:
	ui::Box* _box_tree_controls;
	TreeComponent* _tree;
};