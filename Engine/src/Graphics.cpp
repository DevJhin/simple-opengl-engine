#include "Graphics.h"
#include <GL/glew.h>
#include <sstream>

#include "LightTypes.h"

Vector3 Graphics::lightDir;

Matrix4x4 Graphics::cameraViewMatrix;
Matrix4x4 Graphics::cameraProjectionMatrix;

Vector3 cameraPos;

PointLightData pointLights[4];

DirectionalLightData directionalLightData;
PointLightData pointLightData;
SpotLightData spotLightData;

Vector4 times;
Vector4 sinTimes;
Vector4 cosTimes;
Vector4 deltaTimes;

void Graphics::UpdateGlobalProperties()
{
    Camera* camera = World::GetInstance()->camera;

	for(Light* light : World::GetInstance()->lights)
	{
		switch (light->lightMode)
		{
		case LightMode::Directional:
            directionalLightData.direction = light->transform->GetForward();
			directionalLightData.color = light->color*light->intensity;
	
			break;
		case LightMode::Point:
            pointLightData.position = light->transform->GetPosition();
			pointLightData.range = light->range;
            pointLightData.color = light->color;
			break;
		case LightMode::Spot:
            spotLightData.position = light->transform->GetPosition();
            spotLightData.direction = -spotLightData.position;
            spotLightData.innerCutoffAngle = 17.5;
            spotLightData.outerCutoffAngle = 35;
			break;
		default: ;
		}
	}

	    float currentTime = Time::getCurrentTime();
	    times.x = currentTime/20;
		times.y = currentTime;
		times.z = currentTime*2;
		times.w = currentTime*3;

    float deltaTime = Time::getDeltaTime();
	deltaTimes.x = deltaTime;
	deltaTimes.y = 1.0f / deltaTime;


    sinTimes.x = Mathf::Sin(currentTime / 8);
    sinTimes.y = Mathf::Sin(currentTime / 4);
    sinTimes.z = Mathf::Sin(currentTime / 2);
    sinTimes.w = Mathf::Sin(currentTime);
	
	cosTimes.x = Mathf::Cos(currentTime/8);
    cosTimes.y = Mathf::Cos(currentTime / 4);
    cosTimes.z = Mathf::Cos(currentTime / 2);
    cosTimes.w = Mathf::Cos(currentTime);

	
    // pass projection matrix to shader (note that in this case it could change every frame)
    cameraProjectionMatrix = camera->getProjectionMatrix();
	cameraViewMatrix = camera->getViewMatrix();
    cameraPos = camera->GetTransform().GetPosition();

	GL::EnableDepthTest();
    GL::SetStencilMask(0x00);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

}

void Graphics::PostRender()
{
    GL::SetStencilMask(0xFF);
	GL::SetStencilTestMode(StencilTestMode::Always, 0xFF);
    GL::EnableDepthTest();
}

void Graphics::DrawMesh(Mesh* mesh, const Matrix4x4& modelMatrix, Material* material)
{

	Shader* shader = material->getShader();
	if(shader->useDepthMode)
	{
		GL::EnableDepthTest();
        GL::SetStencilTestMode(StencilTestMode::Always, 0xFF);
		GL::SetStencilMask(0x00);
		GL::SetDepthTestMode(shader->depthTestMode);
	}
	else
	{
        GL::DisableDepthTest();
	}
	
    if (shader->useStencilMode)
    {
        GL::EnableStencilTest();
        GL::SetStencilTestMode(shader->stencilMode,0xFF);
        GL::SetStencilMask(shader->stencilMask);
    }
	else
	{
		GL::DisableStencilTest();
	}
	
	material->Use();

	// pass projection matrix to shader (note that in this case it could change every frame)
	material->SetMat4("projection", cameraProjectionMatrix);
	
	material->SetMat4("view", cameraViewMatrix);
	
	material->SetMat4("model", modelMatrix);
	
	

    material->SetVec3("viewPos", cameraPos);

    material->SetFloat("material.shininess", 16);
	
    // transfer lighting parameters to fragment shader
    // directional light
    material->SetVec3("dirLight.direction", directionalLightData.direction);
    material->SetVec3("dirLight.diffuse", directionalLightData.color);
    material->SetVec3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
    material->SetVec3("dirLight.specular", 0.9f, 0.9f, 0.9f);
	
    // point light
    material->SetFloat("pointLights[0].range", pointLightData.range);
	
    material->SetVec3("pointLights[0].position", pointLightData.position);
    material->SetVec3("pointLights[0].diffuse", pointLightData.color);
    material->SetVec3("pointLights[0].ambient", 0.0f, 0.0f, 0.0f);
    material->SetVec3("pointLights[0].specular", 0.5f, 0.5f, 0.5f);
	
    material->SetFloat("pointLights[0].constant", 1.0f);
    material->SetFloat("pointLights[0].linear", 0.09);
    material->SetFloat("pointLights[0].quadratic", 0.032);

    // spot light
    material->SetVec3("spotLights[0].position", spotLightData.position);
    material->SetVec3("spotLights[0].direction", spotLightData.direction);
	
    material->SetVec3("spotLights[0].ambient", 0.0f, 0.0f, 0.0f);
    material->SetVec3("spotLights[0].diffuse", 0.9f, 0.3f, 0.6f);
    material->SetVec3("spotLights[0].specular", 1.0f, 1.0f, 1.0f);

    material->SetFloat("spotLights[0].constant", 1.0f);
    material->SetFloat("spotLights[0].linear", 0.14);
    material->SetFloat("spotLights[0].quadratic", 0.07);

    material->SetFloat("spotLights[0].innerCutoffAngle", Mathf::Cos(spotLightData.innerCutoffAngle*Mathf::Deg2Rad));
    material->SetFloat("spotLights[0].outerCutoffAngle", Mathf::Cos(spotLightData.outerCutoffAngle*Mathf::Deg2Rad));

	material->SetVec4("Times", times);
	material->SetVec4("SinTimes", sinTimes);
	material->SetVec4("CosTimes", cosTimes);
	
	/*Bind textures*/
    auto textures = material->GetTextures();

    const uint textureSize = textures.size();
	
    for (uint i = 0; i < textureSize; i++)
    {
       BindTexture(textures[i],i,material);
    }


	/*Draw indices*/
	mesh->bindVertexArray();
	GL::DrawElements(mesh->getMeshTopology(), mesh->indicesCount());
    glBindVertexArray(0);

    // Always good practice to set everything back to defaults once configured.
    for (uint i = 0; i < textureSize; i++)
    {
        GL::ActiveTexture(i);
    	
        Texture::Unbind();
    }

}



void Graphics::BindTexture(Texture* texture, uint index, Material* mat)
{
    GL::ActiveTexture(index);
    Texture::Bind(texture);

}

