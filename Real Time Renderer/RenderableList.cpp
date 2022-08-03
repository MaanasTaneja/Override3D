#include "RenderableList.h"

namespace Override
{
	void RenderableList::sortlist(glm::vec3 reference, bool farthestLast)		//Refernce is the position by which distance will be calculated
	{
		//To do when i Get to transparent objects and blending
	}

	CRenderable* RenderableList::findat(glm::vec3 position)
	{
		for (auto i : m_list)
		{
			if (i->getposition() == position)
			{
				return i;
			}
		}
	}
}