#include "../stdafx.h"
#include "EditorTreeControls.h"

EditorTreeControls::EditorTreeControls()
{
	ui::GlobalManager::FillBoxWithCache(this, L"layout/box_tree_controls.xml");
	_box_tree_controls = (ui::Box*)FindSubControl(L"box_tree_controls");
	auto task = [this]() {
		_tree = new TreeComponent;
		_box_tree_controls->Add(_tree);
		_tree->SetWindow(GetWindow(), NULL, false);
		_tree->RegisterStyleUI("ControlChunkUI", [this]() {
			ControlChunkUI* item = new ControlChunkUI;
			item->SetVirtualParent(_tree);
			ui::GlobalManager::FillBoxWithCache(item, L"layout/item_tree_controls.xml");
			item->SetWindow(_tree->GetWindow(), NULL);
			item->SetOwner(_tree);
			return std::shared_ptr< ControlChunkUI>(item);
		});
	};
	nbase::ThreadManager::PostTask(ThreadId::kThreadGlobalMisc, task);
}

EditorTreeControls::~EditorTreeControls()
{
}

void EditorTreeControls::AddNode(const std::wstring& name)
{
	auto doc = _tree->GetDoc();
	auto item = std::make_shared<ControlChunk>();
	item->SetTreeComponent(_tree);
	item->name = name;
	item->desc = name;
	item->SetItemID("111");
	doc->AddItem(item);
	auto itema = std::make_shared<ControlChunk>();
	itema->SetTreeComponent(_tree);
	itema->name = name;
	itema->desc = L"bbbbbb";
	itema->SetItemID("222");
	doc->AddItem(itema, item);
	auto itemb = std::make_shared<ControlChunk>();
	itemb->SetTreeComponent(_tree);
	itemb->name = name;
	itemb->desc = L"cccc";
	itemb->SetItemID("333");
	doc->AddItem(itemb, itema);
	_tree->Update(true);
}

void EditorTreeControls::RemoveNode(const std::wstring& name)
{

}

void EditorTreeControls::Update()
{
	_tree->Update(true);
}

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