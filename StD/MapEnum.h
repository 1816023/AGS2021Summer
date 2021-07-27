#pragma once
enum class ErrorCode : int
{
	NoError,	// エラーなし
	MsSpError,	// 拠点数スポナー数エラー
	MsError,	// 拠点数エラー
	SpError,		// スポナー数エラー
	NonMsSpError,	// 拠点スポナー設置してない時エラー
	NonMsError,		// 拠点設置してない時エラー
	NonSpError		// スポナー設置してない時エラー
};
