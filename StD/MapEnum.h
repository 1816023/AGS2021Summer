#pragma once
enum class ErrorCode : int
{
	NoError,	// �G���[�Ȃ�
	MsSpError,	// ���_���X�|�i�[���G���[
	MsError,	// ���_���G���[
	SpError,		// �X�|�i�[���G���[
	NonMsSpError,	// ���_�X�|�i�[�ݒu���ĂȂ����G���[
	NonMsError,		// ���_�ݒu���ĂȂ����G���[
	NonSpError		// �X�|�i�[�ݒu���ĂȂ����G���[
};
