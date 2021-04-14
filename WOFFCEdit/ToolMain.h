#pragma once

#include <afxext.h>
#include "pch.h"
#include "Game.h"
#include "sqlite3.h"
#include "SceneObject.h"
#include "InputCommands.h"
#include <vector>
#include "Selection.h"

#include "ObjectPropertiesDialog.h"


class ToolMain
{
	static ToolMain* instance;
	static bool isInitialised;

	
	Game d3dRenderer; //Instance of D3D rendering system for our tool
	Selection selection;
	InputCommands toolInputCommands; //input commands that we want to use and possibly pass over to the renderer
	CRect windowRect; //Window area rectangle. 
	char keyArray[256];
	sqlite3* databaseConnection; //sqldatabase handle

	int width; //dimensions passed to directX
	int height;
	int currentChunk; //the current chunk of thedatabase that we are operating on.  Dictates loading and saving. 

	ObjectPropertiesDialog* objectPropertiesDialog;

	std::vector<SceneObject> sceneGraph;	//our scenegraph storing all the objects in the current chunk
	ChunkObject	chunk;//our landscape chunk
	int selectedObject;	//ID of current Selection

	HWND mainWindowHwnd;

	bool isFocused;
	

	// Methods
	void OnContentAdded();

	void UpdateInputCommands();

	// Callbacks for events.
	void OnMouseDown();
	void OnMouseUp();

public:	
	ToolMain();
	~ToolMain();

	static ToolMain* GetInstance();
	static bool IsInitialised();
	
	// Properties

	/// <summary>
	/// Get input commands.
	/// </summary>
	InputCommands& GetInputCommands() { return toolInputCommands; }
	
	/// <summary>
	/// Get a reference to the selection.
	/// </summary>
	/// <returns>The selection object.</returns>
	Selection& GetSelection() { return selection; }

	/// <summary>
	/// Get a reference to the renderer.
	/// </summary>
	/// <returns></returns>
	Game& GetRenderer() { return d3dRenderer; }

	/// <summary>
	/// Get the scene graph.
	/// </summary>
	/// <returns>A reference to the scene graph.</returns>
	std::vector<SceneObject>& GetSceneGraph() { return sceneGraph; }

	/// <summary>
	/// Get current selection index.
	/// </summary>
	/// <returns>-1 if nothing is selected; the index of the item in the Scene Graph.</returns>
	/// <seealso cref="Camera::GetClosestCurrentlySelectedIndex"/>
	int	GetClosestCurrentlySelectedIndex();

	/// <summary>
	/// Get object properties dialog.
	/// </summary>
	/// <returns>nullptr if not set; reference to the object if it is.</returns>
	ObjectPropertiesDialog* GetObjectPropertiesDialog() { return objectPropertiesDialog; }

	/// <summary>
	/// Set reference to the object properties dialog.
	/// </summary>
	/// <param name="objectPropertiesDialog"></param>
	void SetObjectPropertiesDialogReference(ObjectPropertiesDialog* objectPropertiesDialog) { this->objectPropertiesDialog = objectPropertiesDialog; }

	/// <summary>
	/// Set the HWND of the main window that the camera preview is located.
	/// </summary>
	/// <param name="hWnd"></param>
	void SetMainWindowHwnd(HWND hWnd) { mainWindowHwnd = hWnd; }
	
	// MFC Callbacks
	
	void OnActionInitialise(HWND handle, int width, int height);			//Passes through handle and hieght and width and initialises DirectX renderer and SQL LITE
	void OnActionLoad();													//load the current chunk
	afx_msg	void OnActionSave();											//save the current chunk
	afx_msg void OnActionSaveTerrain();									//save chunk geometry

	void OnMainWindowLostFocus();
	void OnMainWindowRegainFocus();
	
	// Called externally.
	
	void Tick(MSG *msg);
	void UpdateInput(MSG *msg);
	
};
