#include "../stdafx.h"
#include "AreaLabel.h"

AreaLabel::AreaLabel():AreaLabelDelegate(this)
{
	SetFixedWidth(80);
	SetFixedHeight(30);
	SetText(L"文本");
}


AreaLabel::AreaLabel(const AreaLabel& label) :AreaLabelDelegate(this),ui::Label(label)
{

}