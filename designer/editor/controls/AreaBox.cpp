#include "../stdafx.h"
#include "AreaBox.h"

AreaBox::AreaBox():AreaBoxDelegate(this)
{
	SetFixedWidth(160);
	SetFixedHeight(80);
}

AreaBox::AreaBox(const AreaBox& box):AreaBoxDelegate(this),ui::Box(box)
{

}