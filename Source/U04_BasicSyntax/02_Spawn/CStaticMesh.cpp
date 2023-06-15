#include "CStaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Global.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Kismet/KismetMaterialLibrary.h"

ACStaticMesh::ACStaticMesh()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

void ACStaticMesh::BeginPlay()
{
	Super::BeginPlay();

	//ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> materialAsset(L"MaterialInstanceConstant'/Game/StaticMeshes/MAT_StaticMesh_Inst.MAT_StaticMesh_Inst'");

	UObject* assetObject = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, L"MaterialInstanceConstant'/Game/StaticMeshes/MAT_StaticMesh_Inst.MAT_StaticMesh_Inst'");

	UMaterialInstanceConstant* materialAsset = Cast<UMaterialInstanceConstant>(assetObject);

	 DynamicMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), materialAsset);

	if (!!materialAsset)		// materialAsset != nullptr ³ÎÃ¼Å©
		Mesh->SetMaterial(0, DynamicMaterial);

	UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.f, true);
}

void ACStaticMesh::ChangeColor()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Magenta, "Hi");

	float r = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
	float g = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
	float b = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
	float a = 1.f;

	DynamicMaterial->SetVectorParameterValue("BaseColor", FLinearColor(r, g, b, a));
	DynamicMaterial->SetScalarParameterValue("Metalic", r);
	DynamicMaterial->SetScalarParameterValue("Roughness", g);

}
