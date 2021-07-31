#pragma once
#include "../extern_ctrl/treectrl/treeitem_uistyle.h"
#include "../extern_ctrl/treectrl/treeview.h"

class DirChunk : virtual public TreeItem<DirData>
{
public:
	virtual std::string OnGetIUIStyleName() const override;
};

class DirChunkUI : public ITreeItemUIStyle
{
public:
	DirChunkUI() = default;
	virtual ~DirChunkUI() = default;
public:
	virtual int GetHeight();
	virtual void OnFill() override;
};

class EditorTreeProject : public ui::Box
{
public:
	EditorTreeProject();
	~EditorTreeProject();
public:
	void LoadData();
private:
	void InitFolder(tinyxml2::XMLElement* element);
private:
	ui::Box* _box_tree_project;
	TreeComponent* _tree;
};