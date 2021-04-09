#pragma once
#include <afxdialogex.h>

#include <afxpropertygridctrl.h>

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
	CMFCPropertyGridCtrl* propertiesGrid;

	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog() override;

	/// <summary>
	/// Create the property grid (as adding through editor doesn't work) and populate it with values.
	/// </summary>
	void InitialisePropertyGrid();

	afx_msg LRESULT OnPropertiesGridPropertyUpdated(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	void UpdateCurrentSceneObject(SceneObject* sceneObject);
};
