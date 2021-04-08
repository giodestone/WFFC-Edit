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
	//DDX_Control(pDX, IDC_OBJECTPROPERTIESGRID, objectPropertiesGrid);
}

BOOL ObjectPropertiesDialog::OnInitDialog()
{
	InitialisePropertyGrid();
	return true;
}

void ObjectPropertiesDialog::InitialisePropertyGrid()
{
	propertiesGrid = new CMFCPropertyGridCtrl;
	propertiesGrid->Create(WS_CHILD | WS_BORDER | WS_VISIBLE, CRect(CPoint(6 * 1.5, 200 * 1.5), CSize(252 * 1.5, 204 * 1.5)), this, WM_USER + 100);
	propertiesGrid->EnableDescriptionArea();
	propertiesGrid->SetVSDotNetLook();
	propertiesGrid->MarkModifiedProperties();

	// Dont try dynamic layout it corrupts the stack
	//propertiesGrid->EnableDynamicLayout();
	//auto propGridDynamicLayout = propertiesGrid->GetDynamicLayout();
	//auto propGridSizeSettings = CMFCDynamicLayout::SizeHorizontalAndVertical(100, 100);
	//auto propGridMoveSettings = CMFCDynamicLayout::MoveNone();
	//propGridDynamicLayout->AddItem(propertiesGrid->GetSafeHwnd(), propGridMoveSettings, propGridSizeSettings);
	//HDITEM item;
	//item.cxy = 120;
	//item.mask = HDI_WIDTH;
	//propertiesGrid->GetHeaderCtrl().SetItem(0, new HDITEM(item));

	static TCHAR BASED_CODE szFilter[] = _T("All Files(*.*)|*.*||"); // Any file filter picker because I'm unsure of file formats this may need.
	
	//auto* group = new CMFCPropertyGridProperty(_T("uhh"));
	auto* id = new CMFCPropertyGridProperty(_T("ID"), _T("0"), _T("The objects' ID."));
	propertiesGrid->AddProperty(id);

	auto* chunkID = new CMFCPropertyGridProperty(_T("Chunk ID"), _T("0"), _T("The objects' ChunkID."));
	propertiesGrid->AddProperty(chunkID);

	COleVariant aiNodeValue((short)VARIANT_TRUE, VT_BOOL);
	auto* aiNode = new CMFCPropertyGridProperty(_T("AI Node"), aiNodeValue, _T("Whether this object is an AI node."));
	propertiesGrid->AddProperty(aiNode);

	COleVariant cameraValue((short)VARIANT_FALSE, VT_BOOL);
	auto* camera = new CMFCPropertyGridProperty(_T("Camera"), cameraValue, _T("Whether the object is a camera."));
	propertiesGrid->AddProperty(camera);
	
	
	auto* renderingGroup = new CMFCPropertyGridProperty(_T("Rendering Properties"));

	COleVariant texDiffuseValue(_T("/../../."));
	auto* texDiffuse = new CMFCPropertyGridFileProperty(_T("Texture Diffuse"), TRUE, _T("Texture diffuse path."), _T(".*"), 0, szFilter, _T("Texture diffuse path."));
	renderingGroup->AddSubItem(texDiffuse);

	COleVariant meshValue(_T("/../../."));
	auto* mesh = new CMFCPropertyGridFileProperty(_T("Mesh Path"), TRUE, meshValue, _T(".*"), 0, szFilter, _T("Path of the mesh model."));
	renderingGroup->AddSubItem(mesh);

	COleVariant renderValue((short)VARIANT_TRUE, VT_BOOL);
	auto* render = new CMFCPropertyGridProperty(_T("Render"), renderValue, _T("Whether the object be rendered."));
	renderingGroup->AddSubItem(render);
	
	propertiesGrid->AddProperty(renderingGroup);


	auto* collisionGroup = new CMFCPropertyGridProperty(_T("Collision Properties"));

	COleVariant collisonValue((short)VARIANT_TRUE, VT_BOOL);
	auto* collision = new CMFCPropertyGridProperty(_T("Collide"), collisonValue, _T("Whether the object should collide with others."));
	collisionGroup->AddSubItem(collision);

	COleVariant collisionMeshValue(_T("/../../."));
	auto* collisionMesh = new CMFCPropertyGridFileProperty(_T("Collision Mesh"), TRUE, collisionMeshValue, _T(".*"), 0, szFilter, _T("Collision mesh path."));
	collisionGroup->AddSubItem(collisionMesh);

	COleVariant collectableValue((short)VARIANT_TRUE, VT_BOOL);
	auto* collectable = new CMFCPropertyGridProperty(_T("Collectable"), collectableValue, _T("Whether the object is a collectable."));
	collisionGroup->AddSubItem(collectable);

	COleVariant destructableValue((short)VARIANT_TRUE, VT_BOOL);
	auto* destructable = new CMFCPropertyGridProperty(_T("Destructable"), destructableValue, _T("Whether the object is destructable."));
	collisionGroup->AddSubItem(destructable);

	COleVariant healthAmountValue(_T("/../../."));
	auto* healthAmount = new CMFCPropertyGridFileProperty(_T("Health Amount"), TRUE, healthAmountValue, _T(".*"), 0, szFilter, _T("Texture diffuse path."));
	collisionGroup->AddSubItem(healthAmount);

	propertiesGrid->AddProperty(collisionGroup);


	auto* editorGroup = new CMFCPropertyGridProperty(_T("Editor Properties"));
	
	COleVariant editorRenderValue((short)VARIANT_TRUE, VT_BOOL);
	auto* editorRender = new CMFCPropertyGridProperty(_T("Editor Render"), editorRenderValue, _T("Whether to show the object in the editor."));
	editorGroup->AddSubItem(editorRender);

	COleVariant editorTextureVisValue((short)VARIANT_TRUE, VT_BOOL);
	auto* editorTextureVis = new CMFCPropertyGridProperty(_T("Texture Visible in Editor"), editorTextureVisValue, _T("Whether the texture is visible in the editor."));
	editorGroup->AddSubItem(editorTextureVis);

	COleVariant editorNormalVisValue((short)VARIANT_TRUE, VT_BOOL);
	auto* editorNormalsVis = new CMFCPropertyGridProperty(_T("Normals Visible in Editor"), editorNormalVisValue, _T("Whether the normals are visible in the editor."));
	editorGroup->AddSubItem(editorNormalsVis);

	COleVariant editorCollisionVisValue((short)VARIANT_TRUE, VT_BOOL);
	auto* editorCollisionVis = new CMFCPropertyGridProperty(_T("Collisions Visible in Editor"), editorCollisionVisValue, _T("Whether the normals are visible in the editor."));
	editorGroup->AddSubItem(editorCollisionVis);

	COleVariant editorPivotVisValue((short)VARIANT_TRUE, VT_BOOL);
	auto* editorPivotVis = new CMFCPropertyGridProperty(_T("Collisions Visible in Editor"), editorPivotVisValue, _T("Whether the normals are visible in the editor."));
	editorGroup->AddSubItem(editorPivotVis);

	COleVariant snapToGroundValue((short)VARIANT_TRUE, VT_BOOL);
	auto* snapToGround = new CMFCPropertyGridProperty(_T("Snap To Ground"), editorPivotVisValue, _T("Whether the placed object should snap to ground."));
	editorGroup->AddSubItem(snapToGround);
	
	COleVariant playInEditorValue((short)VARIANT_TRUE, VT_BOOL);
	auto* playInEditor = new CMFCPropertyGridProperty(_T("Play Audio In Editor"), playInEditorValue, _T("Whether the audio file shoudl play in editor."));
	editorGroup->AddSubItem(playInEditor);

	COleVariant editorWireframeValue((short)VARIANT_TRUE, VT_BOOL);
	auto* editorWireframe = new CMFCPropertyGridProperty(_T("Display Wireframe in Editor"), editorPivotVisValue, _T("Whether this object should appear as wireframe in the editor."));
	editorGroup->AddSubItem(editorWireframe);

	propertiesGrid->AddProperty(editorGroup);
	
	
	auto* pivotGroup = new CMFCPropertyGridProperty( _T("Pivot Coordinates"));

	COleVariant pivotXValue(0.f);
	COleVariant pivotYValue(0.f);
	COleVariant pivotZValue(0.f);

	auto* pivotX = new CMFCPropertyGridProperty(_T("Pivot X"), pivotXValue, _T("X coordinate of the pivot value."));
	pivotGroup->AddSubItem(pivotX);

	auto* pivotY = new CMFCPropertyGridProperty(_T("Pivot Y"), pivotYValue, _T("Y coordinate of the pivot value."));
	pivotGroup->AddSubItem(pivotY);

	auto* pivotZ = new CMFCPropertyGridProperty(_T("Pivot Z"), pivotZValue, _T("Z coordinate of the pivot value."));
	pivotGroup->AddSubItem(pivotZ);

	propertiesGrid->AddProperty(pivotGroup);

	
	auto* audioGroup = new CMFCPropertyGridProperty(_T("Audio Properties"));
	
	COleVariant audioFileValue(_T("/../../."));
	auto* audioFile = new CMFCPropertyGridProperty(_T("Audio File Path"), audioFileValue, _T("Path of the Audio File."));
	audioGroup->AddSubItem(audioFile);

	COleVariant volumeValue(0.f);
	auto* volume = new CMFCPropertyGridProperty(_T("Volume"), volumeValue, _T("Volume of the audio file when played."));
	audioGroup->AddSubItem(volume);

	COleVariant pitchValue(0.f);
	auto* pitch = new CMFCPropertyGridProperty(_T("Pitch"), pitchValue, _T("Pitch of the audio file when played."));
	audioGroup->AddSubItem(pitch);

	COleVariant panValue(0.f);
	auto* pan = new CMFCPropertyGridProperty(_T("Pan"), panValue, _T("Pan of the left/right channel when played."));
	audioGroup->AddSubItem(pan);

	COleVariant oneShotValue((short)VARIANT_TRUE, VT_BOOL);
	auto* oneShot = new CMFCPropertyGridProperty(_T("One Shot"), oneShotValue, _T("Whether the audio file is one shot."));
	audioGroup->AddSubItem(oneShot);

	COleVariant playOnInitValue((short)VARIANT_TRUE, VT_BOOL);
	auto* playOnInit = new CMFCPropertyGridProperty(_T("Play On Init"), playOnInitValue, _T("Whether the audio file should play the sound when initialized."));
	audioGroup->AddSubItem(playOnInit);

	COleVariant minDistValue((long)0);
	auto* minDist = new CMFCPropertyGridProperty(_T("Minimum Distance"), minDistValue, _T("Minimum falloff distance of the sound."));
	minDist->EnableSpinControl();
	audioGroup->AddSubItem(minDist);

	COleVariant maxDistValue((long)0);
	auto* maxDist = new CMFCPropertyGridProperty(_T("Maximum Distance"), maxDistValue, _T("Maximum falloff distance of the sound."));
	maxDist->EnableSpinControl();
	audioGroup->AddSubItem(maxDist);
	
	propertiesGrid->AddProperty(audioGroup);


	auto* pathGroup = new CMFCPropertyGridProperty(_T("Path Properties"));

	COleVariant pathNodeValue((short)VARIANT_TRUE, VT_BOOL);
	auto* pathNode = new CMFCPropertyGridProperty(_T("Path Node"), pathNodeValue, _T("Whether the object is part of a node."));
	pathGroup->AddSubItem(pathNode);
	
	COleVariant pathNodeStartValue((short)VARIANT_TRUE, VT_BOOL);
	auto* pathNodeStart = new CMFCPropertyGridProperty(_T("Path Node Start"), pathNodeStartValue, _T("Whether the object is the start of a node."));
	pathGroup->AddSubItem(pathNodeStart);

	COleVariant pathNodeEndValue((short)VARIANT_TRUE, VT_BOOL);
	auto* pathNodeEnd = new CMFCPropertyGridProperty(_T("Path Node End"), pathNodeEndValue, _T("Whether the object is the end of a node."));
	pathGroup->AddSubItem(pathNodeEnd);

	COleVariant parentIDValue((long)0);
	auto* parentID = new CMFCPropertyGridProperty(_T("Parent ID"), minDistValue, _T("ID of the parent node."));
	pathGroup->AddSubItem(parentID);

	propertiesGrid->AddProperty(pathGroup);


	auto* lightGroup = new CMFCPropertyGridProperty(_T("Light Properties"));

	auto* lightDiffuse = new CMFCPropertyGridColorProperty(_T("Light Diffuse"), RGB(0, 0, 0), NULL, _T("Diffuse colour of the light."));
	lightGroup->AddSubItem(lightDiffuse);

	auto* lightSpecular = new CMFCPropertyGridColorProperty(_T("Light Specular"), RGB(0, 0, 0), NULL, _T("Specular colour of the light."));
	lightGroup->AddSubItem(lightSpecular);

	COleVariant lightSpotCutoffValue(0.f);
	auto* lightSpotCutoff = new CMFCPropertyGridProperty(_T("Light Spot Cutoff"), lightSpotCutoffValue, _T("Spot cutoff value.")); // IDK what this would do. Spotlight angle?
	lightGroup->AddSubItem(lightSpotCutoff);
	
	COleVariant lightConstantValue(0.f);
	auto* lightConstant = new CMFCPropertyGridProperty(_T("Light Constant Falloff"), lightConstantValue, _T("Constant falloff of the light."));
	lightGroup->AddSubItem(lightConstant);

	COleVariant lightLinearValue(0.f);
	auto* lightLinear = new CMFCPropertyGridProperty(_T("Light Linear Falloff"), lightLinearValue, _T("Linear falloff of the light."));
	lightGroup->AddSubItem(lightLinear);

	COleVariant lightQuadraticValue(0.f);
	auto* lightQuadratic = new CMFCPropertyGridProperty(_T("Light Quadratic Falloff"), lightQuadraticValue, _T("Quadratic falloff of the light."));
	lightGroup->AddSubItem(lightQuadratic);
	
	propertiesGrid->AddProperty(lightGroup);
}



BEGIN_MESSAGE_MAP(ObjectPropertiesDialog, CDialogEx)
END_MESSAGE_MAP()


// ObjectPropertiesDialog message handlers
