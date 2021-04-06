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
	DDX_Control(pDX, IDC_OBJECTPROPERTIESGRID, propertiesGrid);
	InitialisePropertyGrid();
}

BOOL ObjectPropertiesDialog::OnInitDialog()
{

	return true;
}

void ObjectPropertiesDialog::InitialisePropertyGrid()
{
	
	HDITEM item;
	item.cxy = 120;
	item.mask = HDI_WIDTH;
	propertiesGrid.GetHeaderCtrl().SetItem(0, new HDITEM(item));
	
	//auto* group = new CMFCPropertyGridProperty(_T("uhh"));
	
	auto* id = new CMFCPropertyGridProperty(_T("ID"), _T("no"), _T("non"));
	id->AddOption(_T("no"));
	id->AddOption(_T("yes"));
	propertiesGrid.AddProperty(id);

	//auto* chunkID = new CMFCPropertyGridProperty(_T("ID"), _T("ID"), _T("ID"));
	//propertiesGrid.AddProperty(chunkID);

	//propertiesGrid.AddProperty(group);
}



BEGIN_MESSAGE_MAP(ObjectPropertiesDialog, CDialogEx)
END_MESSAGE_MAP()


// ObjectPropertiesDialog message handlers
