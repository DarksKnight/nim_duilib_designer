#include "../stdafx.h"
#include "AreaLabel.h"

AreaLabel::AreaLabel():AreaLabelDelegate(this)
{
	SetFixedWidth(50);
	SetFixedHeight(50);
}


AreaLabel::AreaLabel(const AreaLabel& label) :AreaLabelDelegate(this),ui::Label(label)
{

}