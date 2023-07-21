## Puzzle3D

## 소개
젤다의 전설 : 야생의 숨결의 **아이스 메이커** 능력을 활용한 3D 퍼즐을 제작하고 싶었다.
이 능력을 활용하여 여러 장애물을 통과하는 프로토타입을 제작했다.

## 개발환경
- 언어 `C++`
- 엔진 `Unreal engine 5.1`
- IDE `Rider`

## 핵심 기능
## 아이스 큐브 생성 관리 컴포넌트(IceMakerComponent)
- 기능만을 정의하기 위해 `SceneComponent` 구현
  - Actor는 `sceneComponent`를 부착해야만 기능을 사용할 수 있도록 구현
### 생성 방식
#### 아이스 큐브(가이드라인) 생성
- 키 입력을 통한 생성/제거 기능 구현
- 플레이어의 시야로 `LineTraceSingleByChannel`을 활용하여 Visibility 채널 추적
- 충돌 위치에 가이드 라인으로 사용 될 아이스 큐브 생성
  
#### 아이스큐브 생성
- `LineTraceSingleByObjectTypeChannel`로 `Water`타입 추적
- 일치 시 충돌된 위치의 위치값과 회전값 획득
- 가이드라인 아이스 큐브와 `water`타입이 아닌 다른 엑터와의 관계에 따른 생성 가능`mCanPlace` 여부 확인
- 아이스 큐브 생성 가능 여부 시각적 확인을 위한 머테리얼 구현
<p align = "center">
    <img src="https://github.com/hoanart/Puzzle3D-Using-Unreal/assets/56676158/b8b40251-d15c-461f-82c2-70becb740b0c"  width="44%">
  <img src="https://github.com/hoanart/Puzzle3D-Using-Unreal/assets/56676158/51a3e3e2-105e-4143-b08b-4ccd13dc6c81" width="50%" >
   </p>
   
<p align = "center">
  <img src="https://github.com/hoanart/Puzzle3D-Using-Unreal/assets/56676158/28572fc5-23b0-402b-9289-770c9fbbe4b8" width="49%" >
  <img src="https://github.com/hoanart/Puzzle3D-Using-Unreal/assets/56676158/58234a61-c5cf-4cb1-9b4d-e6283d7550ba"  width="48%"> </p>
  


## 아이스 큐브 엑터
- 가이드라인 아이스 큐브의 생성 가능`mCanPlace`에 따라 레벨에 엑터 생성
- 타임라인을 조종할 수 있는 기능을 활용하여 위로 솟아오르는 박스콜리젼과 큐브 구현


## FBX
- `나이아가라 시스템`을 활용하여 폭포 구현
  
![GIFMaker_me (2)](https://github.com/hoanart/Puzzle3D-Using-Unreal/assets/56676158/24005d4b-2ae7-446e-9cca-ee1a0b4f9761)
  
-  `Water System`을 활용하여 물 구현
  
![GIFMaker_me (3)](https://github.com/hoanart/Puzzle3D-Using-Unreal/assets/56676158/712f07b6-2db5-41a5-98d2-c6fd2458ca56)


##입력 부분
- Enhanced Input을 활용하여 키입력 구현
- 움직임 : wasd
- 시야 : 마우스 움직임
- 아이스큐브 생성 : E
- 아이스큐브 생성 확인 : 가이드라인 아이스큐브 생성 상태에서 마우스 좌클
![image](https://github.com/hoanart/Puzzle3D-Using-Unreal/assets/56676158/b7e703f5-6298-45f7-a1c4-4eebc358b9a3)

## 실행 영상
[![Video Label](http://img.youtube.com/vi/UNBh0cKUr1A/0.jpg)](https://youtu.be/UNBh0cKUr1A)
