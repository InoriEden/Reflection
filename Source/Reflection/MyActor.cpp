// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"



// Sets default values
AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
 {
	Super::BeginPlay();
 /*    UFunction* eee = (UFunction*)StaticFindObjectFast(UFunction::StaticClass(), nullptr, TEXT("OOO"), false, true, RF_Transient);
     
       UE_LOG(LogTemp, Warning, TEXT("%s"), *eee->GetName());
       
      
         TTuple<AActor*>qwer;
     
       InvokeFunctione(AMyActor::StaticClass(), nullptr, eee, qwer, 1, 2);*/
    UFunction*fun=FindObject<UFunction>(ANY_PACKAGE,TEXT("Eee"));
    UFunction* eee = (UFunction*)StaticFindObjectFast(UFunction::StaticClass(), nullptr, TEXT("OOO"), false, true);
    TTuple<AMyActor*>a;
    InvokeFunctione(AMyActor::StaticClass(),nullptr, fun, a,1,2);
        
     UE_LOG(LogTemp, Warning, TEXT("AMyActor:%s"),*a.Get<0>()->GetName());
    
     /*   UE_LOG(LogTemp, Warning, TEXT("tupele:%s"), *qwer.Get<0>()->GetName());*/
        
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



AMyActor* AMyActor::Eee(int i, int m, TArray<AMyActor*>& aactor)
{
    UE_LOG(LogTemp, Warning, TEXT("EEE"));
	return this;
}



void AMyActor::abc(int k)
{

}

template<typename...TReturns, typename... TArgs>
void AMyActor::InvokeFunctione(UClass* objClass, UObject* obj, UFunction* func, TTuple<TReturns...>& outParams, TArgs&&... args)
{
    objClass = obj != nullptr ? obj->GetClass() : objClass;
    UObject* context = obj != nullptr ? obj : objClass;
    uint8* outPramsBuffer = (uint8*)&outParams;
    TTuple<TArgs...> inParams(Forward<TArgs>(args)...);
    void* funcPramsBuffer = (uint8*)FMemory_Alloca(func->ParmsSize);
    uint8* inPramsBuffer = (uint8*)&inParams;

    if (func->HasAnyFunctionFlags(FUNC_Native)) 
    {
        FFrame Frame(nullptr,func, &funcPramsBuffer,nullptr,func->ChildProperties);
        uint8* ReturnParams=nullptr;

        FOutParmRec**LastOut=&Frame.OutParms;
        for (TFieldIterator<FProperty>ParmIt(func); ParmIt; ++ParmIt)
        {
            FProperty* Property= *ParmIt;
            if (Property->PropertyFlags & CPF_OutParm)
            {
                if (Property->PropertyFlags & CPF_ReturnParm)
                {
                    ReturnParams= outPramsBuffer;
                    outPramsBuffer +=Property->GetSize();
                }
                else
                {
                    for (;;)
                    {
                        if (*LastOut == nullptr)
                        {
                           ( *LastOut)=(FOutParmRec*)FMemory_Alloca(sizeof(FOutParmRec));
                           (*LastOut)->PropAddr= outPramsBuffer;
                           (*LastOut)->Property=Property;
                           (*LastOut)->NextOutParm=nullptr;
                           LastOut= &(*LastOut)->NextOutParm;
                           outPramsBuffer += Property->GetSize();
                           break;
                        }
                        else
                        {
                            LastOut=&(*LastOut)->NextOutParm;
                        }
                    }
                }
            }
            else if (Property->PropertyFlags & CPF_Parm)
            {
                for (;;)
                {
                    if (*LastOut == nullptr)
                    {
                        (*LastOut) = (FOutParmRec*)FMemory_Alloca(sizeof(FOutParmRec));
                        void* PropAddr = Property->ContainerPtrToValuePtr<void*>(funcPramsBuffer);
                        if (FObjectProperty* ObjectProject = CastField<FObjectProperty>(Property))
                        {
                            ObjectProject->SetObjectPropertyValue(const_cast<uint8*>((*LastOut)->PropAddr),*(UObject**)inPramsBuffer);
                        }
                        else
                        {
                            FMemory::Memcpy(PropAddr, inPramsBuffer+Property->GetOffset_ForInternal(),Property->GetSize());
                        }
                        (*LastOut)->PropAddr = (uint8*)PropAddr;
                        (*LastOut)->Property = Property;
                        (*LastOut)->NextOutParm = nullptr;
                        LastOut = &(*LastOut)->NextOutParm;
                       /* inPramsBuffer+=Property->GetSize();*/
                        break;
                    }   
                    else
                    {
                        LastOut = &(*LastOut)->NextOutParm;
                    }
                }
            }
        }
        func->Invoke(context,Frame, ReturnParams);
        return;
    }

    

    for (TFieldIterator<FProperty> i(func); i; ++i)
    {
        FProperty* prop = *i;
        if (prop->GetFName().ToString().StartsWith("__"))
        {
            //ignore private param like __WolrdContext of function in blueprint funcion library
            continue;
        }
        void* propBuffer = prop->ContainerPtrToValuePtr<void*>(funcPramsBuffer);
        if (prop->PropertyFlags & CPF_OutParm)
        {
       
            prop->CopyCompleteValue(propBuffer, outPramsBuffer);
            outPramsBuffer += prop->GetSize();
        }
        else if (prop->PropertyFlags & CPF_Parm)
        {
            prop->CopyCompleteValue(propBuffer, inPramsBuffer);
            inPramsBuffer += prop->GetSize();
        }
    }

    context->ProcessEvent(func, funcPramsBuffer);   //call function
    outPramsBuffer = (uint8*)&outParams;    //reset to begin

    //copy back out params
    for (TFieldIterator<FProperty> i(func); i; ++i)
    {
        FProperty* prop = *i;
        if (prop->PropertyFlags & CPF_OutParm)
        {
            void* propBuffer = prop->ContainerPtrToValuePtr<void*>(funcPramsBuffer);
            prop->CopyCompleteValue(outPramsBuffer, propBuffer);
            outPramsBuffer += prop->GetSize();
        }
    }
   
}