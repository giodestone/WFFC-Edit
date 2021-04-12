#pragma once
#include <afxdialogex.h>

#include <afxpropertygridctrl.h>
#include <unordered_map>


#include "SceneObject.h"


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
	CEdit nameEdit;
	CEdit posXEdit;
	CEdit posYEdit;
	CEdit posZEdit;
	CEdit rotXEdit;
	CEdit rotYEdit;
	CEdit rotZEdit;
	CEdit scaleXEdit;
	CEdit scaleYEdit;
	CEdit scaleZEdit;

	float testFloat;
	std::wstring testString;

	std::unordered_map<std::string, CMFCPropertyGridProperty*> databaseNameToProperty;
	std::unordered_map<CMFCPropertyGridProperty*, std::string> propertyToDatabaseName;

	SceneObject* currentSceneObject;

	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog() override;
	
	/// <summary>
	/// Create the property grid (as adding through editor doesn't work) and populate it with values.
	/// </summary>
	void InitialisePropertyGrid();

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
	/// Convert a std::string to CString by also converting it to a std::wstring in between.
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	CString ConvertStringToCString(const std::string str) const;

	VARIANT_BOOL ConvertBoolToVARIANTBOOL(const bool b) const;

	afx_msg LRESULT OnPropertiesGridPropertyUpdated(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
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
};
