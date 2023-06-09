// Copyright Epic Games, Inc. All Rights Reserved.

#include "TwoBetterThanOneCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


//////////////////////////////////////////////////////////////////////////
// ATwoBetterThanOneCharacter

ATwoBetterThanOneCharacter::ATwoBetterThanOneCharacter()
	:CanInteract(false),
	ObjectToTakeDetected(false),
	AbleToTakeObject(true),
	GrabbedObjectDistance(90.f),
	ArmReach(150.f)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	InteractionCooldownRemaining = 0.f;
	InteractionCooldown = 2.0f;
}

void ATwoBetterThanOneCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	CheckpointLocation = GetActorLocation();
}

void ATwoBetterThanOneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InteractionCooldownRemaining > 0)
	{ 
		InteractionCooldownRemaining -= DeltaTime;
		if (InteractionCooldownRemaining <= 0)
			InteractionButtonPressed = false;
	}

	if (AbleToTakeObject)
		LookForObject();
	else
	{
		GrabbedObjectLocation = GetActorLocation() + GetActorForwardVector() * GrabbedObjectDistance;
		GrabbedObjectLocation.Z = GetActorLocation().Z;
		MoveGrabbedObject();
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATwoBetterThanOneCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Interacting
EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ATwoBetterThanOneCharacter::Interact);

//MoveObject
EnhancedInputComponent->BindAction(MoveObjectAction, ETriggerEvent::Started, this, &ATwoBetterThanOneCharacter::TakeObject);

//Moving
EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATwoBetterThanOneCharacter::Move);

//Looking
EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATwoBetterThanOneCharacter::Look);

	}

}

void ATwoBetterThanOneCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATwoBetterThanOneCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATwoBetterThanOneCharacter::Interact()
{
	if (CanInteract && !InteractionButtonPressed)
	{
		InteractionButtonPressed = true;
		InteractionCooldownRemaining = InteractionCooldown;
		NotifyInteraction();
	}
}

void ATwoBetterThanOneCharacter::ChangeCanInteract()
{
	CanInteract = !CanInteract;
}

void ATwoBetterThanOneCharacter::RestartLocation()
{
	SetActorLocation(CheckpointLocation);
}

void ATwoBetterThanOneCharacter::LookForObject()
{

	RaycastStart = GetActorLocation() + GetActorForwardVector() * 40;
	RaycastEnd = RaycastStart + GetActorForwardVector() * ArmReach;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, RaycastStart, RaycastEnd, ECollisionChannel::ECC_GameTraceChannel1))
	{
		//DrawDebugPoint(GetWorld(), RaycastStart, 10, FColor::Blue, true);
		//DrawDebugPoint(GetWorld(), RaycastEnd, 10, FColor::Purple, true);
		//DrawDebugPoint(GetWorld(), Hit.Location, 10, FColor::Orange, true);

		if (HitResult.GetActor())
		{
			ObjectToTakeDetected = true;
			ActorHited = HitResult.GetActor();
		}
		else
			ObjectToTakeDetected = false;

	}
}

void ATwoBetterThanOneCharacter::TakeObject()
{
	/*if (ObjectToTakeDetected && AbleToTakeObject)
	{
		if (ActorHited->ActorHasTag("Grabbable"))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Taking Object"));
			AbleToTakeObject = false;
			BP_TakeObject();
		}
		else
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("The object is not grabbable"));

	}
	else if(!AbleToTakeObject)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, TEXT("Releasing Object"));
		GrabbedObjectLocation = { 0.f, 0.f, 0.f };
		AbleToTakeObject = true;
		ObjectToTakeDetected = false;
		ReleaseObject();
	}*/
}
