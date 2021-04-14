#pragma once
#include <afxdialogex.h>

#include <afxpropertygridctrl.h>
#include <unordered_map>


#include "SceneObject.h"
#include "CFloatEdit.h"


// ObjectPropertiesDialog dialog

class ObjectPropertiesDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ObjectPropertiesDialog)

public:
	ObjectPropertiesDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ObjectPropertiesDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTPROPERTIESDIALOG };
#endif

protected:
	class ToolMain* toolMain;
	
	CEdit nameEdit;
	CFloatEdit posXEdit;
	CFloatEdit posYEdit;
	CFloatEdit posZEdit;
	CFloatEdit rotXEdit;
	CFloatEdit rotYEdit;
	CFloatEdit rotZEdit;
	CFloatEdit scaleXEdit;
	CFloatEdit scaleYEdit;
	CFloatEdit scaleZEdit;

	bool isUpdatingFieldsFromCurrentlySelectedObject;

	std::unordered_map<std::string, CMFCPropertyGridProperty*> databaseNameToProperty;
	std::unordered_map<CMFCPropertyGridProperty*, std::string> propertyToDatabaseName;

	SceneObject* currentSceneObject;

	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog() override;

	void InitialiseFloatEdits();
	
	/// <summary>
	/// Add properties to propertiesGrid based on elements of SceneObject.
	/// </summary>
	void InitialisePropertyGrid();

	/// <summary>
	/// Initialise propertyToDatabaseName lookup. Must be called after populating databaseNameToProperty via InitialisePropertyGrid().
	/// </summary>
	void InitialisePropertyToDatabaseNameLookup();

	void UpdateFieldsWithDataFromCurrentSceneObject();

	void SetAllFieldsEnableState(bool state);

	/// <summary>
	/// Verify that contents are the type double, if they are not the contents of field to previousValue.
	/// </summary>
	/// <param name="field">The field to check.</param>
	/// <param name="previousValue">The value of the field before applying.</param>
	/// <returns>True if a double; false if not.</returns>
	bool VerifyContentsAreFloat(CEdit& field, float previousValue, float& outValue);

	/// <summary>
	/// Event callback for when propertiesGrid property is updated. Called by MFC. Updates the changes onto the object that is being modified.
	/// </summary>
	/// <param name="wParam">The control ID of the property list.</param>
	/// <param name="lParam">A pointer to the property (CMFCPropertyGridProperty) that changed.</param>
	afx_msg LRESULT OnPropertiesGridPropertyUpdated(WPARAM wParam, LPARAM lParam);

	LRESULT OnControlChanged(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:

	/// <summary>
	/// Setup reference to ToolMain, must be set up otherwise picking won't work.
	/// </summary>
	/// <param name="toolMain"></param>
	void SetReferenceToToolMain(class ToolMain* toolMain)
	{
		this->toolMain = toolMain;
	}

	/// <summary>
	/// Update the scene object's properties that should be displayed by the ObjectPropertiesDialog.
	/// </summary>
	/// <param name="sceneObject"></param>
	void SetCurrentSceneObject(SceneObject* sceneObject);

	/// <summary>
	/// Clear the current selection and update the properties box to be disabled.
	/// </summary>
	void ClearCurrentSceneObject();
	CMFCPropertyGridCtrl propertiesGrid;
	afx_msg void OnChangeOrUpdateNameEdit();
};
