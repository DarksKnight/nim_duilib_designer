#include "../stdafx.h"
#include "EditorTreeControls.h"

std::string ControlChunk::OnGetIUIStyleName() const
{
	return "ControlChunkUI";
}

int ControlChunkUI::GetHeight()
{
	return 30;
}

void ControlChunkUI::OnFill()
{
	auto&& data = std::dynamic_pointer_cast<ControlData>(doc_item_);
	if (!data) {
		return;
	}
	ui::Label* lbDesc = (ui::Label*)FindSubControl(L"lb_desc");
	lbDesc->SetText(data->desc);
}

EditorTreeControls::EditorTreeControls()
{
	ui::GlobalManager::FillBoxWithCache(this, L"layout/box_tree_controls.xml");
	_box_tree_controls = (ui::Box*)FindSubControl(L"box_tree_controls");
	nbase::ThreadManager::PostTask(ThreadId::kThreadGlobalMisc, ToWeakCallback([this]() {
		_tree = new TreeComponent;
		_box_tree_controls->Add(_tree);
		_tree->SetWindow(GetWindow(), this, false);
		_tree->RegisterStyleUI("ControlChunkUI", [this]() {
			ControlChunkUI* item = new ControlChunkUI;
			ui::GlobalManager::FillBoxWithCache(item, L"layout/item_tree_controls.xml");
			item->SetVirtualParent(_tree);
			item->SetWindow(_tree->GetWindow(), NULL);
			item->SetOwner(_tree);
			return std::shared_ptr<ControlChunkUI>(item);
			});
		}));
}

EditorTreeControls::~EditorTreeControls()
{
}

void EditorTreeControls::AddNode(const ControlData& ctrlData, DelegateData* targetData, DelegateData* parentData)
{
	auto doc = _tree->GetDoc();
	auto item = std::make_shared<ControlChunk>();
	item->SetTreeComponent(_tree);
	item->name = ctrlData.name;
	item->desc = ctrlData.desc;
	item->SetItemID(nbase::IntToString(targetData->GetId()));
	if (!parentData) {
		doc->AddItem(item);
	}
	else {
		auto parentItem = doc->GetItem(nbase::IntToString(parentData->GetId()));
		if (parentItem) {
			doc->AddItem(item, parentItem);
		}
		else {
			doc->AddItem(item);
		}
	}
}

void EditorTreeControls::RemoveNode(const std::wstring& name)
{

}

void EditorTreeControls::Update()
{
	_tree->Update(true);
}