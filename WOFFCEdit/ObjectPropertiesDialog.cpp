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
	, currentSceneObject(nullptr)
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
	DDX_Control(pDX, IDC_POSXEDIT, posXEdit);
	DDX_Control(pDX, IDC_POSYEDIT, posYEdit);
	DDX_Control(pDX, IDC_POSZEDIT, posZEdit);
	DDX_Control(pDX, IDC_ROTXEDIT, rotXEdit);
	DDX_Control(pDX, IDC_rotyedit, rotYEdit);
	DDX_Control(pDX, IDC_ROTZEDIT, rotZEdit);
	DDX_Control(pDX, IDC_SCALEXEDIT, scaleXEdit);
	DDX_Control(pDX, IDC_SCALEYEDIT, scaleYEdit);
	DDX_Control(pDX, IDC_SCALEZEDIT, scaleZEdit);
	DDX_Control(pDX, IDC_OBJECTPROPERTIESGRID, propertiesGrid);

	if (currentSceneObject != nullptr)
	{
		CString temp(currentSceneObject->name.c_str(), currentSceneObject->name.length());
		DDX_Text(pDX, IDC_NAMEEDIT, temp);
		auto tempTo = std::string();

		DDX_Text(pDX, IDC_POSXEDIT, currentSceneObject->posX);
		DDX_Text(pDX, IDC_POSYEDIT, currentSceneObject->posY);
		DDX_Text(pDX, IDC_POSZEDIT, currentSceneObject->posZ);
		
		DDX_Text(pDX, IDC_ROTXEDIT, currentSceneObject->rotX);
		DDX_Text(pDX, IDC_rotyedit, currentSceneObject->rotY);
		DDX_Text(pDX, IDC_ROTZEDIT, currentSceneObject->rotZ);

		DDX_Text(pDX, IDC_SCALEXEDIT, currentSceneObject->scaX);
		DDX_Text(pDX, IDC_SCALEYEDIT, currentSceneObject->scaY);
		DDX_Text(pDX, IDC_SCALEZEDIT, currentSceneObject->scaZ);
	}
}

BOOL ObjectPropertiesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitialisePropertyGrid();

	
	if (currentSceneObject == nullptr) 
		SetAllFieldsEnableState(false);
	return true;
}

void ObjectPropertiesDialog::InitialisePropertyGrid()
{
	propertiesGrid.EnableDescriptionArea();
	propertiesGrid.SetVSDotNetLook();
	propertiesGrid.MarkModifiedProperties();

	static TCHAR BASED_CODE szFilter[] = _T("All Files(*.*)|*.*||"); // Any file filter picker because I'm unsure of file formats this may need.

	databaseNameToProperty.insert({ "id",  new CMFCPropertyGridProperty(_T("ID"), COleVariant((long)0), _T("The objects' ID.")) });
	auto* id = databaseNameToProperty["id"];
	id->AllowEdit(false);
	propertiesGrid.AddProperty(id);

	databaseNameToProperty.insert({ "chunk_id", new CMFCPropertyGridProperty(_T("Chunk ID"), COleVariant((long)0), _T("The objects' ChunkID.")) });
	auto* chunkID = databaseNameToProperty["chunk_id"];
	chunkID->AllowEdit(false);
	propertiesGrid.AddProperty(chunkID);

	databaseNameToProperty.insert({ "ai_node", new CMFCPropertyGridProperty(_T("AI Node"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether this object is an AI node.")) });
	auto* aiNode = databaseNameToProperty["ai_node"];
	propertiesGrid.AddProperty(aiNode);

	databaseNameToProperty.insert({ "camera", new CMFCPropertyGridProperty(_T("Camera"), COleVariant((short)VARIANT_FALSE, VT_BOOL), _T("Whether the object is a camera.")) });
	auto* camera = databaseNameToProperty["camera"];
	propertiesGrid.AddProperty(camera);
	
	
	auto* renderingGroup = new CMFCPropertyGridProperty(_T("Rendering Properties"));

	databaseNameToProperty.insert({ "tex_diffuse", new CMFCPropertyGridFileProperty(_T("Texture Diffuse"), TRUE, COleVariant(_T("/../../.")), _T(".*"), 0, szFilter, _T("Texture diffuse path.")) });
	auto* texDiffuse = databaseNameToProperty["tex_diffuse"];
	renderingGroup->AddSubItem(texDiffuse);

	databaseNameToProperty.insert({ "mesh", new CMFCPropertyGridFileProperty(_T("Mesh Path"), TRUE, COleVariant(_T("/../../.")), _T(".*"), 0, szFilter, _T("Path of the mesh model.")) });
	auto* mesh = databaseNameToProperty["mesh"];
	renderingGroup->AddSubItem(mesh);

	databaseNameToProperty.insert({ "render", new CMFCPropertyGridProperty(_T("Render"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether the object be rendered.")) });
	auto* render = databaseNameToProperty["render"];
	renderingGroup->AddSubItem(render);
	
	propertiesGrid.AddProperty(renderingGroup);


	auto* collisionGroup = new CMFCPropertyGridProperty(_T("Collision Properties"));

	databaseNameToProperty.insert({ "collision", new CMFCPropertyGridProperty(_T("Collide"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether the object should collide with others.")) });
	auto* collision = databaseNameToProperty["collision"];
	collisionGroup->AddSubItem(collision);

	databaseNameToProperty.insert({ "collision_mesh", new CMFCPropertyGridFileProperty(_T("Collision Mesh"), TRUE, COleVariant(_T("/../../.")), _T(".*"), 0, szFilter, _T("Collision mesh path.")) });
	auto* collisionMesh = databaseNameToProperty["collision_mesh"];
	collisionGroup->AddSubItem(collisionMesh);

	databaseNameToProperty.insert({ "collectable", new CMFCPropertyGridProperty(_T("Collectable"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether the object is a collectable.")) });
	auto* collectable = databaseNameToProperty["collectable"];
	collisionGroup->AddSubItem(collectable);

	databaseNameToProperty.insert({ "destructable", new CMFCPropertyGridProperty(_T("Destructable"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether the object is destructable.")) });
	auto* destructable = databaseNameToProperty["destructable"];
	collisionGroup->AddSubItem(destructable);

	databaseNameToProperty.insert({ "health_amount", new CMFCPropertyGridProperty(_T("Health Amount"), COleVariant((long)0),_T("How much health the object has.")) });
	auto* healthAmount = databaseNameToProperty["health_amount"];
	collisionGroup->AddSubItem(healthAmount);

	propertiesGrid.AddProperty(collisionGroup);


	auto* editorGroup = new CMFCPropertyGridProperty(_T("Editor Properties"));
	
	databaseNameToProperty.insert({ "editor_render", new CMFCPropertyGridProperty(_T("Editor Render"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether to show the object in the editor.")) });
	auto* editorRender = databaseNameToProperty["editor_render"];
	editorGroup->AddSubItem(editorRender);

	databaseNameToProperty.insert({ "editor_texture_vis", new CMFCPropertyGridProperty(_T("Texture Visible in Editor"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether the texture is visible in the editor.")) });
	auto* editorTextureVis = databaseNameToProperty["editor_texture_vis"];
	editorGroup->AddSubItem(editorTextureVis);

	databaseNameToProperty.insert({ "editor_normal_vis", new CMFCPropertyGridProperty(_T("Normals Visible in Editor"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether the normals are visible in the editor.")) });
	auto* editorNormalsVis = databaseNameToProperty["editor_normal_vis"];
	editorGroup->AddSubItem(editorNormalsVis);

	databaseNameToProperty.insert({ "editor_collision_vis", new CMFCPropertyGridProperty(_T("Collisions Visible in Editor"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether the normals are visible in the editor.")) });
	auto* editorCollisionVis = databaseNameToProperty["editor_collision_vis"];
	editorGroup->AddSubItem(editorCollisionVis);

	databaseNameToProperty.insert({ "editor_pivot_vis", new CMFCPropertyGridProperty(_T("Collisions Visible in Editor"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether the normals are visible in the editor.")) });
	auto* editorPivotVis = databaseNameToProperty["editor_pivot_vis"];
	editorGroup->AddSubItem(editorPivotVis);

	databaseNameToProperty.insert({ "snap_to_ground", new CMFCPropertyGridProperty(_T("Snap To Ground"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether the placed object should snap to ground.")) });
	auto* snapToGround = databaseNameToProperty["snap_to_ground"];
	editorGroup->AddSubItem(snapToGround);
	
	databaseNameToProperty.insert({ "play_in_editor", new CMFCPropertyGridProperty(_T("Play Audio In Editor"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether the audio file shoudl play in editor.")) });
	auto* playInEditor = databaseNameToProperty["play_in_editor"];
	editorGroup->AddSubItem(playInEditor);

	databaseNameToProperty.insert({ "editor_wireframe", new CMFCPropertyGridProperty(_T("Display Wireframe in Editor"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether this object should appear as wireframe in the editor.")) });
	auto* editorWireframe = databaseNameToProperty["editor_wireframe"];
	editorGroup->AddSubItem(editorWireframe);

	propertiesGrid.AddProperty(editorGroup);
	
	
	auto* pivotGroup = new CMFCPropertyGridProperty( _T("Pivot Coordinates"));

	databaseNameToProperty.insert({ "pivot_x", new CMFCPropertyGridProperty(_T("Pivot X"), COleVariant(0.f), _T("X coordinate of the pivot value.")) });
	auto* pivotX = databaseNameToProperty["pivot_x"];
	pivotGroup->AddSubItem(pivotX);

	databaseNameToProperty.insert({ "pivot_y", new CMFCPropertyGridProperty(_T("Pivot Y"), COleVariant(0.f), _T("Y coordinate of the pivot value.")) });
	auto* pivotY = databaseNameToProperty["pivot_y"];
	pivotGroup->AddSubItem(pivotY);

	databaseNameToProperty.insert({ "pivot_z", new CMFCPropertyGridProperty(_T("Pivot Z"), COleVariant(0.f), _T("Z coordinate of the pivot value.")) });
	auto* pivotZ = databaseNameToProperty["pivot_z"];
	pivotGroup->AddSubItem(pivotZ);

	propertiesGrid.AddProperty(pivotGroup);

	
	auto* audioGroup = new CMFCPropertyGridProperty(_T("Audio Properties"));
	
	databaseNameToProperty.insert({ "audio_file", new CMFCPropertyGridProperty(_T("Audio File Path"), COleVariant(_T("/../../.")), _T("Path of the Audio File.")) });
	auto* audioFile = databaseNameToProperty["audio_file"];
	audioGroup->AddSubItem(audioFile);

	databaseNameToProperty.insert({ "volume", new CMFCPropertyGridProperty(_T("Volume"), COleVariant(0.f), _T("Volume of the audio file when played.")) });
	auto* volume = databaseNameToProperty["volume"];
	audioGroup->AddSubItem(volume);

	databaseNameToProperty.insert({ "pitch", new CMFCPropertyGridProperty(_T("Pitch"), COleVariant(0.f), _T("Pitch of the audio file when played.")) });
	auto* pitch = databaseNameToProperty["pitch"];
	audioGroup->AddSubItem(pitch);

	databaseNameToProperty.insert({ "pan", new CMFCPropertyGridProperty(_T("Pan"), COleVariant(0.f), _T("Pan of the left/right channel when played.")) });
	auto* pan = databaseNameToProperty["pan"];
	audioGroup->AddSubItem(pan);

	databaseNameToProperty.insert({ "one_shot", new CMFCPropertyGridProperty(_T("One Shot"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether the audio file is one shot.")) });
	auto* oneShot = databaseNameToProperty["one_shot"];
	audioGroup->AddSubItem(oneShot);

	databaseNameToProperty.insert({ "play_on_init", new CMFCPropertyGridProperty(_T("Play On Init"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether the audio file should play the sound when initialized.")) });
	auto* playOnInit = databaseNameToProperty["play_on_init"];
	audioGroup->AddSubItem(playOnInit);

	databaseNameToProperty.insert({ "min_dist", new CMFCPropertyGridProperty(_T("Minimum Distance"), COleVariant((long)0), _T("Minimum falloff distance of the sound.")) });
	auto* minDist = databaseNameToProperty["min_dist"];
	minDist->EnableSpinControl();
	audioGroup->AddSubItem(minDist);

	databaseNameToProperty.insert({ "max_dist", new CMFCPropertyGridProperty(_T("Maximum Distance"), COleVariant((long)0), _T("Maximum falloff distance of the sound.")) });
	auto* maxDist = databaseNameToProperty["max_dist"];
	maxDist->EnableSpinControl();
	audioGroup->AddSubItem(maxDist);
	
	propertiesGrid.AddProperty(audioGroup);


	auto* pathGroup = new CMFCPropertyGridProperty(_T("Path Properties"));

	databaseNameToProperty.insert({ "path_node", new CMFCPropertyGridProperty(_T("Path Node"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether the object is part of a node.")) });
	auto* pathNode = databaseNameToProperty["path_node"];
	pathGroup->AddSubItem(pathNode);
	
	databaseNameToProperty.insert({ "path_node_start", new CMFCPropertyGridProperty(_T("Path Node Start"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether the object is the start of a node.")) });
	auto* pathNodeStart = databaseNameToProperty["path_node_start"];
	pathGroup->AddSubItem(pathNodeStart);

	databaseNameToProperty.insert({ "path_node_end", new CMFCPropertyGridProperty(_T("Path Node End"), COleVariant((short)VARIANT_TRUE, VT_BOOL), _T("Whether the object is the end of a node.")) });
	auto* pathNodeEnd = databaseNameToProperty["path_node_end"];
	pathGroup->AddSubItem(pathNodeEnd);

	databaseNameToProperty.insert({ "parent_id", new CMFCPropertyGridProperty(_T("Parent ID"), COleVariant((long)0), _T("ID of the parent node.")) });
	auto* parentID = databaseNameToProperty["parent_id"];
	pathGroup->AddSubItem(parentID);

	propertiesGrid.AddProperty(pathGroup);


	auto* lightGroup = new CMFCPropertyGridProperty(_T("Light Properties"));

	databaseNameToProperty.insert({ "light_type", new CMFCPropertyGridProperty(_T("Light Type"), COleVariant((long)0), _T("Type of light this light is.")) });
	auto* lightType = databaseNameToProperty["light_type"];
	lightType->EnableSpinControl();
	lightGroup->AddSubItem(lightType);
	
	// Light diffuse + light specular handled differently! Not as three inidivudal items but rather as one!
	databaseNameToProperty.insert({ "light_diffuse", new CMFCPropertyGridColorProperty(_T("Light Diffuse"), RGB(0, 0, 0), NULL, _T("Diffuse colour of the light.")) });
	auto* lightDiffuse = databaseNameToProperty["light_diffuse"];
	lightGroup->AddSubItem(lightDiffuse);

	databaseNameToProperty.insert({ "light_specular", new CMFCPropertyGridColorProperty(_T("Light Specular"), RGB(0, 0, 0), NULL, _T("Specular colour of the light.")) });
	auto* lightSpecular = databaseNameToProperty["light_specular"];
	lightGroup->AddSubItem(lightSpecular);

	databaseNameToProperty.insert({ "light_spot_cutoff", new CMFCPropertyGridProperty(_T("Light Spot Cutoff"), COleVariant(0.f), _T("Spotlight cutoff value.")) });
	auto* lightSpotCutoff = databaseNameToProperty["light_spot_cutoff"]; // IDK what this would do. Spotlight angle?
	lightGroup->AddSubItem(lightSpotCutoff);
	
	databaseNameToProperty.insert({ "light_constant",  new CMFCPropertyGridProperty(_T("Light Constant Falloff"), COleVariant(0.f), _T("Constant falloff of the light.")) });
	auto* lightConstant = databaseNameToProperty["light_constant"];
	lightGroup->AddSubItem(lightConstant);

	databaseNameToProperty.insert({ "light_linear", new CMFCPropertyGridProperty(_T("Light Linear Falloff"), COleVariant(0.f), _T("Linear falloff of the light.")) });
	auto* lightLinear = databaseNameToProperty["light_linear"];
	lightGroup->AddSubItem(lightLinear);

	databaseNameToProperty.insert({ "light_quadratic", new CMFCPropertyGridProperty(_T("Light Quadratic Falloff"), COleVariant(0.f), _T("Quadratic falloff of the light.")) });
	auto* lightQuadratic = databaseNameToProperty["light_quadratic"];
	lightGroup->AddSubItem(lightQuadratic);
	
	propertiesGrid.AddProperty(lightGroup);

	// Fix values and properties grid being well sized.
	CRect rect;
	propertiesGrid.GetWindowRect(&rect);
	propertiesGrid.PostMessage(WM_SIZE, 0, MAKELONG(rect.Width(), rect.Height()));
}

void ObjectPropertiesDialog::InitialisePropertyToDatabaseNameLookup()
{
	for (auto& kvp : databaseNameToProperty)
	{
		propertyToDatabaseName.insert({ kvp.second, kvp.first });
	}
}

void ObjectPropertiesDialog::UpdateFieldsWithDataFromCurrentSceneObject()
{
	SetAllFieldsEnableState(false);

	if (currentSceneObject == nullptr)
		return;

	nameEdit.SetWindowTextW(ConvertStringToCString(currentSceneObject->name)); // Silly conversion byt CString takes wchar.
	
	posXEdit.SetWindowTextW(CString(std::to_wstring(currentSceneObject->posX).c_str()));
	posYEdit.SetWindowTextW(CString(std::to_wstring(currentSceneObject->posY).c_str()));
	posZEdit.SetWindowTextW(CString(std::to_wstring(currentSceneObject->posZ).c_str()));
	
	rotXEdit.SetWindowTextW(CString(std::to_wstring(currentSceneObject->rotX).c_str()));
	rotYEdit.SetWindowTextW(CString(std::to_wstring(currentSceneObject->rotY).c_str()));
	rotZEdit.SetWindowTextW(CString(std::to_wstring(currentSceneObject->rotZ).c_str()));
	
	scaleXEdit.SetWindowTextW(CString(std::to_wstring(currentSceneObject->scaX).c_str()));
	scaleYEdit.SetWindowTextW(CString(std::to_wstring(currentSceneObject->scaY).c_str()));
	scaleZEdit.SetWindowTextW(CString(std::to_wstring(currentSceneObject->scaZ).c_str()));

	// In database field order, excluding name, position, rotation, and scale.
	databaseNameToProperty["id"]->SetValue(COleVariant((long)currentSceneObject->ID));
	databaseNameToProperty["chunk_id"]->SetValue(COleVariant((long)currentSceneObject->chunk_ID));
	databaseNameToProperty["mesh"]->SetValue(COleVariant(ConvertStringToCString(currentSceneObject->model_path)));
	databaseNameToProperty["tex_diffuse"]->SetValue(COleVariant(ConvertStringToCString(currentSceneObject->tex_diffuse_path)));
	// pos, rot, sca would go here.
	databaseNameToProperty["render"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->render), VT_BOOL));
	databaseNameToProperty["collision"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->collision), VT_BOOL));
	databaseNameToProperty["collision_mesh"]->SetValue(COleVariant(ConvertStringToCString(currentSceneObject->collision_mesh)));
	databaseNameToProperty["collectable"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->collectable), VT_BOOL));
	databaseNameToProperty["destructable"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->destructable), VT_BOOL));
	databaseNameToProperty["health_amount"]->SetValue(COleVariant((long)currentSceneObject->health_amount));
	databaseNameToProperty["editor_render"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->editor_render), VT_BOOL));
	databaseNameToProperty["editor_texture_vis"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->editor_texture_vis), VT_BOOL));
	databaseNameToProperty["editor_normals_vis"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->editor_normals_vis), VT_BOOL));
	databaseNameToProperty["editor_collision_vis"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->editor_collision_vis), VT_BOOL));
	databaseNameToProperty["editor_pivot_vis"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->editor_pivot_vis), VT_BOOL));
	databaseNameToProperty["pivot_x"]->SetValue(COleVariant(currentSceneObject->pivotX));
	databaseNameToProperty["pivot_y"]->SetValue(COleVariant(currentSceneObject->pivotY));
	databaseNameToProperty["pivot_z"]->SetValue(COleVariant(currentSceneObject->pivotZ));
	databaseNameToProperty["snap_to_ground"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->snapToGround), VT_BOOL));
	databaseNameToProperty["ai_node"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->AINode), VT_BOOL));
	databaseNameToProperty["audio_file"]->SetValue(COleVariant(ConvertStringToCString(currentSceneObject->audio_path)));
	databaseNameToProperty["volume"]->SetValue(COleVariant(currentSceneObject->volume));
	databaseNameToProperty["pitch"]->SetValue(COleVariant(currentSceneObject->pitch));
	databaseNameToProperty["pan"]->SetValue(COleVariant(currentSceneObject->pan));
	databaseNameToProperty["one_shot"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->one_shot), VT_BOOL));
	databaseNameToProperty["play_on_init"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->play_on_init), VT_BOOL));
	databaseNameToProperty["play_in_editor"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->play_in_editor), VT_BOOL));
	databaseNameToProperty["min_dist"]->SetValue(COleVariant((long)currentSceneObject->min_dist));
	databaseNameToProperty["max_dist"]->SetValue(COleVariant((long)currentSceneObject->max_dist));
	databaseNameToProperty["camera"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->camera), VT_BOOL));
	databaseNameToProperty["path_node"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->path_node), VT_BOOL));
	databaseNameToProperty["path_node_start"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->path_node_start), VT_BOOL));
	databaseNameToProperty["path_node_end"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->path_node_end), VT_BOOL));
	databaseNameToProperty["parent_id"]->SetValue(COleVariant((long)currentSceneObject->parent_id));
	databaseNameToProperty["editor_wireframe"]->SetValue(COleVariant((short)ConvertBoolToVARIANTBOOL(currentSceneObject->editor_wireframe), VT_BOOL));
	// name would go here
	databaseNameToProperty["light_type"]->SetValue(COleVariant((long)currentSceneObject->light_type));
	// Light diffuse + light specular handled differently!
	dynamic_cast<CMFCPropertyGridColorProperty*>(databaseNameToProperty["light_diffuse"])->SetColor(RGB(currentSceneObject->light_diffuse_r, currentSceneObject->light_diffuse_g, currentSceneObject->light_diffuse_b));
	dynamic_cast<CMFCPropertyGridColorProperty*>(databaseNameToProperty["light_specular"])->SetColor(RGB(currentSceneObject->light_specular_r, currentSceneObject->light_specular_g, currentSceneObject->light_specular_b));
	databaseNameToProperty["light_spot_cutoff"]->SetValue(COleVariant(currentSceneObject->light_spot_cutoff));
	databaseNameToProperty["light_constant"]->SetValue(COleVariant(currentSceneObject->light_constant));
	databaseNameToProperty["light_linear"]->SetValue(COleVariant(currentSceneObject->light_linear));
	databaseNameToProperty["light_quadratic"]->SetValue(COleVariant(currentSceneObject->light_quadratic));
	
	SetAllFieldsEnableState(true);
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
		auto* currentProperty = propertiesGrid.GetProperty(i);

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
	SetCurrentSceneObject(nullptr);
}




afx_msg LRESULT ObjectPropertiesDialog::OnPropertiesGridPropertyUpdated(WPARAM wParam, LPARAM lParam)
{
	OutputDebugStringW(L"Property box changed!");

	// wparam = The control ID of the property list.
	// lparam = A pointer to the property (CMFCPropertyGridProperty) that changed.

	auto* currentProperty = reinterpret_cast<CMFCPropertyGridProperty*>(lParam);

	//databaseNameToVariable["id"].lVal = 10;
	//propertiesGrid.GetProperty(0)->SetValue(databaseNameToVariable["id"]);

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

CString ObjectPropertiesDialog::ConvertStringToCString(const std::string str) const
{
	return CString(std::string(str.begin(), str.end()).c_str());
}

VARIANT_BOOL ObjectPropertiesDialog::ConvertBoolToVARIANTBOOL(const bool b) const
{
	switch (b)
	{
		case true:
			return VARIANT_TRUE;
		case false:
			return VARIANT_FALSE;
	}
}


BEGIN_MESSAGE_MAP(ObjectPropertiesDialog, CDialogEx)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertiesGridPropertyUpdated)
END_MESSAGE_MAP()
