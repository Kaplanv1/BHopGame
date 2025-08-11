#pragma once

UENUM()
enum class EBHopConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EBHopValidType : uint8
{
	Valid,
	Invalid,
};

UENUM()
enum class EBHopSuccessType : uint8
{
	Successful,
	Failed
};