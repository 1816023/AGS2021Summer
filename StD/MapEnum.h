#pragma once
enum class ErrorCode : int
{
	NoError,	// エラーなし
	MsSpError,	// 拠点数スポナー数エラー
	MsError,	// 拠点数エラー
	SpError		// スポナー数エラー
};
