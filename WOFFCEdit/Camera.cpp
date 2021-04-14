#include "Camera.h"

#include "ToolMain.h"

Camera::Camera()
	: isFocused(true)
	, nearestSelectedIndex(-1)
	, wasClicked(false)
{
}

Camera::~Camera()
{
}

void Camera::OnInitialise(ToolMain* toolMain)
{
	this->toolMain = toolMain;
}

void Camera::OnMouseDown()
{
	if (!isFocused)
		return;

	if (wasClicked)
		return;
	
	currentSelection = toolMain->GetRenderer().MousePicking();

	if (currentSelection.empty())
	{
		currentChunkIDs.clear();
		
		nearestSelectedIndex = -1;
	}
	else
	{
		currentChunkIDs.clear();
		
		nearestSelectedIndex = currentSelection.front().second;
		
		currentChunkIDs.reserve(currentSelection.size());
		for (auto& i : currentSelection)
		{
			currentChunkIDs.push_back(toolMain->GetSceneGraph().at(i.second).chunk_ID);
		}
	}
	
	wasClicked = true; // Prevent the selection from happening twice.
}

void Camera::OnMouseUp()
{
	wasClicked = false; // Allow the mouse to be clicked again.
}

void Camera::OnLostFocus()
{
	this->isFocused = false;
}

void Camera::OnRegainFocus()
{
	this->isFocused = true;
}

void Camera::SetCurrentlySelected(int sceneGraphIndex)
{
	nearestSelectedIndex = sceneGraphIndex;
	currentSelection.clear();
	currentSelection.push_back(std::make_pair(0.f, sceneGraphIndex));
}

int Camera::GetClosestCurrentlySelectedIndex()
{
	return nearestSelectedIndex;
}

SceneObject* Camera::GetNearestSelectedSceneObject()
{
	if (nearestSelectedIndex == -1)
		return nullptr;
	
	return &toolMain->GetSceneGraph().at(nearestSelectedIndex);
}

std::vector<std::pair<float, int>> Camera::GetCurrentlySelected()
{
	return currentSelection;
}
