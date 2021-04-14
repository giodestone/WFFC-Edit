#pragma once
#include <vector>

#include "InputCommands.h"
#include "SceneObject.h"

class ToolMain;

class Camera
{
	ToolMain* toolMain;

	bool isFocused;
	
	std::vector<std::pair<float, int>> currentSelection;
	int nearestSelectedIndex;
	std::vector<int> currentChunkIDs;

	bool wasClicked;
public:
	Camera();
	~Camera();

	/// <summary>
	/// Should be called before use once to set up references.
	/// </summary>
	/// <param name="toolMain"></param>
	void OnInitialise(ToolMain* toolMain);

	/// <summary>
	/// Should be called when the MOUSEDOWN event happens. Updates current selection.
	/// </summary>
	void OnMouseDown();

	/// <summary>
	/// Should be called when the MOUSEUP event happens.
	/// </summary>
	void OnMouseUp();

	/// <summary>
	/// Should be called when WM_ACTIVATE with WM_INACTIVE on the window that the camera is part of comes in.
	/// </summary>
	void OnLostFocus();

	/// <summary>
	/// Should be called when the WM_ACTIVATE with WA_ACTIVE or WA_CLICKACTIVE command comes in for the window that the camera is a part of. By default the window is considered in focus.
	/// </summary>
	void OnRegainFocus();

	
	// Properties

	/// <summary>
	/// Get the index of the closest selected object, as it appears in SceneGraph.
	/// </summary>
	/// <returns>-1 if nothing is selected; index of the item selected in SceneGraph.</returns>
	int GetClosestCurrentlySelectedIndex();

	/// <summary>
	/// Get the Scene object that is currently selected.
	/// </summary>
	/// <returns>nullptr if nothing is selected; the pointer to the SceneObject if it is (do not modify, should modify SceneGraph collection instead if needed).</returns>
	SceneObject* GetNearestSelectedSceneObject();

	/// <summary>
	/// Get all the currently selected objects, as sorted by the distance away from camera. If distance to camera is zero the current selection was set manually.
	/// </summary>
	/// <returns>Empty if none; Currently selected objects, as sorted by the distance away from camera.</returns>
	std::vector<std::pair<float, int>> GetCurrentlySelected();

	/// <summary>
	/// Set the currently selected object based on the scene graph index.
	/// </summary>
	/// <param name="sceneGraphIndex"></param>
	void SetCurrentlySelected(int sceneGraphIndex);
};

