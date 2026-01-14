// Copyright Epic Games, Inc. All Rights Reserved.


#include "ReflectionGameModeBase.h"
#include "MyActor.h"

AReflectionGameModeBase::AReflectionGameModeBase()
{
    NewObject<AMyActor>();

 //   UFunction* Fun = FindObject<UFunction>(ANY_PACKAGE, TEXT("Eee"));
 //   UFunction* eee = (UFunction*)StaticFindObjectFast(UFunction::StaticClass(), nullptr,FName("Eee"), false
 //       , true, RF_Transient);
	//Fun->ChildProperties;
	//AMyActor*myactor=NewObject<AMyActor>();
 //   TTuple<int,int>tuple(10,10);
 //  /* CallUFunction2(TEXT("ttt"),tuple,1,2);
	//UE_LOG(LogTemp,Warning,TEXT("%s"),*myactor->GetName());*/
 //   int32 i = 8;
 //   void* c=&tuple;
	//InvokeFunctione(AMyActor::StaticClass(),nullptr, Fun,tuple,1,2);
   
   /* UE_LOG(LogTemp, Warning, TEXT("%i"),*(((uint8*)c)));*/
}

//template<typename...TReturns,typename... TArgs>
//void AReflectionGameModeBase::InvokeFunctione(UClass* objClass, UObject* obj, UFunction* func,TTuple<TReturns...>& outParams,TArgs&&... args)
//{
//    objClass = obj != nullptr ? obj->GetClass() : objClass;
//    UObject* context = obj != nullptr ? obj : objClass;
//   /* UE_LOG(LogTemp, Warning, TEXT("%s"), *objClass->GetName());*/
//   
//    uint8* outPramsBuffer = (uint8*)&outParams;
//
//    //if (func->HasAnyFunctionFlags(FUNC_Native)) //quick path for c++ functions
//    //{
//        TTuple<TArgs..., TReturns...> params(Forward<TArgs>(args)..., TReturns()...);
//        context->ProcessEvent(func, &params);
//        //copy back out params
//        for (TFieldIterator<FProperty> i(func); i; ++i)
//        {
//            FProperty* prop = *i;
//            if (prop->PropertyFlags & CPF_OutParm)
//            {
//                void* propBuffer = prop->ContainerPtrToValuePtr<void*>(&params);
//                prop->CopyCompleteValue(outPramsBuffer, propBuffer);
//                outPramsBuffer += prop->GetSize();
//            }
//        }
//        return;
//   /* }*/
//}
//
//void AReflectionGameModeBase::StartPlay()
//{
//    UFunction* eee = (UFunction*)StaticFindObjectFast(UFunction::StaticClass(), nullptr, TEXT("TTTR"), false, true, RF_Transient);
//    TTuple<int, int>tuple(10, 10);
//    InvokeFunctione(nullptr, nullptr, eee, tuple, 1, 2);
//    UE_LOG(LogTemp, Warning, TEXT("%s"),*eee->GetName());
//
//}
