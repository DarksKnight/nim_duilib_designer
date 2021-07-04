#pragma once
#include "../extern_ctrl/treectrl/treeitem_uistyle.h"
#include "../extern_ctrl/treectrl/treeview.h"

class ControlChunk : virtual public TreeItem<ControlData>
{
public:
	virtual std::string OnGetIUIStyleName() const override;
};

class ControlChunkUI : public ITreeItemUIStyle
{
public:
	ControlChunkUI() = default;
	virtual ~ControlChunkUI() = default;
public:
	virtual int GetHeight();
	virtual void OnFill() override;
};

class EditorTreeControls : public ui::Box
{
public:
	EditorTreeControls();
	~EditorTreeControls();
public:
	void AddNode(const std::wstring & name);
	void RemoveNode(const std::wstring& name);
private:
	void Update();
private:
	ui::Box* _box_tree_controls;
	TreeComponent* _tree;
};