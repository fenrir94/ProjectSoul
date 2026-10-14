// All Rights Reserved.


#include "Characters/HeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CineCameraComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/SoulInputComponent.h"
#include "SoulGameplayTags.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "SoulFunctionLibrary.h"
#include "Components/UI/HeroUIComponent.h"
#include "Components/TargetLock/SoulTargetLockComponent.h"

#include "DebugHelper.h"

AHeroCharacter::AHeroCharacter()
{

	GetCapsuleComponent()->InitCapsuleSize(36.f, 88.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 60.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//CineCamera = CreateDefaultSubobject<UCineCameraComponent>(TEXT("CineCamera"));
	//CineCamera->SetupAttachment(GetMesh(), TEXT("head"));
	//CineCamera->SetActive(false);

	//CineCamera->PostProcessSettings.bOverride_VignetteIntensity = true;
	//CineCamera->PostProcessSettings.VignetteIntensity = 0.7f;
	//
	//CineCamera->PostProcessSettings.bOverride_ColorGamma = true;
	//CineCamera->PostProcessSettings.ColorGamma = FVector4(0.8f, 0.8f, 0.8f, 1.f);


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));

	HeroUIComponent = CreateDefaultSubobject<UHeroUIComponent>(TEXT("HeroUIComponent"));

	TargetLockComponent = CreateDefaultSubobject<USoulTargetLockComponent>(TEXT("TargetLockComponent"));
}

UPawnCombatComponent* AHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

UPawnUIComponent* AHeroCharacter::GetPawnUIComponent() const
{
	return HeroUIComponent;
}

UHeroUIComponent* AHeroCharacter::GetHeroUIComponent() const
{
	return HeroUIComponent;
}

void AHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(SoulAbilitySystemComponent);
		}
	}
}

void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"));
	ULocalPlayer* LocalPlayer =  GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	USoulInputComponent* SoulInputComponent = CastChecked<USoulInputComponent>(PlayerInputComponent);

	SoulInputComponent->BindNativeInputAction(InputConfigDataAsset, SoulGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	SoulInputComponent->BindNativeInputAction(InputConfigDataAsset, SoulGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	SoulInputComponent->BindNativeInputAction(InputConfigDataAsset, SoulGameplayTags::InputTag_Interact, ETriggerEvent::Started, this, &ThisClass::Input_Interact);

	SoulInputComponent->BindNativeInputAction(InputConfigDataAsset, SoulGameplayTags::InputTag_OpenMenu, ETriggerEvent::Started, this, &ThisClass::Input_OpenMenu);

	SoulInputComponent->BindNativeInputAction(InputConfigDataAsset, SoulGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwitchTargetTriggered);
	SoulInputComponent->BindNativeInputAction(InputConfigDataAsset, SoulGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwitchTargetCompleted);

	SoulInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);

}

void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AHeroCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (USoulFunctionLibrary::IsTargetPawnHostile(this, HitPawn))
		{
			HeroCombatComponent->OnHitTargetActor(HitPawn);
		}
	}
}

void AHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}

}

void AHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	
	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AHeroCharacter::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
}

void AHeroCharacter::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
}

void AHeroCharacter::Input_OpenMenu_Implementation(const FInputActionValue& InputActionValue)
{

}


void AHeroCharacter::Input_Interact_Implementation(const FInputActionValue& InputActionValue)
{	
	//스피어 트레이스 길이 구하기 = 플레이어 로케이션 부터 플레이어 로케이션 + 액터의 포워드 벡터 * 지정한 변수 
	FVector TraceStartVec = GetActorLocation();
	FVector TraceEndVec = TraceStartVec + GetActorForwardVector() * InteractRange;

	//트레이스 무시해야 하는 액터 목록 + 자기자신은 트레이스에 감지되지 않도록, 배열에 추가
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	// 트레이스 결과값 저장하는 변수. (어떤 액터가 잡혔는지)
	FHitResult InteractHitResult; 

	//트레이스 실행 + bInteractHit 에실행 결과 저장

	bool bInteractHit = UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		TraceStartVec,
		TraceEndVec,
		SphereRadius,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), //GameTraceChannel1 = Interact 트레이스 채널.
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		InteractHitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		TraceDuration);


	// 스피어 트레이스에 뭔가 감지 되었다면
	if (bInteractHit)
	{
		//감지된 액터를 가져와서, hit actor에 저장
		AActor* HitActor = InteractHitResult.GetActor();
		UClass* BPInterfaceClass = StaticLoadClass(UClass::StaticClass(), nullptr, TEXT("/Game/Interface/BPI_Interact.BPI_Interact_C"));

		if (!BPInterfaceClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("bad!!!"));
			return;
		}

		//감지된 액터가 상호작용 인터페이스를 가지고 있다면
		if (BPInterfaceClass && HitActor && HitActor->GetClass()->ImplementsInterface(BPInterfaceClass))
		{
			UE_LOG(LogTemp, Warning, TEXT("good!!!"));

			//hit actor를 interacting actor. 즉 상호작용할 대상으로 지정.
			InteractingActor = HitActor;
		}
		else
		{
			//인터페이스가 없으면, 상호작용 대상을 비워준다.
			InteractingActor = nullptr;
		}
	}
	else
	{
		//스피어 트레이스에 아무것도 감지되지 않았다면 , 상호작용 대상을 비워준다.
		InteractingActor = nullptr;
	}


	// interacting actor 변수가 null이 아니면 interact_interface 내의 함수, interact with  함수 발동. + interacting actor 변수를 interact with 변수에 전달(미구현)

}

void AHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	SoulAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	//Debug::Print(InInputTag.ToString());

	SoulAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}
