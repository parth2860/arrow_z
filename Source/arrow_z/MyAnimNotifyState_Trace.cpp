// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotifyState_Trace.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "arrow_zCharacter.h"
#include "cp_mesh.h"
#include "Engine/Engine.h"
//using namespace UGameplayStatics;
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
				//c_player->trace_hit();
				//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("notify_begin_state"));

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
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("notify_end_state"));

		}
	}
}
void UMyAnimNotifyState_Trace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	//c_weapon->second_trace(); //EXCEPTION_ACCESS_VIOLATION reading address 0x0000000000000420


	if (MeshComp && MeshComp->GetOwner())
	{
		c_player = Cast<Aarrow_zCharacter>(MeshComp->GetOwner());
		if (c_player)
		{
			c_player->trace_hit();
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("notify_tick_state"));

		}
	}
	if (MeshComp && MeshComp->GetOwner())
	{
		//c_player = Cast<Aarrow_zCharacter>(MeshComp->GetOwner());//undefined
		//AActor* otheractor;//undefined
		//
		//Acp_mesh* C_WEAPON = Cast<Acp_mesh>(MeshComp->GetOwner());//doent work
		//UStaticMeshComponent* meshp;//uninilitilized used
		//UStaticMesh* meshp;//uninilitilized used
		//Acp_mesh* C_WEAPON = Cast<Acp_mesh>(meshp);//uninilitilized used
		//Acp_mesh* C_WEAPON = Cast<Acp_mesh>(UGameplayStatics::GetActorOfClass(GetWorld(), Acp_mesh::StaticClass()));//A null object was passed as a world context object to UEngine::GetWorldFromContextObject()
		// c_weapon->second_trace();//0013!UMyAnimNotifyState_Trace::NotifyTick() [D:\Users\PARTH\Documents\Unreal Projects\c++\arrow_z\Source\arrow_z\MyAnimNotifyState_Trace.cpp:116]
		//Acp_mesh* C_WEAPON = Cast<Acp_mesh>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));//doent work
		//Acp_mesh* C_WEAPON = Cast<Acp_mesh>(UGameplayStatics::GetActorOfClass(Acp_mesh::StaticClass(),0));
		/*
		if(C_WEAPON)
		{ 
			C_WEAPON->second_trace();
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("notify_tick_state_succeded"));

		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("notify_tick_state_failed"));
		}
		*/
		

	}
	
	/*
	Aarrow_zCharacter* PlayerCharacter = Cast<Aarrow_zCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));//null references
	//ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);//null object references
	//ACharacter* PlayerCharacter;//uninitilized
	if (PlayerCharacter)
	{
		Acp_mesh* c_wp = Cast<Acp_mesh>(PlayerCharacter);
		if (c_wp)
		{
			// Successfully casted to Acp_mesh
			UE_LOG(LogTemp, Warning, TEXT("casting success PlayerCharacter to Acp_mesh."));

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to cast PlayerCharacter to Acp_mesh."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter is null."));
	}
	*/
	
}
void UMyAnimNotifyState_Trace::StartTracing(USkeletalMeshComponent* MeshComp)
{


}
void UMyAnimNotifyState_Trace::StopTracing(USkeletalMeshComponent* MeshComp)
{
}