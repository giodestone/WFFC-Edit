#include "Camera.h"

#include "Game.h"

Camera::Camera()
	: isFocused(true)
	, nearestSelectedIndex(-1)
	, wasClicked(false)
{
}

void Camera::OnInitialise(ToolMain* toolMain, InputCommands* inputCommands, Game* renderer,
                          std::vector<SceneObject>* sceneGraph)
{
	this->toolMain = toolMain;
	this->inputCommands = inputCommands;
	this->renderer = renderer;
	this->sceneGraph = sceneGraph;
}

void Camera::OnMouseDown()
{
	if (!isFocused)
		return;

	if (wasClicked)
		return;
	
	currentSelection = renderer->MousePicking();

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
			currentChunkIDs.push_back(sceneGraph->at(i.second).chunk_ID);
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

int Camera::GetClosestCurrentlySelectedIndex()
{
	return nearestSelectedIndex;
}

SceneObject* Camera::GetNearestSelectedSceneObject()
{
	if (nearestSelectedIndex == -1)
		return nullptr;
	
	return &sceneGraph->at(nearestSelectedIndex);
}

std::vector<float, int> Camera::GetCurrentlySelected()
{
	return currentSelection;
}
