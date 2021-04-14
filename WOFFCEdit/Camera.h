#pragma once

#include "d3d11.h"
#include <SimpleMath.h>

#include "StepTimer.h"

class Camera
{
	float moveRate;
	float fastMoveMultiplier;
	float camRotRate;
	
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 lookAt;
	DirectX::SimpleMath::Vector3 lookDirection;
	DirectX::SimpleMath::Vector3 right;

	DirectX::SimpleMath::Matrix viewMatrix;

	void UpdatePositionAndRotation(DX::StepTimer const& timer);
	void UpdateViewMatrix();
public:
	Camera();
	~Camera();
	
	void Update(DX::StepTimer const& timer);

	DirectX::SimpleMath::Matrix GetCameraViewMatrix() { return viewMatrix; }
};

