#include "CAviCreator.h"
#include <assert.h>
#include <iostream>

CAviCreator::CAviCreator(LONG width, LONG height, 
		const char *file, LONG scale, LONG rate)
: m_Width(width), m_Height(height), m_Scale(scale), m_Rate(rate), 
	m_Size(0), m_Pixels(0), m_FrameCount(0)
{
	m_PboID[0]=0;
	m_PboID[1]=0;

	if(!Open(file)){
		Close();
		return;
	}

	CreatePBO(&m_PboID[0], m_Size);
	CreatePBO(&m_PboID[1], m_Size);

	std::cout << "create avi file: " << file << std::endl;
}

CAviCreator::~CAviCreator()
{
	Close();
	glDeleteBuffers(2, m_PboID);
	m_Pixels = NULL;

	std::cout << "write " << m_FrameCount << " frames." << std::endl;
}

bool CAviCreator::Open(const char* file)
{
	//�@AVI�t�@�C���̏�����
	AVIFileInit();

	// ���k�I�v�V����
	memset(&m_cv,0,sizeof(COMPVARS));
	m_cv.cbSize=sizeof(COMPVARS);
	m_cv.dwFlags=ICMF_COMPVARS_VALID;
	m_cv.fccHandler=comptypeDIB;
	m_cv.lQ=ICQUALITY_DEFAULT;
	if (!ICCompressorChoose(NULL, 0, NULL, NULL ,&m_cv, NULL)){
		return false;
	}

	//�@�t�@�C���I�[�v��
	if(AVIFileOpenA(&m_pAviFile, file, 
				OF_CREATE | OF_WRITE, NULL)!=0)
	{
		MessageBox(NULL, 
				TEXT("Error : �t�@�C�����J���܂���ł���"), 
				TEXT("Error !!"), MB_ICONERROR | MB_OK );
		return false;
	}

	//�@�X�g���[���쐬
	AVISTREAMINFO si = { 
		streamtypeVIDEO, 
		m_cv.fccHandler,
		0, 0, 0, 0, 
		m_Scale, 
		m_Rate, 0, 0, 0, 0, 
		(DWORD)-1, 0, 
		{ 0, 0, m_Width, m_Height }, 
		0, 0, TEXT("VIDEO")
	};
	if(AVIFileCreateStream(m_pAviFile, &m_pAviStream, &si)!= 0){
		MessageBox(NULL, 
				TEXT("Error : �ҏW�p�t�@�C���X�g���[���̍쐬�Ɏ��s���܂���"), 
				TEXT("Error !!"), MB_ICONERROR | MB_OK );
		return false;
	}

	// ���k�X�g���[��
	AVICOMPRESSOPTIONS opt;
	opt.fccType=streamtypeVIDEO;
	opt.fccHandler=m_cv.fccHandler;
	opt.dwKeyFrameEvery=m_cv.lKey;
	opt.dwQuality=m_cv.lQ;
	opt.dwBytesPerSecond=m_cv.lDataRate;
	opt.dwFlags=(m_cv.lDataRate>0?AVICOMPRESSF_DATARATE:0)
		|(m_cv.lKey>0?AVICOMPRESSF_KEYFRAMES:0);
	opt.lpFormat=NULL;
	opt.cbFormat=0;
	opt.lpParms=m_cv.lpState;
	opt.cbParms=m_cv.cbState;
	opt.dwInterleaveEvery=0;
	if(AVIMakeCompressedStream(
				&m_pCompressed, m_pAviStream ,&opt,NULL)!=AVIERR_OK){
		return false;
	}
	AVIStreamClose(m_pAviStream);

	//�@�t�H�[�}�b�g���Z�b�g
	m_Size = (((m_Width*24+31)&~31 )/8) * m_Height;
	BITMAPINFOHEADER bmih = { 
		sizeof(BITMAPINFOHEADER), 
		m_Width, 
		m_Height, 
		1, 
		24, 
		BI_RGB, 
		m_Size, 
		0, 
		0, 
		0, 
		0 
	};
	if (AVIStreamSetFormat(
				m_pCompressed, 0, &bmih, sizeof(BITMAPINFOHEADER))!=0){
		MessageBox(NULL, 
				TEXT("Error : �X�g���[���̃t�H�[�}�b�g�ݒ�Ɏ��s���܂���"), 
				TEXT("Error !!"), MB_ICONERROR | MB_OK );
		return false;
	}

	return true;
}

void CAviCreator::Close()
{
	ICCompressorFree(&m_cv);
	AVIStreamRelease(m_pCompressed);
	//AVIStreamRelease( m_pAviStream );
	AVIFileRelease( m_pAviFile );
	AVIFileExit();
}

void CAviCreator::CreatePBO(GLuint *id, GLuint size)
{
	glGenBuffers(1, id);
	glBindBuffer( GL_PIXEL_PACK_BUFFER, *id);
	glBufferData( GL_PIXEL_PACK_BUFFER, size, 0, GL_STREAM_READ );
	glBindBuffer( GL_PIXEL_PACK_BUFFER, 0);
}

bool CAviCreator::CaptureWindow()
{
	static int index = 0;
	static int nextIndex = 0;

	//�@�C���f�b�N�X����
	index = (index + 1) %2;
	nextIndex = (index + 1) %2;

	//�@�s�N�Z���f�[�^�̓ǂݎ��
	glBindBuffer( GL_PIXEL_PACK_BUFFER, m_PboID[index] );
	glReadPixels( 0, 0, m_Width, m_Height, GL_BGR, GL_UNSIGNED_BYTE, 0 );

	glBindBuffer( GL_PIXEL_PACK_BUFFER, m_PboID[nextIndex] );
	m_Pixels = (GLubyte*)glMapBuffer( GL_PIXEL_PACK_BUFFER, GL_READ_ONLY );

	//�@�t�@�C���ɏ�������
	if(AVIStreamWrite(m_pCompressed, 
				m_FrameCount++, 1, m_Pixels, m_Size, AVIIF_KEYFRAME, 
				NULL, NULL)){
		return false;
	}

	//�@�o�C���h��߂�
	glUnmapBuffer( GL_PIXEL_PACK_BUFFER );
	glBindBuffer( GL_PIXEL_PACK_BUFFER, 0 );

	return true;
}

