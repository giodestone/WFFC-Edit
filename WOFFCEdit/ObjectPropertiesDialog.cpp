// ObjectPropertiesDialog.cpp : implementation file
//

#include "ObjectPropertiesDialog.h"

#include <afxshellmanager.h>
#include <afxvisualmanagerwindows.h>

#include "afxdialogex.h"
#include "resource.h"
#include "afxpropertygridctrl.h"


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
	//DDX_Control(pDX, WM_USER + 100, *propertiesGrid);
	DDX_Control(pDX, IDC_NAMEEDIT, nameEdit);
	CString temp;
	DDX_Text(pDX, IDC_NAMEEDIT, temp);
	testString = std::wstring((LPCTSTR)temp);

	DDX_Control(pDX, IDC_POSXEDIT, posXEdit);
	DDX_Text(pDX, IDC_POSXEDIT, testFloat);

	DDX_Control(pDX, IDC_POSYEDIT, posYEdit);
	DDX_Control(pDX, IDC_POSZEDIT, posZEdit);
	DDX_Control(pDX, IDC_ROTXEDIT, rotXEdit);
	DDX_Control(pDX, IDC_rotyedit, rotYEdit);
	DDX_Control(pDX, IDC_ROTZEDIT, rotZEdit);
	DDX_Control(pDX, IDC_SCALEXEDIT, scaleXEdit);
	DDX_Control(pDX, IDC_SCALEYEDIT, scaleYEdit);
	DDX_Control(pDX, IDC_SCALEZEDIT, scaleZEdit);
	DDX_Control(pDX, IDC_OBJECTPROPERTIESGRID, propertiesGrid);
}

BOOL ObjectPropertiesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitialisePropertyGrid();
	SetAllFieldsEnableState(false);
	return true;
}

void ObjectPropertiesDialog::InitialisePropertyGrid()
{
	propertiesGrid.EnableDescriptionArea();
	propertiesGrid.SetVSDotNetLook();
	propertiesGrid.MarkModifiedProperties();

	// Don't try dynamic layout it corrupts the stack.

	static TCHAR BASED_CODE szFilter[] = _T("All Files(*.*)|*.*||"); // Any file filter picker because I'm unsure of file formats this may need.

	databaseNameToVariable.insert({ "id", COleVariant((long)0) });
	auto* id = new CMFCPropertyGridProperty(_T("ID"), databaseNameToVariable["id"], _T("The objects' ID."));
	propertiesGrid.AddProperty(id);

	databaseNameToVariable.insert({ "chunk_id", COleVariant((long)0) });
	auto* chunkID = new CMFCPropertyGridProperty(_T("Chunk ID"), databaseNameToVariable["chunk_id"], _T("The objects' ChunkID."));
	propertiesGrid.AddProperty(chunkID);

	databaseNameToVariable.insert({ "ai_node", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* aiNode = new CMFCPropertyGridProperty(_T("AI Node"), databaseNameToVariable["ai_node"], _T("Whether this object is an AI node."));
	propertiesGrid.AddProperty(aiNode);

	databaseNameToVariable.insert({ "camera", COleVariant((short)VARIANT_FALSE, VT_BOOL) });
	auto* camera = new CMFCPropertyGridProperty(_T("Camera"), databaseNameToVariable["camera"], _T("Whether the object is a camera."));
	propertiesGrid.AddProperty(camera);
	
	
	auto* renderingGroup = new CMFCPropertyGridProperty(_T("Rendering Properties"));

	databaseNameToVariable.insert({ "tex_diffuse", COleVariant(_T("/../../.")) });
	auto* texDiffuse = new CMFCPropertyGridFileProperty(_T("Texture Diffuse"), TRUE, _T("Texture diffuse path."), _T(".*"), 0, szFilter, _T("Texture diffuse path."));
	renderingGroup->AddSubItem(texDiffuse);

	databaseNameToVariable.insert({ "mesh", COleVariant(_T("/../../.")) });
	auto* mesh = new CMFCPropertyGridFileProperty(_T("Mesh Path"), TRUE, databaseNameToVariable["mesh"], _T(".*"), 0, szFilter, _T("Path of the mesh model."));
	renderingGroup->AddSubItem(mesh);

	databaseNameToVariable.insert({ "render", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* render = new CMFCPropertyGridProperty(_T("Render"), databaseNameToVariable["render"], _T("Whether the object be rendered."));
	renderingGroup->AddSubItem(render);
	
	propertiesGrid.AddProperty(renderingGroup);


	auto* collisionGroup = new CMFCPropertyGridProperty(_T("Collision Properties"));

	databaseNameToVariable.insert({ "collision", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* collision = new CMFCPropertyGridProperty(_T("Collide"), databaseNameToVariable["collision"], _T("Whether the object should collide with others."));
	collisionGroup->AddSubItem(collision);

	databaseNameToVariable.insert({ "collisionMesh", COleVariant(_T("/../../.")) });
	auto* collisionMesh = new CMFCPropertyGridFileProperty(_T("Collision Mesh"), TRUE, databaseNameToVariable["collisionMesh"], _T(".*"), 0, szFilter, _T("Collision mesh path."));
	collisionGroup->AddSubItem(collisionMesh);

	databaseNameToVariable.insert({ "collectable", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* collectable = new CMFCPropertyGridProperty(_T("Collectable"), databaseNameToVariable["collectable"], _T("Whether the object is a collectable."));
	collisionGroup->AddSubItem(collectable);

	databaseNameToVariable.insert({ "destructable", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* destructable = new CMFCPropertyGridProperty(_T("Destructable"), databaseNameToVariable["destructable"], _T("Whether the object is destructable."));
	collisionGroup->AddSubItem(destructable);

	databaseNameToVariable.insert({ "health_amount", COleVariant((long)0) });
	auto* healthAmount = new CMFCPropertyGridProperty(_T("Health Amount"), databaseNameToVariable["health_amount"],_T("How much health the object has."));
	collisionGroup->AddSubItem(healthAmount);

	propertiesGrid.AddProperty(collisionGroup);


	auto* editorGroup = new CMFCPropertyGridProperty(_T("Editor Properties"));
	
	databaseNameToVariable.insert({ "editor_render", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* editorRender = new CMFCPropertyGridProperty(_T("Editor Render"), databaseNameToVariable["editor_render"], _T("Whether to show the object in the editor."));
	editorGroup->AddSubItem(editorRender);

	databaseNameToVariable.insert({ "editor_texture_vis", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* editorTextureVis = new CMFCPropertyGridProperty(_T("Texture Visible in Editor"), databaseNameToVariable["editor_texture_vis"], _T("Whether the texture is visible in the editor."));
	editorGroup->AddSubItem(editorTextureVis);

	databaseNameToVariable.insert({ "editor_normal_vis", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* editorNormalsVis = new CMFCPropertyGridProperty(_T("Normals Visible in Editor"), databaseNameToVariable["editor_normal_vis"], _T("Whether the normals are visible in the editor."));
	editorGroup->AddSubItem(editorNormalsVis);

	databaseNameToVariable.insert({ "editor_collision_vis", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* editorCollisionVis = new CMFCPropertyGridProperty(_T("Collisions Visible in Editor"), databaseNameToVariable["editor_collision_vis"], _T("Whether the normals are visible in the editor."));
	editorGroup->AddSubItem(editorCollisionVis);

	databaseNameToVariable.insert({ "editor_pivot_vis", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* editorPivotVis = new CMFCPropertyGridProperty(_T("Collisions Visible in Editor"), databaseNameToVariable["editor_pivot_vis"], _T("Whether the normals are visible in the editor."));
	editorGroup->AddSubItem(editorPivotVis);

	databaseNameToVariable.insert({ "snap_to_ground", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* snapToGround = new CMFCPropertyGridProperty(_T("Snap To Ground"), databaseNameToVariable["snap_to_ground"], _T("Whether the placed object should snap to ground."));
	editorGroup->AddSubItem(snapToGround);
	
	databaseNameToVariable.insert({ "play_in_editor", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* playInEditor = new CMFCPropertyGridProperty(_T("Play Audio In Editor"), databaseNameToVariable["play_in_editor"], _T("Whether the audio file shoudl play in editor."));
	editorGroup->AddSubItem(playInEditor);

	databaseNameToVariable.insert({ "editor_wireframe", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* editorWireframe = new CMFCPropertyGridProperty(_T("Display Wireframe in Editor"), databaseNameToVariable["editor_wireframe"], _T("Whether this object should appear as wireframe in the editor."));
	editorGroup->AddSubItem(editorWireframe);

	propertiesGrid.AddProperty(editorGroup);
	
	
	auto* pivotGroup = new CMFCPropertyGridProperty( _T("Pivot Coordinates"));

	databaseNameToVariable.insert({ "pivot_x", COleVariant(0.f) });
	auto* pivotX = new CMFCPropertyGridProperty(_T("Pivot X"), databaseNameToVariable["pivot_x"], _T("X coordinate of the pivot value."));
	pivotGroup->AddSubItem(pivotX);

	databaseNameToVariable.insert({ "pivot_y", COleVariant(0.f) });
	auto* pivotY = new CMFCPropertyGridProperty(_T("Pivot Y"), databaseNameToVariable["pivot_y"], _T("Y coordinate of the pivot value."));
	pivotGroup->AddSubItem(pivotY);

	databaseNameToVariable.insert({ "pivot_z", COleVariant(0.f) });
	auto* pivotZ = new CMFCPropertyGridProperty(_T("Pivot Z"), databaseNameToVariable["pivot_z"], _T("Z coordinate of the pivot value."));
	pivotGroup->AddSubItem(pivotZ);

	propertiesGrid.AddProperty(pivotGroup);

	
	auto* audioGroup = new CMFCPropertyGridProperty(_T("Audio Properties"));
	
	databaseNameToVariable.insert({ "audio_file", COleVariant(_T("/../../.")) });
	auto* audioFile = new CMFCPropertyGridProperty(_T("Audio File Path"), databaseNameToVariable["audio_file"], _T("Path of the Audio File."));
	audioGroup->AddSubItem(audioFile);

	databaseNameToVariable.insert({ "volume", COleVariant(0.f) });
	auto* volume = new CMFCPropertyGridProperty(_T("Volume"), databaseNameToVariable["volume"], _T("Volume of the audio file when played."));
	audioGroup->AddSubItem(volume);

	databaseNameToVariable.insert({ "pitch", COleVariant(0.f) });
	auto* pitch = new CMFCPropertyGridProperty(_T("Pitch"), databaseNameToVariable["pitch_value"], _T("Pitch of the audio file when played."));
	audioGroup->AddSubItem(pitch);

	databaseNameToVariable.insert({ "pan", COleVariant(0.f) });
	auto* pan = new CMFCPropertyGridProperty(_T("Pan"), databaseNameToVariable["pan"], _T("Pan of the left/right channel when played."));
	audioGroup->AddSubItem(pan);

	databaseNameToVariable.insert({ "one_shot", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* oneShot = new CMFCPropertyGridProperty(_T("One Shot"), databaseNameToVariable["one_shot"], _T("Whether the audio file is one shot."));
	audioGroup->AddSubItem(oneShot);

	databaseNameToVariable.insert({ "play_on_init", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* playOnInit = new CMFCPropertyGridProperty(_T("Play On Init"), databaseNameToVariable["play_on_init"], _T("Whether the audio file should play the sound when initialized."));
	audioGroup->AddSubItem(playOnInit);

	databaseNameToVariable.insert({ "min_dist", COleVariant((long)0) });
	auto* minDist = new CMFCPropertyGridProperty(_T("Minimum Distance"), databaseNameToVariable["min_dist"], _T("Minimum falloff distance of the sound."));
	minDist->EnableSpinControl();
	audioGroup->AddSubItem(minDist);

	databaseNameToVariable.insert({ "max_dist", COleVariant((long)0) });
	auto* maxDist = new CMFCPropertyGridProperty(_T("Maximum Distance"), databaseNameToVariable["max_dist"], _T("Maximum falloff distance of the sound."));
	maxDist->EnableSpinControl();
	audioGroup->AddSubItem(maxDist);
	
	propertiesGrid.AddProperty(audioGroup);


	auto* pathGroup = new CMFCPropertyGridProperty(_T("Path Properties"));

	databaseNameToVariable.insert({ "path_node", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* pathNode = new CMFCPropertyGridProperty(_T("Path Node"), databaseNameToVariable["path_node"], _T("Whether the object is part of a node."));
	pathGroup->AddSubItem(pathNode);
	
	databaseNameToVariable.insert({ "path_node_start", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* pathNodeStart = new CMFCPropertyGridProperty(_T("Path Node Start"), databaseNameToVariable["path_node_start"], _T("Whether the object is the start of a node."));
	pathGroup->AddSubItem(pathNodeStart);

	databaseNameToVariable.insert({ "path_node_end", COleVariant((short)VARIANT_TRUE, VT_BOOL) });
	auto* pathNodeEnd = new CMFCPropertyGridProperty(_T("Path Node End"), databaseNameToVariable["path_node_end"], _T("Whether the object is the end of a node."));
	pathGroup->AddSubItem(pathNodeEnd);

	databaseNameToVariable.insert({ "parent_id", COleVariant((long)0) });
	auto* parentID = new CMFCPropertyGridProperty(_T("Parent ID"), databaseNameToVariable["parent_id"], _T("ID of the parent node."));
	pathGroup->AddSubItem(parentID);

	propertiesGrid.AddProperty(pathGroup);


	auto* lightGroup = new CMFCPropertyGridProperty(_T("Light Properties"));

	// Light diffuse + light specular handled differently! (Cannot get into COleVariant safely)
	auto* lightDiffuse = new CMFCPropertyGridColorProperty(_T("Light Diffuse"), RGB(0, 0, 0), NULL, _T("Diffuse colour of the light."));
	lightGroup->AddSubItem(lightDiffuse);

	auto* lightSpecular = new CMFCPropertyGridColorProperty(_T("Light Specular"), RGB(0, 0, 0), NULL, _T("Specular colour of the light."));
	lightGroup->AddSubItem(lightSpecular);

	databaseNameToVariable.insert({ "light_spot_cutoff", COleVariant(0.f) });
	auto* lightSpotCutoff = new CMFCPropertyGridProperty(_T("Light Spot Cutoff"), databaseNameToVariable["light_spot_cutoff"], _T("Spotlight cutoff value.")); // IDK what this would do. Spotlight angle?
	lightGroup->AddSubItem(lightSpotCutoff);
	
	databaseNameToVariable.insert({ "light_constant", COleVariant(0.f) });
	auto* lightConstant = new CMFCPropertyGridProperty(_T("Light Constant Falloff"), databaseNameToVariable["light_constant"], _T("Constant falloff of the light."));
	lightGroup->AddSubItem(lightConstant);

	databaseNameToVariable.insert({ "light_linear", COleVariant(0.f) });
	auto* lightLinear = new CMFCPropertyGridProperty(_T("Light Linear Falloff"), databaseNameToVariable["light_linear"], _T("Linear falloff of the light."));
	lightGroup->AddSubItem(lightLinear);

	databaseNameToVariable.insert({ "light_quadratic", COleVariant(0.f) });
	auto* lightQuadratic = new CMFCPropertyGridProperty(_T("Light Quadratic Falloff"), databaseNameToVariable["light_quadratic"], _T("Quadratic falloff of the light."));
	lightGroup->AddSubItem(lightQuadratic);
	
	propertiesGrid.AddProperty(lightGroup);

	// Fix values and properties grid being well sized.
	CRect rect;
	propertiesGrid.GetWindowRect(&rect);
	propertiesGrid.PostMessage(WM_SIZE, 0, MAKELONG(rect.Width(), rect.Height()));
}

void ObjectPropertiesDialog::UpdateFieldsWithDataFromCurrentSceneObject()
{
	if (currentSceneObject == nullptr)
		SetAllFieldsEnableState(true);
	
	// Light diffuse + light specular handled differently!
}

void ObjectPropertiesDialog::SetAllFieldsEnableState(bool state)
{
	nameEdit.EnableWindow(state);
	posXEdit.EnableWindow(state);
	posYEdit.EnableWindow(state);
	posZEdit.EnableWindow(state);
	rotXEdit.EnableWindow(state);
	rotYEdit.EnableWindow(state);
	rotZEdit.EnableWindow(state);
	scaleXEdit.EnableWindow(state);
	scaleYEdit.EnableWindow(state);
	scaleZEdit.EnableWindow(state);
	
	for (auto i = 0; i < propertiesGrid.GetPropertyCount(); ++i)
	{
		auto currentProperty = propertiesGrid.GetProperty(i);

		currentProperty->Enable(state);

		for (auto j = 0; j < currentProperty->GetSubItemsCount(); j++)
		{
			currentProperty->GetSubItem(j)->Enable(state);
		}

	}
}

void ObjectPropertiesDialog::SetCurrentSceneObject(SceneObject* sceneObject)
{
	this->currentSceneObject = sceneObject;

	UpdateFieldsWithDataFromCurrentSceneObject();
}

void ObjectPropertiesDialog::ClearCurrentSceneObject()
{
	this->currentSceneObject = nullptr;

	UpdateFieldsWithDataFromCurrentSceneObject();
}




afx_msg LRESULT ObjectPropertiesDialog::OnPropertiesGridPropertyUpdated(WPARAM wParam, LPARAM lParam)
{
	OutputDebugStringW(L"Property box changed!");

	auto* currentProperty = reinterpret_cast<CMFCPropertyGridProperty*>(lParam);

	// Get position database name

	// Create query

	// Launch query

	
	return 0;
}

bool ObjectPropertiesDialog::VerifyContentsAreFloat(CEdit& field, float previousValue, float& outValue)
{
	CString contents;
	field.GetWindowTextW(contents);
	
	try
	{
		const float finalValue = std::stof(static_cast<LPCTSTR>(contents));
		outValue = finalValue;
		return true;
	}
	catch (...)
	{
		field.SetWindowTextW(CString(std::to_wstring(previousValue).c_str()));
		return false;
	}
}


BEGIN_MESSAGE_MAP(ObjectPropertiesDialog, CDialogEx)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertiesGridPropertyUpdated)
	ON_EN_UPDATE(IDC_POSXEDIT, &ObjectPropertiesDialog::OnEnUpdatePosxedit)
	ON_EN_UPDATE(IDC_POSYEDIT, &ObjectPropertiesDialog::OnEnUpdatePosyedit)
	ON_EN_UPDATE(IDC_POSZEDIT, &ObjectPropertiesDialog::OnEnUpdatePoszedit)
	ON_EN_UPDATE(IDC_ROTXEDIT, &ObjectPropertiesDialog::OnEnUpdateRotxedit)
	ON_EN_UPDATE(IDC_ROTZEDIT, &ObjectPropertiesDialog::OnEnUpdateRotzedit)
	ON_EN_UPDATE(IDC_SCALEXEDIT, &ObjectPropertiesDialog::OnEnUpdateScalexedit)
	ON_EN_UPDATE(IDC_SCALEYEDIT, &ObjectPropertiesDialog::OnEnUpdateScaleyedit)
	ON_EN_UPDATE(IDC_SCALEZEDIT, &ObjectPropertiesDialog::OnEnUpdateScalezedit)
END_MESSAGE_MAP()


// ObjectPropertiesDialog message handlers


void ObjectPropertiesDialog::OnEnUpdatePosxedit()
{
	/*float val = 2.f;
	VerifyContentsAreFloat(posXEdit, 10.f, val);*/
}


void ObjectPropertiesDialog::OnEnUpdatePosyedit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
}


void ObjectPropertiesDialog::OnEnUpdatePoszedit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
}


void ObjectPropertiesDialog::OnEnUpdateRotxedit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
}


void ObjectPropertiesDialog::OnEnUpdateRotzedit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
}


void ObjectPropertiesDialog::OnEnUpdateScalexedit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
}


void ObjectPropertiesDialog::OnEnUpdateScaleyedit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
}


void ObjectPropertiesDialog::OnEnUpdateScalezedit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
}
