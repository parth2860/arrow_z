// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotifyState_Trace.h"

//custom _notify
void UMyAnimNotifyState_Trace::trace_notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	OnNotified.Broadcast();
    //Super::trace_notify(MeshComp,Animation,EventReference);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("notify_begin_broadcast"));

}
void UMyAnimNotifyState_Trace::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	OnNotified.Broadcast();
	//Super::Notify(MeshComp, Animation, EventReference);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("notify_end_broadcast"));

}
//
void UMyAnimNotifyState_Trace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	
		if (MeshComp && MeshComp->GetOwner())
		{
			c_player = Cast<Aarrow_zCharacter>(MeshComp->GetOwner());
			if (c_player)
			{
				c_player->trace_hit();
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("notify_begin_state"));

			}
		}
	
}
void UMyAnimNotifyState_Trace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (c_player)
		{
			//c_player->DeactivateRightWeapon();
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("notify_end_state"));

		}
	}
}