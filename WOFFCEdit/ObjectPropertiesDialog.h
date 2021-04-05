#pragma once
#include <afxdialogex.h>


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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
