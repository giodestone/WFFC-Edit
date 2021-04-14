#include "stdafx.h"

#include "Camera.h"

#include "ToolMain.h"

Camera::Camera()
	: moveRate(18.f)
	, fastMoveMultiplier(2.f)
	, camRotRate(180.f)
	, position(0.f, 3.7f, -3.5f)
	, rotation(0.f, 0.f, 0.f)
{
}

Camera::~Camera()
{
}

void Camera::UpdatePositionAndRotation(DX::StepTimer const& timer)
{
	using namespace DirectX;

	auto inputCommands = ToolMain::GetInstance()->GetInputCommands();

	if (inputCommands.forward)
	{
		auto radians = rotation.y * 0.0174532f;

		// Update the position.
		position.x -= sinf(radians) * moveRate * static_cast<float>(timer.GetElapsedSeconds());
		position.z -= cosf(radians) * moveRate * static_cast<float>(timer.GetElapsedSeconds());
	}
	if (inputCommands.back)
	{
		auto radians = rotation.y * 0.0174532f;

		// Update the position.
		position.x += sinf(radians) * moveRate * static_cast<float>(timer.GetElapsedSeconds());
		position.z += cosf(radians) * moveRate * static_cast<float>(timer.GetElapsedSeconds());
	}
	if (inputCommands.right)
	{
		// Convert degrees to radians.
		auto radians = rotation.y * 0.0174532f;

		// Update the position.
		position.z -= sinf(radians) * moveRate * static_cast<float>(timer.GetElapsedSeconds());
		position.x += cosf(radians) * moveRate * static_cast<float>(timer.GetElapsedSeconds());
	}
	if (inputCommands.left)
	{
		// Convert degrees to radians.
		auto radians = rotation.y * 0.0174532f;

		// Update the position.
		position.z += sinf(radians) * moveRate * static_cast<float>(timer.GetElapsedSeconds());
		position.x -= cosf(radians) * moveRate * static_cast<float>(timer.GetElapsedSeconds());
	}
	if (inputCommands.up)
	{
		position.y += moveRate * static_cast<float>(timer.GetElapsedSeconds());
	}
	if (inputCommands.down)
	{
		position.y -= moveRate * static_cast<float>(timer.GetElapsedSeconds());
	}


	if (inputCommands.rotRight)
	{
		rotation.y -= camRotRate * static_cast<float>(timer.GetElapsedSeconds());
	}
	if (inputCommands.rotLeft)
	{
		rotation.y += camRotRate * static_cast<float>(timer.GetElapsedSeconds());
	}
	if (inputCommands.rotUp)
	{
		rotation.z += camRotRate * static_cast<float>(timer.GetElapsedSeconds());
	}
	if (inputCommands.rotDown)
	{
		rotation.z -= camRotRate * static_cast<float>(timer.GetElapsedSeconds());
	}
}

void Camera::UpdateViewMatrix()
{
	using namespace DirectX;

	XMVECTOR up, positionv, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	// Setup the vectors
	up = XMVectorSet(0.0f, 1.0, 0.0, 1.0f);
	positionv = XMLoadFloat3(&position);
	lookAt = XMVectorSet(0.0, 0.0, 1.0f, 1.0f);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = rotation.x * 0.0174532f;
	yaw = rotation.y * 0.0174532f;
	roll = rotation.z * 0.0174532f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	up = XMVector3TransformCoord(up, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = positionv + lookAt;

	// Finally create the view matrix from the three updated vectors.
	viewMatrix = XMMatrixLookAtLH(positionv, lookAt, up);
}

void Camera::Update(DX::StepTimer const& timer)
{
	UpdatePositionAndRotation(timer);
	UpdateViewMatrix();	
}
