# simple-opengl-engine
 컴퓨터 그래픽스 수업때 배운 내용을 바탕으로 제작한 OpenGL 게임 
 
|기능|구현여부|구현 위치|비고|
|:--:|:--:|:--:|:--:|
|Vertex Shaders  |O|Unlit.vert,Standard.vert, Anim.vert|셰이더는 Engine\resources\shaders\built-in 폴더에 존재|
|Fragment Shaders |O|Unlit.frag, Standard.frag, Anim.frag|셰이더는 Engine\resources\shaders\built-in 폴더에 존재|
|Transformations |O|Transform.cpp, ||
|Viewing(Camera) |O|Camera.cpp, Graphics.cpp||
|Texture|O|Texture.cpp, Resources.cpp||
|Lighting|O|Light.cpp, Material.cpp, Graphics.cpp||
|Model Loading|O|Resources.cpp, GameScene.cpp|렌더링 쪽은 Graphics.cpp 참고|
|Animation|O|Animation.cpp, Animator.cpp, Transform.cpp|키프레임 기반|

추가 기능 - **자세한 내용은 하단의 내용 참고**

|기능|구현여부|구현 위치|비고|
|:--:|:--:|:--:|:--:|
|Game 객체|O|APlayer.cpp, AObstacle.cpp||
|Collision Detection |O|Physics.cpp|Sphere Collision Detection 구현|
|Animated Shader|O|Graphics.cpp|Animation을 사용하는 Shader(Anim.vert 등)|
|OOP Engine System|O|프로그램 전체 구조|하단의 ''엔진 구조 및 구현' 목차 참고|

* 소스코드는 Engine/src 폴더에 존재하며, 기하/수학 관련 코드만 Mathematics/src 폴더에 존재합니다.
* 쉐이더 소스는 Engine\resources\shaders\built-in/shaders폴더의 Standard.frag(vert) 파일 참고


## Build 주의사항
#### Unity Build
컴파일 속도를 향상시키기 위해,  모든 Cpp 파일을 unity_build.cpp 파일 하나에 몰아넣고, 한 번에 컴파일하는 Unity Build를 사용합니다.

프로젝트 설정을 해놓은 상태로 전달해 드릴 것이기 때문에 딱히 건드릴 것은 없지만, 만약 프로젝트 설정이 올바르게 되어있지 않다면 'unity_build.cpp' 파일을 제외한 모든 cpp 파일을 빌드에서 제외시켜 주시기 바랍니다.


## 게임 설명
1. 게임이 시작되면, 플레이어는 다가오는 장애물을 피해야 합니다.
시간이 지날수록 장애물들의 속도와 숫자가 증가하여 난이도가 어려워 집니다.

2. 방향키를 입력하여 플레이를 움직여서 피할 수 있습니다.

3. 장애물과 충돌하게 되면 게임이 종료됩니다.

4. 일정시간 이상 생존했다면, 게임에서 승리합니다.


## 게임 객체 설명
이 게임에는 플레이어, 장애물 두 가지의 주요한 게임 객체가 존재합니다.

#### 1. Character
사용자가 컨트롤 할 수 있는 주요 게임 개체입니다. Player는 사용자의 Input을 받아 움직이며, 게임 상태와 관련된 정보를 가집니다. 또한, Obstacle과 충돌했을 경우 피격 판정을 수행합니다.

```Cpp
APlayer* playerActor = new APlayer();
playerActor->speed = 1;
playerActor->collisionRadius = 0.75f;
...
```
#### 2. Obstacles
Obstacle은 플레이어를 향해 움직이는 개체이며, Player와 충돌했는지 검사하는 충돌판정을 수행합니다. Obstacle은 키프레임 애니메이션에 의해 움직입니다.

```Cpp
AObstacle* obstacle = new AObstacle();
obstacle->collisionRadius = 0.35f;
Animator* animator = obstacle->AddComponent<Animator>();
...
```

## 기본 구현 설명

### 1,2. Vertex & Fragment Shader
이번 과제에서는 라이팅/텍스처를 활용하는 Standard 셰이더 와 라이팅을 활용하지 않는 Unlit 셰이더를 주로 사용합니다. Unlit Shader는 단일 색만 출력하기 때문에 Model, View, Projection 정보만 있으면 충분하지만, Standard Shader는 Lighting 연산을 위해 주어진 Mesh의 Traingles, TexCoord, Normal 정보까지 활용합니다.


### 3. Transformations
사실, Transform이 표현하는 Translation, Rotation, Scale 개념을 Matrix의 형태로 다루는 것은 쉽지 않습니다. 따라서, 이 프로젝트에서는 Transform을 쉽게 다룰 수 있도록 설계하였습니다. 유니티나 Unreal Engine에서 처럼, 복잡한 Matrix 변환 작업은 엔진 내부에서만 다루고, 사용자는 position, rotation, scale이라는 세 가지 개념만 다루면 됩니다. Rotation의 경우, Quaternion을 사용하기 때문에 쉽게 회전을 다룰 수 있습니다.

```Cpp
Vector3 position;
Quaternion rotation;
Vector3 scale;

void Transform::SetPosition(const Vector3& position)
{
	this->position = position;
	//위치 변경시마다 Matrix 연산을 수행하는 것이 아니라, dirty flag 만 설정해준다.
	hasTransformChanged = true;
}
```
또한, position, rotation, scale을 Matrix를 변환하는 작업은 Matrix 가 사용될 때에만 수행할 수 있도록 하여 성능을 개선하였습니다.

```Cpp
//Only called when model matrix is needed
void Transform::updateTRS()
{
	worldMatrix = QuatMath::TRS(position, rotation, scale);
	hasTransformChanged = false;
}

```

### 4. Viewing(Camera)
Camera 객체의 Transform을 바탕으로 View/Projection Matrix를 계산합니다. 자세한 구현은
Camera.cpp를 참고해 주시기 바랍니다.


### 5. Texture
1. 모델의 텍스처를 로드합니다.

```Cpp
unsigned char* image = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

```

2. OpenGL을 통해 각각의 Texture를 생성하고, 로드한 이미지 데이터를 적용한다.

```Cpp
//Texture는 Opengl의 TextureID를 Wrapping한 클래스
Texture* texture = new Texture(width, height, 0, format);
texture->SetPixels(image);
```

3. 생성한 Texture를 Material에 추가한다.

```Cpp
Material* playerMaterial = playerMaterial->copy();
playerMaterial->GetTextures().push_back(playerModelTexture);
```

4. Rendering Phase에서 Material에 설정한 텍스처를 활성화 시키고, Bind한다.

```Cpp
for (uint i = 0; i < textureSize; i++)
{
   BindTexture(textures[i],i,material);
}

```


### 6. Lighting
1. Point Light와 Directional Light를 생성합니다. (엔진 시스템상, Light가 생성되면 자동으로 Rendering 과정에서 Light 데이터를 전달함)

```cpp
//Create Sun Point Light (HWScene.cpp)
Light* sunPointLight = sun->AddComponent<Light>();

sunPointLight->lightMode = LightMode::Point;
sunPointLight->intensity = 2.0f;
sunPointLight->color = Vector3(0.75f, 0.5f, 0.1f);
sunPointLight->range = 50;

```

2. 메시를 그리기 전에, 각 Light가진 정보를 바탕으로 Shader의 uniform 변수를 설정한다.

```cpp
// point light (Graphics.cpp)
 material->SetFloat("pointLights[0].range", pointLightData.range);

 material->SetVec3("pointLights[0].position", pointLightData.position);
 material->SetVec3("pointLights[0].diffuse", pointLightData.color);

 material->SetFloat("pointLights[0].constant", 1.0f);
...
```

3. Shader를 바탕으로 렌더링을 수행합니다.

```cpp
// 쉐이더 코드 일부 (Standard.frag)
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);

```

### 7. Model Loading
수업에서 활용한 assimp 라이브러리를 사용해서 Model을 로드합니다. 자세한 구현은 Resources.h를 참고해주세요.

```cpp
ModelData* modelData = Resources::LoadModel("PlayerModel.obj");
```


### 8. Animation
수업에서 학습한 Keyframe Animation 을 기반으로 하는 Animation 작업을 수행합니다.
Keyframe 데이터를 관리하는 Animation 객체와 Animation에 따라 실제 모델을 움직이는 Animator로 구현되어 있습니다.


```Cpp
//Animation에서 현재 시간에서의 키프레임 정보 가져옴.
Vector3 position = animation->GetPos(time);
Quaternion rotation = animation->GetRotation(time);

//Actor의 Transform에 적용.
transform->SetPosition(position);
transform->SetRotation(rotation);
```



# 추가 기능 설명

1. 충돌 판정
2. 애니메이션 셰이더
3. OpenGL을 객체지향적으로 재구성한 엔진 시스템


## 추가기능 1: 충돌 판정
이번 프로젝트에서 가장 중요한 작업 중 하나인 충돌판정을 구현하였습니다.
수업 초에 배웠던 두 2D Circle이 서로 겹치는지 확인하는 작업을 확장하여
3D 공간 상에서 Sphere과 Sphere 사이의 거리와 각각의 반경을 확인하여 충돌판정을 수행합니다.

```cpp
for(Actor* actor: actors)
{
	if(actor->tag == "Obstacle")
	{
		if(Physics::CheckCollision(playerActor, actor))
		{
			Damage();
		}
	}
}

```


## 추가 기능2: Animated Shader
보통 애니메이션이라고 하면 Transformation으로 모델(Mesh)을 움직이는 것을 생각하겠지만, 사실 Shader를 활용해서도 Animation을 구현할 수도 있습니다. 예를 들어, Fragment Shader에 주어진 Texture coordinate 좌표를 주기적으로 움직이게 만들면, 모델의 텍스처가 스스로 움직이는 것처럼 보이게 만들 수 있습니다. 이러한 Animation 기능을 셰이더에 적용하기 위해서는 Time 등의 추가적인 시간정보를 가져와서 셰이더에서 시간에 따라 다른 모습을 보이도록 처리하는 작업이 필요합니다.

### 과정

1. 매 렌더링 업데이트 마다 시간 정보를 업데이트합니다. Shader에서의 연산을 줄이기 위해, 자주 사용할 것 같은 연산은 미리 CPU에서 연산하여 모든 셰이더에서 공유할 수 있도록 합니다.
```cpp
  float currentTime = Time::getCurrentTime();
  times.x = currentTime/20;
	times.y = currentTime;
	times.z = currentTime*2;
	times.w = currentTime*3;
```

2. 매터리얼을 통하여 unifrom variable로 이 값을 전달합니다.
```cpp
	material->SetVec4("Times", times);
	material->SetVec4("SinTimes", sinTimes);
	material->SetVec4("CosTimes", cosTimes);
```

3. Texture coordinate가 경과 시간에 비례하여 움직이도록 Shader 코드를 작성합니다.
``` Cpp
//매 시간마다 TexCoords의 값이 달라짐에 유의
		vec2 NewTexCoords = TexCoords + vec2(Times.x, Times.x)
    vec3 mainColor = vec3( texture( material.diffuse, TexCoords + NewTexCoords ));
```

AnimSpeed와 같이 추가적인 변수를 제공하면 애니메이션의 속도를 조절할 수도 있습니다.


## 추가 기능 3: 엔진 시스템 및 구조
OpenGL의 기능을 객체지향적으로 디자인하고, 이들을 편리하게 활용할 수 있도록 추상화하는 것이 목적으로 제작되었습니다.

### 업데이트 루프
렌더링 주기에 맞추어 다양한 기능들을 수행할 수 있도록, 업데이트 루프 시스템이 구현되어 있습니다.

```Cpp
// 마다 실행.
void World::Update()
{
  // Input 갱신
  Input::update();

  //생성된 Actor 관련 처리
  ProcessStartActors();

  //Actor 업데이트
  UpdateActors();

  //컴포넌트 업데이트
  UpdateComponents();

  //렌더링 Phase 수행
  Render();

}
```


### Actor (구현: Actor.cpp)
Actor는 엔진에서 다루어지는 가장 기본적인 객체입니다. Actor 클래스를 상속받은 객체는 Start 함수와 Update함수를 오버라이드할 수 있으며, 이들은 아래와 같은 기능을 수행합니다.

`Start()`

처음 프로그램이 실행될 때, 한 번 실행되는 함수입니다. 데이터를 로드하거나 초기화하는 기능을 구현할 때 사용합니다.

`Update()`

매 프레임마다 렌더링 전에 한 번씩 실행되는 함수입니다. 렌더링 주기에 맞추에 수행해야 하는 기능(Animation)을 구현할 때 사용할 수 있습니다.


|클래스|기능|구현 위치|
|:--:|:--:|:--:|
|APlayer|플레이어의 캐릭터를 정의한 Actor|Aplayer.cpp|
|AObstacle|장애물 오브젝트를 정의한 Actor|AObstacle.cpp|
|Camera|View와 관련된 정보를 관리하는 Actor|Camera.cpp|

### Component (구현: Component.cpp)
Component는 Actor의 부분적인 동작을 구성하는 객체입니다. 하나의 Actor는 여러개의 Component를 가지며, 이를 통해 다양한 동작을 수행할 수 있을 뿐만 아니라, 기능을 공유할 수도 있습니다.

|클래스|기능|구현 위치|
|:--:|:--:|:--:|
|Renderer|주어진 Mesh와 Material으로 Rendering을 수행하는 Component|Renderer.cpp|
|Light|빛과 관련된 기능을 수행하는 Component|Light.cpp, Graphics.cpp|
|Animator|주어진 Animation 객체를 가지고 Animation 작업을 실제로 수행|Animator.cpp|


### Object (구현 : Object.cpp)
엔진에서 사용되는 객체입니다. OpenGL에서 사용되는 자료들을 객체지향적으로 재구성한 것이 대부분입니다.

|클래스|기능|구현 위치|
|:--:|:--:|:--:|
|Transform|3D Transform 작업을 수행하는 객체|Transform.cpp|
|GameScene|게임 실행에 필요한 객체를 초기화.|GameScene.cpp|
|Mesh|IBO등의 객체화. 렌더링할 Mesh 데이터를 관리.|Mesh.cpp|
|Texture|TextureID 객체화.|Texture.cpp, Resources.cpp|
|Shader|Compile된 ShaderID 객체화. Material을 생성할 때 사용.|Shader.cpp, ShaderUtils.cpp|
|Material|ShaderProgramID 객체화. Rendering할 때 사용.|Material.cpp|
|Animation|Keyframe 애니메이션 정보를 가지고 있는 객체|Animation.cpp|


### 그 외
|이름|기능|구현 위치|
|:--:|:--:|:--:|
|Application|OpenGL 초기화 등 애플리케이션 실행에 필요한 작업을 수행|Application.cpp|
|Resources|Mesh, Texture등을 로드하는 기능 수행|Resources.h|
|Grahpics|구체적인 Rendering 작업 수행(Mesh Rendering, Unifrom Variable 처리 등)|Graphics.cpp|
|Input|사용자의 Input을 관리합니다|Input.cpp|
|Time|프레임 시간 간격 등, 유용한 시간 데이터를 관리합니다|Time.cpp|
|GL|OpenGL의 주요 기능을 Wrapping한 클래스|GL.cpp|
|Physics|충돌판정 알고리즘 수행|Physics.cpp|

