// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "arrow_zCharacter.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MyAnimNotifyState_Trace.generated.h"

/**
 *
 */
DECLARE_MULTICAST_DELEGATE(FOnNotifiedSignature);//custom notify

UCLASS()
class ARROW_Z_API UMyAnimNotifyState_Trace : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:

	//custom notify
	FOnNotifiedSignature OnNotified;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference); //override;
	virtual void trace_notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
	//
	UPROPERTY()
	Aarrow_zCharacter* c_player;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	//

};
