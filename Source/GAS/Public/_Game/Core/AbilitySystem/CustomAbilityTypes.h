#pragma once 

#include "GameplayEffectTypes.h"
#include "CustomAbilityTypes.generated.h"

USTRUCT(BlueprintType) 
struct FCustomGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY() 

public:

	bool IsBlockedHit() const { return bIsBlockedHit; }
	bool IsCriticalHit() const { return BIsCriticalHit; }

	void SetIsBlockedHit(const bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	void SetIsCriticalHit(const bool bInIsCriticalHit) { BIsCriticalHit = bInIsCriticalHit; }
	
	//FGameplayEffectContext 是一个 可扩展的上下文结构体，设计上允许开发者继承它。
	// 因为它会被 句柄类（FGameplayEffectContextHandle）包装成多态的“指针”，引擎需要在运行时区分“你到底是基类还是子类”。
	// // 所以它才强制要求 子类必须 override GetScriptStruct()，否则 GC/网络复制时就不知道用哪个结构体来解析。
	/** 返回用于序列化的实际结构体 */
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayEffectContext::StaticStruct();
	}

	/** 用于序列化类的参数 因为新增了两个字段*/
	//结构体多态重写他的网络复制序列化
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;
	
	virtual FGameplayEffectContext* Duplicate() const
	{
		FGameplayEffectContext* NewContext = new FGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}
protected:

	UPROPERTY()
	bool bIsBlockedHit = false; //格挡

	UPROPERTY()
	bool BIsCriticalHit = false; //暴击
};

template<>
struct TStructOpsTypeTraits<FCustomGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FCustomGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};

