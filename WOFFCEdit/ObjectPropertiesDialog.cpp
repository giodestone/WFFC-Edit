// ObjectPropertiesDialog.cpp : implementation file
//

#include "ObjectPropertiesDialog.h"
#include "afxdialogex.h"
#include "resource.h"


// ObjectPropertiesDialog dialog

IMPLEMENT_DYNAMIC(ObjectPropertiesDialog, CDialogEx)

ObjectPropertiesDialog::ObjectPropertiesDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OBJECTPROPERTIESDIALOG, pParent)
{

}

ObjectPropertiesDialog::~ObjectPropertiesDialog()
{
}

void ObjectPropertiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ObjectPropertiesDialog, CDialogEx)
END_MESSAGE_MAP()


// ObjectPropertiesDialog message handlers
